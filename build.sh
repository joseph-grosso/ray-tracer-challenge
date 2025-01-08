set -eux

cd build
cmake ..
make challenge.out
cd ..
./build/challenges/challenge.out
