int main(int ac, char **av) {
    char *login = av[1];
    int length = strnlen(login, 32);
    int v4 = (login[3] ^ 0x1337) + 6221293;
    for (int i = 0; i < length; ++i) {
            if (login[i] <= 31)
                return 1;
            v4 += (v4 ^ (unsigned int)login[i]) % 0x539;
        }
    printf("Serial pour %s: %d\n", login, v4);
}