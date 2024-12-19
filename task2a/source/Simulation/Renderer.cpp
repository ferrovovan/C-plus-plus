#include "Renderer.hpp"
#include <iostream>
#include <iomanip> // Для работы с форматированием
#include <string>

// Вывод заголовка таблицы в подробном режиме
void Renderer::render_detailed_table_header(const StrategyNames& strategy_names) const {
	for (const auto& name : strategy_names) {
		std::cout << name << " | ";
	}
	std::cout << "\n";

	for (const auto& name : strategy_names) {
		std::cout << std::string(name.length(), '-') << " | ";
	}
	std::cout << std::endl;
}

// Очистка предыдущих строк
void Renderer::clear_strings(size_t n) const {
	for (size_t i = 0; i < n; ++i) {
		std::cout << "\033[F" // Перейти к предыдущей строке
		          << "\033[K"; // Очистить строку
	}
}

// Отображение данных по ходу симуляции
void Renderer::render_detailed_output(
	size_t num_rounds,
	const Choices& choices,
	const ScoreList& total_scores,
	const StrategyNames& strategy_names) const {

	size_t num_strategий = strategy_names.size();

	// Проверка корректности размеров массивов
	if (choices.size() != num_strategий || total_scores.size() != num_strategий) {
		std::cerr << "Ошибка: Размеры данных не совпадают с количеством стратегий!\n";
		return;
	}

	std::cout << "Раунд " << num_rounds << " | ";

	// Выводим выборы игроков в текущем раунде
	for (size_t j = 0; j < num_strategий; ++j) {
		std::cout << choices[j] << " | ";
	}
	std::cout << std::endl;

	// Выводим сводку по очкам
	for (size_t i = 0; i < num_strategий; ++i) {
		std::cout << "Стратегия: " << strategy_names[i]
		          << " | Очки: " << total_scores[i] << std::endl;
	}
	std::cout << std::endl;
}



// Вывод результатов в быстром режиме
void Renderer::render_fast_output(const StrategyNames& strategy_names, const ScoreList& total_scores) const {
	std::cout << "\nИтоговый счёт:\n";
	for (size_t i = 0; i < strategy_names.size(); ++i) {
		std::cout << "Игрок " << strategy_names[i]
		          << ": общий счёт = " << total_scores[i]
		          << std::endl;
	}
}

// Отображение промежуточных результатов турнира
void Renderer::render_tournament_round(
	const ScoreList& total_scores,
	const StrategyNames& strategy_names) const {

	std::cout << "\nРаунд турнира:\n";
	for (size_t i = 0; i < strategy_names.size(); ++i) {
		std::cout << strategy_names[i] << ": "
		          << total_scores[i] << " очков.\n";
	}
}

// Вывод итогов турнира
void Renderer::render_tournament_results(
	const ScoreList& total_scores,
	const StrategyNames& strategy_names) const {

	std::cout << "\nРезультаты турнира:\n";
	for (size_t i = 0; i < total_scores.size(); ++i) {
		std::cout << "Стратегия " << strategy_names[i]
		          << ": " << total_scores[i] << " очков\n";
	}
}

