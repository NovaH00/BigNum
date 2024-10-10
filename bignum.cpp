#include <algorithm>
#include <iostream>
#include <typeinfo>
#include <vector>
using namespace std;

class BigNum {
private:
    vector<int> digits; // Store digits in reverse order
    bool sign;          // 0 for positive, 1 for negative

    template <typename T>
    void type_check() const {
        static_assert(std::is_same<T, BigNum>::value, "Operator cannot perform on non-BigNum types.");
    }

public:
    BigNum() : digits{0}, sign(0) {}; // Default constructor
    BigNum(const long long &integer) {
        int copy;
        if (integer < 0) {
            sign = 1;
            copy = -integer;
        } else {
            sign = 0;
            copy = integer;
        }
        while (copy > 0) {
            digits.emplace_back(copy % 10);
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
            if (e == '-')
                continue; // Skip sign character
            digits.emplace_back(int(e - '0'));
        }
        if (digits.size() == 1 && digits[0] == 0)
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

    vector<int> get_digits(){
        return this->digits;
    }
    BigNum abs() const {
        vector<int> reverse_digit = this->digits;
        reverse(reverse_digit.begin(), reverse_digit.end());
        BigNum result{reverse_digit, this->sign};
        if ((result < BigNum(0)))
            return -result;
        else
            return result;
    }

    BigNum pow(long long power) const {
        if(power < 0)
            throw invalid_argument("Cannot raise to negative power");
        BigNum result(1);
        vector<int> reverse_digit = this->digits;
        reverse(reverse_digit.begin(), reverse_digit.end());
        BigNum this_bignum{reverse_digit, this->sign};

        while (power > 0) {
            result = result * this_bignum;
            power--;
        }

        return result;
    }

    static BigNum exp(const BigNum &base, const BigNum &exponent){
        BigNum result(1);
        BigNum base_bignum = base;
        BigNum exponent_bignum = exponent;
        while(exponent_bignum >= BigNum(1)){
            result = result*base_bignum;
            exponent_bignum = exponent_bignum - BigNum(1);
        }
        return result;
    }

    // Overload the + operator
    template <typename T>
    BigNum operator+(const T &other) const {
        type_check<T>();
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

        if (result.digits.size() == 1 && result.digits[0] == 0)
            result.sign = 0;
        return result;
    }


    // Overload the - operator
    template <typename T>
    BigNum operator-(const T &other) const {
        type_check<T>();
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

        if (result.digits.size() == 1 && result.digits[0] == 0)
            result.sign = 0;
        return result;
    }


    // Overload the * operator
    template <typename T>
    BigNum operator*(const T &other) const {
        type_check<T>();
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
        if (result.digits.size() == 1 && result.digits[0] == 0)
            result.sign = 0;
        return result;
    }

    template <typename T>
    BigNum operator*=(const T &other) const {
        type_check<T>();
        vector<int> reverse_digit = this->digits;
        reverse(reverse_digit.begin(), reverse_digit.end());
        BigNum this_bignum{reverse_digit, this->sign};

        return this_bignum * other;
    }

    // Overload the / operator
    template <typename T>
    BigNum operator/(const T &other) const {
        type_check<T>();
        if (other == BigNum{0}) {
            throw invalid_argument("Division by zero.");
        }

        BigNum result;
        BigNum current;
        current.digits.clear();
        size_t size = this->digits.size();

        // Get the absolute values of the current and other operands
        BigNum abs_this = this->abs();
        BigNum abs_other = other.abs();

        // Iterate through the digits of the dividend
        for (size_t i = size; i-- > 0;) {
            // Shift the current number left (i.e., append the next digit)
            current.digits.insert(current.digits.begin(), abs_this.digits[i]);

            // Count how many times `abs_other` can be subtracted from `current`
            int count = 0;

            // Check to avoid underflow (if current becomes less than abs_other)
            while (current >= abs_other) {
                current = current - abs_other;
                count++;
            }

            // Insert the count of how many times we could subtract at the start of result
            result.digits.insert(result.digits.begin(), count);
        }

        // Remove leading zeros from the result
        while (result.digits.size() > 1 && result.digits.back() == 0) {
            result.digits.pop_back();
        }

        // Set the sign of the result
        result.sign = this->sign ^ other.sign; // Result is negative if signs are different
        if (result.digits.size() == 1 && result.digits[0] == 0) {
            result.sign = 0; // If the result is zero, ensure the sign is not negative
        }

        return result;
    }



    template <typename T>
    BigNum operator%(const T &other) const {
        type_check<T>();
        vector<int> reverse_digit = this->digits;
        reverse(reverse_digit.begin(), reverse_digit.end());
        BigNum this_bignum{reverse_digit, this->sign};

        BigNum quotient = this_bignum / other;
        BigNum remainder = this_bignum - quotient * other;
        return remainder;
    }


    // Overload comparison operator for less than
    template <typename T>
    bool operator<(const T &other) const {
        type_check<T>();
        
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
    template <typename T>
    bool operator>=(const T &other) const {
        type_check<T>();
        return !(*this < other);
    }
    template <typename T>
    bool operator>(const T &other) const {
        type_check<T>();
        if (*this < other)
            return false;
        if (*this == other)
            return false;

        return true;
    }
    template <typename T>
    bool operator<=(const T &other) const {
        type_check<T>();
        if (*this > other)
            return false;

        return true;
    }

    // Overload comparison operator for equality
    template <typename T>
    bool operator==(const T &other) const {
        type_check<T>();
        return this->digits == other.digits && this->sign == other.sign;
    }

    template <typename T>
    bool operator!=(const T &other) const {
        type_check<T>();
        return !(*this == other);
    }

    // Negation operator
    BigNum operator-() const {
        BigNum result = *this;
        result.sign = !this->sign; // Flip the sign
        if (result.digits.size() == 1 && result.digits[0] == 0)
            result.sign = 0;
        return result;
    }

    friend ostream &operator<<(ostream &os, const BigNum &big_num) {
        if (big_num.sign)
            os << '-'; // Output sign
        for (auto it = big_num.digits.rbegin(); it != big_num.digits.rend(); ++it) {
            os << *it;
        }
        return os;
    }
};
