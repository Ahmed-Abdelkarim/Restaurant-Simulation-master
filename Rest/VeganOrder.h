#pragma once
#include "..\Rest\Order.h"
class VeganOrder
{
public:
	VeganOrder();
	void push(Restaurant * servRest, Order* ord);
	void pop(Restaurant * servRest, Order *&ord);
	void excute(Restaurant * servRest, int timeStep);

private:

};
