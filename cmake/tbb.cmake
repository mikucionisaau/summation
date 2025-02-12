find_package(TBB QUIET) # Thread Building Blocks (parallel execution) library

if (TBB_FOUND)
  message(STATUS "Found TBB: ${TBB_DIR}")
else(TBB_FOUND)
  include(FetchContent)
  message(STATUS "Failed to find TBB, going to compile from source.")
  if (FIND_FATAL)
    message(FATAL_ERROR "Failed to find TBB with CMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}")
  endif(FIND_FATAL)
  set(TBB_TEST OFF CACHE BOOL "Enable testing")
  set(TBB_EXAMPLES OFF CACHE BOOL "Enable examples")
  set(TBB_STRICT OFF CACHE BOOL "Treat compiler warnings as errors")
  set(TBB_WINDOWS_DRIVER OFF CACHE BOOL "Build as Universal Windows Driver (UWD)")
  set(TBB_NO_APPCONTAINER OFF CACHE BOOL "Apply /APPCONTAINER:NO (for testing binaries for Windows Store)")
  set(TBB4PY_BUILD OFF CACHE BOOL "Enable tbb4py build")
  set(TBB_BUILD ON CACHE BOOL "Enable tbb build")
  set(TBBMALLOC_BUILD ON CACHE BOOL "Enable tbbmalloc build")
  set(TBBMALLOC_PROXY_BUILD OFF CACHE BOOL "Enable tbbmalloc_proxy build")
  set(TBB_CPF OFF CACHE BOOL "Enable preview features of the library")
  set(TBB_FIND_PACKAGE OFF CACHE BOOL "Enable search for external oneTBB using find_package instead of build from sources")
  set(TBB_DISABLE_HWLOC_AUTOMATIC_SEARCH ${CMAKE_CROSSCOMPILING} CACHE BOOL "Disable HWLOC automatic search by pkg-config tool")
  set(TBB_ENABLE_IPO ON CACHE BOOL "Enable Interprocedural Optimization (IPO) during the compilation")
  set(TBB_FUZZ_TESTING OFF CACHE BOOL "Enable fuzz testing")
  set(TBB_INSTALL OFF CACHE BOOL "Enable installation")
  FetchContent_Declare(tbb
    GIT_REPOSITORY https://github.com/uxlfoundation/oneTBB
    GIT_TAG v2022.0.0
    GIT_SHALLOW TRUE # get only the last commit version
    GIT_PROGRESS TRUE # show progress of download
    # FIND_PACKAGE_ARGS NAMES benchmark
    USES_TERMINAL_DOWNLOAD TRUE # show progress in ninja generator
    USES_TERMINAL_CONFIGURE ON
    USES_TERMINAL_BUILD ON
    USES_TERMINAL_INSTALL ON
    EXCLUDE_FROM_ALL)
  FetchContent_GetProperties(tbb)
  if (tbb_POPULATED)
    message(STATUS "Found populated TBB: ${tbb_SOURCE_DIR}")
  else (tbb_POPULATED)
    FetchContent_MakeAvailable(tbb)
    #add_subdirectory(${tbb_SOURCE_DIR} ${tbb_BINARY_DIR} EXCLUDE_FROM_ALL)
    message(STATUS "Got TBB: ${tbb_SOURCE_DIR}")
  endif()
endif(TBB_FOUND)
