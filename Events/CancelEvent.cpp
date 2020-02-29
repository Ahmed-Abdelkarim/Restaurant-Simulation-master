#include "CancelEvent.h"
#include "..\Rest\Restaurant.h"


CancelEvent::CancelEvent(int Cancel_Timestep, int Cancel_ID) : Event(Cancel_Timestep, Cancel_ID) {
	cancel_event_Timestep = Cancel_Timestep;
	cancel_order_ID = Cancel_ID;

}

void CancelEvent::Execute(Restaurant* pRest,int current_time) {
	Order* current_ord = new Order(cancel_order_ID);
	Order* deleted_ord;
	if (!pRest->NormalOrdersWaiting.isEmpty() || !pRest->NormalOrders.isEmpty()) 
	{
		pRest->NormalOrders.dequeue(deleted_ord, current_ord);
		pRest->NormalOrdersWaiting.dequeue(deleted_ord, current_ord);
		delete deleted_ord;
		delete current_ord;
	}
}
