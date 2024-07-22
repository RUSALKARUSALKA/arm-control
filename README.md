1、编译

新建工程文件夹ws

cd ws

mkdir src

cd src

clone code

cd ../到ws路径下

rosdep install --from-paths src --ignore-src --rosdistro humble -y

colcon build

2、启动arm-servos，用于与驱动代码通信，基于串口

source install/local_setup.sh

ros2 run arm_servos servios_serial_driver

3、启动moveit demo

ros2 launch moveit2_tutorials demo.launch.py


 
