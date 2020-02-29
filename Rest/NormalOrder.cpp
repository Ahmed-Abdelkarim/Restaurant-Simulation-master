#include "NormalOrder.h"
#include"Restaurant.h"
NormalOrder::NormalOrder()
{

}
void NormalOrder::push(Restaurant * servRest, Order* ord)
{
	double priority = 10;
	servRest->NormalOrdersWaiting.enqueue(ord,priority);
}

void NormalOrder::pop(Restaurant * servRest, Order*&ord)
{
	servRest->NormalOrdersWaiting.dequeue(ord);
}

void NormalOrder::excute(Restaurant * servRest, int timeStep)
{
	if (!servRest->NormalOrders.isEmpty()) {
		Order *normal;
		servRest->NormalOrders.peekFront(normal);
		if (normal->getArrTime() > timeStep)
			return;
		if (servRest->Normal_cooks.isEmpty()) {
			if (servRest->VIP_cooks.isEmpty()) {
				servRest->NormalOrders.dequeue(normal);
				normal->setStatus(WAIT);
				push(servRest, normal);
			}
			else {
				if (!servRest->NormalOrdersWaiting.isEmpty()) {
					pop(servRest, normal);
					int waitTime = timeStep - normal->getArrTime();
					normal->set_Order_Wait_TimeStep(waitTime);
				}
				else
					servRest->NormalOrders.dequeue(normal);
				Cook *vipCook;
				servRest->VIP_cooks.dequeue(vipCook);
				int serviceTime = int(normal->GetDishes() / vipCook->GetSpeed());
				normal->set_Order_ServTime_TimeStep(serviceTime);
				normal->setStatus(SRV);
				pair<Order*, Cook*> servedOrder(normal, vipCook);
				servRest->serving.enqueue(servedOrder);
				servRest->VipBusyCooks.enqueue(vipCook);
			}
		}
		else {
			if (!servRest->NormalOrdersWaiting.isEmpty()) {
				pop(servRest, normal);
				int waitTime = timeStep - normal->getArrTime();
				normal->set_Order_Wait_TimeStep(waitTime);
			}
			else
				servRest->NormalOrders.dequeue(normal);
			Cook *normalCook;
			servRest->Normal_cooks.dequeue(normalCook);
			int serviceTime = int(normal->GetDishes() / normalCook->GetSpeed());
			normal->set_Order_ServTime_TimeStep(serviceTime);
			normal->setStatus(SRV);
			pair<Order*, Cook*> servedOrder(normal, normalCook);
			servRest->serving.enqueue(servedOrder);
			servRest->NormalBusyCooks.enqueue(normalCook);
		}
	}
	if (!servRest->NormalOrdersWaiting.isEmpty()) {
		Order *normal;
		Cook *normalCook;
		if (!servRest->Normal_cooks.isEmpty()) 
		{
			pop(servRest, normal);
			int waitTime = timeStep - normal->getArrTime();
			normal->set_Order_Wait_TimeStep(waitTime);
			servRest->Normal_cooks.dequeue(normalCook);
			int serviceTime = int(normal->GetDishes() / normalCook->GetSpeed());
			normal->set_Order_ServTime_TimeStep(serviceTime);
			normal->setStatus(SRV);
			pair<Order*, Cook*> servedOrder(normal, normalCook);
			servRest->serving.enqueue(servedOrder);
			servRest->NormalBusyCooks.enqueue(normalCook);
		}
		else if (!servRest->VIP_cooks.isEmpty()) 
		{ 
			pop(servRest, normal);
			int waitTime = timeStep - normal->getArrTime();
			normal->set_Order_Wait_TimeStep(waitTime);
			servRest->VIP_cooks.dequeue(normalCook);
			int serviceTime = int(normal->GetDishes() / normalCook->GetSpeed());
			normal->set_Order_ServTime_TimeStep(serviceTime);
			normal->setStatus(SRV);
			pair<Order*, Cook*> servedOrder(normal, normalCook);
			servRest->serving.enqueue(servedOrder);
			servRest->VipBusyCooks.enqueue(normalCook);
		}
	}
	
}

void NormalOrder::prioritize(Restaurant * servRest, int timeStep)
{
	if (!servRest->NormalOrdersWaiting.isEmpty()) 
	{
		Order* normal;
		servRest->NormalOrdersWaiting.peekFront(normal);
		if ((timeStep - normal->getArrTime()) > normal->getLimit()) {
			servRest->NormalOrdersWaiting.dequeue(normal);
			int Dishes = normal->GetDishes();
			double totalMoney = normal->getMoney();
			int ArrTime = normal->getArrTime();
			priority = (totalMoney / Dishes) + (100 / ArrTime);
			normal->setType(TYPE_VIP);
			servRest->VipOrdersWaiting.enqueue(normal, priority);
			servRest->PromotedOrders.enqueue(normal);
		}
	}
}
