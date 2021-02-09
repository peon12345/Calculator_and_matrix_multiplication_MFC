#pragma once
class Calculator
{
public:
	Calculator();
	double calculate();

	void addValue(double value);
	void setOperator(char operat);

	void clear();
private:
	bool m_isFirstValue;

	double m_value1;
	double m_value2;
	char m_operator;
};

