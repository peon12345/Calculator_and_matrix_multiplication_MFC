#include "pch.h"
#include "Calculator.h"

Calculator::Calculator() {
    clear();
}

void Calculator::clear() {

    m_isFirstValue = true; //ждем первое значение
    m_value1 = 0; 
    m_value2 = 0;
}

double Calculator::calculate() {

    switch (m_operator)
    {
    case '+':
        return m_value1 + m_value2;
    case '-':
        return m_value1 - m_value2;
    case '*':
        return m_value1 * m_value2;
    case '/':
        if (m_value2 == 0) {
            return 0;
        }
        return m_value1 / m_value2;
    default:
        return 0;
    }
}

void Calculator::addValue(double value) {

    if (m_isFirstValue) {
        m_value1 = value;
    }
    else {
        m_value2 = value;
    }
    
    m_isFirstValue = !m_isFirstValue; // ставим, что первое значение заполнено
}

void Calculator::setOperator(char operat) {
    m_operator = operat; 
}