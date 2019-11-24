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

    singleAdditionUnitTest("1", "-1"); // should be 0
    singleAdditionUnitTest("-1234", "-3456"); // should be -4690
    singleAdditionUnitTest("-3456", "1234"); // -2222
}

void singleSubtractionUnitTest(const std::string& a, const std::string& b)
{
    std::cout << a << " - " << b << " is " << (BigNum(a) - BigNum(b)).display() << std::endl;
}

void subtractionUnitTests()
{
    singleSubtractionUnitTest("0", "0"); // should be 0
    singleSubtractionUnitTest("1", "0"); // should be 1
    singleSubtractionUnitTest("1", "1"); // should be 0
    singleSubtractionUnitTest("2468", "1234"); // should be 1234
    singleSubtractionUnitTest("97654321", "812345512"); // should be -714691191

    singleSubtractionUnitTest("1", "-1"); // should be 2
    singleSubtractionUnitTest("-1234", "-3456"); // should be 2222
    singleSubtractionUnitTest("-3456", "1234"); // should be -4690
}

void singleLessThanUnitTest(const std::string& a, const std::string& b)
{
    std::cout << a << " < " << b << " is " << std::boolalpha << (BigNum(a) < BigNum(b)) << std::endl;
}

void lessThanUnitTests()
{
    singleLessThanUnitTest("0", "0"); // should be false
    singleLessThanUnitTest("1", "0"); // should be false
    singleLessThanUnitTest("0", "1"); // should be true
    singleLessThanUnitTest("1234", "123"); // should be false
    singleLessThanUnitTest("45681565515", "45681566515"); // should be true

    singleLessThanUnitTest("1234", "-1234"); // should be false
    singleLessThanUnitTest("-3456", "1234"); // should be true
    singleLessThanUnitTest("-1234", "-3456"); // should be false
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

    singleGreaterThanUnitTest("1234", "-1234"); // should be true
    singleGreaterThanUnitTest("-3456", "1234"); // should be false
    singleGreaterThanUnitTest("-1234", "-3456"); // should be true
}

int main()
{
    additionUnitTests();
    subtractionUnitTests();
    lessThanUnitTests();
    greaterThanUnitTests();

    std::cout << "Press enter to continue..." << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return 0;
}
