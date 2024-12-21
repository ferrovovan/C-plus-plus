#include "Simulation.hpp"
#include <iostream>
#include <stdexcept>

Simulation::Simulation(
	Strategies_vector strategies,
	const std::string& file_path,
	int simulation_steps)
	: strategies(std::move(strategies)),
	game_matrix(file_path.empty() ? GameMatrix() : GameMatrix(file_path)),
	steps(simulation_steps),
	renderer() {}

// Проведение одного раунда
Choices Simulation::play_round(History& history) const{
	Choices current_choices = get_choices(history);

	history.add_round(current_choices);
	return current_choices;
}

void Simulation::simulate_round(History& history, ScoreList& total_scores) {
	// Получение хронологии
	Choices round_choices = play_round(history);
	auto round_scores = game_matrix.calculate_scores(round_choices);

	// Обновление хронологии
	history.add_round(round_choices);
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
	History history(get_names());
	ScoreList total_scores(strategies.size(), 0);

	// Симуляция раундов
	size_t num_strategies = strategy_names.size(); // Количество стратегий
	for (int step = 0; step < steps; ++step) {
		simulate_round(history, total_scores);
		renderer.clear_strings(num_strategies + 4);
		renderer.render_detailed_output(
			step + 1, history.get_last_moves(), total_scores, strategy_names);
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
	History history(get_names());

	for (int i = 0; i < steps; ++i) {
		Choices round_choices = play_round(history);
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
	StrategyNames strategy_names = get_names();
	renderer.render_fast_output(strategy_names, total_scores);
}

Choices Simulation::get_choices(const History& history) const {
	Choices choices;
	for (auto& strategy : strategies) {
		choices.push_back(
			strategy->decide(
				history.get_oponents_moves(
					strategy->get_name()
				)
			)
		);
	}
	return choices;
}

Choices Simulation::get_choices(const History& history, Strategy* player1, Strategy* player2, Strategy* player3) const {
	Choices choices = {
		player1->decide(history.get_oponents_moves(player1->get_name())),
		player2->decide(history.get_oponents_moves(player2->get_name())),
		player3->decide(history.get_oponents_moves(player3->get_name()))
	};
	return choices;
}

// Проведение матча с тремя стратегиями
ScoreList Simulation::play_custom_match(Strategy* player1, Strategy* player2, Strategy* player3) {
	History round_history(
		get_names(player1, player2, player3)
	);
	ScoreList scores_for_match(3, 0);

	for (int step = 0; step < steps; ++step) {
		Choices choices = get_choices(round_history, player1, player2, player3);

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

StrategyNames Simulation::get_names() const {
	StrategyNames strategy_names;
	for (const auto& strategy : strategies) {
		strategy_names.push_back(strategy->get_name());
	}
	return strategy_names;
}

StrategyNames Simulation::get_names(Strategy* player1, Strategy* player2, Strategy* player3) const {
	StrategyNames strategy_names;
	strategy_names.push_back(player1->get_name());
	strategy_names.push_back(player2->get_name());
	strategy_names.push_back(player3->get_name());
	return strategy_names;
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

