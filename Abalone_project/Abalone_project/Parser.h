#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <time.h>
#include "Abalone.h"

class Parser
{
public:
	static std::string delimiter_colon;
	static std::string delimiter_space;

	static void get_Abalones_from_data(std::vector<Abalone> &Abalones, std::string file_name);
	static void write_to_file_parameters(std::string file_name, std::map<std::string, std::string> parameters);
	static std::map<std::string, std::string> Parser::get_parameters_from_file(std::string file_name);
	static std::string file_to_string(std::string file_name);
};