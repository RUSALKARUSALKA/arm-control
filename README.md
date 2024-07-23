## 编译

```
mkdir ws
cd ws
mkdir src
cd src
git clone https://github.com/fengyongronglu/arm-control
cd ..
rosdep install --from-paths src --ignore-src --rosdistro humble -y
colcon build
```
moveit: https://moveit.picknik.ai/main/doc/tutorials/getting_started/getting_started.html

## 启动arm-servos，用于与驱动代码通信，基于串口

```
source install/local_setup.sh
ros2 run arm_servos servios_serial_driver
```
## 启动moveit demo
```
ros2 launch moveit2_tutorials demo.launch.py
```

 
