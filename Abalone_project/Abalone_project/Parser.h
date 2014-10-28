#pragma once

#include <vector>
#include <string>
#include "Abalone.h"

class Parser
{
public:
	static void get_Abalones_from_data(std::vector<Abalone> &Abalones, std::string file_name);
};