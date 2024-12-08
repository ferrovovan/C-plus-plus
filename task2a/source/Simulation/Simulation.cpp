#include "Simulation.hpp"
#include <iostream>
#include <stdexcept>

Simulation::Simulation(std::vector<std::unique_ptr<Strategy>> strategies, 
                       const std::string &file_path,
                       int simulation_steps) :
            strategies(std::move(strategies)), 
            game_matrix(GameMatrix(file_path)), 
            steps(simulation_steps)
	{
	
	if (this->strategies.size() != 3) {
		throw std::invalid_argument("Симуляция должна иметь ровно 3 стратегии.");
	}
}

// Проведение одного раунда
Choices Simulation::play_round() {
	Choices current_choices;
	for (auto& strategy : strategies) {
		current_choices.push_back(strategy->decide(history.get_history()));
	}
	history.add_round(current_choices);
	return current_choices;
}

// Режим подробной симуляции
void Simulation::run_detailed_mode() {
	std::cout << "Запуск подробной симуляции...\n";
	for (int i = 0; i < steps; ++i) {
		Choices round_choices = play_round();
		auto scores = game_matrix.calculate_scores(round_choices);

		std::cout << "Раунд " << i + 1 << ": ";
		for (size_t j = 0; j < round_choices.size(); ++j) {
			std::cout << "Игрок " << j + 1 << " выбрал " << round_choices[j]
					<< ", очки: " << scores[j] << " ";
		}
		std::cout << std::endl;
	}
}

// Режим быстрой симуляции
void Simulation::run_fast_mode() {
	std::cout << "Запуск быстрой симуляции...\n";
	std::vector<int> total_scores(3, 0);

	for (int i = 0; i < steps; ++i) {
		Choices round_choices = play_round();
		auto scores = game_matrix.calculate_scores(round_choices);

		for (size_t j = 0; j < total_scores.size(); ++j) {
			total_scores[j] += scores[j];
		}
	}

	for (size_t i = 0; i < total_scores.size(); ++i) {
		std::cout << "Игрок " << i + 1 << ": общий счёт = " << total_scores[i] << std::endl;
	}
}

// Режим турнира
void Simulation::run_tournament() {
	std::cout << "Запуск турнира...\n";
	auto scores = calculate_tournament_scores();

	for (size_t i = 0; i < scores.size(); ++i) {
		std::cout << "Игрок " << i + 1 << ": общий счёт = " << scores[i] << std::endl;
	}
}

// Помощник для вычисления очков в турнире
std::vector<int> Simulation::calculate_tournament_scores() const {
	std::vector<int> total_scores(strategies.size(), 0);

	for (size_t i = 0; i < strategies.size(); ++i) {
		for (size_t j = 0; j < strategies.size(); ++j) {
			if (i == j) continue;

			// Симулируем игру между стратегиями i и j
			for (int round = 0; round < steps; ++round) {
				Choices round_choices = {
					strategies[i]->decide(history.get_history()),
					strategies[j]->decide(history.get_history()),
					'-' // Третий игрок отсутствует в дуэльных раундах
				};

				auto scores = game_matrix.calculate_scores(round_choices);
				total_scores[i] += scores[0];
				total_scores[j] += scores[1];
			}
		}
	}
	return total_scores;
}

