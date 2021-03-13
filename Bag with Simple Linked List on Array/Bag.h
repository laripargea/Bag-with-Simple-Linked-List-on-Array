#pragma once
//DO NOT INCLUDE BAGITERATOR


//DO NOT CHANGE THIS PART
#define NULL_TELEM -11111;
typedef int TElem;
class BagIterator;

struct elem
{
	TElem val;
	int freq;
};

class Bag {

private:
	elem* elems;
	int* next;
	int cap;   //Kapazität der Liste
	int head;
	int	firstEmpty; //gilt als Head für die Liste der leeren Positionen

	//DO NOT CHANGE THIS PART
	friend class BagIterator;
public:
	//constructor
	Bag();

	//adds an element to the bag
	void add(TElem e);

	//removes one occurence of an element from a bag
	//returns true if an eleent was removed, false otherwise (if e was not part of the bag)
	bool remove(TElem e);

	//checks if an element appearch is the bag
	bool search(TElem e) const;

	//returns the number of occurrences for an element in the bag
	int nrOccurrences(TElem e) const;

	//returns the number of elements from the bag
	int size() const;

	//returns an iterator for this bag
	BagIterator iterator() const;

	//checks if the bag is empty
	bool isEmpty() const;

	void durchschnitt(Bag b2, Bag b3);

	//destructor
	~Bag();
};

