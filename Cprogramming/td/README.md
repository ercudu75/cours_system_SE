La commande fork() cree un processus fils du processus appelant (le pere), avec le meme programme que ce dernier.
La valeur renvoyee par fork() est Au pere : le numero (pid) du processus fils.
Au fils : 0 (il peut retrouver le pid de son pere avec getppid()
