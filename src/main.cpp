// Stuff regarding chrono: 
// 		https://en.cppreference.com/w/cpp/chrono/duration
// And about timepoint substraction & steady_clock::now()
// 		https://en.cppreference.com/w/cpp/chrono/steady_clock/now

#include "../incl/maze.hpp"
#include <iostream>
#include <chrono>

int main(){

	typedef std::chrono::microseconds us;
	std::chrono::duration total_duration = std::chrono::duration<double>::zero();
	int trials = 500;
	// Using scopes here to help avoid the program taking up a lot of memory
	// and also to keep the namespace clean.

	std::cout << "Average maze instantiation time in microseconds: "; {
		const auto start = std::chrono::steady_clock::now();
		for (int i = 0; i<trials; i++){
			Maze maze(Position(5,5), Position (13,12), 20, 20, 42, .2);
		}
		const auto end = std::chrono::steady_clock::now();
		const std::chrono::duration<double> it_duration =  end-start;
		total_duration = total_duration + it_duration;
		auto average_duration = total_duration/trials;
		// I think there is probably a way to do this that does not require a cast.
		std::cout << std::chrono::duration_cast<us>(average_duration).count() << "\n";
	}

	std::cout << "Average DFS time in microseconds for a 20x20 maze: ";{
		for (int i = 0; i<trials; i++){
			Maze maze(Position(5,5), Position (13,12), 20, 20, 42, .2);
			const auto start = std::chrono::steady_clock::now();
			maze.dfs();
			const auto end = std::chrono::steady_clock::now();
			const std::chrono::duration<double> it_duration =  end-start;
			total_duration = total_duration + it_duration;
		}
		auto average_duration = total_duration/trials;
		std::cout << std::chrono::duration_cast<us>(average_duration).count() << "\n";

	}

	std::cout << "Average BFS time in microseconds for a 20x20 maze: ";{
		for (int i = 0; i<trials; i++){
			Maze maze(Position(5,5), Position (13,12), 20, 20, 42, .2);
			const auto start = std::chrono::steady_clock::now();
			maze.bfs();
			const auto end = std::chrono::steady_clock::now();
			const std::chrono::duration<double> it_duration =  end-start;
			total_duration = total_duration + it_duration;
		}
		auto average_duration = total_duration/trials;
		std::cout << std::chrono::duration_cast<us>(average_duration).count() << "\n";

	}

	std::cout << "Average DFS time in microseconds for a 50x50 maze: ";{
		for (int i = 0; i<trials; i++){
			Maze maze(Position(1,10), Position (13,12), 50, 50, 42, .2);
			const auto start = std::chrono::steady_clock::now();
			maze.dfs();
			const auto end = std::chrono::steady_clock::now();
			const std::chrono::duration<double> it_duration =  end-start;
			total_duration = total_duration + it_duration;
		}
		auto average_duration = total_duration/trials;
		std::cout << std::chrono::duration_cast<us>(average_duration).count() << "\n";

	}

	std::cout << "Average BFS time in microseconds for a 50x50 maze: ";{
		for (int i = 0; i<trials; i++){
			Maze maze(Position(5,5), Position (13,12), 50, 50, 42, .2);
			const auto start = std::chrono::steady_clock::now();
			maze.bfs();
			const auto end = std::chrono::steady_clock::now();
			const std::chrono::duration<double> it_duration =  end-start;
			total_duration = total_duration + it_duration;
		}
		auto average_duration = total_duration/trials;
		std::cout << std::chrono::duration_cast<us>(average_duration).count() << "\n";

	}
}
