add_executable(output_test output_test.cpp)
target_link_libraries(output_test PRIVATE output output doctest::doctest_with_main)
add_test(NAME output_test COMMAND output_test)

add_library(sum_test OBJECT sum_test.cpp)
target_link_libraries(sum_test PRIVATE doctest::doctest_with_main)

set(SUM_IMPLS loop loop_long accumulate accumulate_long vec2 vec4 vec8 vec16 vec transform reduce
    kahan kahan_long kahan_vec4 kahan_vec8 kahan_vec16)

if (SUM_FASTMATH)
  set(SUM_IMPLS ${SUM_IMPLS} reduce_fm transform_fm)
endif (SUM_FASTMATH)

if (SUM_PARALLEL)
  set(SUM_IMPLS ${SUM_IMPLS} reduce_par reduce_par_unseq transform_par transform_par_unseq)
endif (SUM_PARALLEL)

if (SUM_UNSEQ)
  set(SUM_IMPLS ${SUM_IMPLS} reduce_seq reduce_unseq transform_seq transform_unseq)
endif (SUM_UNSEQ)

if (SUM_SIMD)
  set(SUM_IMPLS ${SUM_IMPLS} reduce_simd transform_simd)
endif (SUM_SIMD)

foreach(impl ${SUM_IMPLS})
  add_executable(sum_${impl}_test)
  target_link_libraries(sum_${impl}_test PRIVATE sum_test sum_${impl} output)
  add_test(NAME sum_${impl}_test COMMAND sum_${impl}_test)
endforeach ()

if (SUM_WITH_TESTS_FAIL)
  if (SUM_PARALLEL)
    set_tests_properties(sum_reduce_par_test sum_reduce_par_unseq_test sum_transform_par_test sum_transform_par_unseq_test PROPERTIES WILL_FAIL TRUE)
  endif(SUM_PARALLEL)
  if (SUM_UNSEQ)
    set_tests_properties(sum_reduce_seq_test sum_reduce_unseq_test sum_transform_seq_test sum_transform_unseq_test PROPERTIES WILL_FAIL TRUE)
  endif(SUM_UNSEQ)
  if (SUM_FASTMATH)
    set_tests_properties(sum_transform_fm_test PROPERTIES WILL_FAIL TRUE)
    if (CMAKE_CXX_COMPILER_ID STREQUAL GNU OR
        CMAKE_CXX_COMPILER_ID STREQUAL AppleClang OR
        (CMAKE_CXX_COMPILER_ID STREQUAL Clang AND CMAKE_SYSTEM_NAME STREQUAL Darwin))
      set_tests_properties(sum_reduce_fm_test PROPERTIES WILL_FAIL TRUE)
    endif()
  endif(SUM_FASTMATH)
  set_tests_properties(sum_loop_test sum_accumulate_test sum_vec2_test sum_vec4_test sum_vec8_test sum_vec16_test sum_vec_test sum_transform_test sum_reduce_test sum_transform_simd_test PROPERTIES WILL_FAIL TRUE)
  if (CMAKE_CXX_COMPILER_ID STREQUAL AppleClang OR
      (CMAKE_CXX_COMPILER_ID STREQUAL Clang AND CMAKE_SYSTEM_NAME STREQUAL Darwin))
    set_tests_properties(sum_loop_long_test sum_accumulate_long_test PROPERTIES WILL_FAIL TRUE)
  endif()
endif (SUM_WITH_TESTS_FAIL)

if (SUM_WITH_BENCHMARKS)
  foreach(impl ${SUM_IMPLS})
    add_executable(sum_${impl}_bm sum_bm.cpp)
    target_compile_definitions(sum_${impl}_bm PRIVATE -DFN_NAME=sum_${impl})
    target_link_libraries(sum_${impl}_bm PRIVATE sum_${impl} benchmark::benchmark_main)
    add_test(NAME sum_${impl}_bm COMMAND sum_${impl}_bm --benchmark_out_format=json --benchmark_out=sum_${impl}.json)
    set_tests_properties(sum_${impl}_bm PROPERTIES RUN_SERIAL ON)
    set(SUM_BMS ${SUM_BMS} sum_${impl}_bm)
    set(SUM_BM_DATA ${SUM_BM_DATA} sum_${impl}.json)
  endforeach ()
  add_test(NAME plot COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/plot.py --logx --logy ${SUM_BM_DATA})
  set_tests_properties(plot PROPERTIES DEPENDS "${SUM_BMS}")
endif (SUM_WITH_BENCHMARKS)
