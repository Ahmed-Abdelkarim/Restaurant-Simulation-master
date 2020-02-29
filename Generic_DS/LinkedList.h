#ifndef _LINKEDLIST
#define _LINKEDLIST

#include "Node.h"
#include <iostream>
#include <string>

template <typename T>
class LinkedList
{
private:
	Node<T> *Head;	//Pointer to the head of the list
	//You can add tail pointer too (depending on your problem)
	int count;	//Number of nodes in the list
public:


	LinkedList()
	{
		count = 0;
		Head = nullptr;
	}

	//List is being desturcted ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll();
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: PrintList.
	* prints the values of all nodes in a linked list.
	*/
	/*void PrintList()	const
	{
		std::cout<<"\nList has "<<count<<" nodes";
		std::cout<<"\nprinting list contents:\n\n";
		Node<T> *p = Head;

		while(p)
		{
			std::cout << "[ " << p->getItem() << " ]";
			std::cout << "--->";
			p = p->getNext();
		}
		std::cout << "*\n";
	}*/
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: InsertBeg.
	* Creates a new node and adds it to the beginning of a linked list.
	* 
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
	void InsertBeg(const T &data)
	{
		Node<T> *R = new Node<T>(data);
		R->setNext(Head);
		Head = R;
		count++;

	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: DeleteAll.
	* Deletes all nodes of the list.
	*/
	void DeleteAll()
	{
		Node<T> *P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
		count = 0;
	}



	////////////////     Requirements   ///////////////////
	//
	// Implement the following member functions


	//[1]InsertEnd 
	//inserts a new node at end if the list
	void InsertEnd(const T &data){

		if(Head == nullptr){
			InsertBeg(data);
			return;
		}
		else{
			Node<T> *p = Head;
			while(p->getNext()){
				p = p->getNext();
				}
			Node<T> *R = new Node<T>(data);
			p->setNext(R);
			count++;
			return;

		}
		
	}	

	//[2]Find 
	//searches for a given value in the list, returns true if found; false otherwise.
	/*bool Find(int Key){
		Node<T> *p = Head;
		while(p){
			if(p->getItem() == Key){
				std::cout<<"Found the element "<<Key<<std::endl;
				return true;
			}
			p = p->getNext();
		}
		std::cout<<"\nElement "<<Key<<" not found"<<std::endl;
		return false;
	}*/

	//[3]CountOccurance
	//returns how many times a certain value appeared in the list
	int CountOccurance(const T &value){
		int occs = 0;
		Node<T> *p= Head;
		while(p){
			if(p->getItem() == value){
				occs++;
			}
			p = p->getNext();
		}
		return occs;
	}

	//[4] DeleteFirst
	//Deletes the first node in the list
	void DeleteFirst(){
		if(Head){
			Node<T> *p = Head->getNext();
			delete Head;
			Head = p;
			count--;
		}
		return;
	}


	//[5] DeleteLast
	//Deletes the last node in the list
	void DeleteLast(){
		if(Head == nullptr){
			return;
		}
		else if(Head->getNext() == nullptr){
			DeleteFirst();
			return;
		}
		else{
			Node<T> *p = Head;
			Node<T> *q = p->getNext();
			while(q->getNext()){
				p = q;
				q = p->getNext();
			}
			delete q;
			p->setNext(nullptr);
			count--;
			return;
		}
	}

	//[6] DeleteNode
	//deletes the first node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNode(const T &value){
		if(Head == nullptr){
			return false;
		}
		
		if(Head->getItem() == value){
			DeleteFirst();
			return true;
		}
		Node<T> *p = Head;
		Node<T> *q = p->getNext();
		
		while(q){
			if(q->getItem()== value){
				p->setNext(q->getNext());
				delete q;
				count--;
				return true;
			}
			p = q;
			q = p->getNext();
		}
		return false;
	}

	//[7] DeleteNodes
	//deletes ALL node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNodes(const T &value){
		if(Head == nullptr){return false;}
		bool flag = false;
		while(Head->getItem() == value){
			DeleteFirst();
			flag = true;
		}
		Node<T>* p = Head;
		while(p->getNext()){
			if((p->getNext())->getItem() == value){
				Node<T>* R = (p->getNext())->getNext();
				delete p->getNext();
				p->setNext(R);
				flag= true;
				count--;

			}
			else{
				p = p->getNext();
			}
		}
		return flag;
	}

	
	//[8]Merge
	//Merges the current list to another list L by making the last Node in the current list 
	//point to the first Node in list L
	Node<T>* getHead() const{
		return Head;
	}

	int getCount(){
		return count;
	}

	void Merge(const LinkedList& L){
		Node<T> *p = Head;
		if(Head == nullptr){
			Head = L->getHead();
			return;
		}
		while(p->getNext()){
			p = p->getNext();
		}
		p->setNext(L->getHead());
		count = count + L->getCount();
		return;
	}

	//[9] Reverse
	////Reverses the linked list (without allocating any new Nodes)
	//void Reverse(){
	//	cout<<"\nReversing the list"<<endl;
	//	if(Head == nullptr){return;}
	//	Node<T>* p = Head;
	//	Node<T>* nextP = Head->getNext();
	//	Head->setNext(nullptr);
	//	while(nextP){
	//		Node<T>* temp = nextP->getNext();
	//		nextP->setNext(p);
	//		p = nextP;
	//		nextP = temp;
	//	}
	//	Head = p;
	//	return;
	//}
	//[a] printKth 
	// it prints the kth elemen in the list
	T PrintKth(int key)	const
	{
		Node<T> *p = Head;

		if(key <= count)
		{
			for (int i = 1; i <= key; i++) {
				p = p->getNext();
			}
			return p->getItem();
		}
		
	}
	//[b] InsertSorted
	// it inserts data in its correct position in a sorted list
	bool InserSorted(const T &data) {

			Node<T> *p = Head->getNext();
			while ((p->getNext())->getItem() < data) {	
				p = p->getNext();
			}
			if ((p->getNext())->getItem() == data)
				return false;
			Node<T> *R = new Node<T>(data);
			R->setNext(p->getNext());
			p->setNext(R);
			count++;
			return true;

	}
	//[c] RemoveMin
	// removes the minimum data in the list
	bool RemoveMin(Node<T> *M){
		const T &MinValue;
		if (Head == nullptr) {
			return false;
		}

		Node<T> *p = Head->getNext();
		Node<T> *temp = p;
		MinValue = p->getItem();
		while (p) {
			if (p->getItem() < MinValue) {
				MinValue = p->getItem();
			}
			p = p->getNext();
		}
		
		while (p) {
			if (p->getItem() == MinValue) {
				temp->setNext(p->getNext());
				M = p;
				delete p;
				count--;
				p = temp;
				return true;		
			}
			p = p->getNext();
		}
		
		return false;
	}
	//[D]CloneList
	// clones the whole list into a new list
	LinkedList<T> CloneList() 
	{	
		LinkedList<T> clone;
		clone();
		Node<T> *p = Head->getNext();
		while (p)
		{
			clone.InsertEnd(p->getItem());
			p = p->getNext();
		}
		return clone;
	}
	void SignSplit()
	{
		LinkedList<T> Lneg;
		LinkedList<T> Lpos;
		Node<T> *p = Head->getNext();
		while (p)
		{
			Node<T> *q = p;
			if (p->getItem() > 0)
			{
				Lpos.InsertEnd(p->getItem());
				q->setNext(p->getNext());
				delete p;
				p = q;
			}
			if (p->getItem() < 0)
			{
				Lneg.InsertEnd(p->getItem());
				q->setNext(p->getNext());
				delete p;
				p = q;
			}
			p = p->getNext();
		}
	}
	/*void MakeDictionary()
	{
		Node<T> *p = Head->getNext();
		while (p)
		{
			LinkedList<T> Dict;
			string data1 = to_string(p->getItem());
			string data2 = to_string(this->CountOccurance());
			string data = data1 + data2;
			if (!(Dict.Find(data)))
				Dict.InsertEnd(data);
			p = p->getNext();
		}
	}*/
	/*void MergeSorted(const LinkedList &L1, const LinkedList &L2)
	{
		Node<T> *p = L1->Head;
		Node<T> *q = L2->Head;

		if ((p->getNext())->getItem() > (q->getNext())->getItem())
		{
			while (p->getNext()) {
				p = p->getNext();
			}
			p->setNext(L2->getHead());
			return;
		}
		else {
			while (q->getNext()) {
				q = q->getNext();
			}
			p->setNext(L2->getHead());
			return;
		}
		
	}*/
	/*LinkedList SumLists(const LinkedList &L1, const LinkedList &L2)
	{
		if (L1.getCount() != L2.getCount())
			return NULL;
		else 
		{
			Node<T> *p = L1->Head;
			Node<T> *q = L2->Head;
			LinkedList<T> sumList;
			while (p->getNext() && q->getNext())
			{
				sumList.InsertEnd(p->getItem() + q->getItem());
			}
			return sumList;
		}
	}
	void RemoveDuplicates()
	{
		Node<T> *p = Head->getNext;
		while (p)
		{
			Node<T> *q = Head->getNext();
			while (q) {
				if (q->getItem() == p->getItem()) {
					Node<T> *temp = q->getNext;
					delete q;
					count--;
					q->setNext(temp);
				}
				q = q->getNext();
			}
			p = p->getNext();
		}
	}*/
};

#endif	
