// gcc -W -Wall -std=c99 liste-chainee.c liste-chainee-main.c -o liste-chaine-main
// gcc -W -Wall -Wno-unused-parameter -std=c99 liste-chainee.c liste-chainee-main.c -o liste-chaine-main

#include "linkedListOfString.c"
#include <stdlib.h>
#include <stdio.h>

int main(void){
	Liste l, p;

	l = NULL;
	printf("estVide(l) = %s\n",estVide(l)?"TRUE":"FALSE");

	l = ajoutTete("tomate",l);
	l = ajoutTete("patate",l);
	l = ajoutTete("oignon",l);
	l = ajoutTete("tomate",l);
	l = ajoutTete("poireau",l);
	l = ajoutTete("courgette",l);
	l = ajoutTete("patate",l);
	l = ajoutTete("oignon",l);
	l = ajoutTete("tomate",l);

	afficheListe_i(l);

	ajoutFin_r("aubergine",l);
	afficheListe_i(l);

	ajoutFin_r("carotte",l);
	afficheListe_i(l);

	p = cherche_i("citron",l);
	printf("cherche_i(citron) : %s\n",estVide(p)?"pas trouve":"[ERREUR] trouve !!!");

	p = cherche_i("aubergine",l);
	if(estVide(p))
		printf("cherche_i(aubergine) : [ERREUR] pas trouve \n");
	else {
		printf("cherche_i(aubergine) : trouve ");
		afficheElement(p->val);
		printf("\n");
	}

	p = cherche_r("citron",l);
	printf("cherche_r(citron) : %s\n",estVide(p)?"pas trouve":"[ERREUR] trouve !!!");

	p = cherche_r("aubergine",l);
	if(estVide(p))
		printf("cherche_r(aubergine) : [ERREUR] pas trouve \n");
	else {
		printf("cherche_r(aubergine) : trouve ");
		afficheElement(p->val);
		printf("\n");
	}

	printf("retirePremier_i(tomate)   : ");
	l = retirePremier_i("tomate",l);
	afficheListe_r(l);

	printf("retirePremier_i(tomate)   : ");
	l = retirePremier_i("tomate",l);
	afficheListe_r(l);

	printf("retirePremier_i(carotte) : ");
	l = retirePremier_i("carotte",l);
	afficheListe_r(l);

	printf("retirePremier_r(oignon)   : ");
	l = retirePremier_r("oignon",l);
	afficheListe_r(l);

	printf("retirePremier_r(oignon)   : ");
	l = retirePremier_r("oignon",l);
	afficheListe_r(l);

	printf("retirePremier_r(aubergine)  : ");
	l = retirePremier_r("aubergine",l);
	afficheListe_r(l);

	detruire_r(l);

	return EXIT_SUCCESS;
}