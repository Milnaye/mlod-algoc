#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "matrice.h"

int main(void) {
    Matrice *A, *B, *C;
    A = creer(1, 2, 3); // valeurInitiale, nbreLignes, nbreColonnes
    B = creer(1, 3, 3);

    initialiserLigne(2, 1, A);
    initialiserLigne(2, 2, B);
    C = multiplier(A, B);

    afficherMatrice(A);
    afficherMatrice(B);

    afficherMatrice(C);

    detruire(A);
    detruire(B);
    detruire(C);
    return EXIT_SUCCESS;
}