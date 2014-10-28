#include "Naive_Bayes.h"
#include <iostream>

void Naive_Bayes::calculate_conditional_probabilities(std::vector<Abalone> &Abalones, std::set<int> &classes, std::set<char> &Sex_classes, int N_learning)
{
	std::map <int, int> classes_map;
	for (int age_class : classes)
	{
		// for classes frequency
		classes_map.insert(std::pair<int, int>(age_class, 0));
		//for Sex conditional probabilities
		std::map <char, float> temp_map;
		for (char sex : Sex_classes)
		{		
			temp_map.insert(std::pair<char, float>(sex, 0));			
		}
		this->conditional_probabilities_Sex.insert(std::pair <int, std::map<char, float> >(age_class, temp_map));
		//for conditional probabilities of other attributes 
		std::map <int, float> temp_map2;
		for (int i = 0; i < classes.size(); i++)
		{
			temp_map2.insert(std::pair<int, float>(i, 0));
		}
		this->conditional_probabilities_Diameter.insert(std::pair <int, std::map<int, float> >(age_class, temp_map2));
		this->conditional_probabilities_Height.insert(std::pair <int, std::map<int, float> >(age_class, temp_map2));
		this->conditional_probabilities_Length.insert(std::pair <int, std::map<int, float> >(age_class, temp_map2));
		this->conditional_probabilities_Shell_weight.insert(std::pair <int, std::map<int, float> >(age_class, temp_map2));
		this->conditional_probabilities_Shucked_weight.insert(std::pair <int, std::map<int, float> >(age_class, temp_map2));
		this->conditional_probabilities_Viscera_weight.insert(std::pair <int, std::map<int, float> >(age_class, temp_map2));
		this->conditional_probabilities_Whole_weight.insert(std::pair <int, std::map<int, float> >(age_class, temp_map2));
	}

	for (int i = 0; i < N_learning; i++)
	{
		classes_map.at(Abalones[i].get_Rings())++;
		this->conditional_probabilities_Sex.at(Abalones[i].get_Rings()).at(Abalones[i].get_Sex())++;
		this->conditional_probabilities_Diameter.at(Abalones[i].get_Rings()).at(
			Abalone::get_int_class_from_float(classes.size(), Abalone::min_Diameter, Abalone::max_Diameter, Abalones[i].get_Diameter()))++;
		this->conditional_probabilities_Height.at(Abalones[i].get_Rings()).at(
			Abalone::get_int_class_from_float(classes.size(), Abalone::min_Height, Abalone::max_Height, Abalones[i].get_Height()))++;
		this->conditional_probabilities_Length.at(Abalones[i].get_Rings()).at(
			Abalone::get_int_class_from_float(classes.size(), Abalone::min_Length, Abalone::max_Length, Abalones[i].get_Length()))++;
		this->conditional_probabilities_Shell_weight.at(Abalones[i].get_Rings()).at(
			Abalone::get_int_class_from_float(classes.size(), Abalone::min_Shell_weight, Abalone::max_Shell_weight, Abalones[i].get_Shell_weight()))++;
		this->conditional_probabilities_Shucked_weight.at(Abalones[i].get_Rings()).at(
			Abalone::get_int_class_from_float(classes.size(), Abalone::min_Shucked_weight, Abalone::max_Shucked_weight, Abalones[i].get_Shucked_weight()))++;
		this->conditional_probabilities_Viscera_weight.at(Abalones[i].get_Rings()).at(
			Abalone::get_int_class_from_float(classes.size(), Abalone::min_Viscera_weight, Abalone::max_Viscera_weight, Abalones[i].get_Viscera_weight()))++;
		this->conditional_probabilities_Whole_weight.at(Abalones[i].get_Rings()).at(
			Abalone::get_int_class_from_float(classes.size(), Abalone::min_Whole_weight, Abalone::max_Whole_weight, Abalones[i].get_Whole_weight()))++;
	}
	for (int age_class : classes)
	{
		for (char sex : Sex_classes)
		{
			this->conditional_probabilities_Sex.at(age_class).at(sex) /= classes_map.at(age_class);
		}
		for (int i = 0; i < classes.size(); i++)
		{
			this->conditional_probabilities_Diameter.at(age_class).at(i) /= classes_map.at(age_class);
			this->conditional_probabilities_Length.at(age_class).at(i) /= classes_map.at(age_class);
			this->conditional_probabilities_Height.at(age_class).at(i) /= classes_map.at(age_class);
			this->conditional_probabilities_Shell_weight.at(age_class).at(i) /= classes_map.at(age_class);
			this->conditional_probabilities_Shucked_weight.at(age_class).at(i) /= classes_map.at(age_class);
			this->conditional_probabilities_Viscera_weight.at(age_class).at(i) /= classes_map.at(age_class);
			this->conditional_probabilities_Whole_weight.at(age_class).at(i) /= classes_map.at(age_class);
		}
	}
}

void Naive_Bayes::calculate_classes_probabilities(std::vector<Abalone> &Abalones, std::set<int> &classes, int N_learning)
{
	for (int age_class : classes)
	{
		this->classes_probabilities.insert(std::pair<int, float>(age_class, 0));
	}
	for (int i = 0; i < N_learning; i++)
	{
		this->classes_probabilities.at(Abalones[i].get_Rings())++;
	}
	for (int age_class : classes)
	{
		this->classes_probabilities.at(age_class) /= N_learning;
	}
}

void Naive_Bayes::show_classes_probabilities()
{
	std::cout << std::endl << "Naive Bayes method " << std::endl << " Classes probabilities " << std::endl;
	for (std::pair<int, float> pair : classes_probabilities)
	{
		std::cout << pair.first << " - " << pair.second << std::endl;
	}
}

int Naive_Bayes::predict_Abalone_age(Abalone A, std::set<int> &classes)
{
	int Diameter_class = Abalone::get_int_class_from_float(classes.size(), Abalone::min_Diameter, Abalone::max_Diameter, A.get_Diameter()),
		Length_class = Abalone::get_int_class_from_float(classes.size(), Abalone::min_Length, Abalone::max_Length, A.get_Length()),
		Height_class = Abalone::get_int_class_from_float(classes.size(), Abalone::min_Height, Abalone::max_Height, A.get_Height()),
		Shell_weight_class = Abalone::get_int_class_from_float(classes.size(), Abalone::min_Shell_weight, Abalone::max_Shell_weight, A.get_Shell_weight()),
		Shucked_weight_class = Abalone::get_int_class_from_float(classes.size(), Abalone::min_Shucked_weight, Abalone::max_Shucked_weight, A.get_Shucked_weight()),
		Viscera_weight_class = Abalone::get_int_class_from_float(classes.size(), Abalone::min_Viscera_weight, Abalone::max_Viscera_weight, A.get_Viscera_weight()),
		Whole_weight_class = Abalone::get_int_class_from_float(classes.size(), Abalone::min_Whole_weight, Abalone::max_Whole_weight, A.get_Whole_weight());
	int res = 1000000000, result_class = 0;
	float eps = pow(10, -7);
	for (int c : classes)
	{
		float tmp = log(this->classes_probabilities.at(c) + eps) +
			log(this->conditional_probabilities_Sex.at(c).at(A.get_Sex()) + eps) +
			log(this->conditional_probabilities_Length.at(c).at(Length_class) + eps) +
			log(this->conditional_probabilities_Diameter.at(c).at(Diameter_class) + eps) +
			log(this->conditional_probabilities_Height.at(c).at(Height_class) + pow(10, -7)) +
			log(this->conditional_probabilities_Shell_weight.at(c).at(Shell_weight_class) + eps) +
			log(this->conditional_probabilities_Shucked_weight.at(c).at(Shucked_weight_class) + eps) +
			log(this->conditional_probabilities_Viscera_weight.at(c).at(Viscera_weight_class) + eps) +
			log(this->conditional_probabilities_Whole_weight.at(c).at(Whole_weight_class) + eps);
		if (res > -tmp)
		{
			res = -tmp;
			result_class = c;
		}
		
	}
	return result_class;
}

float Naive_Bayes::calculate_precision_of_prediction(std::vector<Abalone> &test_Abalones, std::set<int> &classes, int precision)
{
	float almoust_right_answers = 0;
	for (Abalone a : test_Abalones)
	{
		int real_age = a.get_Rings(),
			predicted_age = predict_Abalone_age(a, classes);
		if (abs(real_age - predicted_age) <= precision)
		{
			almoust_right_answers++;
		}
	}
	return (almoust_right_answers / test_Abalones.size());
}