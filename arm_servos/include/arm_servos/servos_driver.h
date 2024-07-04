#include <chrono>
#include <memory>
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <thread>
#include <algorithm>
#include <csignal>
#include <stdlib.h>
#include <serial/serial.h>
#include <time.h>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <geometry_msgs/msg/transform_stamped.hpp>
#include "geometry_msgs/msg/pose_with_covariance_stamped.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "std_msgs/msg/int32.hpp"  

using namespace std::chrono_literals;
using std::placeholders::_1;
using std::placeholders::_2;

class BaseRun : public rclcpp::Node
{
public:
    BaseRun(std::string nodeName);
    ~BaseRun();

private:
    void readSerialData();
    void setMotoTargetPose(uint16_t moto_one, uint16_t moto_two, uint16_t moto_thr, uint16_t moto_fou, uint16_t moto_fiv, uint16_t moto_six);
    void base_timer_callback();
private:
    uint16_t moto_one_pose = 1500;
    serial::Serial serial_;
    std::shared_ptr<std::thread> serial_thread_;
    rclcpp::TimerBase::SharedPtr base_timer;
};