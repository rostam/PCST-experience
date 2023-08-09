# PCST-experience
Here, I just want to do some experiments for PCST problem.
- Write a simple non-optimal kruskal solution for PCST problem
- Write a python binding


## Build

### Pre
First run this:
```
git submodule add -b stable ../../pybind/pybind11 extern/pybind11
git submodule update --init
```


### Compiling 
```
g++ -O3 -Wall -shared -std=c++11 -fPIC $(python3-config --includes) -Iextern/pybind11/include kruskal_pcst.cpp -o PCST$(python3-config --extension-suffix)

python test_kruskal.py
python test_coloring.py
```

### CMake
```
cd build
cmake ..
make
make test
```

### Test

#### Testing if the function is in the object
nm example.cpython-310-x86_64-linux-gnu.so | grep kruskal
nm example.cpython-310-x86_64-linux-gnu.so | grep greedy

#### Larger Test Data
A set of test data ofr different graph algorithms like PCST:
[DIMACS11](https://dimacs11.zib.de/downloads.html)
