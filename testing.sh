set -eux

# mkdir build
cd build
cmake .. -Dtest=ON
make test.out
cd ..
./build/test.out
