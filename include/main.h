#pragma once
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "fastech/MOTION_DEFINE.h"
#include "fastech/ReturnCodes_Define.h"
#include "fastech/FAS_EziMOTIONPlusE.h"

class StepperMotor
{

private:
    BYTE lastIP;
    int id;
    DWORD dwAxisStatus;
    int mm_to_pulse = 1000;

public:
    StepperMotor(BYTE lastIP, int id);
    ~StepperMotor();

	int clearAlarm(int iBdID);
	void setMotorParameter(int iBdID, int ppr, int maxSpeed);
	int servoEnable(int iBdID);
	int findZeroPosition();
    int moveSingleAxis_mm(int id, double posAbs, double period);
    int isMotioning(int id);


};

int PPR = 10;
int MaxSpeed = 40000;
BYTE lastIP = 2;
int id = 0;