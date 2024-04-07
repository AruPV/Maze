#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "linked-lists.hpp"

template <typename T>
class Queue{
	private:
		LinkedList<T> list;

	public:
		void push(T element){list.addRight(element);}
		T pop()             {return list.removeRight();}
		T& top()            {return list.getHead();}
		bool is_empty()     {return list.isEmpty();}
		int size()          {return list.getSize();}

};
#endif
