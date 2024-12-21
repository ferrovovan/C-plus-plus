#include <gtest/gtest.h>
#include "../source/utils/CommandLineParser.hpp"

// Тест: Проверка парсинга с минимальными корректными аргументами
TEST(CommandLineParserTest, ParsesMinimumArgumentsCorrectly) {
	const char* argv[] = {
		"program_name",
		"TitForTat AlwaysCooperate AlwaysDefect",
	};
	int argc = 2;

	SimulationParams params = CommandLineParser::parse(argc, const_cast<char**>(argv));

	EXPECT_EQ(params.strategies.size(), 3);
	EXPECT_EQ(params.strategies[0], "TitForTat");
	EXPECT_EQ(params.strategies[1], "AlwaysCooperate");
	EXPECT_EQ(params.strategies[2], "AlwaysDefect");
	EXPECT_EQ(params.mode, "detailed");
	EXPECT_EQ(params.steps, 20);
	EXPECT_EQ(params.configDir, ""); // Проверяем, что необязательный параметр пуст
	EXPECT_EQ(params.matrixFile, ""); // Проверяем, что необязательный параметр пуст
}

TEST(CommandLineParserTest, ParsesMinimumTournamentArgumentsCorrectly) {
	const char* argv[] = {
		"program_name",
		"TitForTat AlwaysCooperate AlwaysDefect FakeStrategy",
	};
	int argc = 2;

	SimulationParams params = CommandLineParser::parse(argc, const_cast<char**>(argv));

	EXPECT_EQ(params.strategies.size(), 4);
	EXPECT_EQ(params.strategies[0], "TitForTat");
	EXPECT_EQ(params.strategies[1], "AlwaysCooperate");
	EXPECT_EQ(params.strategies[2], "AlwaysDefect");
	EXPECT_EQ(params.strategies[3], "FakeStrategy");
	EXPECT_EQ(params.mode, "tournament");
	EXPECT_EQ(params.steps, 20);
	EXPECT_EQ(params.configDir, "");
	EXPECT_EQ(params.matrixFile, "");
}

// Тест: Проверка парсинга с полным набором аргументов
TEST(CommandLineParserTest, ParsesFullArgumentsCorrectly) {
	const char* argv[] = {
		"program_name",
		"RandomChoice AlwaysDefect AlwaysCooperate AdaptiveCooperator",
		"--mode=tournament",
		"--steps=100",
		"--configs=../config",
		"--matrix=../config/matrices/Strict Punishment for Betrayal.conf"
	};
	int argc = 6;

	SimulationParams params = CommandLineParser::parse(argc, const_cast<char**>(argv));

	EXPECT_EQ(params.strategies.size(), 4);
	EXPECT_EQ(params.strategies[0], "RandomChoice");
	EXPECT_EQ(params.strategies[1], "AlwaysDefect");
	EXPECT_EQ(params.strategies[2], "AlwaysCooperate");
	EXPECT_EQ(params.strategies[3], "AdaptiveCooperator");
	EXPECT_EQ(params.mode, "tournament");
	EXPECT_EQ(params.steps, 100);
	EXPECT_EQ(params.configDir, "../config");
	EXPECT_EQ(params.matrixFile, "../config/matrices/Strict Punishment for Betrayal.conf");
}

// Тест: Проверка некорректного количества шагов
TEST(Invalid, InvalidStepsThrowsException) {
	const char* argv[] = {
		"program_name",
		"TitForTat AlwaysCooperate AdaptiveCooperator",
		"--steps=-10"
	};
	int argc = 4;

	EXPECT_THROW({
		CommandLineParser::parse(argc, const_cast<char**>(argv));
	}, std::invalid_argument);
}

TEST(Invalid, InvalidConfigDirThrowsException) {
	const char* argv[] = {
		"program_name",
		"TitForTat AlwaysCooperate AdaptiveCooperator",
		"--configs=fakeConfig"
	};
	int argc = 3;

	EXPECT_THROW({
		CommandLineParser::parse(argc, const_cast<char**>(argv));
	}, std::invalid_argument);
}

TEST(Invalid, InvalidMatrixThrowsException) {
	const char* argv[] = {
		"program_name",
		"TitForTat AlwaysCooperate AdaptiveCooperator",
		"--matrix=fakeMatrix.conf"
	};
	int argc = 3;

	EXPECT_THROW({
		CommandLineParser::parse(argc, const_cast<char**>(argv));
	}, std::invalid_argument);
}

// Тест: Проверка некорректного формата аргументов
TEST(Invalid, InvalidArgumentFormatThrowsException) {
	const char* argv[] = {
		"program",
		"--invalidOption=value"
	};
	int argc = 2;

	EXPECT_THROW({
		CommandLineParser::parse(argc, const_cast<char**>(argv));
	}, std::invalid_argument);
}

// Тест: Проверка отсутствия стратегий
TEST(MissingArgument, MissingStrategiesThrowsException) {
	const char* argv[] = {
		"program_name",
		"AlwaysCooperate"
	};
	int argc = 2;

	EXPECT_THROW({
		CommandLineParser::parse(argc, const_cast<char**>(argv));
	}, std::invalid_argument);
}
