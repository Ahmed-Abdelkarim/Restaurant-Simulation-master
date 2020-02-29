#pragma once
#include "Order.h"
class NormalOrder
{
public:
	NormalOrder();
	void push(Restaurant * servRest, Order* ord);
	void pop(Restaurant * servRest, Order *&ord);
	void excute(Restaurant * servRest, int timeStep);
	void prioritize(Restaurant * servRest, int timeStep);
private:
	double priority;
};
