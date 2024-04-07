#ifndef CELL_HPP
#define CELL_HPP
#include <string>

enum class Contents : char {
	EMPTY 	= ' ',
	START 	= 'S',
	GOAL 	= 'G',
	BLOCKED = 'x',
	PATH 	= '*',
	UNINT 	= '?'
};

struct Position {
	int row;
	int col;
};

class Cell{

	private:
		Position 	position;
		Contents 	contents;
		Cell* 		parent;

	public:
		Cell(Contents contents);
		Cell(Position position, Contents contents);
		Cell();

		Position getPosition();	
		Contents getContents();
		Cell* getParent();

		void setPosition(int row, int col);
		void setContents(Contents contents);

		bool isBlocked();
		bool isGoal();

		void setParent(Cell* new_parent);
		void markOnPath();
		void markAsBlocked();

		std::string	toString();
		bool operator==(Cell other);
};

#endif
