#include "Art.hpp"

#include "Main.hpp"
#include "Alm.hpp"
#include "All.hpp"
#include "Arm.hpp"




void Art::Step::clearAllFields() {
  memset(this, 0, sizeof(Step));
}

// ReSharper disable once CppPossiblyUninitializedMember
Art::Step::Step() { // NOLINT(*-pro-type-member-init)
  clearAllFields();
}




class ArtCore : public Art, protected Pool4 {
protected:
  /** In-house block to store volatile data. */
  /** In-house as in the same pool as the ArtCore. */
  Alm::IndexBlock volatiles;

  Step feet[2];
  u8 foot : 1;

  /** Leagued Ledger (aka Journal, Logger) */
  All ll;

  /** Resource Manager */
  Arm rm;

  ArtCore()
  : volatiles(defBlockAllocator().pushBlock0())
  , feet(), foot(0)
  , ll(All::def())
  , rm(Arm::def())
  {
    assert(volatiles.isValid());
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

  void initCmdLine(const int argc, char** argv) {
    /* Do something here! */
  }

  /** Returns current step, and swap steps. */
  Step& stepForward() {
    Step& current = feet[foot];
    foot = foot ^ 0x01;
    feet[foot].clearAllFields();
    return current;
  }

  Step& stepFuture() {
    return feet[foot ^ 0x01];
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
ArtCore& Art::castCore() { return *static_cast<ArtCore*>(this); /* NOLINT(*-pro-type-static-cast-downcast) */ }
/* ReSharper disable once CppDFAConstantFunctionResult */
Art* Art::undef() { return castCore().undef(); }
void Art::initCmdLine(const int argc, char** argv) { return castCore().initCmdLine(argc, argv); }
Art::Step& Art::stepForward() { return castCore().stepForward(); }
Art::Step& Art::stepFuture() { return castCore().stepFuture(); }
