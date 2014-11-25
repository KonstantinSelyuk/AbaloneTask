#include "libsvm-3.20/svm.h"
#include <vector>
#include "Abalone.h"
class SupportVectorMachine
{
public:
	svm_model * get_svm_model(std::vector<Abalone> &learning_Abalones);
	int predict_age(Abalone a, svm_model *model);
	double calculate_precision_of_prediction(std::vector<Abalone> &test_Abalones, svm_model *model, int precision);
};