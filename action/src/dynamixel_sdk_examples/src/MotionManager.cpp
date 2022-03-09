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

using namespace Robot;

// Torque adaption every second
const int TORQUE_ADAPTION_CYCLES = 1000 / MotionModule::TIME_UNIT;
const int DEST_TORQUE = 1023;

//#define LOG_VOLTAGES 1

MotionManager* MotionManager::m_UniqueInstance = new MotionManager();

MotionManager::MotionManager() :
        m_ProcessEnable(false),
        m_Enabled(false),
        m_IsRunning(false),
        m_IsThreadRunning(false),
        m_IsLogging(false),
				m_torqueAdaptionCounter(TORQUE_ADAPTION_CYCLES),
				m_voltageAdaptionFactor(1.0),
        DEBUG_PRINT(false)
{
    for(int i = 0; i < JointData::NUMBER_OF_JOINTS; i++)
        m_Offset[i] = 0;

#if LOG_VOLTAGES
    assert((m_voltageLog = fopen("voltage.log", "w")));
    fprintf(m_voltageLog, "Voltage   Torque\n");
#endif
}

MotionManager::~MotionManager()
{
}

bool MotionManager::Initialize(bool fadeIn)
{
	int value, error;

	usleep(10000);
	m_Enabled = false;
	m_ProcessEnable = true;

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

	int value, error;

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
        if((ivalue = ini->geti(section, key, INVALID_VALUE)) != INVALID_VALUE)  m_Offset[i] = ivalue;
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
	//printf("entrou\n");
    if(m_fadeIn && m_torque_count < DEST_TORQUE) {
		while(P_TORQUE_LIMIT_L<=34){
			message.id = {ID_BROADCAST};          
			message.position = {m_torque_count};
			publisher_->publish(message);
			m_torque_count += 2;
		}
    }

    if(m_ProcessEnable == false || m_IsRunning == true)
        return;
		
		m_IsRunning = true;



        m_CalibrationStatus = 1;


    if(m_CalibrationStatus == 1 && m_Enabled == true)
    {

          const double GYRO_ALPHA = 0.1;
          int gyroValFB = (int) (read_int(mem, IMU_GYRO_Y)*16);
          int gyroValRL = (int) (-read_int(mem, IMU_GYRO_X)*16);

          MotionStatus::FB_GYRO = (1.0 - GYRO_ALPHA) * MotionStatus::FB_GYRO + GYRO_ALPHA * gyroValFB;
          MotionStatus::RL_GYRO = (1.0 - GYRO_ALPHA) * MotionStatus::RL_GYRO + GYRO_ALPHA * gyroValRL;

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
	for(int id=JointData::ID_MIN; id<=JointData::ID_MAX-2; id++)
	{
		if(MotionStatus::m_CurrentJoints.GetEnable(id) == true)
		{
		param[n++] = id;
		param[n++] = MotionStatus::m_CurrentJoints.GetCWSlope(id);
		param[n++] = MotionStatus::m_CurrentJoints.GetCCWSlope(id);
		param[n++] = GetLowByte(MotionStatus::m_CurrentJoints.GetValue(id) + m_Offset[id]);
		param[n++] = GetHighByte(MotionStatus::m_CurrentJoints.GetValue(id) + m_Offset[id]);
		message.id[n++] = id;          
        message.position[n++] = GetHighByte(MotionStatus::m_CurrentJoints.GetValue(id) + m_Offset[id]);
		joint_num++;
		if(joint_num > 0)
			publisher_->publish(message[n++]);
		}
		if(DEBUG_PRINT == true)
		fprintf(stderr, "ID[%d] : %d \n", id, MotionStatus::m_CurrentJoints.GetValue(id));
	}
	//if(joint_num > 0)
	//publisher_sync->publish(message);

	}
		

    m_IsRunning = false;

    if(m_torque_count != DEST_TORQUE && --m_torqueAdaptionCounter == 0)
    {
        m_torqueAdaptionCounter = TORQUE_ADAPTION_CYCLES;
        adaptTorqueToVoltage();
    }
}

int GetLowByte(int word)
{
	unsigned short temp;
    temp = word & 0xff;
    return (int)temp;
}

int GetHighByte(int word)
{
	unsigned short temp;
    temp = word & 0xff00;
    return (int)(temp >> 8);
}

void MotionManager::SetEnable(bool enable)
{
	//printf("entrou\n");
	m_Enabled = enable;
}

void MotionManager::AddModule(MotionModule *module)
{
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

void MotionManager::adaptTorqueToVoltage()
{
	static int count_fail=0;
	static int count_volt=0;
    const int DEST_TORQUE = 1023;
    const int FULL_TORQUE_VOLTAGE = 210; // 13V - at 13V darwin will make no adaptation as the standard 3 cell battery is always below this voltage, this implies Nimbro-OP runs on 4 cells

    int voltage;
		// torque is only reduced if it is greater then FULL_TORQUE_VOLTAGE
    count_fail=0;

    if(voltage < 160)
    {
        count_volt++;
        if(count_volt>=4)
        {
		    printf("Tensão Abaixo do recomendado | Tensão = %2.1fV\n", (float)voltage/(float)10);
		    printf("A bateria deve ser trocada\n");
		    logVoltage(voltage); //Escreve no arquivo de log a tensão e a hora que terminou o processo
		    exit(0);
		}
    }
    else
        count_volt=0;

    voltage = (voltage > FULL_TORQUE_VOLTAGE) ? voltage : FULL_TORQUE_VOLTAGE;
    m_voltageAdaptionFactor = ((double)FULL_TORQUE_VOLTAGE) / voltage;
    int torque = m_voltageAdaptionFactor * DEST_TORQUE;

#if LOG_VOLTAGES
    fprintf(m_voltageLog, "%3d       %4d\n", voltage, torque);
#endif

	while(P_TORQUE_LIMIT_L<=34){
			message.id = {ID_BROADCAST};          
			message.position = {torque};
			publisher_->publish(message);
		}
}

void MotionManager::logVoltage(int voltage)
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

void MotionManager::logServo()
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
