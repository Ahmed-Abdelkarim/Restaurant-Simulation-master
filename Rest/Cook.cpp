#include "Cook.h"
#include "Order.h"
#include"Restaurant.h"
Cook::Cook()
{
	NumOfOrders = 0;
}


Cook::~Cook()
{
}


int Cook::GetID() const
{
	return ID;
}

int Cook::GetSpeed() const
{
	return speed;
}


ORD_TYPE Cook::GetType() const
{
	return type;
}


void Cook::setID(int id)
{
	ID = id;
}

void Cook::setSpeed(int s)
{
	speed = s;
}

void Cook::setType(ORD_TYPE t)
{
	type = t;
}

void Cook::takeBreak(Restaurant * servRest, Cook* breakCook ,int timeStep)
{
	int breakTime;
	pair<Cook*, int>CookInBreak;
	switch (breakCook->GetType()) {
	case TYPE_NRM:
		breakTime = timeStep +  breakCook->BNorm;
		CookInBreak.make_pair(breakCook, breakTime);
		servRest->NormalBreakCooks.enqueue(CookInBreak);
		break;
	case TYPE_VEG:
		breakTime = timeStep +  breakCook->BVegan;
		CookInBreak.make_pair(breakCook, breakTime);
		servRest->VeganBreakCooks.enqueue(CookInBreak);
		break;
	case TYPE_VIP:
		breakTime = timeStep +  breakCook->BVip;
		CookInBreak.make_pair(breakCook, breakTime);
		servRest->VipBreakCooks.enqueue(CookInBreak);
		break;
	};
}

void Cook::FinishBreak(Restaurant * servRest, int timeStep)
{
	if(!servRest->VipBreakCooks.isEmpty())
	{ 
		pair<Cook*, int>VipCookOutBreak;
		servRest->VipBreakCooks.peekFront(VipCookOutBreak);
		if (VipCookOutBreak.second <= timeStep)
		{
			servRest->VipBreakCooks.dequeue(VipCookOutBreak);
			VipCookOutBreak.first->NumOfOrders = 0;
			servRest->VIP_cooks.enqueue(VipCookOutBreak.first);
		}
	}
	if (!servRest->NormalBreakCooks.isEmpty()) 
	{
		pair<Cook*, int>NormalCookOutBreak;
		servRest->NormalBreakCooks.peekFront(NormalCookOutBreak);
		if (NormalCookOutBreak.second <= timeStep)
		{
			servRest->NormalBreakCooks.dequeue(NormalCookOutBreak);
			NormalCookOutBreak.first->NumOfOrders = 0;
			servRest->Normal_cooks.enqueue(NormalCookOutBreak.first);
		}
	}
	if (!servRest->VeganBreakCooks.isEmpty())
	{
		pair<Cook*, int>VeganCookOutBreak;
		servRest->VeganBreakCooks.peekFront(VeganCookOutBreak);
		if (VeganCookOutBreak.second <= timeStep)
		{
			servRest->VeganBreakCooks.dequeue(VeganCookOutBreak);
			VeganCookOutBreak.first->NumOfOrders = 0;
			servRest->Vegan_cooks.enqueue(VeganCookOutBreak.first);
		}
	}
}

void Cook::excuteCooking(Restaurant* servRest, int timeStep)
{
	if(!servRest->VipServing.isEmpty()){
		pair<Order*, Cook*>VipServOrder;
		servRest->VipServing.peekFront(VipServOrder);
		int preparingTime = VipServOrder.first->getServTime() + VipServOrder.first->getWaitTime() + VipServOrder.first->getArrTime();
		if (preparingTime <= timeStep) {
			servRest->VipServing.dequeue(VipServOrder);
			VipServOrder.first->setStatus(DONE);
			servRest->VipServiced.InsertEnd(VipServOrder.first);
			Cook*workingCook;
			if (VipServOrder.second->GetType() == TYPE_NRM) {
				servRest->NormalBusyCooks.dequeue(workingCook, VipServOrder.second);
				if (workingCook->NumOfOrders == workingCook->limit) {
					takeBreak(servRest, workingCook, timeStep);
				}
				else {
					workingCook->NumOfOrders++;
					if (workingCook->GetType() == TYPE_NRM)
						servRest->Normal_cooks.enqueue(workingCook);
					if (workingCook->GetType() == TYPE_VIP)
						servRest->VIP_cooks.enqueue(workingCook);
				}
			}
			if (VipServOrder.second->GetType() == TYPE_VIP) {
				servRest->VipBusyCooks.dequeue(workingCook, VipServOrder.second);
				if (workingCook->NumOfOrders == workingCook->limit) {
					takeBreak(servRest, workingCook, timeStep);
				}
				else {
					workingCook->NumOfOrders++;
					if (workingCook->GetType() == TYPE_NRM)
						servRest->Normal_cooks.enqueue(workingCook);
					if (workingCook->GetType() == TYPE_VIP)
						servRest->VIP_cooks.enqueue(workingCook);
				}
			}
		}
	}
	if (!servRest->serving.isEmpty()) {
		pair<Order*, Cook*>servOrder;
		servRest->serving.peekFront(servOrder);
		int preparingTime = servOrder.first->getServTime() + servOrder.first->getWaitTime() + servOrder.first->getArrTime();
		if (preparingTime <= timeStep) {
			servRest->serving.dequeue(servOrder);
			servOrder.first->setStatus(DONE);
			Cook*workingCook = new Cook;
			if (servOrder.first->GetType() == TYPE_NRM)
			{
				servRest->NormalServiced.InsertEnd(servOrder.first);
				if (servOrder.second->GetType() == TYPE_NRM) {
					servRest->NormalBusyCooks.dequeue(workingCook, servOrder.second);
					if (workingCook->NumOfOrders == workingCook->limit) {
						takeBreak(servRest, workingCook, timeStep);
					}
					else {
						workingCook->NumOfOrders++;
						if (workingCook->GetType() == TYPE_NRM)
							servRest->Normal_cooks.enqueue(workingCook);
						if (workingCook->GetType() == TYPE_VIP)
							servRest->VIP_cooks.enqueue(workingCook);
					}
				}	
				if (servOrder.second->GetType() == TYPE_VIP) {
										servRest->VipBusyCooks.dequeue(workingCook, servOrder.second);

					if (workingCook->NumOfOrders == workingCook->limit) {
						takeBreak(servRest, workingCook, timeStep);
					}
					else {
						workingCook->NumOfOrders++;
						if (workingCook->GetType() == TYPE_NRM)
							servRest->Normal_cooks.enqueue(workingCook);
						if (workingCook->GetType() == TYPE_VIP)
							servRest->VIP_cooks.enqueue(workingCook);
					}
				}
			}
			else if (servOrder.first->GetType() == TYPE_VEG)
			{
				servRest->VeganServiced.InsertEnd(servOrder.first);
				servRest->VeganBusyCooks.dequeue(workingCook, servOrder.second);
				if (workingCook->NumOfOrders == workingCook->limit) {
					takeBreak(servRest, workingCook, timeStep);
				}
				else {
					workingCook->NumOfOrders++;
					servRest->Vegan_cooks.enqueue(workingCook);
				}
			}
		}
	}
	
}
bool operator==(Cook const &a, Cook const &b) {
	if (a.GetID() == b.GetID()) return true;
	return false;

}