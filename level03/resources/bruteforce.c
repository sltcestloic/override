#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
int main(int ac, char **av) {
    for (int a1 = 0; a1 < 100; a1++) {
        char v4[20];
        size_t v3;
        strcpy(v4, "Q}|u`sfg~sf{}|a3");
          v3 = strlen(v4);
          for (int i = 0; i < v3; ++i )
                v4[i] ^= a1;
        printf("[%d] %s\n", a1, v4);
    }
}