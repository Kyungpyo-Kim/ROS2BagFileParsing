// C/C++
#include <cstdio>

// STD
#include <iostream>

// ROS
#include "rosbag2/sequential_reader.hpp"
#include "rosbag2/typesupport_helpers.hpp"
#include "rosbag2/converter_interfaces/serialization_format_converter.hpp"

// ROS MSG
#include "dev_cpp_pkg/msg/gps_rx.hpp"

using rosbag2::converter_interfaces::SerializationFormatConverter;

int main(int argc, char ** argv)
{
  (void) argc;
  (void) argv;
  
  rosbag2::SequentialReader reader;
  rosbag2::StorageOptions storage_options{};
  
  storage_options.uri = "../rosbag2_test_data";
  storage_options.storage_id = "sqlite3";

  rosbag2::ConverterOptions converter_options{};
  converter_options.input_serialization_format = "cdr";
  converter_options.output_serialization_format = "cdr";
  reader.open(storage_options, converter_options);
  
  auto topics = reader.get_all_topics_and_types();

  // about metadata
  for (auto t:topics){
    std::cout << "meta name: " << t.name << std::endl;
    std::cout << "meta type: " << t.type << std::endl;
    std::cout << "meta serialization_format: " << t.serialization_format << std::endl;
  }
  
  // read and deserialize "serialized data"
  if (reader.has_next()){

    // serialized data
    auto serialized_message = reader.read_next();
    
    // deserialization and conversion to ros message
    dev_cpp_pkg::msg::GpsRx msg;
    auto ros_message = std::make_shared<rosbag2_introspection_message_t>();
    ros_message->time_stamp = 0;
    ros_message->message = nullptr;
    ros_message->allocator = rcutils_get_default_allocator();
    ros_message->message = &msg;
    auto type_support = rosbag2::get_typesupport("dev_cpp_pkg/msg/GpsRx", "rosidl_typesupport_cpp");

    rosbag2::SerializationFormatConverterFactory factory;
    std::unique_ptr<rosbag2::converter_interfaces::SerializationFormatDeserializer> cdr_deserializer_;
    cdr_deserializer_ = factory.load_deserializer("cdr");
    
    cdr_deserializer_->deserialize(serialized_message, type_support, ros_message);

    // ros message data
    std::cout << std::endl;
    std::cout << msg.gps_latitude << std::endl;
    std::cout << msg.gps_longitude << std::endl;
    std::cout << msg.gps_height << std::endl;
  }
  
  return 0;
}