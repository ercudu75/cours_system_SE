#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
/**
 * Exercice 2: Plusieurs Processus Enfants
Objectif: Gérer plusieurs processus enfants et comprendre la terminaison des processus.

Description:

Écrivez un programme en C qui crée deux processus enfants.
Chaque processus enfant doit afficher son propre PID et celui de son parent.
Utilisez exit() dans les processus enfants avec des codes de sortie différents.
Dans le processus parent, utilisez wait() pour attendre que les deux enfants se terminent.
Le processus parent doit afficher les codes de sortie de chaque enfant.
 *
*/


int main(void)
{
    pid_t pid;
    int statut;

    for (int i = 0; i < 2; i++)
    {
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            return 1;
        }
        else if (pid == 0)
        {
            printf("Voici l'enfant numero %d avec son PID %d et son père PID %d\n", i + 1, getpid(), getppid());
            exit(i + 1);
        }
    }

    for (int j = 0; j < 2; j++)
    {
        pid_t child_pid ;

		child_pid = wait(&statut);
        if (WIFEXITED(statut))
            printf("L'enfant avec PID %d a terminé avec le statut de sortie %d\n", child_pid, WEXITSTATUS(statut));
    }

    return 0;
}
