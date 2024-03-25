#include "../incl/maze.hpp"
Maze::Maze
		(Position 	start_pos
		,Position 	goal_pos
		,size_t		rows
		,size_t		cols
		,bool		debug
		,float		blocked_proportion
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

Cell& Maze::getCell(int row, int col){
	return grid[(row*cols)+col];
}

std::string Maze::toString(){
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
