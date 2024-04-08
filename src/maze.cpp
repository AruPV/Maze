#include <ranges>
#include <algorithm>
#include <random>
#include <array> 
#include <iostream>
#include "../incl/queue.hpp"
#include "../incl/stack.hpp"
#include "../incl/maze.hpp"

Maze::Maze
		(Position start_pos
		,Position goal_pos
		,size_t	  rows
		,size_t	  cols
		,bool     debug
		,float    blocked_proportion
		)
		:start (start_pos)
		,goal  (goal_pos)
		,rows  (rows)
		,cols  (cols){

		int blocked_count = floor(rows*cols*blocked_proportion);
		int variable_cell_count = (rows*cols)-2;

		int start_i = start_pos.row * cols + start_pos.col;
		int goal_i  = goal_pos.row  * cols + goal_pos.col;

		//Add all non-start or end cells
		for (int i: std::views::iota(0, (variable_cell_count-1))){
			Contents cell_contents = (i < blocked_count-1)
				? Contents::BLOCKED
				: Contents::EMPTY;
			grid.push_back(Cell(cell_contents));
		}

		// Non-deterministic random device for seed
		std::random_device rd;
		// Merssene Twister from algorithm library. Feed the 
		// non-deterministic device as seed.
		std::mt19937 rng(rd());	
		if (debug){
			rng = std::mt19937(1312);	
		}
		// Shuffle maze
		std::shuffle(std::begin(grid), std::end(grid), rng);
		
		// Add start and goal.
		if (start_i < goal_i){
			grid.insert(grid.begin()+start_i, Cell(Contents::START));
			grid.insert(grid.begin()+goal_i , Cell(Contents::GOAL));
		} else {
			grid.insert(grid.begin()+goal_i , Cell(Contents::GOAL));
			grid.insert(grid.begin()+start_i, Cell(Contents::START));
		}

		// Initialize positions
		for (int row_i: std::views::iota(0, int(rows)-1)){
			for (int col_i: std::views::iota(0, int(cols)-1)){
				grid[(row_i*cols)+col_i].setPosition(row_i,col_i);
			}
		}
	}


Cell& Maze::getCell(int row, int col){
	return grid[(row*cols)+col];
}


size_t Maze::getRows(){return rows;}
size_t Maze::getCols(){return cols;}
size_t Maze::getSize(){return (cols*rows);}

void Maze::pushSearchLocations(Cell* cell, Stack<Cell*>& search_stack){

	std::vector<Cell*> valid_cells;

	//None of these can be references because they're rvalues.
	Position cur_pos   = cell->getPosition();
	//std::cout << "Start Position: " << cur_pos.row << "," << cur_pos.col << "\n";
	Position north_pos = Position(cur_pos.row  , cur_pos.col-1);
	Position south_pos = Position(cur_pos.row  , cur_pos.col+1);
	Position west_pos  = Position(cur_pos.row-1, cur_pos.col);
	Position east_pos  = Position(cur_pos.row+1, cur_pos.col);

	//std::array is a pointer + size. Worth the small memory cost.
	std::array<Position, 4> directions;		
	directions[0] = north_pos;
	directions[1] = south_pos;
	directions[2] = west_pos;
	directions[3] = east_pos;

	for (Position pos: directions){
		if (pos.col < 0 || pos.row < 0){continue;}
		Cell* cur_cell  = &this->getCell(pos.row, pos.col);
		std::cout 
			<< "Current Position:" 
			<< cur_cell->getPosition().row 
			<< "," 
			<< cur_cell->getPosition().col << "\n";
		bool is_path    = cur_cell->getContents() == Contents::PATH; 
		bool is_blocked = cur_cell->getContents() == Contents::BLOCKED; 
		//std::cout << "is_blocked:" << is_blocked << ". is_path:" << is_path << "\n";
		if (is_blocked || is_path){continue;}
		cur_cell->markOnPath();
		cur_cell->setParent(cell);
		std::cout << cur_cell->getPosition().row << "," << cur_cell->getPosition().col << "\n";
		search_stack.push(cur_cell);	
	}
		std::cout << "test";
}


std::optional<Cell*> Maze::dfs(){
	std::optional<Cell*> return_value;
	Stack<Cell*>        search_stack;
	Cell*               cur_cell  = &this->getCell(start.row, start.col);
	Cell*               goal_cell = &this->getCell(goal.row, goal.col);

	while (cur_cell != goal_cell){
		std::cout << search_stack.toString() << "\n";
		this->pushSearchLocations(cur_cell, search_stack);
		std::cout << "test";
		if (search_stack.isEmpty()){break;}
		std::cout << "test";
		cur_cell = search_stack.pop();
	}
	if (cur_cell == goal_cell){return_value = cur_cell;}
	return return_value;
}


//std::optional<Cell> Maze::bfs(){}

std::string Maze::toString(){
	std::cout << "in string";
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
