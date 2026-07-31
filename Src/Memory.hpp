#pragma once

#ifndef AB_MEMORY_HPP
#define AB_MEMORY_HPP

#include "Main.hpp"
#include "Concur.hpp"

namespace Memory {

/*
███╗   ███╗ █████╗  ██████╗██████╗  ██████╗ ███████╗
████╗ ████║██╔══██╗██╔════╝██╔══██╗██╔═══██╗██╔════╝
██╔████╔██║███████║██║     ██████╔╝██║   ██║███████╗
██║╚██╔╝██║██╔══██║██║     ██╔══██╗██║   ██║╚════██║
██║ ╚═╝ ██║██║  ██║╚██████╗██║  ██║╚██████╔╝███████║
╚═╝     ╚═╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝
*/
/** Memory Objects Metadata Begin */
typedef u8 Scale; /**< Generic type for buffer, block, and pool exponents. */
typedef u8 LittleIndex; /**< Buffer index inside blocks. */
typedef u16 Index; /**< Block index inside pools. */
typedef void* mmPoolIndexType; /**< Pool pointer inside system memory. */
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
void* allocatePool(Index capacity);

/** @return Always returns null. */
void* deallocatePool(void* location, Index capacity);

#if AB_CONCUR
/** [Multithread Safe]
 *  @param used Atomic int, head of pool usage.
 *  @param capacity  Capacity in block units.
 *  @param scale Should be less than or
 *               equal to (`MM_EXPONENT_MAX` - 1).
 *  @return Returns 0 in case of failure. */
Index pushBlock(Atomic* used, Index capacity, Scale scale);
#else
Index pushBlock(int* used, Index capacity, Scale scale);
#endif

#if AB_CONCUR
/** @brief This is NOT intended for multithread use.
 *  @param used Atomic int, head of pool usage.
 *  @param scale Amount of block units to pop. */
Index popBlock(Atomic* used, Scale scale);
#else
Index popBlock(int* used, Scale scale);
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
  BUFFER_TYPE* operator[](const LittleIndex index) {
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
██╗███╗   ██╗██████╗ ███████╗██╗  ██╗
██║████╗  ██║██╔══██╗██╔════╝╚██╗██╔╝
██║██╔██╗ ██║██║  ██║█████╗   ╚███╔╝
██║██║╚██╗██║██║  ██║██╔══╝   ██╔██╗
██║██║ ╚████║██████╔╝███████╗██╔╝ ██╗
╚═╝╚═╝  ╚═══╝╚═════╝ ╚══════╝╚═╝  ╚═╝
*/
class BlockIndex {
private:
  Index index_;
  BlockIndex() : index_(0) {}
public:
  explicit BlockIndex(const Index index) : index_(index) {}
  bool isValid() const {
    return index_ != 0 ? true : false;
  }
  Block0* toBlock0(Pool* location) const { return reinterpret_cast<Block0*>(reinterpret_cast<usize>(location) + (mmBlockSize(0) * index_)); }
  Block1* toBlock1(Pool* location) const { return reinterpret_cast<Block1*>(reinterpret_cast<usize>(location) + (mmBlockSize(0) * index_)); }
  Block2* toBlock2(Pool* location) const { return reinterpret_cast<Block2*>(reinterpret_cast<usize>(location) + (mmBlockSize(0) * index_)); }
  Block3* toBlock3(Pool* location) const { return reinterpret_cast<Block3*>(reinterpret_cast<usize>(location) + (mmBlockSize(0) * index_)); }
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
    BlockIndex pushBlock0(const Index capacity) { return BlockIndex(pushBlock(&used_, capacity, 0)); }
    BlockIndex pushBlock1(const Index capacity) { return BlockIndex(pushBlock(&used_, capacity, 1)); }
    BlockIndex pushBlock2(const Index capacity) { return BlockIndex(pushBlock(&used_, capacity, 2)); }
    BlockIndex pushBlock3(const Index capacity) { return BlockIndex(pushBlock(&used_, capacity, 3)); }
  };
};

template<Index CAPACITY>
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
    BlockIndex pushBlock0() { return pushBlock0(CAPACITY); }
    BlockIndex pushBlock1() { return pushBlock1(CAPACITY); }
    BlockIndex pushBlock2() { return pushBlock2(CAPACITY); }
    BlockIndex pushBlock3() { return pushBlock3(CAPACITY); }
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

} /* namespace Memory */

using Memory::Buffer0;
using Memory::Buffer1;
using Memory::Buffer2;
using Memory::Buffer3;
using Memory::Block0;
using Memory::Block1;
using Memory::Block2;
using Memory::Block3;
using Memory::BlockIndex;
using Memory::Pool4;
using Memory::Pool8;
using Memory::Pool16;
using Memory::Pool32;
using Memory::Pool64;
using Memory::Pool128;
using Memory::Pool256;
using Memory::Pool512;
using Memory::Pool1024;
using Memory::Pool2048;

#endif /* AB_MEMORY_HPP */
