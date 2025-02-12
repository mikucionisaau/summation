find_package(eve QUIET) # Expressive Vector Engine (SIMD) library

if (eve_FOUND)
  message(STATUS "Found EVE: ${eve_DIR}")
else(eve_FOUND)
  include(FetchContent)
  message(STATUS "Failed to find EVE, going to compile from source.")
  if (FIND_FATAL)
    message(FATAL_ERROR "Failed to find EVE with CMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}")
  endif(FIND_FATAL)
  set(EVE_USE_PCH OFF CACHE BOOL "Build unit tests with precompield headers")
  set(EVE_BUILD_TEST OFF CACHE BOOL "Build unit tests for eve")
  set(EVE_BUILD_RANDOM OFF CACHE BOOL "Build random precision tests for eve")
  set(EVE_BUILD_BENCHMARKS OFF CACHE BOOL "Build benchmarks for eve")
  set(EVE_BUILD_DOCUMENTATION OFF CACHE BOOL "Compile Doxygen documentation")
  FetchContent_Declare(eve
    GIT_REPOSITORY https://github.com/jfalcou/eve.git
    GIT_TAG v2023.02.15
    GIT_SHALLOW TRUE # get only the last commit version
    GIT_PROGRESS TRUE # show progress of download
    USES_TERMINAL_DOWNLOAD TRUE # show progress in ninja generator
    USES_TERMINAL_CONFIGURE ON
    USES_TERMINAL_BUILD ON
    USES_TERMINAL_INSTALL ON
    EXCLUDE_FROM_ALL
    )
  FetchContent_GetProperties(eve)
  if (eve_POPULATED)
    message(STATUS "Found populated EVE: ${eve_SOURCE_DIR}")
  else (eve_POPULATED)
    FetchContent_MakeAvailable(eve)
    message(STATUS "Got EVE: ${eve_SOURCE_DIR}")
  endif()
endif(eve_FOUND)