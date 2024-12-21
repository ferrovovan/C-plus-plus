#pragma once

#include "../types.hpp"
#include <memory>
#include <string>

#include "../History/History.hpp"
#include "../strategies/Strategy.hpp"
#include "../GameMatrix/GameMatrix.hpp"

using ScoreList = std::vector<int>;                  // Список итоговых очков
using RoundScores = std::vector<std::vector<int>>;   // Список очков для каждого раунда
using Strategies_vector = std::vector<std::unique_ptr<Strategy>>;
using StrategyNames = std::vector<std::string>;


Choices get_choices(const History& history, Strategy* player1, Strategy* player2, Strategy* player3);

ScoreList play_custom_match(
	Strategy* player1,
	Strategy* player2,
	Strategy* player3,
	const GameMatrix& game_matrix,
	int steps
);

StrategyNames get_names(Strategy* player1, Strategy* player2, Strategy* player3);
