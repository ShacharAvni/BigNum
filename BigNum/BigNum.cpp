#include "BigNum.h"

#include <algorithm>
#include <list>
#include <cassert>

static std::vector<char> uintToChars(unsigned int n)
{
    if (n == 0)
    {
        return { '0' };
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

unsigned int digitToUint(char digit)
{
    return static_cast<unsigned int>(digit - '0');
}

BigNum::BigNum()
{
}

BigNum::BigNum(const std::string& s)
{
    if (s.empty())
    {
        assert(false);
        digits.resize(1, '0');
        return;
    }

    digits.resize(s.length());

    size_t i = 0;
    for (auto it = s.rbegin(); it != s.rend(); ++it, ++i)
    {
        if ((*it >= '0') && (*it <= '9'))
        {
            digits[i] = *it;
        }
        else
        {
            assert(false);
            digits[i] = '0';
        }
    }
}

BigNum::BigNum(unsigned int n)
    : digits(uintToChars(n))
{
}

size_t BigNum::numDigits() const
{
    return digits.size();
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

std::string BigNum::display() const
{
    std::vector<char> reversed = digits;
    std::reverse(reversed.begin(), reversed.end());

    reversed.push_back('\0');

    return reversed.data();
}

bool operator>(const BigNum& a, const BigNum& b)
{
    if (a.numDigits() > b.numDigits())
    {
        return true;
    }

    if (b.numDigits() > a.numDigits())
    {
        return false;
    }

    auto aIter = a.digits.rbegin();
    auto bIter = b.digits.rbegin();

    while (aIter != a.digits.rend())
    {
        unsigned int digitA = digitToUint(*aIter);
        unsigned int digitB = digitToUint(*bIter);

        if (digitA > digitB)
        {
            return true;
        }

        if (digitA < digitB)
        {
            return false;
        }

        ++aIter;
        ++bIter;
    }

    return false;
}

BigNum operator+(const BigNum& a, const BigNum& b)
{
    size_t maxDigits = std::max(a.numDigits(), b.numDigits());

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

        currentSum += a.digitAt(i);
        currentSum += b.digitAt(i);

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

    return result;
}
