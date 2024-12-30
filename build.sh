set -eux

cd build
cmake ..
make
cd ..
./build/challenges/challenge.out
