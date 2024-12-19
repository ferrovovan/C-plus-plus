#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "../types.hpp"
#include <vector>
#include <string>

using StrategyNames = std::vector<std::string>;        // Названия стратегий
using ScoreList = std::vector<int>;                    // Список итоговых очков
using RoundScores = std::vector<std::vector<int>>;     // Очки по каждому раунду
using ColumnWidths = std::vector<size_t>;              // Ширины столбцов таблицы

class Renderer {
public:
	// Подробный режим
	void render_detailed_table_header(const StrategyNames& strategy_names) const;

	void clear_strings(size_t n) const;
	void render_detailed_output(
		size_t num_rounds,
		const Choices& choices,
		const ScoreList& total_scores,
		const StrategyNames& strategy_names) const;

	// Быстрый режим
	void render_fast_output(const StrategyNames& strategy_names, const ScoreList& total_scores) const;

	// Турнирный режим
	void render_tournament_round(
		const ScoreList& total_scores,
		const StrategyNames& strategy_names) const;

	void render_tournament_results(const ScoreList& total_scores, const StrategyNames& strategy_names) const;
};

#endif // RENDERER_HPP
