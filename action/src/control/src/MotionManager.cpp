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
#include <chrono>
#include <memory>
#include <thread>
#include <functional>

#include "rclcpp/rclcpp.hpp"
#include "custom_interfaces/msg/set_position.hpp"
#include "custom_interfaces/msg/decision.hpp"

#include <stdio.h>
#include <math.h>
#include "FSR.h"
#include "MX28.h"
#include "MotionManager.h"
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <fstream>
#include <time.h>


// Torque adaption every second
const int TORQUE_ADAPTION_CYCLES = 1000 / MotionModule::TIME_UNIT;
const int DEST_TORQUE = 1023;

//#define LOG_VOLTAGES 1

#define GYRO_WINDOW_SIZE    100
#define ACCEL_WINDOW_SIZE   30
#define MARGIN_OF_SD        2.0

MotionManager::MotionManager()
: Node("motion")
{
  RCLCPP_INFO(this->get_logger(), "Running motion manager");

  this->declare_parameter("qos_depth", 10);
  int8_t qos_depth = 0;
  this->get_parameter("qos_depth", qos_depth);

  const auto QOS_RKL10V =
    rclcpp::QoS(rclcpp::KeepLast(qos_depth)).reliable().durability_volatile();
  
  publisher_ =
    this->create_publisher<SetPosition>(
    "set_position",
    QOS_RKL10V,
    [this](const std::shared_ptr<SetPosition> msg) -> void 
    {
      if(m_ProcessEnable == false || m_IsRunning == true)
            return;
            
            m_IsRunning = true;

            m_CalibrationStatus = 1;


        if(m_CalibrationStatus == 1 && m_Enabled == true)
        {

            const double GYRO_ALPHA = 0.1;
            //   int gyroValFB = (int) (read_int(mem, IMU_GYRO_Y)*16);
            //   int gyroValRL = (int) (-read_int(mem, IMU_GYRO_X)*16);


    //          const double GYRO_ALPHA = 0.1;
    //          int gyroValFB = m_CM730->m_BulkReadData[CM730::ID_CM].ReadWord(CM730::P_GYRO_Y_L) - m_FBGyroCenter;
    //          int gyroValRL = m_CM730->m_BulkReadData[CM730::ID_CM].ReadWord(CM730::P_GYRO_X_L) - m_RLGyroCenter;

    //          MotionStatus::FB_GYRO = (1.0 - GYRO_ALPHA) * MotionStatus::FB_GYRO + GYRO_ALPHA * gyroValFB;
    //          MotionStatus::RL_GYRO = (1.0 - GYRO_ALPHA) * MotionStatus::RL_GYRO + GYRO_ALPHA * gyroValRL;;
    //          MotionStatus::RL_ACCEL = m_CM730->m_BulkReadData[CM730::ID_CM].ReadWord(CM730::P_ACCEL_X_L);
    //          MotionStatus::FB_ACCEL = m_CM730->m_BulkReadData[CM730::ID_CM].ReadWord(CM730::P_ACCEL_Y_L);


    //        MotionStatus::FB_GYRO = (1.0 - GYRO_ALPHA) * MotionStatus::FB_GYRO + GYRO_ALPHA * gyroValFB;
    //        MotionStatus::RL_GYRO = (1.0 - GYRO_ALPHA) * MotionStatus::RL_GYRO + GYRO_ALPHA * gyroValRL;


    //           m_angleEstimator.update(
    //               (m_CM730->m_BulkReadData[CM730::ID_CM].ReadWord(CM730::P_ACCEL_X_L) - 512),
    //               (m_CM730->m_BulkReadData[CM730::ID_CM].ReadWord(CM730::P_ACCEL_Y_L) - 512),
    //               (m_CM730->m_BulkReadData[CM730::ID_CM].ReadWord(CM730::P_ACCEL_Z_L) - 512)
    //           );

    //           MotionStatus::ANGLE_PITCH = m_angleEstimator.pitch();
    //           MotionStatus::ANGLE_ROLL  = m_angleEstimator.roll();
    //					}

    //        int sum = 0, avr = 512;
    //        for(int idx = 0; idx < ACCEL_WINDOW_SIZE; idx++)
    //            sum += fb_array[idx];
    //        avr = sum / ACCEL_WINDOW_SIZE;

    //        if(avr < MotionStatus::FALLEN_F_LIMIT)
    //            MotionStatus::FALLEN = FORWARD;
    //        else if(avr > MotionStatus::FALLEN_B_LIMIT)
    //            MotionStatus::FALLEN = BACKWARD;
    //        else
    //            MotionStatus::FALLEN = STANDUP;


        if(m_Modules.size() != 0)
        {
            for(std::list<MotionModule*>::iterator i = m_Modules.begin(); i != m_Modules.end(); i++)
            {
                (*i)->Process();
                for(int id=JointData::ID_MIN; id<=JointData::ID_MAX-2; id++)
                {
                    if((*i)->m_Joint.GetEnable(id) == true)
                    {
                    MotionStatus::m_CurrentJoints.SetSlope(id, (*i)->m_Joint.GetCWSlope(id), (*i)->m_Joint.GetCCWSlope(id));
                    MotionStatus::m_CurrentJoints.SetValue(id, (*i)->m_Joint.GetValue(id));
                    // MotionStatus::m_CurrentJoints.SetPGain(id, (*i)->m_Joint.GetPGain(id));
                    // MotionStatus::m_CurrentJoints.SetIGain(id, (*i)->m_Joint.GetIGain(id));
                    // MotionStatus::m_CurrentJoints.SetDGain(id, (*i)->m_Joint.GetDGain(id));
                    }
                }
            }
        }
        int param[JointData::NUMBER_OF_JOINTS * MX28::PARAM_BYTES];
        int n = 0;
        int joint_num = 0;
        auto message = custom_interfaces::msg::SetPosition();   
        int ids[];
        int pos[];
        int cont = 0;
        for(int id=JointData::ID_MIN; id<=JointData::ID_MAX-2; id++)
        {
            ids[cont] = id;
            pos[cont] = MotionStatus::m_CurrentJoints.GetValue(id) + m_Offset[id];
            // param[n++] = id;
            // param[n++] = MotionStatus::m_CurrentJoints.GetCWSlope(id);
            // param[n++] = MotionStatus::m_CurrentJoints.GetCCWSlope(id);
            // param[n++] = CM730::GetLowByte(MotionStatus::m_CurrentJoints.GetValue(id) + m_Offset[id]);
            // param[n++] = CM730::GetHighByte(MotionStatus::m_CurrentJoints.GetValue(id) + m_Offset[id]);
            // joint_num++;
            cont++;
            if(DEBUG_PRINT == true)
            fprintf(stderr, "ID[%d] : %d \n", id, MotionStatus::m_CurrentJoints.GetValue(id));
        }
        //if(joint_num > 0)
        //m_CM730->SyncWrite(MX28::P_CW_COMPLIANCE_SLOPE, MX28::PARAM_BYTES, joint_num, param);
        message.id = {ids[0], ids[1], ids[2], ids[3], ids[4], ids[5], ids[6], ids[7], ids[8], ids[9], ids[10], ids[11], ids[12], ids[13], ids[14], ids[15], ids[16], ids[17]};          
        message.position = {pos[0], pos[1], pos[2], pos[3], pos[4], pos[5], pos[6], pos[7], pos[8], pos[9], pos[10], pos[11], pos[12], pos[13], pos[14], pos[15], pos[16], pos[17]}; 
        publisher_->publish(message); 

        m_IsRunning = false;

        // if(m_torque_count != DEST_TORQUE && --m_torqueAdaptionCounter == 0)
        // {
        //     m_torqueAdaptionCounter = TORQUE_ADAPTION_CYCLES;
        //     adaptTorqueToVoltage();
        // }
        }
    }
    );
}

MotionManager::~MotionManager()
{
}

bool Initialize(bool fadeIn)
{
    int value, error;

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

    // for(int id=JointData::ID_MIN; id<=JointData::ID_MAX-2; id++) //diminui tirando a cabeça
    // {
    // 	if(DEBUG_PRINT == true)
    // 		fprintf(stderr, "ID:%d initializing...", id);
        
    // 	if(m_CM730->ReadWord(id, MX28::P_PRESENT_POSITION_L, &value, &error) == CM730::SUCCESS)
    // 	{
    // 		MotionStatus::m_CurrentJoints.SetValue(id, value);
    // 		MotionStatus::m_CurrentJoints.SetEnable(id, true);

    // 		if(DEBUG_PRINT == true)
    // 			fprintf(stderr, "[%d] Success\n", value);
    // 	}
    // 	else
    // 	{
    // 		MotionStatus::m_CurrentJoints.SetEnable(id, false);

    // 		if(DEBUG_PRINT == true)
    // 			fprintf(stderr, " Fail\n");
    // 	}
    // }

    // if(fadeIn)
    // {
    // 	//for(int i=JointData::ID_R_SHOULDER_PITCH; i<JointData::NUMBER_OF_JOINTS; i++)
    // 		//cm730->WriteWord(i, MX28::P_TORQUE_LIMIT_L, 0, 0);
    // }

    m_fadeIn = fadeIn;
    m_torque_count = 0;

    m_CalibrationStatus = 0;
    m_FBGyroCenter = 512;
    m_RLGyroCenter = 512;

    return true;
}

bool Reinitialize()
{
    m_ProcessEnable = false;

    //m_CM730->DXLPowerOn();

    int value, error;
    // for(int id=JointData::ID_MIN; id<=JointData::ID_MAX-2; id++)//tirando a cabeça
    // {
    // 	if(DEBUG_PRINT == true)
    // 		fprintf(stderr, "ID:%d initializing...", id);
        
    // 	if(m_CM730->ReadWord(id, MX28::P_PRESENT_POSITION_L, &value, &error) == CM730::SUCCESS)
    // 	{
    // 		MotionStatus::m_CurrentJoints.SetValue(id, value);
    // 		MotionStatus::m_CurrentJoints.SetEnable(id, true);

    // 		if(DEBUG_PRINT == true)
    // 			fprintf(stderr, "[%d] Success\n", value);
    // 	}
    // 	else
    // 	{
    // 		MotionStatus::m_CurrentJoints.SetEnable(id, false);

    // 		if(DEBUG_PRINT == true)
    // 			fprintf(stderr, " Fail\n");
    // 	}
    // }

    m_ProcessEnable = true;
    return true;
}

void Restartrobot()
{
    m_torque_count=0;
}

void StartLogging()
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

void StopLogging()
{
    m_IsLogging = false;
    m_LogFileStream.close();
}

void LoadINISettings(minIni* ini)
{
    LoadINISettings(ini, OFFSET_SECTION);
}
void LoadINISettings(minIni* ini, const std::string &section)
{
    int ivalue = INVALID_VALUE;

    for(int i = JointData::ID_MIN; i <= JointData::ID_MAX-2; i++)//tirando a cabeça
    {
        char key[10];
        sprintf(key, "ID_%.2d", i);
        if((ivalue = ini->geti(section, key, INVALID_VALUE)) != INVALID_VALUE)  m_Offset[i] = ivalue;
    }
        m_angleEstimator.LoadINISettings(ini, section + "_angle");
}
void SaveINISettings(minIni* ini)
{
    SaveINISettings(ini, OFFSET_SECTION);
}
void SaveINISettings(minIni* ini, const std::string &section)
{
    for(int i = JointData::ID_MIN; i <= JointData::ID_MAX-2; i++)//tirando a cabeça
    {
        char key[10];
        sprintf(key, "ID_%.2d", i);
        ini->put(section, key, m_Offset[i]);
    }
        m_angleEstimator.SaveINISettings(ini, section + "_angle");
}

    // void MotionManager::SetEnable(bool enable)
// {
// 	//printf("entrou\n");
// 	m_Enabled = enable;
// 	if(m_Enabled == true)
// 		m_CM730->WriteWord(CM730::ID_BROADCAST, MX28::P_MOVING_SPEED_L, 200, 0);
// 		//m_CM730->WriteWord(1, 30, 900, 0);
// }

void AddModule(MotionModule *module)
{
    module->Initialize();
    m_Modules.push_back(module);

}


void RemoveModule(MotionModule *module)
{
    m_Modules.remove(module);
}

void SetJointDisable(int index)
{
    if(m_Modules.size() != 0)
    {
        for(std::list<MotionModule*>::iterator i = m_Modules.begin(); i != m_Modules.end(); i++)
            (*i)->m_Joint.SetEnable(index, false);
    }
}

// void MotionManager::adaptTorqueToVoltage()
// {
// 	static int count_fail=0;
// 	static int count_volt=0;
//     const int DEST_TORQUE = 1023;
//     const int FULL_TORQUE_VOLTAGE = 210; // 13V - at 13V darwin will make no adaptation as the standard 3 cell battery is always below this voltage, this implies Nimbro-OP runs on 4 cells

//     int voltage;
// 		// torque is only reduced if it is greater then FULL_TORQUE_VOLTAGE
// 	// if(m_CM730->ReadByte(7, 42, &voltage, 0) != CM730::SUCCESS && m_CM730->ReadByte(8, 42, &voltage, 0) != CM730::SUCCESS)
// 	// {
//     // 	count_fail++;
//     // 	if(count_fail>=4)
//     // 	{
//     // 		printf("Falha na comunicação: Chave provavelmente desligada\n");
//     // 		logServo(); //Escreve no arquivo de log a hora que terminou o processo
//     // 		exit(0);
//     // 	}
//     //    	return;
//     // }
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

void logVoltage(int voltage)
{
    std::fstream File;
    time_t _tm =time(NULL);
    struct tm * curtime = localtime ( &_tm );
    File.open("../../Control/Control.log", std::ios::app | std::ios::out);
    if (File.good() && File.is_open())
    {
        File << "Tensão Abaixo do recomendado | Tensão = "<<(float)voltage/(float)10<<"V --- ";
        File << asctime(curtime);
        File.flush();
        File.close();
    }
    else
        printf("Erro ao Salvar o arquivo\n");
}

void logServo()
{
    std::fstream File;
    time_t _tm =time(NULL);
    struct tm * curtime = localtime ( &_tm );
    File.open("../../Control/Control.log", std::ios::app | std::ios::out);
    if (File.good() && File.is_open())
    {
        File << "Falha na comunicação: Chave provavelmente desligada"<<" --- ";
        File << asctime(curtime);
        File.flush();
        File.close();
    }
    else
        printf("Erro ao Salvar o arquivo\n");
}


int main(int argc, char * argv[])
{
  
    bool m_ProcessEnable = false;
    bool m_Enabled = false;
    bool m_IsRunning = false;
    bool m_IsThreadRunning = false;
    bool m_IsLogging = false;
	int m_torqueAdaptionCounter = TORQUE_ADAPTION_CYCLES;
	double m_voltageAdaptionFactor = 1.0;
    bool DEBUG_PRINT = false;
{
    for(int i = 0; i < JointData::NUMBER_OF_JOINTS; i++)
        m_Offset[i] = 0;

#if LOG_VOLTAGES
    assert((m_voltageLog = fopen("voltage.log", "w")));
    fprintf(m_voltageLog, "Voltage   Torque\n");
#endif
}

  rclcpp::init(argc, argv);

  auto motion_manager = std::make_shared<MotionManager>();
  rclcpp::spin(motion_manager);
  rclcpp::shutdown();

  return 0;
}