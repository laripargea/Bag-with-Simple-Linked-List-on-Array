#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c) : bag(c)
{
	//initializam cu head si o frecventa initiala pt next, theta(1)
	currentElement = bag.head;
	if (bag.head != -1)
		f = bag.elems[bag.head].freq;
}

void BagIterator::first() {
	//ca in constructor, theta(1)
	currentElement = bag.head;
	if (bag.head != -1)
		f = bag.elems[bag.head].freq;
}


void BagIterator::next() {
	//daca frecventa nu este 1 next-ul elementului curent ramane elementul de frecventa ori altfel trece la elementul urmator, theta(1) 
	//daca nu e valid aruncam exceptie
	if (valid())
	{
		if (bag.elems[currentElement].freq == 1 || f == 1)
		{
			currentElement = bag.next[currentElement];
			f = bag.elems[currentElement].freq;
		}
		else
			f--;
	}
	else
	{
		exception e;
		throw e;
	}
}


bool BagIterator::valid() const {
	//daca e -1 nu e valid, theta(1)
	if (currentElement == -1)
		return false;
	return true;
}



TElem BagIterator::getCurrent() const
{
	//valoarea de pe pozitia curenta, theta(1)
	//daca nu e valid aruncam exceptie
	if (valid())
	{
		TElem e = bag.elems[currentElement].val;
		return e;
	}
	else
	{
		exception e;
		throw e;
	}
}
