#include "Art.hpp"

#include "Main.hpp"
#include "Alm.hpp"
#include "All.hpp"




class ArtCore : public Art, protected Pool4 {
protected:

  ArtCore() { /* Empty */ }

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

};
/* Extra Note About Memory Allocation Of ArtCore: ArtCore is positioned at the first block of the first pool. */
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

// ReSharper disable once CppDFAConstantFunctionResult
Art* Art::undef() {
  return static_cast<ArtCore*>(this)->undef(); // NOLINT(*-pro-type-static-cast-downcast)
}
