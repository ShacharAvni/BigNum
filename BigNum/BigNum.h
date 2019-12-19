#pragma once

#include <vector>
#include <string>
#include <utility>

class BigNum
{
friend bool operator<(const BigNum& a, const BigNum& b);
friend bool operator<=(const BigNum& a, const BigNum& b);
friend bool operator==(const BigNum& a, const BigNum& b);
friend bool operator!=(const BigNum& a, const BigNum& b);
friend bool operator>(const BigNum& a, const BigNum& b);
friend bool operator>=(const BigNum& a, const BigNum& b);

friend BigNum operator+(const BigNum& a, const BigNum& b);
friend void operator+=(BigNum& a, const BigNum& b);
friend BigNum operator-(const BigNum& num);
friend BigNum operator-(const BigNum& a, const BigNum& b);
friend void operator-=(BigNum& a, const BigNum& b);
friend BigNum operator*(const BigNum& a, const BigNum& b);
friend void operator*=(BigNum& a, const BigNum& b);
friend BigNum operator/(const BigNum& a, const BigNum& b);
friend void operator/=(BigNum& a, const BigNum& b);

friend BigNum abs(const BigNum& n);

public:
    explicit BigNum(std::string s);
    explicit BigNum(unsigned int n);

    static const BigNum Zero;
    static const int MaxDigitsAfterDecimal = 1000;

    static BigNum makeWithAdditionalTrailingZeroes(const BigNum& n, size_t numAdditionalTrailingZeroes);

    bool isPositive() const;
    bool isNegative() const;
    size_t numDigits() const;
    size_t numDigitsBeforeDecimal() const;
    size_t numDigitsAfterDecimal() const;
    size_t getDecimalPosition() const;
    unsigned int digitAt(size_t i) const;

    std::string display() const;

    BigNum multPower10(size_t power10) const;
    BigNum dividePower10(size_t power10) const;

private:
    BigNum();

    void forceZero();

    void removeLeadingAndTrailingZeroes();

    BigNum removeLeadingZeroes() const;
    BigNum removeTrailingZeroes() const;

    std::vector<char> digits;
    bool hasNegativeSign = false;
    size_t decimalPosition = 0;
};

bool operator<(const BigNum& a, const BigNum& b);
bool operator<=(const BigNum& a, const BigNum& b);
bool operator==(const BigNum& a, const BigNum& b);
bool operator!=(const BigNum& a, const BigNum& b);
bool operator>(const BigNum& a, const BigNum& b);
bool operator>=(const BigNum& a, const BigNum& b);

BigNum operator+(const BigNum& a, const BigNum& b);
void operator+=(BigNum& a, const BigNum& b);
BigNum operator-(const BigNum& num);
BigNum operator-(const BigNum& a, const BigNum& b);
void operator-=(BigNum& a, const BigNum& b);
BigNum operator*(const BigNum& a, const BigNum& b);
void operator*=(BigNum& a, const BigNum& b);
BigNum operator/(const BigNum& a, const BigNum& b);
void operator/=(BigNum& a, const BigNum& b);

BigNum abs(const BigNum& n);
