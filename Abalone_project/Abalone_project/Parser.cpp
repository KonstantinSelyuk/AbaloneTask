#include <sstream>
#include <fstream>
#include <iostream>
#include <time.h>
#include "Parser.h"

void Parser::get_Abalones_from_data(std::vector<Abalone> &Abalones, std::string file_name)
{
	clock_t time;
	time = clock();
	
	std::string line;
	std::ifstream infile(file_name);
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		char Sex, delimiter;
		float Length, Diameter, Height, Whole_weight, Shucked_weight, Viscera_weight, Shell_weight;
		int Rings;
		if (!(iss >> Sex >> delimiter >> Length >> delimiter >> Diameter >> delimiter >> 
			Height >> delimiter >> Whole_weight >> delimiter >> Shucked_weight >> delimiter >> 
			Viscera_weight >> delimiter >> Shell_weight >> delimiter >> Rings)) 
		{
			break; // error
		} 
		Abalones.push_back(Abalone(Sex, Length, Diameter, Height, Whole_weight, Shucked_weight, Viscera_weight, Shell_weight, Rings));
	}
	time = clock() - time;
	//std::cout << " Parsing is completed with time: ";
	printf("%s %f %s", " Parsing is completed with time:", ((double)time / CLOCKS_PER_SEC), "seconds.");
	std::cout << std::endl << " Was found " << Abalones.size() << " items of Abalones." << std::endl;
}