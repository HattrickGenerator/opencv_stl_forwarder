cmake_minimum_required(VERSION 3.12)


option(OPENCV_STL_FORWARDER_BUILD_TESTS ON)
option(OPENCV_STL_FORWARDER_BUILD_BENCHMARKS ON)

project(opencv_stl_forwarder
        VERSION 0.1
        DESCRIPTION "Foward opencv matrices to stl algorithms to make them run more efficiently."
        HOMEPAGE_URL "https://github.com/HattrickGenerator/opencv_stl_forwarder"
        LANGUAGES CXX
)

find_package(OpenCV REQUIRED)


file(GLOB DETAIL_HDR_FILES ${PROJECT_SOURCE_DIR}/include/opencv_stl_forwarder/detail/*.hpp)
file(GLOB STL_HDR_FILES ${PROJECT_SOURCE_DIR}/include/opencv_stl_forwarder/stl/*.hpp)

add_library(${PROJECT_NAME} INTERFACE ${DETAIL_HDR_FILES} ${STL_HDR_FILES})
# add alias so the project can be uses with add_subdirectory
add_library(opencv_stl_forwarder::opencv_stl_forwarder ALIAS ${PROJECT_NAME})

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(CMAKE_CXX_STANDARD 14)

# Adding the install interface generator expression makes sure that the include
# files are installed to the proper location (provided by GNUInstallDirs)
target_include_directories(
  ${PROJECT_NAME}
  INTERFACE $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

if(OPENCV_STL_FORWARDER_BUILD_BENCHMARKS)
    if(NOT OPENCV_STL_FORWARDER_BUILD_TESTS)
        message("Benchmark requires tests. Turning on tests.")
        set(OPENCV_STL_FORWARDER_BUILD_TESTS ON) #Benchmark requires tests
    endif()
endif()

if(OPENCV_STL_FORWARDER_BUILD_TESTS)
    add_subdirectory(test)
endif()

if(OPENCV_STL_FORWARDER_BUILD_BENCHMARKS)
    add_subdirectory(benchmark)
endif()

# locations are provided by GNUInstallDirs
install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}_Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_NAME}ConfigVersion.cmake"
                                 VERSION ${PROJECT_VERSION}
                                 COMPATIBILITY SameMajorVersion)

configure_package_config_file(
  "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION
  ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)

install(EXPORT ${PROJECT_NAME}_Targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)

install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
              "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/SI DESTINATION include)

set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")

include(CPack)
