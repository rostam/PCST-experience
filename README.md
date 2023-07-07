# PCST-experience
Here, I just want to do some experiments for PCST problem.
- Write a simple non-optimal kruskal solution for PCST problem
- Write a python binding


First run this:
```
git submodule add -b stable ../../pybind/pybind11 extern/pybind11
git submodule update --init


g++ -O3 -Wall -shared -std=c++11 -fPIC $(python3-config --includes) -Iextern/pybind11/include kruskal_pcst.cpp -o example$(python3-config --extension-suffix)

python test.py

```

A set of test data ofr different graph algorithms like PCST:
[DIMACS11](https://dimacs11.zib.de/downloads.html)
