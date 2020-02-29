#include "PromoEvent.h"

PromoEvent::PromoEvent(int TS, int o_ID, double extra_Money) :Event(TS, o_ID)
{
	PromoTS = TS;
	oID = o_ID;
	extraMoney = extra_Money;
}

void PromoEvent::Execute(Restaurant* pRest,int time)
{
	if (!pRest->NormalOrdersWaiting.isEmpty()) 
	{
		Order* ord = new Order(oID);
		Order* ToVIp;
		pRest->NormalOrdersWaiting.dequeue(ToVIp, ord);
		if (ToVIp != nullptr)
		{
			ToVIp->setType(TYPE_VIP);
			ToVIp->setMoney(ToVIp->getMoney() + extraMoney);
			int Dishes = ToVIp->GetDishes();
			double totalMoney = ToVIp->getMoney();
			int ArrTime = ToVIp->getArrTime();
			double priority = (totalMoney / Dishes) + (100 / ArrTime);
			pRest->VipOrdersWaiting.enqueue(ToVIp, priority);
		}

	}
	
	//pRest->PromotedOrders.enqueue(ToVIp);
	
}