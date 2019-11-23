#include "BigNum.h"

#include <iostream>
#include <limits>

void singleAdditionUnitTest(const std::string& a, const std::string& b)
{
    std::cout << a << " + " << b << " is " << (BigNum(a) + BigNum(b)).display() << std::endl;
}

void additionUnitTests()
{
    singleAdditionUnitTest("0", "0"); // should be 0
    singleAdditionUnitTest("1", "0"); // should be 1
    singleAdditionUnitTest("1", "1"); // should be 2
    singleAdditionUnitTest("1234", "1234"); // should be 2468
    singleAdditionUnitTest("97654321", "812345512"); // should be 909999833
}

void singleGreaterThanUnitTest(const std::string& a, const std::string& b)
{
    std::cout << a << " > " << b << " is " << std::boolalpha << (BigNum(a) > BigNum(b)) << std::endl;
}

void greaterThanUnitTests()
{
    singleGreaterThanUnitTest("0", "0"); // should be false
    singleGreaterThanUnitTest("1", "0"); // should be true
    singleGreaterThanUnitTest("0", "1"); // should be false
    singleGreaterThanUnitTest("1234", "123"); // should be true
    singleGreaterThanUnitTest("45681565515", "45681566515"); // should be false
}

int main()
{
    additionUnitTests();
    greaterThanUnitTests();

    std::cout << "Press enter to continue..." << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return 0;
}
