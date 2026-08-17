#include "Alm.hpp"

#include "All.hpp"

#if IS_OS_LINUX
  #include <sys/sysinfo.h>
  #include <sys/mman.h>
#endif

namespace Alm {

#if IS_OS_LINUX
static void* allocateRawMemory(const usize size) {
  const int prot = PROT_READ | PROT_WRITE;
  const int flags = MAP_ANONYMOUS | MAP_PRIVATE;
  void* result = null;
  result = mmap(null, size, prot, flags, -1, 0);
  if (result == MAP_FAILED) {
    All::reportSystemError("allocateRawMemory Failed");
    debugBreak
    return null;
  } else {
    return result;
  }
}

static void deallocateRawMemory(void* location, const usize size) {
  if (location == null) { return; }
  if (munmap(location, size) != 0) {
    All::reportSystemError("deallocateRawMemory Failed");
    debugBreak
  }
}

#elif IS_OS_WINDOWS
static void* allocateRawMemory(const usize size) {
  void* result = VirtualAlloc(
    NULL,                           // lpAddress: NULL lets system choose address
    size,                           // dwSize: size in bytes
    MEM_RESERVE | MEM_COMMIT,       // flAllocationType: reserve and commit
    PAGE_READWRITE                  // flProtect: equivalent to PROT_READ | PROT_WRITE
  );
  if (result == null) {
    All::reportSystemError("allocateRawMemory Failed");
    debugBreak;
    return NULL;
  } else {
    return result;
  }
}

static void deallocateRawMemory(void* location, const usize size) {
  if (location == null) { return; }
  if (VirtualFree(location, 0, MEM_RELEASE) == 0) {
    All::reportSystemError("deallocateRawMemory Failed");
    debugBreak;
  }
}

#endif

void* allocatePool(const IndexMedium capacity) {
  void* result = allocateRawMemory(mmPoolSize(capacity));
  return result;
}

void* deallocatePool(void* location, const IndexMedium capacity) {
  const usize size = mmBlockSize(0) * capacity;
  deallocateRawMemory(location, size);
  return null;
}

#if AB_CONCUR
IndexMedium pushBlock(Atomic* used, const IndexMedium capacity, const Scale scale) {
  /* `pool->used_units` should never fall below 1. */
  /* Because, 0 is failure indicator. */
  /* And index 0 is always implicitly allocated. */
  assert(atomicGet(used) > 0);
  /* Exponent should not be greater than (MM_BLOCK_CAPACITY_MAX_EXPONENT - 1) to prevent overflow. */
  assert(mmBlockExponentCheck(scale) == false);
  const int request = mmBlockUnitCount(scale);
  while (true) {
    const int current = atomicGet(used);
    const int final = current + request;
    if (final > capacity) {
      return 0;
    } else {
      const bool didWork = atomicCAS(used, current, final);
      if (didWork) { return static_cast<IndexMedium>(current); }
    }
  }
}
#else
IndexMedium pushBlock(int* used, const IndexMedium capacity, const Scale scale) {
  /* `pool->used_units` should never fall below 1. */
  /* Because, 0 is failure indicator. */
  /* And index 0 is always implicitly allocated. */
  assert(*used > 0);
  /* Exponent should not be greater than (MM_BLOCK_CAPACITY_MAX_EXPONENT - 1) to prevent overflow. */
  assert(mmBlockExponentCheck(scale) == false);
  const int request = mmBlockUnitCount(scale);
  const int current = *used;
  const int final = current + request;
  if (final > capacity) {
    return 0;
  } else {
    *used = final;
    return static_cast<IndexMedium>(current);
  }
}
#endif

#if AB_CONCUR
IndexMedium popBlock(Atomic* used, const Scale scale) {
  /* `pool->used` should never fall below 1. */
  /* Because, 0 is failure indicator. */
  /* And index 0 is always implicitly allocated. */
  assert(atomicGet(used) > 0);
  /* Exponent should not be greater than (MM_BLOCK_CAPACITY_MAX_EXPONENT - 1) to prevent overflow. */
  assert(mmBlockExponentCheck(scale) == false);
  const int request = mmBlockUnitCount(scale);
  while (true) {
    const int current = atomicGet(used);
    int final = current - request;
    assert(final > 0);
    final = final > 0 ? final : 1;
    const bool didWork = atomicCAS(used, current, final);
    if (didWork) { return final; }
  }
}
#else
IndexMedium popBlock(int* used, const Scale scale) {
  /* `pool->used` should never fall below 1. */
  /* Because, 0 is failure indicator. */
  /* And index 0 is always implicitly allocated. */
  assert(*used > 0);
  /* Exponent should not be greater than (MM_BLOCK_CAPACITY_MAX_EXPONENT - 1) to prevent overflow. */
  assert(mmBlockExponentCheck(scale) == false);
  const int request = mmBlockUnitCount(scale);
  const int current = *used;
  int final = current - request;
  assert(final > 0);
  final = final > 0 ? final : 1;
  *used = final;
  return final;
}
#endif

}
