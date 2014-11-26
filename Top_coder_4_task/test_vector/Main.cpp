#include <vector>
#include <time.h>
#include <iostream>

class MyClass
{
public:
	MyClass() : v(20000000, 1.123) {};
	MyClass(MyClass&& ob) { std::cout << "(const MyClass&& ob)" << std::endl; };
private:
	std::vector<double> v;
};
 
void func(MyClass ob)
{

}
int main()
{

	//std::vector<double> v(20000000, 1.123);
	clock_t t1, t2;
	t1 = clock();
	func(MyClass());
	t2 = clock();
	float diff((float)t2 - (float)t1);
	std::cout << (diff) / CLOCKS_PER_SEC << std::endl;
	system("pause");
	return 0;
}

