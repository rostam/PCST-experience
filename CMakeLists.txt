cmake_minimum_required(VERSION 3.15)
project(PCST-EXPERIENCE)

set(CMAKE_CXX_STANDARD 14)

find_package(pybind11 REQUIRED) 
# add_subdirectory(extern/pybind11)



add_executable (kruskal_pcst kruskal_pcst.cpp)
target_link_libraries(kruskal_pcst PRIVATE pybind11::module)
set_target_properties(kruskal_pcst PROPERTIES PREFIX "${PYTHON_MODULE_PREFIX}"
                                         SUFFIX "${PYTHON_MODULE_EXTENSION}")