cd build
make test_rotation test_elasticity
cd ..
./build/tests/test_rotation img/clean_finger.png
./build/tests/test_elasticity img/clean_finger.png
