#ifndef COMMANDLINEPARSER_HPP
#define COMMANDLINEPARSER_HPP

#include "SimulationParams.hpp"
#include <string>
#include <vector>
#include <map>

class CommandLineParser {
public:
	static SimulationParams parse(int argc, char* argv[]);

private:
	static std::map<std::string, std::string> parseArguments(int argc, char* argv[]);

	static void parse_Strategies(const std::string& strategiesStr, SimulationParams& params) ;
	static void parse_Mode(const std::map<std::string, std::string>& args, SimulationParams& params) ;
	static void parse_Steps(const std::map<std::string, std::string>& args, SimulationParams& params) ;
	static void parse_ConfigDir(const std::map<std::string, std::string>& args, SimulationParams& params) ;
	static void parse_MatrixFile(const std::map<std::string, std::string>& args, SimulationParams& params) ;

	static void validateStrategies(const SimulationParams& params) ;
};

#endif // COMMANDLINEPARSER_HPP
