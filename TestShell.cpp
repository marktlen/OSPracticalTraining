#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

#include "myProcess.h"

//-------------------------------------------------------------------
// Local Defines
//-------------------------------------------------------------------
#define NumOfresources 4 //资源种类数量

/**
 * @brief 格式化传入命令 
 */
struct Shell
{
	char command[8] = ""; //命令
	char R_Pname[8] = ""; //进行名或资源名
	int reqNum = 0;		  //请求数量或创建进程优先级
} shell;

//-------------------------------------------------------------------
// Member function
//-------------------------------------------------------------------
void InitResources(Resources *resource); //初始化函数

int main()
{
	//初始化资源
	Resources resource[NumOfresources];
	InitResources(resource);

	//初始化空闲进程块
	myProcess proc[10];
	for (int i = 0; i < 10; i++)
	{
		memset(proc[i].pcb.other_resources, 0, sizeof(proc[i].pcb.other_resources));
	}
	Priority prio = Priority::Prio_Init; //进程状态中间变量
	std::queue<int> readyList;			 //就绪队列

	//从文件读取指令
	FILE *fp; //获取命令
	fopen_s(&fp, "input.txt", "r");
	char fstr[256]; //单行指令最大长度

	//PID计数器，防止PID重复
	int PIDcounter = 1;

	while (fgets(fstr, 256, fp) != NULL)
	{
		//命令分割与判断运行
		std::stringstream ss(fstr);

		//读取第一个字段，判断命令类型
		ss >> shell.command;
		if (!strcmp(shell.command, "cr")) //创建进程
		{
			//读取创建进程名和优先级
			ss >> shell.R_Pname >> shell.reqNum;

			//输入的权限分析
			if (shell.reqNum == 0)
			{
				prio = Priority::Prio_Init;
			}
			else if (shell.reqNum == 1)
			{
				prio = Priority::Prio_User;
			}
			else
			{
				prio = Priority::Prio_System;
			}
			//填写PID，进程名，权值
			proc[PIDcounter].Create(shell.R_Pname[0], PIDcounter, prio);
			proc[PIDcounter].pcb.status = process_state::PS_ready;
			readyList.push(PIDcounter); //将新建的目录挂进就绪队列中
			PIDcounter++;				//自动增加PID号
		}
		else if (!strcmp(shell.command, "req")) //请求资源
		{
			//请求资源名，请求数量
			ss >> shell.R_Pname >> shell.reqNum;

			//申请资源号
			int rid = shell.R_Pname[1] - '0' - 1;
			//资源分配是否成功
			if (resource[rid].request(readyList.front(), shell.reqNum) == successDistribute)
			{
				//记录请求对应资源的数量
				proc[readyList.front()].pcb.other_resources[rid] = shell.reqNum;
			}
			else
			{
				//请求无法满足，从运行态转入阻塞态，并转入阻塞队列
				proc[readyList.front()].pcb.status = process_state::PS_blocked; //标记为阻塞状态
				proc[readyList.front()].pcb.block_resources = shell.reqNum;		//记录最后需求资源数量
				readyList.pop();												//移出就绪队列
			}
		}
		else if (!strcmp(shell.command, "de")) //释放资源，调整队列
		{
			ss >> shell.R_Pname;

			//查找释放的进程号
			int releasePid = 0;							   //释放资源的进程ID
			int length = sizeof(proc) / sizeof(myProcess); //进程最大数量
			for (int i = 1; i < length; i++)
			{
				if (proc[i].pcb.PID_name == shell.R_Pname[0])
				{
					releasePid = i;
					break;
				}
			}

			//释放对应进程里的资源
			for (int i = 0; i < NumOfresources; i++)
			{
				if (proc[releasePid].pcb.other_resources[i])
				{
					int readyPid = resource[i].release(releasePid, proc[releasePid].pcb.other_resources[i]);
					proc[releasePid].pcb.other_resources[i] = 0; //清空资源计数

					//查看阻塞的进程，是否达到运行条件，如果满足逐一返回对应资源的阻塞队列队首的pid
					if (resource[i].avalibleNumber >= proc[readyPid].pcb.block_resources)
					{
						resource[i].avalibleNumber -= proc[readyPid].pcb.block_resources; //添加资源
						resource[i].block_list.pop();									  //移出阻塞队列
						readyList.push(readyPid);										  //移入就绪队列
					}
				}
			}
		}
		else if (!strcmp(shell.command, "to")) //超时，进行调度
		{
			//换入新进程
			readyList.push(readyList.front());
			proc[readyList.front()].pcb.status = process_state::PS_ready; //设为就绪态
			readyList.pop();
		}
		else
		{
			printf("shell error!");
		}

		//打印当前运行内容
		proc[readyList.front()].pcb.status = process_state::PS_running; //设为运行态
		std::cout << proc[readyList.front()].pcb.PID_name << std::endl; //打印正在运行的任务
	}
	getchar();
	return 0;
}

/**
 * @brief 用于初始化资源数组
 * 
 * @param resource 资源数组指针
 */
void InitResources(Resources *resource)
{
	for (int i = 0; i < NumOfresources; i++)
	{
		resource[i].setResources(i + 1, i + 1);
	}
	std::cout << "init" << std::endl;
}
