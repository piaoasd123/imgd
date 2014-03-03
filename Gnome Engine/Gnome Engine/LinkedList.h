#pragma once

#include <stdio.h>

#define forEach(type, ptr, start) for(Link<type>* ptr = start; ptr != nullptr; ptr = ptr->next)

template<class Content> struct Link
{
	Content* first;
	Link<Content>* next;
};

template <class Content> class LinkedList
{
public:
	LinkedList(void);
	virtual ~LinkedList(void);
	void insert(Content* obj);
	void remove(Content* obj);
	Link<Content>* getFirst();
	void freeAll(void); //make sure all objects in list were newed!
	LinkedList<Content>* copyList(); //creates a duplicate list pointing to all the same items
private:
	Link<Content>* first;
};

template<class Content> LinkedList<Content>::LinkedList(void)
{
	first = nullptr;
}


template<class Content> LinkedList<Content>::~LinkedList(void)
{
	Link<Content>* last;
	if(first != nullptr)
	{
		for(Link<Content>* ptr = first; ptr->next != nullptr; ptr)
		{
			last = ptr->next;
			delete ptr;
			ptr = last;
		}
	}
	delete first;
}

template<class Content> void LinkedList<Content>::insert(Content* obj)
{
	Link<Content>* in = new Link<Content>();
	in->first = obj;
	in->next = first;
	first = in;
}

template<class Content> void LinkedList<Content>::remove(Content* obj)
{
	Link<Content>** last = &first;
	forEach(Content, ptr, first)
	{
		if(ptr->first == obj)
		{
			*last = ptr->next;
			delete ptr;
			break;
		}
		else
		{
			last = &(ptr->next);
		}
	}
}

template<class Content> void LinkedList<Content>::freeAll(void)
{
	Link<Content>* last;
	for(Link<Content>* ptr = first; ptr != nullptr; ptr)
	{
		delete ptr->first;
		last = ptr->next;
		delete ptr;
		ptr = last;
	}
	first = nullptr;
}

//doublecheck this function
template<class Content> LinkedList<Content>* LinkedList<Content>::copyList(void)
{
	LinkedList<Content>* dupList = new LinkedList<Content>();
	Link<Content>* nextToDup = first;
	Link<Content>** nextToPutDup = &(dupList->first);
	while(nextToDup != nullptr)
	{
		*nextToPutDup = new Link<Content>;
		(*nextToPutDup)->first = nextToDup->first;
		//(*nextToPutDup)->next = nullptr; //this line is redundant
		nextToPutDup = &((*nextToPutDup)->next);
		nextToDup = nextToDup->next;
	}
	*nextToPutDup = nullptr;
	return dupList;
}

template<class Content> Link<Content>* LinkedList<Content>::getFirst()
{
	return first;
}