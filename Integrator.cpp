#include <iostream>
#include <cmath>
#include <vector>

using Func = double(*)(double);
using FuncM = double(*)(Func, double, double, int);

int step = 1;

struct Function
{
	const char * name;
	Func f;
	FuncM fm;

	Function(const char * _n, Func _f) : name{ _n }, f{ _f }{}
	Function(const char * _n, FuncM _fm) : name{ _n }, fm{ _fm }{}
};

double x(double arg) { return arg; }
double xx(double arg) { return arg * arg; }

double column(Func f, double a, double b, int N)
{
	double sum = 0, h = (b - a) / N;
	for (int i = 0; i < N; i++)
		sum += f(a + h * i);
	return h * sum;
}

double trapeze(Func f, double a, double b, int N)
{
	double sum = 0, h = (b - a) / N;
	for (int i = 0; i < N; i++)
		sum += f(a + h * i) + f(a + h * (i + 1));
	return h/2 * sum ;
}

int Choose(const char* subject, std::vector<Function>& vars)
{
	std::cout << "Choose " << subject << ": \n";
	for (int i = 0; i < vars.size(); i++) 
	{
		std::cout << "\t" << i + 1 << ". " << vars[i].name << "\n";
	}
	//std::cout << "\t" << vars.size() + 1 << ". Cancel\n";

	int chosen = 0;
	std::cin >> chosen;

	return chosen;
}

Func ChooseFunc()
{
	Function f1{ "x", x };
	Function f2{ "x*x", xx };
	Function f3{ "sin(x)", std::sin };
	Function f4{ "cos(x)", std::cos };

	std::vector<Function> vars = { f1, f2, f3, f4 };

	int chosen = 0;
	chosen = Choose("funcion", vars);
	if (chosen < 1 || chosen > vars.size())
	{
		std::cout << "Wrong input: " << chosen << ", expected 1-" << vars.size();
		return ChooseFunc();
	}

	std::cout << "0.Quit  1.Choose function anew  2.Next step: ";
	std::cin >> step;

	return vars[chosen - 1].f;
}

FuncM ChooseMethod()
{
	Function method1{ "trapeze", trapeze };
	Function method2{ "column", column };

	std::vector<Function> vars = { method1, method2 };

	int chosen = Choose("method", vars);
	if (chosen < 1 || chosen > 2)
	{
		std::cout << "Wrong input: " << chosen << ", expected 1, 2";
		return ChooseMethod();
	}

	std::cout << "0.Quit  1.Choose function  2.Choose method anew  3.Next step: ";
	std::cin >> step;

	return vars[chosen - 1].fm;
}

std::pair<double, double> ChooseLimits()
{
	std::pair<double, double> ab = { 0,0 };
	std::cout << "Write limits:\n" << "a: ";
	std::cin >> ab.first;
	std::cout << "b: ";
	std::cin >> ab.second;
	if (ab.first > ab.second)
	{
		std::cout << "Wrong limits: a = " << ab.first <<
			" b = " << ab.second << ", expected a < b";
		return ChooseLimits();
	}

	std::cout << "0.Quit  1.Choose function  2.Choose method  \n3.Choose limits anew  4.Next step: ";
	std::cin >> step;

	return ab;
}

int ChooseStepNumber()
{
	int n;
	std::cout << "Write number of steps:\n" << "N: ";
	std::cin >> n;

	std::cout << "0.Quit  1.Choose function  2.Choose method  \n3.Choose limits  4.Choose step number  5.Next step: ";
	std::cin >> step;

	return n;
}

int main()
{
	Func chosen_func = x;
	FuncM chosen_method = column;
	std::pair<double, double> limits = { 0, 0 };
	int N = 100;

	while(step)
		switch (step)
		{
		case(1):
			chosen_func = ChooseFunc();
		case(2):
			chosen_method = ChooseMethod();
		case(3):
			limits = ChooseLimits();
		case(4):
			N = ChooseStepNumber();
		case(5):
			std::cout << "Result:" << chosen_method(chosen_func, limits.first, limits.second, N) << '\n';
			step = 0;
		default:
			std::cout << "Buy!\n";
			step = 0;
		}

	std::getchar();
	return 0;
}