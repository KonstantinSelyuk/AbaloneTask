#pragma once
#include <string>

class Global
{
public:
	enum ATTRIBUTES
	{
		DIAMETER, LENGTH, HEIGHT, WHOLE_WEIGHT, VISCERA_WEIGHT, SHELL_WEIGHT, SHUCKED_WEIGHT, SEX
	};
	static std::string DATA_FILE_NAME;
	static float LEARNING_COEFFICIENT;
	static std::string attribute_to_string(ATTRIBUTES tag);
	// For Naive Bayes
	static std::string PARAMETERS_NAIVE_BAYES_FILE_NAME;
	static std::string NB_OPTIMAL_INTERVAL_COUNT_DIAMETER_STRING;
	static std::string NB_OPTIMAL_INTERVAL_COUNT_LENGTH_STRING;
	static std::string NB_OPTIMAL_INTERVAL_COUNT_HEIGHT_STRING;
	static std::string NB_OPTIMAL_INTERVAL_COUNT_WHOLE_WEIGHT_STRING;
	static std::string NB_OPTIMAL_INTERVAL_COUNT_VISCERA_WEIGHT_STRING;
	static std::string NB_OPTIMAL_INTERVAL_COUNT_SHELL_WEIGHT_STRING;
	static std::string NB_OPTIMAL_INTERVAL_COUNT_SHUCKED_WEIGHT_STRING;

	// For C4.5 algorithm

	/*
	Parameter that constrain the count of unique values for float parameters
	(that is used for decreasing learning time in finding optimal threshold)
	*/
	static int MAX_UNIQUE_VALUES_COUNT;
	static std::string C45_DESIGION_TREE_FILE_NAME;
	static ATTRIBUTES attribute_from_string(std::string s);
};