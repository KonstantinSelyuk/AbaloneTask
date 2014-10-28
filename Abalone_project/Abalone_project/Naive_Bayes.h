#pragma once
#include "Abalone.h"

class Naive_Bayes
{
private:
	typedef std::map < int, std::map <int, float> > param;
	std::map <int, std::map <char, float> > conditional_probabilities_Sex;
	param conditional_probabilities_Length;
	param conditional_probabilities_Diameter;
	param conditional_probabilities_Height;
	param conditional_probabilities_Whole_weight;
	param conditional_probabilities_Shucked_weight;
	param conditional_probabilities_Viscera_weight;
	param conditional_probabilities_Shell_weight;
	std::map <int, float> classes_probabilities;
public:
	std::map <int, std::map <char, float> > get_conditional_probabilities_Sex(){ return this->conditional_probabilities_Sex; }
	std::map <int, std::map <int, float> > get_conditional_probabilities_Length(){ return this->conditional_probabilities_Length; }
	void calculate_conditional_probabilities(std::vector<Abalone> &Abalones, std::set<int> &classes, std::set<char> &Sex_classes, int N_learning);
	void calculate_classes_probabilities(std::vector<Abalone> &Abalones, std::set<int> &classes, int N_learning);
	void show_classes_probabilities();
	int predict_Abalone_age(Abalone A, std::set<int> &classes);
	float calculate_precision_of_prediction(std::vector<Abalone> &test_Abalones, std::set<int> &classes, int precision);
};