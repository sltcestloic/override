# level00

On a un executable `level00` à la racine.

Le programme demande un mot de passe lors de son execution :
```bash
level00@OverRide:~$ ./level00 
***********************************
*          -Level00 -          *
***********************************
Password:password

Invalid Password!
```

Un coup d'oeil au main désassemblé permet de repérer une condition très simple :
```as
0x080484e7 <+83>:    cmp    $0x149c,%eax
```

En affichant le contenu de `$0x149c` on trouve la valeur du mot de passe : `5276`.
```as
(gdb) p 0x149c
$1 = 5276
```
On obtient accès à un terminal et donc à notre flag avec ce mot de passe :
```bash
level00@OverRide:~$ ./level00 
***********************************
*          -Level00 -          *
***********************************
Password:5276

Authenticated!
$ cat /home/users/level01/.pass
uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL
```