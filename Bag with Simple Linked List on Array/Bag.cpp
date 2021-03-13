#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {
	//initializam toate necesare pt slla
	//best theta(n), worst theta(n), average theta(n) -> theta(n) (pt ca avem for)
	cap = 99999; //i-am dat o capacitate mare ca nu imi merge realocarea
	elems = new elem[cap];
	next = new int[cap];
	head = -1;
	for (int i = 0; i < cap - 1; i++)
		next[i] = i + 1;
	next[cap - 1] = -1;
	firstEmpty = 0;
}


void Bag::add(TElem e) {
	//prima data verificam daca depaseste capacitatea si o dublam daca da folosind 2 array-uri auxiliare
	//pornim cu un current de la head si cautam elementul iar daca il gasim ii crestem frecventa
	//altfel il adaugam la inceput cu frecventa 1
	//best theta(1)-daca il gasim si e primul, worst theta(n)-dublam capacitatea sau e ultimul, average theta(n) -> O(n)
	if (firstEmpty == -1)
	{
		elem* newElems = new elem[cap * 2];
		int* newNext = new int[cap * 2];
		for (int i = 0; i < cap; i++)
		{
			newElems[i] = elems[i];
			newNext[i] = next[i];
		}
		for (int i = cap - 1; i < cap * 2 - 1; i++)
			newNext[i] = i + 1;
		newNext[cap * 2 - 1] = -1;
		elems = newElems;
		next = newNext;
		delete[] newElems;
		delete[] newNext;
		firstEmpty = cap;
		cap = cap * 2;
	}
	int current = head;
	while (current != -1 && elems[current].val != e)
		current = next[current];
	if (elems[current].val == e && current != -1)
		elems[current].freq++;
	else
	{
		int newPosition = firstEmpty;
		elems[newPosition].val = e;
		elems[newPosition].freq = 1;
		firstEmpty = next[firstEmpty];
		next[newPosition] = head;
		head = newPosition;
	}
}

bool Bag::remove(TElem elem) {
	//pornim cu un current de la head si cautam elementul iar daca il gasim ii scadem frecventa daca e mai mare ca 1
	//altfel il stergem
	//best theta(1)-primul, worst theta(n)-ultimul sau nu-l gasim, average theta(n) -> O(n)
	int nodC = head;
	int prevNode = -1;
	while (nodC != -1 && elems[nodC].val != elem)
	{
		prevNode = nodC;
		nodC = next[nodC];
	}
	if (nodC != -1)
	{
		if (elems[nodC].freq > 1)
			elems[nodC].freq--;
		else
		{
			if (nodC == head)
				head = next[head];
			else
				next[prevNode] = next[nodC];
			next[nodC] = firstEmpty;
			firstEmpty = nodC;
		}
	}
	else
		return false;
	return true;
}


bool Bag::search(TElem elem) const {
	//pornim cu un current de la head si cautam elementul, search ne da pozitia, daca il gasim returnam adevarat altfel fals
	//best theta(1), worst theta(n), average theta(n) -> O(n)
	int current = head, search = -1;
	while (current != -1 && elems[current].val != elem)
		current = next[current];
	search = current;
	if (search != -1)
		return true;
	return false;
}

int Bag::nrOccurrences(TElem elem) const {
	//pornim cu un current de la head si cautam elementul, daca il gasim ii returnam frecventa altfel 0
	//best theta(1), worst theta(n), average theta(n) -> O(n)
	int current = head, nr = 0;
	while (current != -1 && elems[current].val != elem)
		current = next[current];
	if (current == -1)
		return 0;
	else if (elems[current].val == elem)
		nr = elems[current].freq;
	return nr;
}


int Bag::size() const {
	//pornim cu un current de la head si adunam frecventele elementelor pe rand
	//best theta(n), worst theta(n), average theta(n) -> theta(n) 
	int current = head, s = 0;
	while (current != -1)
	{
		s += elems[current].freq;
		current = next[current];
	}
	return s;
}


bool Bag::isEmpty() const {
	//daca head e -1 nu are niciun element, theta(1)
	if (head == -1)
		return true;
	return false;
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}

void Bag::durchschnitt(Bag b2, Bag b3)
{
	//parcurgem cele 2 bag-uri, comparam fiecare element din primul cu fiecare element din al doilea
	//formam un al treilea bag unde se vor afla elementele comune din bag 1 si 2 o singura data la frecventa cea mai mica
	//best theta(n), worst theta(n), average theta(n) -> theta(n) pt while in while
	int head2 = b2.head, curr1 = head, curr2 = head2;
	while (curr1 != -1)
	{
		while (curr2 != -1)
		{
			if (curr1 == curr2)
			{
				int newPosition = b3.firstEmpty;
				b3.elems[newPosition].val = elems[curr1].val;
				if (elems[curr1].freq > b2.elems[curr2].freq)
					b3.elems[newPosition].freq = elems[curr1].freq - b2.elems[curr2].freq;
				else if (elems[curr1].freq == b2.elems[curr2].freq)
					b3.elems[newPosition].freq = elems[curr1].freq;
				else
					b3.elems[newPosition].freq = b2.elems[curr2].freq - elems[curr1].freq;
				b3.firstEmpty = b3.next[b3.firstEmpty];
				b3.next[newPosition] = b3.head;
				b3.head = newPosition;
			}
			curr2 = b2.next[curr2];
		}
		curr2 = head2;
		curr1 = next[curr1];
	}
}

Bag::~Bag() {
	//dealocam spatiul pt cele 2 array-uri, O(1)
	delete[] elems;
	delete[] next;
}
