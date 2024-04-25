# level03

On voit un main qui appelle `test()` avec notre input parsé en `int`, et un nombre arbitraire

Dans `test()`, la fonction soustrait le 1er paramètre au 2ème, puis, si le résultat est entre 1 et 23, appelle decrypt avec le résultat, sinon, appelle decrypt avec un nombre random

Dans `decrypt()`, c'est cette partie qui va nous intéresser:
```C
  strcpy(v4, "Q}|u`sfg~sf{}|a3");
  v3 = strlen(v4);
  for ( i = 0; i < v3; ++i )
    v4[i] ^= a1;
  if ( !strcmp(v4, "Congratulations!") )
    return system("/bin/sh");
  else
    return puts("\nInvalid Password");
```

On voit que le programme utilise un bitwise XOR operator pour décrypter une chaine de caractères en utilisant a1 qui est le résultat de la soustraction effectuée dans `test()`, puis, compare la chaine décryptée avec `Congratulations !`

J'ai donc fait un petit programme en C qui fait la même chose en essayant toutes les combinaisons de 1 à 100 pour trouver quelle valeur nous donne le résultat attendu (voir resources)

```sh
> $ ./a.out                                  
...
[17] @lmdqbwvobwjlmp"
[18] Congratulations!
[19] Bnofs`utm`uhnor 
...
```

On voit donc que c'est le chiffre 18 qui nous donne le résultat attendu. En revenant dans `main()`, on voit que le 2ème paramètre de  `test()` est `322424845`. On cherche donc quel nombre soustraire à ce dernier pour trouver 18: `322424827`

```sh
level03@OverRide:~$ ./level03 
***********************************
*        level03        **
***********************************
Password:322424827
$ whoami
level04
$ cat /home/users/level04/.pass
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
```