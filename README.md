# BigNum, công cụ để xử lý những con số lớn.

# Tổng quan  
BigNum được sử dụng khi kích thước của số đang làm việc lớn hơn kích thước tối đa của các kiểu dữ liệu có sẵn của C++  

# Mục lục
- [Khai báo BigNum](#1-khai-báo-bignum)
- [Toán tử số học](#2-các-toán-tử-số-học)
- [Toán tử so sánh](#3-các-toán-tử-so-sánh)

# Những tính năng

## 1. Khai báo BigNum 
BigNum có 4 cách khai báo  
+ Cách 1, khai báo BigNum rỗng
    ```c++
    BigNum num;
    ```
    Mặc định nếu khai báo không có giá trị thì BigNum có giá trị là 0  
    ```c++
    cout << num; // 0
    ```
+ Cách 2, sử dụng các kiểu số nguyên  
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
+ Cách 3, sử dụng string  
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
+ Cách 4, giống với cách khai báo mảng  
    ```c++
    BigNum num = {1,2,3};

    cout << num; // 123
    ```
    Hoặc
    ```c++
    BigNum num{1,2,3};

    cout << num; // 123
    ```
    Nếu muốn khai báo số âm  
    ```c++
    BigNum num1 = {{1,6}, {1}};
    BigNum num2{{2,5}, {1}};

    cout << num1; // -16
    cout << num2; // -25
    ```
    Cũng có thể khai báo số dương với cú pháp trên  
    ```c++
    BigNum num1 = {{1,4,4}, {0}};
    BigNum num2{{2,5,6}, {0}};

    cout << num1; // 144
    cout << num2; // 256
    ```    
    Vậy giá trị của phần tử số 2 chính là dấu của BigNum, 0 là dấu dương, 1 là dấu âm  
+ Cách 5, sử dụng vector  
    Cách khai báo dấu của BigNum giống với [cách 4](#4th-way) 
    ```c++
    vector<int> num_vec1 = {1,6};
    vector<int> num_vec2 = {2,5};

    BigNum num1 = {num_vec1, {0}};
    BigNum num2({num_vec2, {1}});

    cout << num1; // 16
    cout << num2; //-25
    ```

## 2. Các toán tử số học
Các phép +, -, *, / hoạt động như bình thường
```c++
    BigNum a(10);
    BigNum b(5);

    cout << a + b << endl; // 15
    cout << a - b << endl; // 5
    cout << a * b << endl; // 50
    cout << a / b << endl; // 2
```
- Lưu ý, đối với phép chia thì nếu mẫu số bằng 0 thì sẽ bị lỗi invalid_argument   

Phép phủ định
```c++
    BigNum a(10);

    cout << -a; // -10
```
## 3. Các toán tử so sánh
Các toán tử so sánh hoạt động như bình thường  
```c++
    BigNum a(10);
    BigNum b(5);

    cout << (a <  b) << endl; // 0
    cout << (a <= b) << endl; // 0
    cout << (a >  b) << endl; // 1
    cout << (a >= b) << endl; // 1
    cout << (a == b) << endl; // 0
    cout << (a != b);         // 1
```