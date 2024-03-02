set -eux

# mkdir build
cd build
cmake .. -Dtest=ON
make
cd ..
./build/hello_test.out
