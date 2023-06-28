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

add_executable(day_4 day_4.cpp ${UTILS})
configure_file(data/input_day_4.txt ${CMAKE_BINARY_DIR}/ COPYONLY)

add_executable(day_5 day_5.cpp ${UTILS})
configure_file(data/input_day_5.txt ${CMAKE_BINARY_DIR}/ COPYONLY)

add_executable(day_6 day_6.cpp ${UTILS})
configure_file(data/input_day_6.txt ${CMAKE_BINARY_DIR}/ COPYONLY)

add_executable(day_7 day_7.cpp ${UTILS})
configure_file(data/input_day_7.txt ${CMAKE_BINARY_DIR}/ COPYONLY)

add_executable(day_8 day_8.cpp ${UTILS})
configure_file(data/input_day_8.txt ${CMAKE_BINARY_DIR}/ COPYONLY)


