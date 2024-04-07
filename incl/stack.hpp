#ifndef STACK_HPP
#define STACK_HPP
#include <vector>
#include <iterator>

template <typename T>
class Stack{

	private:
		std::vector<T> data;	
	public:
		Stack(){}
		size_t getSize()      {return data.size();}
		void   push(T element){data.push_back(element);}
		T&     top()          {return data.top();}
		T      pop()          {
			T return_val = data.front();
			data.pop_back();
			return return_val;
		}
		bool   isEmpty()      {return (data.size() == 0);}

		std::string toString(){
			if (this->isEmpty()){return "[EMPTY]";}
			std::string result = "---";
			// Loop w iterators
			for (auto it = data.end(); it != data.begin(); it++){
				result += *it + "---\n";
			}
			return result;
		}


};
#endif
