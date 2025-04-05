#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// 插入新節點到鏈結串列開頭
struct Node* insertAtHead(struct Node* head, int value) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = head;
    return newNode;
}

// 列印鏈結串列
void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// 陣列反轉函數
void reverseArray(int arr[], int size) {
    int start = 0;
    int end = size - 1;
    while (start < end) {
        // 交換元素
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        
        // 移動指標
        start++;
        end--;
    }
}

// 印出陣列內容
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    // 原有的鏈結串列部分
    struct Node* head = NULL;
    head = insertAtHead(head, 3);
    head = insertAtHead(head, 7);
    head = insertAtHead(head, 12);
    printList(head);
    
    // 陣列反轉範例
    printf("\n陣列反轉範例：\n");
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(array) / sizeof(array[0]);
    
    printf("原始陣列: ");
    printArray(array, size);
    
    reverseArray(array, size);
    
    printf("反轉後陣列: ");
    printArray(array, size);
    
    // 釋放鏈結串列記憶體
    struct Node* current = head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
    return 0;
}