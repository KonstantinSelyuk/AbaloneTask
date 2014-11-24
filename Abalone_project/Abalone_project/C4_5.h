#pragma once
#include "Abalone.h"
#include "Parser.h"
#include <iostream>
#include <algorithm>
#include <time.h>

class Condition {
public:
	float entropy;
	Global::ATTRIBUTES TAG;
	Condition(){ entropy = 0; TAG = Global::DIAMETER; }
	virtual ~Condition(){ /*std::cout << "DESTRUCTOR Condition " << std::endl;*/ }
	Condition(float entropy, Global::ATTRIBUTES TAG){ this->entropy = entropy; this->TAG = TAG; }
	static bool compare(Condition *a, Condition *b){ return a->entropy < b->entropy; }
	virtual std::string to_string(){ return Global::attribute_to_string(TAG).append(Parser::delimiter_space).append(std::to_string(entropy)); }
};
class Equally : public Condition
{
public:
	Equally() : Condition(){}
	Equally(float entropy, Global::ATTRIBUTES TAG, std::set<char> classes) : Condition(entropy, TAG){ this->classes = classes; }
	~Equally(){ /*std::cout << "DESTRUCTOR Equally " << std::endl;*/ }
	std::set<char> classes;
	std::string to_string(){ return Condition::to_string(); }
};
class Less : public Condition
{
public:
	float threshold;
	Less() : Condition(){ threshold = 0; }
	Less(float entropy, Global::ATTRIBUTES TAG, float threshold) : Condition(entropy, TAG){ this->threshold = threshold; }
	~Less(){ /*std::cout << "DESTRUCTOR Less " << std::endl;*/ }
	std::string to_string(){ return Condition::to_string().append(Parser::delimiter_space).append(std::to_string(threshold)); }
};

class Node
{
public:
	static int count;
	int id;
	int result_class;
	Condition *condition;
	Node(){ isLeave = false; father = NULL; id = ++count; result_class = -1; Sex_class = '-'; condition = new Condition(); }
	Node(Node * f){ father = f; isLeave = false; id = ++count; result_class = -1; Sex_class = '-'; condition = new Condition(); }
	~Node()
	{ 
		delete condition; 
		for (Node *n : children){ delete n; } 
	}
	Node * get_father(){ return this->father; }
	void set_father(Node * father){ this->father = father; }
	bool is_leave(){ return isLeave; }
	void set_isLeave(bool isLeave) { this->isLeave = isLeave; }
	void add_child(Node * ch){ children.push_back(ch); }
	std::vector<Node *> get_children(){ return children; }
	std::string to_string();
	//Only for Equally situation
	char Sex_class;
private:
	bool isLeave;
	std::vector<Node *> children;
	Node *father;
	
};

class C4_5
{
public:
	float info(std::vector<Abalone> &Abalones, std::set<int> &classes);
	float info(std::vector<Abalone> &Abalones, std::vector<Abalone>::iterator first, std::vector<Abalone>::iterator last, std::set<int> &classes);
	Condition * info_Sex(std::vector<Abalone> &Abalones, std::set<char> &Sex_classes, std::set<int> &classes);
	float info_Diameter_old(std::vector<Abalone> &Abalones, std::set<int> &classes);
	Condition * info_float_parameter(std::vector<Abalone> &Abalones, std::set<int> &classes, Global::ATTRIBUTES TAG);
	void build_desigion_tree(Node * node, std::vector<Abalone> &Abalones, std::set<char> &Sex_classes, std::set<int> &classes);
	Condition * find_min_entropy(std::vector<Abalone> &learning_Abalones, std::set<char> &Sex_classes, std::set<int> &classes);
	int predict_Abalone_age(Abalone A, Node *DesigionTree);
	float calculate_precision_of_prediction(std::vector<Abalone> &test_Abalones, Node *DesigionTree, int precision);
	void desigion_tree_to_file(Node *tree, std::string file_name);
	Node * C4_5::tree_from_file(std::string file_name, std::set<char> &Sex_classes);
private:
	float full_tree_info;
	void get_uniq_values(std::vector<Abalone> &Abalones, std::vector<float> &all_values, Global::ATTRIBUTES TAG, int count);
	float get_parameter_value(Abalone a, Global::ATTRIBUTES TAG);
	void add_node_id_to_ofstream(Node * node, std::ofstream &fout);
	void add_node_to_ofstream(Node * node, std::ofstream &fout);
};