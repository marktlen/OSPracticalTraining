#pragma once

#include "Resources.h"
#include <string>

/**
 * @brief Describe processs status
 * ready/running/blocked
 */
enum process_state
{
	PS_blocked = -1,
	PS_ready = 0,
	PS_running = 1
};

/**
 * @brief priority of process
 */
enum Priority
{
	Prio_Init = 0,
	Prio_User = 1,
	Prio_System = 2
};

struct myPCB
{
	char PID_name;			  //进程名
	int PID = -1;			  //进程号
	int other_resources[256]; //进程占用资源
	process_state status;	  //进程状态
	int block_resources;	  //阻塞时，请求资源数量
	Priority priority;		  //进程优先级
};

class myProcess
{
public:
	myProcess();
	~myProcess();

	myPCB pcb;
	void SetPID_name(char name);
	void Create(char name, int setPID, Priority prio);
};
