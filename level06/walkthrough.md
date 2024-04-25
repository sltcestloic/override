# level06

Le main ouvre un shell après avoir passé la fonction `authenticate`

authenticate génère un serial correspondant au nom d'utilisateur, l'idée donc va simplement être de récupérer le code qui génère le serial et de générer un serial pour un nom d'utilisateur aléatoire

```sh
lbertran@z1r10p3 ~/work/override/level06/resources                                                                                                                          
> $ ./a.out aaaaaa         
Serial pour aaaaaa: 6231562
```

```sh
level06@OverRide:~$ ./level06 
***********************************
*        level06          *
***********************************
-> Enter Login: aaaaaa
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6231562
Authenticated!
$ whoami
level07
$ cat /home/users/level07/.pass
GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8
$ 
```