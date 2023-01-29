set(UNIT_TESTS unit_tests)

list(APPEND DEPENDENCIES ${OpenCV_LIBS})

# ------------------------------------------------------------------------------
# Dependencies
set(GTEST "${CMAKE_CURRENT_SOURCE_DIR}/googletest")
if (NOT EXISTS ${GTEST})
    message(
        FATAL_ERROR
	"Googletest missing. Maybe forgot to fetch git submodules with:
	git submodule init
	git submodule update
	?"
    )
endif()

add_subdirectory(${GTEST})

set(SOURCES
    test-main.cpp
    test_stl_forward.cpp
)

add_executable(${UNIT_TESTS} ${SOURCES})

target_link_libraries(${UNIT_TESTS} gtest gtest_main ${PROJECT_NAME}  ${OpenCV_LIBS})
target_include_directories(${UNIT_TESTS} PRIVATE  PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

set_target_properties(${UNIT_TESTS} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

