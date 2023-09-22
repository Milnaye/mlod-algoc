#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>

typedef struct{
    int64_t nbLignes;
    int64_t nbColonnes;
    int64_t* matrice;   //on stocke les cases sur une seule dimension car plus pratique
} Matrice;

Matrice* creer(int64_t valeurInitiale, int64_t nbLignes, int64_t nbColonnes);

void initialiserLigne(int64_t ligne, int64_t valeur, Matrice* matrice);

void afficherMatrice(Matrice* matrice);

Matrice* multiplier(Matrice* matriceA, Matrice* matriceB);

void detruire(Matrice* matrice);