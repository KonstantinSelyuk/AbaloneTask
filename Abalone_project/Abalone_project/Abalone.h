#pragma once
#include <vector>
#include <set>
#include <map>
#include "Global.h"
class Abalone
{
private:
	char Sex;
	float Length, Diameter, Height, Whole_weight, Shucked_weight, Viscera_weight, Shell_weight;
	int Rings;
public:
	static Global::ATTRIBUTES COMPARE_ORIENTATION;
	static float max_Length, max_Diameter, max_Height, max_Whole_weight, max_Shucked_weight, max_Viscera_weight, max_Shell_weight;
	static float min_Length, min_Diameter, min_Height, min_Whole_weight, min_Shucked_weight, min_Viscera_weight, min_Shell_weight;
	Abalone();
	~Abalone(){};
	Abalone(char Sex, float Length, float Diameter, float Height, float Whole_weight, float Shucked_weight, float Viscera_weight, float Shell_weight, int Rings);
	char get_Sex(){ return this->Sex; };
	float get_Length(){ return this->Length; };
	float get_Diameter(){ return this->Diameter; };
	float get_Height(){ return this->Height; };
	float get_Whole_weight(){ return this->Whole_weight; };
	float get_Shucked_weight(){ return this->Shucked_weight; };
	float get_Viscera_weight(){ return this->Viscera_weight; };
	float get_Shell_weight(){ return this->Shell_weight; };
	int get_Rings(){ return this->Rings; }
	static void define_classes(std::vector<Abalone> &Abalones, std::set<int> &classes);
	static void define_Sex_classes(std::vector<Abalone> &Abalones, std::set<char> &Sex_classes);
	static void define_max_min_values(std::vector<Abalone> &Abalones, std::set<int> &classes);
	static int get_int_class_from_float(int number_of_classes, float left_border, float right_border, float value);
	static bool compare(Abalone a, Abalone b);
};