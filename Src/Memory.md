
# Memory

This is our low-level memory module.

More specialized memory containers will use
these set of classes, primitives, and data
to be constructed.

There are three level of memory management
and their respected types:

- Buffers
- Blocks
- Pools

## Buffer

A buffer, is a fixed sized array or just a raw
memory, that can be used as an array of data,
or just a memory for a data structure.

Buffers are allocated from blocks.

Buffers came in 4 scales:

- Buffer0 is sized at 512 bytes.
- Buffer1 is double the previous scale, sized at 1024 bytes.
- Buffer2 is doubled yet again, sized at 2048 bytes.
- Buffer3 is the largest one, sized at 4096 bytes.

The unscaled buffer (Buffer0) by default is set to
512 bytes to fit around an 8 cache line (assuming 64 byte cache lines).

To be honest, this is a very conservative decision.
As I want it to ensure to fill a whole cache line, even on
systems with 128 byte cache lines, but I've gone overboard, and
because I see no downside, then just let it be.

Also, there is no buffer size difference between
32-bit and 64-bit runtime. Both are set to have
buffers of 512 bytes by default.

## Scale

We store size of buffers and blocks by `Scale`.
Scales are 2's exponents. Each memory level
have a base size (unscaled), for example buffers are
512 bytes by default. And each scale, multiply the
previous scale size by 2. So, we can store size of
each scale by only a 2's exponent. For example buffers
are as follows:

- Buffer0: Scale 0. Unscaled. 512 bytes. Exponent 9.
- Buffer1: Scale 1. 1024 bytes. Exponent 10.
- Buffer2: Scale 2. 2048 bytes. Exponent 11.
- Buffer3: Scale 3. 4096 bytes. Exponent 12.

## Block

Blocks containers of 128 buffers (by default)
of the same scale. The buffers are consecutive
in memory (array). Blocks are fixed array of buffers!

Blocks allow memory and algorithms to allocate buffers.

Blocks themselves are allocated from pools.

Blocks also came in 4 scales:

- Block0: 512 bytes * 128 = 64KB.
- Block1: 1024 bytes * 128 = 128KB
- Block2: 2048 bytes * 128 = 256KB
- Block3: 4096 bytes * 128 = 512KB

## Pools 

Pools are large memory spaces, 4MB up to 2GB.

Pools themselves are allocated from system memory
through operating system calls like mmap.

Pools provide a simple bump allocator for blocks to
be allocated as fast as possible.

Pools do not have scales but rather are identify by
their `capacity`, but their capacity is identified by
the amount of Block0 they can hold.

For example, a 2GB pool has the capacity of 32768, which
is 32768 Block0.

So, to allocate a Block3, it will cost 8 capacity from
our pool. 16 is `unit` count of Block3. It is how much
of a Block0 can be fit into a Block3.

## Unit

A unit buffer is Buffer0.

A unit block is Block0.

A Buffer4 can hold 8 buffer unit.

A Block4 can hold 8 buffer unit.

- 1 unit is just a unit.
- 2 units is scale 1 which contains double the unit.
- 4 units is scale 2 which contains double the scale 1.
- 8 units is scale 3 which contains double the scale 2.

Each scale unit count is 2 to the power of the
scale number.

A unit is always the unscaled object of that level (Buffer0 or Block0).
Scale S occupies 1 << S units.

## TTT and Binlog

TTTs are macros defined in `Main.hpp` and
the triple T stand for "2 To The" x.

They are constants or the function that calculate
the power result of a two's exponent.

Just as Binlog that is doing the reverse.

Binlog calculate a two's exponent from a given power.
