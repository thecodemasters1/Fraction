#if !defined SAFEARITHMETIC_HPP_
#define SAFEARITHMETIC_HPP_

class SafeArithmetic
{
public:
	static int add(int num1, int num2);
	static int subtract(int num1, int num2);
	static int multiply(int num1, int num2);
	static int divide(int num1, int num2);

private:
	SafeArithmetic() {}
	~SafeArithmetic() {}
};

#endif