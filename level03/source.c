int __cdecl decrypt(char a1)
{
  unsigned int i;
  unsigned int v3; 
  char v4[29]; 

  *(_DWORD *)&v4[17] = __readgsdword(0x14u);
  strcpy(v4, "Q}|u`sfg~sf{}|a3");
  v3 = strlen(v4);
  for ( i = 0; i < v3; ++i )
    v4[i] ^= a1;
  if ( !strcmp(v4, "Congratulations!") )
    return system("/bin/sh");
  else
    return puts("\nInvalid Password");
}


void test(unsigned int v1, unsigned int a0)
{
    unsigned int v0;  // [bp-0x10]

    v0 = a0 - v1;
    switch (v0)
    {
    case 1:
        decrypt(v0);
        return;
    case 2:
        decrypt(v0);
        return;
    case 3:
        decrypt(v0);
        return;
    case 4:
        decrypt(v0);
        return;
    case 5:
        decrypt(v0);
        return;
    case 6:
        decrypt(v0);
        return;
    case 7:
        decrypt(v0);
        return;
    case 8:
        decrypt(v0);
        return;
    case 9:
        decrypt(v0);
        return;
    case 16:
        decrypt(v0);
        return;
    case 17:
        decrypt(v0);
        return;
    case 18:
        decrypt(v0);
        return;
    case 19:
        decrypt(v0);
        return;
    case 20:
        decrypt(v0);
        return;
    case 21:
        decrypt(v0);
        return;
    default:
        decrypt(rand());
        return;
    }
}

int __cdecl main(int argc, const char **argv, const char **envp)
{
  unsigned int v3; // eax
  int savedregs; 

  v3 = time(0);
  srand(v3);
  puts("***********************************");
  puts("*\t\tlevel03\t\t**");
  puts("***********************************");
  printf("Password:");
  __isoc99_scanf("%d", &savedregs);
  test(savedregs, 322424845);
  return 0;
}