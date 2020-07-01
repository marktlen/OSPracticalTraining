#include "Resources.h"

Resources::Resources()
{
	rid = 0;
	InitNum = 0;
	avalibleNumber = 0;
}

Resources::~Resources()
{
}

/**
 * @brief request resource when is only one resource
 *
 * @param pid process ID
 * @return status code
 */
bool Resources::setResources(int setRid, int setNum)
{
	rid = setRid;
	InitNum = setNum;
	avalibleNumber = setNum;
	return true;
}
int Resources::request(int pid)
{
	if (avalibleNumber == 1) //only one resource
	{
		avalibleNumber = 0; // set resource is null
		return successDistribute;
	}
	else
	{
		block_list.push(pid);// push process in Waiting list
		return errDistribute;
	}
}
/**
 * @brief request numbers of resource
 *
 * @param pid process id
 * @param num number of resource
 * @return status code
 */
int Resources::request(int pid, int num)
{
	if (avalibleNumber >= num)
	{
		avalibleNumber -= num;
		return successDistribute;
	}
	else
	{
		block_list.push(pid);
		return errDistribute;
	}
}

/**
 * @brief request numbers of resource
 *
 * @param pid resource id
 * @return waiting list is empty return zero ,otherwish return front pid in queue
 */
int Resources::release(int pid)
{
	avalibleNumber = 1;
	if (block_list.empty())
	{
		return successDistribute;
	}
	else
	{
		pid = block_list.front();
		block_list.pop();
		return pid;
	}
}

/**
 * @brief request numbers of resource
 *
 * @param pid resource id
 * @param num number of resource
 * @return waiting list is empty return zero ,otherwish return front pid in queue
 */
int Resources::release(int pid, int num)
{
	avalibleNumber += num;
	if (block_list.empty())
	{
		return successDistribute;
	}
	else
	{
		pid = block_list.front();
		//block_list.pop();
		return pid;
	}
}