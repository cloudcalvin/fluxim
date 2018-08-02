cmake_minimum_required (VERSION 3.5.1)
project (Jhin)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Ensure C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(cmake_generated ${CMAKE_BINARY_DIR}/CMakeCache.txt
                    ${CMAKE_BINARY_DIR}/cmake_install.cmake
                    ${CMAKE_BINARY_DIR}/Makefile
                    ${CMAKE_BINARY_DIR}/CMakeFiles)

foreach(file ${cmake_generated})
  if (EXISTS ${file})
     file(REMOVE_RECURSE ${file})
  endif()
endforeach(file)

add_subdirectory(src)

find_package(Boost 1.57.0 COMPONENTS system filesystem REQUIRED)
find_package(Armadillo REQUIRED)
find_package(VTK REQUIRED)

include(${VTK_USE_FILE})

include_directories(${ARMADILLO_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/local)

if(Boost_FOUND)
    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})
endif()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
link_directories(${CONAN_LIB_DIRS})
include_directories(${CONAN_INCLUDE_DIRS})

add_executable(Jhin ${JHIN_SRC})

target_compile_features(Jhin PRIVATE cxx_range_for)

target_link_libraries(Jhin ${ARMADILLO_LIBRARIES})
target_link_libraries(Jhin ${Boost_LIBRARIES})
target_link_libraries(Jhin ${VTK_LIBRARIES})
target_link_libraries(Jhin ${CONAN_LIBS_DOCOPT.CPP})
