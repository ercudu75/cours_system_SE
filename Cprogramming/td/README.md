La commande fork() cree un processus fils du processus appelant (le pere), avec le meme programme que ce dernier.
La valeur renvoyee par fork() est Au pere : le numero (pid) du processus fils.
Au fils : 0 (il peut retrouver le pid de son pere avec getppid()
<img width="697" alt="Screenshot 2023-10-06 at 20 02 45" src="https://github.com/ercudu75/cours_system_SE/assets/75138084/35f6bb81-fd9c-4336-8381-2ffa45079592">
