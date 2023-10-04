#include "arbre-bin-recherche.h"
#include <stdlib.h>
#include <stdbool.h>

// retourne TRUE si a est l'arbre vide et FALSE sinon
bool estVide(ArbreBinaire a) {
	return a == NULL;
}

// initialise l'arbre a à l'arbre vide
void initialiser(ArbreBinaire* a)
{
	*a = NULL;
}

// créer un arbre contenant un seul noeud ayant la valeur e
ArbreBinaire creer(Element e) {
	ArbreBinaire a = (ArbreBinaire) malloc(sizeof(Noeud));
	a->val = e;
	a->filsDroit = NULL;
	a->filsGauche = NULL;
	return a;
}

// insere e dans a sachant que a est un arbre binaire de recherche
// si a contient déjà un element e, ce dernier n'est pas insérer afin d'éviter les doublons
// version itérative
ArbreBinaire insere_i(ArbreBinaire a, Element e) {
	if(estVide(a))
	{
		return creer(e);
	}

	ArbreBinaire current = a;
	bool inserted = false;

	while (!inserted)
	{
		if(e == current->val)
		{
			inserted = true;
		}
		else if(e > current->val)
		{
			if(estVide(current->filsDroit))
			{
				current->filsDroit = creer(e);
				inserted = true;
			}
			else
			{
				current = current->filsDroit;
			}
		}
		else // e < current->val
		{
			if(estVide(current->filsGauche))
			{
				current->filsGauche = creer(e);
				inserted = true;
			}
			else
			{
				current = current->filsDroit;
			}
		}
	}
	return a;
}

// insere e dans a sachant que a est un arbre binaire de recherche
// si a contient déjà un element e, ce dernier n'est pas insérer afin d'éviter les doublons
// version récursive
ArbreBinaire insere_r(ArbreBinaire a, Element e) {
	if(estVide(a))
	{
		return creer(e);
	}

	if(e > a->val)
	{
		if(estVide(a->filsDroit))
		{
			a->filsDroit = creer(e);
		}
		else
		{
			insere_r(a->filsDroit, e);
		}
	}
	if(e < a->val)
	{
		if(estVide(a->filsGauche))
		{
			a->filsGauche = creer(e);
		}
		else
		{
			insere_r(a->filsGauche, e);
		}
	}

	return a;
}

// retourne le nombre de noeud contenus dans l'arbre a
int nombreDeNoeud(ArbreBinaire a){
	if(estVide(a))
	{
		return 0;
	}
	return 1 + nombreDeNoeud(a->filsDroit) + nombreDeNoeud(a->filsGauche);
}


// retourne la profondeur du noeud ayant la valeur e dans a
// retourne -1 si a est vide ou si e n'est pas dans a
int profondeur(ArbreBinaire a, Element e){
	if(estVide(a))
	{
		return -1;
	}
	if(a->val == e)
	{
		return 0;
	}

	int depthRChild = profondeur(a->filsDroit, e);
	int depthLChild = profondeur(a->filsGauche, e);
	if(depthRChild >= 0)
	{
		return depthRChild + 1;
	}
	if(depthLChild >= 0)
	{
		return depthLChild + 1;
	}
	return -1;
}

// retourne la hauteur de l'arbre a
int hauteur(ArbreBinaire a){
	if(estVide(a))
	{
		return 0;
	}
	int heighRChild = hauteur(a->filsDroit);
	int heighLChild = hauteur(a->filsGauche);

	return 1 + (heighRChild > heighLChild ? heighRChild : heighLChild);
}

// retourne le pere de elem dans l'arbre a ou NULL s'il n'existe pas
ArbreBinaire pere(ArbreBinaire a, Element elem){
	if(estVide(a) || a->val == elem)
	{
		return NULL;
	}

	ArbreBinaire currentFather = NULL;
	ArbreBinaire current = a;

	while (true)
	{
		if(elem == current->val)
		{
			return currentFather;
		}
		else if(elem > current->val)
		{
			if(estVide(current->filsDroit))
			{
				return NULL;
			}
			else
			{
				currentFather = current;
				current = current->filsDroit;
				//we love nesting
			}
		}
		else // e < current->val
		{
			if(estVide(current->filsGauche))
			{
				return NULL;
			}
			else
			{
				currentFather = current;
				current = current->filsGauche;
			}
		}
	}
	return a;
}


void afficher(Element e)
{
	printf("%d ", e);
}

void afficheRGD_r(ArbreBinaire a)
{
	if (estVide(a))
	{
		return;
	}

	afficher(a->val);
	afficheRGD_r(a->filsGauche);
	afficheRGD_r(a->filsDroit);
}

void afficheGRD_r(ArbreBinaire a)
{
	if (estVide(a))
	{
		return;
	}

	afficheGRD_r(a->filsGauche);
	afficher(a->val);
	afficheGRD_r(a->filsDroit);
}

void afficheGDR_r(ArbreBinaire a)
{
	if (estVide(a))
	{
		return;
	}

	afficheGDR_r(a->filsGauche);
	afficheGDR_r(a->filsDroit);
	afficher(a->val);
}

// retourne le noeud dont la valeur est minimum dans l'arbre
// Suppose que a est un arbre binaire de recherche sans doublons
ArbreBinaire min(ArbreBinaire a)
{
	if(estVide(a))
	{
		return NULL;
	}

	ArbreBinaire noeudMin = a;
	while(!estVide(noeudMin->filsGauche))
	{
		noeudMin = noeudMin->filsGauche;
	}
	return noeudMin;
}

// retourne le noeud dont la valeur est maximum dans l'arbre
// Suppose que a est un arbre binaire de recherche sans doublons
ArbreBinaire max(ArbreBinaire a)
{
	if(estVide(a))
	{
		return NULL;
	}

	ArbreBinaire noeudMax = a;
	while(!estVide(noeudMax->filsDroit))
	{
		noeudMax = noeudMax->filsDroit;
	}
	return noeudMax;
}


// retourne l'arbre dont la valeur de la racine est elem et NULL si elem n'existe dans a
// version récursive -> on pourrait utiliser la fonction père
ArbreBinaire recherche_r(ArbreBinaire a, Element elem){
	if(estVide(a))
	{
		return NULL;
	}
	if (a->val == elem)
	{
		return a;
	}

	if (elem > a->val)
	{
		if (estVide(a->filsDroit))
		{
			return NULL;
		}
		return recherche_r(a->filsDroit, elem);
	}

	// elem < a->val
	if (estVide(a->filsGauche))
	{
		return NULL;
	}
	return recherche_r(a->filsGauche, elem);

}


// suppime x de a
ArbreBinaire supprimer_r(ArbreBinaire a,Element x)
{
	return NULL;
}

void detruire_r(ArbreBinaire a){
	ArbreBinaire LChild = a->filsGauche;
	ArbreBinaire RChild = a->filsDroit;
	if(!estVide(LChild))
	{
		detruire_r(LChild);
		LChild = NULL;
	}
	if(!estVide(RChild))
	{
		detruire_r(RChild);
		RChild = NULL;
	}
	free(a);
}

