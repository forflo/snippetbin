#include <stdio.h>

int main(int argc, char **argv){
    printf("%0+10.*2$d\n", 2, 5);
    printf("%0+10.*2$f\n", 0.32, 3);
    printf("%0+10.*2$hhd\n", 127, 5);
    printf("%0+10.*2$hhd\n", 129, 5);
    printf("%0+10.*2$hhu\n", 255, 5);
    printf("%0+20.*2$li\n", 1230010023001203L, 30);
    printf("%1$d %1$05d\n", 42);
    return 0;
}
