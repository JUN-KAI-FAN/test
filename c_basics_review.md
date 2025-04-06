# README

本文件是 C 語言基礎語法的全面複習指南，適合用於學習、面試準備以及快速回顧 C 語言的核心概念。
#由GPT所產生，經過本人整理後上傳

## 文件內容

1. **基本結構**：介紹 C 程式的基本組成部分。
2. **資料型別**：涵蓋基本型別、型別修飾詞與常數。
3. **運算子**：詳細列出算術、邏輯、位元等運算子。
4. **條件語句**：包括 if-else、switch 和三元運算子。
5. **循環語句**：for、while、do-while 迴圈及控制語句。
6. **陣列與字串**：介紹一維與多維陣列及字串操作。
7. **指標**：指標的基本概念與應用。
8. **函數**：函數定義、聲明與函數指針。
9. **結構體與聯合體**：結構體與聯合體的使用方法。
10. **列舉**：列舉型別的定義與使用。
11. **動態記憶體配置**：malloc、calloc、realloc 與 free 的使用。
12. **檔案操作**：檔案的開啟、讀寫與關閉。
13. **預處理器指令**：條件編譯與巨集定義。
14. **標準函式庫**：常用標頭檔與函數。
15. **面試常考題目**：五道經典 C 語言面試題，附解答與輸出解析。

## 使用方式

- **學習**：逐章閱讀，掌握每個主題的核心概念。
- **面試準備**：重點練習面試題，理解其背後的邏輯。
- **快速查閱**：作為 C 語言的參考手冊，快速查找語法與範例。

歡迎對本文件提出改進建議！

# C 語言基礎語法複習

## 1. 基本結構

```c
#include <stdio.h>  // 引入標準輸入輸出函式庫

int main() {        // 程式進入點
    // 程式主體
    printf("Hello, World!\n");  // 輸出函數
    return 0;       // 回傳值，0 表示正常結束
}
```

## 2. 資料型別

### 基本資料型別
- **int**: 整數型別 (e.g., `int a = 10;`)
- **float**: 單精度浮點數 (e.g., `float b = 10.5f;`)
- **double**: 雙精度浮點數 (e.g., `double c = 10.5;`)
- **char**: 字元型別 (e.g., `char d = 'A';`)

### 型別修飾詞
- **short**: 短整數
- **long**: 長整數
- **unsigned**: 無符號
- **signed**: 有符號

### 常數
```c
#define MAX_SIZE 100  // 前置處理器定義常數
const int MIN_SIZE = 10;  // const 常數
```

## 3. 運算子

### 算術運算子
`+`, `-`, `*`, `/`, `%` (模數/餘數)

### 關係運算子
`==`, `!=`, `>`, `<`, `>=`, `<=`

### 邏輯運算子
`&&` (AND), `||` (OR), `!` (NOT)

### 位元運算子
`&` (位元 AND), `|` (位元 OR), `^` (位元 XOR), `~` (位元 NOT), `<<` (左移), `>>` (右移)

### 賦值運算子
`=`, `+=`, `-=`, `*=`, `/=`, `%=`, `<<=`, `>>=`, `&=`, `^=`, `|=`

### 遞增與遞減
`++`, `--`

## 4. 條件語句

### if-else 語句
```c
if (condition) {
    // 如果條件為真執行
} else if (another_condition) {
    // 如果另一條件為真執行
} else {
    // 其他情況執行
}
```

### switch 語句
```c
switch (variable) {
    case value1:
        // 當 variable == value1 時執行
        break;
    case value2:
        // 當 variable == value2 時執行
        break;
    default:
        // 其他情況執行
        break;
}
```

### 三元運算子 (條件運算子)
```c
result = (condition) ? value_if_true : value_if_false;
```

## 5. 循環語句

### for 迴圈
```c
for (初始化; 條件; 遞增/遞減) {
    // 循環體
}
```

### while 迴圈
```c
while (條件) {
    // 循環體
}
```

### do-while 迴圈
```c
do {
    // 循環體
} while (條件);
```

### 控制語句
- **break**: 跳出迴圈
- **continue**: 跳過當前迭代，繼續下一次迭代
- **goto**: 無條件跳轉（盡量避免使用）

## 6. 陣列 (Array)

```c
int numbers[5] = {1, 2, 3, 4, 5};
int matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
```

## 7. 字串

```c
char greeting[] = "Hello";  // 等同於 {'H', 'e', 'l', 'l', 'o', '\0'}
```

## 8. 指標 (Pointer)

```c
int a = 10;
int *ptr = &a;  // ptr 儲存 a 的記憶體位址
printf("%d", *ptr);  // 使用 * 運算子取得 ptr 所指位址的值 (解參照)
```

## 9. 函數

### 函數定義
```c
返回型別 函數名稱(參數型別 參數1, 參數型別 參數2, ...) {
    // 函數體
    return 值;  // 如果有返回值
}
```

### 函數聲明
```c
返回型別 函數名稱(參數型別 參數1, 參數型別 參數2, ...);
```

### Call by Value vs Call by Address (Reference)

#### Call by Value（傳值呼叫）
傳值呼叫時，函數接收的是參數的複本，在函數內部修改參數不會影響原始值。

```c
#include <stdio.h>

void swap_value(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
    printf("在函數內: a = %d, b = %d\n", a, b);
}

int main() {
    int x = 10, y = 20;
    printf("呼叫前: x = %d, y = %d\n", x, y);
    swap_value(x, y);
    printf("呼叫後: x = %d, y = %d\n", x, y);  // 原始值不變
    return 0;
}

// 輸出:
// 呼叫前: x = 10, y = 20
// 在函數內: a = 20, b = 10
// 呼叫後: x = 10, y = 20
```

#### Call by Address（傳址呼叫）
傳址呼叫時，函數接收的是參數的記憶體位址，可以直接修改原始值。

```c
#include <stdio.h>

void swap_address(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    printf("在函數內: a = %d, b = %d\n", *a, *b);
}

int main() {
    int x = 10, y = 20;
    printf("呼叫前: x = %d, y = %d\n", x, y);
    swap_address(&x, &y);
    printf("呼叫後: x = %d, y = %d\n", x, y);  // 值已交換
    return 0;
}

// 輸出:
// 呼叫前: x = 10, y = 20
// 在函數內: a = 20, b = 10
// 呼叫後: x = 20, y = 10
```

### 函數指針
```c
返回型別 (*指針名稱)(參數型別, ...);
```

#### 函數指針範例
```c
#include <stdio.h>

// 定義兩個簡單函數
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int calculate(int (*operation)(int, int), int x, int y) {
    return operation(x, y);  // 透過函數指針呼叫函數
}

int main() {
    // 聲明函數指針
    int (*func_ptr)(int, int);
    
    // 指向 add 函數
    func_ptr = add;
    printf("使用函數指針呼叫 add: %d\n", func_ptr(5, 3));  // 輸出: 8
    
    // 指向 subtract 函數
    func_ptr = subtract;
    printf("使用函數指針呼叫 subtract: %d\n", func_ptr(5, 3));  // 輸出: 2
    
    // 透過 calculate 函數傳遞函數指針
    printf("透過函數指針參數呼叫 add: %d\n", calculate(add, 5, 3));  // 輸出: 8
    printf("透過函數指針參數呼叫 subtract: %d\n", calculate(subtract, 5, 3));  // 輸出: 2
    
    return 0;
}
```

#### 函數指針陣列範例
```c
#include <stdio.h>

int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) { return (b != 0) ? (a / b) : 0; }

int main() {
    // 定義函數指針陣列
    int (*operations[4])(int, int) = {add, subtract, multiply, divide};
    char *op_names[4] = {"加法", "減法", "乘法", "除法"};
    
    int a = 10, b = 5;
    
    // 使用函數指針陣列調用不同函數
    for (int i = 0; i < 4; i++) {
        printf("%s結果: %d\n", op_names[i], operations[i](a, b));
    }
    
    return 0;
}
```

## 10. 結構體與聯合體

### 結構體 (struct)
```c
struct Person {
    char name[50];
    int age;
    float height;
};

struct Person p1 = {"John", 25, 175.5};
```

### 聯合體 (union)
```c
union Data {
    int i;
    float f;
    char str[20];
};

union Data data;
data.i = 10;  // 此時只有 data.i 有效
```

## 11. 列舉 (enum)

```c
enum Days {Sun, Mon, Tue, Wed, Thu, Fri, Sat};
enum Days today = Wed;
```

## 12. 動態記憶體配置

```c
int *p = (int*) malloc(sizeof(int));  // 配置一個 int 大小的記憶體空間
*p = 10;
free(p);  // 釋放記憶體

int *arr = (int*) calloc(10, sizeof(int));  // 配置 10 個 int 大小的記憶體空間，並初始化為 0
free(arr);

arr = (int*) realloc(arr, 20 * sizeof(int));  // 重新配置大小
```

## 13. 檔案操作

```c
FILE *file = fopen("file.txt", "r");  // 開啟檔案，模式可以是 r, w, a, r+, w+, a+ 等
if (file) {
    // 進行檔案操作
    fclose(file);  // 關閉檔案
}
```

## 14. 預處理器指令

- **#include**: 引入標頭檔
- **#define**: 定義巨集
- **#ifdef**, **#ifndef**, **#endif**: 條件編譯
- **#pragma**: 編譯器特定指令

## 15. 常見標準函式庫

- **stdio.h**: 輸入輸出函數
- **stdlib.h**: 通用工具函數
- **string.h**: 字串處理函數
- **math.h**: 數學函數
- **time.h**: 時間相關函數
- **ctype.h**: 字元處理函數

## 重要提醒與最佳實踐

- 始終初始化變數
- 檢查記憶體分配的返回值
- 釋放所有動態分配的記憶體
- 避免記憶體洩漏
- 注意陣列邊界
- 善用註解提高程式可讀性
- 適當處理錯誤
- 避免未定義行為

## 面試常考複習題

### 問題 1: 指標與陣列
```c
#include <stdio.h>
int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int *ptr = arr;
    printf("%d %d %d\n", *ptr, *(ptr + 2), *(arr + 4));
    return 0;
}
```

**猜輸出**:  
```
10 30 50
```

**解答**:  
- `*ptr` 取得 `arr[0]` 的值，即 `10`。
- `*(ptr + 2)` 取得 `arr[2]` 的值，即 `30`。
- `*(arr + 4)` 取得 `arr[4]` 的值，即 `50`。

---

### 問題 2: 字串與指標
```c
#include <stdio.h>
int main() {
    char str[] = "Hello";
    char *p = str;
    p[0] = 'h';
    printf("%s\n", str);
    return 0;
}
```

**猜輸出**:  
```
hello
```

**解答**:  
- `p` 指向字串 `str` 的起始位址。
- 修改 `p[0]` 等同於修改 `str[0]`，將 `'H'` 改為 `'h'`。
- 最後輸出修改後的字串 `hello`。

---

### 問題 3: 遞增運算子
```c
#include <stdio.h>
int main() {
    int a = 5;
    int b = a++ + ++a;
    printf("%d %d\n", a, b);
    return 0;
}
```

**猜輸出**:  
```
7 12
```

**解答**:  
- `a++` 使用 `a` 的值後再遞增，值為 `5`，`a` 變為 `6`。
- `++a` 先遞增後使用，值為 `7`。
- `b = 5 + 7 = 12`，最後 `a = 7`。

---

### 問題 4: 靜態變數
```c
#include <stdio.h>
void func() {
    static int x = 0;
    x++;
    printf("%d ", x);
}
int main() {
    func();
    func();
    func();
    return 0;
}
```

**猜輸出**:  
```
1 2 3
```

**解答**:  
- 靜態變數 `x` 在函數內部只初始化一次，且其值在函數調用之間保持不變。
- 每次調用 `func()`，`x` 的值遞增 1。

---

### 問題 5: 結構體與指標
```c
#include <stdio.h>
struct Point {
    int x, y;
};
int main() {
    struct Point p1 = {10, 20};
    struct Point *ptr = &p1;
    printf("%d %d\n", ptr->x, ptr->y);
    return 0;
}
```

**猜輸出**:  
```
10 20
```

**解答**:  
- `ptr` 是指向結構體 `p1` 的指標。
- 使用 `ptr->x` 和 `ptr->y` 訪問結構體成員，分別輸出 `10` 和 `20`。

---

這些題目涵蓋了指標、陣列、字串、運算子、靜態變數與結構體等 C 語言的核心概念，適合用於面試準備與基礎複習。

## 16. 實用程式範例

### 字串反轉
```c
#include <stdio.h>
#include <string.h>

void reverse_string(char* str) {
    int length = strlen(str);
    int i, j;
    char temp;
    
    for (i = 0, j = length - 1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

int main() {
    char str[100];
    
    printf("請輸入一個字串: ");
    gets(str);  // 注意: 實際應用中應使用 fgets 以避免緩衝區溢出
    
    printf("原始字串: %s\n", str);
    reverse_string(str);
    printf("反轉後字串: %s\n", str);
    
    return 0;
}
```

### 檢查回文
回文是指正著讀和反著讀都一樣的字詞或句子，例如「竹塹」、「上海自來水來自海上」。

#### 方法一：使用迴圈比較
```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>  // 用於 tolower 函數

// 檢查字串是否為回文
int is_palindrome(char* str) {
    int left = 0;
    int right = strlen(str) - 1;
    
    while (left < right) {
        // 忽略非字母數字字符
        while (left < right && !isalnum(str[left])) 
            left++;
        while (left < right && !isalnum(str[right])) 
            right--;
            
        // 忽略大小寫差異
        if (tolower(str[left]) != tolower(str[right]))
            return 0;  // 不是回文
            
        left++;
        right--;
    }
    
    return 1;  // 是回文
}

int main() {
    char str[100];
    
    printf("請輸入一個字串: ");
    fgets(str, sizeof(str), stdin);
    
    // 移除換行符
    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';
    
    if (is_palindrome(str))
        printf("\"%s\" 是回文\n", str);
    else
        printf("\"%s\" 不是回文\n", str);
    
    return 0;
}
```

#### 方法二：反轉比較法
```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// 將字串轉為純字母數字，並轉換為小寫
char* prepare_string(const char* input) {
    int i, j = 0;
    int len = strlen(input);
    char* result = (char*)malloc(len + 1);
    
    for (i = 0; i < len; i++) {
        if (isalnum(input[i])) {
            result[j++] = tolower(input[i]);
        }
    }
    result[j] = '\0';
    return result;
}

// 反轉字串
void reverse_string(char* str) {
    int length = strlen(str);
    int i, j;
    char temp;
    
    for (i = 0, j = length - 1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

// 檢查是否為回文
int is_palindrome(const char* str) {
    char* processed = prepare_string(str);
    int len = strlen(processed);
    
    if (len <= 1) {
        free(processed);
        return 1;  // 空字串或單個字符視為回文
    }
    
    char* reversed = (char*)malloc(len + 1);
    strcpy(reversed, processed);
    reverse_string(reversed);
    
    int result = (strcmp(processed, reversed) == 0);
    
    free(processed);
    free(reversed);
    
    return result;
}

int main() {
    char str[100];
    
    printf("請輸入一個字串: ");
    fgets(str, sizeof(str), stdin);
    
    // 移除換行符
    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';
    
    if (is_palindrome(str))
        printf("\"%s\" 是回文\n", str);
    else
        printf("\"%s\" 不是回文\n", str);
    
    return 0;
}
```
