set(BENCHMARKS benchmarks)

list(APPEND DEPENDENCIES ${OpenCV_LIBS})
# ------------------------------------------------------------------------------
# Dependencies
set(GBENCH "${CMAKE_CURRENT_SOURCE_DIR}/benchmark")
if (NOT EXISTS ${GBENCH})
    message(
        FATAL_ERROR
	"Googlebenchmark missing. Maybe forgot to fetch git submodules with:
	git submodule init
	git submodule update
	?"
    )
endif()

add_subdirectory(${GBENCH})

set(SOURCES
    bench-main.cpp
)

add_executable(${BENCHMARKS} ${SOURCES})

target_link_libraries(${BENCHMARKS} benchmark::benchmark gtest gtest_main  ${PROJECT_NAME}  ${OpenCV_LIBS})
target_include_directories(${BENCHMARKS} PRIVATE  PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

set_target_properties(${BENCHMARKS} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

