#include <stdio.h>
#include <cstdlib>
#include <cmath>

class Calculator
{
public:
	Calculator(char* str);

	int GetExpr();
	int GetSumSub();
	int GetMulDiv();
	int GetPow();
	int GetBraces();
	int GetNumber();
private:
	const char* str_;
	int p_;
};

Calculator::Calculator(char* str):
	str_ 	(str),
	p_ 	(0)
	{
		if (!str)
		{
			printf("Calculator: error: invalid expression xtring received!\n");
			exit(EXIT_FAILURE);
		}
	}

int Calculator::GetExpr()
{
	int val = GetSumSub();
	if (str_[p_] == '\0')
		return val;
	return -1;
}

int Calculator::GetSumSub()
{                          	
	int val = GetMulDiv();
	while (str_[p_] == '-' || str_[p_] == '+')
	{
		char op_r =  str_[p_];
		p_++;
		int val2 = GetMulDiv();
		(op_r == '+')? val += val2 : val -= val2; 
	}	
	return val;
}

int Calculator::GetMulDiv()
{
	int val = GetPow();
	while (str_[p_] == '*' || str_[p_] == '/')
	{
		char op_r = str_[p_];
		p_++;
		int val2 = GetPow();
		(op_r == '*')? val *= val2 : val /= val2;
	}
	return val;
}

int Calculator::GetPow()
{
	int val = GetBraces();
	while (str_[p_] == '^')
	{
		p_++;
		val = pow(val, GetBraces());
	}
	return val;
}

int Calculator::GetBraces()
{
	if (str_[p_] == '(')
	{
		p_++;
		int val = GetSumSub();
		if (str_[p_] == ')')
		{
			p_++;
			return val;
		}
		else
		{
			printf("Something's wrong with your math: closing brace not found\n");
			exit(0);
		}
	}
	else	return GetNumber();
}

int Calculator::GetNumber()
{
	int val = 0;
	int remembered_p = p_;
	while ('0' <= str_[p_] && str_[p_] <= '9')
	{
		val = val * 10 + (str_[p_] - '0');
		p_++;
	}
	if (remembered_p != p_) return val;
	else			return -1;
}

int main()
{
	char str[30] = {};
	printf("enter your str\n");
	scanf("%s", str);

	Calculator calc(str);

	printf("calculated value: %d\n", calc.GetExpr());	
	system("pause");

}                          	
