#include "Alm.hpp"

#include "Main.hpp"

#if IS_OS_LINUX
  #include <sys/sysinfo.h>
  #include <sys/mman.h>
#endif

namespace Alm {
static void* allocateRawMemory(const usize size) {
  const int prot = PROT_READ | PROT_WRITE;
  const int flags = MAP_ANONYMOUS | MAP_PRIVATE;
  void* result = null;
  result = mmap(null, size, prot, flags, -1, 0);
  if (result == MAP_FAILED) {
    perror("allocateRawMemory Failed");
    debugBreak
    return null;
  } else {
    return result;
  }
}

// ReSharper disable once CppDFAConstantFunctionResult
static void* deallocateRawMemory(void* location, const usize size) {
  if (location == null) { return null; }
  if (munmap(location, size) != 0) {
    perror("deallocateRawMemory Failed");
    debugBreak
  }
  return null;
}

usize totalRawMemory() {
  struct sysinfo info = {};
  if (sysinfo(&info) == 0) {
    return info.totalram;
  } else {
    print("Failed to get sysinfo");
    debugBreak
    return 0;
  }
}

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
