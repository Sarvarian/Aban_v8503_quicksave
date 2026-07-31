#include "Memory.hpp"

#include <sys/sysinfo.h>
#include <sys/mman.h>
#include <cerrno>
#include <csignal>

namespace Memory {
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
    debugBreak;
    return 0;
  }
}

void* allocatePool(const Index capacity) {
  const usize size = mmBlockSize(0) * capacity;
  void* result = allocateRawMemory(size);
  return result;
}

void* deallocatePool(void* location, const Index capacity) {
  const usize size = mmBlockSize(0) * capacity;
  deallocateRawMemory(location, size);
  return null;
}

Index pushBlock(Atomic* used, const Index capacity, const Scale scale) {
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
      if (didWork) { return static_cast<Index>(current); }
    }
  }
}

Index popBlock(Atomic* used, const Scale scale) {
  /* `pool-used` should never fall below 1. */
  /* Because, 0 is failure indicator. */
  /* And index 0 is always implicitly allocated. */
  assert(atomicGet(used) > 0);
  /* Exponent should not be greater than (MM_BLOCK_CAPACITY_MAX_EXPONENT - 1) to prevent overflow. */
  assert(mmBlockExponentCheck(scale) == false);
  const int request = mmBlockUnitCount(scale);
  while (true) {
    const int current = atomicGet(used);
    if (request > current) {
      debugBreak;
      atomicSet(used, 0);
      return 0;
    } else {
      const int final = current - request;
      const bool didWork = atomicCAS(used, current, final);
      if (didWork) { return final; }
    }
  }
}
}

