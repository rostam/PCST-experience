# PCST-experience
look at PCST problem 

First run this:
```
git submodule add -b stable ../../pybind/pybind11 extern/pybind11
git submodule update --init


g++ -O3 -Wall -shared -std=c++11 -fPIC $(python3-config --includes) -Iextern/pybind11/include example.cpp -o example$(python3-config --extension-suffix)

```

```
import example
example.add(1,2)

```