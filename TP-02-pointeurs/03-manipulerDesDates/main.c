#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum Mois{
    JANVIER =1,
    FEVRIER,
    MARS,
    AVRIL,
    MAI,
    JUIN,
    JUILLET,
    AOUT,
    SEPTEMBRE,
    OCTOBRE,
    NOVEMBRE,
    DECEMBRE
} Mois;

typedef struct{
    Mois mois;
    unsigned int jour;
    int annee;
} Date;

void initialiseDate(Date* d)
{
    printf("Entrer le jour : ");
    scanf("%u", &d->jour);
    printf("Entrer le mois : ");
    scanf("%d", (int *)&d->mois);
    printf("Entrer l'annee : ");
    scanf("%d", &d->annee);
}

Date creerDateParCopie()
{
    Date d;
    initialiseDate(&d);
    return d; // Copie, peut être lourd dans le cas d'une grosse structure
}

Date* newDate()
{
    Date* d = malloc(sizeof(Date));
    initialiseDate(d);
    return d;
}

unsigned int nbreJoursFevrier(unsigned int annee)
{
    if(annee % 4 == 0 && // année bisextile sont les multiples de 4
        ((annee % 100 != 0) || (annee % 400 == 0))) // qui ne sont pas multiples de 100, sauf les multiples de 400
    {
        return 29;
    }
    return 28;
}

unsigned int nbreJours(Mois mois, unsigned int annee)
{
    if(mois == FEVRIER)
    {
        return nbreJoursFevrier(annee);
    }

    if( (mois <= 7 && (mois % 2 == 0)) // mois pair, hors février, première moitié
        || (mois >= 8 && (mois % 2 == 1))) // ou mois impair, seconde moitié
    {
        return 30;
    }
    return 31;
}

bool dateValide(Date d)
{

    if(d.jour < 0 || d.jour > nbreJours(d.mois, d.annee))
    {
        return false;
    }

    if(d.mois < JANVIER || d.mois > DECEMBRE)
    {
        return false;
    }

    return true;
}

unsigned int jourDansAnnee(Date d)
{
    return nbreJoursFevrier(d.annee) + 365 - 28; // nombre de jour d'une année - le nombre de jour en fevrier + nombre de jours en fevrier de l'année
}

void afficheDate(Date* d)
{
    printf("Nous sommes le %d/%d/%d\n", d->jour, d->mois, d-> annee);
    printf("Cette année dure %u jours\n", jourDansAnnee(*d));
}

int main(void)
{
    Date* d;
    d = newDate(); //Pourquoi a t-on ajouté un &? -> Pour ne pas recopier la structure
    afficheDate(d);

    free(d);
    return EXIT_SUCCESS;
}