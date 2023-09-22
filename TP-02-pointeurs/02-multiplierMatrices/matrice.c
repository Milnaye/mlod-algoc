#include "matrice.h"

Matrice* creer(int64_t valeurInitiale, int64_t nbLignes, int64_t nbColonnes)
{
    Matrice* mat = (Matrice*) malloc(sizeof(Matrice));

    int64_t nbCases = nbColonnes*nbLignes;
    mat->matrice = (int64_t* ) calloc(nbCases, sizeof(int64_t));
    mat->nbColonnes = nbColonnes;
    mat->nbLignes = nbLignes;

    for (int64_t iCase = 0; iCase < nbCases; iCase++)
    {
        mat->matrice[iCase] = valeurInitiale;
    }
    return mat;
}

void initialiserLigne(int64_t valeur, int64_t ligne, Matrice* matrice)
{
    if(ligne > matrice->nbLignes)
    {
        return;
    }

    int64_t ligneOffset = (ligne-1) * matrice->nbColonnes;
    for (int64_t iColonne = 0; iColonne < matrice->nbColonnes; iColonne++)
    {
        matrice->matrice[ligneOffset + iColonne] = valeur;
    }
}

void afficherMatrice(Matrice* matrice)
{
    int64_t ligneOffset = 0;
    for (int64_t iLigne = 0; iLigne < matrice->nbLignes; iLigne++)
    {
        ligneOffset = iLigne * matrice->nbColonnes;

        for (int64_t iColonne = 0; iColonne < matrice->nbColonnes; iColonne++)
        {
            printf("%"PRId64" ", matrice->matrice[ligneOffset + iColonne]);
        }
        printf("\n");
    }
    printf("\n");
}

int64_t multiplier_part(Matrice* matrice1, Matrice* matrice2, int64_t ligne, int64_t colonne, int64_t k)
{
    // On calcule la somme des matrice1[i][k] * matrice2[k][j] avec k allant de 0 à taille de la matrice -1,
    // i et j étant l'emplacement de la case de la matrice
    int64_t resultat = 0;
    for (int i = 0; i < k; i++)
    {
        int64_t matrice1CaseIK = matrice1->matrice[ligne*(matrice1->nbColonnes) + i];
        int64_t matrice2CaseKJ = matrice2->matrice[i* matrice2->nbColonnes + colonne];
        resultat += matrice1CaseIK * matrice2CaseKJ;
    }
    return resultat;
}

// si la multiplication est impossible, on retourne une matrice qu'on a pas voulu
Matrice* multiplier(Matrice* matriceA, Matrice* matriceB)
{
    Matrice* mat_result = creer(0, matriceA->nbLignes, matriceB->nbColonnes);

    if(matriceA->nbColonnes != matriceB->nbLignes)
    {
        return mat_result;
    }

    int64_t ligneOffset = 0;
    for (int64_t iLigne = 0; iLigne < mat_result->nbLignes; iLigne++)
    {
        ligneOffset = iLigne * mat_result->nbColonnes;
        for (int64_t iColonne = 0; iColonne < mat_result->nbColonnes; iColonne++)
        {
            mat_result->matrice[ligneOffset + iColonne] = multiplier_part(matriceA, matriceB, iLigne, iColonne, matriceB->nbLignes);
        }
    }
    return mat_result;
}

void detruire(Matrice* m)
{
    free(m->matrice);
    free(m);
}