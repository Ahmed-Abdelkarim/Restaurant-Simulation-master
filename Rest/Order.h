#pragma once
#include "..\Defs.h"
class Restaurant;
class Order
{

protected:
	int ID;         //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		//order type: Normal, Vegan, VIP
	ORD_STATUS status;	//waiting, in-service, done
	int Dishes;	//The number of dishes in that order 	                
	double totalMoney;	//Total order money
	int ArrTime = 0, ServTime = 0,WaitTime = 0, FinishTime = 0;	//arrival, service start, and finish times
	int limit;
	//
	// TODO: Add More Data Members As Needed
	//

public:
	Order();
	Order(int D);
	Order(int ID, ORD_TYPE r_Type);
	virtual ~Order();
	void setMoney(double money);
	void setLimit(int l);
	void set_Order_Arrival_TimeStep(int tim);
	void set_Order_Wait_TimeStep(int tim);
	void set_Order_ServTime_TimeStep(int tim);
	double getMoney();
	int getLimit();
	int getArrTime();
	int getServTime();
	int getWaitTime();
	int getFinishTime();
	int GetID() const;

	void setType(ORD_TYPE t);
	ORD_TYPE GetType() const;

	void SetDishes(int d);
	int GetDishes() const;

	void setStatus(ORD_STATUS s);
	ORD_STATUS getStatus() const;
	
	//
	// TODO: Add More Member Functions As Needed
	//
};
