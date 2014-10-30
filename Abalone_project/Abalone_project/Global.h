#pragma once
#include <string>

class Global
{
public:
	static std::string DATA_FILE_NAME;
	static float LEARNING_COEFFICIENT;
	// For Naive Bayes
	static std::string PARAMETERS_NAIVE_BAYES_FILE_NAME;
	static std::string NB_OPTIMAL_INTERVAL_COUNT_DIAMETER_STRING;
	static std::string NB_OPTIMAL_INTERVAL_COUNT_LENGTH_STRING;
	static std::string NB_OPTIMAL_INTERVAL_COUNT_HEIGHT_STRING;
	static std::string NB_OPTIMAL_INTERVAL_COUNT_WHOLE_WEIGHT_STRING;
	static std::string NB_OPTIMAL_INTERVAL_COUNT_VISCERA_WEIGHT_STRING;
	static std::string NB_OPTIMAL_INTERVAL_COUNT_SHELL_WEIGHT_STRING;
	static std::string NB_OPTIMAL_INTERVAL_COUNT_SHUCKED_WEIGHT_STRING;
};