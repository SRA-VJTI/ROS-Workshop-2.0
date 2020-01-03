## ROS_Workshop - 2.0
#### Offficial Repository for the ROS-based Manipulator Workshop

1. Create ROS package named **SRA**

* `cd ~/catkin_ws/src`

* `catkin_create_pkg SRA std_msgs rospy roscpp`

2. Build catkin workspace and source the setup file

* `cd ~/catkin_ws`

* `catkin_make`

* `. ~/catkin_ws/devel/setup.bash`

3. Check dependencies

* `rospack depends1 SRA`

* `roscd SRA`

* `cat package.xml`

4. Copy the *package.xml*, *CMakelists.txt*, *msg* & *script* from the ROS_python folder and paste it to *`~/catkin_ws/src/SRA`*

5. Enter the *`catkin_make`* command from the catkin_ws directory

6. Navigate to *`~/catkin_ws/src/SRA/scripts`* and enter the command, for each of the files

* `sudo chmod +x file_name.py`

7. Copy the ***ROS_SRA19*** from the ESP-IDF folder to the *`~/esp/esp-idf/components' folder`*

8. Copy all the codes to the *`~/esp/esp-idf/`* folder
