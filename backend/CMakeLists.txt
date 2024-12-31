cmake_minimum_required(VERSION 3.22)
project(tsp_solver_backend)

set(CMAKE_CXX_STANDARD 20)

# Setting "Crow"
find_package(Crow)

# Setting "OR-Tools"
set(OR_TOOLS_DIR /app/or-tools)
include_directories(${OR_TOOLS_DIR}/include)
link_directories(${OR_TOOLS_DIR}/lib)

add_executable(tsp_solver_backend src/main.cpp)

# Link "Crow"
target_link_libraries(tsp_solver_backend PUBLIC Crow::Crow)

# Link "OR-Tools"
target_link_libraries(tsp_solver_backend PUBLIC ortools)
