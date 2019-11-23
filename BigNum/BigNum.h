#pragma once

#include <vector>
#include <string>

class BigNum
{
friend BigNum operator+(const BigNum& a, const BigNum& b);

public:
    explicit BigNum(const std::string& s);
    explicit BigNum(unsigned int n);

    size_t numDigits() const;
    unsigned int digitAt(size_t i) const;

    std::string display() const;

private:
    BigNum();

    std::vector<char> digits;
};

BigNum operator+(const BigNum& a, const BigNum& b);
