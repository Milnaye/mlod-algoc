// Candaes Corentin
// votre nom

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "vaccins_covid.h"

// =========
// = Types =
// =========

const char NUCLEOTIDES[] = "ATCG";

typedef struct{
	int index;
	int distance;
} Difference;

typedef struct{
	int differenceSize;
	Difference* differenceTab;
} Differences;


// =============
// = Fonctions =
// =============


bool isNucleotide(char c) {
    return (c==NUCLEOTIDES[0] || c==NUCLEOTIDES[1] || c==NUCLEOTIDES[2] || c==NUCLEOTIDES[3]);
}

int indexOf(char nucleotide) {
	switch(nucleotide) {
		case 'A': return 0;
		case 'T': return 1;
		case 'C': return 2;
		case 'G': return 3;
		default:
			return -1;
	}
}

int distanceBetweenNucleotides(char n1, char n2) {
    return indexOf(n1)-indexOf(n2);
}

int* statistics(char sequenceNucleotides[])
{
	const int nbNucleotidesDifferents = 4;
	int* occurence = (int*) calloc(4, sizeof(int));;

	for (size_t iNucleotide = 0; iNucleotide < strlen(sequenceNucleotides); iNucleotide++)
	{
		if(isNucleotide(sequenceNucleotides[iNucleotide]))
		{
			occurence[indexOf(sequenceNucleotides[iNucleotide])]++;
		}
	}

	for (int iNucleotide = 0; iNucleotide < nbNucleotidesDifferents; iNucleotide++)
	{
		occurence[iNucleotide] = occurence[iNucleotide]*100 / strlen(sequenceNucleotides);
	}
	return occurence;
}

int numberOfDifferencesBeetween(const char sequenceNucleotides1[], const char sequenceNucleotides2[])
{
	int nbDifferences = 0;
	for (size_t iNucleotide = 0; iNucleotide < strlen(sequenceNucleotides1); iNucleotide++)
	{
		if(sequenceNucleotides1[iNucleotide] != sequenceNucleotides2[iNucleotide])
		{
			nbDifferences++;
		}
	}
	return nbDifferences;
}

Differences* createNewDifferences(int nbDifferences)
{
	Differences* differences = (Differences*) malloc(sizeof(Differences));

	differences->differenceSize = nbDifferences;
	differences->differenceTab = (Difference*) calloc(differences->differenceSize, sizeof(Difference));

	return differences;
}

Differences* computeDifferencesBeetween(const char sequenceNucleotides1[], const char sequenceNucleotides2[])
{
	Differences* differences = createNewDifferences(numberOfDifferencesBeetween(sequenceNucleotides1, sequenceNucleotides2));

	int iDiff = 0;
	for (size_t iNucleotide = 0; iNucleotide < strlen(sequenceNucleotides1); iNucleotide++)
	{
		if(sequenceNucleotides1[iNucleotide] != sequenceNucleotides2[iNucleotide])
		{
			differences->differenceTab[iDiff].index = iNucleotide;
			differences->differenceTab[iDiff].distance =
				distanceBetweenNucleotides(sequenceNucleotides1[iNucleotide], sequenceNucleotides2[iNucleotide]);
			iDiff++;
		}
	}
	return differences;
}

void printDifference(Difference* difference)
{
	printf("<%d,%d>\n", difference->index, difference->distance);
}

void printDifferences(Differences* differences)
{
	for (int iDifference = 0; iDifference < differences->differenceSize; iDifference++)
	{
		printDifference(&(differences->differenceTab[iDifference]));
	}
}

void printStatistics(int* stats)
{
	printf("< ");
	for (size_t i = 0; i < strlen(NUCLEOTIDES); i++)
	{
		printf("%d", stats[i]);
		if(i != strlen(NUCLEOTIDES) -1)
		{
			printf(",");
		}
	}
	printf(" >\n");
}

void destroyDifferences(Differences* differences)
{
	free(differences->differenceTab);
	free(differences);
	differences = NULL;
}

// ========
// = Main =
// ========

int main(void){

	char sequenceDeNucleotides[]="ATGCATCCATCATGCATGTA";

	int* stats = statistics(sequenceDeNucleotides);
	printStatistics(stats); printf("\n");

	free(stats);

	Differences* differences = computeDifferencesBeetween(code_proteine_spike_moderna, code_proteine_spike_pfizer);

	printf("%s\n",code_proteine_spike_moderna); printf("\n");
	printDifferences(differences); printf("\n");
	printf("%d\n",differences->differenceSize); printf("\n");

	// Il manque un truc, papy va avoir des problèmes...
	destroyDifferences(differences);
	differences = NULL;
	return EXIT_SUCCESS;
}

