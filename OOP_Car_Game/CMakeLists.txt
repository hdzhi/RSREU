cmake_minimum_required(VERSION 3.20.0)

project(RacingGame)

file(GLOB_RECURSE APP_SOURCES 
    src/Model/*.cpp
    src/View/*.cpp
    src/Controller/*.cpp
) 

# Specify the source files for the project
set(SOURCES 
    src/main.cpp
    ${APP_SOURCES}
)

add_executable(${PROJECT_NAME} ${SOURCES})

option(STATIC_BUILD "Enable static build" ON)
set(HIDE_CONSOLE ON)

# Find the FLTK library
find_package(FLTK REQUIRED)

if(MINGW)
    # Configure a static build
    if(STATIC_BUILD)
        set(BUILD_SHARED_LIBS OFF)
        set_target_properties(${PROJECT_NAME} PROPERTIES LINK_SEARCH_START_STATIC 1)
        set_target_properties(${PROJECT_NAME} PROPERTIES LINK_SEARCH_END_STATIC 1)
        set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
    endif()

    # Disable the command window
    if(HIDE_CONSOLE)
        message("Console hidden")
        set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")
    endif()
endif()

# Add the path to the headers for compilation
target_include_directories(${PROJECT_NAME} PUBLIC 
    ${FLTK_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(${PROJECT_NAME} 
    ${FLTK_LIBRARIES}
)

# Also add necessary libraries when building on Windows
if(WIN32)
    target_link_libraries(${PROJECT_NAME} comctl32 ws2_32)
endif()

# Also add necessary libraries when building on Unix
if(UNIX)
    target_link_libraries(${PROJECT_NAME} X11 Xrender)
endif()