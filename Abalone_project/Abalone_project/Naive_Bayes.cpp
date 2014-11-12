#include "Naive_Bayes.h"

Naive_Bayes::Naive_Bayes()
{
	this->optimal_interval_count_Diameter = 1;
	this->optimal_interval_count_Length = 1;
	this->optimal_interval_count_Height = 1;
	this->optimal_interval_count_Whole_weight = 1;
	this->optimal_interval_count_Viscera_weight = 1;
	this->optimal_interval_count_Shell_weight = 1;
	this->optimal_interval_count_Shucked_weight = 1;
	this->is_classes_probabilities_calculated = false;
}

Naive_Bayes::Naive_Bayes(int default_optimal_count)
{
	this->optimal_interval_count_Diameter = default_optimal_count;
	this->optimal_interval_count_Length = default_optimal_count;
	this->optimal_interval_count_Height = default_optimal_count;
	this->optimal_interval_count_Whole_weight = default_optimal_count;
	this->optimal_interval_count_Viscera_weight = default_optimal_count;
	this->optimal_interval_count_Shell_weight = default_optimal_count;
	this->optimal_interval_count_Shucked_weight = default_optimal_count;
	this->is_classes_probabilities_calculated = false;
}

void Naive_Bayes::calculate_conditional_probabilities(std::vector<Abalone> &Abalones, std::set<int> &classes, std::set<char> &Sex_classes)
{
	if (!is_classes_probabilities_calculated)
	{
		calculate_classes_probabilities(Abalones, classes);
	}
	this->conditional_probabilities_Sex.clear();
	this->conditional_probabilities_Diameter.clear();
	this->conditional_probabilities_Height.clear();
	this->conditional_probabilities_Length.clear();
	this->conditional_probabilities_Shell_weight.clear();
	this->conditional_probabilities_Shucked_weight.clear();
	this->conditional_probabilities_Viscera_weight.clear();
	this->conditional_probabilities_Whole_weight.clear();

	int N_learning = Abalones.size();
	for (int age_class : classes)
	{
		//for Sex conditional probabilities
		std::map <char, float> temp_map;
		for (char sex : Sex_classes)
		{		
			temp_map.insert(std::pair<char, float>(sex, 0));			
		}
		this->conditional_probabilities_Sex.insert(std::pair <int, std::map<char, float> >(age_class, temp_map));
		//for conditional probabilities of other attributes 
		// Diameter
		std::map <int, float> temp_map_2;
		for (int i = 0; i < this->optimal_interval_count_Diameter; i++)
		{
			temp_map_2.insert(std::pair<int, float>(i, 0));
		}
		this->conditional_probabilities_Diameter.insert(std::pair <int, std::map<int, float> >(age_class, temp_map_2));
		// Length
		temp_map_2.clear();
		for (int i = 0; i < this->optimal_interval_count_Length; i++)
		{
			temp_map_2.insert(std::pair<int, float>(i, 0));
		}
		this->conditional_probabilities_Length.insert(std::pair <int, std::map<int, float> >(age_class, temp_map_2));
		// Height
		temp_map_2.clear();
		for (int i = 0; i < this->optimal_interval_count_Height; i++)
		{
			temp_map_2.insert(std::pair<int, float>(i, 0));
		}
		this->conditional_probabilities_Height.insert(std::pair <int, std::map<int, float> >(age_class, temp_map_2));
		// Whole_weight
		temp_map_2.clear();
		for (int i = 0; i < this->optimal_interval_count_Whole_weight; i++)
		{
			temp_map_2.insert(std::pair<int, float>(i, 0));
		}
		this->conditional_probabilities_Whole_weight.insert(std::pair <int, std::map<int, float> >(age_class, temp_map_2));
		// Viscera_weight
		temp_map_2.clear();
		for (int i = 0; i < this->optimal_interval_count_Viscera_weight; i++)
		{
			temp_map_2.insert(std::pair<int, float>(i, 0));
		}
		this->conditional_probabilities_Viscera_weight.insert(std::pair <int, std::map<int, float> >(age_class, temp_map_2));
		// Shell_weight
		temp_map_2.clear();
		for (int i = 0; i < this->optimal_interval_count_Shell_weight; i++)
		{
			temp_map_2.insert(std::pair<int, float>(i, 0));
		}
		this->conditional_probabilities_Shell_weight.insert(std::pair <int, std::map<int, float> >(age_class, temp_map_2));
		// Shucked_weight
		temp_map_2.clear();
		for (int i = 0; i < this->optimal_interval_count_Shucked_weight; i++)
		{
			temp_map_2.insert(std::pair<int, float>(i, 0));
		}
		this->conditional_probabilities_Shucked_weight.insert(std::pair <int, std::map<int, float> >(age_class, temp_map_2));			
	}

	for (int i = 0; i < N_learning; i++)
	{
		this->conditional_probabilities_Sex.at(Abalones[i].get_Rings()).at(Abalones[i].get_Sex())++;
		this->conditional_probabilities_Diameter.at(Abalones[i].get_Rings()).at(
			Abalone::get_int_class_from_float(optimal_interval_count_Diameter, Abalone::min_Diameter, Abalone::max_Diameter, Abalones[i].get_Diameter()))++;
		this->conditional_probabilities_Height.at(Abalones[i].get_Rings()).at(
			Abalone::get_int_class_from_float(optimal_interval_count_Height, Abalone::min_Height, Abalone::max_Height, Abalones[i].get_Height()))++;
		this->conditional_probabilities_Length.at(Abalones[i].get_Rings()).at(
			Abalone::get_int_class_from_float(optimal_interval_count_Length, Abalone::min_Length, Abalone::max_Length, Abalones[i].get_Length()))++;
		this->conditional_probabilities_Shell_weight.at(Abalones[i].get_Rings()).at(
			Abalone::get_int_class_from_float(optimal_interval_count_Shell_weight, Abalone::min_Shell_weight, Abalone::max_Shell_weight, Abalones[i].get_Shell_weight()))++;
		this->conditional_probabilities_Shucked_weight.at(Abalones[i].get_Rings()).at(
			Abalone::get_int_class_from_float(optimal_interval_count_Shucked_weight, Abalone::min_Shucked_weight, Abalone::max_Shucked_weight, Abalones[i].get_Shucked_weight()))++;
		this->conditional_probabilities_Viscera_weight.at(Abalones[i].get_Rings()).at(
			Abalone::get_int_class_from_float(optimal_interval_count_Viscera_weight, Abalone::min_Viscera_weight, Abalone::max_Viscera_weight, Abalones[i].get_Viscera_weight()))++;
		this->conditional_probabilities_Whole_weight.at(Abalones[i].get_Rings()).at(
			Abalone::get_int_class_from_float(optimal_interval_count_Whole_weight, Abalone::min_Whole_weight, Abalone::max_Whole_weight, Abalones[i].get_Whole_weight()))++;
	}
	for (int age_class : classes)
	{
		int p = this->classes_probabilities.at(age_class) * N_learning;
		for (char sex : Sex_classes)
		{
			this->conditional_probabilities_Sex.at(age_class).at(sex) /= p;
		}
		for (int i = 0; i < optimal_interval_count_Diameter; i++)
		{
			this->conditional_probabilities_Diameter.at(age_class).at(i) /= p;
		}
		for (int i = 0; i < optimal_interval_count_Length; i++)
		{
			this->conditional_probabilities_Length.at(age_class).at(i) /= p;
		}
		for (int i = 0; i < optimal_interval_count_Height; i++)
		{
			this->conditional_probabilities_Height.at(age_class).at(i) /= p;
		}
		for (int i = 0; i < optimal_interval_count_Shell_weight; i++)
		{
			this->conditional_probabilities_Shell_weight.at(age_class).at(i) /= p;
		}
		for (int i = 0; i < optimal_interval_count_Shucked_weight; i++)
		{
			this->conditional_probabilities_Shucked_weight.at(age_class).at(i) /= p;
		}
		for (int i = 0; i < optimal_interval_count_Viscera_weight; i++)
		{
			this->conditional_probabilities_Viscera_weight.at(age_class).at(i) /= p;
		}
		for (int i = 0; i < optimal_interval_count_Whole_weight; i++)
		{
			this->conditional_probabilities_Whole_weight.at(age_class).at(i) /= p;
		}
	}
}

void Naive_Bayes::calculate_classes_probabilities(std::vector<Abalone> &Abalones, std::set<int> &classes)
{
	int N_learning = Abalones.size();
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
	this->is_classes_probabilities_calculated = true;
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
	int Diameter_class = Abalone::get_int_class_from_float(optimal_interval_count_Diameter, Abalone::min_Diameter, Abalone::max_Diameter, A.get_Diameter()),
		Length_class = Abalone::get_int_class_from_float(optimal_interval_count_Length, Abalone::min_Length, Abalone::max_Length, A.get_Length()),
		Height_class = Abalone::get_int_class_from_float(optimal_interval_count_Height, Abalone::min_Height, Abalone::max_Height, A.get_Height()),
		Shell_weight_class = Abalone::get_int_class_from_float(optimal_interval_count_Shell_weight, Abalone::min_Shell_weight, Abalone::max_Shell_weight, A.get_Shell_weight()),
		Shucked_weight_class = Abalone::get_int_class_from_float(optimal_interval_count_Shucked_weight, Abalone::min_Shucked_weight, Abalone::max_Shucked_weight, A.get_Shucked_weight()),
		Viscera_weight_class = Abalone::get_int_class_from_float(optimal_interval_count_Viscera_weight, Abalone::min_Viscera_weight, Abalone::max_Viscera_weight, A.get_Viscera_weight()),
		Whole_weight_class = Abalone::get_int_class_from_float(optimal_interval_count_Whole_weight, Abalone::min_Whole_weight, Abalone::max_Whole_weight, A.get_Whole_weight());
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

int Naive_Bayes::find_optimal_interval_counts(std::vector<Abalone> &learning_Abalones, std::vector<Abalone> &test_Abalones, std::set<int> &classes, std::set<char> &Sex_classes, int precision, std::string file_name)
{
	if (is_optimal_interval_counts_calculated(file_name))
	{
		char answer;
		std::cout << " Optional interval counts are already calculated: " << std::endl << std::endl <<
			Parser::file_to_string(file_name) << std::endl << std::endl << "If you want to recalculate, press 'y' " << std::endl << std::endl;
		std::cin >> answer;
		if (answer != 'y' && answer != 'Y')
		{
			// set all parameters from file
			set_NB_parameters_from_file(file_name);
			calculate_conditional_probabilities(learning_Abalones, classes, Sex_classes);
			return 0;
		}
	}
	this->optimal_interval_count_Diameter = find_max_precision(Global::DIAMETER, learning_Abalones, test_Abalones, classes, Sex_classes, precision);
	this->optimal_interval_count_Length = find_max_precision(Global::LENGTH, learning_Abalones, test_Abalones, classes, Sex_classes, precision);
	this->optimal_interval_count_Height = find_max_precision(Global::HEIGHT, learning_Abalones, test_Abalones, classes, Sex_classes, precision);
	this->optimal_interval_count_Viscera_weight = find_max_precision(Global::VISCERA_WEIGHT, learning_Abalones, test_Abalones, classes, Sex_classes, precision);
	this->optimal_interval_count_Shell_weight = find_max_precision(Global::SHELL_WEIGHT, learning_Abalones, test_Abalones, classes, Sex_classes, precision);
	this->optimal_interval_count_Shucked_weight = find_max_precision(Global::SHUCKED_WEIGHT, learning_Abalones, test_Abalones, classes, Sex_classes, precision);
	this->optimal_interval_count_Whole_weight = find_max_precision(Global::WHOLE_WEIGHT, learning_Abalones, test_Abalones, classes, Sex_classes, precision);
	calculate_conditional_probabilities(learning_Abalones, classes, Sex_classes);

	std::map<std::string, std::string> map_ofparameters;
	map_ofparameters.insert(std::pair<std::string, std::string>(Global::NB_OPTIMAL_INTERVAL_COUNT_DIAMETER_STRING, std::to_string(this->optimal_interval_count_Diameter)));
	map_ofparameters.insert(std::pair<std::string, std::string>(Global::NB_OPTIMAL_INTERVAL_COUNT_LENGTH_STRING, std::to_string(this->optimal_interval_count_Length)));
	map_ofparameters.insert(std::pair<std::string, std::string>(Global::NB_OPTIMAL_INTERVAL_COUNT_HEIGHT_STRING, std::to_string(this->optimal_interval_count_Height)));
	map_ofparameters.insert(std::pair<std::string, std::string>(Global::NB_OPTIMAL_INTERVAL_COUNT_VISCERA_WEIGHT_STRING, std::to_string(this->optimal_interval_count_Viscera_weight)));
	map_ofparameters.insert(std::pair<std::string, std::string>(Global::NB_OPTIMAL_INTERVAL_COUNT_SHELL_WEIGHT_STRING, std::to_string(this->optimal_interval_count_Shell_weight)));
	map_ofparameters.insert(std::pair<std::string, std::string>(Global::NB_OPTIMAL_INTERVAL_COUNT_SHUCKED_WEIGHT_STRING, std::to_string(this->optimal_interval_count_Shucked_weight)));
	map_ofparameters.insert(std::pair<std::string, std::string>(Global::NB_OPTIMAL_INTERVAL_COUNT_WHOLE_WEIGHT_STRING, std::to_string(this->optimal_interval_count_Whole_weight)));
	Parser::write_to_file_parameters(file_name, map_ofparameters);
	return 0;
}

bool Naive_Bayes::is_optimal_interval_counts_calculated(std::string file_name)
{
	std::map<std::string, std::string> parameters = Parser::get_parameters_from_file(file_name);
	if (parameters.count(Global::NB_OPTIMAL_INTERVAL_COUNT_DIAMETER_STRING) == 0 ||
		parameters.count(Global::NB_OPTIMAL_INTERVAL_COUNT_HEIGHT_STRING) == 0 ||
		parameters.count(Global::NB_OPTIMAL_INTERVAL_COUNT_LENGTH_STRING) == 0 ||
		parameters.count(Global::NB_OPTIMAL_INTERVAL_COUNT_SHELL_WEIGHT_STRING) == 0 ||
		parameters.count(Global::NB_OPTIMAL_INTERVAL_COUNT_WHOLE_WEIGHT_STRING) == 0 ||
		parameters.count(Global::NB_OPTIMAL_INTERVAL_COUNT_SHUCKED_WEIGHT_STRING) == 0 ||
		parameters.count(Global::NB_OPTIMAL_INTERVAL_COUNT_VISCERA_WEIGHT_STRING) == 0)

	{
		return false;
	}
	if (parameters.at(Global::NB_OPTIMAL_INTERVAL_COUNT_DIAMETER_STRING).empty() ||
		parameters.at(Global::NB_OPTIMAL_INTERVAL_COUNT_HEIGHT_STRING).empty() ||
		parameters.at(Global::NB_OPTIMAL_INTERVAL_COUNT_LENGTH_STRING).empty() ||
		parameters.at(Global::NB_OPTIMAL_INTERVAL_COUNT_SHELL_WEIGHT_STRING).empty() ||
		parameters.at(Global::NB_OPTIMAL_INTERVAL_COUNT_WHOLE_WEIGHT_STRING).empty() ||
		parameters.at(Global::NB_OPTIMAL_INTERVAL_COUNT_SHUCKED_WEIGHT_STRING).empty() ||
		parameters.at(Global::NB_OPTIMAL_INTERVAL_COUNT_VISCERA_WEIGHT_STRING).empty())
	{
		return false;
	}
	return true;
}

int Naive_Bayes::find_max_precision(Global::ATTRIBUTES TAG, std::vector<Abalone> &learning_Abalones, std::vector<Abalone> &test_Abalones, std::set<int> &classes, std::set<char> &Sex_classes, int precision)
{
	int N = 50, tmp_count = 0;
	float tmp = 0;
	for (int i = 1; i < N; i++)
	{
		switch (TAG)
		{
		case Global::DIAMETER:
			this->optimal_interval_count_Diameter = i;
			std::cout << "DIAMETER: ";
			break;
		case Global::LENGTH:
			this->optimal_interval_count_Length = i;
			std::cout << "LENGTH: ";
			break;
		case Global::HEIGHT:
			this->optimal_interval_count_Height = i;
			std::cout << "HEIGHT: ";
			break;
		case Global::WHOLE_WEIGHT:
			this->optimal_interval_count_Whole_weight = i;
			std::cout << "WHOLE_WEIGHT: ";
			break;
		case Global::VISCERA_WEIGHT:
			this->optimal_interval_count_Viscera_weight = i;
			std::cout << "VISCERA_WEIGHT: ";
			break;
		case Global::SHELL_WEIGHT:
			this->optimal_interval_count_Shell_weight = i;
			std::cout << "SHELL_WEIGHT: ";
			break;
		case Global::SHUCKED_WEIGHT:
			this->optimal_interval_count_Shucked_weight = i;
			std::cout << "SHUCKED_WEIGHT: ";
			break;
		}
		calculate_conditional_probabilities(learning_Abalones, classes, Sex_classes);
		float pr = calculate_precision_of_prediction(test_Abalones, classes, precision);
		std::cout << pr << "  ";
		if (tmp < pr)
		{
			tmp = pr;
			tmp_count = i;
		}
	}
	std::cout << std::endl << tmp << std::endl;
	return tmp_count;
}

bool Naive_Bayes::set_NB_parameters_from_file(std::string file_name)
{
	std::map<std::string, std::string> m = Parser::get_parameters_from_file(file_name);
	for (std::pair<std::string, std::string> p : m)
	{
		if (p.first.compare(Global::NB_OPTIMAL_INTERVAL_COUNT_DIAMETER_STRING) == 0)
		{
			this->optimal_interval_count_Diameter = atoi(p.second.c_str());
		}
		else if (p.first.compare(Global::NB_OPTIMAL_INTERVAL_COUNT_LENGTH_STRING) == 0)
		{
			this->optimal_interval_count_Length = atoi(p.second.c_str());
		}
		else if (p.first.compare(Global::NB_OPTIMAL_INTERVAL_COUNT_HEIGHT_STRING) == 0)
		{
			this->optimal_interval_count_Height = atoi(p.second.c_str());
		}
		else if (p.first.compare(Global::NB_OPTIMAL_INTERVAL_COUNT_SHELL_WEIGHT_STRING) == 0)
		{
			this->optimal_interval_count_Shell_weight = atoi(p.second.c_str());
		}
		else if (p.first.compare(Global::NB_OPTIMAL_INTERVAL_COUNT_SHUCKED_WEIGHT_STRING) == 0)
		{
			this->optimal_interval_count_Shucked_weight = atoi(p.second.c_str());
		}
		else if (p.first.compare(Global::NB_OPTIMAL_INTERVAL_COUNT_VISCERA_WEIGHT_STRING) == 0)
		{
			this->optimal_interval_count_Viscera_weight = atoi(p.second.c_str());
		}
		else if (p.first.compare(Global::NB_OPTIMAL_INTERVAL_COUNT_WHOLE_WEIGHT_STRING) == 0)
		{
			this->optimal_interval_count_Whole_weight = atoi(p.second.c_str());
		}
	}
	return true;
}