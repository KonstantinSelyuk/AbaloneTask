#include <iostream>
#include "Abalone.h"

float Abalone::max_Length, Abalone::max_Diameter, Abalone::max_Height, Abalone::max_Whole_weight,
      Abalone::max_Shucked_weight, Abalone::max_Viscera_weight, Abalone::max_Shell_weight, 
	  Abalone::min_Length, Abalone::min_Diameter, Abalone::min_Height, Abalone::min_Whole_weight,
	  Abalone::min_Shucked_weight, Abalone::min_Viscera_weight, Abalone::min_Shell_weight;
Global::ATTRIBUTES Abalone::COMPARE_ORIENTATION;

Abalone::Abalone()
{
	this->Diameter = 0;
	this->Height = 0;
	this->Length = 0;
	this->Rings = 0;
	this->Sex = 0;
	this->Shell_weight = 0;
	this->Shucked_weight = 0;
	this->Viscera_weight = 0;
	this->Whole_weight = 0;
}

Abalone::Abalone(char Sex, float Length, float Diameter, float Height, float Whole_weight, float Shucked_weight, float Viscera_weight, float Shell_weight, int Rings)
{
	this->Diameter = Diameter;
	this->Height = Height;
	this->Length = Length;
	this->Rings = Rings;
	this->Sex = Sex;
	this->Shell_weight = Shell_weight;
	this->Shucked_weight = Shucked_weight;
	this->Viscera_weight = Viscera_weight;
	this->Whole_weight = Whole_weight;
}

void Abalone::define_classes(std::vector<Abalone> &Abalones, std::set<int> &classes)
{
	int N_learning = Abalones.size();
	for (int i = 0; i < N_learning; i++)
	{
		classes.insert(Abalones[i].get_Rings());
	}
}

void Abalone::define_Sex_classes(std::vector<Abalone> &Abalones, std::set<char> &Sex_classes)
{
	int N_learning = Abalones.size();
	for (int i = 0; i < N_learning; i++)
	{
		Sex_classes.insert(Abalones[i].get_Sex());
	}
}

void Abalone::define_max_min_values(std::vector<Abalone> &Abalones, std::set<int> &classes)
{
	int N_learning = Abalones.size();
	max_Length = min_Length = Abalones[0].get_Length();
	max_Diameter = min_Diameter = Abalones[0].get_Diameter();
	max_Height = min_Height = Abalones[0].get_Height();
	max_Whole_weight = min_Whole_weight = Abalones[0].get_Whole_weight();
	max_Shucked_weight = min_Shucked_weight = Abalones[0].get_Shucked_weight();
	max_Viscera_weight = min_Viscera_weight = Abalones[0].get_Viscera_weight();
	max_Shell_weight = min_Shell_weight = Abalones[0].get_Shell_weight();
	for (int i = 0; i < N_learning; i++)
	{
		max_Length = (max_Length > Abalones[i].get_Length()) ? max_Length : Abalones[i].get_Length();
		max_Diameter = (max_Diameter > Abalones[i].get_Diameter()) ? max_Diameter : Abalones[i].get_Diameter();
		max_Height = (max_Height > Abalones[i].get_Height()) ? max_Height : Abalones[i].get_Height();
		max_Whole_weight = (max_Whole_weight > Abalones[i].get_Whole_weight()) ? max_Whole_weight : Abalones[i].get_Whole_weight();
		max_Shucked_weight = (max_Shucked_weight > Abalones[i].get_Shucked_weight()) ? max_Shucked_weight : Abalones[i].get_Shucked_weight();
		max_Viscera_weight = (max_Viscera_weight > Abalones[i].get_Viscera_weight()) ? max_Viscera_weight : Abalones[i].get_Viscera_weight();
		max_Shell_weight = (max_Shell_weight > Abalones[i].get_Shell_weight()) ? max_Shell_weight : Abalones[i].get_Shell_weight();

		min_Length = (min_Length < Abalones[i].get_Length()) ? min_Length : Abalones[i].get_Length();
		min_Diameter = (min_Diameter < Abalones[i].get_Diameter()) ? min_Diameter : Abalones[i].get_Diameter();
		min_Height = (min_Height < Abalones[i].get_Height()) ? min_Height : Abalones[i].get_Height();
		min_Whole_weight = (min_Whole_weight < Abalones[i].get_Whole_weight()) ? min_Whole_weight : Abalones[i].get_Whole_weight();
		min_Shucked_weight = (min_Shucked_weight < Abalones[i].get_Shucked_weight()) ? min_Shucked_weight : Abalones[i].get_Shucked_weight();
		min_Viscera_weight = (min_Viscera_weight < Abalones[i].get_Viscera_weight()) ? min_Viscera_weight : Abalones[i].get_Viscera_weight();
		min_Shell_weight = (min_Shell_weight < Abalones[i].get_Shell_weight()) ? min_Shell_weight : Abalones[i].get_Shell_weight();
	}
}

int Abalone::get_int_class_from_float(int number_of_classes, float left_border, float right_border, float value)
{
	if (fabs(right_border - value) < 0.0000005f || right_border < value)
	{
		return number_of_classes - 1;
	}
	else if (left_border > value) 
	{
		return 0;
	}
	return (int)(((value - left_border) * number_of_classes) / (right_border - left_border));
}

bool Abalone::compare(Abalone a, Abalone b)
{
	switch (COMPARE_ORIENTATION)
	{
	case Global::DIAMETER:
		return a.Diameter < b.Diameter;
	case Global::HEIGHT:
		return a.Height < b.Height;
	case Global::LENGTH:
		return a.Length < b.Length;
	case Global::SHELL_WEIGHT:
		return a.Shell_weight < b.Shell_weight;
	case Global::SHUCKED_WEIGHT:
		return a.Shucked_weight < b.Shucked_weight;
	case Global::WHOLE_WEIGHT:
		return a.Whole_weight < b.Whole_weight;
	case Global::VISCERA_WEIGHT:
		return a.Viscera_weight < b.Viscera_weight;
	}
	return false;
}