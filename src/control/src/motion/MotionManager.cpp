/*--------------------------------------------------------------------

******************************************************************************
* @file MotionManager.cpp
* @author ROBOTIS
* @version V2.0.0 - ROBOFEI-HT
* @created -
* @Modified Isaac Jesus da Silva - University Center FEI - 27/09/2016  😛
* @e-mail isaac25silva@yahoo.com.br
* @brief MotionManager 😛
****************************************************************************
**************************************************************************** 
---------------------------------------------------------------------------*/
// ros2 run control gait_publisher


#include <stdio.h>
#include <math.h>
#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include "FSR.h"
#include "MX28.h"
#include "MotionManager.h"
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <cstdlib>
#include "minIni.h"

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "custom_interfaces/msg/set_position.hpp"
#include "custom_interfaces/msg/set_position_original.hpp"
#include "custom_interfaces/srv/get_position.hpp"
#include "custom_interfaces/msg/walk.hpp"
#include "custom_interfaces/msg/param_walk.hpp"

#define INI_FILE_PATH       "/home/robofei/ROS2/src/walk_test/src/control/Data/config.ini"
#define MOTION_FILE_PATH    "/home/robofei/ROS2/src/walk_test/src/control/Data/motion_4096.bin"

using namespace Robot;
using namespace std::chrono_literals;
using std::placeholders::_1;

// Torque adaption every second
const int TORQUE_ADAPTION_CYCLES = 1000 / MotionModule::TIME_UNIT;
const int DEST_TORQUE = 1023;
int position;

#define BROADCAST_ID        0xFE    // 254

//#define LOG_VOLTAGES 1
rclcpp::NodeOptions options;

float X_AMPLITUDE = 0;
float Y_AMPLITUDE = 0;
float A_AMPLITUDE = 0;
int last_movement = 0;
int walk=0;

MotionManager* MotionManager::m_UniqueInstance = new MotionManager(options);

MotionManager::MotionManager(const rclcpp::NodeOptions & options) :
        m_ProcessEnable(false),
        m_IsRunning(false),
        m_IsThreadRunning(false),
        m_IsLogging(false),
				m_torqueAdaptionCounter(TORQUE_ADAPTION_CYCLES),
				m_voltageAdaptionFactor(1.0),
        DEBUG_PRINT(false),
		rclcpp::Node("gait_publisher", options)
{
	
	subscription_imu = this->create_subscription<sensor_msgs::msg::Imu>("imu/data", 10, std::bind(&MotionManager::topic_callback, this, _1));
	subscription_walk = this->create_subscription<custom_interfaces::msg::Walk>("walking", 10, std::bind(&MotionManager::topic_callback_walk, this, _1));
	subscription_param = this->create_subscription<custom_interfaces::msg::ParamWalk>("param_walk", 10, std::bind(&MotionManager::topic_callback_param, this, _1));
	publisher_ = this->create_publisher<custom_interfaces::msg::SetPosition>("set_position", 10); 
	publisher_single = this->create_publisher<custom_interfaces::msg::SetPositionOriginal>("set_position_single", 10); 
	client = this->create_client<custom_interfaces::srv::GetPosition>("get_position");
    timer_ = this->create_wall_timer(8ms, std::bind(&MotionManager::Process, this));
	keep_walking = false;
	for(int i = 0; i < JointData::NUMBER_OF_JOINTS; i++)
        m_Offset[i] = 0;
	// update_thread_ = std::thread(std::bind(&MotionManager::update_loop, this));
	printf("CONSTRUTOR\n");
	ini = new minIni((char *)INI_FILE_PATH);
	
}

void MotionManager::update_loop(void)
{
  while (rclcpp::ok())
  {
   RCLCPP_INFO(this->get_logger(), "Running motion manager");
   this->Process();
  }  
}

MotionManager::~MotionManager()
{
}

void MotionManager::topic_callback_param(const std::shared_ptr<custom_interfaces::msg::ParamWalk> param_msg_) const
    {
        X_AMPLITUDE = param_msg_->walk;
        Y_AMPLITUDE = param_msg_->sidle;
		A_AMPLITUDE = param_msg_->turn;
	}

void MotionManager::topic_callback(const std::shared_ptr<sensor_msgs::msg::Imu> imu_msg_) const
    {
        float IMU_GYRO_X = -imu_msg_->angular_velocity.x/10;
        float IMU_GYRO_Y  = -imu_msg_->angular_velocity.y/10;
	}

void MotionManager::topic_callback_walk(const std::shared_ptr<custom_interfaces::msg::Walk> walk_msg_) const
    {
        walk = (int)walk_msg_->walk;
		// printf("MOVEMENT %d\n", walk);
		// printf("LAST MOVEMENT %d\n", last_movement);
		// printf("KEEP WALKING %d\n", MotionManager::GetInstance()->keep_walking);

		if (walk != last_movement && walk!=0){ 
			//printf("CALLBACK NAO WALK\n");
			//MotionManager::GetInstance()->SetEnable(false);
			MotionManager::GetInstance()->keep_walking=false;
		}
		//printf("KEEP WALKING DEPOIS DO IF %d\n", MotionManager::GetInstance()->keep_walking);
		//printf("FASE DEPOIS DO IF %d\n", Walking::GetInstance()->GetCurrentPhase());
		
		if (MotionManager::GetInstance()->keep_walking==false && Walking::GetInstance()->GetCurrentPhase()==0){
			//printf("MOVEMENT DENTRO DO IF %d\n", walk);
			//printf("LAST MOVEMENT DENTRO DO IF %d\n", last_movement);
			if (walk == 1 && last_movement!=1){
				printf("CALLBACK WALK\n");
				last_movement = walk;
				printf("FASE %d\n", Walking::GetInstance()->GetCurrentPhase());
				printf("IS RUNNING %d\n", Walking::GetInstance()->IsRunning());
				Walking::GetInstance()->LoadINISettings(ini, "Walking Config");
			}
			else if (walk == 2 && last_movement!=2){
				printf("CALLBACK GAIT\n");
				last_movement = walk;
				printf("FASE %d\n", Walking::GetInstance()->GetCurrentPhase());
				printf("IS RUNNING %d\n", Walking::GetInstance()->IsRunning());
				Walking::GetInstance()->LoadINISettings(ini, "Gait");
				//printf("CALLBACK GAIT\n");
			}
			else if (walk == 3 && last_movement!=3){
				last_movement = walk;
				printf("CALLBACK TURN\n");
				Walking::GetInstance()->LoadINISettings(ini, "Turn Robot");
				//printf("CALLBACK TURN\n");
			}
			else if (walk == 4 && last_movement!=4){
				last_movement = walk;
				printf("CALLBACK WALK SLOW\n");
				Walking::GetInstance()->LoadINISettings(ini, "Walk Slow");
			}
			else if (walk == 5 && last_movement!=5){
				last_movement = walk;
				printf("CALLBACK TURN BALL RIGHT\n");
				Walking::GetInstance()->LoadINISettings(ini, "Turn Ball Right");
			}
			else if (walk == 6 && last_movement!=6){
				last_movement = walk;
				printf("CALLBACK TURN BALL LEFT\n");
				Walking::GetInstance()->LoadINISettings(ini, "Turn Ball Left");
			}
			else if (walk == 7 && last_movement!=7){
				last_movement = walk;
				printf("CALLBACK SIDLE RIGHT\n");
				Walking::GetInstance()->LoadINISettings(ini, "Sidle Right");
			}
			else if (walk == 8 && last_movement!=8){
				last_movement = walk;
				printf("CALLBACK SIDLE LEFT\n");
				Walking::GetInstance()->LoadINISettings(ini, "Sidle Left");
			}
			else if (walk == 9 && last_movement!=9){
				last_movement = walk;
				printf("CALLBACK WALK BACKWARD\n");
				Walking::GetInstance()->LoadINISettings(ini, "Walking Backward");
			}
			else if (walk == 10 && last_movement!=10){
				last_movement = walk;
				printf("CALLBACK WALK BACKWARD SLOW\n");
				Walking::GetInstance()->LoadINISettings(ini, "Walking Backward Slow");
			}
			else if (walk == 11 && last_movement!=11){
				last_movement = walk;
				printf("CALLBACK TURN ROBOT RIGHT\n");
				Walking::GetInstance()->LoadINISettings(ini, "Turn Robot Right");
			}
			else if (walk == 12 && last_movement!=12){
				last_movement = walk;
				printf("CALLBACK TURN ROBOT LEFT\n");
				Walking::GetInstance()->LoadINISettings(ini, "Turn Robot Left");
			}


			if(walk!=0){
				printf("WALK FUNFANDO\n");
				MotionManager::GetInstance()->LoadINISettings(ini);
				Action::GetInstance()->Stop();
				//MotionManager::GetInstance()->AddModule((MotionModule*)Walking::GetInstance());
				MotionManager::GetInstance()->Initialize();
				Walking::GetInstance()->m_Joint.SetEnableBody(true);
				Action::GetInstance()->m_Joint.SetEnableBody(false);
				MotionStatus::m_CurrentJoints.SetEnableBodyWithoutHead(true);
				MotionManager::GetInstance()->SetEnable(true);
				printf("%d\n", MotionManager::GetInstance()->GetEnable());
				Walking::GetInstance()->X_MOVE_AMPLITUDE = X_AMPLITUDE; 
				Walking::GetInstance()->Y_MOVE_AMPLITUDE = Y_AMPLITUDE; 
				Walking::GetInstance()->A_MOVE_AMPLITUDE = A_AMPLITUDE; 
				Walking::GetInstance()->Start();
				// printf("WALKING %d\n", Walking::GetInstance()->IsRunning());
				// printf("ACTION %d\n", Action::GetInstance()->IsRunning());
				MotionManager::GetInstance()->keep_walking=true;
				//printf("KEEP WALKING DEPOIS %d\n", MotionManager::GetInstance()->keep_walking);
			}
			
			else{ // parar o walking
				printf("WALK PARADDO :( \n");
				MotionManager::GetInstance()->LoadINISettings(ini);
				Walking::GetInstance()->LoadINISettings(ini);
				if (MotionManager::GetInstance()->keep_walking==false && Walking::GetInstance()->GetCurrentPhase()==0){
					Action::GetInstance()->Stop();
					MotionManager::GetInstance()->AddModule((MotionModule*)Walking::GetInstance());
					MotionManager::GetInstance()->Initialize();
					Walking::GetInstance()->m_Joint.SetEnableBody(false);
					Action::GetInstance()->m_Joint.SetEnableBody(false);
					MotionStatus::m_CurrentJoints.SetEnableBodyWithoutHead(true);
					MotionManager::GetInstance()->SetEnable(true);
					printf("%d\n", MotionManager::GetInstance()->GetEnable());
					Walking::GetInstance()->Stop();
					// printf("WALKING %d\n", Walking::GetInstance()->IsRunning());
					// printf("ACTION %d\n", Action::GetInstance()->IsRunning());
					MotionManager::GetInstance()->keep_walking=true;
				}
				
			}

			
			// if(walk == 5){
			// 	MotionManager::GetInstance()->LoadINISettings(ini);
			// 	Walking::GetInstance()->LoadINISettings(ini);
			// 	Action::GetInstance()->LoadFile(MOTION_FILE_PATH);
			// 	MotionManager::GetInstance()->Initialize();
			// 	Action::GetInstance()->Initialize();
			// 	Walking::GetInstance()->Stop();
			// 	Walking::GetInstance()->m_Joint.SetEnableBody(false);
			// 	Action::GetInstance()->m_Joint.SetEnableBody(true);
			// 	MotionStatus::m_CurrentJoints.SetEnableBodyWithoutHead(true);
			// 	MotionManager::GetInstance()->SetEnable(true);
			// 	Action::GetInstance()->Start(24); 
			// 	printf("WALKING %d\n", Walking::GetInstance()->IsRunning());
			// 	printf("ACTION %d\n", Action::GetInstance()->IsRunning());
			// 	MotionManager::GetInstance()->keep_walking=true;
			// }
		}
		
		else{
				printf("CALLBACK NAO WALK\n");
		}
	}

bool MotionManager::Initialize(bool fadeIn)
{
	//rclcpp::spin_some(std::make_shared<GaitPublisher>());
	int value, error;
	printf("INITIALIZE\n");

	usleep(10000);
	//m_CM730 = cm730;
	m_Enabled = false;
	m_ProcessEnable = true;

	// if(m_CM730->Connect() == false)
	// {
	// 	if(DEBUG_PRINT == true)
	// 		fprintf(stderr, "Fail to connect CM-730\n");
	// 	return false;
	// }
	// auto request = std::make_shared<custom_interfaces::srv::GetPosition::Request>();
	// custom_interfaces::srv::GetPosition();
	

	for(int id=JointData::ID_MIN; id<=JointData::ID_MAX-2; id++) //diminui tirando a cabeça
	{
		if(DEBUG_PRINT == true)
			fprintf(stderr, "ID:%d initializing...", id);

	// 	request->id = id;
	// 	while (!client->wait_for_service(1s)) {
	// 		if (!rclcpp::ok()) {
	// 		RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
	// 		return 0;
	// 		}
	// 		RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
	// 	}

	// 	 using ServiceResponseFuture = rclcpp::Client<custom_interfaces::srv::GetPosition>::SharedFuture;
    // auto response_received_callback = [this](ServiceResponseFuture future) {
    //     auto result = future.get();
	// 	position = result->position;

    //     RCLCPP_INFO(this->get_logger(), "Position: %ld", result->position);
	// 	};

	// 	auto future_result = client->async_send_request(request, response_received_callback);
    

	// 	MotionStatus::m_CurrentJoints.SetValue(id, position);
	// 	MotionStatus::m_CurrentJoints.SetEnable(id, true);

		// if(m_CM730->ReadWord(id, MX28::P_PRESENT_POSITION_L, &value, &error) == CM730::SUCCESS)
		// {
		// 	MotionStatus::m_CurrentJoints.SetValue(id, value);
		// 	MotionStatus::m_CurrentJoints.SetEnable(id, true);

		// 	if(DEBUG_PRINT == true)
		// 		fprintf(stderr, "[%d] Success\n", value);
		// }
		// else
		// {
		// 	MotionStatus::m_CurrentJoints.SetEnable(id, false);

		// 	if(DEBUG_PRINT == true)
		// 		fprintf(stderr, " Fail\n");
		// }
		
	}

	if(fadeIn)
	{
		//for(int i=JointData::ID_R_SHOULDER_PITCH; i<JointData::NUMBER_OF_JOINTS; i++)
			//cm730->WriteWord(i, MX28::P_TORQUE_LIMIT_L, 0, 0);
	}

	m_fadeIn = fadeIn;
	m_torque_count = 0;

	m_CalibrationStatus = 0;
	m_FBGyroCenter = 512;
	m_RLGyroCenter = 512;

	return true;
}

bool MotionManager::Reinitialize()
{
	m_ProcessEnable = false;

	//m_CM730->DXLPowerOn();

	int value, error;
	for(int id=JointData::ID_MIN; id<=JointData::ID_MAX-2; id++)//tirando a cabeça
	{
		if(DEBUG_PRINT == true)
			fprintf(stderr, "ID:%d initializing...", id);
		
		// if(m_CM730->ReadWord(id, MX28::P_PRESENT_POSITION_L, &value, &error) == CM730::SUCCESS)
		// {
		// 	MotionStatus::m_CurrentJoints.SetValue(id, value);
		// 	MotionStatus::m_CurrentJoints.SetEnable(id, true);

		// 	if(DEBUG_PRINT == true)
		// 		fprintf(stderr, "[%d] Success\n", value);
		// }
		else
		{
			MotionStatus::m_CurrentJoints.SetEnable(id, false);

			if(DEBUG_PRINT == true)
				fprintf(stderr, " Fail\n");
		}
	}

	m_ProcessEnable = true;
	return true;
}

void MotionManager::Restartrobot()
{
	m_torque_count=0;
}

void MotionManager::StartLogging()
{
    char szFile[32] = {0,};

    int count = 0;
    while(1)
    {
        sprintf(szFile, "Logs/Log%d.csv", count);
        if(0 != access(szFile, F_OK))
            break;
        count++;
		if(count > 256) return;
    }
		m_LogFileStream.open(szFile, std::ios::out);
    for(int id = JointData::ID_MIN; id <= JointData::ID_MAX-2; id++)//tirando a cabeça
        m_LogFileStream << "nID_" << id << "_GP,nID_" << id << "_PP,";
    m_LogFileStream << "GyroFB,GyroRL,AccelFB,AccelRL,L_FSR_X,L_FSR_Y,R_FSR_X,R_FSR_Y," << "\x0d\x0a";

    m_IsLogging = true;
}

void MotionManager::StopLogging()
{
    m_IsLogging = false;
    m_LogFileStream.close();
}

void MotionManager::LoadINISettings(minIni* ini)
{
    LoadINISettings(ini, OFFSET_SECTION);
}
void MotionManager::LoadINISettings(minIni* ini, const std::string &section)
{
    int ivalue = INVALID_VALUE;

    for(int i = JointData::ID_MIN; i <= JointData::ID_MAX-2; i++)//tirando a cabeça
    {
        char key[10];
        sprintf(key, "ID_%.2d", i);
        if((ivalue = ini->geti(section, key, INVALID_VALUE)) != INVALID_VALUE)  MotionManager::GetInstance()->m_Offset[i] = ivalue;
		printf("OFFSET %d\n", MotionManager::GetInstance()->m_Offset[i]);
    }
		m_angleEstimator.LoadINISettings(ini, section + "_angle");
}
void MotionManager::SaveINISettings(minIni* ini)
{
    SaveINISettings(ini, OFFSET_SECTION);
}
void MotionManager::SaveINISettings(minIni* ini, const std::string &section)
{
    for(int i = JointData::ID_MIN; i <= JointData::ID_MAX-2; i++)//tirando a cabeça
    {
        char key[10];
        sprintf(key, "ID_%.2d", i);
        ini->put(section, key, m_Offset[i]);
    }
		m_angleEstimator.SaveINISettings(ini, section + "_angle");
}

#define GYRO_WINDOW_SIZE    100
#define ACCEL_WINDOW_SIZE   30
#define MARGIN_OF_SD        2.0
void MotionManager::Process()
{
	if(walk!=0){
	//RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "dentro do process");
	if((Walking::GetInstance())->m_Joint.GetEnable(5) == true)
	{
		Walking::GetInstance()->Process();
	}
	else if((Action::GetInstance())->m_Joint.GetEnable(5) == true)
	{
		Action::GetInstance()->Process();
	}
	// printf("FASE PROCESS %d\n", Walking::GetInstance()->GetCurrentPhase());
	// printf("IS RUNNING PROCESS %d\n", Walking::GetInstance()->IsRunning());

	// auto message = custom_interfaces::msg::SetPosition();  

    // message.id = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};          
	// message.position = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};   
	// publisher_->publish(message);
	if(m_fadeIn && m_torque_count < DEST_TORQUE) {
		//RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "dentro do primeiro if");
      //printf("entrou\n");
        if(m_torque_count < 100)
            m_torque_count += 3;
        else
            m_torque_count = 2047 ;

        //m_CM730->WriteWord(CM730::ID_BROADCAST, MX28::P_TORQUE_LIMIT_L, m_torque_count, 0);

		auto message_single = custom_interfaces::msg::SetPositionOriginal(); 
		message_single.id = BROADCAST_ID;
		message_single.address = MX28::P_GOAL_CURRENT;
		message_single.position = m_torque_count;
		publisher_single->publish(message_single);
        // m_CM730->write2ByteTxRx(portHandler, BROADCAST_ID, MX28::P_GOAL_CURRENT, m_torque_count, &dxl_error);
		
        if(m_torque_count == 2047)
        {
			RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "torque 2047");
			message_single.id = 3;
			message_single.address = MX28::P_GOAL_CURRENT;
			message_single.position = 1941;
			publisher_single->publish(message_single);
            //m_CM730->write2ByteTxRx(portHandler, 3, MX28::P_GOAL_CURRENT, 1941, &dxl_error);
			message_single.id = 4;
			message_single.address = MX28::P_GOAL_CURRENT;
			message_single.position = 1941;
			publisher_single->publish(message_single);
            //m_CM730->write2ByteTxRx(portHandler, 4, MX28::P_GOAL_CURRENT, 1941, &dxl_error);
			message_single.id = 5;
			message_single.address = MX28::P_GOAL_CURRENT;
			message_single.position = 1941;
			publisher_single->publish(message_single);
            //m_CM730->write2ByteTxRx(portHandler, 5, MX28::P_GOAL_CURRENT, 1941, &dxl_error);
			message_single.id = 6;
			message_single.address = MX28::P_GOAL_CURRENT;
			message_single.position = 1941;
			publisher_single->publish(message_single);
            //m_CM730->write2ByteTxRx(portHandler, 6, MX28::P_GOAL_CURRENT, 1941, &dxl_error);
        }
	}
	//RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "passou primeiro if");
	//printf("entrou\n");
    // if(m_fadeIn && m_torque_count < DEST_TORQUE) {
    //     m_CM730->WriteWord(CM730::ID_BROADCAST, MX28::P_TORQUE_LIMIT_L, m_torque_count, 0);
    //     m_torque_count += 2;
    // }
	// auto message = custom_interfaces::msg::SetPosition();  

    // message.id = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};          
	// message.position = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};   
	// publisher_->publish(message);
	// m_ProcessEnable == true; // TIRAR DEPOIS
	// m_IsRunning == false; // TIRAR DEPOIS
    if(MotionManager::GetInstance()->m_ProcessEnable == false || MotionManager::GetInstance()->m_IsRunning == true)
        return;
		
	MotionManager::GetInstance()->m_IsRunning = true;



	MotionManager::GetInstance()->m_CalibrationStatus = 1;
	//RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "antes do segundo if");
	// RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "%d", m_Enabled);

	// if(m_CalibrationStatus == 1 && m_Enabled == true)
    if(MotionManager::GetInstance()->m_CalibrationStatus == 1 && MotionManager::GetInstance()->GetEnable() == true)
    {
		//RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "pegando coisa da imu");

		const double GYRO_ALPHA = 0.1;
		// int gyroValFB = (int) (IMU_GYRO_Y*16);
		// int gyroValRL = (int) (IMU_GYRO_X*16);
		int gyroValFB = 1;
		int gyroValRL = 1;


		MotionStatus::FB_GYRO = (1.0 - GYRO_ALPHA) * MotionStatus::FB_GYRO + GYRO_ALPHA * gyroValFB;
		MotionStatus::RL_GYRO = (1.0 - GYRO_ALPHA) * MotionStatus::RL_GYRO + GYRO_ALPHA * gyroValRL;
		// printf("IMU 2 %f\n", MotionStatus::FB_GYRO);
		// printf("IMU %f\n", MotionStatus::RL_GYRO);
		//printf("MODULE SIZE %ld\n", m_Modules.size());
		// if(m_Modules.size() != 0)
		// {
		// 	for(std::list<MotionModule*>::iterator i = m_Modules.begin(); i != m_Modules.end(); i++)
		// 	{
		// 		(*i)->Process();
				for(int id=JointData::ID_MIN; id<=JointData::ID_MAX-2; id++)
				{
					//printf("TRUE? %d\n", (*i)->m_Joint.GetEnable(id));
					if((Walking::GetInstance())->m_Joint.GetEnable(id) == true)
					{
						MotionStatus::m_CurrentJoints.SetValue(id, (Walking::GetInstance())->m_Joint.GetValue(id));
						//printf("ACTION  %d: %d", id, (*i)->m_Joint.GetValue(id));
						MotionStatus::m_CurrentJoints.SetPGain(id, (Walking::GetInstance())->m_Joint.GetPGain(id));
						MotionStatus::m_CurrentJoints.SetIGain(id, (Walking::GetInstance())->m_Joint.GetIGain(id));
						MotionStatus::m_CurrentJoints.SetDGain(id, (Walking::GetInstance())->m_Joint.GetDGain(id));
					// MotionStatus::m_CurrentJoints.SetSlope(id, (*i)->m_Joint.GetCWSlope(id), (*i)->m_Joint.GetCCWSlope(id));
					// MotionStatus::m_CurrentJoints.SetValue(id, (*i)->m_Joint.GetValue(id));
					}
					else if((Action::GetInstance())->m_Joint.GetEnable(id) == true)
					{
						MotionStatus::m_CurrentJoints.SetValue(id, (Action::GetInstance())->m_Joint.GetValue(id));
						//printf("ACTION  %d: %d", id, (*i)->m_Joint.GetValue(id));
						MotionStatus::m_CurrentJoints.SetPGain(id, (Action::GetInstance())->m_Joint.GetPGain(id));
						MotionStatus::m_CurrentJoints.SetIGain(id, (Action::GetInstance())->m_Joint.GetIGain(id));
						MotionStatus::m_CurrentJoints.SetDGain(id, (Action::GetInstance())->m_Joint.GetDGain(id));
					// MotionStatus::m_CurrentJoints.SetSlope(id, (*i)->m_Joint.GetCWSlope(id), (*i)->m_Joint.GetCCWSlope(id));
					// MotionStatus::m_CurrentJoints.SetValue(id, (*i)->m_Joint.GetValue(id));
					}
				}
		// 	}
		// }
		auto message = custom_interfaces::msg::SetPosition();  
		int param[JointData::NUMBER_OF_JOINTS * MX28::PARAM_BYTES];
		int joint_num = 0;
		int pos[18];
		//RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "antes de pub as posicoes");
		for(int id=JointData::ID_MIN; id<=JointData::ID_MAX-2; id++) // loop que vai de 1 até 18
				{
				param[id] = id;
				pos[id] = MotionStatus::m_CurrentJoints.GetValue(id)+ MotionManager::GetInstance()->m_Offset[id];
				
				if(DEBUG_PRINT == true)
				fprintf(stderr, "ID[%d] : %d \n", id, MotionStatus::m_CurrentJoints.GetValue(id));
				}
		message.id = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};          
		message.position = {pos[1], pos[2], pos[3], pos[4], pos[5], pos[6], pos[7], pos[8], pos[9], pos[10], pos[11], pos[12], pos[13], pos[14], pos[15], pos[16], pos[17], pos[18], 2048};   
		publisher_->publish(message);

	}
	else
		RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "nao entrou no segundo if");

    MotionManager::GetInstance()->m_IsRunning = false;
    // if(m_torque_count != DEST_TORQUE && --m_torqueAdaptionCounter == 0)
    // {
    //     m_torqueAdaptionCounter = TORQUE_ADAPTION_CYCLES;
    //     adaptTorqueToVoltage();
    // }

	//rclcpp::spin_some(std::make_shared<GaitPublisher>());
	}
}

void MotionManager::SetEnable(bool enable)
{
	printf("Set enable \n");
	m_Enabled = enable;
	uint32_t valor = 1020; //declarado "0" -= velocidade infinita.
	auto message_single = custom_interfaces::msg::SetPositionOriginal(); 
	message_single.id = BROADCAST_ID;
	message_single.address = MX28::P_PROFILE_VELOCITY;
	message_single.position = valor;
	publisher_single->publish(message_single);
	// m_CM730->write4ByteTxRx(portHandler, BROADCAST_ID, MX28::P_PROFILE_VELOCITY, valor, &dxl_error);
	// if(m_Enabled == true)
	// 	m_CM730->WriteWord(CM730::ID_BROADCAST, MX28::P_MOVING_SPEED_L, 200, 0);
	// 	//m_CM730->WriteWord(1, 30, 900, 0);
}

void MotionManager::AddModule(MotionModule *module)
{
	printf("ADD MODULE \n");
	module->Initialize();
	m_Modules.push_back(module);

}

void MotionManager::RemoveModule(MotionModule *module)
{
	m_Modules.remove(module);
}

void MotionManager::SetJointDisable(int index)
{
    if(m_Modules.size() != 0)
    {
        for(std::list<MotionModule*>::iterator i = m_Modules.begin(); i != m_Modules.end(); i++)
            (*i)->m_Joint.SetEnable(index, false);
    }
}

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(Robot::MotionManager)


// void MotionManager::adaptTorqueToVoltage()
// {
// 	static int count_fail=0;
// 	static int count_volt=0;
//     const int DEST_TORQUE = 1023;
//     const int FULL_TORQUE_VOLTAGE = 210; // 13V - at 13V darwin will make no adaptation as the standard 3 cell battery is always below this voltage, this implies Nimbro-OP runs on 4 cells

//     int voltage;
// 		// torque is only reduced if it is greater then FULL_TORQUE_VOLTAGE
// 	if(m_CM730->ReadByte(7, 42, &voltage, 0) != CM730::SUCCESS && m_CM730->ReadByte(8, 42, &voltage, 0) != CM730::SUCCESS)
// 	{
//     	count_fail++;
//     	if(count_fail>=4)
//     	{
//     		printf("Falha na comunicação: Chave provavelmente desligada\n");
//     		logServo(); //Escreve no arquivo de log a hora que terminou o processo
//     		exit(0);
//     	}
//        	return;
//     }
//     count_fail=0;

//     if(voltage < 160)
//     {
//         count_volt++;
//         if(count_volt>=4)
//         {
// 		    printf("Tensão Abaixo do recomendado | Tensão = %2.1fV\n", (float)voltage/(float)10);
// 		    printf("A bateria deve ser trocada\n");
// 		    logVoltage(voltage); //Escreve no arquivo de log a tensão e a hora que terminou o processo
// 		    exit(0);
// 		}
//     }
//     else
//         count_volt=0;
//     write_int(mem, VOLTAGE, voltage);

//     if(m_CM730->ReadByte(200, CM730::P_VOLTAGE, &voltage, 0) != CM730::SUCCESS)
//         return;

//     voltage = (voltage > FULL_TORQUE_VOLTAGE) ? voltage : FULL_TORQUE_VOLTAGE;
//     m_voltageAdaptionFactor = ((double)FULL_TORQUE_VOLTAGE) / voltage;
//     int torque = m_voltageAdaptionFactor * DEST_TORQUE;

// #if LOG_VOLTAGES
//     fprintf(m_voltageLog, "%3d       %4d\n", voltage, torque);
// #endif

//     m_CM730->WriteWord(CM730::ID_BROADCAST, MX28::P_TORQUE_LIMIT_L, torque, 0);
// }

// void MotionManager::logVoltage(int voltage)
// {
//         std::fstream File;
//         time_t _tm =time(NULL);
//         struct tm * curtime = localtime ( &_tm );
//         File.open("../../Control/Control.log", std::ios::app | std::ios::out);
//         if (File.good() && File.is_open())
//         {
//             File << "Tensão Abaixo do recomendado | Tensão = "<<(float)voltage/(float)10<<"V --- ";
//             File << asctime(curtime);
//             File.flush();
//             File.close();
//         }
//         else
// 	        printf("Erro ao Salvar o arquivo\n");
// }

// void MotionManager::logServo()
// {
//         std::fstream File;
//         time_t _tm =time(NULL);
//         struct tm * curtime = localtime ( &_tm );
//         File.open("../../Control/Control.log", std::ios::app | std::ios::out);
//         if (File.good() && File.is_open())
//         {
//             File << "Falha na comunicação: Chave provavelmente desligada"<<" --- ";
//             File << asctime(curtime);
//             File.flush();
//             File.close();
//         }
//         else
// 	        printf("Erro ao Salvar o arquivo\n");
// }