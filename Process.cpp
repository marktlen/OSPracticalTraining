#include "myProcess.h"

myProcess::myProcess()
{
}

myProcess::~myProcess()
{
}

/**
 * @brief set pid name in pcb
 * 
 * @param name pcb.PID_name
 */
void myProcess::SetPID_name(char name)
{
    pcb.PID_name = name;
}

/**
 * @brief set process information
 * 
 * @param name pcb.PID_name
 * @param setPID pcb.PID
 * @param prio pcb Priority
 */
void myProcess::Create(char name, int setPID, Priority prio)
{
    pcb.PID_name = name;
    pcb.PID = setPID;
    pcb.priority = prio;
}