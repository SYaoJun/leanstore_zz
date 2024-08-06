# Examples

## 1. Build the leanstore library

```sh
cd $LEANSTORE_HOME
cmake --preset=debug
cmake --build build/debug -j `nproc`

```

The leanstore library should be found in `$LEANSTORE/dist/debug` after the above commands.

## 2. Build the example

```sh
cmake --install build/debug_tsan
cd examples
cmake -B build -S . -DLEANSTORE_INCLUDE_DIR=../dist/debug_tsan/include -DLEANSTORE_LIBRARY_DIR=../dist/debug_tsan/lib
cmake --build build -j `nproc`
./build/BasicKvExample
```