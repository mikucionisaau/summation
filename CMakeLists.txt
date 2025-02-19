cmake_minimum_required(VERSION 3.25)
project(summation LANGUAGES C CXX)

message(STATUS "Configuring for ${CMAKE_SYSTEM_NAME} using ${CMAKE_CXX_COMPILER_ID}")

if (NOT "cxx_std_23" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
  message(FATAL_ERROR "Compiler does not support C++23")
endif()

include(CheckSourceCompiles)
check_source_compiles(CXX
  "#include <version>
  #if !defined(__cpp_lib_execution) || __cpp_lib_execution < 201603L
  #error \"execution policies are not supported\"
  #endif
  int main() { return 0; }"
  SUM_PARALLEL)

check_source_compiles(CXX
  "#include <version>
  #if !defined(__cpp_lib_execution) || __cpp_lib_execution < 201902L
  #error \"unsequenced policy is not supported\"
  #endif
  int main() { return 0; }"
  SUM_UNSEQ)

if (CMAKE_SYSTEM_NAME STREQUAL Darwin AND CMAKE_CXX_COMPILER_ID STREQUAL GNU)
  message(STATUS "Disabling FASTMATH implementations (GCC/Darwin can't handle)")
  set(SUM_FASTMATH OFF) # clang: error: unsupported argument 'apple-m3' to option '-mtune='
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL MSVC)
  message(STATUS "Disabling SIMD implementations (MSVC can't handle EVE library)")
  set(SUM_SIMD OFF)
endif()

option(SUM_WITH_TESTS "Unit Tests" ON)
option(SUM_WITH_TESTS_FAIL "Expect specific tests to fail" OFF)
option(SUM_WITH_BENCHMARKS "Benchmarks" ON)
option(SUM_FASTMATH "Tune to native CPU with fast-math optimizations" ON)
option(SUM_PARALLEL "Parallel implementations" ON)
option(SUM_SIMD "SIMD implementations using Expressive Vector Engine (EVE)" ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # generates compile_commands.json

if (SUM_PARALLEL)
  if (CMAKE_CXX_COMPILER_ID STREQUAL GNU OR CMAKE_CXX_COMPILER_ID STREQUAL Clang)
    include(cmake/tbb.cmake)
    set(SUM_USING_TBB TRUE)
  endif()
endif (SUM_PARALLEL)

if (SUM_SIMD)
  include(cmake/eve.cmake)
endif (SUM_SIMD)

include_directories(include)
add_subdirectory(source)

if (SUM_WITH_TESTS)
  include(cmake/doctest.cmake)
  if (SUM_WITH_BENCHMARKS)
    include(cmake/benchmark.cmake)
  endif (SUM_WITH_BENCHMARKS)
  enable_testing()
  message(STATUS "Enabled Unit Tests and Benchmarks")
  add_subdirectory(tests)
else (SUM_WITH_TESTS)
  message(STATUS "Disabled Unit Tests and Benchmarks")
endif (SUM_WITH_TESTS)

install(TARGETS sum main EXPORT sum)
install(DIRECTORY include/sum DESTINATION include)
# write_basic_package_version_file()
