# ROS-Workshop-2.0

*Official Repository for ROS-based Manipulator, implemented with ESP32*

__Prerequisites__: **ROS, initialiased with a catkin_ws workspace; ESP-IDF**

Run the following command for a quick install:

```bash
./install.sh
```
## Steps:

1) Flash the code 'Server_with_Servo_Control' onto your ESP32; wait till it connects to the server
```bash
cd ~/esp/esp-idf/codes/Server_with_Servo_Control
make -j8 flash monitor
```
2) Start the ROS Core service i.e. the ROS Master by the `roscore` command.

3) Start the ROS Publisher by executing the relevant python script: (e.g. angle -> coordinates)
```bash
rosrun sra Publisher_ForwardKinematics.py
```
4) Start the ROS Subscriber by executing the relevant python script, which would then connect to the ESP32 via the server
```bash
rosrun sra SubscriberSocketTCP.py
```
5) Enter the angles on the publisher side and voila! See your manipulator moving!
