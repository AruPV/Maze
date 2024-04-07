#include <cstdlib>
#include <ranges>
#include <gtest/gtest.h>
#include "../incl/cell.hpp"
#include "../incl/maze.hpp"


class CellTest : public testing::Test {
	protected:
		Cell empty_cell = Cell(Position(0,0), Contents::EMPTY) ;
		Cell start_cell = Cell(Position(0,0), Contents::START) ;
		Cell goal_cell = Cell(Position(0,0), Contents::GOAL) ;
		Cell blocked_cell = Cell(Position(0,0), Contents::BLOCKED) ;
		Cell path_cell = Cell(Position(0,0), Contents::PATH) ;
};

class MazeTest : public testing::Test {
	protected:
		Maze default_maze = Maze(Position(0,0), Position(9,9), 10, 10, true, 0.2);
};

TEST_F(CellTest, empty_cell){
	EXPECT_EQ(empty_cell.getContents(), Contents::EMPTY);
	EXPECT_EQ(empty_cell.isBlocked(), false);
	EXPECT_EQ(empty_cell.isGoal(), false);
	EXPECT_EQ(empty_cell.toString(), " ");
}

TEST_F(CellTest, start_cell){
	EXPECT_EQ(start_cell.getContents(), Contents::START);
	EXPECT_EQ(start_cell.isBlocked(), false);
	EXPECT_EQ(start_cell.isGoal(), false);
	EXPECT_EQ(start_cell.toString(), "S");
}

TEST_F(CellTest, goal_cell){
	EXPECT_EQ(goal_cell.getContents(), Contents::GOAL);
	EXPECT_EQ(goal_cell.isBlocked(), false);
	EXPECT_EQ(goal_cell.isGoal(), true);
	EXPECT_EQ(goal_cell.toString(), "G");
}

TEST_F(CellTest, blocked_cell){
	EXPECT_EQ(blocked_cell.getContents(), Contents::BLOCKED);
	EXPECT_EQ(blocked_cell.isBlocked(), true);
	EXPECT_EQ(blocked_cell.isGoal(), false);
	EXPECT_EQ(blocked_cell.toString(), "x");
}

TEST_F(CellTest, path_cell){
	EXPECT_EQ(path_cell.getContents(), Contents::PATH);
	EXPECT_EQ(path_cell.isBlocked(), false);
	EXPECT_EQ(path_cell.isGoal(), false);
	EXPECT_EQ(path_cell.toString(), "*");
}

TEST_F(MazeTest, default_maze){
	EXPECT_EQ(default_maze.toString(), "| S |   |   |   |   | x |   |   |   |   |\n|   |   |   | x |   | x |   |   |   |   |\n|   |   |   | x |   |   |   |   |   |   |\n|   |   |   |   |   | x |   |   |   |   |\n| x |   | x |   |   |   |   |   | x |   |\n|   |   |   |   |   |   |   |   |   | x |\n|   |   |   |   | x | x |   | x |   |   |\n|   |   |   |   |   |   |   | x | x |   |\n|   | x |   |   |   | x |   |   |   | x |\n|   |   | x |   | x |   |   |   |   | G |");
}

TEST_F(MazeTest, get_search_locations){
	EXPECT_EQ(default_maze.getCell(0, 0).getContents(), Contents::START );
	EXPECT_EQ(default_maze.getCell(9, 9).getContents(), Contents::GOAL );
}

TEST_F(MazeTest, check_all_positions){
	for (int i: std::views::iota(0, 99)){
		int cur_row = i%9;
		int cur_col = i-(cur_row*9);
		Position cell_pos = default_maze.getCell(cur_row, cur_col).getPosition(); 
		Position expected_pos = Position(cur_row,cur_col);
		EXPECT_EQ(cell_pos.row,expected_pos.row);
		EXPECT_EQ(cell_pos.col,expected_pos.col);
	}
}

TEST_F(MazeTest, dfs){
	EXPECT_EQ(default_maze.dfs().has_value(), true);
	//EXPECT_EQ(default_maze.dfs().value()->getParent()->isGoal(), true);
	//EXPECT_EQ(default_maze.toString(), "| S |   |   |   |   | x |   |   |   |   |\n|   |   |   | x |   | x |   |   |   |   |\n|   |   |   | x |   |   |   |   |   |   |\n|   |   |   |   |   | x |   |   |   |   |\n| x |   | x |   |   |   |   |   | x |   |\n|   |   |   |   |   |   |   |   |   | x |\n|   |   |   |   | x | x |   | x |   |   |\n|   |   |   |   |   |   |   | x | x |   |\n|   | x |   |   |   | x |   |   |   | x |\n|   |   | x |   | x |   |   |   |   | G |");
}
