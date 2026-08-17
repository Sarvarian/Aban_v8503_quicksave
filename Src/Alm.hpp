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
#define mmBlockExponentCheck(VALUE) ((VALUE) > (MM_BLOCK_CAPACITY_MAX_EXPONENT - 1) || (VALUE) < 0)
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

/** @return Check return for failure. */
void* allocatePool(IndexMedium capacity);

/** @return Always returns null. */
void* deallocatePool(void* location, IndexMedium capacity);

#if AB_CONCUR
/** [Multithread Safe]
 *  @param used Atomic int, head of pool usage.
 *  @param capacity Capacity in block units.
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

} /* namespace Alm */

#endif /* AB_ALM_HPP */
