#include "Global.h"

std::string Global::DATA_FILE_NAME = "data.txt";
float Global::LEARNING_COEFFICIENT = 0.8;
// For Naive Bayes
std::string Global::PARAMETERS_NAIVE_BAYES_FILE_NAME = "Naive_Bayes_optimal_parameters.txt";
std::string Global::NB_OPTIMAL_INTERVAL_COUNT_DIAMETER_STRING = "NB_OPTIMAL_INTERVAL_COUNT_DIAMETER_STRING";
std::string Global::NB_OPTIMAL_INTERVAL_COUNT_LENGTH_STRING = "NB_OPTIMAL_INTERVAL_COUNT_LENGTH_STRING";
std::string Global::NB_OPTIMAL_INTERVAL_COUNT_HEIGHT_STRING = "NB_OPTIMAL_INTERVAL_COUNT_HEIGHT_STRING";
std::string Global::NB_OPTIMAL_INTERVAL_COUNT_WHOLE_WEIGHT_STRING = "NB_OPTIMAL_INTERVAL_COUNT_WHOLE_WEIGHT_STRING";
std::string Global::NB_OPTIMAL_INTERVAL_COUNT_VISCERA_WEIGHT_STRING = "NB_OPTIMAL_INTERVAL_COUNT_VISCERA_WEIGHT_STRING";
std::string Global::NB_OPTIMAL_INTERVAL_COUNT_SHELL_WEIGHT_STRING = "NB_OPTIMAL_INTERVAL_COUNT_SHELL_WEIGHT_STRING";
std::string Global::NB_OPTIMAL_INTERVAL_COUNT_SHUCKED_WEIGHT_STRING = "NB_OPTIMAL_INTERVAL_COUNT_SHUCKED_WEIGHT_STRING";

// For C4.5 algorithm

std::string Global::C45_DESIGION_TREE_FILE_NAME = "C45_Desigion_tree.txt";
int Global::MAX_UNIQUE_VALUES_COUNT = 50;
std::string Global::attribute_to_string(ATTRIBUTES tag)
{
	switch (tag)
	{
	case Global::DIAMETER:
		return "DIAMETER";
	case Global::LENGTH:
		return "LENGTH";
	case Global::HEIGHT:
		return "HEIGHT";
	case Global::WHOLE_WEIGHT:
		return "WHOLE_WEIGHT";
	case Global::VISCERA_WEIGHT:
		return "VISCERA_WEIGHT";
	case Global::SHELL_WEIGHT:
		return "SHELL_WEIGHT";
	case Global::SHUCKED_WEIGHT:
		return "SHUCKED_WEIGHT";
	case Global::SEX:
		return "SEX";
	}
	return "";
}
Global::ATTRIBUTES Global::attribute_from_string(std::string s)
{
	if (s.compare("DIAMETER") == 0) { return Global::DIAMETER; }
	if (s.compare("LENGTH") == 0) { return Global::LENGTH; }
	if (s.compare("HEIGHT") == 0) { return Global::HEIGHT; }
	if (s.compare("WHOLE_WEIGHT") == 0) { return Global::WHOLE_WEIGHT; }
	if (s.compare("VISCERA_WEIGHT") == 0) { return Global::VISCERA_WEIGHT; }
	if (s.compare("SHELL_WEIGHT") == 0) { return Global::SHELL_WEIGHT; }
	if (s.compare("SHUCKED_WEIGHT") == 0) { return Global::SHUCKED_WEIGHT; }
	if (s.compare("SEX") == 0) { return Global::SEX; }
}