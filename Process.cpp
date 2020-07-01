#include "myProcess.h"

myProcess::myProcess()
{
}

myProcess::~myProcess()
{
}

void myProcess::SetPID_name(char name)
{
    pcb.PID_name = name;
}

void myProcess::Create(char name, int setPID, Priority prio)
{
    pcb.PID_name = name;
    pcb.PID = setPID;
    pcb.priority = prio;
}