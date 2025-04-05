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

### 函數指針
```c
返回型別 (*指針名稱)(參數型別, ...);
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
```

## 重要提醒與最佳實踐

- 始終初始化變數
- 檢查記憶體分配的返回值
- 釋放所有動態分配的記憶體
- 避免記憶體洩漏
- 注意陣列邊界
- 善用註解提高程式可讀性
- 適當處理錯誤
- 避免未定義行為
