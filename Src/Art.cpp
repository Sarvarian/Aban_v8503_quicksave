#include "Art.hpp"

#include "Main.hpp"
#include "Alm.hpp"
#include "All.hpp"




class ArtCore : public Art, protected Pool4 {
protected:
  Alm::IndexBlock volatile_block_in_house_;
  Step feet_[2];
  u8 foot_ : 1;

  ArtCore() : feet_(), foot_(0) {
    /* advance route, shutdown route.
     */
    volatile_block_in_house_ = defBlockAllocator().pushBlock0();
    assert(volatile_block_in_house_.isValid());
  }

public:
  static Art* def(Pool4* pool) {
    ArtCore* self = static_cast<ArtCore*>(pool); // NOLINT(*-pro-type-static-cast-downcast)
    (*self) = ArtCore();
    return self;
  }

  Art* undef() {
    static_cast<Pool4*>(this)->undef();
    return null;
  }

  /** Returns current step, and swap steps. */
  Step& stepForward() {
    Step& current = feet_[foot_];
    foot_ = foot_ ^ 0x01;
    memset(&feet_[foot_], 0, sizeof(feet_[foot_]));
    return current;
  }

};
/* ArtCore is positioned at the first block of the first pool. */
staticAssert(sizeof(ArtCore) <= sizeof(Block0), ArtCore_SHOULD_FIT_INTO_A_Block0)




Art* Art::def() {
  /* Art is positioned at the first block of the first pool. */
  Pool4* pool = Pool4::def();
  if (pool == null) {
    All::firstPoolAllocationForArtFailed();
    return null;
  }
  return ArtCore::def(pool);
}

ArtCore& Art::castCore() {
  return *static_cast<ArtCore*>(this); // NOLINT(*-pro-type-static-cast-downcast)
}

// ReSharper disable once CppDFAConstantFunctionResult
Art* Art::undef() {
  return castCore().undef();
}

Art::Step& Art::stepForward() {
  return castCore().stepForward();
}
