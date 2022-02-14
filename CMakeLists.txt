cmake_minimum_required(VERSION 2.8.3)
project(fsm_bump_go)

set(CMAKE_CXX_STANDARD 17)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  roslint
)

catkin_package(
CATKIN_DEPENDS roscpp std_msgs kobuki_msgs sensor_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  include
)

add_library(${PROJECT_NAME}
  src/fsm_bump_go/BumpGo.cpp
  src/fsm_bump_go/BumpGoAdv.cpp
  src/fsm_bump_go/BumpGoPro.cpp
)

add_executable(bumpgo_node src/bumpgo_node.cpp)
target_link_libraries(bumpgo_node ${catkin_LIBRARIES} ${PROJECT_NAME})

add_executable(bumpgoadv_node src/bumpgoadv_node.cpp)
target_link_libraries(bumpgoadv_node ${catkin_LIBRARIES} ${PROJECT_NAME})

add_executable(bumpgopro_node src/bumpgopro_node.cpp)
target_link_libraries(bumpgopro_node ${catkin_LIBRARIES} ${PROJECT_NAME})

roslint_cpp(
 src/bumpgo_node.cpp
 src/fsm_bump_go/BumpGo.cpp
 include/fsm_bump_go/BumpGo.h
 src/bumpgoadv_node.cpp
 src/fsm_bump_go/BumpGoAdv.cpp
 include/fsm_bump_go/BumpGoAdv.h
 src/bumpgopro_node.cpp
 src/fsm_bump_go/BumpGoPro.cpp
 include/fsm_bump_go/BumpGoPro.h
)
