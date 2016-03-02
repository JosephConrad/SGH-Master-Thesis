set -e

mkdir -p build
cp config.ini build/
cd build
#cmake .. -DCMAKE_BUILD_TYPE=Debug -LAH
cmake ..
cmake --build .
ctest -VV
cd ..
