#include "Art.hpp"

#include "Main.hpp"
#include "Alm.hpp"
#include "Journal.hpp"

class ArtCore {
public:
  Art* def();
  Art* undef();
private:
  Block0* toBlock();
  Pool4* toPool();
};
/* Extra Note About Memory Allocation Of ArtCore: ArtCore is and positioned at first block of the first pool. */
staticAssert(sizeof(ArtCore) <= sizeof(Block0), ArtCore_SHOULD_FIT_INTO_A_Block0)

Art* ArtCore::def() {
  return reinterpret_cast<Art*>(this);
}

Art* ArtCore::undef() {
  toPool()->undef();
  return null;
}

Block0* ArtCore::toBlock() {
  return reinterpret_cast<Block0*>(this);
}

Pool4* ArtCore::toPool() {
  return reinterpret_cast<Pool4*>(this);
}

Art::Art() {
}

Art* Art::def() {
  /* Art is and positioned at first block of the first pool. */
  ArtCore* art = reinterpret_cast<ArtCore*>(BlockIndex::def(0).toBlock0(Pool4::def()));
  if (art == null) {
    Journal::firstPoolAllocationForArtFailed();
    return null;
  }
  return art->def();
}

// ReSharper disable once CppDFAConstantFunctionResult
Art* Art::undef() {
  return toCore()->undef();
}

ArtCore* Art::toCore() {
  return reinterpret_cast<ArtCore*>(this);
}
