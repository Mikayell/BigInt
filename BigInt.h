class BigInt
{
public:
	BigInt() = default;
	BigInt(std::string num);
	BigInt(const BigInt& obj);
		
	void setNum(std::string num);
	std::string getNum() const;
	std::string mod() const;
	
	BigInt& operator=(const BigInt& rhs);
	BigInt& operator++();
	BigInt& operator--();
	BigInt& operator+=(const BigInt& rhs);
	BigInt& operator-=(const BigInt& rhs);
	BigInt& operator*=(const BigInt& rhs);
	BigInt& operator/=(const long rhs);
	
	friend BigInt operator+(const BigInt& num1, const BigInt& num2);
	friend BigInt operator-(const BigInt& num1, const BigInt& num2);
	friend BigInt operator*(const BigInt& num1, const BigInt& num2);
	friend BigInt operator/(const BigInt& num1, long divisor);
	friend bool operator==(const BigInt& num1, const BigInt& num2);
	friend std::ostream& operator<<(std::ostream& out, const BigInt& obj);
	friend std::istream& operator>>(std::istream& in, const BigInt& obj);

	bool operator>(const BigInt& obj); // check for reference
	bool operator<(const BigInt&);//
	bool operator>=(const BigInt&);
	bool operator<=(const BigInt&);
		
	
	
private:
	std::string _number;

private:
	friend void removeZeros(std::string& num);
	friend bool isSmaller(const std::string num1, const std::string num2);
        friend std::string sumOfPos(std::string num1, std::string num2);
        friend std::string diffOfPos(std::string num1, std::string num2);
};
