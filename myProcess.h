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
 *
 */
enum Priority
{
	Prio_Init = 0,
	Prio_User = 1,
	Prio_System = 2
};


struct myPCB
{
	char PID_name;
	int PID = -1;
	int CPU_state;
	/*int memory;
	int open_files;*/
	//Resources* other_resources;
	int other_resources[256];
	process_state status;
	int block_resources;
	//Process creation_tree;
	Priority priority;
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

