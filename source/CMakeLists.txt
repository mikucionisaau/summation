add_library(output OBJECT output.cpp)

set(SUM_IMPLS loop loop_long accumulate accumulate_long vec2 vec4 vec8 vec16 vec transform reduce
        kahan kahan_long kahan_vec4 kahan_vec8 kahan_vec16)

foreach(impl ${SUM_IMPLS})
  add_library(sum_${impl} OBJECT sum_${impl}.cpp)
endforeach ()

if (SUM_FASTMATH)
  add_library(sum_reduce_fm OBJECT sum_reduce.cpp)
  target_compile_options(sum_reduce_fm PRIVATE -ffast-math)

  add_library(sum_transform_fm OBJECT sum_transform.cpp)
  target_compile_options(sum_transform_fm PRIVATE -mtune=native -ffast-math)
endif (SUM_FASTMATH)

if (SUM_PARALLEL)
  foreach(impl reduce_par reduce_par_unseq transform_par transform_par_unseq)
    add_library(sum_${impl} OBJECT sum_${impl}.cpp)
    if (SUM_USING_TBB)
      target_link_libraries(sum_${impl} PRIVATE TBB::tbb)
    endif()
  endforeach ()
endif (SUM_PARALLEL)

if (SUM_UNSEQ)
  foreach(impl reduce_seq reduce_unseq transform_seq transform_unseq)
    add_library(sum_${impl} OBJECT sum_${impl}.cpp)
    if (SUM_USING_TBB)
      target_link_libraries(sum_${impl} PRIVATE TBB::tbb)
    endif()
  endforeach ()
endif (SUM_UNSEQ)

if (SUM_SIMD)
  set(SUM_SIMD reduce_simd transform_simd)
  foreach(impl ${SUM_SIMD})
    add_library(sum_${impl} OBJECT sum_${impl}.cpp)
    target_link_libraries(sum_${impl} PRIVATE eve::eve)
  endforeach ()
endif (SUM_SIMD)

add_library(sum output sum_loop)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE output sum_loop)
