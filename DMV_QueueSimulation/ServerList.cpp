/*
	Yilmaz, Ferah
	Krishcko, Alina
*/

#include "ServerList.h"
#include <cmath>

using namespace std;

	//default constructor
ServerList::ServerList()
{
	numOfServers = 1;
	servers = new ServerType[10];
}

	//overloaded constructor
ServerList::ServerList(int theNumOfServers)
{
	numOfServers = theNumOfServers;
	servers = new ServerType[theNumOfServers + 10];
}

	//setServerBusy
void ServerList::setServerBusy(int serverID,
	const CustomerType& theCustomer)
{
	int time = theCustomer.getTransactionTime();

	servers[serverID].setBusy();
	servers[serverID].setTransactionTime(time);
	servers[serverID].setCurrentCustomer(theCustomer);
}

	//setServerBusy
void ServerList::setServerBusy(int serverID,
	const CustomerType& theCustomer, int theTransactionTime)
{
	servers[serverID].setBusy();
	servers[serverID].setTransactionTime(theTransactionTime);
	servers[serverID].setCurrentCustomer(theCustomer);
}

	//getFreeServerID
int ServerList::getFreeServerID() const
{
	int serverID = -1;

	int i = 0;
	while (i < numOfServers)
	{
		if (servers[i].isFree()) return i;
		else ++i;
	}

	return serverID;
}

	//getNumberOfBusyServers
int ServerList::getNumberOfBusyServers() const
{
	int numFree = 0;

	for(int i = 0; i < numOfServers; ++i)
	{
		if (servers[i].isFree())
			++numFree; 
	}

	return (numOfServers - numFree);
}

	//updateServers
void ServerList::updateServers()
{
	for(int i = 0; i < numOfServers; i++)
		if(!servers[i].isFree())
		{
			servers[i].decreaseTransactionTime();
			if(servers[i].getRemainingTransactionTime() == 0)
			{
				cout << "Server No: " << (i+1) << " Customer number "
					<< servers[i].getCurrentCustomerNumber()
					<< " departed at " << endl
					<< "             clock unit "
					<< servers[i].getCurrentCustomerArrivalTime() 
					+ servers[i].getCurrentCustomerWaitingTime() 
					+ servers[i].getCurrentCustomerTransactionTime()
					<< endl;
				servers[i].setFree();
			}
		}
}

	//destructor
ServerList::~ServerList()
{
	delete [] servers; 
}