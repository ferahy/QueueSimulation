/*
	Yilmaz, Ferah
	Krishcko, Alina
*/

#include "Simulation.h"

#include <cstdlib>
#include <iomanip>
#include <cmath>

using namespace std;

void runSimulation()
{
	int simulationTime = 0;
	int numOfServers = 0;
	int transactionTime = 0;
	int timeBetweenCustomerArrival = 0;

	setSimulationParameters(simulationTime, numOfServers, 
							transactionTime, timeBetweenCustomerArrival);

	int customerNumer = 0;
	int clock = 0; 
	int totalWaitingTime = 0; 
	int numOfCustArrived = 0; 

	queue<CustomerType> waitingCustomersQueue; 
	ServerList myList(numOfServers);

	for (clock = 1; clock <= simulationTime; clock++)
	{
		myList.updateServers(); 

		if (!waitingCustomersQueue.empty())
		{
			int numOfCustLeftInQueue = static_cast<int>(waitingCustomersQueue.size()); 

			for (int i = 0; i < numOfCustLeftInQueue; ++i)
			{
				CustomerType tempCust = waitingCustomersQueue.front();
				tempCust.incrementWaitingTime(); 
				waitingCustomersQueue.pop(); 
				waitingCustomersQueue.push(tempCust); 
			}
		}
		
		if (isCustomerArrived(timeBetweenCustomerArrival))
		{
			++customerNumer;
			waitingCustomersQueue.push(CustomerType(customerNumer, clock, 0, transactionTime));
			++numOfCustArrived;
			cout << "Customer number " << customerNumer 
				 << " arrived at time unit " << clock << endl; 
		}

		int freeId = myList.getFreeServerID(); 

		if ((freeId != -1) && !waitingCustomersQueue.empty())
		{
			myList.setServerBusy(freeId, waitingCustomersQueue.front());
			totalWaitingTime = totalWaitingTime + waitingCustomersQueue.front().getWaitingTime();
			waitingCustomersQueue.pop(); 
		}
	}

	cout << "\nSimulation ran for " << simulationTime << " time units \n"
		<< "Number of servers : " << numOfServers << "\n"
		<< "Average transaction time : " << transactionTime << "\n"
		<< "Average arrival time difference between customers : " 
		<< timeBetweenCustomerArrival << "\n"; 

	generateStatistics(myList, waitingCustomersQueue, numOfCustArrived,
		totalWaitingTime); 
}

void setSimulationParameters(int& simulationTime, int& numOfServers,
	int& transactionTime,
	int& timeBetweenCustomerArrival)
{
	cout << "Enter the simulation time: " << flush;
	cin >> simulationTime;
	cout << endl;

	cout << "Enter the number of servers: " << flush;
	cin >> numOfServers;
	cout << endl;

	cout << "Enter the transaction time: " << flush;
	cin >> transactionTime;
	cout << endl;

	cout << "Enter the time between customer arrivals: " << flush;
	cin >> timeBetweenCustomerArrival;
	cout << endl;
}


bool isCustomerArrived(double arrivalTimeDifference)
{
	double value = 0.0;

	value = static_cast<double> (rand()) / static_cast<double>(RAND_MAX);

	return (value > exp(-1.0 / arrivalTimeDifference));
}


void generateStatistics(ServerList& serverList,
	queue<CustomerType>& customerQueue,
	int numOfCustomersArrived,
	int waitTimeServedCustomers)
{
	int customersLeftInQueue = 0;

	int totalWaitTime = waitTimeServedCustomers;

	CustomerType customer;

	while (!customerQueue.empty())
	{
		customer = customerQueue.front();
		customerQueue.pop();
		totalWaitTime = totalWaitTime + customer.getWaitingTime();
		customersLeftInQueue++;
	}

	//Find number of customers left in servers
	int customersLeftInServers = serverList.getNumberOfBusyServers();
	//Find number of customers completely served
	int numberOfCustomersServed = numOfCustomersArrived -
		customersLeftInServers -
		customersLeftInQueue;

	double averageWaitTime = 0;

	cout << "Total wait time: " << totalWaitTime << endl;
	cout << "Number of customers who completed a transaction: "
		<< numberOfCustomersServed << endl;
	cout << "Number of customers left in the servers: "
		<< customersLeftInServers << endl;
	cout << "Number of customers left in the queue: " << customersLeftInQueue
		<< endl;

	if (numOfCustomersArrived > 0)  // If number of customers arrived is > 0
		averageWaitTime = (static_cast<double>(totalWaitTime)) / numOfCustomersArrived;

	cout << fixed << showpoint;
	cout << setprecision(2);
	cout << "Average wait time: " << averageWaitTime << endl;

	cout << "\n************** END SIMULATION *************" << endl;

}

void updateCustQueue(queue<CustomerType>& customerQueue)
{
	CustomerType customer;

	customer.setWaitingTime(-1);
	int wTime = 0;

	customerQueue.push(customer);

	while (wTime != -1)
	{
		customer = customerQueue.front();
		customerQueue.pop();
		wTime = customer.getWaitingTime();
		if (wTime != -1)
		{
			customer.incrementWaitingTime();
			customerQueue.push(customer);
		}
	}
}

