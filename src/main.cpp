#import "../incl/maze.hpp"
#import <iostream>
#import <chrono>

int main(){
	std::cout << "Testing multiple mazes";
	std::cout << "Testing multiple mazes";
	const auto start =std::chrono::steady_clock::now();
Maze Maze(Position(5,5), Position (13,12), 20, 20, 42, .5);
	const auto end = std::chrono::steady_clock::now();
	const std::chrono::duration duration = end-start;

}
