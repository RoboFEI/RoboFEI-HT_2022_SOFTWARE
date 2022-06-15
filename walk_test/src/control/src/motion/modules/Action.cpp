/*
 *   Action.cpp
 *
 *   Author: ROBOTIS
 *
 */

#include <string.h>
#include "MotionStatus.h"
#include "Action.h"
#include <unistd.h>

using namespace Robot;


Action* Action::m_UniqueInstance = new Action();

Action::Action()
{
	DEBUG_PRINT = false;
	m_ActionFile = 0;
	m_Playing = false;
}

Action::~Action()
{
	if(m_ActionFile != 0)
		fclose( m_ActionFile );
}

bool Action::VerifyChecksum( PAGE *pPage )
{
	unsigned char checksum = 0x00;
    unsigned char *pt = (unsigned char*)pPage;

    for(unsigned int i = 0; i < sizeof(PAGE); i++)
    {
        checksum += *pt;
        pt++;
    }

    if(checksum != 0xff)
        return false;

    return true;
}

void Action::SetChecksum( PAGE *pPage )
{
	unsigned char checksum = 0x00;
    unsigned char *pt = (unsigned char*)pPage;

    pPage->header.checksum = 0x00;

    for(unsigned int i=0; i<sizeof(PAGE); i++)
    {
        checksum += *pt;
        pt++;
    }

    pPage->header.checksum = (unsigned char)(0xff - checksum);
}

void Action::ResetPage(PAGE *pPage)
{
	unsigned char *pt = (unsigned char*)pPage;

    for(unsigned int i=0; i<sizeof(PAGE); i++)
    {
        *pt = 0x00;
        pt++;
    }

    pPage->header.schedule = TIME_BASE_SCHEDULE; // default time base
    pPage->header.repeat = 1;
    pPage->header.speed = 32;
    pPage->header.accel = 32;

	for(int i=0; i<JointData::NUMBER_OF_JOINTS; i++)
        pPage->header.slope[i] = 0x55;

    for(int i=0; i<MAXNUM_STEP; i++)
    {
        for(int j=0; j<31; j++)
            pPage->step[i].position[j] = INVALID_BIT_MASK;

        pPage->step[i].pause = 0;
        pPage->step[i].time = 0;
    }

    SetChecksum( pPage );
}

void Action::Initialize()
{
	m_Playing = false;

    //for( int id=JointData::ID_MIN; id<=JointData::ID_MAX; id++ )
        //m_Joint.SetValue(id, MotionStatus::m_CurrentJoints.GetValue(id));
}

bool Action::LoadFile( char* filename )
{
	FILE *action = fopen( filename, "r+b" );
    if( action == 0 )
	{
		if(DEBUG_PRINT == true)
			fprintf(stderr, "Can not open Action file!\n");
        return false;
	}

    fseek( action, 0, SEEK_END );
    if( ftell(action) != (long)(sizeof(PAGE) * MAXNUM_PAGE) )
    {
		if(DEBUG_PRINT == true)
			fprintf(stderr, "It's not an Action file!\n");
        fclose( action );
        return false;
    }

	if(m_ActionFile != 0)
		fclose( m_ActionFile );

	m_ActionFile = action;
	return true;
}

bool Action::CreateFile(char* filename)
{
	FILE *action = fopen( filename, "ab" );
	if( action == 0 )
	{
		if(DEBUG_PRINT == true)
			fprintf(stderr, "Can not create Action file!\n");
		return false;
	}

	PAGE page;
	ResetPage(&page);
	for(int i=0; i<MAXNUM_PAGE; i++)
		fwrite(&page, 1, sizeof(PAGE), action);
    
	if(m_ActionFile != 0)
		fclose( m_ActionFile );

	m_ActionFile = action;
	return true;
}

bool Action::Start(int iPage)
{
	if( iPage < 1 || iPage >= MAXNUM_PAGE )
	{
		if(DEBUG_PRINT == true)
			fprintf(stderr, "Can not play page.(%d is invalid index)\n", iPage);
        return false;
	}

	PAGE page;
	if( LoadPage(iPage, &page) == false )
        return false;

	return Start(iPage, &page);
}

bool Action::Start(char* namePage)
{
	int index;
	PAGE page;

	for(index=1; index<MAXNUM_PAGE; index++)
	{
		if(LoadPage(index, &page) == false)
			return false;

		if(strcmp(namePage, (char*)page.header.name) == 0)
			break;
	}

	return Start(index, &page);
}

bool Action::Start(int index, PAGE *pPage)
{
	if(m_Playing == true)
	{
		if(DEBUG_PRINT == true)
			fprintf(stderr, "Can not play page %d.(Now playing)\n", index);
        return false;
	}

	m_PlayPage = *pPage;

    if( m_PlayPage.header.repeat == 0 || m_PlayPage.header.stepnum == 0 )
	{
		if(DEBUG_PRINT == true)
			fprintf(stderr, "Page %d has no action\n", index);
        return false;
	}
		m_IndexPlayingPage = index;
		m_StartingPage = index;
		m_SeqCount = 0;
		m_StartingPageSeqCount = m_PlayPage.header.seq_repeats;
    m_FirstDrivingStart = true;    
    m_Playing = true;
	return true;
}

void Action::Stop()
{
	m_StopPlaying = true;
}

void Action::Brake()
{
	m_Playing = false;
}

bool Action::IsRunning()
{
	return m_Playing;
}

bool Action::IsRunning(int *iPage, int *iStep)
{
	if(iPage != 0)
		*iPage = m_IndexPlayingPage;

	if(iStep != 0)
		*iStep = m_PageStepCount - 1;

	return IsRunning();
}

bool Action::LoadPage(int index, PAGE *pPage)
{
	long position = (long)(sizeof(PAGE)*index);

    if( fseek( m_ActionFile, position, SEEK_SET ) != 0 )
        return false;

    if( fread( pPage, 1, sizeof(PAGE), m_ActionFile ) != sizeof(PAGE) )
        return false;

    if( VerifyChecksum( pPage ) == false )
        ResetPage( pPage );

    return true;
}

bool Action::SavePage(int index, PAGE *pPage)
{
	long position = (long)(sizeof(PAGE)*index);

	if( VerifyChecksum(pPage) == false )
        SetChecksum(pPage);

    if( fseek( m_ActionFile, position, SEEK_SET ) != 0 )
        return false;

    if( fwrite( pPage, 1, sizeof(PAGE), m_ActionFile ) != sizeof(PAGE) )
        return false;
    
	return true;
}

void Action::Process()
{
    printf("ACTION PROCESS\n");
	//////////////////// ���� ����
    unsigned char bID;
    unsigned long ulTotalTime256T;
    unsigned long ulPreSectionTime256T;
    unsigned long ulMainTime256T;
    long lStartSpeed1024_PreTime_256T;
    long lMovingAngle_Speed1024Scale_256T_2T;
    long lDivider1,lDivider2;
    unsigned short wMaxAngle1024;
    unsigned short wMaxSpeed256;
    unsigned short wTmp;
    short int wPrevTargetAngle; // Start position
    short int wCurrentTargetAngle; // Target position
    short int wNextTargetAngle; // Next target position
    unsigned char bDirectionChanged;

    ///////////////// Static ����
	static short int wpStartAngle1024[JointData::NUMBER_OF_JOINTS]; // ������ ���� ����
    static short int wpTargetAngle1024[JointData::NUMBER_OF_JOINTS]; // ������ ���� ����
    static short int ipMovingAngle1024[JointData::NUMBER_OF_JOINTS]; // �� ������ �Ÿ�
    static short int ipMainAngle1024[JointData::NUMBER_OF_JOINTS]; // ��� �������� ������ �Ÿ�
    static short int ipAccelAngle1024[JointData::NUMBER_OF_JOINTS]; // ���� �������� ������ �Ÿ�
    static short int ipMainSpeed1024[JointData::NUMBER_OF_JOINTS]; // ��ǥ ��ӵ�
    static short int ipLastOutSpeed1024[JointData::NUMBER_OF_JOINTS]; // �� �� ������ �ӵ�(����)
    static short int ipGoalSpeed1024[JointData::NUMBER_OF_JOINTS]; // ���Ͱ� ���� �� ��ǥ�ӵ�
    static unsigned char bpFinishType[JointData::NUMBER_OF_JOINTS]; // ���� ������ ������ ����
    short int iSpeedN;
    static unsigned short wUnitTimeCount;
    static unsigned short wUnitTimeNum;
    static unsigned short wPauseTime;
    static unsigned short wUnitTimeTotalNum;
    static unsigned short wAccelStep;
    static unsigned char bSection;
    static unsigned char bPlayRepeatCount;
    static unsigned short wNextPlayPage;

    /////////////// Enum ����

    /**************************************
    * Section             /----\
    *                    /|    |\
    *        /+---------/ |    | \
    *       / |        |  |    |  \
    * -----/  |        |  |    |   \----
    *      PRE  MAIN   PRE MAIN POST PAUSE
    ***************************************/
    enum{ PRE_SECTION, MAIN_SECTION, POST_SECTION, PAUSE_SECTION };
    enum{ ZERO_FINISH, NONE_ZERO_FINISH};

    if( m_Playing == false )
        return;

    if( m_FirstDrivingStart == true ) // ó�� �����Ҷ�
    {
        m_FirstDrivingStart = false; //First Process end
        m_PlayingFinished = false;
		m_StopPlaying = false;
        wUnitTimeCount = 0;
        wUnitTimeNum = 0;
        wPauseTime = 0;
        bSection = PAUSE_SECTION;
        m_PageStepCount = 0;
        bPlayRepeatCount = m_PlayPage.header.repeat;
        wNextPlayPage = 0;

		for( bID=JointData::ID_MIN; bID<=JointData::ID_MAX; bID++ )
        {
			if(m_Joint.GetEnable(bID) == true)
			{
				wpTargetAngle1024[bID] = MotionStatus::m_CurrentJoints.GetValue(bID);
				ipLastOutSpeed1024[bID] = 0;
				ipMovingAngle1024[bID] = 0;
				ipGoalSpeed1024[bID] = 0;
			}
        }
    }

    if( wUnitTimeCount < wUnitTimeNum ) // ���� �������̶��
    {
        wUnitTimeCount++;
				if( bSection == PAUSE_SECTION )
        {
        }
        else
        {
            for( bID=JointData::ID_MIN; bID<=JointData::ID_MAX; bID++ )
            {
                // ���� ����ϴ� ������ ���
              if(m_Joint.GetEnable(bID) == true)
                {
                    printf("ACTION SET VALUE %d\n", m_Joint.GetValue(bID));
						if( ipMovingAngle1024[bID] == 0 )
						m_Joint.SetValue(bID, wpStartAngle1024[bID]);
					else
					{
						if( bSection == PRE_SECTION )
						{
							iSpeedN = (short)(((long)(ipMainSpeed1024[bID] - ipLastOutSpeed1024[bID]) * wUnitTimeCount) / wUnitTimeNum);
							ipGoalSpeed1024[bID] = ipLastOutSpeed1024[bID] + iSpeedN;
							ipAccelAngle1024[bID] =  (short)((((long)(ipLastOutSpeed1024[bID] + (iSpeedN >> 1)) * wUnitTimeCount * 144) / 15) >> 9);

							m_Joint.SetValue(bID, wpStartAngle1024[bID] + ipAccelAngle1024[bID]);
						}
						else if( bSection == MAIN_SECTION )
						{
							m_Joint.SetValue(bID, wpStartAngle1024[bID] + (short int)(((long)(ipMainAngle1024[bID])*wUnitTimeCount) / wUnitTimeNum));
							ipGoalSpeed1024[bID] = ipMainSpeed1024[bID];
						}
						else // POST_SECTION
						{
							if( wUnitTimeCount == (wUnitTimeNum-1) )
							{
								// ���� ������ ������ ���̱����� �׳� ��ǥ ��ġ ���� ���
								m_Joint.SetValue(bID, wpTargetAngle1024[bID]);
							}
							else
							{
								if( bpFinishType[bID] == ZERO_FINISH )
								{
									iSpeedN = (short int)(((long)(0 - ipLastOutSpeed1024[bID]) * wUnitTimeCount) / wUnitTimeNum);
									ipGoalSpeed1024[bID] = ipLastOutSpeed1024[bID] + iSpeedN;
									m_Joint.SetValue(bID, wpStartAngle1024[bID] +  (short)((((long)(ipLastOutSpeed1024[bID] + (iSpeedN>>1)) * wUnitTimeCount * 144) / 15) >> 9));
								}
								else // NONE_ZERO_FINISH
								{
									// MAIN Section�� �����ϰ� �۵�-����
									// step���� ������� ���� � ������ �����ϴ� ��Ȳ�� �߻��� �� �����Ƿ� �̷��� �� ���ۿ� ����
									m_Joint.SetValue(bID, wpStartAngle1024[bID] + (short int)(((long)(ipMainAngle1024[bID]) * wUnitTimeCount) / wUnitTimeNum));
									ipGoalSpeed1024[bID] = ipMainSpeed1024[bID];
								}
							}
						}
					}

					m_Joint.SetSlope(bID, 1 << (m_PlayPage.header.slope[bID]>>4), 1 << (m_PlayPage.header.slope[bID]&0x0f));                    
                    m_Joint.SetPGain(bID, (256 >> (m_PlayPage.header.slope[bID]>>4)) << 2);
                }
            }
        }
    }
    else if( wUnitTimeCount >= wUnitTimeNum ) // ���� Section�� �Ϸ�Ǿ��ٸ�
    {
        wUnitTimeCount = 0;
							
        for( bID=JointData::ID_MIN; bID<=JointData::ID_MAX; bID++ )
        {
			if(m_Joint.GetEnable(bID) == true)
			{
				wpStartAngle1024[bID] = m_Joint.GetValue(bID);
				ipLastOutSpeed1024[bID] = ipGoalSpeed1024[bID];
			}
        }

        // Section ������Ʈ ( PRE -> MAIN -> POST -> (PAUSE or PRE) ... )
        if( bSection == PRE_SECTION )
        {
            // MAIN Section �غ�
            bSection = MAIN_SECTION;
            wUnitTimeNum =  wUnitTimeTotalNum - (wAccelStep << 1);

            for( bID=JointData::ID_MIN; bID<=JointData::ID_MAX; bID++ )
            {
				if(m_Joint.GetEnable(bID) == true)
				{
					if( bpFinishType[bID] == NONE_ZERO_FINISH )
					{
						if( (wUnitTimeTotalNum - wAccelStep) == 0 ) // ��� ������ ���� ���ٸ�
							ipMainAngle1024[bID] = 0;
						else
							ipMainAngle1024[bID] = (short)((((long)(ipMovingAngle1024[bID] - ipAccelAngle1024[bID])) * wUnitTimeNum) / (wUnitTimeTotalNum - wAccelStep));
					}
					else // ZERO_FINISH
						ipMainAngle1024[bID] = ipMovingAngle1024[bID] - ipAccelAngle1024[bID] - (short int)((((long)ipMainSpeed1024[bID] * wAccelStep * 12) / 5) >> 8);
				}
            }
        }
        else if( bSection == MAIN_SECTION )
        {
            // POST Section �غ�
            bSection = POST_SECTION;
            wUnitTimeNum = wAccelStep;

            for( bID=JointData::ID_MIN; bID<=JointData::ID_MAX; bID++ )
			{
				if(m_Joint.GetEnable(bID) == true)
					ipMainAngle1024[bID] = ipMovingAngle1024[bID] - ipMainAngle1024[bID] - ipAccelAngle1024[bID];
			}
        }
        else if( bSection == POST_SECTION )
        {
            // Pause time ���������� �޶���
            if( wPauseTime )
            {
                bSection = PAUSE_SECTION;
                wUnitTimeNum = wPauseTime;
            }
            else
            {
                bSection = PRE_SECTION;
            }
        }
        else if( bSection == PAUSE_SECTION )
        {
            // PRE Section �غ�
            bSection = PRE_SECTION;

            for( bID=JointData::ID_MIN; bID<=JointData::ID_MAX; bID++ )
			{
				if(m_Joint.GetEnable(bID) == true)
					ipLastOutSpeed1024[bID] = 0;
			}
        }

        // PRE Section�ÿ� ��� �غ� �Ѵ�.
        if( bSection == PRE_SECTION )
        {
            if( m_PlayingFinished == true ) // ����� �����ٸ�
            {
                m_Playing = false;
                return;
            }

            m_PageStepCount++;

            if( m_PageStepCount > m_PlayPage.header.stepnum ) // ���� ������ ����� �����ٸ�
            {
                // ���� ������ ����
                m_PlayPage = m_NextPlayPage;
                if( m_IndexPlayingPage != wNextPlayPage )
                    bPlayRepeatCount = m_PlayPage.header.repeat;
                m_PageStepCount = 1;
                m_IndexPlayingPage = wNextPlayPage;
            }

            if( m_PageStepCount == m_PlayPage.header.stepnum ) // ������ �����̶��
            {
                // ���� ������ �ε�
                if( m_StopPlaying == true ) // ��� ���� ������ �ִٸ�
                {
										wNextPlayPage = m_PlayPage.header.exit; // ���� �������� Exit ��������
                }
                else
                {
                    bPlayRepeatCount--;
                    if( bPlayRepeatCount > 0 ) // �ݺ� Ƚ���� ���Ҵٸ�
                        wNextPlayPage = m_IndexPlayingPage; // ���� �������� ���� ��������
                    else // �ݺ��� ���ߴٸ�
                        wNextPlayPage = m_PlayPage.header.next; // ���� �������� Next ��������
                }

                if( wNextPlayPage == 0 ) // ����� ���� �������� ���ٸ� ���� ���ܱ����ϰ� ����
                    {
										if(m_SeqCount < m_StartingPageSeqCount && m_StopPlaying == false)
											{
											wNextPlayPage = m_StartingPage;
											LoadPage( wNextPlayPage, &m_NextPlayPage );
											}
										else
											m_PlayingFinished = true;
										m_SeqCount++;
										}
                else
                {
                    // ���������� �ε�(������ �޸� ����, �ٸ��� ���� �б�)
                    if( m_IndexPlayingPage != wNextPlayPage )
                        LoadPage( wNextPlayPage, &m_NextPlayPage );
                    else
                        m_NextPlayPage = m_PlayPage;

                    // ����� ������ ���ٸ� ���� ���ܱ����ϰ� ����
                    if( m_NextPlayPage.header.repeat == 0 || m_NextPlayPage.header.stepnum == 0 )
                        m_PlayingFinished = true;
                }
            }

            //////// Step �Ķ���� ���
            wPauseTime = (((unsigned short)m_PlayPage.step[m_PageStepCount-1].pause) << 5) / m_PlayPage.header.speed;
            wMaxSpeed256 = ((unsigned short)m_PlayPage.step[m_PageStepCount-1].time * (unsigned short)m_PlayPage.header.speed) >> 5;
            if( wMaxSpeed256 == 0 )
                wMaxSpeed256 = 1;
            wMaxAngle1024 = 0;

            ////////// Joint�� �Ķ���� ���
            for( bID=JointData::ID_MIN; bID<=JointData::ID_MAX; bID++ )
			{
				if(m_Joint.GetEnable(bID) == true)
				{
					// ����, ����, �̷��� �������� ������ ���
					ipAccelAngle1024[bID] = 0;



					// Find current target angle
					//if( m_PlayPage.step[m_PageStepCount-1].position[bID] & INVALID_BIT_MASK )
					//	wCurrentTargetAngle = wpTargetAngle1024[bID];
					//else
						wCurrentTargetAngle = m_PlayPage.step[m_PageStepCount-1].position[bID];

					// Update start, prev_target, curr_target
					wpStartAngle1024[bID] = wpTargetAngle1024[bID];
					wPrevTargetAngle = wpTargetAngle1024[bID];
					wpTargetAngle1024[bID] = wCurrentTargetAngle;

					// Find Moving offset
					ipMovingAngle1024[bID] = (int)(wpTargetAngle1024[bID] - wpStartAngle1024[bID]);

					// Find Next target angle
					if( m_PageStepCount == m_PlayPage.header.stepnum ) // ���� ������ �������̶��
					{
						if( m_PlayingFinished == true ) // ���� �����̶��
							wNextTargetAngle = wCurrentTargetAngle;
						else
						{
							//if( m_NextPlayPage.step[0].position[bID] & INVALID_BIT_MASK )
							//	wNextTargetAngle = wCurrentTargetAngle;
							//else
								wNextTargetAngle = m_NextPlayPage.step[0].position[bID];
						}
					}
					else
					{
						//if( m_PlayPage.step[m_PageStepCount].position[bID] & INVALID_BIT_MASK )
						//	wNextTargetAngle = wCurrentTargetAngle;
						//else
							wNextTargetAngle = m_PlayPage.step[m_PageStepCount].position[bID];
					}

					// Find direction change
					if( ((wPrevTargetAngle < wCurrentTargetAngle) && (wCurrentTargetAngle < wNextTargetAngle))
						|| ((wPrevTargetAngle > wCurrentTargetAngle) && (wCurrentTargetAngle > wNextTargetAngle)) )
					{
						// ��� �����ϰų� �����ϰ�, Ȥ�� ���ٸ�(��, �ҿ��� ���� ���ٸ�)
						bDirectionChanged = 0;
					}
					else
					{
						bDirectionChanged = 1;
					}

					// Find finish type
					if( bDirectionChanged || wPauseTime || m_PlayingFinished == true )
					{
						bpFinishType[bID] = ZERO_FINISH;
					}
					else
					{
						bpFinishType[bID] = NONE_ZERO_FINISH;
					}

					if( m_PlayPage.header.schedule == SPEED_BASE_SCHEDULE )
					{
						//MaxAngle1024 update
						if( ipMovingAngle1024[bID] < 0 )
							wTmp = -ipMovingAngle1024[bID];
						else
							wTmp = ipMovingAngle1024[bID];

						if( wTmp > wMaxAngle1024 )
							wMaxAngle1024 = wTmp;
					}
				}
            }

            //�ð��� ����ؼ� �ٽ� 7.8msec�� ������(<<7)-�׽ð����ȿ� 7.8msec�� ������� ����� ��
            //���� ��ȯ�ڿ� ��/�ӵ��� ���ϰ�(�ð�)�� �ð��� �ٽ� 7.8msec�� ����ִ��� ���
            //���� ��ȯ ---  �� :1024��->300����,  �ӵ�: 256�� ->720��
            //wUnitTimeNum = ((wMaxAngle1024*300/1024) /(wMaxSpeed256 * 720/256)) /7.8msec;
            //             = ((128*wMaxAngle1024*300/1024) /(wMaxSpeed256 * 720/256)) ;    (/7.8msec == *128)
            //             = (wMaxAngle1024*40) /(wMaxSpeed256 *3);
            if( m_PlayPage.header.schedule == TIME_BASE_SCHEDULE )
                wUnitTimeTotalNum  = wMaxSpeed256; //TIME BASE 051025
            else
                wUnitTimeTotalNum  = (wMaxAngle1024 * 40) / (wMaxSpeed256 * 3);

            wAccelStep = m_PlayPage.header.accel;
            if( wUnitTimeTotalNum <= (wAccelStep << 1) )
            {
                if( wUnitTimeTotalNum == 0 )
                    wAccelStep = 0;
                else
                {
                    wAccelStep = (wUnitTimeTotalNum - 1) >> 1;
                    if( wAccelStep == 0 )
                        wUnitTimeTotalNum = 0; //�����̷��� ��� ����,����� �� �����̻��� �����ؾ�
                }
            }

            ulTotalTime256T = ((unsigned long)wUnitTimeTotalNum) << 1;// /128 * 256
            ulPreSectionTime256T = ((unsigned long)wAccelStep) << 1;// /128 * 256
            ulMainTime256T = ulTotalTime256T - ulPreSectionTime256T;
            lDivider1 = ulPreSectionTime256T + (ulMainTime256T << 1);
            lDivider2 = (ulMainTime256T << 1);

            if(lDivider1 == 0)
                lDivider1 = 1;

            if(lDivider2 == 0)
                lDivider2 = 1;

            for( bID=JointData::ID_MIN; bID<=JointData::ID_MAX; bID++ )
			{
				if(m_Joint.GetEnable(bID) == true)
				{
					lStartSpeed1024_PreTime_256T = (long)ipLastOutSpeed1024[bID] * ulPreSectionTime256T; //  *300/1024 * 1024/720 * 256 * 2
					lMovingAngle_Speed1024Scale_256T_2T = (((long)ipMovingAngle1024[bID]) * 2560L) / 12;

					if( bpFinishType[bID] == ZERO_FINISH )
						ipMainSpeed1024[bID] = (short int)((lMovingAngle_Speed1024Scale_256T_2T - lStartSpeed1024_PreTime_256T) / lDivider2);
					else
						ipMainSpeed1024[bID] = (short int)((lMovingAngle_Speed1024Scale_256T_2T - lStartSpeed1024_PreTime_256T) / lDivider1);

					if( ipMainSpeed1024[bID] > 1023 )
						ipMainSpeed1024[bID] = 1023;

					if( ipMainSpeed1024[bID] < -1023 )
						ipMainSpeed1024[bID] = -1023;
				}
            }

            wUnitTimeNum = wAccelStep; //PreSection
        }
    }
}
