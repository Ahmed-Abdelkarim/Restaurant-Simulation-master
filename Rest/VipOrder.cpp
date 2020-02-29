#include "VipOrder.h"
#include "Restaurant.h"
VipOrder::VipOrder()
{

}
void VipOrder::push(Restaurant * servRest, Order* ord)
{
	int Dishes = ord->GetDishes();
	double totalMoney = ord->getMoney();
	int ArrTime = ord->getArrTime();

	priority = (totalMoney / Dishes) + (100 / ArrTime);
	servRest->VipOrdersWaiting.enqueue(ord, priority);
}

inline void VipOrder::pop(Restaurant * servRest, Order*&ord)
{
	servRest->VipOrdersWaiting.dequeue(ord);
}

void VipOrder::excute(Restaurant * servRest, int timeStep)
{
	if (!servRest->VipOrders.isEmpty()) {
		Order *vip;
		servRest->VipOrders.peekFront(vip);
		if (vip->getArrTime() > timeStep)
			return;
		if (servRest->VIP_cooks.isEmpty()) {
			if (servRest->Normal_cooks.isEmpty()) {
				servRest->VipOrders.dequeue(vip);
				vip->setStatus(WAIT);
				push(servRest, vip);
			}
			else {
				if (!servRest->VipOrdersWaiting.isEmpty()) {
					pop(servRest, vip);
					int waitTime = timeStep - vip->getArrTime();
					vip->set_Order_Wait_TimeStep(waitTime);
				}
				else
					servRest->VipOrders.dequeue(vip);
				Cook *NormalCook;
				servRest->Normal_cooks.dequeue(NormalCook);
				int serviceTime = int(vip->GetDishes() / NormalCook->GetSpeed());
				vip->set_Order_ServTime_TimeStep(serviceTime);
				vip->setStatus(SRV);
				pair<Order*, Cook*> servedOrder(vip, NormalCook);
				servRest->VipServing.enqueue(servedOrder);
				servRest->NormalBusyCooks.enqueue(NormalCook);
			}
		}
		else {
			if (!servRest->VipOrdersWaiting.isEmpty()) {
				pop(servRest, vip);
				int waitTime = timeStep - vip->getArrTime();
				vip->set_Order_Wait_TimeStep(waitTime);
			}
			else
				servRest->VipOrders.dequeue(vip);
			Cook *vipCook;
			servRest->VIP_cooks.dequeue(vipCook);
			int serviceTime = int(vip->GetDishes() / vipCook->GetSpeed());
			vip->set_Order_ServTime_TimeStep(serviceTime);
			vip->setStatus(SRV);
			pair<Order*, Cook*> servedOrder(vip, vipCook);
			servRest->VipServing.enqueue(servedOrder);
			servRest->VipBusyCooks.enqueue(vipCook);
		}
	}
	if (!servRest->VipOrdersWaiting.isEmpty()) {
		Order *vip;
		Cook *vipCook;
		if (!servRest->VIP_cooks.isEmpty()) {
			pop(servRest, vip);
			int waitTime = timeStep - vip->getArrTime();
			vip->set_Order_Wait_TimeStep(waitTime);
			servRest->VIP_cooks.dequeue(vipCook);
			int serviceTime = int(vip->GetDishes() / vipCook->GetSpeed());
			vip->set_Order_ServTime_TimeStep(serviceTime);
			vip->setStatus(SRV);
			pair<Order*, Cook*> servedOrder(vip, vipCook);
			servRest->VipServing.enqueue(servedOrder);
			servRest->VipBusyCooks.enqueue(vipCook);
		}
		else if (!servRest->Normal_cooks.isEmpty())
		{
			pop(servRest, vip);
			int waitTime = timeStep - vip->getArrTime();
			vip->set_Order_Wait_TimeStep(waitTime);
			servRest->Normal_cooks.dequeue(vipCook);
			int serviceTime = int(vip->GetDishes() / vipCook->GetSpeed());
			vip->set_Order_ServTime_TimeStep(serviceTime);
			vip->setStatus(SRV);
			pair<Order*, Cook*> servedOrder(vip, vipCook);
			servRest->VipServing.enqueue(servedOrder);
			servRest->NormalBusyCooks.enqueue(vipCook);
		}

	}
	
}
