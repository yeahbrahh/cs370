# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project state

This is a CS370 assignment skeleton for implementing a **red-black tree backed by a custom memory pool allocator** in C. The `Makefile` defines the full intended build (sources, tests, fuzzer, sanitizer/valgrind targets), but the source tree it references does not exist yet:

- `include/rbtree.h`
- `src/rbtree.c`, `src/pool.c`
- `tests/test_rbtree.c`, `tests/fault_alloc.c`, `tests/fuzz.c`

`main.c` at the repo root (a no-op `main` returning 0) is a leftover stub and is **not** part of the Makefile build — it's not referenced by any target.

When implementing, create files at the paths above; the Makefile expects that exact layout.

## Commands

```sh
make            # builds build/test_rbtree and build/fuzz
make test       # builds, then runs the unit tests followed by the fuzzer (100000 iterations)
make asan       # rebuilds from clean with -fsanitize=address,undefined, then runs `test`
make memcheck   # builds, then runs both binaries under valgrind --leak-check=full (fails on any leak)
make clean      # removes build/
```

There is no target for a single test case — `tests/test_rbtree.c` is expected to be a single self-contained binary that runs its own cases; run `./build/test_rbtree` directly once built. The fuzzer (`build/fuzz`) takes an iteration count as its only argument (e.g. `./build/fuzz 100000`).

`fault_alloc.c` is linked into both the test binary and the fuzzer — it's expected to provide an allocator shim for injecting allocation failures, which `pool.c` should call through rather than `malloc` directly, so tests can exercise OOM paths.

## Build environment note

The Makefile compiles with `-std=c23`. The installed `gcc` (11.5.0) does **not** recognize this flag (only `-std=c2x`) and will fail with "unrecognized command-line option". If a build fails immediately on that error, this is an environment/toolchain mismatch, not a code bug — check `gcc --version` before debugging further.

`-Werror` is set, so any warning fails the build.
