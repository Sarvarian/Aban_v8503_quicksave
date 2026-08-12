#pragma once

#ifndef AB_ALM_HPP
#define AB_ALM_HPP

#include "Main.hpp"
#include "Ado.hpp"

/** Aban Low-level Memory System */
namespace Alm {

/** Memory Objects Metadata Begin */
typedef u8 Scale; /**< Generic type for buffer, block, and pool exponents. */
typedef u8 IndexLittle; /**< Index of buffers inside block. */
typedef u16 IndexMedium; /**< Index of blocks inside pool. */
typedef void* IndexBig; /**< Pointer of pools inside system memory. */
#define MM_BUFFER_UNIT_EXPONENT BINLOG_512 /**< Binlog of minimum buffer size. */
staticAssert(
  MM_BUFFER_UNIT_EXPONENT >= mul2BL(BINLOG_64, PTR_EXPONENT),
  mmBufferShouldRoomFor64PointersAtLeast)
#define MM_BLOCK_CAPACITY_EXPONENT BINLOG_128
#define MM_BLOCK_UNIT_EXPONENT mul2BL(MM_BLOCK_CAPACITY_EXPONENT, MM_BUFFER_UNIT_EXPONENT) /**< Binlog of minimum block size. */
staticAssert(
  MM_BLOCK_UNIT_EXPONENT > MM_BUFFER_UNIT_EXPONENT,
  mmBlocksShouldBeBiggerThanBuffers)
#define MM_BLOCK_CAPACITY tttUSize(MM_BLOCK_CAPACITY_EXPONENT)
#define mmBufferExponent(EXPONENT) mul2BL(MM_BUFFER_UNIT_EXPONENT, (EXPONENT))
#define mmBlockExponent(EXPONENT) mul2BL(MM_BLOCK_UNIT_EXPONENT, (EXPONENT))
#define MM_BLOCK_CAPACITY_MAX_EXPONENT U16_WIDTH
#define MM_POOL_CAPACITY_MIN tttUSize(div2BL(BINLOG_4194304, MM_BLOCK_UNIT_EXPONENT))
staticAssert(MM_POOL_CAPACITY_MIN > 0, mmPoolShouldBeBiggerThanBuffers)
#define MM_POOL_CAPACITY_MAX tttUSize(MM_BLOCK_CAPACITY_MAX_EXPONENT)
#define MM_POOL_CAPACITY_DEFAULT tttUSize(div2BL(BINLOG_33554432, MM_BLOCK_UNIT_EXPONENT))
#define mmBlockExponentCheck(VALUE) ((VALUE) > (MM_BLOCK_CAPACITY_MAX_EXPONENT - 1) || (VALUE) < 0)
#define mmPoolCapacityCheck(CAPACITY) ((CAPACITY) > MM_POOL_CAPACITY_MAX || (CAPACITY) < MM_POOL_CAPACITY_MIN)
#define mmBlockUnitCount(EXPONENT) tttUSize(EXPONENT)
#define mmBufferSize(EXPONENT) tttUSize(mmBufferExponent(EXPONENT))
#define mmBlockSize(EXPONENT) tttUSize(mmBlockExponent(EXPONENT))
#define mmPoolSize(CAPACITY) mul1BL(MM_BLOCK_UNIT_EXPONENT, CAPACITY)
/*  Memory Objects Metadata End */

/* Note about Scales: When scales get
 *   apply to sizes, sizes get bitwise
 *   shifted by the scale; in other word
 *   multiplied by 2 exponentially.
 */

/*
  ███████╗ ██████╗ ██╗   ██╗███╗   ██╗██████╗  █████╗ ████████╗██╗ ██████╗ ███╗   ██╗
  ██╔════╝██╔═══██╗██║   ██║████╗  ██║██╔══██╗██╔══██╗╚══██╔══╝██║██╔═══██╗████╗  ██║
  █████╗  ██║   ██║██║   ██║██╔██╗ ██║██║  ██║███████║   ██║   ██║██║   ██║██╔██╗ ██║
  ██╔══╝  ██║   ██║██║   ██║██║╚██╗██║██║  ██║██╔══██║   ██║   ██║██║   ██║██║╚██╗██║
  ██║     ╚██████╔╝╚██████╔╝██║ ╚████║██████╔╝██║  ██║   ██║   ██║╚██████╔╝██║ ╚████║
  ╚═╝      ╚═════╝  ╚═════╝ ╚═╝  ╚═══╝╚═════╝ ╚═╝  ╚═╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝
*/
/** Cache and minimize calling this routine.
 *  @return Returns 0 in case of failure to get system memory. */
usize totalRawMemory();

/** @return Check return for failure. */
void* allocatePool(IndexMedium capacity);

/** @return Always returns null. */
void* deallocatePool(void* location, IndexMedium capacity);

#if AB_CONCUR
/** [Multithread Safe]
 *  @param used Atomic int, head of pool usage.
 *  @param capacity  Capacity in block units.
 *  @param scale Should be less than or
 *               equal to (`MM_EXPONENT_MAX` - 1).
 *  @return Returns 0 in case of failure. */
IndexMedium pushBlock(Atomic* used, IndexMedium capacity, Scale scale);
#else
IndexMedium pushBlock(int* used, IndexMedium capacity, Scale scale);
#endif

#if AB_CONCUR
/** @brief This is NOT intended for multithread use.
 *  @param used Atomic int, head of pool usage.
 *  @param scale Amount of block units to pop. */
IndexMedium popBlock(Atomic* used, Scale scale);
#else
IndexMedium popBlock(int* used, Scale scale);
#endif

class Pool;
class Block {};
class Buffer {};

/*
  ██████╗ ██╗   ██╗███████╗███████╗███████╗██████╗
  ██╔══██╗██║   ██║██╔════╝██╔════╝██╔════╝██╔══██╗
  ██████╔╝██║   ██║█████╗  █████╗  █████╗  ██████╔╝
  ██╔══██╗██║   ██║██╔══╝  ██╔══╝  ██╔══╝  ██╔══██╗
  ██████╔╝╚██████╔╝██║     ██║     ███████╗██║  ██║
  ╚═════╝  ╚═════╝ ╚═╝     ╚═╝     ╚══════╝╚═╝  ╚═╝
*/
template<Scale SCALE>
class BufferTemplated : public Buffer {
protected:
  u8 raw_[mmBufferSize(SCALE)];
  BufferTemplated() : raw_() {}
};

class Buffer0 : public BufferTemplated<0> {};
class Buffer1 : public BufferTemplated<1> {};
class Buffer2 : public BufferTemplated<2> {};
class Buffer3 : public BufferTemplated<3> {};
staticAssert(sizeof(Buffer0) == mmBufferSize(0), IS_SIZE_OF_CLASS_BUFFER0_CORRECT)
staticAssert(sizeof(Buffer1) == mmBufferSize(1), IS_SIZE_OF_CLASS_BUFFER1_CORRECT)
staticAssert(sizeof(Buffer2) == mmBufferSize(2), IS_SIZE_OF_CLASS_BUFFER2_CORRECT)
staticAssert(sizeof(Buffer3) == mmBufferSize(3), IS_SIZE_OF_CLASS_BUFFER3_CORRECT)

/*
  ██████╗ ██╗      ██████╗  ██████╗██╗  ██╗
  ██╔══██╗██║     ██╔═══██╗██╔════╝██║ ██╔╝
  ██████╔╝██║     ██║   ██║██║     █████╔╝
  ██╔══██╗██║     ██║   ██║██║     ██╔═██╗
  ██████╔╝███████╗╚██████╔╝╚██████╗██║  ██╗
  ╚═════╝ ╚══════╝ ╚═════╝  ╚═════╝╚═╝  ╚═╝
*/
template<class BUFFER_TYPE>
class BlockTemplated : public Block {
protected:
  BUFFER_TYPE buffer_[MM_BLOCK_CAPACITY];
  BlockTemplated() : buffer_(0) {}
public:
  bool isValid(const Pool* location) const {
    return static_cast<const void*>(location) != static_cast<const void*>(buffer_) ? true : false;
  }
  BUFFER_TYPE* operator[](const IndexLittle index) {
    return &(buffer_[index]);
  }
};

class Block0 : public BlockTemplated<Buffer0> {};
class Block1 : public BlockTemplated<Buffer1> {};
class Block2 : public BlockTemplated<Buffer2> {};
class Block3 : public BlockTemplated<Buffer3> {};
staticAssert(sizeof(Block0) == mmBlockSize(0), IS_SIZE_OF_CLASS_BLOCK0_CORRECT)
staticAssert(sizeof(Block1) == mmBlockSize(1), IS_SIZE_OF_CLASS_BLOCK1_CORRECT)
staticAssert(sizeof(Block2) == mmBlockSize(2), IS_SIZE_OF_CLASS_BLOCK2_CORRECT)
staticAssert(sizeof(Block3) == mmBlockSize(3), IS_SIZE_OF_CLASS_BLOCK3_CORRECT)

/*
  ██╗███╗   ██╗██████╗ ██╗ ██████╗███████╗███████╗
  ██║████╗  ██║██╔══██╗██║██╔════╝██╔════╝██╔════╝
  ██║██╔██╗ ██║██║  ██║██║██║     █████╗  ███████╗
  ██║██║╚██╗██║██║  ██║██║██║     ██╔══╝  ╚════██║
  ██║██║ ╚████║██████╔╝██║╚██████╗███████╗███████║
  ╚═╝╚═╝  ╚═══╝╚═════╝ ╚═╝ ╚═════╝╚══════╝╚══════╝
*/

class IndexItem {
public:
  u8 item;
  IndexItem() : item(0) {}
};

class IndexBuffer {
public:
  IndexLittle buffer;
  IndexBuffer() : buffer(0) {}
};

class IndexBlock {
protected:
  IndexMedium index_;
  IndexBlock() : index_(0) {}
public:
  explicit IndexBlock(const IndexMedium index) : index_(index) {}
  static IndexBlock def(const IndexMedium index) { return IndexBlock(index); }
  bool isValid() const {
    return index_ != 0 ? true : false;
  }
  Block0* toBlock0(Pool* location) const { return reinterpret_cast<Block0*>(reinterpret_cast<usize>(location) + (mmBlockSize(0) * index_)); }
  Block1* toBlock1(Pool* location) const { return reinterpret_cast<Block1*>(reinterpret_cast<usize>(location) + (mmBlockSize(0) * index_)); }
  Block2* toBlock2(Pool* location) const { return reinterpret_cast<Block2*>(reinterpret_cast<usize>(location) + (mmBlockSize(0) * index_)); }
  Block3* toBlock3(Pool* location) const { return reinterpret_cast<Block3*>(reinterpret_cast<usize>(location) + (mmBlockSize(0) * index_)); }
};

class Index1 : public IndexItem, public IndexBuffer { /* Empty */ };

class Index2 : public Index1, public IndexBlock { /* Empty */ };

class Index3 : public Index2 {
public:
  IndexLittle pool;
  Index3() : pool(0) {}
};

/*
  ██████╗  ██████╗  ██████╗ ██╗
  ██╔══██╗██╔═══██╗██╔═══██╗██║
  ██████╔╝██║   ██║██║   ██║██║
  ██╔═══╝ ██║   ██║██║   ██║██║
  ██║     ╚██████╔╝╚██████╔╝███████╗
  ╚═╝      ╚═════╝  ╚═════╝ ╚══════╝
*/
class Pool {
protected:
  Pool() {}
public:
  class BlockAllocator {
  protected:
#if AB_CONCUR
    Atomic used_; /**< Always initialize it with 1.
                       Block index 0, is implicitly allocated.
                       So, we can use index 0 as null index. */
    BlockAllocator() : used_() { atomicSet(&used_, 1); }
#else
    int used_;
    BlockAllocator() : used_(1) {}
#endif
  public:
    IndexBlock pushBlock0(const IndexMedium capacity) { return IndexBlock::def(pushBlock(&used_, capacity, 0)); }
    IndexBlock pushBlock1(const IndexMedium capacity) { return IndexBlock::def(pushBlock(&used_, capacity, 1)); }
    IndexBlock pushBlock2(const IndexMedium capacity) { return IndexBlock::def(pushBlock(&used_, capacity, 2)); }
    IndexBlock pushBlock3(const IndexMedium capacity) { return IndexBlock::def(pushBlock(&used_, capacity, 3)); }
  };
};

template<IndexMedium CAPACITY>
class PoolTemplated : public Pool {
protected:
  PoolTemplated() {}
  PoolTemplated* getPoolTemplated() { return this; }
public:
  static PoolTemplated* def() {
    return static_cast<PoolTemplated*>(allocatePool(CAPACITY));
  }
  PoolTemplated* undef() {
    return static_cast<PoolTemplated*>(deallocatePool(this, CAPACITY));
  }

  class BlockAllocator : public Pool::BlockAllocator {
  public:
    static BlockAllocator def() {
      return BlockAllocator();
    }
    IndexBlock pushBlock0() { return pushBlock0(CAPACITY); }
    IndexBlock pushBlock1() { return pushBlock1(CAPACITY); }
    IndexBlock pushBlock2() { return pushBlock2(CAPACITY); }
    IndexBlock pushBlock3() { return pushBlock3(CAPACITY); }
  };

  BlockAllocator defBlockAllocator() {
    return BlockAllocator::def();
  }
};

class Pool4 : public PoolTemplated<TTT_6> {
protected:
  Pool4() {}
public:
  static Pool4* def() {
    return reinterpret_cast<Pool4*>(PoolTemplated::def());
  }
  Pool4* undef() {
    return reinterpret_cast<Pool4*>(getPoolTemplated()->undef());
  }
};

class Pool8 : public PoolTemplated<TTT_7> {
protected:
  Pool8() {}
public:
  static Pool8* def() {
    return reinterpret_cast<Pool8*>(PoolTemplated::def());
  }
  Pool8* undef() {
    return reinterpret_cast<Pool8*>(getPoolTemplated()->undef());
  }
};

class Pool16 : public PoolTemplated<TTT_8> {
protected:
  Pool16() {}
public:
  static Pool16* def() {
    return reinterpret_cast<Pool16*>(PoolTemplated::def());
  }
  Pool16* undef() {
    return reinterpret_cast<Pool16*>(getPoolTemplated()->undef());
  }
};

class Pool32 : public PoolTemplated<TTT_9> {
protected:
  Pool32() {}
public:
  static Pool32* def() {
    return reinterpret_cast<Pool32*>(PoolTemplated::def());
  }
  Pool32* undef() {
    return reinterpret_cast<Pool32*>(getPoolTemplated()->undef());
  }
};

class Pool64 : public PoolTemplated<TTT_10> {
protected:
  Pool64() {}
public:
  static Pool64* def() {
    return reinterpret_cast<Pool64*>(PoolTemplated::def());
  }
  Pool64* undef() {
    return reinterpret_cast<Pool64*>(getPoolTemplated()->undef());
  }
};

class Pool128 : public PoolTemplated<TTT_11> {
protected:
  Pool128() {}
public:
  static Pool128* def() {
    return reinterpret_cast<Pool128*>(PoolTemplated::def());
  }
  Pool128* undef() {
    return reinterpret_cast<Pool128*>(getPoolTemplated()->undef());
  }
};

class Pool256 : public PoolTemplated<TTT_12> {
protected:
  Pool256() {}
public:
  static Pool256* def() {
    return reinterpret_cast<Pool256*>(PoolTemplated::def());
  }
  Pool256* undef() {
    return reinterpret_cast<Pool256*>(getPoolTemplated()->undef());
  }
};

class Pool512 : public PoolTemplated<TTT_13> {
protected:
  Pool512() {}
public:
  static Pool512* def() {
    return reinterpret_cast<Pool512*>(PoolTemplated::def());
  }
  Pool512* undef() {
    return reinterpret_cast<Pool512*>(getPoolTemplated()->undef());
  }
};

class Pool1024 : public PoolTemplated<TTT_14> {
protected:
  Pool1024() {}
public:
  static Pool1024* def() {
    return reinterpret_cast<Pool1024*>(PoolTemplated::def());
  }
  Pool1024* undef() {
    return reinterpret_cast<Pool1024*>(getPoolTemplated()->undef());
  }
};

class Pool2048 : public PoolTemplated<TTT_15> {
protected:
  Pool2048() {}
public:
  static Pool2048* def() {
    return reinterpret_cast<Pool2048*>(PoolTemplated::def());
  }
  Pool2048* undef() {
    return reinterpret_cast<Pool2048*>(getPoolTemplated()->undef());
  }
};

inline Pool* pool4Undef(Pool* pool) { return static_cast<Pool4*>(pool)->undef(); } // NOLINT(*-pro-type-static-cast-downcast)
inline Pool* pool8Undef(Pool* pool) { return static_cast<Pool8*>(pool)->undef(); } // NOLINT(*-pro-type-static-cast-downcast)
inline Pool* pool16Undef(Pool* pool) { return static_cast<Pool16*>(pool)->undef(); } // NOLINT(*-pro-type-static-cast-downcast)
inline Pool* pool32Undef(Pool* pool) { return static_cast<Pool32*>(pool)->undef(); } // NOLINT(*-pro-type-static-cast-downcast)
inline Pool* pool64Undef(Pool* pool) { return static_cast<Pool64*>(pool)->undef(); } // NOLINT(*-pro-type-static-cast-downcast)
inline Pool* pool128Undef(Pool* pool) { return static_cast<Pool128*>(pool)->undef(); } // NOLINT(*-pro-type-static-cast-downcast)
inline Pool* pool256Undef(Pool* pool) { return static_cast<Pool256*>(pool)->undef(); } // NOLINT(*-pro-type-static-cast-downcast)
inline Pool* pool512Undef(Pool* pool) { return static_cast<Pool512*>(pool)->undef(); } // NOLINT(*-pro-type-static-cast-downcast)
inline Pool* pool1024Undef(Pool* pool) { return static_cast<Pool1024*>(pool)->undef(); } // NOLINT(*-pro-type-static-cast-downcast)
inline Pool* pool2048Undef(Pool* pool) { return static_cast<Pool2048*>(pool)->undef(); } // NOLINT(*-pro-type-static-cast-downcast)

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
    POOL_DESTRUCTOR_COUNT,
    INVALID_INDEX = 0x0F
  };
  staticAssert(POOL_DESTRUCTOR_COUNT <= 0x0F, EDestructorIndex_CAN_FIT_INTO_A_NIBBLE)
  staticAssert(INVALID_INDEX <= 0x0F, INVALID_INDEX_CAN_FIT_INTO_A_NIBBLE)

  class DestructorIndexDouble {
  protected:
    u8 first_ : 4;
    u8 second_ : 4;
  public:
    DestructorIndexDouble() : first_(INVALID_INDEX), second_(INVALID_INDEX) {}
    u8 getFirst() const { return first_; }
    u8 getSecond() const { return second_; }
    void setFirst(const u8 nibble) { first_ = nibble & 0x0F; }
    void setSecond(const u8 nibble) { second_ = nibble & 0x0F; }
  };

  typedef Pool* (*DestructorProc)(Pool*);

protected:

  DestructorProc destructor[POOL_DESTRUCTOR_COUNT];

  PoolDestructor() : destructor() {
    destructor[POOL_4_DESTRUCTOR_INDEX]    = pool4Undef;
    destructor[POOL_8_DESTRUCTOR_INDEX]    = pool8Undef;
    destructor[POOL_16_DESTRUCTOR_INDEX]   = pool16Undef;
    destructor[POOL_32_DESTRUCTOR_INDEX]   = pool32Undef;
    destructor[POOL_64_DESTRUCTOR_INDEX]   = pool64Undef;
    destructor[POOL_128_DESTRUCTOR_INDEX]  = pool128Undef;
    destructor[POOL_256_DESTRUCTOR_INDEX]  = pool256Undef;
    destructor[POOL_512_DESTRUCTOR_INDEX]  = pool512Undef;
    destructor[POOL_1024_DESTRUCTOR_INDEX] = pool1024Undef;
    destructor[POOL_2048_DESTRUCTOR_INDEX] = pool2048Undef;
  }

public:

  static PoolDestructor def() {
    return PoolDestructor();
  }

  Pool* destroyFirstNibbleIndex(Pool* pool, const DestructorIndexDouble index) const {
    assert(index.getFirst() < POOL_DESTRUCTOR_COUNT);
    return destructor[index.getFirst()](pool);
  }

  Pool* destroySecondNibbleIndex(Pool* pool, const DestructorIndexDouble index) const {
    assert(index.getSecond() < POOL_DESTRUCTOR_COUNT);
    return destructor[index.getSecond()](pool);
  }

};
staticAssert(sizeof(PoolDestructor) <= sizeof(Buffer0), PoolDestructor_CAN_FIT_INTO_A_Buffer0)

} /* namespace Alm */

using Alm::Buffer0;
using Alm::Buffer1;
using Alm::Buffer2;
using Alm::Buffer3;
using Alm::Block0;
using Alm::Block1;
using Alm::Block2;
using Alm::Block3;
using Alm::IndexItem;
using Alm::IndexBuffer;
using Alm::IndexBlock;
using Alm::Index1;
using Alm::Index2;
using Alm::Index3;
using Alm::Pool4;
using Alm::Pool8;
using Alm::Pool16;
using Alm::Pool32;
using Alm::Pool64;
using Alm::Pool128;
using Alm::Pool256;
using Alm::Pool512;
using Alm::Pool1024;
using Alm::Pool2048;

#endif /* AB_ALM_HPP */
