#include "C4_5.h"

float C4_5::info(std::vector<Abalone> &Abalones, std::set<int> &classes)
{
	std::map<int, float> p;
	for (int i : classes)
	{
		p.insert(std::pair<int, float>(i, 0));
	}
	for (int i = 0; i < Abalones.size(); i++)
	{
		p.at(Abalones[i].get_Rings())++;
	}
	for (int i : classes)
	{
		p.at(i) /= Abalones.size();
	}
	float result = 0;
	for (int i : classes)
	{
		if (p.at(i) != 0)
		{
			result += -p.at(i) * log(p.at(i));
		}
	}
	//std::cout << " - " << Abalones.size() << "  ";
	return result;
}

float C4_5::info(std::vector<Abalone> &Abalones, std::vector<Abalone>::iterator first, std::vector<Abalone>::iterator last, std::set<int> &classes)
{
	std::map<int, float> p;
	for (int i : classes)
	{
		p.insert(std::pair<int, float>(i, 0));
	}
	for (std::vector<Abalone>::iterator it = first; it != last; it++)
	{
		p.at((*it).get_Rings())++;
	}
	for (int i : classes)
	{
		p.at(i) /= (last - first);
	}
	float result = 0;
	for (int i : classes)
	{
		if (p.at(i) != 0)
		{
			result += -p.at(i) * log(p.at(i));
		}
	}
	//std::cout << " - " << (last - first) << "  ";
	return result;
}

Condition * C4_5::info_Sex(std::vector<Abalone> &Abalones, std::set<char> &Sex_classes, std::set<int> &classes)
{
	std::map<char, float> p;
	std::map<char, std::vector<Abalone> > temp;
	for (char i : Sex_classes)
	{
		p.insert(std::pair<char, float>(i, 0));
		std::vector<Abalone> a;
		temp.insert(std::pair<char, std::vector<Abalone> >(i, a));
	}
	for (int i = 0; i < Abalones.size(); i++)
	{
		p.at(Abalones[i].get_Sex())++;
		temp.at(Abalones[i].get_Sex()).push_back(Abalones[i]);
	}
	float result = 0;
	for (char i : Sex_classes)
	{
		if (p.at(i) != 0)
		{
			p.at(i) = (p.at(i) * info(temp.at(i), classes)) / Abalones.size();
			result += p.at(i);
		}
	}
	Equally *c = new Equally(result, Global::SEX, Sex_classes);
	return c;
}

float C4_5::info_Diameter_old(std::vector<Abalone> &Abalones, std::set<int> &classes)
{
	// This function copies elements from one vector to another, so it is slower than new version of such function that uses pointers 
	clock_t time;
	time = clock();
	std::map<bool, float> p;
	std::map<bool, std::vector<Abalone> > temp;
	p.insert(std::pair<bool, float>(true, 0));
	p.insert(std::pair<bool, float>(false, 0));
	std::vector<Abalone> a, a1;
	temp.insert(std::pair<bool, std::vector<Abalone> >(true, a));
	temp.insert(std::pair<bool, std::vector<Abalone> >(false, a1));

	std::vector<float> all_values;
	for (int i = 0; i < Abalones.size(); i++)
	{
		all_values.push_back(Abalones[i].get_Diameter());
	}

	std::sort(all_values.begin(), all_values.end());
	all_values.erase(std::unique(all_values.begin(), all_values.end()), all_values.end());
	float min_entrop = 100000, global_threshold = 0;
	for (int i = 0; i < all_values.size() - 1; i++)
	{
		float threshold = (all_values[i] + all_values[i + 1]) / 2;
		for (int j = 0; j < Abalones.size(); j++)
		{
			p.at((Abalones[j].get_Diameter() > threshold))++;
			temp.at((Abalones[j].get_Diameter() > threshold)).push_back(Abalones[j]);
		}
		p.at(false) /= Abalones.size();
		p.at(true) /= Abalones.size();
		float local_result = p.at(false) * info(temp.at(false), classes) +
			p.at(true) * info(temp.at(true), classes);
		//std::cout << " local = " << local_result << " ";
		if (min_entrop > local_result)
		{
			min_entrop = local_result;
			global_threshold = threshold;
		}
		p.at(false) = p.at(true) = 0;
		temp.at(false).clear(); temp.at(true).clear();
	}
	time = clock() - time;
	std::cout << " time: " << ((double)time / CLOCKS_PER_SEC) << std::endl;
	return min_entrop;
}

Condition * C4_5::info_float_parameter(std::vector<Abalone> &Abalones, std::set<int> &classes, Global::ATTRIBUTES TAG)
{
	clock_t time;
	time = clock();

	Abalone::COMPARE_ORIENTATION = TAG;
	std::vector<float> all_values;
	get_uniq_values(Abalones, all_values, TAG, Global::MAX_UNIQUE_VALUES_COUNT);
	std::sort(Abalones.begin(), Abalones.end(), Abalone::compare);
	float min_entrop = 100000, global_threshold = 0;
	std::vector<Abalone>::iterator first = Abalones.begin(), last = Abalones.begin();
	for (int i = 0; i < all_values.size() - 1; i++)
	{
		float threshold = (all_values[i] + all_values[i + 1]) / 2;
		for (std::vector<Abalone>::iterator it = last; it != Abalones.end(); it++)
		{
			float val = get_parameter_value(*it, TAG);
			if (val > threshold)
			{
				last = it;
				break;
			}
		}
		float local_result = (((float)(last - Abalones.begin())) / Abalones.size()) * info(Abalones, Abalones.begin(), last, classes) +
			(((float)(Abalones.end() - last)) / Abalones.size()) * info(Abalones, last, Abalones.end(), classes);
		//std::cout << " local = " << local_result << " ";
		if (min_entrop > local_result)
		{
			min_entrop = local_result;
			global_threshold = threshold;
		}
	}
	time = clock() - time;
	std::cout << " time: " << ((double)time / CLOCKS_PER_SEC) << std::endl;
	Less *c = new Less(min_entrop, TAG, global_threshold);
	return c;
}

void C4_5::build_desigion_tree(Node * node, std::vector<Abalone> &learning_Abalones, std::set<char> &Sex_classes, std::set<int> &classes)
{
	int class_id = learning_Abalones[0].get_Rings();
	node->set_isLeave(true);
	for (Abalone a : learning_Abalones) {
		if (a.get_Rings() != class_id)
		{ 
			node->set_isLeave(false);
			break; 
		}
	}
	if (!node->is_leave())
	{
		Condition *cond = find_min_entropy(learning_Abalones, Sex_classes, classes);
		node->condition = cond;
		if (dynamic_cast<Equally*>(cond))
		{
			std::set<char> char_classes = (dynamic_cast<Equally*>(cond))->classes;
			std::map<char, std::vector<Abalone>> m;
			for (char c : char_classes)
			{
				std::vector<Abalone> v;
				m.insert(std::pair<char, std::vector<Abalone> >(c, v));
			}
			for (Abalone a : learning_Abalones)
			{
				m.at(a.get_Sex()).push_back(a);
			}
			for (char c : char_classes)
			{
				if (!m.at(c).empty())
				{
					Node *ch = new Node(node);
					ch->Sex_class = c;
					node->add_child(ch);
					build_desigion_tree(ch, m.at(c), Sex_classes, classes);
				}
			}
		}
		else if (dynamic_cast<Less*>(cond))
		{
			float threshold = (dynamic_cast<Less*>(cond))->threshold;
			Global::ATTRIBUTES tag = (dynamic_cast<Less*>(cond))->TAG;
			std::vector<Abalone> v1, v2;
			for (Abalone a : learning_Abalones)
			{
				if (get_parameter_value(a, tag) < threshold) { v1.push_back(a); }
				else { v2.push_back(a); }
			}
			if (!v1.empty())
			{
				Node *ch = new Node(node);
				node->add_child(ch);
				build_desigion_tree(ch, v1, Sex_classes, classes); 
			}
			if (!v2.empty())
			{
				Node *ch = new Node(node);
				node->add_child(ch);
				build_desigion_tree(ch, v2, Sex_classes, classes);
			}
		}
	}
	else
	{
		node->result_class = class_id;
	}
}

int C4_5::predict_Abalone_age(Abalone a, Node *DesigionTree)
{
	Node *n = DesigionTree;
	while (!n->is_leave())
	{
		if (dynamic_cast<Equally*>(n->condition))
		{
			std::vector<Node *> children = n->get_children();
			bool ind = false;
			for (Node *ch : children)
			{
				if (ch->Sex_class == a.get_Sex())
				{
					n = ch;
					ind = true;
					break;
				}
			}
			if (!ind)
			{
				n = children[0];
			}
		}
		else if (dynamic_cast<Less*>(n->condition))
		{
			float threshold = (dynamic_cast<Less*>(n->condition))->threshold;
			std::vector<Node *> children = n->get_children();
			if (get_parameter_value(a, n->condition->TAG) < threshold)
			{
				n = children[0];
			}
			else
			{
				n = children[1];
			}
		}
	}
	return n->result_class;
}

float C4_5::calculate_precision_of_prediction(std::vector<Abalone> &test_Abalones, Node *DesigionTree, int precision)
{
	float almoust_right_answers = 0;
	for (Abalone a : test_Abalones)
	{
		int real_age = a.get_Rings(),
			predicted_age = predict_Abalone_age(a, DesigionTree);
		//std::cout << real_age << " " << predicted_age << " " << std::endl;
		if (abs(real_age - predicted_age) <= precision)
		{
			almoust_right_answers++;
		}
	}
	return (almoust_right_answers / test_Abalones.size());
}
void C4_5::get_uniq_values(std::vector<Abalone> &Abalones, std::vector<float> &all_values, Global::ATTRIBUTES TAG, int count)
{
	for (int i = 0; i < Abalones.size(); i++)
	{
		switch (TAG)
		{
		case Global::DIAMETER:
			all_values.push_back(Abalones[i].get_Diameter());
			break;
		case Global::LENGTH:
			all_values.push_back(Abalones[i].get_Length());
			break;
		case Global::HEIGHT:
			all_values.push_back(Abalones[i].get_Height());
			break;
		case Global::WHOLE_WEIGHT:
			all_values.push_back(Abalones[i].get_Whole_weight());
			break;
		case Global::VISCERA_WEIGHT:
			all_values.push_back(Abalones[i].get_Viscera_weight());
			break;
		case Global::SHELL_WEIGHT:
			all_values.push_back(Abalones[i].get_Shell_weight());
			break;
		case Global::SHUCKED_WEIGHT:
			all_values.push_back(Abalones[i].get_Shucked_weight());
			break;
		default:
			break;
		}
	}
	std::sort(all_values.begin(), all_values.end());
	all_values.erase(std::unique(all_values.begin(), all_values.end()), all_values.end());
	// we must leave only "count" elements, so we need to define step and delete another elements
	// choosing only "count" representative elements
	if (all_values.size() > count)
	{
		float step = ((float)all_values.size()) / count;
		step += (step / count);
		std::vector<float> tmp;
		for (int i = 0; i < count; i++)
		{
			tmp.push_back(all_values[(int)(step * i)]);
		}
		all_values.swap(tmp);
	}
}

float C4_5::get_parameter_value(Abalone a, Global::ATTRIBUTES TAG)
{
	switch (TAG)
	{
	case Global::DIAMETER:
		return a.get_Diameter();
	case Global::LENGTH:
		return a.get_Length();
	case Global::HEIGHT:
		return a.get_Height();
	case Global::WHOLE_WEIGHT:
		return a.get_Whole_weight();
	case Global::VISCERA_WEIGHT:
		return a.get_Viscera_weight();
	case Global::SHELL_WEIGHT:
		return a.get_Shell_weight();
	case Global::SHUCKED_WEIGHT:
		return a.get_Shucked_weight();
	default:
		break;
	}
	return 0;
}

Condition * C4_5::find_min_entropy(std::vector<Abalone> &learning_Abalones, std::set<char> &Sex_classes, std::set<int> &classes)
{
	std::vector<Condition * > conditions;
	conditions.push_back(info_Sex(learning_Abalones, Sex_classes, classes));
	conditions.push_back(info_float_parameter(learning_Abalones, classes, Global::DIAMETER));
	conditions.push_back(info_float_parameter(learning_Abalones, classes, Global::HEIGHT));
	conditions.push_back(info_float_parameter(learning_Abalones, classes, Global::LENGTH));
	conditions.push_back(info_float_parameter(learning_Abalones, classes, Global::VISCERA_WEIGHT));
	conditions.push_back(info_float_parameter(learning_Abalones, classes, Global::SHELL_WEIGHT));
	conditions.push_back(info_float_parameter(learning_Abalones, classes, Global::SHUCKED_WEIGHT));
	conditions.push_back(info_float_parameter(learning_Abalones, classes, Global::WHOLE_WEIGHT));
	sort(conditions.begin(), conditions.end(), Condition::compare);
	for (int i = 1; i < conditions.size(); i++){ delete conditions[i]; }
	return conditions[0];
}

void C4_5::desigion_tree_to_file(Node *tree, std::string file_name)
{
	std::ofstream fout(file_name);
	fout << Node::count << std::endl;
	Node *n = tree;
	add_node_id_to_ofstream(n, fout);
	fout << std::endl;
	fout << tree->to_string() << std::endl;
	add_node_to_ofstream(n, fout);
	fout.close();
}
Node * C4_5::tree_from_file(std::string file_name, std::set<char> &Sex_classes)
{
	std::string line;
	std::ifstream infile(file_name);
	std::getline(infile, line);
	std::istringstream iss1(line);
	int count;
	iss1 >> count;
	std::getline(infile, line);
	std::istringstream iss2(line);
	std::map<int, Node *> map;
	Node *root = new Node(); root->id = 1;
	map.insert(std::pair<int, Node*>(root->id, root));
	for (int i = 0; i < count-1; i++)
	{
		int a, b;
		iss2 >> a >> b;
		if (map.count(a) == 0 && map.count(b) == 0)
		{
			Node *A = new Node(); A->id = a; 
			Node *B = new Node(A); B->id = b;
			A->add_child(B);
		}
		else if (map.count(a) == 1 && map.count(b) == 0)
		{
			Node *B = new Node(map.at(a)); B->id = b;
			map.insert(std::pair<int, Node*>(B->id, B));
			map.at(a)->add_child(B);
		}
		else if (map.count(a) == 0 && map.count(b) == 1)
		{
			Node *A = new Node(); A->id = a; A->add_child(map.at(b));
			map.insert(std::pair<int, Node*>(A->id, A));
			map.at(b)->set_father(A);
		}
		else
		{
			map.at(a)->add_child(map.at(b));
			map.at(b)->set_father(map.at(a));
		}
	}
	for (int i = 0; i < count; i++)
	{
		std::getline(infile, line);
		std::istringstream iss3(line);
		int id, result_class;
		char Sex_class, isLeave;
		float threshold, entropy;
		std::string tag;
		iss3 >> id >> isLeave >> result_class >> Sex_class >> tag >> entropy;
		Global::ATTRIBUTES t = Global::attribute_from_string(tag);
		if (Global::attribute_from_string(tag) != Global::SEX)
		{
			if (result_class == -1)
			{
				iss3 >> threshold;
				map.at(id)->condition = new Less(entropy, Global::attribute_from_string(tag), threshold);
			}
		}
		else
		{
			map.at(id)->condition = new Equally(entropy, Global::attribute_from_string(tag), Sex_classes);
		}	
		map.at(id)->result_class = result_class;
		map.at(id)->Sex_class = Sex_class;
		map.at(id)->set_isLeave(isLeave == 'T');
	}
	return root;
}
void C4_5::add_node_id_to_ofstream(Node * node, std::ofstream &fout)
{
	std::vector<Node *> v = node->get_children();
	for (Node * n : v)
	{
		fout << n->get_father()->id << Parser::delimiter_space << n->id << Parser::delimiter_space;
	}
	for (Node * n : v)
	{
		add_node_id_to_ofstream(n, fout);
	}
}
void C4_5::add_node_to_ofstream(Node * node, std::ofstream &fout)
{
	std::vector<Node *> v = node->get_children();
	for (Node * n : v)
	{
		fout << n->to_string() << std::endl;
	}
	for (Node * n : v)
	{
		add_node_to_ofstream(n, fout);
	}
}

int Node::count = 0;
std::string Node::to_string()
{
	std::string leave = isLeave ? "T" : "F";
	std::string s; s += Sex_class;
	return std::to_string(id).append(Parser::delimiter_space).append(leave).append(Parser::delimiter_space).append(std::to_string(result_class)).
		append(Parser::delimiter_space).append(s).append(Parser::delimiter_space).append(condition->to_string());
}