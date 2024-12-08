#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "../strategies/Strategy.hpp"
#include "../GameMatrix/GameMatrix.hpp"
#include "../History/History.hpp"
#include <vector>
#include <memory>
#include <string>

class Simulation {
private:
	std::vector<std::unique_ptr<Strategy>> strategies; // Стратегии участников
	GameMatrix game_matrix;                            // Матрица игры
	History history;                                   // История игры
	int steps = 100;                                   // Количество шагов (раундов)

	// Проведение одного раунда
	Choices play_round();

	// Помощник для вычисления очков в турнирном режиме
	std::vector<int> calculate_tournament_scores() const;

public:
	Simulation(std::vector<std::unique_ptr<Strategy>> strategies, 
			const std::string &file_path, 
			int simulation_steps);

	void run_detailed_mode();
	void run_fast_mode();
	void run_tournament();
};

#endif // SIMULATION_HPP
