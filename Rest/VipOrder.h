#pragma once
#include "..\Rest\Order.h"
class VipOrder
{
private:
	double priority;
public:
	VipOrder();
	void push(Restaurant * servRest,Order* ord);
	void pop(Restaurant * servRest,Order*&ord);
	void excute(Restaurant * servRest, int timeStep);
};
