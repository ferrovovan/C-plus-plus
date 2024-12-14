#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "../strategies/Strategy.hpp"
#include "../GameMatrix/GameMatrix.hpp"
#include "../History/History.hpp"
#include "Renderer.hpp"
#include <vector>
#include <memory>
#include <string>

// Псевдонимы для упрощения работы с данными
using ScoreList = std::vector<int>;                  // Список итоговых очков
using RoundScores = std::vector<std::vector<int>>;   // Список очков для каждого раунда
using Strategies_vector = std::vector<std::unique_ptr<Strategy>>;

class Simulation {
private:
	std::vector<std::unique_ptr<Strategy>> strategies; // Стратегии участников
	GameMatrix game_matrix;                            // Матрица игры
	History history;                                   // История игры
	int steps;                                         // Количество шагов (раундов)
	Renderer renderer;

	// Проведение одного раунда
	Choices play_round();
	void simulate_round(ChoiceHistory& choices_history, ScoreList& total_scores);
	void play_custom_round(
		Strategy* player1, Strategy* player2, Strategy* player3,
		size_t i, size_t j, size_t k,
		ScoreList& total_scores);

	// Подсчёт результатов для раундов
	RoundScores simulate_rounds(int steps, ScoreList& total_scores);

public:
	Simulation(Strategies_vector strategies,
		const std::string& file_path,
		int simulation_steps);

	void run_detailed_mode();
	void run_fast_mode();
	void run_tournament();
};

#endif // SIMULATION_HPP
