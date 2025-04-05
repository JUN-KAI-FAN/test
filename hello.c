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

int total = 0; // 全域變數，儲存總和
int aabb = 0; // 全域變數，儲存總和

// 列印鏈結串列
void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;
    head = insertAtHead(head, 3);
    head = insertAtHead(head, 7);
    head = insertAtHead(head, 12);
    printList(head);

    // 釋放記憶體
    struct Node* current = head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
    return 0;
}