#include "Simulation.hpp"
#include <iostream>
#include <stdexcept>

Simulation::Simulation(
	std::vector<std::unique_ptr<Strategy>> strategies,
	const std::string& file_path,
	int simulation_steps)
	: strategies(std::move(strategies)),
	game_matrix(file_path.empty() ? GameMatrix() : GameMatrix(file_path)),
	steps(simulation_steps),
	renderer() {}

// Проведение одного раунда
Choices Simulation::play_round() {
	Choices current_choices;
	for (auto& strategy : strategies) {
		current_choices.push_back(strategy->decide(history.get_history()));
	}
	history.add_round(current_choices);
	return current_choices;
}

void Simulation::simulate_round(ChoiceHistory& choices_history, ScoreList& total_scores) {
	Choices round_choices = play_round();
	auto round_scores = game_matrix.calculate_scores(round_choices);

	// Обновление исторических данных
	choices_history.push_back(round_choices);
	for (size_t i = 0; i < total_scores.size(); ++i) {
		total_scores[i] += round_scores[i];
	}
}

// Подробный режим
void Simulation::run_detailed_mode() {
	std::cout << "\nЗапуск подробной симуляции...\n";
	std::cout << "Стратегии:\n";

	StrategyNames strategy_names;
	for (const auto& strategy : strategies) {
		strategy_names.push_back(strategy->get_name());
	}

	renderer.render_detailed_table_header(strategy_names);

	// Инициализация истории и счёта
	ChoiceHistory choices_history;
	ScoreList total_scores(strategies.size(), 0);

	// Симуляция раундов
	size_t num_strategies = strategy_names.size(); // Количество стратегий
	for (int step = 0; step < steps; ++step) {
		simulate_round(choices_history, total_scores);
		renderer.clear_strings(num_strategies + 4);
		renderer.render_detailed_output(
			step + 1, choices_history.back(), total_scores, strategy_names);
		std::cout << "Нажмите \"Enter\" клавишу, чтобы продолжить..." << std::endl;
		std::cin.get();
	}
	renderer.clear_strings(4);

	// Итоговый счёт
	renderer.render_fast_output(strategy_names, total_scores);
}


// Симуляция нескольких раундов
RoundScores Simulation::simulate_rounds(int steps, ScoreList& total_scores) {
	RoundScores detailed_results;

	for (int i = 0; i < steps; ++i) {
		Choices round_choices = play_round();
		auto scores = game_matrix.calculate_scores(round_choices);

		// Обновление общего счёта
		for (size_t j = 0; j < total_scores.size(); ++j) {
			total_scores[j] += scores[j];
		}

		// Сохранение подробностей для истории
		detailed_results.push_back(scores);
	}
	return detailed_results;
}

// Быстрый режим
void Simulation::run_fast_mode() {
	std::cout << "Запуск быстрой симуляции...\n";

	ScoreList total_scores(strategies.size(), 0);
	simulate_rounds(steps, total_scores);
	StrategyNames strategy_names;
	for (const auto& strategy : strategies) {
		strategy_names.push_back(strategy->get_name());
	}
	renderer.render_fast_output(strategy_names, total_scores);
}

// Проведение матча с тремя стратегиями
ScoreList Simulation::play_custom_match(Strategy* player1, Strategy* player2, Strategy* player3) {
	History round_history;
	ScoreList scores_for_match(3, 0);

	for (int step = 0; step < steps; ++step) {
		Choices choices = {
			player1->decide(round_history.get_history()),
			player2->decide(round_history.get_history()),
			player3->decide(round_history.get_history())
		};

		round_history.add_round(choices);
		ScoreList round_scores = game_matrix.calculate_scores(choices);

		for (size_t idx = 0; idx < 3; ++idx) {
			scores_for_match[idx] += round_scores[idx];
		}
	}
	return scores_for_match;
}

void Simulation::add_total_score(ScoreList& scores_for_match,
	size_t i, size_t j, size_t k, ScoreList& total_scores) const {
	total_scores[i] += scores_for_match[0];
	total_scores[j] += scores_for_match[1];
	total_scores[k] += scores_for_match[2];
}

// Режим турнира
void Simulation::run_tournament() {
	std::cout << "Запуск турнира...\n";

	size_t n = strategies.size();
	ScoreList total_scores(n, 0);
	ScoreList scores_for_match(3, 0);

	// Перебор всех возможных троек стратегий без повторений
	for (size_t i = 0; i < n; ++i) {
		for (size_t j = i + 1; j < n; ++j) {
			for (size_t k = j + 1; k < n; ++k) {
				scores_for_match = play_custom_match(
					strategies[i].get(),
					strategies[j].get(),
					strategies[k].get()
				);
				add_total_score(scores_for_match, i, j, k, total_scores);

				renderer.render_tournament_round(
					scores_for_match,
					{strategies[i]->get_name(),
					 strategies[j]->get_name(),
					 strategies[k]->get_name()}
				);
			}
		}
	}


	StrategyNames strategy_names;
	for (const auto& strategy : strategies) {
		strategy_names.push_back(strategy->get_name());
	}
	renderer.render_tournament_results(total_scores, strategy_names);
}

