#include "VeganOrder.h"
#include "Restaurant.h"
VeganOrder::VeganOrder()
{

}
void VeganOrder::push(Restaurant * servRest, Order* ord)
{
	servRest->VeganOrdersWaiting.enqueue(ord);
}

void VeganOrder::pop(Restaurant * servRest, Order*&ord)
{
	servRest->VeganOrdersWaiting.dequeue(ord);
}

void VeganOrder::excute(Restaurant * servRest, int timeStep)
{
	if (!servRest->VeganOrders.isEmpty()) {
		Order *vegan;
		servRest->VeganOrders.peekFront(vegan);
		if (vegan->getArrTime() > timeStep)
			return;
		if (servRest->Vegan_cooks.isEmpty()) {
			servRest->VeganOrders.dequeue(vegan);
			vegan->setStatus(WAIT);
			push(servRest, vegan);
		}
		else {
			if (!servRest->VeganOrdersWaiting.isEmpty()) {
				pop(servRest, vegan);
				int waitTime = timeStep - vegan->getArrTime();
				vegan->set_Order_Wait_TimeStep(waitTime);
			}
			else
				servRest->VeganOrders.dequeue(vegan);
			Cook *veganCook;
			servRest->Vegan_cooks.dequeue(veganCook);
			int serviceTime = int(vegan->GetDishes() / veganCook->GetSpeed());
			vegan->set_Order_ServTime_TimeStep(serviceTime);
			vegan->setStatus(SRV);
			pair<Order*, Cook*> servedOrder(vegan, veganCook);
			servRest->serving.enqueue(servedOrder);
			servRest->VeganBusyCooks.enqueue(veganCook);
		}
	}
	if (!servRest->VeganOrdersWaiting.isEmpty() && !servRest->Vegan_cooks.isEmpty()) {

		Order *vegan;
		pop(servRest, vegan);
		int waitTime = timeStep - vegan->getArrTime();
		vegan->set_Order_Wait_TimeStep(waitTime);
		Cook *veganCook;
		servRest->Vegan_cooks.dequeue(veganCook);
		int serviceTime = int(vegan->GetDishes() / veganCook->GetSpeed());
		vegan->set_Order_ServTime_TimeStep(serviceTime);
		vegan->setStatus(SRV);
		pair<Order*, Cook*> servedOrder(vegan, veganCook);
		servRest->serving.enqueue(servedOrder);
		servRest->VeganBusyCooks.enqueue(veganCook);
	}
}
