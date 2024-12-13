#include "AdaptiveCooperator.hpp"

// Конструктор с чтением конфигурационного файла
AdaptiveCooperator::AdaptiveCooperator(const std::string& config_path) {
    StrategyConfig config(config_path); // Чтение из конфигурационного файла
    cooperation_threshold = config.get("cooperation_threshold", 0.5);
    betrayal_penalty = config.get("betrayal_penalty", -5.0);
    history_depth = static_cast<int>(config.get("history_depth", 5));
}

Decision AdaptiveCooperator::decide(const ChoiceHistory& history) {
    // Анализ истории для последнего видимого количества раундов
    double cooperation_count = 0.0;

    // Ограничиваем глубину видимой истории
    int max_visible_depth = std::min(history_depth, static_cast<int>(history.size()));

    // Проходим по истории и считаем количество коопераций
    for (int i = 0; i < max_visible_depth; ++i) {
        if (history[history.size() - i - 1][0] == 'C') {  // История начинается с последнего раунда
            cooperation_count++;
        }
    }

    // Рассчитываем коэффициент кооперации на основе видимой истории
    double cooperation_rate = cooperation_count / max_visible_depth;

    // Принимаем решение на основе кооперации
    return cooperation_rate >= cooperation_threshold ? 'C' : 'D';
}

