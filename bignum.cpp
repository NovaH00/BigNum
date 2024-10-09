#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class BigNum {
private:
    vector<int> digits; // Store digits in reverse order
    bool sign;         // 0 for positive, 1 for negative
public:
    BigNum() : digits{0}, sign(0) {}; // Default constructor
    BigNum(const long long &integer){
        int copy;
        if(integer < 0){
            sign = 1;
            copy = -integer;
        }   
        else{
            sign = 0;
            copy = integer;
        }
        while(copy > 0){
            digits.emplace_back(copy%10);
            copy /= 10;
        }
    }
    // Constructor to initialize BigNum with an initializer list and sign
    BigNum(initializer_list<int> init, bool sign = 0) : digits(init), sign(sign) {
        for (int digit : init) {
            if (digit < 0 || digit > 9) {
                throw invalid_argument("Digit must be between 0 and 9");
            }
        }

        // Reverse the input list to store digits from least to most significant
        reverse(digits.begin(), digits.end());

        // Remove leading zeros
        while (digits.size() > 1 && digits.back() == 0) {
            digits.pop_back();
        }
    }

    BigNum(const vector<int> &num_vec, bool sign = 0) : digits(num_vec), sign(sign) {
        for (int digit : num_vec) {
            if (digit < 0 || digit > 9) {
                throw invalid_argument("Digit must be between 0 and 9");
            }
        }

        // Reverse the input list to store digits from least to most significant
        reverse(digits.begin(), digits.end());

        // Remove leading zeros
        while (digits.size() > 1 && digits.back() == 0) {
            digits.pop_back();
        }
    }

    BigNum(const string &num_str) {
        sign = (num_str[0] == '-') ? 1 : 0;
        for (char e : num_str) {
            if (e == '-') continue; // Skip sign character
            digits.emplace_back(int(e - '0'));
        }
        if(digits.size() == 1 && digits[0] == 0)
            sign = 0;

        // Reverse the input list to store digits from least to most significant
        reverse(digits.begin(), digits.end());

        for (int digit : digits) {
            if (digit < 0 || digit > 9) {
                throw invalid_argument("Digit must be between 0 and 9");
            }
        }

        // Remove leading zeros
        while (digits.size() > 1 && digits.back() == 0) {
            digits.pop_back();
        }
    }


    // Overload the + operator
    BigNum operator+(const BigNum &other) const {
        if (this->sign != other.sign) {
            // If signs are different, use subtraction
            return (*this - (-other));
        }

        BigNum result;
        const vector<int> &lhs = this->digits;
        const vector<int> &rhs = other.digits;

        int carry = 0;
        size_t maxLength = max(lhs.size(), rhs.size());
        result.digits.resize(maxLength);

        for (size_t i = 0; i < maxLength; ++i) {
            int lhsDigit = (i < lhs.size()) ? lhs[i] : 0;
            int rhsDigit = (i < rhs.size()) ? rhs[i] : 0;
            int sum = lhsDigit + rhsDigit + carry;
            result.digits[i] = sum % 10; // Store current digit
            carry = sum / 10;            // Calculate carry
        }

        if (carry) {
            result.digits.push_back(carry); // Handle remaining carry
        }

        result.sign = this->sign; // Result has the same sign

        if(result.digits.size() == 1 && result.digits[0] == 0)
            result.sign = 0;
        return result;
    }

    // Overload the - operator
    BigNum operator-(const BigNum &other) const {
        if (this->sign != other.sign) {
            // If signs are different, use addition
            return (*this + (-other));
        }

        // Handle subtraction
        if (*this < other) {
            // Result would be negative
            return -(other - *this);
        }

        BigNum result;
        const vector<int> &lhs = this->digits;
        const vector<int> &rhs = other.digits;

        result.digits.resize(lhs.size());
        int borrow = 0;

        for (size_t i = 0; i < lhs.size(); ++i) {
            int lhsDigit = lhs[i];
            int rhsDigit = (i < rhs.size()) ? rhs[i] : 0;

            if (lhsDigit < rhsDigit + borrow) {
                lhsDigit += 10;
                result.digits[i] = lhsDigit - rhsDigit - borrow;
                borrow = 1;
            } else {
                result.digits[i] = lhsDigit - rhsDigit - borrow;
                borrow = 0;
            }
        }

        // Remove leading zeros
        while (result.digits.size() > 1 && result.digits.back() == 0) {
            result.digits.pop_back();
        }

        result.sign = this->sign; // Result has the same sign

        if(result.digits.size() == 1 && result.digits[0] == 0)
            result.sign = 0;
        return result;
    }

    // Overload the * operator
    BigNum operator*(const BigNum &other) const {
        BigNum result;
        const vector<int> &lhs = this->digits;
        const vector<int> &rhs = other.digits;

        result.digits.resize(lhs.size() + rhs.size(), 0); // Prepare for the maximum possible size

        for (size_t i = 0; i < lhs.size(); ++i) {
            for (size_t j = 0; j < rhs.size(); ++j) {
                int product = lhs[i] * rhs[j];
                result.digits[i + j] += product;

                // Handle carry
                if (result.digits[i + j] >= 10) {
                    result.digits[i + j + 1] += result.digits[i + j] / 10;
                    result.digits[i + j] %= 10;
                }
            }
        }

        // Remove leading zeros
        while (result.digits.size() > 1 && result.digits.back() == 0) {
            result.digits.pop_back();
        }

        result.sign = this->sign ^ other.sign; // Result is negative if signs are different
        if(result.digits.size() == 1 && result.digits[0] == 0)
            result.sign = 0;
        return result;
    }

    // Overload the / operator
    BigNum operator/(const BigNum &other) const {
        if (other == BigNum{0}) {
            throw invalid_argument("Division by zero.");
        }

        BigNum result;
        BigNum current;
        current.digits.clear();
        size_t size = this->digits.size();

        for (size_t i = size; i-- > 0;) {
            current.digits.insert(current.digits.begin(), this->digits[i]);
            int count = 0;

            // Subtract `other` from `current` until it is no longer possible
            while (current >= other) {
                current = current - other;
                count++;
            }

            result.digits.insert(result.digits.begin(), count); // Build the result digit by digit
        }

        // Remove leading zeros
        while (result.digits.size() > 1 && result.digits.back() == 0) {
            result.digits.pop_back();
        }

        result.sign = this->sign ^ other.sign; // Result is negative if signs are different
        if(result.digits.size() == 1 && result.digits[0] == 0)
            result.sign = 0;
        return result;
    }

    // Overload comparison operator for less than
    bool operator<(const BigNum &other) const {
        if (this->sign != other.sign) {
            return this->sign > other.sign; // Negative is less than positive
        }
        if (this->digits.size() != other.digits.size()) {
            return this->digits.size() < other.digits.size();
        }
        for (size_t i = this->digits.size(); i-- > 0;) {
            if (this->digits[i] != other.digits[i]) {
                return this->digits[i] < other.digits[i];
            }
        }
        return false;
    }

    // Overload comparison operator for greater than or equal
    bool operator>=(const BigNum &other) const {
        return !(*this < other);
    }
    bool operator>(const BigNum &other) const {
        if(*this < other)
            return false;
        if(*this == other)
            return false;

        return true;
    }
    bool operator<=(const BigNum &other) const {
        if(*this > other)
            return false;
        
        return true;
    }

    // Overload comparison operator for equality
    bool operator==(const BigNum &other) const {
        return this->digits == other.digits && this->sign == other.sign;
    }

    bool operator!=(const BigNum &other) const {
        return !(*this == other);
    }

    // Negation operator
    BigNum operator-() const {
        BigNum result = *this;
        result.sign = !this->sign; // Flip the sign
        if(result.digits.size() == 1 && result.digits[0] == 0)
            result.sign = 0;
        return result;
    }

    friend ostream &operator<<(ostream &os, const BigNum &big_num) {
        if (big_num.sign) os << '-'; // Output sign
        for (auto it = big_num.digits.rbegin(); it != big_num.digits.rend(); ++it) {
            os << *it;
        }
        return os;
    }
};
