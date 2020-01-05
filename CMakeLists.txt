cmake_minimum_required(VERSION 3.14)
set(PROJECT_NAME LinearSolver)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)

if(APPLE)
    # Fix linking on 10.14+. See https://stackoverflow.com/questions/54068035
    link_directories(/usr/local/lib)
endif()

# might be system specific
set(SYS_INCLUDE /usr/local/include/)
# add to headers
include_directories(${SYS_INCLUDE})

# OpenMP
FIND_PACKAGE(OpenMP REQUIRED)
if(OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

file(GLOB SOURCE_FILES
        "main.cpp"
        "row.cpp"
        "solver.cpp"
        "matrix.cpp"
        "dualSimplexSolver.cpp"
        "vanillaSimplexSolver.cpp"
        "utility.cpp"
        )

add_executable(${PROJECT_NAME} ${SOURCE_FILES} )