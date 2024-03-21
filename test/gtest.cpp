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
		Maze default_maze;
};

TEST_F(CellTest, empty_cell){
	//EXPECT_EQ(empty_cell.getPosition().row, 0);
	//#include "../incl/maze.hpp":w
	//EXPECT_EQ(empty_cell.getPosition().col, 0);
	EXPECT_EQ(empty_cell.getContents(), Contents::EMPTY);
	EXPECT_EQ(empty_cell.isBlocked(), false);
	EXPECT_EQ(empty_cell.isGoal(), false);
	EXPECT_EQ(empty_cell.toString(), " ");
}

TEST_F(CellTest, start_cell){
	//EXPECT_EQ(start_cell.getPosition().row, 0);
	//EXPECT_EQ(start_cell.getPosition().col, 0);
	EXPECT_EQ(start_cell.getContents(), Contents::START);
	EXPECT_EQ(start_cell.isBlocked(), false);
	EXPECT_EQ(start_cell.isGoal(), false);
	EXPECT_EQ(start_cell.toString(), "S");
}

TEST_F(CellTest, goal_cell){
	//EXPECT_EQ(goal_cell.getPosition().row, 0);
	//EXPECT_EQ(goal_cell.getPosition().col, 0);
	EXPECT_EQ(goal_cell.getContents(), Contents::GOAL);
	EXPECT_EQ(goal_cell.isBlocked(), false);
	EXPECT_EQ(goal_cell.isGoal(), true);
	EXPECT_EQ(goal_cell.toString(), "G");
}

TEST_F(CellTest, blocked_cell){
	//EXPECT_EQ(blocked_cell.getPosition().row, 0);
	//EXPECT_EQ(blocked_cell.getPosition().col, 0);
	EXPECT_EQ(blocked_cell.getContents(), Contents::BLOCKED);
	EXPECT_EQ(blocked_cell.isBlocked(), true);
	EXPECT_EQ(blocked_cell.isGoal(), false);
	EXPECT_EQ(blocked_cell.toString(), "x");
}

TEST_F(CellTest, path_cell){
	//EXPECT_EQ(start_cell.getPosition().row, 0);
	//EXPECT_EQ(start_cell.getPosition().col, 0);
	EXPECT_EQ(path_cell.getContents(), Contents::PATH);
	EXPECT_EQ(path_cell.isBlocked(), false);
	EXPECT_EQ(path_cell.isGoal(), false);
	EXPECT_EQ(path_cell.toString(), "*");
}

TEST_F(MazeTest, default_maze){
	//EXPECT_EQ(start_cell.getPosition().row, 0);
	//EXPECT_EQ(start_cell.getPosition().col, 0);
	EXPECT_EQ(default_maze.toString(), "");
}
