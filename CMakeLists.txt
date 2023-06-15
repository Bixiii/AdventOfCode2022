cmake_minimum_required(VERSION 3.16)
project(AdventOfCode2021)

set(CMAKE_CXX_STANDARD 20)

set(UTILS utils.cpp utils.h)

add_executable(template day_0.cpp ${UTILS})
configure_file(data/input_day_0.txt ${CMAKE_BINARY_DIR}/ COPYONLY)

add_executable(day_1 day_1.cpp ${UTILS})
configure_file(data/input_day_1.txt ${CMAKE_BINARY_DIR}/ COPYONLY)

add_executable(day_2 day_2.cpp ${UTILS})
configure_file(data/input_day_2.txt ${CMAKE_BINARY_DIR}/ COPYONLY)

add_executable(day_3 day_3.cpp ${UTILS})
configure_file(data/input_day_3.txt ${CMAKE_BINARY_DIR}/ COPYONLY)


