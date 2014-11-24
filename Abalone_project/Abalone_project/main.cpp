

#include "Parser.h"
#include "Abalone.h"
#include "Global.h"
#include "Naive_Bayes.h"
#include "C4_5.h"
#include "Linear_Regression.h"
#include "Linear_Regression_Matrix.h"

#include "libsvm-3.20/svm.h"
//#include "Matrix.h"

template <typename T1, typename T2, typename T3>
void show_map_of_maps(std::map<T1, std::map<T2, T3> > &map_of_maps);
void init();
void run_Naive_Bayes();
void run_C45();
void run_Linear_Regression();
void run_Linear_Regression_Matrix_version();

// Global vriables
std::vector<Abalone> Abalones, learning_Abalones, test_Abalones;
int N, N_learning, first_index_for_checking;
std::set<int> classes;
std::set<char> Sex_classes;

int main()
{
	init();
	run_Naive_Bayes();
	run_C45();
	run_Linear_Regression();
	run_Linear_Regression_Matrix_version();
	


	return 0;
}


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

void init()
{
	//defining Abalones (4177)
	// We will use first 80% (3341) of input data for learning and last 20% (836) for checking

	Parser::get_Abalones_from_data(Abalones, Global::DATA_FILE_NAME);
	N = Abalones.size(); N_learning = N * Global::LEARNING_COEFFICIENT; first_index_for_checking = N_learning + 1;

	learning_Abalones.insert(learning_Abalones.begin(), Abalones.begin(), Abalones.begin() + N_learning);
	test_Abalones.insert(test_Abalones.begin(), Abalones.begin() + N_learning, Abalones.end());

	// finding classes
	Abalone::define_classes(learning_Abalones, classes);
	Abalone::define_Sex_classes(learning_Abalones, Sex_classes);
	Abalone::define_max_min_values(learning_Abalones, classes);
	std::cout << " Was found " << classes.size() << " classes! " << std::endl;
}

void run_Naive_Bayes()
{
	Naive_Bayes NB(1);
	NB.calculate_classes_probabilities(learning_Abalones, classes);
	NB.calculate_conditional_probabilities(learning_Abalones, classes, Sex_classes);
	NB.find_optimal_interval_counts(learning_Abalones, test_Abalones, classes, Sex_classes, 0, Global::PARAMETERS_NAIVE_BAYES_FILE_NAME);

	//Predicting (Naive Bayes method)

	std::cout << "Naive Bayes method " << std::endl;
	for (int i = 0; i < 5; i++)
	{
		double out_precision = NB.calculate_precision_of_prediction(test_Abalones, classes, i);
		std::cout << " Precision + or - " << i << " years: " << out_precision * 100 << "% " << std::endl;
	}
}

void run_C45()
{
	C4_5 C45;

	double f = C45.info(learning_Abalones, classes);
	//Node *tree = new Node();
	//C45.build_desigion_tree(tree, learning_Abalones, Sex_classes, classes);
	//C45.desigion_tree_to_file(tree, Global::C45_DESIGION_TREE_FILE_NAME);
	std::cout << "C4.5 Algorithm " << std::endl;
	Node *tree = C45.tree_from_file(Global::C45_DESIGION_TREE_FILE_NAME, Sex_classes);
	for (int i = 0; i < 5; i++)
	{
		double out_precision = C45.calculate_precision_of_prediction(test_Abalones, tree, i);
		std::cout << " Precision + or - " << i << " years: " << out_precision * 100 << "% " << std::endl;
	}
	delete tree;
}

void run_Linear_Regression()
{
	Linear_Regression LR;
	double * alpha = LR.find_coeff_for_linear_regress(Abalones);
	std::cout << "Linear_Regression method " << std::endl;
	for (int i = 0; i < 5; i++)
	{
		double out_precision = LR.calculate_precision_of_prediction(test_Abalones, alpha, i);
		std::cout << " Precision + or - " << i << " years: " << out_precision * 100 << "% " << std::endl;
	}
	delete[] alpha;
}

void run_Linear_Regression_Matrix_version()
{
	Linear_Regression_Matrix LR_M;
	Matrix<double> alpha_ = LR_M.find_coeff_for_linear_regress(Abalones);
	std::cout << "Linear_Regression (with matrix) method " << std::endl;
	for (int i = 0; i < 5; i++)
	{
		double out_precision = LR_M.calculate_precision_of_prediction(test_Abalones, alpha_, i);
		std::cout << " Precision + or - " << i << " years: " << out_precision * 100 << "% " << std::endl;
	}
}