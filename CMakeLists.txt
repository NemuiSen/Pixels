cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 20)
set(EXECUTABLE_OUTPUT_PATH "../bin")
# set(CMAKE_EXE_LINKER_FLAGS "-Xlinker /subsystem:windows")

project(pixels)
file(GLOB SRC "src/*.cpp")
include_directories(include)
add_executable(${PROJECT_NAME} ${SRC})

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "D:/Core/sen/programacion/cpp_libs/sfml/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)