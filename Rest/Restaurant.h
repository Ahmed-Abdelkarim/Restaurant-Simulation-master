#pragma once

#include "..\Defs.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Generic_DS\PriorityQueue.h"
#include "..\Generic_DS\pair.h"
#include "..\Generic_DS\LinkedList.h"
#include"Cook.h"
class Event;
class Order;
class VipOrder;
class NormalOrder;
class VeganOrder;


// it is the maestro of the project
class Restaurant  
{	
private:
	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	VipOrder* pOrder;
	NormalOrder* nOrder;
	VeganOrder* vOrder;
	//
	// TODO: Add More Data Members As Needed
	Cook* chef;

	//


public:
	//orders Queues
	Queue<Order*>NormalOrders;
	Queue<Order*>VeganOrders;
	Queue<Order*> VipOrders;
	Queue<Order*> PromotedOrders;
	////////////////////////////////////
	// waiting Queues
	PriorityQueue<Order*>NormalOrdersWaiting;
	Queue<Order*>VeganOrdersWaiting;
	PriorityQueue<Order*> VipOrdersWaiting;
	////////////////////////////////////
	//Cooks Queues
	Queue<Cook*>Normal_cooks;
	Queue<Cook*>Vegan_cooks;
	Queue<Cook*>VIP_cooks;
	Queue<pair<Order*,Cook*>>serving;
	Queue<pair<Order*, Cook*>>VipServing;
	////////////////////////////////////
	Queue<pair<Cook*,int>> VipBreakCooks;
	Queue<pair<Cook*,int>> NormalBreakCooks;
	Queue<pair<Cook*,int>> VeganBreakCooks;
	Queue<Cook*> NormalBusyCooks;
	Queue<Cook*> VeganBusyCooks;
	Queue<Cook*> VipBusyCooks;
	////////////////////////////////////
	LinkedList<Order*>VipServiced;
	LinkedList<Order*>NormalServiced;
	LinkedList<Order*>VeganServiced;
	Restaurant();
	~Restaurant();
	
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void ExecuteOrders (int TimeStep);	//executes all orders at current timestep
	void CookOrders (int TimeStep);	//executes all orders at current timestep
	void RunSimulation();
	void SilentMode();
	void StepMode();
	void IntrMode();
	void LoadData(Restaurant*pRest);

	void FillDrawingList();

	//
	// TODO: Add More Member Functions As Needed
	//

};
