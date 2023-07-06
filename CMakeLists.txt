cmake_minimum_required(VERSION 3.12)
project(example)

# Find Python interpreter, libraries, and headers
find_package(Python COMPONENTS Interpreter Development REQUIRED)

# Find pybind11
add_subdirectory(extern/pybind11)
# list(APPEND CMAKE_PREFIX_PATH "extern/pybind11")
# set(pybind11_DIR "extern/pybind11")
# find_package(pybind11 REQUIRED)

# Add your source file
# add_library(example MODULE kruskal_pcst.cpp)
add_executable(example kruskal_pcst.cpp)

# Set properties for the target
set_target_properties(example PROPERTIES PREFIX "${PYTHON_MODULE_PREFIX}"
                                         SUFFIX "${PYTHON_MODULE_EXTENSION}")

# Link against the Python libraries and pybind11
# target_link_libraries(example PRIVATE Python::Python pybind11::module)

# Set the C++ standard
set_target_properties(example PROPERTIES CXX_STANDARD 11)

# Add the Python and pybind11 include directories
target_include_directories(example PRIVATE ${Python_INCLUDE_DIRS} extern/pybind11/include)

# Add the compile options
target_compile_options(example PRIVATE -O3 -Wall)

target_link_libraries(example pybind11::headers)
set_target_properties(example PROPERTIES
                                INTERPROCEDURAL_OPTIMIZATION ON
                                CXX_VISIBILITY_PRESET default
                                VISIBILITY_INLINES_HIDDEN ON)
