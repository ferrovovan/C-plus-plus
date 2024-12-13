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
	if (strategies.size() < 4) {
		std::cerr << "Для проведения турнира требуется минимум 4 стратегии.\n";
		return;
	}
	std::cout << "Запуск турнира...\n";

	size_t n = strategies.size(); // Количество стратегий
	std::vector<int> total_scores(n, 0); // Результирующий массив очков каждой стратегии

	// Генерация всех возможных троек стратегий с повторением
	for (size_t i = 0; i < n; ++i) {
		for (size_t j = i; j < n; ++j) {
			for (size_t k = j; k < n; ++k) {
				// Текущие участники турнира
				Strategy* player1 = strategies[i].get();
				Strategy* player2 = strategies[j].get();
				Strategy* player3 = strategies[k].get();

				// Временная история для этих трёх участников
				History round_history;

				// Очки за текущую тройку
				std::vector<int> scores_for_match(3, 0);

				// Симулируем раунды для трёх участников
				for (int step = 0; step < steps; ++step) {
					Choices choices = {
						player1->decide(round_history.get_history()),
						player2->decide(round_history.get_history()),
						player3->decide(round_history.get_history())
					};

					// Добавляем раунд в историю
					round_history.add_round(choices);

					// Рассчитываем очки за текущий раунд
					std::vector<int> round_scores = game_matrix.calculate_scores(choices);

					// Суммируем очки
					for (size_t idx = 0; idx < 3; ++idx) {
						scores_for_match[idx] += round_scores[idx];
					}
				}

				// Учитываем результаты матча для глобальных счётчиков
				total_scores[i] += scores_for_match[0];
				total_scores[j] += scores_for_match[1];
				total_scores[k] += scores_for_match[2];
			}
		}
	}

	// Вывод итогов турнира
	std::cout << "Результаты турнира:\n";
	for (size_t i = 0; i < n; ++i) {
		std::cout << "Стратегия " << i + 1 << ": " << total_scores[i] << " очков\n";
	}
}


