#include <iostream>
#include <string>
#include <algorithm>
#include <cstddef>
#include "BigInt.h"

void removeZeros(std::string& num)
{
        int len = num.length();
        if(num.find_first_not_of('0') == std::string::npos)
                num = "0";
        else
                num = num.substr(num.find_first_not_of('0'));
}

BigInt::BigInt(std::string num)
: _number{num}
{
	removeZeros(_number);
}

BigInt::BigInt(const BigInt& obj)
: _number{obj._number}
{
	removeZeros(_number);
}

void BigInt::setNum(std::string num)
{
	removeZeros(num);
	_number = num;
		
}

std::string BigInt::getNum() const
{
	return _number;
}

std::string BigInt::mod() const
{
	if(_number[0] == '-')
		return _number.substr(1);
	return _number;
}

bool isSmaller(const std::string num1, const std::string num2)
{
	long len1 = num1.length();
	long len2 = num2.length();
	if(len1 < len2)
		return true;
	if(len2 < len1)
		return false;
	for(int i = 0; i < len1; ++i)
	{
		if(num1[i] < num2[i])
			return true;
		else if(num1[i] > num2[i])
			return false;
	}
	return false;
}

std::string sumOfPos(std::string num1, std::string num2)
{
	std::string sum = "";

	if(num1.length() > num2.length())
		std::swap(num1, num2);

        long len1 = num1.length();
        long len2 = num2.length();

        std::reverse(num1.begin(), num1.end());
        std::reverse(num2.begin(), num2.end());

        int carry = 0;
        for(int i = 0; i < len1; ++i)
        {
                int x = ((num1[i] - '0') + (num2[i] - '0') + carry);
                sum.push_back(x % 10 + '0');
                carry = x / 10;
        }
        for(int i = len1; i < len2; ++i)
        {
                int x = ((num2[i] - '0') + carry);
                sum.push_back(x % 10 + '0');
                carry = x / 10;
        }
        if(carry)
                sum.push_back(carry + '0');
        std::reverse(sum.begin(), sum.end());

        return sum;
}

std::string diffOfPos(std::string num1, std::string num2)
{
	if(num1 == "0" && num2 != "0")
		return '-' + num2;
	std::string result = "";
	if(isSmaller(num1, num2))
		std::swap(num1, num2);
	long len1 = num1.length();
	long len2 = num2.length();
	long diff = len1 - len2;
	int carry = 0;
	for(int i = len2 - 1; i >= 0; --i)
	{
		int sub = ((num1[i + diff] - '0') - (num2[i] - '0') - carry);
		if(sub < 0)
		{
			sub += 10;
			carry = 1;
		}
		else
			carry = 0;
		result.push_back(sub + '0');
	}
	for(int i = len1 - len2 - 1; i >= 0; --i)
	{
		if(num1[i] == '0' && carry)
		{
			result.push_back('9');
			continue;
		}
		int sub = ((num1[i] - '0') - carry);
		if(i > 0 || sub > 0)
			result.push_back(sub + '0');
		carry = 0;
	}

	std::reverse(result.begin(), result.end());
	removeZeros(result);
	return result;
}

BigInt operator+(const BigInt& num1, const BigInt& num2)
{
	std::string sum;
	if((num1._number)[0] == '-' && (num2._number)[0] != '-')
	{
		if(isSmaller(num1.mod(), num2._number))
			return BigInt(diffOfPos(num2._number, num1.mod()));
		if(isSmaller(num2._number, num1.mod()))
			return BigInt('-' + diffOfPos(num1.mod(), num2._number));
		return BigInt("0"); 
	}
	if((num1._number)[0] != '-' && (num2._number)[0] == '-') 
	{
		if(isSmaller(num1._number, num2.mod()))
			return BigInt('-' + diffOfPos(num2.mod(), num1._number));
		if(isSmaller(num2.mod(), num1._number))
			return BigInt(diffOfPos(num1._number, num2.mod()));
		return BigInt(diffOfPos(num1._number, num2._number)); // !!!
	}
	if((num1._number)[0] == '-' && (num2._number)[0] == '-')
		return BigInt('-' + sumOfPos(num1.mod(), num2.mod()));
	return BigInt(sumOfPos(num1._number, num2._number));
}

BigInt operator-(const BigInt& num1, const BigInt& num2)
{
	std::string result;
	if(num1._number[0] != '-' && num2._number[0] == '-')
		return BigInt(sumOfPos(num1._number, num2.mod()));
	if(num1._number[0] == '-' && num2._number[0] != '-')
		return BigInt('-' + sumOfPos(num1._number.substr(1), num2._number));
	if(num1._number[0] == '-' && num2._number[0] == '-')
	{
		if(isSmaller(num1.mod(), num2.mod())) 
			return BigInt(diffOfPos(num2.mod(), num1.mod()));
		if(isSmaller(num2.mod(), num1.mod()))
			return BigInt('-' + diffOfPos(num1.mod(), num2.mod()));
		return BigInt("0");
	}
	return BigInt(diffOfPos(num1._number, num2._number));
}

BigInt operator*(const BigInt& num1, const BigInt& num2)
{
	if(num1._number == "0" || num2._number == "0")
		return BigInt("0");
	if(num1._number[0] == '-' && num2._number[0] == '-')
		return BigInt(num1.mod() * num2.mod());
	long len1 = num1._number.length();
	long len2 = num2._number.length();
	std::string product = "";
	for(int i = len1 - 1; i >= 0; --i)
	{
		int carry = 0;
		std::string val;
		for(int j = len2 - 1; j >= 0; --j)
		{
			int p = (num2._number[j] - '0') * (num1._number[i] - '0') + carry;
			val.insert(val.begin(), p % 10 + '0');
			carry = p / 10;
		}
		if(carry)
			val.insert(val.begin(), carry + '0');
		for(int j = i; j < len1 - 1; ++j)
			val.push_back('0');
		product = sumOfPos(product, val);
	}
	return BigInt(product);
}

BigInt operator/(const BigInt& num, const long divisor)
{
	long len = num._number.length();
	std::string result = "";
	int i = 0;
	int tmp = num._number[i] - '0';
	while(tmp < divisor)
		tmp = tmp * 10 + num._number[++i] - '0';
	while(i < len)
	{
		result += (tmp / divisor) + '0';
		tmp = (tmp % divisor) * 10 + num._number[++i] - '0';
	}
	return BigInt(result);
}

BigInt& BigInt::operator=(const BigInt& rhs)
{
	_number = rhs._number;
	removeZeros(_number);
	return *this;
}

bool operator==(const BigInt& num1, const BigInt& num2)
{
	return num1._number == num2._number;
}

BigInt& BigInt::operator++()
{
	BigInt one("1");
	*this = *this + one;
	return *this;
}

BigInt& BigInt::operator--()
{
	BigInt one("1");
	*this = *this - one;
	return *this;
}

BigInt& BigInt::operator+=(const BigInt& rhs)
{
	*this = *this + rhs;
	return *this;
}

BigInt& BigInt::operator-=(const BigInt& rhs)
{
	*this = *this - rhs;
	return *this;
}

BigInt& BigInt::operator*=(const BigInt& rhs)
{
	*this = *this * rhs;
	return *this;
}

BigInt& BigInt::operator/=(const long rhs)
{
	*this = *this / rhs;
	return *this;
}

std::ostream& operator<<(std::ostream& out, const BigInt& obj)
{
	out << obj._number;
	return out;
}

std::istream& operator>>(std::istream& in, const BigInt& obj)
{
	in >> obj._number;
	return in;
}
