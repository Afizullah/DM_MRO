/*# 1-5-1
1 1
1 3 8
6 -1 16
-1 -4 11
1 0 1
# 2-7-3
 1.00E0
# 3-6-4 */

#include <stdlib.h>
#include <stdio.h>

void DFS(int nb_class, int *etat_com, int *visited, int s1, int s2)
{
    if (s1 == s2)
    {
        visited[s2] = 1;
        return;
    }
    int s;
    for (s = 0; s < nb_class; s++)
    {
        if (visited[s] == 0 && etat_com[s1 * nb_class + s] == 1)
        {
            visited[s] = 1;
            DFS(nb_class, etat_com, visited, s, s2);
        }
    }
    return;
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

    int *etat_com = calloc(nb_class * nb_class, sizeof(int));

    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (transitions[i - 1][j - 1] > 0)
            {
                etat_com[(comclasses[i - 1] - 1) * nb_class + (comclasses[j - 1] - 1)] = 1;
                printf("coordonnée dans etat_com : (%d, %d)\n", comclasses[i - 1] - 1, comclasses[j - 1] - 1);
            }
        }
    }
    printf("\nAffichage de la matrice du graphe réduit :\n");
    for (k = 0; k < nb_class; k++)
    {
        for (l = 0; l < nb_class; l++)
        {
            printf("%d ", etat_com[k * nb_class + l]);
        }
        printf("\n");
    }

    int *visited = calloc(nb_class, sizeof(int));

    for (k = 0; k < nb_class; k++)
    {
        int *visited = calloc(nb_class, sizeof(int));

        for (l = 0; l < nb_class; l++)
        {
            if (etat_com[k * nb_class + l] == 1)
            {
                DFS(nb_class, etat_com, visited, l, k);
            }
        }

        if (visited[k] == 1)
        {
            for (i = 1; i <= n; i++)
            {
                if (comclasses[i - 1] == k + 1)
                {
                    transientstates[i - 1] = 0;
                }
            }
        }
        else
        {
            for (i = 1; i <= n; i++)
            {
                if (comclasses[i - 1] == k + 1)
                {
                    transientstates[i - 1] = 1;
                }
            }
        }

        for (k = 0; k < nb_class; k++)
        {
            visited[k] = 0;
        }
    }
    free(visited);

    for (i = 0; i < n; i++)
    {
        if (transientstates[i] == -1)
        {
            transientstates[i] = 0;
        }
    }

    free(etat_com);
    return;
}

int main(void)
{
    int n = 4;
    int i, j;
    float transition_bis[4][4] = {{0.0, 0.0, 0.0, 1.0}, {0.0, 1.0, 0.0, 0.0}, {0.0, 0.0, 1.0, 0.0}, {0.0, 0.89, 0.11, 0.0}};
    float **transitions = calloc(4, sizeof(float *));
    for (i = 0; i < 4; i++)
    {
        transitions[i] = calloc(4, sizeof(float));
    }

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            transitions[i][j] = transition_bis[i][j];
        }
    }

    int comclasses[4] = {1, 2, 3, 4};

    int transientstates[4] = {-1, -1, -1, -1};
    /* début*/
    transient_states_algorithm(n, transitions, comclasses, transientstates);
    printf("\nVoici les états transitoires :\n");

    for (i = 0; i < n; i++)
    {
        printf("%d ", transientstates[i]);
    }

    for (i = 0; i < 4; i++)
    {
        free(transitions[i]);
    }
    free(transitions);

    return 0;
}
