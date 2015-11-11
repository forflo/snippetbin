#include <stdio.h>

struct foo {
    struct {
        double a[4];
    } abc;
    struct {
        char a[33]; 
    } bcd;
};

int main(void){
    printf("Sizeof: %d\n", sizeof(struct foo)); 

    return 0;
}
