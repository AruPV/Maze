#include "../incl/cell.hpp"
#include <string>

Cell::Cell(Position pos, Contents contents):
	position 	{pos}, 
	contents 	{contents},
	parent 		{nullptr}{}

Cell::Cell():
	position 	{-1,-1}, 
	contents 	{Contents::UNINT},
	parent 		{nullptr}{
}

Position Cell::getPosition()              {return position;}
Contents Cell::getContents()              {return contents;}
Cell*    Cell::getParent()                {return parent;}

void	 Cell::setPosition(int row, int col){position = Position(row,col);}
void     Cell::setContents(Contents contents){contents = contents;};

bool     Cell::isBlocked()                {return contents == Contents::BLOCKED;}
bool     Cell::isGoal()                   {return contents == Contents::GOAL;}

void     Cell::setParent(Cell* new_parent){parent = new_parent;}
void     Cell::markOnPath()	              {contents = Contents::PATH;}
void     Cell::markAsBlocked()            {contents = Contents::BLOCKED;}

std::string	Cell::toString() {
	std::string str_contents = std::string(1, static_cast<char>(contents));
	return str_contents;
}

bool Cell::operator==(Cell other) {
	return (
		(position.col 	== other.getPosition().col) &&
		(position.row 	== other.getPosition().row) &&
		(contents 		== other.getContents()) 	&&
		(parent 		== other.getParent())
	);
}

