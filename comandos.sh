blue='\e[0;34m'
NC='\e[0m' # No Color
#font colors:
#Black        0;30     Dark Gray     1;30
#Blue         0;34     Light Blue    1;34
#Green        0;32     Light Green   1;32
#Cyan         0;36     Light Cyan    1;36
#Red          0;31     Light Red     1;31
#Purple       0;35     Light Purple  1;35
#Brown/Orange 0;33     Yellow        1;33
#Light Gray   0;37     White         1;37

echo -e "${blue} Instalação do ROS2...${NC}"
apt-cache policy | grep universe
sudo apt update && sudo apt install curl gnupg lsb-release
sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(source /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null
sudo apt update
sudo apt upgrade
sudo apt install ros-humble-desktop
echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc
sudo apt install python3-colcon-common-extensions

echo -e "${blue} Instalação das bibliotecas necessárias...${NC}"
sudo apt install python3-pip
sudo pip3 install opencv-python
cd src/vision_test/vision_test
pip install -r requirements.txt 
sudo pip install construct

echo -e "${blue} setup new rules for usb names${NC}"
sudo mv robot-usb-ports.rules /etc/udev/rules.d/
sudo udevadm control --reload-rules
sudo udevadm trigger

echo -e "${blue} setup commands${NC}"
sudo cp ~/RoboFEI-HT_2022_SOFTWARE/scripts/compile.sh /usr/local/bin/compile
sudo cp ~/RoboFEI-HT_2022_SOFTWARE/scripts/imu.sh /usr/local/bin/imu
sudo cp ~/RoboFEI-HT_2022_SOFTWARE/scripts/control.sh /usr/local/bin/control
sudo cp ~/RoboFEI-HT_2022_SOFTWARE/scripts/vision.sh /usr/local/bin/vision
sudo cp ~/RoboFEI-HT_2022_SOFTWARE/scripts/decision.sh /usr/local/bin/decision
sudo cp ~/RoboFEI-HT_2022_SOFTWARE/scripts/gamecontroller.sh /usr/local/bin/gamecontroller
sudo cp ~/RoboFEI-HT_2022_SOFTWARE/scripts/motors.sh /usr/local/bin/motors

sudo chown root: /usr/local/bin/compile /usr/local/bin/imu /usr/local/bin/control /usr/local/bin/vision /usr/local/bin/decision /usr/local/bin/gamecontroller /usr/local/bin/motors
sudo chmod 755 /usr/local/bin/compile /usr/local/bin/imu /usr/local/bin/control /usr/local/bin/vision /usr/local/bin/decision /usr/local/bin/gamecontroller /usr/local/bin/motors




