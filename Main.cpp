#include "pch.h"
#include <iostream>

#include "Calculator.h"

int main()
{
	Caluclator ob("(35+300)*(60+55)");
	ob.to_postfix();
	std::cout << ob.get_postfix() << std::endl;
	std::cout << ob.do_calculation() << std::endl;
}