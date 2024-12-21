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
	Strategies_vector strategies; // Стратегии участников
	GameMatrix game_matrix;                            // Матрица игры
	int steps;                                         // Количество шагов (раундов)
	Renderer renderer;

	StrategyNames get_names() const;
	StrategyNames get_names(Strategy* player1, Strategy* player2, Strategy* player3) const;

	Choices get_choices(const History& history) const;
	Choices get_choices(const History& history, Strategy* player1, Strategy* player2, Strategy* player3) const;

	// Проведение одного раунда
	Choices play_round(History& history) const;
	void simulate_round(History& history, ScoreList& total_scores);
	ScoreList play_custom_match(
		Strategy* player1, Strategy* player2, Strategy* player3
	);
	// Обновление общего счёта
	void add_total_score(ScoreList& scores_for_match,
		size_t i, size_t j, size_t k, ScoreList& total_scores
	) const;

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
