#include "BigNum.h"

#include <iostream>
#include <limits>

unsigned int numPassed = 0;
unsigned int numFailed = 0;

template <typename resultType>
void printResult(const resultType& actualResult)
{
    std::cout << actualResult;
}

template <>
void printResult(const bool& actualResult)
{
    std::cout << std::boolalpha << actualResult;
}

template <typename resultType>
void runUnitTest(const std::string& a, const std::string& b, const std::string& operation, const resultType& actualResult, const resultType& expectedResult)
{
    std::cout << a << operation << b << " is ";
    printResult(actualResult);
    std::cout << " : ";

    if (actualResult == expectedResult)
    {
        std::cout << "PASS";
        ++numPassed;
    }
    else
    {
        std::cout << "FAIL";
        ++numFailed;
    }

    std::cout << std::endl;
}

void singleAdditionUnitTest(const std::string& a, const std::string& b, const std::string& expectedResult)
{
    runUnitTest(a, b, " + ", (BigNum(a) + BigNum(b)).display(), expectedResult);
}

void additionUnitTests()
{
    singleAdditionUnitTest("0", "0", "0");
    singleAdditionUnitTest("1", "0", "1");
    singleAdditionUnitTest("1", "1", "2");
    singleAdditionUnitTest("1234", "1234", "2468");
    singleAdditionUnitTest("97654321", "812345512", "909999833");

    singleAdditionUnitTest("1", "-1", "0");
    singleAdditionUnitTest("-1234", "-3456", "-4690");
    singleAdditionUnitTest("-3456", "1234", "-2222");

    singleAdditionUnitTest("1.5", "2.25", "3.75");
    singleAdditionUnitTest("3", "1.23456", "4.23456");
    singleAdditionUnitTest("1.23456", "3", "4.23456");
}

void singleSubtractionUnitTest(const std::string& a, const std::string& b, const std::string& expectedResult)
{
    runUnitTest(a, b, " - ", (BigNum(a) - BigNum(b)).display(), expectedResult);
}

void subtractionUnitTests()
{
    singleSubtractionUnitTest("0", "0", "0");
    singleSubtractionUnitTest("1", "0", "1");
    singleSubtractionUnitTest("1", "1", "0");
    singleSubtractionUnitTest("2468", "1234", "1234");
    singleSubtractionUnitTest("97654321", "812345512", "-714691191");

    singleSubtractionUnitTest("1", "-1", "2");
    singleSubtractionUnitTest("-1234", "-3456", "2222");
    singleSubtractionUnitTest("-3456", "1234", "-4690");

    singleSubtractionUnitTest("1.5", "2.25", "-0.75");
    singleSubtractionUnitTest("3", "1.23456", "1.76544");
    singleSubtractionUnitTest("1.23456", "3", "-1.76544");
}

void singleMultiplicationUnitTest(const std::string& a, const std::string& b, const std::string& expectedResult)
{
    runUnitTest(a, b, " * ", (BigNum(a) * BigNum(b)).display(), expectedResult);
}

void multiplicationUnitTests()
{
    singleMultiplicationUnitTest("0", "0", "0");
    singleMultiplicationUnitTest("1", "0", "0");
    singleMultiplicationUnitTest("1", "1", "1");
    singleMultiplicationUnitTest("2468", "1234", "3045512");
    singleMultiplicationUnitTest("97654321", "812345512", "79329049391757352");

    singleMultiplicationUnitTest("1", "-1", "-1");
    singleMultiplicationUnitTest("-1234", "-3456", "4264704");
    singleMultiplicationUnitTest("-3456", "1234", "-4264704");

    singleMultiplicationUnitTest("1.5", "2.25", "3.375");
    singleMultiplicationUnitTest("3", "1.23456", "3.70368");
    singleMultiplicationUnitTest("-1.23456", "3", "-3.70368");
}

void singleDivisionUnitTest(const std::string& a, const std::string& b, const std::string& expectedResult)
{
    runUnitTest(a, b, " / ", (BigNum(a) / BigNum(b)).display(), expectedResult);
}

void divisionUnitTests()
{
    singleDivisionUnitTest("0", "1", "0");
    singleDivisionUnitTest("1", "2", "0.5");
    singleDivisionUnitTest("5", "2", "2.5");
    singleDivisionUnitTest("21542184597952765727218712792342", "100000000000000000000000000000000", "0.21542184597952765727218712792342");
    singleDivisionUnitTest("-21542184597952765727218712792342", "100000000000000000000000000000000", "-0.21542184597952765727218712792342");
    singleDivisionUnitTest("-21542184597952765727218712792342", "-100000000000000000000000000000000", "0.21542184597952765727218712792342");

    std::string zeroPoint3Repeating = "0.";
    zeroPoint3Repeating.append(BigNum::MaxDigitsAfterDecimal, '3');
    singleDivisionUnitTest("1", "3", zeroPoint3Repeating);
}

void singleLessThanUnitTest(const std::string& a, const std::string& b, bool expectedResult)
{
    runUnitTest(a, b, " < ", (BigNum(a) < BigNum(b)), expectedResult);
}

void lessThanUnitTests()
{
    singleLessThanUnitTest("0", "0", false);
    singleLessThanUnitTest("1", "0", false);
    singleLessThanUnitTest("0", "1", true);
    singleLessThanUnitTest("1234", "123", false);
    singleLessThanUnitTest("2468", "2468", false);
    singleLessThanUnitTest("45681565515", "45681566515", true);

    singleLessThanUnitTest("1234", "-1234", false);
    singleLessThanUnitTest("-3456", "1234", true);
    singleLessThanUnitTest("-1234", "-3456", false);

    singleLessThanUnitTest("1.23456789", "2.5", true);
    singleLessThanUnitTest("3.1", "4", true);
    singleLessThanUnitTest("5", "4.75", false);
}

void singleGreaterThanUnitTest(const std::string& a, const std::string& b, bool expectedResult)
{
    runUnitTest(a, b, " > ", (BigNum(a) > BigNum(b)), expectedResult);
}

void greaterThanUnitTests()
{
    singleGreaterThanUnitTest("0", "0", false);
    singleGreaterThanUnitTest("1", "0", true);
    singleGreaterThanUnitTest("0", "1", false);
    singleGreaterThanUnitTest("1234", "123", true);
    singleGreaterThanUnitTest("2468", "2468", false);
    singleGreaterThanUnitTest("45681565515", "45681566515", false);

    singleGreaterThanUnitTest("1234", "-1234", true);
    singleGreaterThanUnitTest("-3456", "1234", false);
    singleGreaterThanUnitTest("-1234", "-3456", true);

    singleGreaterThanUnitTest("1.23456789", "2.5", false);
    singleGreaterThanUnitTest("3.1", "4", false);
    singleGreaterThanUnitTest("5", "4.75", true);
}

int main()
{
    additionUnitTests();
    subtractionUnitTests();
    multiplicationUnitTests();
    divisionUnitTests();
    lessThanUnitTests();
    greaterThanUnitTests();

    std::cout << std::endl;
    std::cout << numPassed << " passed" << std::endl;
    std::cout << numFailed << " failed" << std::endl;
    std::cout << std::endl;

    std::cout << "Press enter to continue..." << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return 0;
}
