# BigNum, a tool for big numbers.

# Overview
BigNum is used when the size of the numbers exceed the maximum size of the primitive C++ types.

# Table of content
- [I. Declare BigNum](#i-declare-bignum)  
- [II. Arithmetic operators](#ii-arithmetic-operators)  
- [III. Comparison operators](#iii-comparison-operators)  
- [IV. Other functionalities](#iv-other-functionalities)
- [V. Edge cases](#v-edge-cases)

## I. Declare BigNum
There are 5 ways to declare BigNum.

- First, empty BigNum.
    ```c++
    BigNum num;
    ```
    An empty BigNum has the value of 0.
    ```c++
    cout << num; // 0
    ```
- Second, use integer types.  
    ```c++
    BigNum num(12);

    int a = 10;
    long b = -30;
    BigNum num_a(a);
    BigNum num_b(b);

    cout << num;   // 12
    cout << num_a; // 10
    cout << num_b; //-30
    ```

- Third, use string.  
    ```c++
    string str_num = "16";
    BigNum num1(str_num);
    BigNum num2("25");
    BigNum num3("-144")

    cout << num1; // 16
    cout << num2; // 25
    cout << num3; //-144
    ```

<a id="4th-way"></a>
- Fourth, the same as the way you declare an array.  

    ```c++
    BigNum num = {1,2,3};

    cout << num; // 123
    ```
    Or
    ```c++
    BigNum num{1,2,3};

    cout << num; // 123
    ```

    If you want to declare negative number.  
    ```c++
    BigNum num1 = {{1,6}, true};
    BigNum num2{{2,5}, true};

    cout << num1; // -16
    cout << num2; // -25
    ```

    You can also declare positive number using the same pattern.  
    ```c++
    BigNum num1 = {{1,4,4}, false};
    BigNum num2{{2,5,6}, false};

    cout << num1; // 144
    cout << num2; // 256
    ```

    Noted how the second value in the declaration is equivalence to the question "is the number have a negative sign?", true means it has a negative sign, false means it isn't.  

- Fifth, use vector  
    Sign declaration is the same as the [4th way](#4th-way).

    ```c++
    vector<int> num_vec1 = {1,6};
    vector<int> num_vec2 = {2,5};

    BigNum num1 = {num_vec1, false};
    BigNum num2({num_vec2, true});

    cout << num1; // 16
    cout << num2; //-25
    ```

## II. Arithmetic operators  
Arithmetic operators work as expected.    
```c++  
BigNum a(10);
BigNum b(5);

cout << a + b << endl; // 15
cout << a - b << endl; // 5
cout << a * b << endl; // 50
cout << a / b << endl; // 2
cout << a % b;         // 0
```

- Note:
    + Arithmetic operators return a BigNum.
    + Those operators will throw an error when operate on a BigNum and a non-BigNum.
    + When divide, if the divisor equal to zero it will throw a invalid_argument error.
    + The divide operator is a integer division, meaning divide and take the integer part.
        ```c++
        BigNum a(10);
        BigNum b(3);

        BigNum quotient = a / b;
        cout << quotient; // 3
        ```
    + For the modulo operator (%), check out this table: 
        |  a  |  b  |  a % b  |    Explain       |
        |-----|-----|---------|------------------|
        |  7  |  3  |    1    |    7 = 3.2 + 1   |
        | -7  |  3  |   -1    | -7 = 3.(-2) - 1  |
        |  7  | -3  |    1    | 7 = -3.(-2) + 1  |
        | -7  | -3  |   -1    | -7 = -3.2  - 1   |

Negate operator.
  ```c++
      BigNum a(10);
      BigNum negate = -a;
      cout << negate; // -10
  ```

## III. Comparison operators  
Comparison operators work as expected. 

```c++
    BigNum a(10);
    BigNum b(5);

    cout << (a <  b) << endl; // 0 (false)
    cout << (a <= b) << endl; // 0 (false)
    cout << (a >  b) << endl; // 1 (true)
    cout << (a >= b) << endl; // 1 (true)
    cout << (a == b) << endl; // 0 (false)
    cout << (a != b);         // 1 (true)
```

- Note:
  - These operators will throw an error when operate on a BigNum and a non-BigNum.  

## IV. Other functionalities

- Absolute value.
  ```c++
  BigNum a(-3);
  BigNum abs = a.abs();
  cout << abs; // 3
  ```
- Exponential
    ```c++
    BigNum base(2);
    BigNum exponent(2);

    BigNum power = BigNum::exp(base, exponent);
    cout << power; // 4
    ```
    Exponent must not be negative or it will throw an invalid_argument error  

## V. Edge cases
- [1. Very large numbers](#1-very-large-numbers)
- [2. Operations involving Zero](#2-operations-involving-zero)
- [3. Negative numbers](#3-negative-numbers)
- [4. Comparison involving Negative and Large numbers](#4-comparison-involving-negative-and-large-numbers)
### 1. Very large numbers  
BigNum is designed to handle numbers far exceeding the limits of primitive C++ types. Here's an example using a large number:
```c++
BigNum large_num1("123456789012345678901234567890");
BigNum large_num2("987654321098765432109876543210");

BigNum sum = large_num1 + large_num2;
cout << sum; // 1111111110111111111011111111100
```
In this example, adding two numbers far larger than typical int or long long limits works as expected.
### 2. Operations involving Zero
- Addition and subtraction:
    ```c++
    BigNum zero(0);
    BigNum num(12345);

    cout << num + zero; // 12345
    cout << num - zero; // 12345
    ```
- Multiplication:
    ```c++
    cout << num * zero; // 0
    ```
- Division: Dividing by zero will throw an invalid_argument exception:
    ```c++
    try {
        BigNum result = num / zero;
    } catch (const invalid_argument& e) {
        cout << e.what(); // "Division by zero is not allowed"
    }
    ```
- Exponential:
    ```c++
    BigNum num(2);
    BigNum zero(0);

    cout << BigNum::exp(zero, num); // 0
    cout << BigNum::exp(num, zero); // 1
    ```
### 3. Negative numbers
Operations with negative numbers follow standard arithmetic rules:
- Addition and subtraction.
    ```c++
    BigNum a(100);
    BigNum b(-50);

    cout << a + b; // 50
    cout << a - b; // 150
    ```
- Multiplication and division.
    ```c++
    BigNum c(10);
    BigNum d(-3);

    cout << c * d; // -30
    cout << c / d; // -3
    ```
- Exponential.
    ```c++
    BigNum num(-2);
    BigNum odd(3);
    BigNum even(4);

    cout << BigNum::exp(num, odd); // -8
    cout << BigNum::exp(num, even);// 16
    ```
### 4. Comparison involving Negative and Large numbers
Comparison operators also work as expected for large and negative values:
```c++
BigNum large_num("1000000000000000000000000");
BigNum small_num("-1000000000000000000000000");

cout << (large_num > small_num);  // 1 (true)
cout << (large_num < BigNum(0));  // 0 (false)
cout << (small_num == BigNum("-1000000000000000000000000"));  // 1 (true)
```
