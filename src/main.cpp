#include "main.h"
using namespace PE;

StepperMotor::StepperMotor(BYTE lastIP, int id){
    while(FAS_ConnectTCP(192,168,0,lastIP, id) == FALSE){
        std::cout << "Connection Failed" << std::endl;
        Sleep(1000);
    }

    std::cout << "Successfully Connected" << std::endl;
    this->lastIP = lastIP;
    this->id= id;

}

StepperMotor::~StepperMotor(){
    FAS_Close(id);
}

int StepperMotor::clearAlarm(int id){
    return FAS_ServoAlarmReset(id);
}

void StepperMotor::setMotorParameter(int id, int ppr, int maxspeed){
    FAS_SetParameter(id, 0, ppr);
	FAS_SetParameter(id, 1, maxspeed);

    clearAlarm(id);
    return;
}

int StepperMotor::servoEnable(int id){
    return FAS_ServoEnable(id, TRUE);
}

int StepperMotor::findZeroPosition(){
    
}

int StepperMotor::moveSingleAxis_mm(int id, double posAbs, double period){
    long pulseAbs = posAbs * mm_to_pulse;	// 1rev : 1mm -> 1/1000 rev : 1 micron
	int velocity = abs(pulseAbs	/ period);

    FAS_MoveSingleAxisAbsPos(id, pulseAbs, velocity);

}

int StepperMotor::isMotioning(int id){
    EZISERVO_AXISSTATUS stAxisStatus;
    int nRtn;
    do{
        Sleep(1);
        int nRtn = FAS_GetAxisStatus(id, &dwAxisStatus);
        stAxisStatus.dwValue = dwAxisStatus;
    }
    while(stAxisStatus.FFLAG_MOTIONING);
}


int main(){
    StepperMotor *motor1 = new StepperMotor(lastIP, id);

    motor1->setMotorParameter(id, PPR, MaxSpeed);
    motor1->clearAlarm(id);
    motor1->servoEnable(id);

    for (int i = 0; i< 10 ; i++){
        motor1->moveSingleAxis_mm(id, 10000, 1);
        motor1->isMotioning(id);

        motor1->moveSingleAxis_mm(id, 0, 1);
        motor1->isMotioning(id);
    }
}