#include "pch.h"
#include "Calculator.h"
#include "Exception.h"

#include <stack>
#include <string>

	void Calculator::to_postfix()
	{
		std::stack<char> opStack;
		unsigned i = 0;
		while (i < m_str.size())
		{
			if (is_operand(m_str[i]))
			{
				while (is_operand(m_str[i]) && i <= m_str.size())
					m_pos += m_str[i++];
				m_pos += ' ';
			}
			else if (is_operator(m_str[i]))
			{
				if (!opStack.empty() && op_value(opStack.top()) >= op_value(m_str[i]))
				{
					m_pos += opStack.top();
					opStack.pop();
					opStack.push(m_str[i++]);
				}
				else
					opStack.push(m_str[i++]);
			}
			else if (is_parenthes(m_str[i]))
			{
				if (m_str[i] == static_cast<char>(Parenthes::Open))
					opStack.push(m_str[i++]);
				else
				{
					while (!opStack.empty() && opStack.top() != static_cast<char>(Parenthes::Open))
					{
						m_pos += opStack.top();
						m_pos += ' ';
						opStack.pop();
					}
					opStack.pop();
					i++;
				}
			}
			else if (m_str[i] = ' ')
				i++;
		}
		while (!opStack.empty())
		{
			m_pos += opStack.top();
			opStack.pop();
		}
	}
	int Calculator::do_calculation()
	{
		std::stack<int> opStack;
		std::string tmp;
		while (!m_pos.empty())
		{
			if (m_pos[0] == ' ')
				m_pos.erase(m_pos.begin());
			else if (is_operand(m_pos[0]))
			{
				while (m_pos[0] != ' ' && is_operand(m_pos[0]))
				{
					tmp += m_pos[0];
					m_pos.erase(m_pos.begin());
				}
				opStack.push(std::stoi(tmp));
				tmp.erase(tmp.begin(), tmp.end());
			}
			else if (is_operator(m_pos[0]))
			{
				int op1 = opStack.top();
				opStack.pop();
				int op2 = opStack.top();
				opStack.pop();
				int val = compute(op2, op1, m_pos[0]);
				opStack.push(val);
				m_pos.erase(m_pos.begin());
			}
			else
				throw UnknownExcep("Calculator.cpp", "do_calculation()", 88);
		}
		return opStack.top();
	}
	void Calculator::to_assembly()
	{
		while (!m_pos.empty())
		{
			if (is_operand(m_pos[0]))
			{

			}
		}
	}

	std::string Calculator::get_postfix()const
	{
		return m_pos;
	}
	void Calculator::set_osteram(std::string str)
	{
		m_ostream << str << std::endl;
	}

	//private functions//
	bool Calculator::is_operator(const char& ch)const
	{
		return
			(
				ch == static_cast<char>(Operators::Add) ||
				ch == static_cast<char>(Operators::Deegre) ||
				ch == static_cast<char>(Operators::Divide) ||
				ch == static_cast<char>(Operators::Minus) ||
				ch == static_cast<char>(Operators::Plus)
				);
	}
	bool Calculator::is_operand(const char& ch)const
	{
		return (!is_operator(ch) && !is_parenthes(ch));
	}
	bool Calculator::is_parenthes(const char& ch)const
	{
		return (ch == static_cast<char>(Parenthes::Open) || ch == static_cast<char>(Parenthes::Close));
	}
	int Calculator::op_value(const char& ch)const
	{
		switch (ch)
		{
		case'+':
		case'-':
			return 1;
		case'*':
		case'/':
			return 2;
		case'^':
			return 3;
		default:
			return -1; // if case "(65+45)" check top of opStack
			//throw WrongOperator("Convert.cpp", "ch_value()", 178);
		}
	}
	int Calculator::compute(int op1, int op2, const char op)
	{
		int val = 0;
		switch (op)
		{
		case '+':
			val = op1 + op2;
			break;
		case '-':
			val = op1 - op2;
			break;
		case '*':
			val = op1 * op2;
			break;
		case '/':
			val = op1 / op2;
			break;
		case '%':
			val = op1 % op2;
			break;
		case '^':
			val = op1 ^ op2;
			break;
		default:
			throw WrongOperator("Convert.cpp", "int compute()", 112);
		}
		return val;
	}


}