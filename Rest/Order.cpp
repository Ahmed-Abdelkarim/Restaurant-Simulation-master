#include "Order.h"

Order::Order()
{
}


Order::Order(int D)
{
	ID = D;
}

Order::Order(int id, ORD_TYPE r_Type)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	status = WAIT;
}

Order::~Order()
{
}

int Order::GetID() const
{
	return ID;
}


void Order::setType(ORD_TYPE t)
{
	type = t;
}

ORD_TYPE Order::GetType() const
{
	return type;
}


void Order::SetDishes(int d)
{
	Dishes = d>0?d:0;
}

int Order::GetDishes() const
{
	return Dishes;
}


void Order::setStatus(ORD_STATUS s)
{
	status = s;
}

void Order::setMoney(double money) { //setter function that assigns the order paid money
	totalMoney = money;
}

void Order::setLimit(int l)
{
	limit = l;
}

void Order::set_Order_Arrival_TimeStep(int tim) {
	ArrTime = tim;
}

void Order::set_Order_Wait_TimeStep(int tim)
{
	WaitTime = tim;
}

void Order::set_Order_ServTime_TimeStep(int tim)
{
	ServTime = tim;
}

ORD_STATUS Order::getStatus() const
{
	return status;
}
double Order::getMoney() { //setter function that assigns the order paid money
	return totalMoney;
}
int Order::getLimit()
{
	return limit;
}
int Order::getArrTime() { //setter function that assigns the order paid money
	return ArrTime;
}

int Order::getServTime()
{
	return ServTime;
}

int Order::getWaitTime()
{
	return WaitTime;
}

int Order::getFinishTime()
{
	return FinishTime;
}
bool operator==(Order const &a, Order const &b) {
	if (a.GetID() == b.GetID()) return true;
	return false;

}