/*--------------------------------------------------------------------

******************************************************************************
* @file control.cpp
* @author Isaac Jesus da Silva - ROBOFEI-HT - FEI 😛
* @version V2.2.0
* @created 20/01/2015
* @Modified 15/07/2016
* @e-mail isaac25silva@yahoo.com.br
* @brief control 😛
****************************************************************************
**************************************************************************** 
Arquivo fonte contendo o programa que controla os servos do corpo do robô
---------------------------------------------------------------------------*/

#include <unistd.h> //sleep, usleep
#include <libgen.h> //dirname
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fstream>
#include <time.h>
#include <string>

#include "minIni.h"
#include <string>

#include <chrono>
#include <memory>
#include <thread>

#include "rclcpp/rclcpp.hpp"
#include "custom_interfaces/msg/set_position.hpp"
#include "std_msgs/msg/string.hpp"

//#include "MX28.h"
#include "MotionManager.h"
#include "LinuxMotionTimer.h"
//#include "LinuxCM730.h"
//#include <blackboard.h>
#include <boost/program_options.hpp> //tratamento de argumentos linha de comando
#include "ActionMove.hpp"
#include "GaitMove.hpp"

#ifdef MX28_1024
#define MOTION_FILE_PATH    "../../Control/Data/motion_1024.bin"
#else
#define MOTION_FILE_PATH    "../../Control/Data/motion_4096.bin"
#endif

#define INI_FILE_PATH       "../../Control/Data/config.ini"

#define DEBUG_PRINT true

#define LIMITE_TEMP 80    // Define a temperatura maxima dos motores

using namespace Robot;
using namespace std;
using std::placeholders::_1;


const char* movement;
const char* last_movement;
bool same_moviment = false;
unsigned int count_read=0;
unsigned int step_time=20; // Determina a frequencia de leitura do blackboard

class ActionNode : public rclcpp::Node
{
  public:
    ActionNode()
    : Node("action_node")
    {
      subscription_ = this->create_subscription<std_msgs::msg::String>(
      "decision", 10, std::bind(&ActionNode::topic_callback, this, _1));
      publisher_ = this->create_publisher<custom_interfaces::msg::SetPosition>("set_position", 10);
    } 

    private:
    void topic_callback(const std_msgs::msg::String::SharedPtr msg) const
    {
        movement = msg->data.c_str();
        //***************************************************************************************
        //-------------------------Controle pela decisão-----------------------------------------
        logInit(); // save the time when start the control process
        while(1)
        {
                //Confere se o movimento atual e o mesmo do anterior----------
            if(movement == last_movement)
                same_moviment = true;
            else
            {
                same_moviment = false;
                std::cout<< "\nAction " << movement; // Mostra o valor da ação
                count_read=0;
            }
            //------------------------------------------------------------

            //if (read_int(mem, IMU_STATE) && !variables.count("g")){ // Ve se esta caido
            //    if(read_float(mem, IMU_ACCEL_X) > 0){  //Levanta se caido de frente
            //        actionMove.standupFront(stop_gait);
            //   }
            //    else{  //Levanta se caido de costa
            //        actionMove.standupBack(stop_gait);
            //    }
            //    stop_gait = 1;
            //    sleep(1);
            //    flag_stop = false;
            //}


            // if(read_int(mem, DECISION_ACTION_A) == 0)
            // {
            //     if(flag_stop==false)
            //         gaitMove.robot_stop(stop_gait);
            //     flag_stop = true; //variavel que indica que o robo ja estava parado, isso evita de repetir o movimento
            // }
            // else
            //     flag_stop = false;

            // if(read_int(mem, DECISION_ACTION_A) == 1)
            //     gaitMove.walk_foward_fast(stop_gait, same_moviment);

            // if(read_int(mem, DECISION_ACTION_A) == 2)
            //     gaitMove.turn_left(stop_gait, true, same_moviment);

            // if(read_int(mem, DECISION_ACTION_A) == 3)
            //     gaitMove.turn_right(stop_gait, true, same_moviment);

            // if(read_int(mem, DECISION_ACTION_A) == 4)
            //     actionMove.kick_right_strong(&cm730, stop_gait);

            // if(read_int(mem, DECISION_ACTION_A) == 5)
            //     actionMove.kick_left_strong(&cm730, stop_gait);

            // if(read_int(mem, DECISION_ACTION_A) == 6)
            //     gaitMove.sidle_left(stop_gait, same_moviment);

            // if(read_int(mem, DECISION_ACTION_A) == 7)
            //     gaitMove.sidle_right(stop_gait, same_moviment);

            // if(read_int(mem, DECISION_ACTION_A) == 8)
            //     gaitMove.walk_foward_slow(stop_gait, true, same_moviment);

            // if(read_int(mem, DECISION_ACTION_A) == 9)
            //     gaitMove.turn_around_ball_left(stop_gait, same_moviment);

            // if(read_int(mem, DECISION_ACTION_A) == 10)
            //     actionMove.goalkeeper(stop_gait);

            // if(read_int(mem, DECISION_ACTION_A) == 11)
            //     gaitMove.Gait_in_place(stop_gait, same_moviment);

            // if(read_int(mem, DECISION_ACTION_A) == 12)
            //     actionMove.pass_left(&cm730, stop_gait);

            // if(read_int(mem, DECISION_ACTION_A) == 13)
            //     actionMove.pass_right(&cm730, stop_gait);

            // if(read_int(mem, DECISION_ACTION_A) == 14)
            //     gaitMove.turn_around_ball_right(stop_gait, same_moviment);

            // if(read_int(mem, DECISION_ACTION_A) == 15)
            // {
            //     if (read_int(mem, IMU_STATE))// check if robot is fall
            //         actionMove.standupFront(stop_gait);
            //     else
            //         std::cout<<" | \e[1;31mRobô não está caido ou IMU está desligada\e[0m"<<std::endl;
            // }
            // if(read_int(mem, DECISION_ACTION_A) == 16)
            // {
            //     if (read_int(mem, IMU_STATE))// check if robot is fall
            //         actionMove.standupBack(stop_gait);
            //     else
            //         std::cout<<" | \e[1;31mRobô não está caido ou IMU está desligada\e[0m"<<std::endl;
            // }
            // if(read_int(mem, DECISION_ACTION_A) == 17)
            // {
            //     gaitMove.walk_backward_fast(stop_gait, same_moviment);
            // }
            // if(read_int(mem, DECISION_ACTION_A) == 18)
            // {
            //     gaitMove.walk_backward_slow(stop_gait, true, same_moviment);
            // }

            // if(read_int(mem, DECISION_ACTION_A) == 19)
            //     actionMove.greetings(stop_gait);

            if(movement=="goodbye")
                goodBye();

            // if(read_int(mem, DECISION_ACTION_A) == 21)
            //     actionMove.kick_right_weak(stop_gait); //Chute fraco com pe direito

            // if(read_int(mem, DECISION_ACTION_A) == 22)
            //     actionMove.kick_left_weak(stop_gait); //Chute fraco com pe esquerdo

            // // Escreve na variável de telemetria.
            // write_int(mem, CONTROL_WORKING, 1);

            //Imprime na tela o tempo que esta ocioso por nao receber uma nova instrucao da decisao-------
            count_read++;
            std::cout << "\rReading BlackBoard" <<"[\e[38;5;82m"<< count_read<<"\e[0m] | Tempo ocioso"<<"[\e[38;5;82m"<< count_read*step_time/1000<<"s\e[0m]";
            fflush (stdout);
            usleep(step_time*1000); //Operando na frequencia de 1/step_time Hertz
            //--------------------------------------------------------------------------------------------
    
            //--------------------------------------------------------------------------------------------------
            //==================================================================

            std::cout<<"Press some key to end!\n"<<std::endl;
            getchar();

        //    LinuxActionScript::ScriptStart("script.asc");
        //    while(LinuxActionScript::m_is_running == 1) sleep(10);

        }    
    }  

    void goodBye() const{
        auto message = custom_interfaces::msg::SetPosition();                               
        for (int i=1; i<=4; i++){
            message.id = {2, 4, 6};          
            message.position = {1024, 1024, 2593};   
            publisher_->publish(message);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            message.id = {2, 4, 6};          
            message.position = {1024, 1024, 3553};   
            publisher_->publish(message);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            // RCLCPP_INFO(this->get_logger(), "%d", i);
            if (i%4==0){
                break;
            }
        }
    size_t count_;
    }

    void logInit() const
    {
            std::fstream File;
            time_t _tm =time(NULL);
            struct tm * curtime = localtime ( &_tm );
            File.open("../../Control/Control.log", std::ios::app | std::ios::out);
            if (File.good() && File.is_open())
            {
                File << "Inicializando o processo do controle "<<" --- ";
                File << asctime(curtime);
                File.flush();
                File.close();
            }
            else
            printf("Erro ao Salvar o arquivo\n");
    }

    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
    rclcpp::Publisher<custom_interfaces::msg::SetPosition>::SharedPtr publisher_;  
    rclcpp::TimerBase::SharedPtr timer_;
};

int kbhit(); //Function kbhit.cpp

void sighandler(int sig)
{
    cout<< "\nProgram being closed!" << endl;
    exit(1); 
}



void change_current_dir()
{
    char exepath[1024] = {0};
    if(readlink("/proc/self/exe", exepath, sizeof(exepath)) != -1)
        chdir(dirname(exepath));
}

int main(int argc, char **argv)
{
    char string1[50]; //String
    bool stop_gait = true;
    char *Servoport;
    int value;
    int idServo;
    bool flag_stop = 0;
    unsigned int buffer = 10000;

    change_current_dir();

    minIni* ini;
    ini = new minIni((char *)INI_FILE_PATH);

    //Detecta o Ctrl+C-----------
    signal(SIGABRT, &sighandler);
    signal(SIGTERM, &sighandler);
    signal(SIGINT, &sighandler);
    //---------------------------

    //Configurando para prioridade maxima para executar este processo-------
    sprintf(string1,"echo fei 123456| sudo -S renice -20 -p %d", getpid());
    system(string1);//prioridade

    printf( "\n===== ROBOFEI-HT Control Process =====\n\n");

    //-------------para entrada de argumentos-----------------------------------
    namespace po=boost::program_options;

    po::options_description desc("options");
    desc.add_options()
    ("help", "produce help message")
    ("k", "Inicia com o controle do robô pelo teclado")
    ("v", "Verifica a tensao nos servos do corpo")
    ("t", "Verifica a temperatura dos servos do corpo")
    ("g", "Inicia o controle para usar com a interface grafica")
    ;
  
    po::variables_map variables;
    po::store(po::parse_command_line(argc, argv, desc), variables);
    po::notify(variables); 
    //--------------------------------------------------------------------------

    //    MotionManager::GetInstance()->LoadINISettings(ini);

    //Criando objeto da classe dos movimentos de caminhada----------------------
    GaitMove gaitMove(ini);
    //**************************************************************************

//    MotionManager::GetInstance()->LoadINISettings(ini);
//    Walking::GetInstance()->LoadINISettings(ini); 
//    MotionManager::GetInstance()->AddModule((MotionModule*)Action::GetInstance());
//    MotionManager::GetInstance()->AddModule((MotionModule*)Walking::GetInstance());
    LinuxMotionTimer linuxMotionTimer;
    linuxMotionTimer.Initialize(MotionManager::GetInstance());
    linuxMotionTimer.Start();
    /////////////////////////////////////////////////////////////////////

    //actionMove.poseStandup(stop_gait); /* Init(stand up) pose */
    //movement = 'pose_stand_up';

    //====== Reset the IMU ==========
    //sleep(2);
    //write_int(mem, IMU_RESET, 1);
    //sleep(1);
    //int k=0;

    //if (!variables.count("k")) //verifica se foi chamado o argumento de controle pelo teclado
    //{
    //    //====== Reset the IMU ==========
    //    while(read_float(mem, IMU_EULER_Z) > 0.0005 || read_float(mem, IMU_EULER_Z) < -0.0005)
    //    {
    //        sleep(2);
    //        write_int(mem, IMU_RESET, 1);
    //        cout<<"Reseting IMU"<<endl;
    //        sleep(1);
    //        if (k>4)
    //        {
    //            cout<<"Error: reset IMU failed"<<endl;
    //            break;
    //        }
    //        k++;
    //    }
    //}
    //===============================

  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ActionNode>());
  rclcpp::shutdown();
  return 0;
}
