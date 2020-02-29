#pragma once
#include "..\Defs.h"
#include "..\Generic_DS\pair.h"
#include "..\Generic_DS\LinkedList.h"
#include "..\Rest\Restaurant.h"
#include "..\Rest\Order.h"
#include "..\Rest\VipOrder.h"

class serving 
{
public:
	Restaurant* workingRest;
	LinkedList<pair<Order *, Cook *>> servingList;
	serving(Restaurant* obj){
		workingRest = obj;
	}
	void excute(int timeStep) {
		//handling VIP orders
		if (workingRest->VIP_cooks.isEmpty()) {
			if (workingRest->Normal_cooks.isEmpty()) {
				Order *vip;
				workingRest->VIP_queue.dequeue(vip);
				double priority = 10;
				workingRest->Normalwaiting.enqueue(vip, priority);
			}
			else {
				Order *normal;
				if (!workingRest->Normalwaiting.isEmpty())
					workingRest->Normalwaiting.dequeue(normal);
				else
					workingRest->Normal_queue.dequeue(normal);
				Cook *vipCook;
				workingRest->VIP_cooks.dequeue(vipCook);
				pair<Order*, Cook*> servedOrder(normal, vipCook);
				servingList.InsertEnd(servedOrder);
			}
		// handling of normal orders
		if (workingRest->Normal_cooks.isEmpty()) {
			if (workingRest->VIP_cooks.isEmpty()) {
				Order *normal;
				workingRest->Normal_queue.dequeue(normal);
				double priority = 10;
				workingRest->Normalwaiting.enqueue(normal,priority);
			}
			else {
				Order *normal;
				if (!workingRest->Normalwaiting.isEmpty())
					workingRest->Normalwaiting.dequeue(normal);
				else
					workingRest->Normal_queue.dequeue(normal);
				Cook *vipCook;
				workingRest->VIP_cooks.dequeue(vipCook);
				pair<Order*, Cook*> servedOrder(normal,vipCook);
				servingList.InsertEnd(servedOrder);
			}
		}else {
			Order *normal;
			if (!workingRest->Normalwaiting.isEmpty())
				workingRest->Normalwaiting.dequeue(normal);
			else
				workingRest->Normal_queue.dequeue(normal);
			Cook *normalCook;
			workingRest->Normal_cooks.dequeue(normalCook);
			pair<Order*, Cook*> servedOrder(normal, normalCook);
			servingList.InsertEnd(servedOrder);
		}

		// handling vegan cooks
		if (workingRest->Normal_cooks.isEmpty()) {
			Order *vegan;
			workingRest->Vegan_queue.dequeue(vegan);
			workingRest->Veganwaiting.enqueue(vegan);
		}
		else {
			Order *vegan;
			if (!workingRest->Normalwaiting.isEmpty())
				workingRest->Veganwaiting.dequeue(vegan);
			else
				workingRest->Vegan_queue.dequeue(vegan);
			Cook *veganCook;
			workingRest->Normal_cooks.dequeue(veganCook);
			pair<Order*, Cook*> servedOrder(vegan, veganCook);
			servingList.InsertEnd(servedOrder);
		}

	}



};