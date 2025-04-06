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