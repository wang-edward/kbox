#!/bin/bash
(
  # utilizing cmake's parallel build options
  # recommended: -j <number of processor cores + 1>
  # This is supported in cmake >= 3.12 use -- -j5 for older versions
  # use -v for verbose editing
  cmake --build build/release -j 5
)

result=$?
if [ ${result} == 0 ]; then
  ./bin/app
fi
