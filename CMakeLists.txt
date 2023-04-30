cmake_minimum_required(VERSION 3.25)
project(least_square_approximation)

set(CMAKE_CXX_STANDARD 23)

find_package(Boost 1.40.0 COMPONENTS filesystem system iostreams REQUIRED)
find_package(Gnuplot REQUIRED)

add_executable(least_square_approximation main.cpp agla/mtx/matrix.cpp agla/mtx/matrix.hpp agla/mtx/square_matrix.cpp agla/mtx/square_matrix.hpp agla/mtx/identity_matrix.cpp agla/mtx/identity_matrix.hpp agla/mtx/elimination_matrix.cpp agla/mtx/elimination_matrix.hpp agla/mtx/permutation_matrix.cpp agla/mtx/permutation_matrix.hpp agla/mtx/column_vector.cpp agla/mtx/column_vector.hpp agla/predator_prey.hpp)

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

include_directories(${GNUPLOT_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GNUPLOT_LIBRARIES})
