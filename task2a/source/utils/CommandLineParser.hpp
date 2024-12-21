#ifndef COMMANDLINEPARSER_HPP
#define COMMANDLINEPARSER_HPP

#include "SimulationParams/SimulationParams.hpp"
#include <string>
#include <vector>
#include <map>


using ArgsMap = std::map<std::string, std::string>;

class CommandLineParser {
public:
	static SimulationParams parse(int argc, char* argv[]);

private:
	static ArgsMap parseArguments(int argc, char* argv[]);

	static void parse_Strategies(const std::string& strategiesStr, SimulationParams& params) ;
	static void parse_Mode(const ArgsMap& args, SimulationParams& params) ;
	static void parse_Steps(const ArgsMap& args, SimulationParams& params) ;
	static void parse_ConfigDir(const ArgsMap& args, SimulationParams& params) ;
	static void parse_MatrixFile(const ArgsMap& args, SimulationParams& params) ;

	static void validateStrategies(const SimulationParams& params) ;

	static void debug_args(const ArgsMap& args) ;
};

#endif // COMMANDLINEPARSER_HPP
