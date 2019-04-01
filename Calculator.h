#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <sstream>
	namespace
	{
		enum class Operators : char
		{
			Plus = '+',
			Minus = '-',
			Divide = '/',
			Add = '*',
			Deegre = '^',
		};

		enum class Parenthes : char
		{
			Open = '(',
			Close = ')',
		};
	}


	class Caluclator
	{
	public:
		Caluclator() = default;
		Caluclator(std::string str) : m_str(str) {}
		void to_postfix();
		int do_calculation();
		void to_assembly();
		std::string get_postfix()const;

		void set_osteram(std::string);
	private:
		bool is_operator(const char&)const;
		bool is_operand(const char&)const;
		bool is_parenthes(const char&)const;
		int  op_value(const char&)const;
		int  compute(int, int, const char);

	private:
		std::string m_str;
		std::string m_pos;
		std::ostringstream m_ostream;
		std::istringstream m_istream;
		std::string m_fileName;
	};
#endif