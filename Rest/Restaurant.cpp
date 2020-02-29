#include <cstdlib>
#include <time.h>
#include <iostream>
#include <fstream>
#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include "..\Events\CancelEvent.h"
#include "..\Events\PromoEvent.h"
#include"NormalOrder.h"
#include"VipOrder.h"
#include"VeganOrder.h"

Restaurant::Restaurant()
{
	pGUI = NULL;
	pOrder = new VipOrder;
	nOrder = new NormalOrder;
	vOrder = new VeganOrder;
}
void Restaurant::LoadData(Restaurant*pRest) {
	int SN = 0, SG = 0, SV = 0;
	int N = 0, G = 0, V = 0;
	int BM = 0, BN = 0, BG = 0, BV = 0;
	int AutoS = 0;
	int M = 0;
	int L = 0;
	char eventLetter;
	char TYPE;
	ORD_TYPE R_TYP;
	int R_eTS,R_oID,R_oSIZE;
	double R_oMONEY;
	double ExMony;
	int X_eTS, X_oID;
	int pTS, P_oID;
	std::ifstream newfile;
	newfile.open("test6.txt", std::ios::in);
	if (newfile.is_open()) {   //checking whether the file is open

		newfile >> SN >> SG >> SV >> N >> G >> V >> BM >> BN >> BG >> BV >> AutoS >> M;
		for (int i = 0; i < N; i++) {
			Cook* current_cook = new Cook;
			current_cook->setID(i+1);
			current_cook->setType(TYPE_NRM);
			current_cook->setSpeed(SN);
			current_cook->BNorm = BN;
			current_cook->limit = BM;
			pRest->Normal_cooks.enqueue(current_cook);
			//delete current_cook;

		}
		for (int i = 0; i < G; i++) {
			Cook* current_cook = new Cook;
			current_cook->setID(i+1);
			current_cook->setType(TYPE_VEG);
			current_cook->setSpeed(SG);
			current_cook->BVegan = BG;
			current_cook->limit = BM;
			pRest->Vegan_cooks.enqueue(current_cook);
			//delete current_cook;

		}
		for (int i = 0; i < V; i++) {
			Cook* current_cook = new Cook;
			current_cook->setID(i+1);
			current_cook->setType(TYPE_VIP);
			current_cook->setSpeed(SV);
			current_cook->BVip = BV;
			current_cook->limit = BM;
			pRest->VIP_cooks.enqueue(current_cook);
			//delete current_cook;
		}
		for (int i = 0; i < M; i++) {
			newfile >> eventLetter;
			switch (eventLetter) {
			case 'R': {
				newfile >> TYPE >> R_eTS >> R_oID >> R_oSIZE >> R_oMONEY;
				switch (TYPE)
				{
				case 'N':
					R_TYP = TYPE_NRM;// Assigns the order type
					L = AutoS;
					break;

				case 'G':
					R_TYP = TYPE_VEG;
					break;

				case 'V':
					R_TYP = TYPE_VIP;
					break;
				}

				ArrivalEvent* ev = new ArrivalEvent(R_eTS, R_oID, R_TYP, R_oSIZE, R_oMONEY,L);
				EventsQueue.enqueue(ev);
				//delete ev;
				 }
			break;
			case 'X': {
				newfile >> X_eTS >> X_oID;
				CancelEvent *cev = new CancelEvent(X_eTS, X_oID);
				EventsQueue.enqueue(cev);
				//delete cev;
			}break;
			case 'P':
				newfile >> pTS >> P_oID >> ExMony;
				PromoEvent* P_cev = new PromoEvent(pTS, P_oID, ExMony);
				EventsQueue.enqueue(P_cev);
			}
		}
	}

}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE mode = pGUI->getProgramMode();
	// If you want to use the simulation GUI you must call initSimMode() same as the demo mode
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR+1:
		IntrMode();
		break;
	case MODE_STEP+1:
		StepMode();
		break;
	case MODE_SLNT+1:
		SilentMode();
		break;
	case MODE_DEMO+1:
		pGUI->initSimMode();
		break;
	};

}

void Restaurant::SilentMode()
{
	LoadData(this);
	int steps = 1;
	while (steps <100) {
		ExecuteEvents(steps);
		ExecuteOrders(steps);
		CookOrders(steps);
		steps++;
	}
	std::ofstream outputfile;
	outputfile.open("output6.txt", std::ios::out);
	outputfile << "FT\t" << "ID\t" << "AT\t" << "WT\t" << "ST" << "\n";


	double temp_count_norm = NormalServiced.getCount();
	double temp_count_veg = VeganServiced.getCount();
	double temp_count_VIP = VipServiced.getCount();


	int FT = 0; int WT = 0; int ST = 0; int AT = 0;

	double sum_ST_norm = 0; double sum_WT_norm = 0;
	double sum_ST_veg = 0; double sum_WT_veg = 0;
	double sum_ST_VIP = 0; double sum_WT_VIP = 0;

	double count_WT_ST_norm = 0; double count_WT_ST_veg = 0; double count_WT_ST_VIP = 0;
	// print table output test

	/*cout << "Start output file test " << endl;
	*/
	for (int i = 0; i < temp_count_norm; i++) {
		ST = NormalServiced.PrintKth(i)->getServTime();
		WT = NormalServiced.PrintKth(i)->getWaitTime();
		AT = NormalServiced.PrintKth(i)->getArrTime();
		FT = ST + WT + AT;
		outputfile << FT << "\t";
		outputfile << NormalServiced.PrintKth(i)->GetID() << "\t";
		outputfile << AT << "\t";
		outputfile << WT << "\t";
		outputfile << ST << "\n";
		sum_ST_norm += ST;
		sum_WT_norm += WT;
	}
	for (int i = 0; i < temp_count_veg; i++) {
		ST = VeganServiced.PrintKth(i)->getServTime();
		WT = VeganServiced.PrintKth(i)->getWaitTime();
		AT = VeganServiced.PrintKth(i)->getArrTime();
		FT = ST + WT + AT;
		outputfile << FT << "\t";
		outputfile << VeganServiced.PrintKth(i)->GetID() << "\t";
		outputfile << AT << "\t";
		outputfile << WT << "\t";
		outputfile << ST << "\n";
		sum_ST_veg += ST;
		sum_WT_veg += WT;
	}
	for (int i = 0; i < temp_count_VIP; i++) {
		ST = VipServiced.PrintKth(i)->getServTime();
		WT = VipServiced.PrintKth(i)->getWaitTime();
		AT = VipServiced.PrintKth(i)->getArrTime();
		FT = ST + WT + AT;
		outputfile << FT << "\t";
		outputfile << VipServiced.PrintKth(i)->GetID() << "\t";
		outputfile << AT << "\t";
		outputfile << WT << "\t";
		outputfile << ST << "\n";
		sum_ST_VIP += ST;
		sum_WT_VIP += WT;
	}


	//calculations:
	int tot_Normal_cooks = 0;
	int tot_VIP_cooks = 0;
	int tot_Veg_cooks = 0;
	tot_Normal_cooks = Normal_cooks.getQueueCount();
	tot_VIP_cooks = VIP_cooks.getQueueCount();
	tot_Veg_cooks = Vegan_cooks.getQueueCount();
	int tot_cooks = tot_Normal_cooks + tot_Veg_cooks + tot_VIP_cooks;
	outputfile << "Cooks: " << tot_cooks << "	[Norm:" << tot_Normal_cooks << ", Veg:" << tot_Veg_cooks <<
		", VIP:" << tot_VIP_cooks << "] \n";
	
	double tot_ords = temp_count_norm + temp_count_veg + temp_count_VIP;
	outputfile << "Orders: " << tot_ords << "	[Normal:" << temp_count_norm << " ,Veg:" << temp_count_veg <<
		", VIP:" << temp_count_VIP << "] \n";

	//AVGs calculations
	double tot_sum_ST = sum_ST_norm + sum_ST_veg + sum_ST_VIP;
	double tot_sum_WT = sum_WT_norm + sum_WT_veg + sum_WT_VIP;
	double tot_count_and_sum_STorWT = temp_count_norm + temp_count_veg + temp_count_VIP;
	double avg_ST = tot_sum_ST / tot_count_and_sum_STorWT;
	double avg_WT = tot_sum_WT / tot_count_and_sum_STorWT;
	outputfile << "AVG Wait = " << avg_WT << ", AVG Serv = " << avg_ST << "\n";
	double perc_promo = (double)PromotedOrders.getQueueCount() / temp_count_norm;
	outputfile << "Auto-promoted: " << perc_promo << "\n";
	outputfile.close();
}

void Restaurant::StepMode()
{
	pGUI->initSimMode();
	int steps = 1;
	LoadData(this);
	while (true) {
		ExecuteEvents(steps);
		ExecuteOrders(steps);
		CookOrders(steps);
		FillDrawingList();
		if (steps % 5 == 0) {
			pGUI->printStringInStatusBar("Current Time: " + std::to_string(steps));
		}
		//pGUI->printStringInStatusBar("Hello from mahmoud Yasser");
		std::string status;
		status = "Simulation Timestep " + std::to_string(steps) + "\n";
		status = status + "Normal waiting = " + std::to_string(NormalOrdersWaiting.getQueueCount()) + "\t";
		status = status + "VIP waiting = " + std::to_string(VipOrdersWaiting.getQueueCount()) + "\t";
		status = status + "Vegan waiting = " + std::to_string(VeganOrdersWaiting.getQueueCount()) + "\n";
		////////
		status = status + "Normal Cooks = " + std::to_string(Normal_cooks.getQueueCount()) + "\t";
		status = status + "VIP Cooks = " + std::to_string(VIP_cooks.getQueueCount()) + "\t";
		status = status + "Vegan Cooks = " + std::to_string(Vegan_cooks.getQueueCount()) + "\n";
		//////
		int totalO = VipServiced.getCount() + VeganServiced.getCount() + NormalServiced.getCount();
		status = status + "Orders Served = " + std::to_string(totalO) + "\n";
		pGUI->printStringInStatusBar(status);
		pGUI->updateInterface();
		pGUI->handleSimGUIEvents();
		// For Interactive mode
		//pGUI->waitForClick();
		// For step-by-step mode
		pGUI->sleep(1000);
		steps++;
	}
}

void Restaurant::IntrMode()
{
	pGUI->initSimMode();
	LoadData(this);
	int steps = 1;
	while (true) {
		ExecuteEvents(steps);
		ExecuteOrders(steps);
		CookOrders(steps);
		FillDrawingList();
		if (steps % 5 == 0) {
			pGUI->printStringInStatusBar("Current Time: " + std::to_string(steps));
		}
		//pGUI->printStringInStatusBar("Hello from mahmoud Yasser");
		std::string status;
		status = "Simulation Timestep " + std::to_string(steps) + "\n";
		status = status + "Normal waiting = " + std::to_string(NormalOrdersWaiting.getQueueCount()) + "\t";
		status = status + "VIP waiting = " + std::to_string(VipOrdersWaiting.getQueueCount()) + "\t";
		status = status + "Vegan waiting = " + std::to_string(VeganOrdersWaiting.getQueueCount()) + "\n";
		////////
		status = status + "Normal Cooks = " + std::to_string(Normal_cooks.getQueueCount()) + "\t";
		status = status + "VIP Cooks = " + std::to_string(VIP_cooks.getQueueCount()) + "\t";
		status = status + "Vegan Cooks = " + std::to_string(Vegan_cooks.getQueueCount()) + "\n";
		//////
		int totalO = VipServiced.getCount() + VeganServiced.getCount() + NormalServiced.getCount();
		status = status + "Orders Served = " + std::to_string(totalO) + "\n";
		pGUI->printStringInStatusBar(status);
		pGUI->updateInterface();
		pGUI->handleSimGUIEvents();
		// For Interactive mode
		pGUI->waitForClick();
		// For step-by-step mode
		pGUI->sleep(100);
		steps++;
	}
}

//////////////////////////////////  Event handling functions   /////////////////////////////

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep )	//no more events at current time
			return;

		pE->Execute(this,CurrentTimeStep);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}
void Restaurant::ExecuteOrders(int CurrentTimeStep)
{
	
	nOrder->excute(this, CurrentTimeStep);
	nOrder->prioritize(this, CurrentTimeStep);
	pOrder->excute(this, CurrentTimeStep);
	vOrder->excute(this, CurrentTimeStep);
	
}

void Restaurant::CookOrders(int TimeStep)
{
	chef->excuteCooking(this,TimeStep);
	chef->FinishBreak(this, TimeStep);
	
}


Restaurant::~Restaurant()
{
		delete pGUI;
}


void Restaurant::FillDrawingList()
{
	//This function should be implemented in phase1
	//It should add ALL orders and cooks to the drawing list
	//It should get orders from orders lists/queues/stacks/whatever (same for cooks)
	// drawing all cooks
	int Ncount;
	Cook **NormalCooks = Normal_cooks.toArray(Ncount);
	for (int i = 0; i < Ncount;i++) {
		pGUI->addGUIDrawable(new NormalGUIElement(NormalCooks[i]->GetID(), GUI_REGION::COOK_REG));
	}

	int Vcount;
	Cook **VIPcooks = VIP_cooks.toArray(Vcount);
	for (int i = 0; i < Vcount; i++) {
		pGUI->addGUIDrawable(new VIPGUIElement(VIPcooks[i]->GetID(), GUI_REGION::COOK_REG));
	}

	int Gcount;
	Cook **veganCooks = Vegan_cooks.toArray(Gcount);
	for (int i = 0; i < Gcount; i++) {
		pGUI->addGUIDrawable(new VeganGUIElement(veganCooks[i]->GetID(), GUI_REGION::COOK_REG));
	}
	///////////////////////////////////////////////////////////////////////////////////////////////
	//drawing all waiting Orderss
	int Nwaits;
	Order **NOrders = NormalOrdersWaiting.toArray(Nwaits);
	for (int i = 0; i < Nwaits; i++) {
		pGUI->addGUIDrawable(new NormalGUIElement(NOrders[i]->GetID(), GUI_REGION::ORD_REG));
	}

	int Vwaits;
	Order **VOrders = VipOrdersWaiting.toArray(Vwaits);
	for (int i = 0; i < Vwaits; i++) {
		pGUI->addGUIDrawable(new VIPGUIElement(VOrders[i]->GetID(), GUI_REGION::ORD_REG));
	}

	int Gwaits;
	Order **GOrders = VeganOrdersWaiting.toArray(Gwaits);
	for (int i = 0; i < Gwaits; i++) {
		pGUI->addGUIDrawable(new VeganGUIElement(GOrders[i]->GetID(), GUI_REGION::ORD_REG));
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////
	// draw all serving Orders.
	int sevs;
	pair<Order*,Cook *>*servings = serving.toArray(sevs);
	for (int i = 0; i < sevs; i++) {
		if(servings[i].first->GetType() == TYPE_NRM)
			pGUI->addGUIDrawable(new NormalGUIElement(servings[i].first->GetID(), GUI_REGION::SRV_REG));
		else
			pGUI->addGUIDrawable(new VeganGUIElement(servings[i].first->GetID(), GUI_REGION::SRV_REG));
	}
	int vservs;
	pair<Order*, Cook *>*vservings = VipServing.toArray(vservs);
	for (int i = 0; i < vservs; i++) {
		pGUI->addGUIDrawable(new VeganGUIElement(vservings[i].first->GetID(), GUI_REGION::SRV_REG));
	}

	for (int i = 0; i < NormalServiced.getCount(); i++) {
		pGUI->addGUIDrawable(new NormalGUIElement(NormalServiced.PrintKth(i)->GetID(), GUI_REGION::DONE_REG));
	}
	for (int i = 0; i < VipServiced.getCount(); i++) {
		pGUI->addGUIDrawable(new VIPGUIElement(VipServiced.PrintKth(i)->GetID(), GUI_REGION::DONE_REG));
	}
	for (int i = 0; i < VeganServiced.getCount(); i++) {
		pGUI->addGUIDrawable(new VeganGUIElement(VeganServiced.PrintKth(i)->GetID(), GUI_REGION::DONE_REG));
	}
}
