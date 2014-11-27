#include <vector>
#include <string>
//#include <time.h>
#include <iostream>
#include <algorithm>
using namespace std;
class State
{
public:
	bool parts[7];
	State(){}
	friend ostream& operator<<(ostream& os, const State& dt)
	{
		for (int i = 0; i < 7; i++)
			os << dt.parts[i] ;
		os << endl;
		return os;
	}
	static void set_possible_numbers_by_working_segment(bool * numbers, int segment)
	{
		switch (segment)
		{
		case 0:
			numbers[1] = false;
			numbers[4] = false;
			break;
		case 1:
			numbers[5] = false;
			numbers[6] = false;
			break;
		case 2:
			numbers[2] = false;
			break;
		case 3:
			numbers[1] = false;
			numbers[4] = false;
			numbers[7] = false;
			break;
		case 4:
			numbers[1] = false;
			numbers[3] = false;
			numbers[4] = false;
			numbers[5] = false;
			numbers[7] = false;
			numbers[9] = false;
			break;
		case 5:
			numbers[1] = false;
			numbers[2] = false;
			numbers[3] = false;
			numbers[7] = false;
			break;
		case 6:
			numbers[0] = false;
			numbers[1] = false;
			numbers[7] = false;
			break;
		default:
			break;
		}
	}
	static bool * get_number_as_bool_array(int number)
	{
		bool *number_as_array = new bool[7];
		for (int k = 0; k < 7; k++){ number_as_array[k] = false; }
		switch (number)
		{
		case 0:
			number_as_array[0] = true;
			number_as_array[1] = true;
			number_as_array[2] = true;
			number_as_array[3] = true;
			number_as_array[4] = true;
			number_as_array[5] = true;
			break;
		case 1:
			number_as_array[1] = true;
			number_as_array[2] = true;
			break;
		case 2:
			number_as_array[0] = true;
			number_as_array[1] = true;
			number_as_array[3] = true;
			number_as_array[4] = true;
			number_as_array[6] = true;
			break;
		case 3:
			number_as_array[0] = true;
			number_as_array[1] = true;
			number_as_array[2] = true;
			number_as_array[3] = true;
			number_as_array[6] = true;
			break;
		case 4:
			number_as_array[1] = true;
			number_as_array[2] = true;
			number_as_array[5] = true;
			number_as_array[6] = true;
			break;
		case 5:
			number_as_array[0] = true;
			number_as_array[2] = true;
			number_as_array[3] = true;
			number_as_array[5] = true;
			number_as_array[6] = true;
			break;
		case 6:
			number_as_array[0] = true;
			number_as_array[2] = true;
			number_as_array[3] = true;
			number_as_array[4] = true;
			number_as_array[5] = true;
			number_as_array[6] = true;
			break;
		case 7:
			number_as_array[0] = true;
			number_as_array[1] = true;
			number_as_array[2] = true;
			break;
		case 8:
			number_as_array[0] = true;
			number_as_array[1] = true;
			number_as_array[2] = true;
			number_as_array[3] = true;
			number_as_array[4] = true;
			number_as_array[5] = true;
			number_as_array[6] = true;
			break;
		case 9:
			number_as_array[0] = true;
			number_as_array[1] = true;
			number_as_array[2] = true;
			number_as_array[3] = true;
			number_as_array[5] = true;
			number_as_array[6] = true;
			break;
		default:
			break;
		}
		return number_as_array;
	}
	static string get_number_as_string_with_broken_segments(int number, bool *broken_segments)
	{
		bool * number_as_bool_arr = get_number_as_bool_array(number);
		string result = "";
		for (int i = 0; i < 7; i++)
		{
			if (number_as_bool_arr[i] && !broken_segments[i]) { result += "1"; }
			else { result += "0"; }
		}
		delete[] number_as_bool_arr;
		return result;
	}
	static int calculate_first_number(int index, int number)
	{
		return (number + index) % 10;
	}
};
int main()
{

	int T; cin >> T;
	for (int i = 1; i <= T; i++)
	{
		string answer;
		int N; cin >> N;
		bool *broken_segments = new bool[7];
		for (int j = 0; j < 7; j++){ broken_segments[j] = true; }
		State * states = new State[N];
		for (int j = 0; j < N; j++)
		{
			State S;
			for (int k = 0; k < 7; k++)
			{
				char tmp; cin >> tmp;
				S.parts[k] = (tmp == '1');
			}
			states[j] = S;
		}
		bool *possible_numbers = new bool[10];
		for (int j = 0; j < 10; j++){ possible_numbers[j] = true; }
		// Solving
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < 10; k++) {if (states[j].parts[k]) { State::set_possible_numbers_by_working_segment(possible_numbers, k); broken_segments[k] = false; }}
			vector<int> v;
			for (int k = 0; k < 10; k++) { if (possible_numbers[k]) { v.push_back(k); } }
			if (v.empty()) { answer = "ERROR!";  break; }
			else if (v.size() == 1)
			{
				int first = State::calculate_first_number(j, v[0]);
				int answer_number = first - N; // 
			}
		}

		cout << answer;
		delete[] broken_segments;
		delete[] states;
	}


	//clock_t t1, t2;
	//t1 = clock();
	//t2 = clock();
	//float diff((float)t2 - (float)t1);
	//std::cout << (diff) / CLOCKS_PER_SEC << std::endl;
	//system("pause");
	return 0;
}


