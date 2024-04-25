int authenticate(char *login, int serial) {
    login[strcspn(login, "\n")] = '\0';

    int length = strnlen(login, 32);

    if (length <= 5)
        return 1;

    if (ptrace(PTRACE_TRACEME, 0, 1, 0) == -1) {
        puts("\x1B[32m.---------------------------.");
        puts("\x1B[31m| !! TAMPERING DETECTED !!  |");
        puts("\x1B[32m'---------------------------'");
        return 1;
    } else {
        int v4 = (login[3] ^ 0x1337) + 6221293;
        for (int i = 0; i < length; ++i) {
            if (login[i] <= 31)
                return 1;
            v4 += (v4 ^ (unsigned int)login[i]) % 0x539;
        }
        return serial != v4;
    }
}

int main(int argc, const char **argv, const char **envp) {
    int serial;
    char login[28];

    puts("***********************************");
    puts("*\t\tlevel06\t\t  *");
    puts("***********************************");
    printf("-> Enter Login: ");
    fgets(login, 32, stdin);
    puts("***********************************");
    puts("***** NEW ACCOUNT DETECTED ********");
    puts("***********************************");
    printf("-> Enter Serial: ");
    scanf("%d", &serial);

    if (authenticate(login, serial))
        return 1;

    puts("Authenticated!");
    system("/bin/sh");
    return 0;
}