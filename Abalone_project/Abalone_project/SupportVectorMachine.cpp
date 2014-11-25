#include "SupportVectorMachine.h"

svm_model * SupportVectorMachine::get_svm_model(std::vector<Abalone> &learning_Abalones)
{
	svm_problem SVM_Problem;
	SVM_Problem.l = learning_Abalones.size();
	SVM_Problem.y = Abalone::get_target_values(learning_Abalones);
	svm_node **x = new svm_node*[learning_Abalones.size()];
	for (int i = 0; i < learning_Abalones.size(); i++)
	{
		x[i] = new svm_node[9];
		svm_node node1; node1.index = 1; node1.value = learning_Abalones[i].get_Sex();
		x[i][0] = node1;
		svm_node node2; node2.index = 2; node2.value = learning_Abalones[i].get_Diameter();
		x[i][1] = node2;
		svm_node node3; node3.index = 3; node3.value = learning_Abalones[i].get_Height();
		x[i][2] = node3;
		svm_node node4; node4.index = 4; node4.value = learning_Abalones[i].get_Length();
		x[i][3] = node4;
		svm_node node5; node5.index = 5; node5.value = learning_Abalones[i].get_Shell_weight();
		x[i][4] = node5;
		svm_node node6; node6.index = 6; node6.value = learning_Abalones[i].get_Shucked_weight();
		x[i][5] = node6;
		svm_node node7; node7.index = 7; node7.value = learning_Abalones[i].get_Viscera_weight();
		x[i][6] = node7;
		svm_node node8; node8.index = 8; node8.value = learning_Abalones[i].get_Whole_weight();
		x[i][7] = node8;
		svm_node node9; node9.index = -1; node9.value = '?';
		x[i][8] = node9;
	}
	SVM_Problem.x = x;
	svm_parameter SVM_Parameter;
	SVM_Parameter.C = 1;
	SVM_Parameter.svm_type = C_SVC;
	SVM_Parameter.kernel_type = LINEAR;
	SVM_Parameter.degree = 3; /* for poly */
	SVM_Parameter.gamma = 2; /* for poly/rbf/sigmoid */
	SVM_Parameter.coef0 = 1; /* for poly/sigmoid */
	SVM_Parameter.cache_size = 64;
	SVM_Parameter.eps = 0.001;
	SVM_Parameter.nr_weight = 0;
	svm_check_parameter(&SVM_Problem, &SVM_Parameter);
	 
	svm_model *model = svm_train(&SVM_Problem, &SVM_Parameter);

	/*for (int i = 0; i < learning_Abalones.size(); i++)
	{
		delete[] x[i];
	}
	delete[] x;
	delete SVM_Problem.y;*/

	return model;
}

int SupportVectorMachine::predict_age(Abalone a, svm_model *model)
{
	svm_node *nodes = new svm_node[9];
	svm_node node1; node1.index = 1; node1.value = a.get_Sex();
	nodes[0] = node1;
	svm_node node2; node2.index = 2; node2.value = a.get_Diameter();
	nodes[1] = node2;
	svm_node node3; node3.index = 3; node3.value = a.get_Height();
	nodes[2] = node3;
	svm_node node4; node4.index = 4; node4.value = a.get_Length();
	nodes[3] = node4;
	svm_node node5; node5.index = 5; node5.value = a.get_Shell_weight();
	nodes[4] = node5;
	svm_node node6; node6.index = 6; node6.value = a.get_Shucked_weight();
	nodes[5] = node6;
	svm_node node7; node7.index = 7; node7.value = a.get_Viscera_weight();
	nodes[6] = node7;
	svm_node node8; node8.index = 8; node8.value = a.get_Whole_weight();
	nodes[7] = node8;
	svm_node node9; node9.index = -1; node9.value = '?';
	nodes[8] = node9;
	double result = svm_predict(model, nodes);
	//delete[] nodes;
	return result;
}
double SupportVectorMachine::calculate_precision_of_prediction(std::vector<Abalone> &test_Abalones, svm_model *model, int precision)
{
	float almoust_right_answers = 0;
	for (Abalone a : test_Abalones)
	{
		int real_age = a.get_Rings(),
			predicted_age = predict_age(a, model);
		if (predicted_age - ((int)(predicted_age)) > 0.5){ predicted_age = (int)predicted_age + 1; }
		else { predicted_age = (int)predicted_age; }
		if (abs(real_age - predicted_age) <= precision)
		{
			almoust_right_answers++;
		}
	}
	return (almoust_right_answers / test_Abalones.size());
}