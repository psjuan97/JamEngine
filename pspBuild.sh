#! /bin/bash
echo $PSPDEV

cd build
cmake ..  -DCMAKE_TOOLCHAIN_FILE=$PSPDEV/toolchain-psp.cmake -DCMAKE_C_COMPILER_FORCED=TRUE     -DCMAKE_CXX_COMPILER_FORCED=TRUE

make -j4
