#include "Parser.h"

std::string Parser::delimiter_colon = ":";
std::string Parser::delimiter_space = " ";

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

void Parser::write_to_file_parameters(std::string file_name, std::map<std::string, std::string> parameters)
{
	std::ofstream fout(file_name);
	for (std::pair<std::string, std::string> p : parameters)
	{
		fout << p.first << Parser::delimiter_colon << p.second << std::endl;
	}
	fout.close();
}

std::map<std::string, std::string> Parser::get_parameters_from_file(std::string file_name)
{
	std::map<std::string, std::string> returned_map;
	std::string line;
	std::ifstream infile(file_name);
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		std::string s, s_value;
		if (!(iss >> s))
		{
			break; // error
		}
		std::string s2;
		for (std::string::iterator it = s.begin(); it != s.end(); it++)
		{
			if (*it == Parser::delimiter_colon.at(0))
			{
				s2.insert(s2.begin(), s.begin(), it);
				s_value.insert(s_value.begin(), it + 1, s.end());
				returned_map.insert(std::pair<std::string, std::string>(s2, s_value));
				break;
			}
		}
	}
	return returned_map;
}

std::string Parser::file_to_string(std::string file_name)
{
	std::string line, result;
	std::ifstream infile(file_name);
	while (std::getline(infile, line))
	{
		result.append(line).append("\n\r");
	}
	return result;
}