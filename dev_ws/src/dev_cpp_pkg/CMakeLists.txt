cmake_minimum_required(VERSION 3.5)
project(dev_cpp_pkg)


# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()


find_package(ament_cmake REQUIRED)
find_package(ament_index_cpp REQUIRED)
find_package(rosbag2 REQUIRED)
find_package(rosbag2_storage REQUIRED)
find_package(rosidl_generator_cpp REQUIRED)
find_package(rosidl_typesupport_cpp REQUIRED)
find_package(rosidl_typesupport_introspection_cpp REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(std_msgs REQUIRED)
find_package(dev_cpp_pkg REQUIRED)


rosidl_generate_interfaces(dev_cpp_pkg
  msg/GpsRx.msg
  DEPENDENCIES std_msgs
  DEPENDENCIES builtin_interfaces
)

include_directories(
  include
  ${dev_cpp_pkg_INCLUDE_DIRS}
)

add_executable(dev_cpp_node src/dev_cpp_node.cpp)

target_include_directories(dev_cpp_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

install(TARGETS dev_cpp_node
  EXPORT export_${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME})

ament_target_dependencies(
  dev_cpp_node
  "rclcpp"
  "rosbag2"
  "rosbag2_storage"
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_dependencies(rosidl_default_runtime)

ament_package()
