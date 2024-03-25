#ifndef MAZE_CPP
#define MAZE_CPP
#include <ranges>
#include <algorithm>
#include <random>
#include <array> 
#include "cell.hpp"

class Maze {
	private:
		Position start;
		Position goal;
		//Using a vector because c-style arrays and std::arrays need to have a 
		//set size at compile time
		std::vector<Cell> grid;			
		size_t rows;
		size_t cols;
	public:
		Maze
			(Position 	start_pos 			= Position(0,0)
			,Position 	goal_pos 			= Position(9,9)
			,size_t		rows				= 10
			,size_t		cols				= 10
			,bool		debug				= false
			,float		blocked_proportion	= 0.2
			);

		Cell& getCell(int row, int col);

		std::string toString();
};


#endif
