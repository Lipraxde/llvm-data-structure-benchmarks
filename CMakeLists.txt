cmake_minimum_required(VERSION 3.9)
project(llvm_data_structure_benchmarks)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost 1.65 REQUIRED)
if(${Boost_FOUND})
    include_directories (${Boost_INCLUDE_DIRS})
    # According: https://bugzilla.redhat.com/show_bug.cgi?id=1485641
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-new-ttp-matching")
    endif()
endif()

find_package (LLVM 8 CONFIG REQUIRED)
if (${LLVM_FOUND})
    message (STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
    message (STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
    include_directories (${LLVM_INCLUDE_DIRS})
    add_definitions (${LLVM_DEFINITIONS})
endif ()

llvm_map_components_to_libnames(llvm_libs support)

add_executable(llvm_data_structure_benchmarks
		data_structure_benchmarks.cpp)
target_link_libraries(llvm_data_structure_benchmarks ${llvm_libs})
target_include_directories(llvm_data_structure_benchmarks SYSTEM PRIVATE
		"/usr/local/Cellar/google-benchmark/1.3.0/include/") # Get this on Mac from $ brew install google-benchmark
find_library(GOOGLE_BENCHMARK benchmark)
target_link_libraries(llvm_data_structure_benchmarks
		${GOOGLE_BENCHMARK})

target_compile_options(llvm_data_structure_benchmarks PRIVATE
		-march=haswell) # May want to try with -march=native as well
