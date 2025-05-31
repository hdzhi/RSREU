cmake_minimum_required(VERSION 3.10)
project(RacingGame)

set(CMAKE_CXX_STANDARD 17)

find_package(FLTK REQUIRED)

include_directories(
    include
    ${FLTK_INCLUDE_DIRS}
)

file(GLOB SOURCES
    "src/*.cpp"
    "src/Controller/*.cpp"
    "src/Model/*.cpp"
    "src/View/*.cpp"
)

add_executable(RacingGame ${SOURCES})
target_link_libraries(RacingGame ${FLTK_LIBRARIES})