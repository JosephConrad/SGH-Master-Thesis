rm -rf build
mkdir build
cd build
cmake ..
cmake --build .
ctest -VV
cd ..