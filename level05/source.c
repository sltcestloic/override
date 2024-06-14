int main() {
    char s[100];
    unsigned int i;

    i = 0;
    fgets(s, 100, stdin);    
    for (i = 0; i < strlen(s); ++i) {
        if (s[i] > '@' && s[i] <= 'Z')
            s[i] ^= 0x20; //XOR 00100000
    }
    printf(s);
    exit(0);
}