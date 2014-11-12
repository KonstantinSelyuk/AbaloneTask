#pragma once
#include "Abalone.h"
#include "Parser.h"
#include "Global.h"
#include <iostream>

class Naive_Bayes
{
private:
	typedef std::map < int, std::map <int, float> > probability_map;
	std::map <int, std::map <char, float> > conditional_probabilities_Sex;
	probability_map conditional_probabilities_Length;
	probability_map conditional_probabilities_Diameter;
	probability_map conditional_probabilities_Height;
	probability_map conditional_probabilities_Whole_weight;
	probability_map conditional_probabilities_Shucked_weight;
	probability_map conditional_probabilities_Viscera_weight;
	probability_map conditional_probabilities_Shell_weight;
	std::map <int, float> classes_probabilities;
	int optimal_interval_count_Length;
	int optimal_interval_count_Diameter;
	int optimal_interval_count_Height;
	int optimal_interval_count_Whole_weight;
	int optimal_interval_count_Shucked_weight;
	int optimal_interval_count_Viscera_weight;
	int optimal_interval_count_Shell_weight;
	bool is_classes_probabilities_calculated;
	int find_max_precision(Global::ATTRIBUTES TAG, std::vector<Abalone> &learning_Abalones, std::vector<Abalone> &test_Abalones, std::set<int> &classes, std::set<char> &Sex_classes, int precision);
	bool set_NB_parameters_from_file(std::string file_name);
public:
	Naive_Bayes();
	Naive_Bayes(int default_optimal_count);
	std::map <int, std::map <char, float> > get_conditional_probabilities_Sex(){ return this->conditional_probabilities_Sex; }
	std::map <int, std::map <int, float> > get_conditional_probabilities_Length(){ return this->conditional_probabilities_Length; }

	int get_optimal_interval_count_Length(){ return this->optimal_interval_count_Length; }
	int get_optimal_interval_count_Diameter(){ return this->optimal_interval_count_Diameter; }
	int get_optimal_interval_count_Height(){ return this->optimal_interval_count_Height; }
	int get_optimal_interval_count_Whole_weight(){ return this->optimal_interval_count_Whole_weight; }
	int get_optimal_interval_count_Shucked_weight(){ return this->optimal_interval_count_Shucked_weight; }
	int get_optimal_interval_count_Viscera_weight(){ return this->optimal_interval_count_Viscera_weight; }
	int get_optimal_interval_count_Shell_weight(){ return this->optimal_interval_count_Shell_weight; }

	void set_optimal_interval_count_Length(int optimal_interval_count_Length){ this->optimal_interval_count_Length = optimal_interval_count_Length; }
	void set_optimal_interval_count_Diameter(int optimal_interval_count_Diameter){ this->optimal_interval_count_Diameter = optimal_interval_count_Diameter; }
	void set_optimal_interval_count_Height(int optimal_interval_count_Height){ this->optimal_interval_count_Height = optimal_interval_count_Height; }
	void set_optimal_interval_count_Whole_weight(int optimal_interval_count_Whole_weight){ this->optimal_interval_count_Whole_weight = optimal_interval_count_Whole_weight; }
	void set_optimal_interval_count_Shucked_weight(int optimal_interval_count_Shucked_weight){ this->optimal_interval_count_Shucked_weight = optimal_interval_count_Shucked_weight; }
	void set_optimal_interval_count_Viscera_weight(int optimal_interval_count_Viscera_weight){ this->optimal_interval_count_Viscera_weight = optimal_interval_count_Viscera_weight; }
	void set_optimal_interval_count_Shell_weight(int optimal_interval_count_Shell_weight){ this->optimal_interval_count_Shell_weight = optimal_interval_count_Shell_weight; }

	void calculate_conditional_probabilities(std::vector<Abalone> &Abalones, std::set<int> &classes, std::set<char> &Sex_classes);
	void calculate_classes_probabilities(std::vector<Abalone> &Abalones, std::set<int> &classes);
	void show_classes_probabilities();
	int predict_Abalone_age(Abalone A, std::set<int> &classes);
	float calculate_precision_of_prediction(std::vector<Abalone> &test_Abalones, std::set<int> &classes, int precision);
	int find_optimal_interval_counts(std::vector<Abalone> &learning_Abalones, std::vector<Abalone> &test_Abalones, std::set<int> &classes, std::set<char> &Sex_classes, int precision, std::string file_name);
	bool is_optimal_interval_counts_calculated(std::string file_name);
};