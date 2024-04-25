int32_t verify_user_name()
{
    int32_t __saved_esi;
    bool c = &__saved_esi < 0x10;
    bool z = &__saved_esi == 0x10;
    puts("verifying username....\n");
    int32_t ecx = 7;
    char* esi = &a_user_name;
    void* const edi = "dat_wil";
    while (ecx != 0)
    {
        char temp1_1 = *esi;
        char temp2_1 = *edi;
        c = temp1_1 < temp2_1;
        z = temp1_1 == temp2_1;
        esi = &esi[1];
        edi = (edi + 1);
        ecx = (ecx - 1);
        if ((!z))
        {
            break;
        }
    }
    return (((!z) && (!c)) - c);
}

int32_t verify_user_pass(char* arg1)
{
    int32_t ecx = 5;
    char* esi = arg1;
    void* const edi = "admin";
    bool c;
    bool z;
    while (ecx != 0)
    {
        char temp0_1 = *esi;
        char temp1_1 = *edi;
        c = temp0_1 < temp1_1;
        z = temp0_1 == temp1_1;
        esi = &esi[1];
        edi = (edi + 1);
        ecx = (ecx - 1);
        if ((!z))
        {
            break;
        }
    }
    char* edx;
    edx = ((!z) && (!c));
    return (edx - c);
}

int32_t main(int32_t argc, char** argv, char** envp)
{
    void var_54;
    __builtin_memset(&var_54, 0, 0x40);
    int32_t var_14 = 0;
    puts("********* ADMIN LOGIN PROMPT ***…");
    printf("Enter Username: ");
    fgets(&a_user_name, 0x100, stdin);
    int32_t eax_1;
    if (verify_user_name() != 0)
    {
        puts("nope, incorrect username...\n");
        eax_1 = 1;
    }
    else
    {
        puts("Enter Password: ");
        fgets(&var_54, 0x64, stdin);
        int32_t eax_2 = verify_user_pass(&var_54);
        if ((eax_2 == 0 || (eax_2 != 0 && eax_2 != 0)))
        {
            puts("nope, incorrect password...\n");
            eax_1 = 1;
        }
        if (eax_2 == 0)
        {
            eax_1 = 0;
        }
    }
    return eax_1;
}