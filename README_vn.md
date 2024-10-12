# BigNum, công cụ để xử lý những con số lớn.  

# Tổng quan
BigNum được sử dụng khi kích thước của số đang làm việc lớn hơn kích thước tối đa của các kiểu dữ liệu có sẵn của C++.

# Mục lục
- [I. Khai báo BigNum](#i-khai-báo-bignum)  
- [II. Toán tử số học](#ii-các-toán-tử-số-học)  
- [III. Toán tử so sánh](#iii-các-toán-tử-so-sánh)  
- [IV. Các tính năng khác](#iv-các-tính-năng-khác)
- [V. Trường hợp đặc biệt](#v-trường-hợp-đặc-biệt)
## I. Khai báo BigNum

BigNum có 5 cách khai báo.

- Cách 1, khai báo BigNum rỗng.
	```c++
	BigNum num;
	```
	Mặc định nếu khai báo không có giá trị thì BigNum có giá trị là 0.
	```c++
	cout << num; // 0
	```
- Cách 2, sử dụng các kiểu số nguyên.
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
- Cách 3, sử dụng string.
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
- Cách 4, giống với cách khai báo mảng.

  ```c++
  BigNum num = {1,2,3};

  cout << num; // 123
  ```

  Hoặc

  ```c++
  BigNum num{1,2,3};

  cout << num; // 123
  ```

  Nếu muốn khai báo số âm.

  ```c++
  BigNum num1 = {{1,6}, true};
  BigNum num2{{2,5}, true};

  cout << num1; // -16
  cout << num2; // -25
  ```

  Cũng có thể khai báo số dương với cú pháp trên.

  ```c++
  BigNum num1 = {{1,4,4}, false};
  BigNum num2{{2,5,6}, false};

  cout << num1; // 144
  cout << num2; // 256
  ```

  Vậy giá trị của phần tử số 2 chính là câu hỏi "số này có dấu - đằng trước hay không?", true là có dấu âm, false tức là không có.

- Cách 5, sử dụng vector  
   Cách khai báo dấu của BigNum giống với [cách 4](#4th-way)

  ```c++
  vector<int> num_vec1 = {1,6};
  vector<int> num_vec2 = {2,5};

  BigNum num1 = {num_vec1, false};
  BigNum num2({num_vec2, true});

  cout << num1; // 16
  cout << num2; //-25
  ```

## II. Các toán tử số học

Các phép +, -, \*, / hoạt động như bình thường

```c++
    BigNum a(10);
    BigNum b(5);

    cout << a + b << endl; // 15
    cout << a - b << endl; // 5
    cout << a * b << endl; // 50
    cout << a / b << endl; // 2
    cout << a % b;         // 0
```

- Lưu ý:

  - Các toán tử trả về số ở dạng BigNum
  - Các toán tử trên sẽ báo lỗi nếu hai số khi thực hiện phép tính không phải là BigNum
  - Đối với phép chia thì nếu mẫu số bằng 0 thì sẽ bị lỗi invalid_argument
  - Phép chia nếu có phần thập phân thì là phép chia lấy số nguyên

    ```c++
    BigNum a(10);
    BigNum b(3);

    BigNum quotient = a / b;
    cout << quotient; // 3
    ```

  - Đối với phép chia lấy phần dư (modulo: %): Tham khảo bảng sau
    | a | b | a % b | Giải Thích |
    |-----|-----|---------|------------------|
    | 7 | 3 | 1 | 7 = 3.2 + 1 |
    | -7 | 3 | -1 | -7 = 3.(-2) - 1 |
    | 7 | -3 | 1 | 7 = -3.(-2) + 1 |
    | -7 | -3 | -1 | -7 = -3.2 - 1 |

Phép phủ định

```c++
    BigNum a(10);
    BigNum negate = -a;
    cout << negate; // -10
```

## III. Các toán tử so sánh

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

- Lưu ý:
  - Các toán tử trên sẽ báo lỗi nếu hai số khi thực hiện so sánh không phải là BigNum

## IV. Các tính năng khác

- Giá trị tuyệt đối
  ```c++
  BigNum a(-3);
  BigNum abs = a.abs();
  cout << abs; // 3
  ```
- Lũy thừa

  - Lũy thừa với một BigNum có sẵn
    ```c++
    BigNum a(2);
    BigNum power = a.pow(2);
    cout << power; // 4;
    ```
  - Luỹ thừa chung

    ```c++
    BigNum base(2);
    BigNum exponent(2);

    BigNum power = BigNum::exp(base, exponent);
    cout << power; // 4
    ```
## V. Trường hợp đặc biệt

- [1. Số rất lớn](#1-số-rất-lớn)
- [2. Toán tử liên quan đến số Không](#2-toán-tử-liên-quan-đến-số-không)
- [3. Số âm](#3-số-âm)
- [4. So sánh có liên quan đến số âm và số rất lớn](#4-so-sánh-có-liên-quan-đến-số-âm-và-số-rất-lớn)
### 1. Số rất lớn
BigNum được thiết kể để xử lý những số vượt quá giới hạn những kiểu dữ liệu có sẵn của C++, dưới đây là một ví dụ: 
```c++
BigNum large_num1("123456789012345678901234567890");
BigNum large_num2("987654321098765432109876543210");

BigNum sum = large_num1 + large_num2;
cout << sum; // 1111111110111111111011111111100
```

### 2. Toán tử liên quan đến số Không
- Cộng và trừ:
    ```c++
    BigNum zero(0);
    BigNum num(12345);

    cout << num + zero; // 12345
    cout << num - zero; // 12345
    ```
- Nhân:
    ```c++
    cout << num * zero; // 0
    ```
- Chia: Chia cho 0 sẽ báo lỗi invalid_argument.
    ```c++
    try {
        BigNum result = num / zero;
    } catch (const invalid_argument& e) {
        cout << e.what(); // "Division by zero is not allowed"
    }
    ```
- Lũy thừa:
    ```c++
    BigNum num(2);
    BigNum zero(0);

    cout << BigNum::exp(zero, num); // 0
    cout << BigNum::exp(num, zero); // 1
    ```
### 3. Số âm
Các toán tử liên quan đến số âm vẫn theo đúng như quy luật đại số:
- Cộng và trừ.
    ```c++
    BigNum a(100);
    BigNum b(-50);

    cout << a + b; // 50
    cout << a - b; // 150
    ```
- Nhân và chia.
    ```c++
    BigNum c(10);
    BigNum d(-3);

    cout << c * d; // -30
    cout << c / d; // -3
    ```
- Lũy thừa.
    ```c++
    BigNum num(-2);
    BigNum odd(3);
    BigNum even(4);

    cout << BigNum::exp(num, odd); // -8
    cout << BigNum::exp(num, even);// 16
    ```
### 4. So sánh có liên quan đến số âm và số rất lớn

```c++
BigNum large_num("1000000000000000000000000");
BigNum small_num("-1000000000000000000000000");

cout << (large_num > small_num);  // 1 (true)
cout << (large_num < BigNum(0));  // 0 (false)
cout << (small_num == BigNum("-1000000000000000000000000"));  // 1 (true)
```