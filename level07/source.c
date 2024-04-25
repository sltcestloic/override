#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int clear_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    return c;
}

int get_unum() {
    int result = 0;
    fflush(stdout);
    scanf("%u", &result);
    clear_stdin();
    return result;
}

int store_number(int *data) {
    printf(" Number: ");
    int num = get_unum();
    printf(" Index: ");
    unsigned int index = get_unum();
    if (index != index / 3 && (num & -0x1000000) != -0x49000000) {
        data[index] = num;
        return 0;
    } else {
        puts(" *** ERROR! ***");
        puts("   This index is reserved for wil!");
        puts(" *** ERROR! ***");
        return 1;
    }
}

int read_number(int *data) {
    printf(" Index: ");
    int index = get_unum();
    printf(" Number at data[%u] is %u\n", index, data[index]);
    return 0;
}

int main(int argc, char **argv) {
    char str[100] = {0};
    char *commands[] = {"store", "read", "quit"};
    printf("----------------------------------------------------\n"
           "  Welcome to wil's crappy number storage service!   \n"
           "----------------------------------------------------\n"
           " Commands:                                          \n"
           "    store - store a number into the data storage    \n"
           "    read  - read a number from the data storage     \n"
           "    quit  - exit the program                        \n"
           "----------------------------------------------------\n"
           "   wil has reserved some storage :>                 \n"
           "----------------------------------------------------\n");

    while (1) {
        printf("Input command: ");
        fgets(str, sizeof(str), stdin);
        str[strcspn(str, "\n")] = 0;

        int command_found = 0;
        for (int i = 0; i < sizeof(commands) / sizeof(commands[0]); i++) {
            if (strcmp(str, commands[i]) == 0) {
                command_found = 1;
                break;
            }
        }

        if (!command_found) {
            printf(" Failed to do %s command\n", str);
            continue;
        }

        if (strcmp(str, "store") == 0) {
            store_number((int *)argv);
        } else if (strcmp(str, "read") == 0) {
            read_number((int *)argv);
        } else if (strcmp(str, "quit") == 0) {
            break;
        }
    }

    return 0;
}