#pragma once

#include "..\Defs.h"
class Restaurant;
class Order;
#pragma once
class Cook
{
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding type (VIP, Normal, Vegan)
	int speed;		//dishes it can prepare in one clock tick (in one timestep)
public:
	Cook();
	virtual ~Cook();
	int GetID() const;
	int GetSpeed() const;
	ORD_TYPE GetType() const;
	void setID(int id);
	void setSpeed(int s);
	void setType(ORD_TYPE);
	void takeBreak(Restaurant * servRest, Cook* breakCook ,int timeStep);
	void FinishBreak(Restaurant * servRest,int timeStep);
	void excuteCooking(Restaurant* servRest, int timeStep);
	int limit;
	int BNorm;
	int BVegan;
	int BVip;
	int NumOfOrders;
};
