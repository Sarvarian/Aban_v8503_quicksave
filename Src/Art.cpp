#include "Art.hpp"

#include "All.hpp"
#include "Arm.hpp"




void Art::Step::clearAllFields() {
  memset(this, 0, sizeof(Step));
}

Art::Step::Step() { // NOLINT(*-pro-type-member-init)
  clearAllFields();
}




class ArtCore : public Art, protected Pool4 {
protected:
  /** In-house block to store volatile data. */
  /** In-house as in the same pool as the ArtCore. */
  Atm::IndexBlock volatiles_;

  Step feet_[2];
  u8 foot_ : 1;

  /** Leagued Ledger (aka Journal, Logger) */
  All all_;

  /** Resource Manager */
  Arm arm_;

  ArtCore()
  : volatiles_(defBlockAllocator().pushBlock0())
  , feet_(), foot_(0)
  , all_(All::def())
  , arm_(Arm::def())
  {
    assert(volatiles_.isValid());
    /* advance route, shutdown route. */
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

  /** Pre-SDL Initialization */
  ESysStatus init1(const int argc, char** argv) { // NOLINT(*-convert-member-functions-to-static)
    /* Do something here! */
    return E_SYS_CONTINUE;
  }

  /** On-Engine Initialization */
  ESysStatus init2(const int argc, char** argv) { // NOLINT(*-convert-member-functions-to-static)
    /* Do something here! */
    return E_SYS_CONTINUE;
  }

  /** Returns current step, and swap steps. */
  Step& stepForward() {
    Step& current = feet_[foot_];
    foot_ = foot_ ^ 0x01;
    feet_[foot_].clearAllFields();
    return current;
  }

  Step& stepFuture() {
    return feet_[foot_ ^ 0x01];
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
