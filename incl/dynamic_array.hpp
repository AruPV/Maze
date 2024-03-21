// SOURCES:
// CPython's List implementation: https://github.com/python/cpython/blob/main/Include/listobject.h
// 								  https://github.com/python/cpython/blob/main/Include/listobject.c
// NOTES:
//
// I made the decision to zero-initialize the array if no values are passed. I 
// could have (and for a second thought about) using options instead (a datatype
// included in c++17), but I decided against it because I decided to not let 
// users interact with the uninitialized elements of the array.
//
// I also decided to implement this with keywords similar to those that the
// vector class uses, but I did not copy its implementation (or, like, I 
// didn't look at it so if it's similar it's not intentional!!).
//
// One final thing, I decided to hold the array like a c-style array instead
// of an std::array because i wanted to force myself to work with pointers thought
// I know it is probably a better idea to just use std::array in an actual implementation
// of dynamic arrays!

#include <cstddef>					// For size_t
#include <array>
#include <ios>
#include <string>
#include <map>
#include <functional>
#include <iostream>
#include <ranges>

template<typename T>
class DynamicArray{

	private:
		static int 		resize_count;
		static int 		copies;
		static int 		(*resize_operation)(int);
		static float 	resize_factor;
		static bool		logs;

		static int 		add(int);
		static int 		mult(int);
		static void 	resetStats();
		
		T* 		array;			
		int 	next_i;
		size_t 	capacity;

		void resize(){		
			// Allocate new memory in heap
			T* new_array = new T[resize_operation(capacity)];
			for (int i : std::views::iota(0, int(capacity))){
				new_array[i] = array[i];
			}
			delete[] array; 	// ptr is now dangling
			array = new_array;  // ptr reassigned to new array location 
			capacity = resize_operation(capacity);
		}

	public:
		static void toggleLogs(){
			logs = !logs;
		}

		std::map<std::string,int> getStatsMap(){
			std::map<std::string,int> return_map;
			return_map["Resizes"] = resize_count;
			return_map["Copies"] = copies;
			return return_map;
		}

		DynamicArray(): 
			capacity {0}{
			// Default constructor.
			array = new T[1];
			next_i = 0;
		}

		template<int array_length>
		DynamicArray(std::array<int, array_length> i_array)
			: capacity {array_length}{
			array = new T[array_length];
			next_i = 0;
		}

		~DynamicArray(){
			delete[] array;
		}

		int getSize(){
			return (next_i);
		}

		int getCapacity(){
			return (capacity);
		}

		void append(T new_value){
			if (capacity == 0 ){
				capacity = 1;
			} else if (capacity <= next_i){
				this->resize();
				if (logs) {std::cout << "array resized to: " << capacity << "\n";}
				resize_count += 1;
			}
			array[next_i] = new_value;
			next_i += 1;
			return;
		}

		T& operator[](size_t index){
			if (index >= next_i){
				throw std::out_of_range("Index out of bounds");
			}
			return array[index];
		}

		std::string toString(){
			if (next_i == 0){
				return "[]";
			}
			std::string return_str = "[ ";
			// Range object implemented in c++20.
			for (int i : std::views::iota(0, (next_i))){
				return_str.append(std::to_string(array[i]) + " | ");
				copies += 1;
			}
			return_str.resize(return_str.size() - 2);
			return_str += "]";
			return return_str;
		}

		void modifyResize(int (*new_func)(int), float new_factor){
			resize_operation = new_func; 
			resize_factor = new_factor;
		}

		T top(){
			return array[next_i-1];
		}

		void push(T element){
			this->append(element);	
		}

		T pop(){
			T top_element = array[next_i-1]; 
			next_i = next_i -1;
		}

};

// INITIALIZE STATIC MEMBERS AND METHODS
template<typename T>
int 	DynamicArray<T>::resize_count = 0;
template<typename T>
int 	DynamicArray<T>::copies = 0;
template<typename T>
int 	(*DynamicArray<T>::resize_operation)(int) = DynamicArray::mult;
template<typename T>
float 	DynamicArray<T>::resize_factor = 2;
template<typename T>
bool 	DynamicArray<T>::logs = false;

template<typename T>
int DynamicArray<T>::mult(int capacity){
	return (capacity * resize_factor);
}

template<typename T>
int DynamicArray<T>::add(int capacity){
	return (capacity + resize_factor);
}

template<typename T>
void DynamicArray<T>::resetStats(){
}

// Template specialization for toString, given that it to_string does not take 
// std::string
template<>
inline std::string DynamicArray<std::string>::toString(){
	if (next_i == 0){
		return "[]";
	}
	std::string return_str = "[ ";
	// Range object implemented in c++20.
	for (int i : std::views::iota(0, (next_i))){
		return_str.append(array[i] + " | ");
		copies += 1;
	}
	return_str.resize(return_str.size() - 2);
	return_str += "]";
	return return_str;
}
