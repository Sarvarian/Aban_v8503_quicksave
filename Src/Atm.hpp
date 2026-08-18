#pragma once

#ifndef AB_ATM_HPP
#define AB_ATM_HPP

#include "Main.hpp"
#include "Alm.hpp"

/** Aban Typed Memory System */
namespace Atm {

using namespace Alm;

/*
  ██████╗ ██╗   ██╗███████╗███████╗███████╗██████╗
  ██╔══██╗██║   ██║██╔════╝██╔════╝██╔════╝██╔══██╗
  ██████╔╝██║   ██║█████╗  █████╗  █████╗  ██████╔╝
  ██╔══██╗██║   ██║██╔══╝  ██╔══╝  ██╔══╝  ██╔══██╗
  ██████╔╝╚██████╔╝██║     ██║     ███████╗██║  ██║
  ╚═════╝  ╚═════╝ ╚═╝     ╚═╝     ╚══════╝╚═╝  ╚═╝
*/
template<typename ITEM, Scale SCALE>
class BufferTemplated : public Buffer {
public:
  enum {
    CAPACITY = (mmBufferSize(SCALE) / sizeof(ITEM))
  };

protected:
  ITEM raw_[CAPACITY];

public:
  BufferTemplated() : raw_() {
    /* Empty */
  }

  ITEM* get(const usize index) {
    assert(index <= CAPACITY);
    return &raw_[index];
  }
};

class Buffer0 : public BufferTemplated<u8, 0> {};
class Buffer1 : public BufferTemplated<u8, 1> {};
class Buffer2 : public BufferTemplated<u8, 2> {};
class Buffer3 : public BufferTemplated<u8, 3> {};
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

/** Index 0 is reserved as invalid index.
 *
 *  Valid indices start from 1.
 *
 *  To index into an actual C/C++ array (a buffer)
 *  decrement `index_` by one, before indexing.
 */
class IndexItem {
public:
  typedef u16 Base;

  enum {
    INVALID = 0 /**< This also indicates start of a new bank indices. */
  };

protected:
  const Base index_;

public:
  IndexItem() : index_(INVALID) {
    /* Empty */
  }

  explicit IndexItem(const Base index) : index_(index) {
    /* Empty */
  }

  template<typename ITEM, Scale SCALE>
  ITEM* get(BufferTemplated<ITEM, SCALE>* array) const {
    assert(index_ != INVALID);
    return array->get(index_ - 1);
  }

  template<typename ITEM, Scale SCALE>
  ITEM* get(BufferTemplated<ITEM, SCALE>& array) const {
    return get(&array);
  }

  bool isValid() const {
    return index_ != INVALID ? true : false;
  }

  operator Base() const {
  return index_;
  }
};

class IndexBuffer {
public:
  IndexLittle buffer;
  IndexBuffer() : buffer(0) {}
};

class IndexBlock {
protected:
  IndexMedium index_;
public:
  IndexBlock() : index_(0) {}
  explicit IndexBlock(const IndexMedium index) : index_(index) {}
  static IndexBlock def(const IndexMedium index) { return IndexBlock(index); }
  bool isValid() const { return index_ != 0 ? true : false; }
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
    IndexBlock pushBlock0(const IndexMedium capacity) { return IndexBlock::def(pushBlock(&used_, capacity, 0)); }
    IndexBlock pushBlock1(const IndexMedium capacity) { return IndexBlock::def(pushBlock(&used_, capacity, 1)); }
    IndexBlock pushBlock2(const IndexMedium capacity) { return IndexBlock::def(pushBlock(&used_, capacity, 2)); }
    IndexBlock pushBlock3(const IndexMedium capacity) { return IndexBlock::def(pushBlock(&used_, capacity, 3)); }
  };
};

template<IndexMedium CAPACITY_>
class PoolTemplated : public Pool {
protected:
  PoolTemplated() {}
  PoolTemplated* getPoolTemplated() { return this; }
public:
  enum { CAPACITY = CAPACITY_ };

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
    IndexBlock pushBlock0() { return static_cast<Pool::BlockAllocator>(*this).pushBlock0(CAPACITY); }
    IndexBlock pushBlock1() { return static_cast<Pool::BlockAllocator>(*this).pushBlock1(CAPACITY); }
    IndexBlock pushBlock2() { return static_cast<Pool::BlockAllocator>(*this).pushBlock2(CAPACITY); }
    IndexBlock pushBlock3() { return static_cast<Pool::BlockAllocator>(*this).pushBlock3(CAPACITY); }
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

  class IndexDouble {
  protected:
    u8 first_ : 4;
    u8 second_ : 4;
  public:
    IndexDouble() : first_(INVALID_INDEX), second_(INVALID_INDEX) {}
    static IndexDouble def() { return IndexDouble(); }
    u8 getFirst() const { return first_; }
    u8 getSecond() const { return second_; }
    void setFirst(const u8 nibble) { first_ = nibble & 0x0F; }
    void setSecond(const u8 nibble) { second_ = nibble & 0x0F; }
  };
  staticAssert(sizeof(IndexDouble) == sizeof(u8), IndexDouble_SHOULD_BE_U8)

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

  Pool* destroyFirstNibbleIndex(Pool* pool, const IndexDouble index) const {
    assert(index.getFirst() < POOL_DESTRUCTOR_COUNT);
    return destructor[index.getFirst()](pool);
  }

  Pool* destroySecondNibbleIndex(Pool* pool, const IndexDouble index) const {
    assert(index.getSecond() < POOL_DESTRUCTOR_COUNT);
    return destructor[index.getSecond()](pool);
  }

};
staticAssert(sizeof(PoolDestructor) <= sizeof(Buffer0), PoolDestructor_CAN_FIT_INTO_A_Buffer0)

class PoolDestructorArray {
public:
  enum { CAPACITY = (sizeof(Buffer0) / sizeof(PoolDestructor::IndexDouble)) };
protected:
  PoolDestructor::IndexDouble indices[CAPACITY];
public:
  Pool* destroy(const PoolDestructor& destructor, Pool* pool, const IndexLittle item) const {
    return isEvenBL(item)
    ? destructor.destroyFirstNibbleIndex(pool, indices[halfBL(item)])
    : destructor.destroySecondNibbleIndex(pool, indices[halfBL(item)])
    ;
  }
  void set(const IndexLittle item, const u8 value) {
    if (isEvenBL(item)) {
      indices[halfBL(item)].setFirst(value);
    } else {
      indices[halfBL(item)].setSecond(value);
    }
  }
};
staticAssert(sizeof(PoolDestructorArray) == sizeof(Buffer0), PoolDestructorArray_CAN_FIT_INTO_A_Buffer0)

class PoolDestructorArrayBook {
public:
  enum { CAPACITY = ((sizeof(Buffer0) / PTR_SIZE) - 1) /* Calculate Buffer Capacity - Subtract 1 `next` Pointer */ };
  PoolDestructorArray* buffer[CAPACITY];
  PoolDestructorArrayBook* next;
};
staticAssert(sizeof(PoolDestructorArrayBook) == sizeof(Buffer0), PoolDestructorArrayBook_CAN_FIT_INTO_A_Buffer0)

class PoolArray {
public:
  enum { CAPACITY = (sizeof(Buffer0) / PTR_SIZE) };
  Pool* buffer[CAPACITY];
  PoolArray() : buffer() {}
};
staticAssert(sizeof(PoolArray) == sizeof(Buffer0), PoolArray_CAN_FIT_INTO_A_Buffer0)

class PoolArrayBook {
public:
  enum { CAPACITY = ((sizeof(Buffer0) / PTR_SIZE) - 1) /* Calculate Buffer Capacity - Subtract 1 `next` Pointer */ };
  PoolArray* buffer[CAPACITY];
  PoolArrayBook* next;
  PoolArrayBook() : buffer(), next(null) {}
};
staticAssert(sizeof(PoolArrayBook) == sizeof(Buffer0), PoolArrayBook_CAN_FIT_INTO_A_Buffer0)


/*
  ██████╗ ███████╗ ██████╗ ██╗   ██╗███████╗███████╗████████╗
  ██╔══██╗██╔════╝██╔═══██╗██║   ██║██╔════╝██╔════╝╚══██╔══╝
  ██████╔╝█████╗  ██║   ██║██║   ██║█████╗  ███████╗   ██║
  ██╔══██╗██╔══╝  ██║▄▄ ██║██║   ██║██╔══╝  ╚════██║   ██║
  ██║  ██║███████╗╚██████╔╝╚██████╔╝███████╗███████║   ██║
  ╚═╝  ╚═╝╚══════╝ ╚══▀▀═╝  ╚═════╝ ╚══════╝╚══════╝   ╚═╝
*/

enum RequestType {
  REQUEST_INVALID = 0,
  REQUEST_BUFFER_0,
  REQUEST_BUFFER_1,
  REQUEST_BUFFER_2,
  REQUEST_BUFFER_3,
  REQUEST_BLOCK_0,
  REQUEST_BLOCK_1,
  REQUEST_BLOCK_2,
  REQUEST_BLOCK_3,
  REQUEST_POOL_4,
  REQUEST_POOL_8,
  REQUEST_POOL_16,
  REQUEST_POOL_32,
  REQUEST_POOL_64,
  REQUEST_POOL_128,
  REQUEST_POOL_256,
  REQUEST_POOL_512,
  REQUEST_POOL_1024,
  REQUEST_POOL_2048,
  REQUEST_TYPE_COUNT
};
staticAssert(REQUEST_INVALID == 0, SHOULD_BE_ABLE_TO_USE_memset_TO_REST_REQUEST_TYPE_TO_INVALID)

class RequestMemory {
protected:
  u8 request_;

public:
  RequestMemory() : request_(REQUEST_INVALID) {}
  explicit RequestMemory(const RequestType request) : request_(request) {}

  static RequestMemory invalid() { return RequestMemory(REQUEST_INVALID); }
  static RequestMemory buffer0() { return RequestMemory(REQUEST_BUFFER_0); }
  static RequestMemory buffer1() { return RequestMemory(REQUEST_BUFFER_1); }
  static RequestMemory buffer2() { return RequestMemory(REQUEST_BUFFER_2); }
  static RequestMemory buffer3() { return RequestMemory(REQUEST_BUFFER_3); }
  static RequestMemory block0() { return RequestMemory(REQUEST_BLOCK_0); }
  static RequestMemory block1() { return RequestMemory(REQUEST_BLOCK_1); }
  static RequestMemory block2() { return RequestMemory(REQUEST_BLOCK_2); }
  static RequestMemory block3() { return RequestMemory(REQUEST_BLOCK_3); }
  static RequestMemory pool4() { return RequestMemory(REQUEST_POOL_4); }
  static RequestMemory pool8() { return RequestMemory(REQUEST_POOL_8); }
  static RequestMemory pool16() { return RequestMemory(REQUEST_POOL_16); }
  static RequestMemory pool32() { return RequestMemory(REQUEST_POOL_32); }
  static RequestMemory pool64() { return RequestMemory(REQUEST_POOL_64); }
  static RequestMemory pool128() { return RequestMemory(REQUEST_POOL_128); }
  static RequestMemory pool256() { return RequestMemory(REQUEST_POOL_256); }
  static RequestMemory pool512() { return RequestMemory(REQUEST_POOL_512); }
  static RequestMemory pool1024() { return RequestMemory(REQUEST_POOL_1024); }
  static RequestMemory pool2048() { return RequestMemory(REQUEST_POOL_2048); }

  /** Only for scale 0-3 inclusively. Any scale larger than 3 will return REQUEST_INVALID type. */
  static RequestMemory buffer(const Scale scale) {
    switch (scale) {
    case 0: return buffer0();
    case 1: return buffer1();
    case 2: return buffer2();
    case 3: return buffer3();
    default: return invalid();
    }
  }

  /** Only for scale 0-3 inclusively. Any scale larger than 3 will return REQUEST_INVALID type. */
  static RequestMemory block(const Scale scale) {
    switch (scale) {
    case 0: return block0();
    case 1: return block1();
    case 2: return block2();
    case 3: return block3();
    default: return invalid();
    }
  }

  bool isValid() const {
    return ((REQUEST_INVALID < request_) && (request_ < REQUEST_TYPE_COUNT)) ? true : false;
  }

  bool isBuffer() const {
    switch (request_) {
    case REQUEST_BUFFER_0: return true; // NOLINT(*-branch-clone)
    case REQUEST_BUFFER_1: return true; // NOLINT(*-branch-clone)
    case REQUEST_BUFFER_2: return true; // NOLINT(*-branch-clone)
    case REQUEST_BUFFER_3: return true; // NOLINT(*-branch-clone)
    default: return false;
    }
  }

  bool isBlock() const {
    switch (request_) {
    case REQUEST_BLOCK_0: return true; // NOLINT(*-branch-clone)
    case REQUEST_BLOCK_1: return true; // NOLINT(*-branch-clone)
    case REQUEST_BLOCK_2: return true; // NOLINT(*-branch-clone)
    case REQUEST_BLOCK_3: return true; // NOLINT(*-branch-clone)
    default: return false;
    }
  }

  bool isPool() const {
    switch (request_) {
    case REQUEST_POOL_4: return true; // NOLINT(*-branch-clone)
    case REQUEST_POOL_8: return true; // NOLINT(*-branch-clone)
    case REQUEST_POOL_16: return true; // NOLINT(*-branch-clone)
    case REQUEST_POOL_32: return true; // NOLINT(*-branch-clone)
    case REQUEST_POOL_64: return true; // NOLINT(*-branch-clone)
    case REQUEST_POOL_128: return true; // NOLINT(*-branch-clone)
    case REQUEST_POOL_256: return true; // NOLINT(*-branch-clone)
    case REQUEST_POOL_512: return true; // NOLINT(*-branch-clone)
    case REQUEST_POOL_1024: return true; // NOLINT(*-branch-clone)
    case REQUEST_POOL_2048: return true; // NOLINT(*-branch-clone)
    default: return false;
    }
  }

  /** For Buffer and Block requests. */
  Scale getScale() const {
    switch (request_) {
    case REQUEST_BUFFER_0: return 0;
    case REQUEST_BUFFER_1: return 1;
    case REQUEST_BUFFER_2: return 2;
    case REQUEST_BUFFER_3: return 3;
    case REQUEST_BLOCK_0: return 0;
    case REQUEST_BLOCK_1: return 1;
    case REQUEST_BLOCK_2: return 2;
    case REQUEST_BLOCK_3: return 3;
    default: return REQUEST_INVALID;
    }
  }

  /** For Pool requests. */
  IndexMedium getCapacity() const {
    switch (request_) {
    case REQUEST_POOL_4: return Pool4::CAPACITY;
    case REQUEST_POOL_8: return Pool8::CAPACITY;
    case REQUEST_POOL_16: return Pool16::CAPACITY;
    case REQUEST_POOL_32: return Pool32::CAPACITY;
    case REQUEST_POOL_64: return Pool64::CAPACITY;
    case REQUEST_POOL_128: return Pool128::CAPACITY;
    case REQUEST_POOL_256: return Pool256::CAPACITY;
    case REQUEST_POOL_512: return Pool512::CAPACITY;
    case REQUEST_POOL_1024: return Pool1024::CAPACITY;
    case REQUEST_POOL_2048: return Pool2048::CAPACITY;
    default: return REQUEST_INVALID;
    }
  }

};
staticAssert(sizeof(RequestMemory) == sizeof(u8), RequestMemory_CAN_FIT_INTO_AN_u8)

/*
  ███████╗████████╗██████╗ ██╗███╗   ██╗ ██████╗
  ██╔════╝╚══██╔══╝██╔══██╗██║████╗  ██║██╔════╝
  ███████╗   ██║   ██████╔╝██║██╔██╗ ██║██║  ███╗
  ╚════██║   ██║   ██╔══██╗██║██║╚██╗██║██║   ██║
  ███████║   ██║   ██║  ██║██║██║ ╚████║╚██████╔╝
  ╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝ ╚═════╝
*/

typedef IndexItem IndexString;

/** CAUTION: `string` is NOT null terminated. Consider the `length` field.
 *
 *  `string` can be `null`. `length` can be `0`.
 *  Consult the constructor, create, and provider API.
 *
 *  This is a temporary, and internal data structure.
 *  Not intended for storage or long-term use.
 */
class String {
public:
  const char* string;
  IndexString::Base length;
  String() : string(null), length(0) {}
  explicit String(const char* location, const u8 string_length) : string(location), length(string_length) {}
  static String def(const char* location, const u8 string_length) { return String(location, string_length); }
};

/** A bank is a collection of strings.
 *
 *  CAUTION: strings are NOT null terminated.
 *  Index them in `BankIndices` type below.
 *  Each index also determine the end of previous string.
 *
 *  No stored string can go beyond end of the `Bank` buffer.
 */
class Bank : BufferTemplated<char, 0> {
public:
  char* get(const IndexString index) {
    return index.get(this);
  }
  String get(const IndexString index, const IndexString next) {
    return String::def(get(index), (next - index));
  }
};
staticAssert(sizeof(Bank) == sizeof(Buffer0), Bank_IS_A_Buffer0_FOR_A_COLLECTION_OF_STRINGS)

/** Keep indices of strings kept in `Bank` buffers.
 *
 *  Each index is start of a new string and end of the previous one.
 */
class BankIndices {
public:
  IndexString indices[mmBufferSize(0) / sizeof(IndexString)];
  BankIndices() : indices() {}
};
staticAssert(sizeof(BankIndices) == sizeof(Buffer0), BankIndices_CAN_FIT_INTO_A_Buffer0)

/*  - Bank Reference Count
 *  - Node Array
 *  - Node Reference Count
 */

} /* namespace Atm */

using Atm::Buffer0;
using Atm::Buffer1;
using Atm::Buffer2;
using Atm::Buffer3;
using Atm::Block0;
using Atm::Block1;
using Atm::Block2;
using Atm::Block3;
using Atm::Pool4;
using Atm::Pool8;
using Atm::Pool16;
using Atm::Pool32;
using Atm::Pool64;
using Atm::Pool128;
using Atm::Pool256;
using Atm::Pool512;
using Atm::Pool1024;
using Atm::Pool2048;

#endif /* AB_ATM_HPP */
