#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
//#include <ncurses.h>
#include <curses.h>
#include <signal.h>
#include <string.h>
#include <libgen.h>
#include "MotionManager.h"
#include "minIni.h"
#include <stdlib.h>     /* system, NULL, EXIT_FAILURE */
#include <chrono>
#include <functional>
#include <memory>
#include <term.h>
#include <termios.h>
#include "cmd_process.h"
#include "JointData.h"
#include "Action.h"
#include "MX28.h"
#include "rclcpp/rclcpp.hpp"
#include "dynamixel_sdk_custom_interfaces/msg/set_position.hpp"
#include "dynamixel_sdk_custom_interfaces/msg/set_position_original.hpp"


#define MOTION_FILE_PATH    "/home/robo/ROS2/walk_test/src/control/Data/motion_4096.bin"

#define INI_FILE_PATH       "/home/robo/ROS2/walk_test/src/control/Data/config.ini"


using namespace Robot;
using namespace std::chrono_literals;

const std::string azul = "\e[0;36m";
const std::string azulE = "\e[0;34m";
const std::string amare = "\e[0;33m";
const std::string verde = "\e[0;32m";
const std::string red = "\e[0;31m";
const std::string gray = "\e[0;37m";
const std::string nulo = "\e[0m";

const std::string Lazul = "\e[96m";
const std::string LazulE = "\e[94m";
const std::string Lamare = "\e[93m";
const std::string Lverde = "\e[92m";
const std::string Lred = "\e[91m";
const std::string Lgray = "\e[97m";

int Col = STP7_COL;
int Row = ID_1_ROW;
int Old_Col;
int Old_Row;
bool bBeginCommandMode = false;
bool bEdited = false;
int indexPage = 1;
int indexPageBuffer = 1;
Action::PAGE Page;
Action::STEP Step;
int ch;

uint8_t dxl_error;

// void teste(){
// 	printf("FUNCAO TESTE\n");
// }

MinimalPublisher::MinimalPublisher()
    : Node("action_editor")
    {
        publisher_ = this->create_publisher<dynamixel_sdk_custom_interfaces::msg::SetPosition>("set_position", 10); 
        publisher_single = this->create_publisher<dynamixel_sdk_custom_interfaces::msg::SetPositionOriginal>("set_position_single", 10); 
      timer_ = this->create_wall_timer(
      8ms, std::bind(&MinimalPublisher::process, this));
    }

int MinimalPublisher::process()
{
        ch = _getch();

        if(ch == 0x1b)
        {
            ch = _getch();
            if(ch == 0x5b)
            {
                ch = _getch();
                if(ch == 0x41)      // Up arrow key
                    MoveUpCursor();
                else if(ch == 0x42) // Down arrow key
                    MoveDownCursor();
                else if(ch == 0x44) // Left arrow key
                    MoveLeftCursor();
                else if(ch == 0x43) // Right arrow key
                    MoveRightCursor();
            }
        }
        else if( ch == '[' )
            UpDownValue(-1);
        else if( ch == ']' )
            UpDownValue(1);
        else if( ch == '{' )
            UpDownValue(-10);
        else if( ch == '}' )
            UpDownValue(10);
        else if( ch == ' ' )
            ToggleTorque();
        else if( ch >= 'A' && ch <= 'z' )
        {
            char input[128] = {0,};
            char *token;
            int input_len;
            char cmd[80];
            int num_param;
            int iparam[30];

            int idx = 0;

            BeginCommandMode();

            printf("%c", ch);
            input[idx++] = (char)ch;

            while(1)
            {
                ch = _getch();
                if( ch == 0x0A )
                    break;
                else if( ch == 0x7F )
                {
                    if(idx > 0)
                    {
                        ch = 0x08;
                        printf("%c", ch);
                        ch = ' ';
                        printf("%c", ch);
                        ch = 0x08;
                        printf("%c", ch);
                        input[--idx] = 0;
                    }
                }
                else if( ( ch >= 'A' && ch <= 'z' ) || ch == ' ' || ch == '-' || ( ch >= '0' && ch <= '9'))
                {
                    if(idx < 127)
                    {
                        printf("%c", ch);
                        input[idx++] = (char)ch;
                    }
                }
            }

            fflush(stdin);
            input_len = strlen(input);
            if(input_len > 0)
            {
                token = strtok( input, " " );
                if(token != 0)
                {
                    strcpy( cmd, token );
                    token = strtok( 0, " " );
                    num_param = 0;
                    while(token != 0)
                    {
                        iparam[num_param++] = atoi(token);
                        token = strtok( 0, " " );
                    }

                    if(strcmp(cmd, "exit") == 0)
                    {
                        if(AskSave() == false)
                            rclcpp::shutdown();
                    }
                    else if(strcmp(cmd, "re") == 0)
                        DrawPage();
                    else if(strcmp(cmd, "help") == 0)

                        HelpCmd();
                    else if(strcmp(cmd, "n") == 0)
                        NextCmd();
                    else if(strcmp(cmd, "b") == 0)
                        PrevCmd();						
                    else if(strcmp(cmd, "time") == 0)
                        TimeCmd();
                    else if(strcmp(cmd, "speed") == 0)
                        SpeedCmd();
                    else if(strcmp(cmd, "page") == 0)
                    {
                        if(num_param > 0)
                            PageCmd(iparam[0]);
                        else
                            PrintCmd("Need parameter");
                    }
                    else if(strcmp(cmd, "play") == 0)
                    {
                        PlayCmd();
                    }
                    else if(strcmp(cmd, "set") == 0)
                    {
                        if(num_param > -900)
                            SetValue(iparam[0]);
                        else
                            PrintCmd("Need parameter");
                    }
                    else if(strcmp(cmd, "list") == 0)
                        ListCmd();
                    else if(strcmp(cmd, "on") == 0)
                        OnOffCmd(true, num_param, iparam);
                    else if(strcmp(cmd, "off") == 0)
                        OnOffCmd(false, num_param, iparam);
                    else if(strcmp(cmd, "w") == 0)
                    {
                        if(num_param > 0)
                            WriteStepCmd(iparam[0]);
                        else
                            PrintCmd("Need parameter");
                    }
                    else if(strcmp(cmd, "d") == 0)
                    {
                        if(num_param > 0)
                            DeleteStepCmd(iparam[0]);
                        else
                            PrintCmd("Need parameter");
                    }
                    else if(strcmp(cmd, "i") == 0)
                    {
                        if(num_param == 0)
                            InsertStepCmd(0);
                        else
                            InsertStepCmd(iparam[0]);
                    }
                    else if(strcmp(cmd, "m") == 0)
                    {
                        if(num_param > 1)
                            MoveStepCmd(iparam[0], iparam[1]);
                        else
                            PrintCmd("Need parameter");
                    }
                    else if(strcmp(cmd, "copy") == 0)
                    {
                        if(num_param > 0)
                            CopyCmd(iparam[0]);
                        else
                            PrintCmd("Need parameter");
                    }
                    else if(strcmp(cmd, "new") == 0)
                        NewCmd();
                    else if(strcmp(cmd, "g") == 0)
                    {
                        if(num_param > 0)
                            GoCmd(iparam[0]);
                        else
                            PrintCmd("Need parameter");
                    }
                    else if(strcmp(cmd, "save") == 0)
                        SaveCmd();
                    else if(strcmp(cmd, "name") == 0)
                        NameCmd();
                    else if(strcmp(cmd, "t") == 0)
					{
						goInitPage();
						PlayCmd();
						backToPage();
					}
                    else if(strcmp(cmd, "read") == 0)
						readServo();
					else
                        PrintCmd("Bad command! please input 'help'");
                }
            }

            EndCommandMode();
        }

        return 0;
    }

int MinimalPublisher::_getch()
{
	struct termios oldt, newt;
	int ch;
	tcgetattr( STDIN_FILENO, &oldt );
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr( STDIN_FILENO, TCSANOW, &newt );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
	return ch;
}

int MinimalPublisher::kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}

struct termios oldterm, new_term;
void MinimalPublisher::set_stdin(void)
{
	tcgetattr(0,&oldterm);
	new_term = oldterm;
	new_term.c_lflag &= ~(ICANON | ECHO | ISIG); // �ǹ̴� struct termios�� ã���� ��.
	new_term.c_cc[VMIN] = 1;
	new_term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &new_term);
}

void MinimalPublisher::reset_stdin(void)
{
	tcsetattr(0, TCSANOW, &oldterm);
}

// // void ReadStep(CM730 *cm730)
void MinimalPublisher::ReadStep()
{
	uint8_t value8;
	uint32_t value32;
	dxl_error = 0;

	// for(int id=0; id<31; id++)
	// {
	// 	if(id >= JointData::ID_MIN && id <= JointData::ID_MAX)
	// 	{
	// 		// if(cm730->ReadByte(id, MX28::P_TORQUE_ENABLE, &value, 0) == CM730::SUCCESS)
	// 		// if(packetHandler->read1ByteTxRx(portHandler, id, MX28::P_TORQUE_ENABLE, &value8, &dxl_error) == COMM_SUCCESS)
	// 		// {
	// 		// 	if(value8 == 1)
	// 		// 	{
	// 				// if(cm730->ReadWord(id, MX28::P_GOAL_POSITION_L, &value, 0) == CM730::SUCCESS)
	// 				// if(packetHandler->read4ByteTxRx(portHandler, id, MX28::P_GOAL_POSITION, &value32, &dxl_error) == COMM_SUCCESS)
	// 					Step.position[id] = value32 - MotionManager::GetInstance()->m_Offset[id];
	// 		// 		else
	// 		// 			Step.position[id] = Action::INVALID_BIT_MASK;
	// 		// 	}
	// 		// 	else
	// 		// 		Step.position[id] = Action::TORQUE_OFF_BIT_MASK;
	// 		// }
	// 		// else
	// 		// 	Step.position[id] = Action::INVALID_BIT_MASK;
	// 	}
	// 	else
	// 		Step.position[id] = Action::INVALID_BIT_MASK;
	// }
}


bool MinimalPublisher::AskSave()
{
	if(bEdited == true)
	{
		PrintCmd("Are you sure? (y/n)");
		if(_getch() != 'y')
		{
			ClearCmd();
			return true;
		}
	}

	return false;
}


void MinimalPublisher::GoToCursor(int col, int row)
{
	char *cursor;
	char *esc_sequence;
	cursor = tigetstr("cup");
	esc_sequence = tparm(cursor, row, col);
	putp(esc_sequence);

	Col = col;
	Row = row;
}

void MinimalPublisher::MoveUpCursor()
{
	if(Col >= STP7_COL && Col <= CCWSLOPE_COL)
	{
		if( Row > ID_1_ROW )
			GoToCursor(Col, Row-1);
	}
	else
	{
		if( Row > PLAYCOUNT_ROW )
			GoToCursor(Col, Row-1);
	}
}

void MinimalPublisher::MoveDownCursor()
{
	if(Col >= STP7_COL && Col <= STP6_COL)
	{
		if( Row < SPEED_ROW )
			GoToCursor(Col, Row+1);
	}
	else if(Col <= CCWSLOPE_COL)
	{
		if( Row < ID_20_ROW )
			GoToCursor(Col, Row+1);
	}
	else
	{
		if( Row < EXIT_ROW )
			GoToCursor(Col, Row+1);
	}
}

void MinimalPublisher::MoveLeftCursor()
{
	switch(Col)
	{
	case STP0_COL:
		GoToCursor(STP7_COL, Row);
		break;

	case STP1_COL:
		GoToCursor(STP0_COL, Row);
		break;

	case STP2_COL:
		GoToCursor(STP1_COL, Row);
		break;

	case STP3_COL:
		GoToCursor(STP2_COL, Row);
		break;

	case STP4_COL:
		GoToCursor(STP3_COL, Row);
		break;

	case STP5_COL:
		GoToCursor(STP4_COL, Row);
		break;

	case STP6_COL:
		GoToCursor(STP5_COL, Row);
		break;

	case CWSLOPE_COL:
		GoToCursor(STP6_COL, Row);
		break;

	case CCWSLOPE_COL:
		GoToCursor(CWSLOPE_COL, Row);
		break;

	case PAGEPARAM_COL:
		GoToCursor(CCWSLOPE_COL, Row);
		break;
	}
}

void MinimalPublisher::MoveRightCursor()
{
	switch(Col)
	{
	case STP7_COL:
		GoToCursor(STP0_COL, Row);
		break;

	case STP0_COL:
		GoToCursor(STP1_COL, Row);
		break;

	case STP1_COL:
		GoToCursor(STP2_COL, Row);
		break;

	case STP2_COL:
		GoToCursor(STP3_COL, Row);
		break;

	case STP3_COL:
		GoToCursor(STP4_COL, Row);
		break;

	case STP4_COL:
		GoToCursor(STP5_COL, Row);
		break;

	case STP5_COL:
		GoToCursor(STP6_COL, Row);
		break;

	case STP6_COL:
		GoToCursor(CWSLOPE_COL, Row);
		break;

	case CWSLOPE_COL:
		GoToCursor(CCWSLOPE_COL, Row);
		break;

	case CCWSLOPE_COL:
		if(Row >= PLAYCOUNT_ROW && Row <= EXIT_ROW)
			GoToCursor(PAGEPARAM_COL, Row);
		break;
	}
}

// // void DrawIntro(CM730 *cm730)
void MinimalPublisher::DrawIntro()
{
	int nrows, ncolumns;
    setupterm(NULL, fileno(stdout), (int *)0);
    nrows = tigetnum("lines");
    ncolumns = tigetnum("cols");

	system("clear");
	printf("\n");
	std::cout<<"---------------- "<<Lazul<<"RoboFEI-HT Robot Teen"<<nulo<<" ---------------------";
	printf("\n\n");
	printf(" *Terminal screen size must be %d(col)x%d(row).\n", SCREEN_COL+2, SCREEN_ROW);
  printf(" *Current terminal has %d columns and %d rows.\n", ncolumns, nrows);
	printf("\n");
	printf("\n");
	printf("Press any key to start program...\n");
	_getch();

	system("printf '\e[8;27;80t'");

	// Action::GetInstance()->LoadPage(indexPage, &Page);

	ReadStep();
	Step.pause = 0;
	Step.time = 0; 

	DrawPage();
}

void MinimalPublisher::DrawEnding()
{
	system("clear");
	printf("\n");
	printf("Terminate Action Editor");
	printf("\n");
}

void MinimalPublisher::DrawPage()
{
	int old_col = Col;
	int old_row = Row;

	system("clear");
	// 80    01234567890123456789012345678901234567890123456789012345678901234567890123456789     //24
	printf( "ID: 1(R_SHO_PITCH)[    ]                                                       \n" );//0
	printf( "ID: 2(L_SHO_PITCH)[    ]                                       Page Number:    \n" );//1
	printf( "ID: 3(R_SHO_ROLL) [    ]                                        Address:       \n" );//2
	printf( "ID: 4(L_SHO_ROLL) [    ]                                         Play Count:   \n" );//3
	printf( "ID: 5(R_ELBOW)    [    ]                                          Page Step:   \n" );//4
	printf( "ID: 6(L_ELBOW)    [    ]                                         Page Speed:   \n" );//5
	printf( "ID: 7(R_HIP_YAW)  [    ]                                         Accel Time:   \n" );//6
	printf( "ID: 8(L_HIP_YAW)  [    ]                                       Link to Next:   \n" );//7
	printf( "ID: 9(R_HIP_ROLL) [    ]                                       Link to Exit:   \n" );//8
	printf( "ID:10(L_HIP_ROLL) [    ]                                                       \n" );//9
	printf( "ID:11(R_HIP_PITCH)[    ]                                                       \n" );//0
	printf( "ID:12(L_HIP_PITCH)[    ]                                                       \n" );//1
	printf( "ID:13(R_KNEE)     [    ]                                                       \n" );//2
	printf( "ID:14(L_KNEE)     [    ]                                                       \n" );//3
	printf( "ID:15(R_ANK_PITCH)[    ]                                                       \n" );//4
	printf( "ID:16(L_ANK_PITCH)[    ]                                                       \n" );//5
	printf( "ID:17(R_ANK_ROLL) [    ]                                                       \n" );//6
	printf( "ID:18(L_ANK_ROLL) [    ]                                                       \n" );//7
	printf( "ID:19(HEAD_PAN)   [    ]                                                       \n" );//8
	printf( "ID:20(HEAD_TILT)  [    ]                                                       \n" );//9
	printf( "ID:21(R_GRIPPER)  [    ]                                                       \n" );//8
	printf( "ID:22(L_GRIPPER)  [    ]                                                       \n" );//9
	printf( "   PauseTime      [    ]                                                       \n" );//0

	if( Page.header.schedule == Action::SPEED_BASE_SCHEDULE )
		printf( "   Speed          [    ]                                                       \n" );//1
	else if( Page.header.schedule == Action::TIME_BASE_SCHEDULE )
		printf( "   Time(x 8msec)  [    ]                                                       \n" );//1

	printf( "                   STP7  STP0 STP1 STP2 STP3 STP4 STP5 STP6                    \n" );//2
	printf( "]                                                                              " );  // 3

	for(int i=0; i<=Action::MAXNUM_STEP; i++ )
		DrawStep(i);

	// Draw Compliance slope
	for( int id=JointData::ID_R_SHOULDER_PITCH; id<JointData::NUMBER_OF_JOINTS; id++ )
	{
		GoToCursor(CWSLOPE_COL, id -1);
		printf( "%.1d%.1d", Page.header.slope[id]>>4, Page.header.slope[id]&0x0f );
	}

	// Draw Page parameter
	GoToCursor( PAGEPARAM_COL, PLAYCOUNT_ROW );
	printf( "%.3d", Page.header.repeat );

	GoToCursor( PAGEPARAM_COL, STEPNUM_ROW );
	printf( "%.3d", Page.header.stepnum );

	GoToCursor( PAGEPARAM_COL, PLAYSPEED_ROW );
	printf( "%.3d", Page.header.speed );

	GoToCursor( PAGEPARAM_COL, ACCEL_ROW );
	printf( "%.3d", Page.header.accel );

	GoToCursor( PAGEPARAM_COL, NEXT_ROW );
	printf( "%.3d", Page.header.next );

	GoToCursor( PAGEPARAM_COL, EXIT_ROW );
	printf( "%.3d", Page.header.exit );

	// Draw Page information
	DrawName();

	GoToCursor(PAGENUM_COL, PAGENUM_ROW);
	std::cout<<Lverde;
	printf( "%.4d", indexPage );
	std::cout<<nulo;

	GoToCursor(ADDR_COL, ADDR_ROW);
	printf( "0x%.5X", (int)(indexPage*sizeof(Action::PAGE)) );

	DrawStepLine(false);

	GoToCursor(old_col, old_row);
}

void MinimalPublisher::DrawStep(int index)
{
	int old_col = Col;
	int old_row = Row;
	Action::STEP *step;
	int col;

	switch(index)
	{
	case 0:
		col = STP0_COL;
		step = &Page.step[0];
		break;

	case 1:
		col = STP1_COL;
		step = &Page.step[1];
		break;

	case 2:
		col = STP2_COL;
		step = &Page.step[2];
		break;

	case 3:
		col = STP3_COL;
		step = &Page.step[3];
		break;

	case 4:
		col = STP4_COL;
		step = &Page.step[4];
		break;

	case 5:
		col = STP5_COL;
		step = &Page.step[5];
		break;

	case 6:
		col = STP6_COL;
		step = &Page.step[6];
		break;

	case 7:
		col = STP7_COL;
		step = &Step;
		break;

	default:
		return;
	}

	for( int id=JointData::ID_R_SHOULDER_PITCH; id<JointData::NUMBER_OF_JOINTS; id++ )
	{
		GoToCursor(col, id -1);
		//if((step->position[id] + MotionManager::GetInstance()->m_Offset[id]) & Action::INVALID_BIT_MASK)
			printf("----");
		// else if((step->position[id] + MotionManager::GetInstance()->m_Offset[id]) & Action::TORQUE_OFF_BIT_MASK)
		// 	printf("????");
		if(step->position[id]  < 0)
			printf("%.3d", step->position[id]);
		else
			printf("%.4d", step->position[id]);
	}

	GoToCursor(col, PAUSE_ROW);
	printf("%4.3d", step->pause);

	GoToCursor(col, SPEED_ROW);
	printf("%4.3d", step->time);

	GoToCursor( old_col, old_row );
}

void MinimalPublisher::DrawStepLine(bool erase)
{
	int old_col = Col;
	int old_row = Row;
	int col;

	switch(Page.header.stepnum)
	{
	case 0:
		col = STP0_COL;
		break;

	case 1:
		col = STP1_COL;
		break;

	case 2:
		col = STP2_COL;
		break;

	case 3:
		col = STP3_COL;
		break;

	case 4:
		col = STP4_COL;
		break;

	case 5:
		col = STP5_COL;
		break;

	case 6:
		col = STP6_COL;
		break;

	case 7:
		col = CWSLOPE_COL;
		break;

	default:
		return;
	}
	col--;

	for( int id=JointData::ID_R_SHOULDER_PITCH; id<(JointData::NUMBER_OF_JOINTS + 2); id++ )
	{
		GoToCursor(col, id - 1);
		if(erase == true)
			printf( " " );
		else
			std::cout<<Lred<< "|"<<nulo;
	}

	GoToCursor(old_col, old_row);
}

void MinimalPublisher::DrawName()
{
	int old_col = Col;
	int old_row = Row;

	GoToCursor(NAME_COL, NAME_ROW);
	printf( "                " );
	GoToCursor(NAME_COL, NAME_ROW);

	for(int i=0; i<Action::MAXNUM_NAME; i++)
		printf("%c", (char)Page.header.name[i]);

	GoToCursor( old_col, old_row );
}

void MinimalPublisher::ClearCmd()
{
	PrintCmd("");
}

void MinimalPublisher::PrintCmd(const char *message)
{
	int len = strlen(message);
	MinimalPublisher::GoToCursor(0, CMD_ROW);

	printf( "] %s", message);
	for(int i=0; i<(SCREEN_COL - (len + 2)); i++)
		printf(" ");

	MinimalPublisher::GoToCursor(len + 2, CMD_ROW);
}

// void UpDownValue(CM730 *cm730, int offset)
void MinimalPublisher::UpDownValue(int offset)
{
	// SetValue(cm730, GetValue() + offset);
	MinimalPublisher::SetValue(GetValue() + offset);
}

int MinimalPublisher::GetValue()
{
	int col;
	int row;
	if(bBeginCommandMode == true)
	{
		col = Old_Col;
		row = Old_Row;
	}
	else
	{
		col = Col;
		row = Row;
	}

	if( col == STP7_COL )
	{
		if( row == PAUSE_ROW )
			return Step.pause;
		else if( row == SPEED_ROW )
			return Step.time;
		else
			return Step.position[row + 1];
	}
	else if( col <= STP6_COL )
	{
		int i;
		switch(col)
		{
		case STP0_COL:
			i = 0;
			break;

		case STP1_COL:
			i = 1;
			break;

		case STP2_COL:
			i = 2;
			break;

		case STP3_COL:
			i = 3;
			break;

		case STP4_COL:
			i = 4;
			break;

		case STP5_COL:
			i = 5;
			break;

		case STP6_COL:
			i = 6;
			break;
		}

		if( row == PAUSE_ROW )
			return Page.step[i].pause;
		else if( row == SPEED_ROW )
			return Page.step[i].time;
		else
			return Page.step[i].position[row + 1];
	}
	else if(col == CWSLOPE_COL)
		return (Page.header.slope[row + 1] >> 4);
	else if(col == CCWSLOPE_COL)
		return (Page.header.slope[row + 1] & 0x0f);
	else if(col == PAGEPARAM_COL)
	{
		if(row == PLAYCOUNT_ROW)
			return Page.header.repeat;
		else if(row == STEPNUM_ROW)
			return Page.header.stepnum;
		else if(row == PLAYSPEED_ROW)
			return Page.header.speed;
		else if(row == ACCEL_ROW)
			return Page.header.accel;
		else if(row == NEXT_ROW)
			return Page.header.next;
		else if(row == EXIT_ROW)
			return Page.header.exit;
	}

	return -1;
}

// void SetValue(CM730 *cm730, int value)
void MinimalPublisher::SetValue(uint32_t value)
{
	int col;
	int row;
	if(bBeginCommandMode == true)
	{
		col = Old_Col;
		row = Old_Row;
	}
	else
	{
		col = Col;
		row = Row;
	}

	GoToCursor(col, row);

	if( col == STP7_COL )
	{
		//printf("Dentro do primeiro if\n");
		if( row == PAUSE_ROW )
		{
			//printf("pause row\n");
			if(value >= 0 && value <= 255)
			{
				Step.pause = value;
				printf( "%4.3d", value );
				bEdited = true;
			}
		}
		else if( row == SPEED_ROW )
		{
			//printf("speed row\n");
			if(value >= 0 && value <= 255)
			{
				Step.time = value;
				printf( "%4.3d", value );
				bEdited = true;
			}
		}
		else
		{
			//printf("publisher\n");
			// if(value  + MotionManager::GetInstance()->m_Offset[row + 1] >= 0 && value  + MotionManager::GetInstance()->m_Offset[row + 1] <= MX28::MAX_VALUE)
			// {
			// 	if(!((Step.position[row + 1] + MotionManager::GetInstance()->m_Offset[row + 1]) & Action::INVALID_BIT_MASK) && !((Step.position[row + 1] + MotionManager::GetInstance()->m_Offset[row + 1])  & Action::TORQUE_OFF_BIT_MASK))
			// 	{
			// 		int error;

                    auto message_single = dynamixel_sdk_custom_interfaces::msg::SetPositionOriginal(); 
                    message_single.id = row+1;
                    message_single.address = MX28::P_GOAL_POSITION;
                    message_single.position = value;
                    publisher_single->publish(message_single);

                    
					// if(cm730->WriteWord(row + 1, MX28::P_GOAL_POSITION_L, value  + MotionManager::GetInstance()->m_Offset[row + 1], &error) == CM730::SUCCESS)
					// if(packetHandler->write4ByteTxRx(portHandler, (row+1), MX28::P_GOAL_POSITION, value  + MotionManager::GetInstance()->m_Offset[row + 1], &dxl_error) == COMM_SUCCESS)
					// {
						// if(!(error))
						// {
                    Step.position[row + 1] = value;
                    if(value > 0)
                        printf( "%.4d", value );
                    else
                        printf( "%.3d", value );
                    bEdited = true;
					// 	}
					// }
			// 	}
			// }
			// else
			// 	PrintCmd("Valor ultrapassando o limite do servo");
		}
	}
	else if( col <= STP6_COL )
	{
		int i;
		switch(col)
		{
		case STP0_COL:
			i = 0;
			break;

		case STP1_COL:
			i = 1;
			break;

		case STP2_COL:
			i = 2;
			break;

		case STP3_COL:
			i = 3;
			break;

		case STP4_COL:
			i = 4;
			break;

		case STP5_COL:
			i = 5;
			break;

		case STP6_COL:
			i = 6;
			break;
		}

		if( row == PAUSE_ROW )
		{
			if(value >= 0 && value <= 255)
			{
				Page.step[i].pause = value;
				printf( "%4.3d", value );
				bEdited = true;
			}
		}
		else if( row == SPEED_ROW )
		{
			if(value >= 0 && value <= 255)
			{
				Page.step[i].time = value;
				printf( "%4.3d", value );
				bEdited = true;
			}
		}
		else
		{
			// if(value  + MotionManager::GetInstance()->m_Offset[row + 1] >= 0 && value  + MotionManager::GetInstance()->m_Offset[row + 1] <= MX28::MAX_VALUE) //Aumentando o valor da entrada
			// {
			// 	if(!((Page.step[i].position[row + 1] + MotionManager::GetInstance()->m_Offset[row + 1]) & Action::INVALID_BIT_MASK))
			// 	{
					Page.step[i].position[row + 1] = value;
					if(value > 0)
						printf( "%.4d", value );
					else
						printf( "%.3d", value );
					bEdited = true;
			// 	}
			// }
		}
	}
	else if(col == CWSLOPE_COL)
	{
		if(value >= 1 && value <= 7)
		{
			Page.header.slope[row + 1] = (value << 4) + (Page.header.slope[row + 1] & 0x0f);
			printf( "%.1d", value );
			bEdited = true;
		}
	}
	else if(col == CCWSLOPE_COL)
	{
		if(value >= 1 && value <= 7)
		{
			Page.header.slope[row + 1] = (Page.header.slope[row + 1] & 0xf0) + (value & 0x0f);
			printf( "%.1d", value );
			bEdited = true;
		}
	}
	else if(col == PAGEPARAM_COL)
	{
		if(row == PLAYCOUNT_ROW)
		{
			if(value >= 0 && value <= 255)
			{
				Page.header.repeat = value;
				printf( "%.3d", value );
				bEdited = true;
			}
		}
		else if(row == STEPNUM_ROW)
		{
			if(value >= 0 && value <= Action::MAXNUM_STEP)

			{
				if(Page.header.stepnum != value)
				{

					DrawStepLine(true);
					Page.header.stepnum = value;
					DrawStepLine(false);
					printf( "%.3d", value );
					bEdited = true;
				}
			}
		}
		else if(row == PLAYSPEED_ROW)
		{
			if(value >= 0 && value <= 255)
			{
				Page.header.speed = value;
				printf( "%.3d", value );
				bEdited = true;
			}
		}
		else if(row == ACCEL_ROW)
		{
			if(value >= 0 && value <= 255)
			{
				Page.header.accel = value;
				printf( "%.3d", value );
				bEdited = true;
			}
		}
		else if(row == NEXT_ROW)
		{
			if(value >= 0 && value <= 255)
			{
				Page.header.next = value;
				printf( "%.3d", value );
				bEdited = true;
			}
		}
		else if(row == EXIT_ROW)
		{
			if(value >= 0 && value <= 255)
			{
				Page.header.exit = value;
				printf( "%.3d", value );
				bEdited = true;
			}
		}
	}

	GoToCursor(col, row);
}

void MinimalPublisher::ToggleTorque()
{
	if(Col != STP7_COL || Row > ID_20_ROW)
		return;

	int id = Row + 1;

	
		//if(cm730->WriteByte(id, MX28::P_TORQUE_ENABLE, 1, 0) != CM730::SUCCESS)
		// if(packetHandler->write1ByteTxRx(portHandler, id, MX28::P_TORQUE_ENABLE, 1, &dxl_error) != COMM_SUCCESS)
		// 	return;

		uint32_t value;
		// if(cm730->ReadWord(id, MX28::P_PRESENT_POSITION_L, &value, 0) != CM730::SUCCESS)
		// if(packetHandler->read4ByteTxRx(portHandler, id, MX28::P_PRESENT_POSITION, &value, &dxl_error) != COMM_SUCCESS)
		// 	return;

		Step.position[id] = value;
		printf("%.4d", value);
	// }
	// else
	// {
	// 	// if(cm730->WriteByte(id, MX28::P_TORQUE_ENABLE, 0, 0) != CM730::SUCCESS)
	// 	// if(packetHandler->write4ByteTxRx(portHandler, id, MX28::P_TORQUE_ENABLE, 0, &dxl_error) != COMM_SUCCESS)
	// 	// 	return;

	// 	Step.position[id] = Action::TORQUE_OFF_BIT_MASK;
	// 	printf("????");
	// }

	GoToCursor(Col, Row);
}

void MinimalPublisher::BeginCommandMode()
{
	Old_Col = Col;
	Old_Row = Row;
	ClearCmd();
	GoToCursor(CMD_COL, CMD_ROW);
	bBeginCommandMode = true;
}

void MinimalPublisher::EndCommandMode()
{
	GoToCursor(Old_Col, Old_Row);
	bBeginCommandMode = false;
}

void MinimalPublisher::HelpCmd()
{
	system("clear");
	printf(" exit               Exits the program.\n");
	printf(" re                 Refreshes the screen.\n");
	printf(" b                  Move to previous page.\n");
	printf(" n                  Move to next page.\n");
	printf(" page [index]       Move to page [index].\n");
	printf(" list               View list of pages.\n");
	printf(" new                Clears data of current page and initializes page.\n");
	printf(" copy [index]       Copy data from page [index].\n");
	printf(" set [value]        Sets value on cursor [value].\n");
	printf(" save               Saves changes.\n");
	printf(" play               Motion playback of current page.\n");
    printf(" g [index]          Motion playback of STP[index].\n");
	printf(" name               Name for current page or changes the name of current page.\n");
	printf(" time               Change time base playing.\n");
	printf(" speed              Change speed base playing.\n");
	printf(" w [index]          Overwrites data from STP[index] with STP7.\n");
	printf(" i                  Inserts data from STP7 to STP0. \n" \
	       "                    Moves data from STP[x] to STP[x+1].\n");
	printf(" i [index]          Inserts data from STP7 to STP[index]. \n" \
	       "                    Moves data from STP[index] to STP[index+1].\n");
	printf(" m [index] [index2] Moves data from [index] to [index2] step.\n");
	printf(" z                  PID in maximum torque. \n");
	printf(" x                  PID in minimum torque. \n");
	printf(" d [index]          Deletes data from STP[index]. \n"
	       "                    Pushes data from STP[index] to STP[index-1].\n");
	printf(" on/off             Turn On/Off torque from ALL actuators.\n");
	printf(" on/off [index1] [index2] ...  \n"
	       "                    turns On/Off torque from ID[index1] ID[index2]...\n");
	printf(" t                  Motion playback of page 1 keeping the current page.\n");
	printf(" read               Read the motor position.\n");
	printf("\n");
	printf("       Copyright ROBOTIS CO.,LTD.\n");
	printf("\n");
	printf(" Press any key to continue...");
	_getch();

	DrawPage();
}

void MinimalPublisher::NextCmd()
{
	PageCmd(indexPage + 1);
}

void MinimalPublisher::PrevCmd()
{
	PageCmd(indexPage - 1);
}

void MinimalPublisher::PageCmd(int index)
{
	Action* action;
	if(AskSave() == true)
		return;

	if(index > 0 && index < Action::MAXNUM_PAGE)
	{
		indexPage = index;
		action->LoadPage(indexPage, &Page);

		Col = STP7_COL;
		Row = ID_1_ROW;
		DrawPage();
	}
	else
		PrintCmd("Invalid page index");

	bEdited = false;
}

void MinimalPublisher::TimeCmd()
{
	Page.header.schedule = Action::TIME_BASE_SCHEDULE;
	bEdited = true;
	DrawPage();
}

void MinimalPublisher::SpeedCmd()
{
	Page.header.schedule = Action::SPEED_BASE_SCHEDULE;
	bEdited = true;
	DrawPage();
}

void MinimalPublisher::PlayCmd()
{
	int value;


	PrintCmd("Playing... ('s' to stop, 'b' to brake)");
	//linuxMotionTimer.Start();

	// minIni* ini;
	// ini = new minIni((char *)INI_FILE_PATH);
	// MotionManager::GetInstance()->LoadINISettings(ini);
	// //MotionManager::GetInstance()->StartThread();
	// Action::GetInstance()->m_Joint.SetEnableBody(true, true);
	// MotionManager::GetInstance()->SetEnable(true);
	// if(Action::GetInstance()->Start(indexPage, &Page) == false)
	// {
	// 	PrintCmd("Failed to play this page!");
	// 	MotionManager::GetInstance()->SetEnable(false);
	// 	//linuxMotionTimer.Stop();
	// 	return;
	// }

	set_stdin();
	while(1)
	{
	// 	if(Action::GetInstance()->IsRunning() == false)
	// 		break;

		if(kbhit())
		{
			int key = _getch();
			GoToCursor(CMD_COL, CMD_ROW);
			if(key == 's')
			{
				//Action::GetInstance()->Stop();
				fprintf(stderr, "\r] Stopping...                                  ");
			}
			else if(key == 'b')
			{
				//Action::GetInstance()->Brake();
				fprintf(stderr, "\r] Braking...                                   ");
			}
			else
				fprintf(stderr, "\r] Playing... ('s' to stop, 'b' to brake)");
		}

		usleep(10000);
	}
	reset_stdin();

	// MotionManager::GetInstance()->SetEnable(false);
	// //MotionManager::GetInstance()->StopThread();
	// //linuxMotionTimer.Stop();

	GoToCursor(CMD_COL, CMD_ROW);
	PrintCmd("Done.");

	usleep(10000);

	ReadStep();
	DrawStep(7);
}

void MinimalPublisher::ListCmd()
{
	int old_col = Col;
	int old_row = Row;
	int index = 0;

	while(1)
	{
		system("clear");
		for(int i=0; i<22; i++)
		{
			for(int j=0; j<4; j++)
			{
				int k = (index * 88) + (j*22 + i);
				Action::PAGE page;
				// if(Action::GetInstance()->LoadPage(k, &page) == true)
				// {
					printf(" |%.3d.", k);
					for(int n=0; n<Action::MAXNUM_NAME; n++)
					{
						if((char)page.header.name[n] >= ' ' && (char)page.header.name[n] <= '~')
							printf("%c", (char)page.header.name[n]);
						else
							printf(" ");
					}
				// }
				// else
				// {
				// 	printf(" |                ");
				// }
			}
			printf("\n");
		}

		printf("\nAction Page List (%d/3) - Press key n(Next), b(Prev), q(Quit)", index + 1);
		while(1)
		{
			int ch = _getch();
			if(ch == 'n')
			{
				if(index < 2)
				{
					index++;
					break;
				}
			}
			else if(ch == 'b')
			{
				if(index > 0)
				{
					index--;
					break;
				}
			}
			else if(ch == 'q')
			{
				DrawPage();
				GoToCursor(old_col, old_row);
				return;
			}
		}
	}
}

// void OnOffCmd(CM730 *cm730, bool on, int num_param, int *list)
void MinimalPublisher::OnOffCmd(bool on, int num_param, int *list)
{
	// if(num_param == 0)
	// {
	// 	for(int id=JointData::ID_R_SHOULDER_PITCH; id<JointData::NUMBER_OF_JOINTS; id++)
	// 		// cm730->WriteByte(id, MX28::P_TORQUE_ENABLE, (int)on, 0);
	// 		packetHandler->write1ByteTxRx(portHandler, id, MX28::P_TORQUE_ENABLE, (uint8_t)on, &dxl_error);
	// }
	// else
	// {
	// 	for(int i=0; i<num_param; i++)
	// 	{
	// 		if(list[i] >= JointData::ID_R_SHOULDER_PITCH && list[i] <= JointData::ID_HEAD_TILT)
	// 			// cm730->WriteByte(list[i], MX28::P_TORQUE_ENABLE, (int)on, 0);
	// 			packetHandler->write1ByteTxRx(portHandler, list[i], MX28::P_TORQUE_ENABLE, (uint8_t)on, &dxl_error);
	// 	}
	// }

	ReadStep();
	DrawStep(7);
}

void MinimalPublisher::WriteStepCmd(int index)
{
	// for(int id=JointData::ID_R_SHOULDER_PITCH; id<JointData::NUMBER_OF_JOINTS; id++)
	// {
	// 	if((Step.position[id] + MotionManager::GetInstance()->m_Offset[id]) & Action::TORQUE_OFF_BIT_MASK)
	// 		return;
	// }

	if(index >= 0 && index < Action::MAXNUM_STEP)
	{
		Page.step[index] = Step;
		DrawStep(index);
		bEdited = true;
	}
	else
		PrintCmd("Invalid step index");
}

void MinimalPublisher::DeleteStepCmd(int index)
{
	if(index >= 0 && index < Action::MAXNUM_STEP)
	{
		for(int i=index; i<Action::MAXNUM_STEP; i++)
		{
			if(i == (Action::MAXNUM_STEP - 1))
			{
				for(int id=JointData::ID_R_SHOULDER_PITCH; id<JointData::NUMBER_OF_JOINTS; id++)
					Page.step[i].position[id] = Action::INVALID_BIT_MASK;

				Page.step[i].pause = 0;
				Page.step[i].time = 0;
			}
			else
				Page.step[i] = Page.step[i + 1];

			DrawStep(i);
		}

		if(index < Page.header.stepnum)
		{
			if(Page.header.stepnum != 0)
			{
				DrawStepLine(true);
				Page.header.stepnum--;
				DrawStepLine(false);
			}

			GoToCursor(PAGEPARAM_COL, STEPNUM_ROW);
			printf( "%.3d", Page.header.stepnum );
		}

		bEdited = true;
	}
	else
		PrintCmd("Invalid step index");
}

void MinimalPublisher::InsertStepCmd(int index)
{
// 	for(int id=JointData::ID_R_SHOULDER_PITCH; id<JointData::NUMBER_OF_JOINTS; id++)
// 	{
// 		if((Step.position[id] + MotionManager::GetInstance()->m_Offset[id]) & Action::TORQUE_OFF_BIT_MASK)
// 		{
// 			PrintCmd("Exist invalid joint value");
// 			return;
// 		}
// 	}

	if(index >= 0 && index < Action::MAXNUM_STEP)
	{
		for(int i=Action::MAXNUM_STEP-1; i>index; i-- )
		{
			Page.step[i] = Page.step[i-1];
			DrawStep(i);
		}

		Page.step[index] = Step;
		DrawStep(index);

		if(index == 0 || index < Page.header.stepnum)
		{
			if(Page.header.stepnum != Action::MAXNUM_STEP)
			{
				DrawStepLine(true);
				Page.header.stepnum++;
				DrawStepLine(false);
			}

			GoToCursor(PAGEPARAM_COL, STEPNUM_ROW);
			printf( "%.3d", Page.header.stepnum );
		}

		bEdited = true;
	}
	else
		PrintCmd("Invalid step index");
}

void MinimalPublisher::MoveStepCmd(int src, int dst)
{
	if(src < 0 || src >= Action::MAXNUM_STEP)
	{
		PrintCmd("Invalid step index");
		return;
	}

	if(dst < 0 || dst >= Action::MAXNUM_STEP)
	{
		PrintCmd("Invalid step index");
		return;
	}

	if(src == dst)
		return;

	Action::STEP step = Page.step[src];
	if(src < dst)
	{
		for(int i=src; i<dst; i++)
		{
			Page.step[i] = Page.step[i + 1];
			DrawStep(i);
		}
	}
	else
	{
		for(int i=src; i>dst; i--)
		{
			Page.step[i] = Page.step[i - 1];
			DrawStep(i);
		}
	}

	Page.step[dst] = step;
	DrawStep(dst);
	bEdited = true;
}

void MinimalPublisher::CopyCmd(int index)
{
	if(index == indexPage)
		return;

// 	if(Action::GetInstance()->LoadPage(index, &Page) == true)
// 	{
		DrawPage();
		bEdited = true;
// 	}
// 	else
// 		PrintCmd("Invalid page index");
}

void MinimalPublisher::NewCmd()
{
	//Action::GetInstance()->ResetPage(&Page);
	DrawPage();
	bEdited = true;
}

void MinimalPublisher::GoCmd(int index)
{
	//printf("%d INDEX\n", index);
	if(index < 0 || index >= Action::MAXNUM_STEP)
	{
		PrintCmd("Invalid step index");
		return;
	}

	if(index > Page.header.stepnum)
	{
		char frase[50];
		sprintf(frase, "%d INDEX\n", index);
		PrintCmd(frase);
		sleep(5);
		PrintCmd("Are you sure? (y/n) aaaaaaaaaa");
		if(_getch() != 'y')
		{
			ClearCmd();
			return;
		}
	}

	int id;
	int n = 0;
	uint8_t param[JointData::NUMBER_OF_JOINTS * (1 + MX28::PARAM_BYTES)];
	uint32_t wGoalPosition, wStartPosition, wDistance;
	auto message = dynamixel_sdk_custom_interfaces::msg::SetPosition();  
	int pos[18];

	for(id=JointData::ID_R_SHOULDER_PITCH; id<JointData::NUMBER_OF_JOINTS-1; id++)
	{
		if(id==19 || id==20 || id==21 || id==22)
			continue;

// 		if((Page.step[index].position[id] + MotionManager::GetInstance()->m_Offset[id]) & Action::INVALID_BIT_MASK)
// 		{
// 			printf("conta id %d =%d", id, (Page.step[index].position[id] + MotionManager::GetInstance()->m_Offset[id]));
// 			_getch();
// 			PrintCmd("Exist invalid joint value");
// 			return;
// 		}

// 		// if(cm730->ReadWord(id, MX28::P_PRESENT_POSITION_L, &wStartPosition, 0) != CM730::SUCCESS)
// 		// if(packetHandler->read4ByteTxRx(portHandler, id, MX28::P_PRESENT_POSITION, &wStartPosition, &dxl_error) != COMM_SUCCESS)
// 		// {
// 		// 	// printf("lendo id %d =%d", id, cm730->ReadWord(id, MX28::P_PRESENT_POSITION_L, &wStartPosition, 0));
// 		// 	printf("lendo id %d =%d", id, packetHandler->read4ByteTxRx(portHandler, id, MX28::P_PRESENT_POSITION, &wStartPosition, &dxl_error));
// 		// 	_getch();
// 		// 	PrintCmd("Failed to read position");
// 		// 	return;
// 		// }

 		wGoalPosition = (Page.step[index].position[id]); //wGoalPosition = (Page.step[index].position[id] + MotionManager::GetInstance()->m_Offset[id]);
// 		if( wStartPosition > wGoalPosition )
// 			wDistance = wStartPosition - wGoalPosition;
// 		else
// 			wDistance = wGoalPosition - wStartPosition;

// 		wDistance >>= 2;
// 		if( wDistance < 8 )
// 			wDistance = 8;

// 		param[n++] = id;
// 		// param[n++] = CM730::GetLowByte(wGoalPosition);
// 		// param[n++] = CM730::GetHighByte(wGoalPosition);
// 		// param[n++] = CM730::GetLowByte(wDistance);
// 		// param[n++] = CM730::GetHighByte(wDistance);
// 	// 	param[n++] = (DXL_LOBYTE(DXL_LOWORD(wGoalPosition)));
//     // param[n++] = (DXL_HIBYTE(DXL_LOWORD(wGoalPosition)));
//     // param[n++] = (DXL_LOBYTE(DXL_HIWORD(wDistance)));
//     // param[n++] = (DXL_HIBYTE(DXL_HIWORD(wDistance)));
        pos[id] = wGoalPosition;
	}

    message.id = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};          
    message.position = {pos[1], pos[2], pos[3], pos[4], pos[5], pos[6], pos[7], pos[8], pos[9], pos[10], pos[11], pos[12], pos[13], pos[14], pos[15], pos[16], pos[17], pos[18], 2048};   
    publisher_->publish(message);
// 	// cm730->SyncWrite(MX28::P_GOAL_POSITION_L, 5, JointData::NUMBER_OF_JOINTS - 1, param);
// 	// packetHandler->syncWriteTxOnly(portHandler, MX28::P_GOAL_POSITION, MX28::PARAM_BYTES, param, (JointData::NUMBER_OF_JOINTS * (1 + MX28::PARAM_BYTES)));

	Step = Page.step[index];
	DrawStep(7);
}

void MinimalPublisher::goInitPage()
{
	indexPageBuffer = indexPage;
	//Action::GetInstance()->LoadPage(1, &Page);
}

void MinimalPublisher::backToPage()
{
	// Action::GetInstance()->LoadPage(indexPageBuffer, &Page);
	indexPage = indexPageBuffer;
}

void MinimalPublisher::SaveCmd()
{
	if(bEdited == false)
		return;

	//if(Action::GetInstance()->SavePage(indexPage, &Page) == true)
		bEdited = false;
}

void MinimalPublisher::readServo()
{
	uint32_t value;
	// for(int id=JointData::ID_MIN; id<JointData::ID_MAX; id++)
	// {
	// 		// if(cm730->ReadWord(id, MX28::P_GOAL_POSITION_L, &value, 0) == CM730::SUCCESS)
	// 		if(packetHandler->read4ByteTxRx(portHandler, id, MX28::P_GOAL_POSITION, &value, &dxl_error) == COMM_SUCCESS)
	// 			Step.position[id] = value - MotionManager::GetInstance()->m_Offset[id];
	// }
	DrawStep(7);
}

void MinimalPublisher::NameCmd()
{
	ClearCmd();
	GoToCursor(CMD_COL, CMD_ROW);
	printf("name: ");
	char name[80] = {0};
	fgets(name, 80, stdin);
	fflush(stdin);
	for(int i=0; i<=Action::MAXNUM_NAME; i++)
		Page.header.name[i] = name[i];
	DrawName();
	bEdited = true;
}


void MinimalPublisher::change_current_dir()
{
    char exepath[1024] = {0};
    if(readlink("/proc/self/exe", exepath, sizeof(exepath)) != -1)
        chdir(dirname(exepath));
}

void MinimalPublisher::sighandler(int sig)
{
    struct termios term;
    tcgetattr( STDIN_FILENO, &term );
    term.c_lflag |= ICANON | ECHO;
    tcsetattr( STDIN_FILENO, TCSANOW, &term );

    exit(0);
}

int main(int argc, char * argv[])
{
	 rclcpp::init(argc, argv);
  char filename[128];
	char string1[50]; //String

    signal(SIGABRT, &MinimalPublisher::sighandler);
    signal(SIGTERM, &MinimalPublisher::sighandler);
    signal(SIGQUIT, &MinimalPublisher::sighandler);
    signal(SIGINT, &MinimalPublisher::sighandler);

    MinimalPublisher::change_current_dir();

    minIni* ini;
    ini = new minIni((char *)INI_FILE_PATH);

   //Acopla ou cria a memoria compartilhada
    // int *mem = using_shared_memory(ini->getd("Communication","no_player_robofei",-1024) * 100); //0 for real robot

    // if(argc < 2)
    strcpy(filename, MOTION_FILE_PATH); // Set default motion file path
    // else
    //     strcpy(filename, argv[1]);

    //Configurando para prioridade maxima para executar este processo-------
    sprintf(string1,"echo robo 123456| sudo -S renice -20 -p %d", getpid());
    system(string1);
  MinimalPublisher::DrawIntro();
   rclcpp::spin(std::make_shared<MinimalPublisher>());
  MinimalPublisher::DrawEnding();
   rclcpp::shutdown();
  return 0;
}