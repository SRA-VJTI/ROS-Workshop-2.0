# ROS_Workshop-2.0
Offficial Repository for the ROS-based Manipulator Workshop

I) Create ROS package named 'SRA'

cd ~/catkin_ws/src 

catkin_create_pkg SRA std_msgs rospy roscpp

II) Build catkin workspace and source the setup file:

cd ~/catkin_ws

catkin_make

. ~/catkin_ws/devel/setup.bash

III) Check dependencies

rospack depends1 SRA

roscd SRA

cat package.xml

IV) Copy the 'package.xml', 'CMakelists.txt', 'msg' & 'script' from the ROS_python folder and paste it to '~/catkin_ws/src/SRA'

V) Enter the 'catkin make' command from the catkin_ws directory

VI) Navigate to '~/catkin_ws/src/SRA/scripts' and enter the command, for each of the files:

sudo chmod +x file_name.py

VII) Copy the ROS_SRA19 from the ESP-IDF folder to the '~/esp/esp-idf/components' folder

VIII) Copy all the codes to the '~/esp/esp-idf/' folder.
