cd build
make Test_geom
make Test_geom_advanced
cd ..
./build/tests/Test_geom $1
./build/tests/Test_geom_advanced $1
