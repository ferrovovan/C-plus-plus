#include "simulation_function.hpp"
#include <memory>

Choices get_choices(const History& history, Strategy* player1, Strategy* player2, Strategy* player3) {
	Choices choices = {
		player1->decide(history.get_oponents_moves(player1->get_name())),
		player2->decide(history.get_oponents_moves(player2->get_name())),
		player3->decide(history.get_oponents_moves(player3->get_name()))
	};
	return choices;
}

ScoreList play_custom_match(
	Strategy* player1,
	Strategy* player2,
	Strategy* player3,
	const GameMatrix& game_matrix,
	int steps
) {
	History round_history(get_names(player1, player2, player3));
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

StrategyNames get_names(Strategy* player1, Strategy* player2, Strategy* player3) {
	StrategyNames strategy_names;
	strategy_names.push_back(player1->get_name());
	strategy_names.push_back(player2->get_name());
	strategy_names.push_back(player3->get_name());
	return strategy_names;
}

