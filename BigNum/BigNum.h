#pragma once

#include <vector>
#include <string>

class BigNum
{
friend bool operator<(const BigNum& a, const BigNum& b);
friend bool operator<=(const BigNum& a, const BigNum& b);
friend bool operator==(const BigNum& a, const BigNum& b);
friend bool operator>(const BigNum& a, const BigNum& b);
friend bool operator>=(const BigNum& a, const BigNum& b);

friend BigNum operator+(const BigNum& a, const BigNum& b);
friend BigNum operator-(const BigNum& num);
friend BigNum operator-(const BigNum& a, const BigNum& b);

public:
    explicit BigNum(std::string s);
    explicit BigNum(unsigned int n);

    bool isPositive() const;
    bool isNegative() const;
    size_t numDigits() const;
    unsigned int digitAt(size_t i) const;

    std::string display() const;

private:
    BigNum();

    std::vector<char> digits;
    bool hasNegativeSign = false;
};

bool operator<(const BigNum& a, const BigNum& b);
bool operator<=(const BigNum& a, const BigNum& b);
bool operator==(const BigNum& a, const BigNum& b);
bool operator>(const BigNum& a, const BigNum& b);
bool operator>=(const BigNum& a, const BigNum& b);

BigNum operator+(const BigNum& a, const BigNum& b);
BigNum operator-(const BigNum& num);
BigNum operator-(const BigNum& a, const BigNum& b);
