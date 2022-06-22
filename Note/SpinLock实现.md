## Erik Rigtorp
link: https://rigtorp.se/spinlock/

Correctly implementing a spinlock in C++

2020-04-25

I’ve seen a lot of poorly implemented spinlocks floating around the internet. They all make the same mistake: spinning on a read-modify-write (RMW) operation. I will explain why that’s bad and how to correctly implement a spinlock in C++. The explanation and implementation will easily carry over to other programming languages. At the end of the note I provide a complete spinlock implementation adhearing to the Mutex named requirements.

## Discussion thread on Reddit.

The bad spinlock
The most basic spinlock works by using a boolean (or single bit) to indicate whether the lock is held or not. To acquire the lock a atomic exchange operation is used to set the boolean to true. If the previous value returned by the exchange operation was false the lock is now held, otherwise we need to try again until the lock is successfully acquired:

```
struct tas_lock {
  std::atomic<bool> lock_ = {false};

  void lock() { while(lock_.exchange(true)); }

  void unlock() { lock_.store(false); }
};
```

This implementation is usually called a test-and-set (TAS) lock. Other atomic operations can be used to implement a spinlock. In my benchmarking on x86_64 architecture I found little difference in spinlock performance between the different atomic operations that can be used. Additionally according to Agner Fog’s instruction tables and upos.info all LOCK prefixed instructions have very similar instruction latencies1.

## Use correct memory ordering
The default memory ordering of C++ atomics std::memory_order_seq_cst (sequentially-consistent ordering) is overly restrictive and can be changed to std::memory_order_acquire for operations that acquires the lock and std::memory_order_release for operations that releases the lock2. This will allow the compiler to emit more efficent code.

```
struct tas_lock {
  std::atomic<bool> lock_ = {false};

  void lock() { while(lock_.exchange(true, std::memory_order_acquire)); }

  void unlock() { lock_.store(false, std::memory_order_release); }
};
```

## Reducing cache coherency traffic under contention

The problem with the above implementation occurs when there is contention on the lock. In order to keep all CPU caches synchronized a cache coherency protocol is used. There are several different cache coherency protocols (MESI, MOESI, MESIF), but they all have in common that only a single CPU core may write to a cache line but multiple CPU cores may simultaneously read from a cache line. The atomic exchange operation requires write access to the cache line where the lock is stored. If more than one thread is spinning trying to acquire the lock a lot of cache coherency traffic is required to continuously change which core has exclusive write access to the lock.

Since the coherency protocol allows for multiple simultaneous readers we can reduce the coherency traffic by instead spinning on an atomic load operation (spin-wait loop). Instead of continuos futile attempts to acquire the held lock we wait for the lock holder to first release the lock. This eliminates cache coherency traffic during spinning:

```
struct ttas_lock {
  ...
  void lock() {
    for (;;) {
      if (!lock_.exchange(true, std::memory_order_acquire)) {
        break;
      }
      while (lock_.load(std::memory_order_relaxed));
    }
  }
  ...
};
```

This implementation is usually called a test and test-and-set (TTAS) lock. Note that implementation is optimized for the uncontended case. First it tries to acquire the lock, if that fails it spins waiting for the lock to be released.

Reducing load-store unit utilization
Typical CPUs in use today support simultaneous multithreading (SMT) (referred to as hyper-threading (HT) by Intel) allowing multiple logical CPU cores to share the main execution resources such as arithmetic logic unit (ALU), load-store unit (LSU) etc.

Our improved lock above will execute a load operation almost every cycle while spinning. This will starve other logical CPU cores sharing the same load-store unit as the spinning core. To alleviate this problem Intel introduced the PAUSE instruction which provides a hint that a spin-wait loop is running and throttles the CPU core in some architecture specific way in order to reduce power usage and contention on the load-store units. On GCC and clang we can emit the PAUSE instruction using the built-in function __builtin_ia32_pause() and on MSVC using _mm_pause(). Adding this to our spin-wait loop we get:

```
struct ttas_lock {
  ...
  void lock() {
    for (;;) {
      if (!lock_.exchange(true, std::memory_order_acquire)) {
        break;
      }
      while (lock_.load(std::memory_order_relaxed)) {
        __builtin_ia32_pause();
      }
    }
  }
  ...
};
```

Other CPU architectures may have similar primitives. For example ARM has the YIELD instruction.

Note that if you don’t use hyper-threading and you don’t care about power efficiency using the PAUSE instruction will slow down lock acquisition on contended locks.

## Benchmark
I created a simple benchmark where N threads are launched, each thread acquires and releases the lock 100M / N times and finally the average time for a lock()-unlock() pair is calculated.

Running on my computer with 4 cores / 8 hyper-threads we can see that the good spinlock implementation scales better than the bad spinlock:

N threads	Good spinlock ns/op	Bad spinlock ns/op
1	7	7
2	28	43
3	70	168
4	112	205
5	190	381
6	241	509
7	274	884
8	442	854
We can also use the perf command to see the amount of cache misses and atomic operations for each implementation.

For the good spinlock:

sudo perf stat -e L1-dcache-loads,L1-dcache-load-misses,mem_inst_retired.lock_loads ./a.out 100000000 8

 Performance counter stats for './a.out 100000000 8':

     1,038,332,933      L1-dcache-loads
       282,408,737      L1-dcache-load-misses     #   27.20% of all L1-dcache hits  
       161,632,506      mem_inst_retired.lock_loads

       5.148648364 seconds time elapsed

      39.249547000 seconds user
       0.015969000 seconds sys
For the bad spinlock:

sudo perf stat -e L1-dcache-loads,L1-dcache-load-misses,mem_inst_retired.lock_loads ./a.out 100000000 8

 Performance counter stats for './a.out 100000000 8':

     1,067,168,715      L1-dcache-loads
       509,077,190      L1-dcache-load-misses     #   47.70% of all L1-dcache hits  
       552,378,083      mem_inst_retired.lock_loads

      11.225589133 seconds time elapsed

      82.805909000 seconds user
       0.051584000 seconds sys
We can see that the good spinlock has significantly fewer cache misses and atomic operations.

## References
Lock Scaling Analysis on Intel® Xeon® Processors
PAUSE instruction
YILED instruction
Example of poor spinlock implementations:

Using locks in real-time audio processing, safely - timur.audio
std::atomic_flag - cppreference.com (Archived version)
Fabian Renn-Giles & Dave Rowland - Real-time 101 - part I: Investigating the real-time problem space (YouTube)
Bryce Adelstein Lelbach — The C++20 synchronization library (YouTube)
Appendix: Complete spinlock implementation
Below is the complete implementation of the basic spinlock using C++11 atomics. It should be easy to adapt to C11 atomics and other languages.

Update 2020-04-26: As suggested by user adops_dsp on Reddit the try_lock() should first check if the lock is free before attempting to acquire it. This would prevent excessive coherency traffic in case someone loops over try_lock().

```
struct spinlock {
  std::atomic<bool> lock_ = {0};

  void lock() noexcept {
    for (;;) {
      // Optimistically assume the lock is free on the first try
      if (!lock_.exchange(true, std::memory_order_acquire)) {
        return;
      }
      // Wait for lock to be released without generating cache misses
      while (lock_.load(std::memory_order_relaxed)) {
        // Issue X86 PAUSE or ARM YIELD instruction to reduce contention between
        // hyper-threads
        __builtin_ia32_pause();
      }
    }
  }

  bool try_lock() noexcept {
    // First do a relaxed load to check if lock is free in order to prevent
    // unnecessary cache misses if someone does while(!try_lock())
    return !lock_.load(std::memory_order_relaxed) &&
           !lock_.exchange(true, std::memory_order_acquire);
  }

  void unlock() noexcept {
    lock_.store(false, std::memory_order_release);
  }
};
```

Instruction latencies from Agner Fogg’s tables for some instructions that can be used to create spinlocks:
```
Instruction	µops	Latency
XCHG	8	23
LOCK XADD	9	18
LOCK CMPXCHG	10	18
LOCK CMPXCHG8B	20	19
```
Latency: “This is the delay that the instruction generates in a dependency chain. The numbers are minimum values. Cache misses, misalignment, and exceptions may increase the clock counts considerably. Where hyperthreading is enabled, the use of the same execution units in the other thread leads to inferior perfor-mance. Denormal numbers, NAN’s and infinity do not increase the latency. The time unit used is core clock cycles, not the reference clock cycles given by the time stamp counter.” ↩︎

C++ committee member Tony Van Eerdcommented on reddit that with std::memory_order_acquire and two locks a and b; calls to a.unlock(); b.lock() and lock() for different locks could be reordered to b.lock(); a.unlock(); and introduce a potential deadlock. I don’t think that’s true. Reading section 6.9.2.1 Data races (paragraph 9) of the C++ standard] no loads or stores can bed moved into or out from between a load-acquire and store-release pair. ↩︎

## Other posts
Optimizing a ring buffer for throughput
Using huge pages on Linux
Fuzzing floating point code
Generating std::ostream &operator<< for C++ enums and structs using libClang
Tips for using the sockets API
Uses of immediately invoked function expressions (IIFE) in C++
Latency implications of virtual memory
Aligned AVX loads and stores are atomic
Correctly implementing a spinlock in C++
Low latency tuning guide
Performance impact of split locks
C++ Best Practices
Estimating order queue position
Designing a high performance market data feed handler
Efficient rolling statistics with NumPy
Erlang Latency Guide

© 2021 Erik Rigtorp <erik@rigtorp.se> GitHub LinkedIn