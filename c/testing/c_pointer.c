#include <stdio.h>

int main(){
    struct foobar { int len; char *str; };
    struct foobar moo[3] = { {2, "foobar"}, {4, "fumu"}, {6, "arche"} };
    struct foobar *ptr = moo;
    printf("%c\n", *ptr++->str++);
    printf("%c\n", *0[moo].str);
    printf("%s\n", ptr->str);
}
