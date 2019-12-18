#include "BigNum.h"

#include <algorithm>
#include <list>
#include <cassert>

const BigNum BigNum::Zero("0");

static std::vector<char> uintToChars(unsigned int n)
{
    if (n == 0)
    {
        return {'0'};
    }

    std::vector<char> chars;

    while (n != 0)
    {
        char nextChar = (n % 10);
        n -= static_cast<unsigned int>(nextChar);
        n /= 10;

        chars.push_back(nextChar + '0');
    }

    return chars;
}

BigNum BigNum::makeWithAdditionalTrailingZeroes(const BigNum& n, size_t numAdditionalTrailingZeroes)
{
    BigNum withAdditionalTrailingZeroes = n;

    std::vector<char> zeroes(numAdditionalTrailingZeroes, '0');

    std::vector<char> digits = std::move(withAdditionalTrailingZeroes.digits);

    withAdditionalTrailingZeroes.digits = zeroes;
    withAdditionalTrailingZeroes.digits.insert(withAdditionalTrailingZeroes.digits.end(), digits.begin(), digits.end());

    withAdditionalTrailingZeroes.decimalPosition += numAdditionalTrailingZeroes;

    return withAdditionalTrailingZeroes;
}

std::pair<BigNum, BigNum> makeWithLinedUpDecimalPositions(const BigNum& a, const BigNum& b)
{
    if (a.numDigitsAfterDecimal() > b.numDigitsAfterDecimal())
    {
        return { a, BigNum::makeWithAdditionalTrailingZeroes(b, a.numDigitsAfterDecimal() - b.numDigitsAfterDecimal()) };
    }
    else
    {
        return { BigNum::makeWithAdditionalTrailingZeroes(a, b.numDigitsAfterDecimal() - a.numDigitsAfterDecimal()), b };
    }
}

unsigned int digitToUint(char digit)
{
    return static_cast<unsigned int>(digit - '0');
}

BigNum::BigNum()
{
}

BigNum::BigNum(std::string s)
{
    if (s.empty())
    {
        forceZero();
        return;
    }

    if (s[0] == '-')
    {
        if (s.length() == 1)
        {
            forceZero();
            return;
        }

        hasNegativeSign = true;

        s = s.substr(1, s.length() - 1);
    }

    size_t decimalFindResult = s.find('.');

    bool hasDecimal = (decimalFindResult != std::string::npos);

    size_t numDecimals = 0;

    digits.resize(s.length() - (hasDecimal ? 1 : 0));

    if (hasDecimal)
    {
        decimalPosition = digits.size() - decimalFindResult;
    }

    size_t i = 0;
    for (auto it = s.rbegin(); it != s.rend(); ++it, ++i)
    {
        if ((*it >= '0') && (*it <= '9'))
        {
            digits[i] = *it;
        }
        else if (*it == '.')
        {
            ++numDecimals;
            if (numDecimals == 1)
            {
                --i;
            }
            else
            {
                assert(false);
                digits[i] = '0';
            }

            continue;
        }
        else
        {
            assert(false);
            digits[i] = '0';
        }
    }

    if (decimalFindResult == 0)
    {
        digits.push_back('0');
    }

    removeLeadingAndTrailingZeroes();
}

BigNum::BigNum(unsigned int n)
    : digits(uintToChars(n))
{
}

void BigNum::forceZero()
{
    assert(false);
    digits.resize(1, '0');
}

void BigNum::removeLeadingAndTrailingZeroes()
{
    *this = removeLeadingZeroes().removeTrailingZeroes();
}

BigNum BigNum::removeLeadingZeroes() const
{
    BigNum result = *this;

    size_t numZeroesOnLeft = 0;
    for (auto it = result.digits.rbegin(); it != result.digits.rend(); ++it)
    {
        if (digitToUint(*it) != 0)
        {
            break;
        }

        ++numZeroesOnLeft;
    }

    if (numZeroesOnLeft == result.numDigits())
    {
        result.digits.resize(1, '0');
        result.decimalPosition = 0;
    }
    else
    {
        size_t numLeadingZeroesToDiscard = std::min(numDigitsBeforeDecimal() - 1, numZeroesOnLeft);

        result.digits.erase(result.digits.end() - numLeadingZeroesToDiscard, result.digits.end());
    }

    return result;
}

BigNum BigNum::removeTrailingZeroes() const
{
    BigNum result = *this;

    size_t numZeroesOnRight = 0;
    for (size_t i = 0; i < numDigits(); ++i)
    {
        if (digitAt(i) != 0)
        {
            break;
        }

        ++numZeroesOnRight;
    }

    if (numZeroesOnRight == numDigits())
    {
        result.digits.resize(1, '0');
        result.decimalPosition = 0;
        return result;
    }

    size_t numTrailingZeroesToDiscard = std::min(numZeroesOnRight, result.numDigitsAfterDecimal());

    if (numTrailingZeroesToDiscard > 0)
    {
        if (decimalPosition < numTrailingZeroesToDiscard)
        {
            result.decimalPosition = 0;
        }
        else
        {
            result.decimalPosition -= numTrailingZeroesToDiscard;
        }

        size_t numDigitsAfterDiscardingTrailingZeroes = result.numDigits() - numTrailingZeroesToDiscard;

        std::vector<char> newDigits(numDigitsAfterDiscardingTrailingZeroes);

        for (size_t i = 0; i < numDigitsAfterDiscardingTrailingZeroes; ++i)
        {
            newDigits[i] = digits[i + numTrailingZeroesToDiscard];
        }

        result.digits = std::move(newDigits);
    }

    return result;
}

bool BigNum::isPositive() const
{
    return !isNegative();
}

bool BigNum::isNegative() const
{
    return hasNegativeSign;
}

size_t BigNum::numDigits() const
{
    return digits.size();
}

size_t BigNum::numDigitsBeforeDecimal() const
{
    return numDigits() - decimalPosition;
}

size_t BigNum::numDigitsAfterDecimal() const
{
    return numDigits() - numDigitsBeforeDecimal();
}

size_t BigNum::getDecimalPosition() const
{
    return decimalPosition;
}

unsigned int BigNum::digitAt(size_t i) const
{
    if (i >= numDigits())
    {
        // Not an error as there are leading zeroes
        return 0;
    }

    return digitToUint(digits[i]);
}

BigNum BigNum::multPower10(size_t power10) const
{
    BigNum result;

    if (this->decimalPosition >= power10)
    {
        result = *this;
        result.decimalPosition = this->decimalPosition - power10;
    }
    else
    {
        std::vector<char> zeroes(power10 - this->decimalPosition, '0');

        result.hasNegativeSign = this->hasNegativeSign;

        result.digits.reserve(zeroes.size() + this->digits.size());

        result.digits.insert(result.digits.end(), zeroes.begin(), zeroes.end());
        result.digits.insert(result.digits.end(), this->digits.begin(), this->digits.end());
    }

    return result.removeTrailingZeroes();
}

BigNum BigNum::dividePower10(size_t power10) const
{
    BigNum result;

    if ((this->decimalPosition + power10) < numDigits())
    {
        result = *this;
        result.decimalPosition = this->decimalPosition + power10;
    }
    else
    {
        std::vector<char> zeroes((this->decimalPosition + power10) - (numDigits() - 1), '0');

        result.hasNegativeSign = this->hasNegativeSign;

        result.digits.reserve(this->digits.size() + zeroes.size());

        result.digits.insert(result.digits.end(), this->digits.begin(), this->digits.end());
        result.digits.insert(result.digits.end(), zeroes.begin(), zeroes.end());

        result.decimalPosition = result.numDigits() - zeroes.size();
    }

    return result;
}

std::string BigNum::display() const
{
    std::vector<char> displayed;

    displayed.reserve(numDigits() + 3); // reserve space for possible negative sign, decimal, and null terminator

    if (isNegative())
    {
        displayed.push_back('-');
    }

    std::vector<char> reversed = digits;
    std::reverse(reversed.begin(), reversed.end());

    displayed.insert(displayed.end(), reversed.begin(), reversed.end());

    if (decimalPosition != 0)
    {
        displayed.insert(displayed.end() - decimalPosition, '.');
    }

    displayed.push_back('\0');

    return displayed.data();
}

bool operator<(const BigNum& a, const BigNum& b)
{
    return !(a >= b);
}

bool operator<=(const BigNum& a, const BigNum& b)
{
    return !(a > b);
}

bool operator==(const BigNum& a, const BigNum& b)
{
    if (a.isNegative() && b.isPositive())
    {
        return false;
    }

    if (a.isPositive() && b.isNegative())
    {
        return false;
    }

    if (a.numDigits() != b.numDigits())
    {
        return false;
    }

    for (size_t i = 0; i < a.numDigits(); ++i)
    {
        if (a.digitAt(i) != b.digitAt(i))
        {
            return false;
        }
    }

    return true;
}

bool operator!=(const BigNum& a, const BigNum& b)
{
    return !(a == b);
}

bool operator>(const BigNum& a, const BigNum& b)
{
    if (a.isNegative() && b.isPositive())
    {
        return false;
    }

    if (a.isPositive() && b.isNegative())
    {
        return true;
    }

    if (a.isNegative() && b.isNegative())
    {
        return (-(a) < -(b));
    }

    if (a.numDigitsBeforeDecimal() > b.numDigitsBeforeDecimal())
    {
        return true;
    }

    if (b.numDigitsBeforeDecimal() > a.numDigitsBeforeDecimal())
    {
        return false;
    }

    std::pair<BigNum, BigNum> decimalsLinedUp = makeWithLinedUpDecimalPositions(a, b);

    auto firstIter = decimalsLinedUp.first.digits.rbegin();
    auto secondIter = decimalsLinedUp.second.digits.rbegin();

    while (firstIter != decimalsLinedUp.first.digits.rend())
    {
        unsigned int firstDigit = digitToUint(*firstIter);
        unsigned int secondDigit = digitToUint(*secondIter);

        if (firstDigit > secondDigit)
        {
            return true;
        }

        if (firstDigit < secondDigit)
        {
            return false;
        }

        ++firstIter;
        ++secondIter;
    }

    return false;
}

bool operator>=(const BigNum& a, const BigNum& b)
{
    return ((a > b) || (a == b));
}

BigNum operator+(const BigNum& a, const BigNum& b)
{
    if (a.isNegative() && b.isPositive())
    {
        return (b - -(a));
    }

    if (a.isPositive() && b.isNegative())
    {
        return (a - -(b));
    }

    if (a.isNegative() && b.isNegative())
    {
        return -(-(a) + -(b));
    }

    std::pair<BigNum, BigNum> decimalsLinedUp = makeWithLinedUpDecimalPositions(a, b);

    size_t maxDigits = std::max(decimalsLinedUp.first.numDigits(), decimalsLinedUp.second.numDigits());

    std::list<std::vector<char>> carries;

    BigNum result;

    size_t i = 0;
    while ((i < maxDigits) || !carries.empty())
    {
        unsigned int currentSum = 0;

        if (!carries.empty())
        {
            for (char c : carries.front())
            {
                currentSum += digitToUint(c);
            }

            carries.pop_front();
        }

        currentSum += decimalsLinedUp.first.digitAt(i);
        currentSum += decimalsLinedUp.second.digitAt(i);

        std::vector<char> chars = uintToChars(currentSum);

        result.digits.push_back(chars[0]);

        auto carriesIter = carries.begin();

        for (size_t currentSumCharIndex = 1; currentSumCharIndex < chars.size(); ++currentSumCharIndex)
        {
            if (carriesIter == carries.end())
            {
                carries.push_front({});
                carriesIter = carries.begin();
            }

            carriesIter->push_back(chars[currentSumCharIndex]);
            ++carriesIter;
        }

        ++i;
    }

    result.decimalPosition = decimalsLinedUp.first.numDigitsAfterDecimal();

    return result;
}

void operator+=(BigNum& a, const BigNum& b)
{
    a = a + b;
}

BigNum operator-(const BigNum& num)
{
    BigNum negated = num;
    negated.hasNegativeSign = !negated.hasNegativeSign;

    return negated;
}

BigNum operator-(const BigNum& a, const BigNum& b)
{
    if (a.isNegative() && b.isPositive())
    {
        return -(-(a) + b);
    }

    if (a.isPositive() && b.isNegative())
    {
        return (a + -(b));
    }

    if (a.isNegative() && b.isNegative())
    {
        return (-(b) - -(a));
    }

    if (b > a)
    {
        return -(b - a);
    }

    BigNum result;

    std::pair<BigNum, BigNum> decimalsLinedUp = makeWithLinedUpDecimalPositions(a, b);

    size_t maxDigits = std::max(decimalsLinedUp.first.numDigits(), decimalsLinedUp.second.numDigits());
    for (size_t i = 0; i < maxDigits; ++i)
    {
        unsigned int currentDifference = decimalsLinedUp.first.digitAt(i);

        if (decimalsLinedUp.first.digitAt(i) < decimalsLinedUp.second.digitAt(i))
        {
            currentDifference += 10;

            size_t borrowIndex = i + 1;

            while (decimalsLinedUp.first.digitAt(borrowIndex) == 0)
            {
                decimalsLinedUp.first.digits[borrowIndex] = '9';
                ++borrowIndex;
            }

            decimalsLinedUp.first.digits[borrowIndex] -= static_cast<char>(1);
        }

        currentDifference -= decimalsLinedUp.second.digitAt(i);

        std::vector<char> chars = uintToChars(currentDifference);
        assert(chars.size() == 1);

        result.digits.push_back(chars[0]);
    }

    result.decimalPosition = decimalsLinedUp.first.numDigitsAfterDecimal();

    return result.removeLeadingZeroes();
}

void operator-=(BigNum& a, const BigNum& b)
{
    a = a - b;
}

static bool haveDifferentSigns(const BigNum& a, const BigNum& b)
{
    return ((a.isNegative() && !b.isNegative()) || (!a.isNegative() && b.isNegative()));
}

BigNum multLessThan10(const BigNum& lessThan10, const BigNum& n)
{
    BigNum result = BigNum::Zero;

    BigNum absN = abs(n);

    unsigned int absLessThan10AsNum = lessThan10.digitAt(0);

    for (unsigned int i = 0; i < absLessThan10AsNum; ++i)
    {
        result += absN;
    }

    if (haveDifferentSigns(lessThan10, n))
    {
        return -result;
    }

    return result;
}

BigNum operator*(const BigNum& a, const BigNum& b)
{
    BigNum result = BigNum::Zero;

    std::pair<BigNum, BigNum> decimalsLinedUp = makeWithLinedUpDecimalPositions(a, b);

    size_t numAfterDecimal = decimalsLinedUp.first.numDigitsAfterDecimal();

    std::pair<BigNum, BigNum> withoutDecimals = { decimalsLinedUp.first.multPower10(numAfterDecimal), decimalsLinedUp.second.multPower10(numAfterDecimal) };

    for (size_t i = 0; i < withoutDecimals.first.numDigits(); ++i)
    {
        BigNum aDigit(withoutDecimals.first.digitAt(i));
        aDigit.hasNegativeSign = withoutDecimals.first.hasNegativeSign;

        result += multLessThan10(aDigit, withoutDecimals.second).multPower10(i);
    }

    return result.dividePower10(2 * numAfterDecimal).removeTrailingZeroes();
}

void operator*=(BigNum& a, const BigNum& b)
{
    a = a * b;
}

static BigNum integerDivide(const BigNum& dividend, const BigNum& divisor)
{
    BigNum result = BigNum::Zero;

    BigNum remainder = dividend;

    while (remainder >= divisor)
    {
        remainder -= divisor;
        result += BigNum("1");
    }

    return result;
}

BigNum operator/(const BigNum& a, const BigNum& b)
{
    if (abs(b) == BigNum::Zero)
    {
        assert(false);
        return BigNum::Zero;
    }

    size_t maxDecimals = std::max(a.numDigitsAfterDecimal(), b.numDigitsAfterDecimal());

    BigNum dividend = abs(a.multPower10(maxDecimals));
    BigNum divisor = abs(b.multPower10(maxDecimals));

    std::vector<char> resultString;

    if (haveDifferentSigns(a, b))
    {
        resultString.push_back('-');
    }

    resultString.push_back('0');

    size_t digitIndex = dividend.numDigits() - 1;
    BigNum integerDividend = BigNum(dividend.digitAt(digitIndex));

    int digitsAfterDecimal = -1;

    while (integerDividend != BigNum::Zero)
    {
        BigNum singleDigitResult = integerDivide(integerDividend, divisor);
        assert(singleDigitResult.numDigits() == 1);

        resultString.push_back(singleDigitResult.digits[0]);

        integerDividend -= singleDigitResult * divisor;

        integerDividend = integerDividend.multPower10(1);

        if (digitIndex == 0)
        {
            ++digitsAfterDecimal;
            if (digitsAfterDecimal == BigNum::MaxDigitsAfterDecimal)
            {
                break;
            }
        }
        else
        {
            --digitIndex;
            integerDividend += BigNum(dividend.digitAt(digitIndex));
        }
    }

    if (digitsAfterDecimal > 0)
    {
        size_t negativeSignOffset = (resultString[0] == '-') ? 1 : 0;
        resultString.insert(resultString.begin() + dividend.numDigits() + 1 + negativeSignOffset, '.');
    }

    resultString.push_back('\0');

    return BigNum(resultString.data());
}

void operator/=(BigNum& a, const BigNum& b)
{
    a = a / b;
}

BigNum abs(const BigNum& n)
{
    BigNum result = n;
    result.hasNegativeSign = false;

    return result;
}
