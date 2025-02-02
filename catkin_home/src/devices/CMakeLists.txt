# TODO: Review why we are using this old version of CMake.
cmake_minimum_required(VERSION 2.8.3)
project(devices)

# Includes `ExternalProject_Add()`.
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  roslib
  audio_common_msgs
  message_generation
  intercom
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)


## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

## To declare and build messages, services or actions from within this
## package, follow these steps:
## * Let MSG_DEP_SET be the set of packages whose message types you use in
##   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
## * In the file package.xml:
##   * add a build_depend tag for "message_generation"
##   * add a build_depend and a exec_depend tag for each package in MSG_DEP_SET
##   * If MSG_DEP_SET isn't empty the following dependency has been pulled in
##     but can be declared for certainty nonetheless:
##     * add a exec_depend tag for "message_runtime"
## * In this file (CMakeLists.txt):
##   * add "message_generation" and every package in MSG_DEP_SET to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * add "message_runtime" and every package in MSG_DEP_SET to
##     catkin_package(CATKIN_DEPENDS ...)
##   * uncomment the add_*_files sections below as needed
##     and list every .msg/.srv/.action file to be processed
##   * uncomment the generate_messages entry below
##   * add every package in MSG_DEP_SET to generate_messages(DEPENDENCIES ...)

## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate services in the 'srv' folder
add_service_files(
  FILES
  GetCameraIndex.srv
)

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
 generate_messages(
   DEPENDENCIES
   audio_common_msgs
   intercom
 )

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

## To declare and build dynamic reconfigure parameters within this
## package, follow these steps:
## * In the file package.xml:
##   * add a build_depend and a exec_depend tag for "dynamic_reconfigure"
## * In this file (CMakeLists.txt):
##   * add "dynamic_reconfigure" to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * uncomment the "generate_dynamic_reconfigure_options" section below
##     and list every .cfg file to be processed

## Generate dynamic reconfigure parameters in the 'cfg' folder
# generate_dynamic_reconfigure_options(
#   cfg/DynReconf1.cfg
#   cfg/DynReconf2.cfg
# )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
# TODO: Include the dependencies of RNNoise.
# https://answers.ros.org/question/261002/catkin_packagecatkin_depends-vs-find_packagecatkin-required-components/
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES devices
   CATKIN_DEPENDS roscpp rospy roslib message_runtime audio_common_msgs intercom
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  src
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
# add_library(${PROJECT_NAME}
#   src/${PROJECT_NAME}/devices.cpp
# )

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
# add_executable(${PROJECT_NAME}_node src/devices_node.cpp)

## Rename C++ executable without prefix
## The above recommended prefix causes long target names, the following renames the
## target back to the shorter version for ease of user use
## e.g. "rosrun someones_pkg node" instead of "rosrun someones_pkg someones_pkg_node"
# set_target_properties(${PROJECT_NAME}_node PROPERTIES OUTPUT_NAME node PREFIX "")

## Add cmake target dependencies of the executable
## same as for the library above
# add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
# target_link_libraries(${PROJECT_NAME}_node
#   ${catkin_LIBRARIES}
# )


# Declare the rnnoise_sl target.
# It is an external, static, c library (.a).
# It is directly downloaded from https://github.com/xiph/rnnoise and built as its
# README says. For this, linux is assumed, also that configure, make, and ar are 
# installed.
# https://mirkokiefer.com/cmake-by-example-f95eb47d45b1

# TODO: Because we are using this to only download the file and uncompress it,
# maybe try to use another simpler macro.
ExternalProject_Add(
  rnnoise_project
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/rnnoise_project_dir
  # TODO: Check using better the GIT args and maybe using a commit instead of master.
  URL https://github.com/xiph/rnnoise/archive/master.zip
  # As this macro seems to not support several *_COMMAND args, we move the 
  # commands to `add_custom_command()`.
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
)
# Make the building steps for the downloaded RNNoise.
# TODO: Try to move this to the downloading part or something to avoid cmake running
# this steps each time.
add_custom_command(
  TARGET rnnoise_project
  # Even that the library is actually used in link-time, with PRE_LINK doesn't
  # work. Maybe because it is used but through another target.
  PRE_BUILD
  COMMAND "${CMAKE_CURRENT_BINARY_DIR}/rnnoise_project_dir/src/rnnoise_project/autogen.sh"
  COMMAND "${CMAKE_CURRENT_BINARY_DIR}/rnnoise_project_dir/src/rnnoise_project/configure"
  COMMAND "make" "--directory=${CMAKE_CURRENT_BINARY_DIR}/rnnoise_project_dir/src/rnnoise_project"
  COMMAND "ar" "rcs" "${CMAKE_CURRENT_BINARY_DIR}/rnnoise_project_dir/src/rnnoise_project/rnnoise.a" "${CMAKE_CURRENT_BINARY_DIR}/rnnoise_project_dir/src/rnnoise_project/src/*.o"
  COMMENT "Building the library RNNoise (Note you need linux, configure, make, and ar installed)....."
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/rnnoise_project_dir/src/rnnoise_project
)

# Declare an "actual" library that will depend in the real RNNoise downloaded-and-built library.
add_library(rnnoise_sl STATIC IMPORTED)
set_target_properties(rnnoise_sl PROPERTIES 
  LINKER_LANGUAGE C
  IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/rnnoise_project_dir/src/rnnoise_project/rnnoise.a
  # This header location doesn't seem to be used, that's why the following `include_directories()`.
  PUBLIC_HEADER ${CMAKE_CURRENT_BINARY_DIR}/rnnoise_project_dir/src/rnnoise_project/include/rnnoise.h
)
add_dependencies(rnnoise_sl rnnoise_project)

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}/rnnoise_project_dir/src/rnnoise_project/include
)

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
# install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_devices.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)

# Declare the `InputAudio` target.
# TODO: Maybe move this to the "Building" section will be better.
add_executable(InputAudio
  src/InputAudio.cpp
  src/RnnoiseMethods/HelperMethods.cpp
  src/RnnoiseMethods/Algorithm3Steps1.cpp
  src/RnnoiseMethods/AlgorithmAccTolerance1.cpp
)
target_link_libraries(InputAudio ${catkin_LIBRARIES} rnnoise_sl)
# TODO: These dependecies seem to be not needed, now they generate a warning
# and, in later cmake versions, an error...
add_dependencies(InputAudio audio_common_msgs message_generation)
