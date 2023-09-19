#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

int64_t matrix_mult_part(int64_t matrice1[][SIZE], int64_t matrice2[][SIZE], int ligne, int colonne)
{
    // On calcule la somme des matrice1[i][k] * matrice2[k][j] avec k allant de 0 à taille de la matrice -1,
    // i et j étant l'emplacement de la case de la matrice
    int64_t resultat = 0;
    for (int i = 0; i < SIZE; i++)
    {
        resultat += matrice1[ligne][i] * matrice2[i][colonne];
    }
    return resultat;
}

void matrix_mult(int64_t matriceResultat[][SIZE], int64_t matrice1[][SIZE], int64_t matrice2[][SIZE])
{
    for (int iLigne = 0; iLigne < SIZE; iLigne++)
    {
        for (int iColonne = 0; iColonne < SIZE; iColonne++)
        {
            matriceResultat[iLigne][iColonne] = matrix_mult_part(matrice1, matrice2, iLigne, iColonne);
        }
    }
}

void matrix_print(int64_t matrice[][SIZE])
{
    for (int iLigne = 0; iLigne < SIZE; iLigne++)
    {
        for (int iColone = 0; iColone < SIZE; iColone++)
        {
            printf("%ld ", matrice[iLigne][iColone]);
        }
        printf("\n");
    }
}

int main(void) {
    //matrices en ligne * colonne
    int64_t matrice1[][SIZE]={{1,2,3,4,5},{1,2,3,4,5},{1,2,3,4,5},{1,2,3,4,5},{1,2,3,4,5}};
    int64_t matrice2[][SIZE]={{6,7,8,9,10},{6,7,8,9,10},{6,7,8,9,10},{6,7,8,9,10},{6,7,8,9,10}};
    int64_t matriceResultat[SIZE][SIZE];

    matrix_mult(matriceResultat, matrice1, matrice2);
    matrix_print(matriceResultat);

    return EXIT_SUCCESS;
}