#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
/**
 * Exercice 1: Création et Synchronisation de Processus
Objectif: Comprendre le fonctionnement de fork(), wait(), et exit().

Description:

Écrivez un programme en C qui crée un processus enfant en utilisant fork().
Dans le processus enfant, affichez "Je suis l'enfant" suivi de son PID.
Dans le processus enfant, utilisez exit() avec un code de sortie unique.
Dans le processus parent, attendez que le processus enfant se termine en utilisant wait().
Affichez dans le processus parent "L'enfant a terminé" avec le code de sortie de l'enfant.
*/
int main(void)
{
	int i, n;

	i = fork();
	if (i == -1)
	{
		perror("fork");
		return (1);
	}
	else if (i == 0)
	{
		printf("Je suis l'enfant %d\n", getpid());
		exit(0);	/* Envoyer le code de sortie 0 */
	}
	else
	{
		wait(&n);
		/**
		 * WIFEXITED est une macro pour obtenir le code de sortie réel
		*/
		if (WIFEXITED(n))
			printf("L'enfant a terminé avec le code %d\n", WEXITSTATUS(n));
	}
}
