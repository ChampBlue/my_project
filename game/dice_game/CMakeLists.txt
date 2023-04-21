cmake_minimum_required(VERSION 3.24)
project(dice_game)

set("${CMAKE_CXX_FLAGS} 17")
find_package(OpenCV REQUIRED)
set(SOURCE_FILES main.cpp)
add_executable(dice_game ${SOURCE_FILES})
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${MYSQL_INCLUDE_DIR})
target_link_libraries(dice_game ${OpenCV_LIBS} mysqlclient pthread)

