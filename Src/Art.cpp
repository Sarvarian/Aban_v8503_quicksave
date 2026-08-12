#include "Art.hpp"

#include "Main.hpp"
#include "Alm.hpp"
#include "All.hpp"

class PoolDestructor {
public:

  enum EDestructorIndex {
    POOL_4_DESTRUCTOR_INDEX = 0,
    POOL_8_DESTRUCTOR_INDEX,
    POOL_16_DESTRUCTOR_INDEX,
    POOL_32_DESTRUCTOR_INDEX,
    POOL_64_DESTRUCTOR_INDEX,
    POOL_128_DESTRUCTOR_INDEX,
    POOL_256_DESTRUCTOR_INDEX,
    POOL_512_DESTRUCTOR_INDEX,
    POOL_1024_DESTRUCTOR_INDEX,
    POOL_2048_DESTRUCTOR_INDEX,
    POOL_DESTRUCTOR_COUNT
  };
  staticAssert(POOL_DESTRUCTOR_COUNT < U8_MAX, EDestructorIndex_CAN_FIT_INTO_AN_u8)

  typedef u8 DestructorIndex;

  typedef Alm::Pool* (*Destructor)(Alm::Pool*);

protected:

  Destructor destructor[POOL_DESTRUCTOR_COUNT];

  PoolDestructor() : destructor() {
    destructor[POOL_4_DESTRUCTOR_INDEX]    = Alm::pool4Undef;
    destructor[POOL_8_DESTRUCTOR_INDEX]    = Alm::pool8Undef;
    destructor[POOL_16_DESTRUCTOR_INDEX]   = Alm::pool16Undef;
    destructor[POOL_32_DESTRUCTOR_INDEX]   = Alm::pool32Undef;
    destructor[POOL_64_DESTRUCTOR_INDEX]   = Alm::pool64Undef;
    destructor[POOL_128_DESTRUCTOR_INDEX]  = Alm::pool128Undef;
    destructor[POOL_256_DESTRUCTOR_INDEX]  = Alm::pool256Undef;
    destructor[POOL_512_DESTRUCTOR_INDEX]  = Alm::pool512Undef;
    destructor[POOL_1024_DESTRUCTOR_INDEX] = Alm::pool1024Undef;
    destructor[POOL_2048_DESTRUCTOR_INDEX] = Alm::pool2048Undef;
  }

public:

  static PoolDestructor def() {
    return PoolDestructor();
  }

  Alm::Pool* destroy(Alm::Pool* pool, const DestructorIndex destructor_index) const {
    return destructor[destructor_index](pool);
  }
};
staticAssert(sizeof(PoolDestructor) <= sizeof(Buffer0), PoolDestructor_CAN_FIT_INTO_A_Buffer0)

class ArtCore : public Art, public Pool4 {
protected:

  PoolDestructor pool_destructor_;

  ArtCore()
  : pool_destructor_(PoolDestructor::def())
  { /* Empty */ }

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
/* Extra Note About Memory Allocation Of ArtCore: ArtCore is and positioned at first block of the first pool. */
staticAssert(sizeof(ArtCore) <= sizeof(Block0), ArtCore_SHOULD_FIT_INTO_A_Block0)

Art* Art::def() {
  /* Art is positioned at first block of the first pool. */
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
