#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"
ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType,int size, double money, int limit):Event(eTime, oID)
{
	OrdType = oType;
	OrderID = oID;
	OrdMoney = money;
	OrdDishes = size;
	Limit = limit;
}

void ArrivalEvent::Execute(Restaurant* pRest, int current_time)
{
	
	//This function should create an order and fills its data 
	Order * current_order = new Order(OrderID, OrdType);
	current_order->SetDishes(OrdDishes);
	current_order->setMoney(OrdMoney);
	current_order->set_Order_Arrival_TimeStep(current_time);
	switch (current_order->GetType())
	{
	case TYPE_NRM:
		current_order->setLimit(Limit);
		pRest->NormalOrders.enqueue(current_order);
		break;
	case TYPE_VEG:
		pRest->VeganOrders.enqueue(current_order);
		break;
	case TYPE_VIP:
		pRest->VipOrders.enqueue(current_order);
		break;
	default:
		break;
	}
	
	//delete current_order;
	// Then adds it to normal, vegan, or VIP order lists that you will create in phase1

}
