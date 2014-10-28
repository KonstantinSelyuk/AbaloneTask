#include <iostream>
#include "Parser.h"
#include "Abalone.h"
#include "Naive_Bayes.h"

template <typename T1, typename T2, typename T3>
void show_map_of_maps(std::map<T1, std::map<T2, T3> > &map_of_maps)
{
	for (std::pair<T1, std::map<T2, T3>> pair : map_of_maps)
	{
		std::cout << pair.first << "  ";
		for (std::pair <T2, T3> pair2 : pair.second)
		{
			std::cout << pair2.second << " ";
		}
		std::cout << std::endl;
	}
}


int main()
{
	//defining Abalones (4177)
	// We will use first 80% (3341) of input data for learning and last 20% (836) 
	std::vector<Abalone> Abalones;
	Parser::get_Abalones_from_data(Abalones, "data.txt");

	// finding classes
	int N = Abalones.size(), N_learning = N * 0.8, first_index_for_checking = N_learning + 1;
	// finding classes

	std::set<int> classes;
	std::set<char> Sex_classes;
	Abalone::define_classes(Abalones, classes, N_learning);
	Abalone::define_Sex_classes(Abalones, Sex_classes, N_learning);
	Abalone::define_max_min_values(Abalones, classes, N_learning);
	std::cout << " Was found " << classes.size() << " classes! " << std::endl;

	//Learning (Naive Bayes method)
	Naive_Bayes NB;

	NB.calculate_classes_probabilities(Abalones, classes, N_learning);
	NB.calculate_conditional_probabilities(Abalones, classes, Sex_classes, N_learning);

	//Predictiong (Naive Bayes method)
	std::vector<Abalone> test_Abalones;
	test_Abalones.insert(test_Abalones.begin(), Abalones.begin() + N_learning, Abalones.end());
	for (int i = 0; i < 5; i++)
	{
		float out_precision = NB.calculate_precision_of_prediction(test_Abalones, classes, i);
		std::cout << "Precision + or - " << i << " years: "<< out_precision * 100 << "% " << std::endl;
	}
	

	
	//show_map_of_maps(NB.get_conditional_probabilities_Length());
	//NB.show_classes_probabilities();
	return 0;
}

