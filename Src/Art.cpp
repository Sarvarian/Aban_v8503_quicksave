#include "Art.hpp"

#include "Main.hpp"
#include "Alm.hpp"
#include "All.hpp"

class ArtCore : public Art {
private:
  ArtCore() { /* Empty */ }
  /* ReSharper disable once CppDeclaratorNeverUsed */
  Block0* castBlock() { return reinterpret_cast<Block0*>(this); }
  Pool4* castPool() { return reinterpret_cast<Pool4*>(this); }

public:
  Art* def() {
    return this;
  }

  Art* undef() {
    castPool()->undef();
    return null;
  }

};
/* Extra Note About Memory Allocation Of ArtCore: ArtCore is and positioned at first block of the first pool. */
staticAssert(sizeof(ArtCore) <= sizeof(Block0), ArtCore_SHOULD_FIT_INTO_A_Block0)

Art* Art::def() {
  /* Art is and positioned at first block of the first pool. */
  ArtCore* art = reinterpret_cast<ArtCore*>(IndexBlock::def(0).toBlock0(Pool4::def()));
  if (art == null) {
    All::firstPoolAllocationForArtFailed();
    return null;
  }
  return art->def();
}

// ReSharper disable once CppDFAConstantFunctionResult
Art* Art::undef() {
  return static_cast<ArtCore*>(this)->undef(); // NOLINT(*-pro-type-static-cast-downcast)
}
