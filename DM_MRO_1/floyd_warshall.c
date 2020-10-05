/*
# 1-3-4
E 2 E 4 E E 7 t
E 2 E E 5 6 E t
ajout de 0(=s) et 8(=t) 
E 2 E E 5 6 E 8
dernière itération
# 2-2-2
630
la consigne indique : 1 ligne contenant 8 entiers et/ou lettres ’E’ séparés 
par un espace (mais l'exemple en contient 9) Pour chaque noeud, dans l’ordre,
en commençant par 1 et en terminant par t
du coup j'ai ajouté le noeud 0 et j'ai remplacé t par 8. 

Également pour l'algorithme de johnson, l'exo correspondant 
n'a pas été fait en TD, j'ai appliqué la technique "M1' = M1+M2" et une autre consistant à trier dans l'ordre croissant
*/

void floyd_warshall_pred_algorithm(int n, int **weights, int **pred)
{
    int m, i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (weights[i][j] != -1)
            {
                pred[i][j] = i + 1;
            }
        }
    }

    for (m = 0; m < n; m++)
    {
        for (i = 0; i < n; i++)
        {
            if (i == m && i < n - 1)
                i++;
            for (j = 0; j < n; j++)
            {
                if (weights[i][m] != -1 && weights[m][j] != -1)
                {
                    if ((weights[i][j] == -1) || (weights[i][m] + weights[m][j] < weights[i][j]))
                    {
                        weights[i][j] = weights[i][m] + weights[m][j];
                        pred[i][j] = m + 1;
                    }
                }
            }
        }
    }
}

void floyd_warshall_pred_algorithm(int n, int **weights, int **pred)
{
    int m, i, j, max = 999999;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (weights[i][j] == -1)
            {
                weights[i][j] = max;
            }
            else
            {
                pred[i][j] = i + 1;
            }
        }
    }

    for (m = 0; m < n; m++)
    {
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                if ((weights[i][m] + weights[m][j] < weights[i][j]))
                {
                    weights[i][j] = weights[i][m] + weights[m][j];
                    pred[i][j] = m + 1;
                }
            }
        }
    }
}