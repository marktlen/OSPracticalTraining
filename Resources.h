#include "queue"

/**
 * @brief return status code
 *
 */
enum statusCode
{
	unknowerr = -2,
	errDistribute = -1,
	successDistribute = 0
};

/**
 * @brief resource for process
 *
 */
class Resources
{
private:
	int rid;            //Resource ID
	int InitNum;        //Initial number of resources

public:
	int avalibleNumber; //Avalialbe number of resources currently
	std::queue<int> block_list; //Waiting list
	
	Resources();
	~Resources();

	bool setResources(int setRid, int setNum); //×ÊÔ´ÉèÖÃ
	int request(int pid);          //request resource when is only one resource
	int request(int pid, int num); //request numbers of resource

	int release(int pid);
	int release(int pid, int num);
};
