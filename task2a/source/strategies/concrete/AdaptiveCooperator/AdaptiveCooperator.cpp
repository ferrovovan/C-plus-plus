#include "AdaptiveCooperator.hpp"
// #include <iostream>

// Конструктор с чтением конфигурационного файла
AdaptiveCooperator::AdaptiveCooperator(const std::string& config_path) : Strategy("AdaptiveCooperator") {
	StrategyConfig config(config_path); // Чтение из конфигурационного файла
	cooperation_threshold = config.get("cooperation_threshold", 0.5);
	history_depth = static_cast<int>(config.get("history_depth", 10));
	// Предательство уменьшает общий счёт стратегии, понижая вероятность дальнейшей кооперации.
	betrayal_penalty = config.get("betrayal_penalty", -5.0);
}

Decision AdaptiveCooperator::decide(const ChoiceHistory& history) {
	// Если история пуста, по умолчанию выбираем кооперацию.
	if (history.empty()) return 'C';

	// Ограничиваем глубину видимой истории
	int max_visible_depth = std::min(history_depth, static_cast<int>(history.size()));
	// Переменная для вычисления среднего коэффициента кооперации.
	double cooperation_count = 0.0;

	// Проходим по последним раундам истории.
	for (int i = 0; i < max_visible_depth; ++i) {
		const auto& round = history[history.size() - i - 1]; // Берём i-тый с конца раунд.
		for (const char& decision : round) {
			if (decision == 'C') {
				cooperation_count += 1.0; // Кооперация прибавляет к общему счёту.
			} else if (decision == 'D') {
				cooperation_count += betrayal_penalty; // Предательство наказывается.
			}
		}
	}

	// Рассчитываем коэффициент кооперации на основе видимой истории
	// std::cout << cooperation_count << " | " << max_visible_depth << std::endl;
	double cooperation_rate = cooperation_count / max_visible_depth;
	// std::cout << cooperation_rate << std::endl;

	// Принимаем решение на основе кооперации
	return cooperation_rate >= cooperation_threshold ? 'C' : 'D';
}

