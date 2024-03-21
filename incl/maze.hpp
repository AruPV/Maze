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
			)
			:start (start_pos)
			,goal  (goal_pos)
			,rows (rows)
			,cols (cols){

			int blocked_count = floor(rows*cols*blocked_proportion);
			int start_i = start_pos.row * cols + start_pos.col;
			int goal_i = goal_pos.row * cols + goal_pos.col;
			
			int variable_cell_count = (rows*cols)-2;

			//Add all non-start or end cells
			for (int i: std::views::iota(0, (variable_cell_count-1))){
				Contents cell_contents = (i < blocked_count-1)
					? Contents::BLOCKED
					: Contents::EMPTY;
				int cur_row = i%(cols-1);
				int cur_col = i-(cols*cur_row);
				grid.push_back(Cell(Position(cur_row,cur_col), cell_contents));
			}

			// Non-deterministic random device
			std::random_device 	rd;
			// Merssene Twister from algorithm library. Feed the 
			// non-deterministic device as parameter.
			std::mt19937 		rng(rd());	
			// Shuffle maze
			std::shuffle(std::begin(grid), std::end(grid), rng);
			
			// Add start and goal. Relatively expensive when done this way but 
			// it is only done once.
			if (start_i < goal_i){
				grid.insert(grid.begin()+ start_i, Cell(start_pos,Contents::START));
				grid.insert(grid.begin()+ goal_i, Cell(goal_pos,Contents::GOAL));
			} else {
				grid.insert(grid.begin()+ goal_i, Cell(goal_pos,Contents::GOAL));
				grid.insert(grid.begin()+ start_i, Cell(start_pos,Contents::START));
			}

		}

		Cell& getCell(int row, int col){
			return grid[(row*cols)+col];
		}

		std::string toString(){
			std::string return_str; 
			for (int row_i = 0; row_i < rows; row_i++){
				return_str.append("|");
				for (int col_i = 0; col_i < cols; col_i++){
					int cell_i = (row_i * cols) + col_i;
					return_str.append(" " + grid[cell_i].toString() + " |");
				}
				return_str.append("\n");
			}
			return_str.erase(return_str.end()-1, return_str.end());
			return return_str;
		}
};


#endif
