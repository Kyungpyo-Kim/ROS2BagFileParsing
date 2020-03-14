# ROS2BagFileParsing
ROS2 Bag file parsing
Korean document: https://kyungpyo-kim.github.io/study/ROS2-Bag-file-parsing/

# Getting started

1. Install ros1 melodic
2. Install ros2 dashing
3. Install rosbag2 packages

    ```bash
    sudo apt install ros-dashing-rosbag2* ros-dashing-ros2bag*
    ```
4. Build
    
    ```bash
    cd dev_cpp_pkg
    colcon build
    ```

5. Run package

    ```bash
    . install/setup.bash
    ros2 run dev_cpp_pkg dev_cpp_node
    ```
