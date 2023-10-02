#include "liste-chainee.h"
#include <stdlib.h>
#include <stdio.h>

#define TODO NULL;

// retourne vrai si l est vide et faux sinon
bool estVide(Liste l)
{
	return l == NULL;
}

// créer une liste d'un seul élément contenant la valeur v
Liste creer(Element v)
{
	Liste l = (Liste) malloc(sizeof(Cellule));
	l->val = v;
	l->suiv = NULL;
	return l;
}

// ajoute l'élément v en tete de la liste l
Liste ajoutTete(Element v, Liste l)
{
	Liste newHead = creer(v);
	newHead->suiv = l;
	return newHead;
}


void afficheElement(Element e)
{
	printf("%i ",e);
}

// affiche tous les éléments de la liste l
// Attention, cette fonction doit être indépendante du type des éléments de la liste
// utiliser une fonction annexe affiche_element
// Attention la liste peut être vide !
// version itérative
void afficheListe_i(Liste l)
{
	Liste current = l;
	while (estVide(current))
	{
		afficheElement(current->val);
		current = current->suiv;
	}
	printf("\n");
}

// version recursive
void afficheListe_r(Liste l)
{
	if (estVide(l))
	{
		printf("\n");
		return;
	}
	afficheElement(l->val);
	afficheListe_r(l->suiv);
}

void detruireElement(Element e) {}

// Détruit tous les éléments de la liste l
// version itérative
void detruire_i(Liste l)
{
	Cellule* current = l;
	Cellule* next = NULL;
	do
	{
		next = current->suiv;
		detruireElement(current->val);
		free(current);
		current = next;
	} while (!estVide(next));
}

// version récursive
void detruire_r(Liste l)
{
	if(estVide(l))
	{
		return;
	}
	detruire_r(l->suiv);
	detruireElement(l->val);
	free(l);
}

// retourne la liste dans laquelle l'élément v a été ajouté en fin
// version itérative
Liste ajoutFin_i(Element v, Liste l)
{
	Cellule* current = l;
	while (!estVide(current->suiv))
	{
		current = current->suiv;
	}
	// current is now last

	Liste new = creer(v);
	current->suiv = new;
	return l;
}

// version recursive
Liste ajoutFin_r(Element v, Liste l)
{
	if(estVide(l))
	{
		return creer(v);
	}

	if(!estVide(l->suiv))
	{
		ajoutFin_r(v, l->suiv);
		return l;
	}
	l->suiv = creer(v);
	return l;
}

// compare deux elements
bool equalsElement(Element e1, Element e2){
	return e1 == e2;
}

// Retourne un pointeur sur l'élément de la liste l contenant la valeur v ou NULL
// version itérative
Liste cherche_i(Element v,Liste l)
{
	while(!estVide(l))
	{
		if(equalsElement(v, l->val))
		{
			return l;
		}
		l = l->suiv;
	}
	return NULL;
}

// version récursive
Liste cherche_r(Element v,Liste l)
{
	if(estVide(l))
	{
		return NULL;
	}
	if(equalsElement(v, l->val))
	{
		return l;
	}
	return cherche_r(v, l->suiv);
}

// Retourne la liste modifiée dans la laquelle le premier élément ayant la valeur v a été supprimé
// ne fait rien si aucun élément possède cette valeur
// version itérative
Liste retirePremier_i(Element v, Liste l)
{
	Cellule* current = l;
	Cellule* previous = NULL;

	while (!estVide(current))
	{
		if(equalsElement(v, current->val))
		{
			if(previous == NULL)
			{
				Cellule* toReturn = current->suiv;
				detruireElement(current->val);
				free(current);
				return toReturn;
			}
			previous->suiv = current->suiv;
			detruireElement(current->val);
			free(current);
			return l;
		}
		previous = current;
		current = current->suiv;
	}

	return l;
}


// version recursive
Liste retirePremier_r(Element v, Liste l) {
	if(l->val == v)
	{
		Liste toReturn = l->suiv;
		detruireElement(l->val);
		free(l);
		return toReturn;
	}

	if(estVide(l->suiv))
	{
		return NULL;
	}

	if(l->suiv->val == v)
	{
		Liste toRemove = l->suiv;
		l->suiv = l->suiv->suiv;
		detruireElement(toRemove->val);
		free(toRemove);
		return l;
	}

	retirePremier_r(v, l->suiv);
	return l;
}


void afficheEnvers_r(Liste l) {
	if (estVide(l))
	{
		printf("\n");
		return;
	}
	afficheListe_r(l->suiv);
	afficheElement(l->val);
}



