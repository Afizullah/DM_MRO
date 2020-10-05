#include <stdlib.h>
#include <stdio.h>

void Warshall(int n, int **A, int **C)
{
    int i, j, k;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (i != j)
            {
                A[i][j] = C[i][j];
            }
        }
    }
    for (k = 0; k < n; k++)
    {
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                A[i][j] = A[i][j] || (A[i][k] && A[k][j]);
            }
        }
    }
}

void transient_states_algorithm(int n, float **transitions, int *comclasses, int *transientstates)
{
    int i, j, k, l;

    int nb_class = comclasses[0];
    for (i = 1; i <= n; i++)
    {
        if (comclasses[i - 1] >= nb_class)
        {
            nb_class = comclasses[i - 1];
        }
    }
    if (nb_class == 1)
    {
        for (i = 0; i < n; i++)
        {
            transientstates[i] = 0;
        }
        return;
    }

    int **etats_com = (int **)malloc(nb_class * sizeof(int *));
    for (k = 0; k < nb_class; k++)
    {
        etats_com[k] = (int *)calloc(nb_class, sizeof(int));
    }
    /*    printf("\nnb_classe = %d ; fin\n", nb_class);
    return;*/

    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (transitions[i - 1][j - 1] > 0)
            {
                etats_com[comclasses[i - 1] - 1][comclasses[j - 1] - 1] = 1;
                printf("coordonnée dans etats_com : (%d, %d)\n", comclasses[i - 1] - 1, comclasses[j - 1] - 1);
            }
        }
    }
    printf("\nAffichage de la matrice du graphe réduit :\n");
    for (k = 0; k < nb_class; k++)
    {
        for (l = 0; l < nb_class; l++)
        {
            printf("%d ", etats_com[k][l]);
        }
        printf("\n");
    }

    int **etats_com_ferm = (int **)malloc(nb_class * sizeof(int *));
    for (k = 0; k < nb_class; k++)
    {
        etats_com_ferm[k] = (int *)calloc(nb_class, sizeof(int));
    }

    Warshall(nb_class, etats_com_ferm, etats_com);

    printf("Voici la fermeture transitive de etat_com\n");

    for (k = 0; k < nb_class; k++)
    {
        for (l = 0; l < nb_class; l++)
        {
            printf("%d ", etats_com_ferm[k][l]);
        }
        printf("\n");
    }

    for (i = 1; i <= n; i++)
    {
        int classe = comclasses[i - 1] - 1;

        if (etats_com_ferm[classe][classe] == 0)
        {
            transientstates[i - 1] = 1;
        }
    }

    for (k = 0; k < nb_class; k++)
    {
        free(etats_com[k]);
        free(etats_com_ferm[k]);
    }
    free(etats_com);
    free(etats_com_ferm);

    for (k = 0; k < nb_class; k++)
    {
        int solo = 1;
        for (i = 1; i <= n; i++)
        {
            if (comclasses[i - 1] == k + 1)
            {
                for (j = 1; j <= n; j++)
                {
                    if (transitions[i - 1][j - 1] > 0 && comclasses[j - 1] != comclasses[i - 1])
                    {
                        solo = 0;
                    }
                }
            }
        }
        if (solo == 1)
        {
            printf("\n la classe %d est isolé, ses sommets sont mis à 1\n", k);
            for (j = 1; j <= n; j++)
            {
                if (comclasses[j - 1] == k + 1)
                {
                    transientstates[j - 1] = 0;
                }
            }
        }
    }
   /* for (i = 1; i <= n; i++)
    {
        if (transitions[i - 1][i - 1] == 1)
        {
            printf("\n la classe %d comporte 1 seul sommet absorbant\n", comclasses[i - 1] - 1);
            transientstates[i - 1] = 0;
        }
    }
    */
    return;
}

int main(void)
{
    int n = 4;
    int i, j;
    float transition_bis[4][4] = {{1.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 1.0}, {0.0, 0.0, 1.0, 0.0}, {0.0, 1.0, 0.0, 0.0}};
    float **transitions = (float **)malloc(4 * sizeof(float *));
    for (i = 0; i < n; i++)
    {
        transitions[i] = (float *)malloc(4 * sizeof(float));
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            transitions[i][j] = transition_bis[i][j];
        }
    }
    int comclasses[4] = {1, 2, 3, 2};

    int transientstates[4] = {-1, -1, -1, -1};

    /* début*/
    transient_states_algorithm(n, transitions, comclasses, transientstates);
    printf("\nVoici les états transitoires :\n");

    for (i = 0; i < n; i++)
    {
        printf("%d ", transientstates[i]);
    }

    for (i = 0; i < n; i++)
    {
        free(transitions[i]);
    }
    free(transitions);

    return 0;
}
