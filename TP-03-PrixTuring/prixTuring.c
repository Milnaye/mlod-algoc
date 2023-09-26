/**
 Compilation
 gcc --std=c99 -W -Wall -o prixTuring prixTuring.c

 Exécution
 ./prixTuring

 Tests
 diff out.csv turingWinners.csv

**/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#define STRING_SEPARATOR ';'

typedef uint16_t IntWinnerSize;

typedef struct{
	uint16_t year;
	char* names;
	char* works;
} Winner;

typedef struct{
	IntWinnerSize nbWinner;
	Winner* winners;
} Winners;


bool fileIsOk(FILE* file)
{
	if(file == NULL)
	{
		return false;
	}
	return true;
}

IntWinnerSize numberOfWinners(FILE* fileToRead)
{
	// the number of winner corresponds to the number of line in the input file

	// we want to start at the beginning of the file
	rewind(fileToRead);

	uint32_t nbLine = 0;
	char current = fgetc(fileToRead);
  	while (current != EOF)
	{
		if (current == '\n')
		{
			nbLine++;
		}
		current = fgetc(fileToRead);
	}
	return nbLine;
}

Winners* newWinnerList(FILE* inputFile)
{
	Winners* winners = (Winners*) malloc (sizeof(Winners));
	winners->nbWinner = numberOfWinners(inputFile);

	winners->winners = (Winner*) calloc (winners->nbWinner, sizeof(Winner));

	return winners;
}

int numberCharCurrentString(FILE* inputfile)
{
	int nbChar = 0;
	char current;

  	do
	{
		current = fgetc(inputfile);
		nbChar++;
	} while (current != EOF && current != STRING_SEPARATOR && current != '\n');

	fseek(inputfile, -nbChar, SEEK_CUR);
	return nbChar;
}

void readString(Winner* winner, FILE* inputFile)
{
	/*two possibilities here:
	 *	- use fgetc() to find the number of characters, then fseek back, allocate and fgets
	 *	- allocate, use fgetc, reallocate when size limit is reached.
	*/

	uint32_t nbChar = numberCharCurrentString(inputFile);
	winner->names = (char*) calloc(nbChar+1, sizeof(char));
	fgets(winner->names, nbChar, inputFile);

	fgetc(inputFile); // read ';'

	nbChar = numberCharCurrentString(inputFile);
	winner->works = (char*) calloc(nbChar+1, sizeof(char));
	fgets(winner->works, nbChar, inputFile);
}

void readWinner(Winner* winner, FILE* inputFile)
{
	fscanf(inputFile, "%"SCNu16";", &(winner->year));
	readString(winner, inputFile);
}

Winners* readWinners(FILE* inputFile)
{
	// we want to start at the beginning of the file
	Winners* winners = newWinnerList(inputFile);

	rewind(inputFile);

	// iteration over each winner of winners struct
	for (IntWinnerSize iWinner = 0;	iWinner < winners->nbWinner; iWinner++)
	{
		readWinner(&winners->winners[iWinner], inputFile);
	}
	return winners;
}

void printWinner(Winner* winner, FILE* outputFile)
{
	fprintf(outputFile, "%"PRIu16";%s;%s\n", winner->year, winner->names, winner->works);
}

void printWinner(Winner* winner)
{
	printf("%"PRIu16";%s;%s\n", winner->year, winner->names, winner->works);
}

void printWinners(Winners* winners, FILE* outputFile)
{
	for (IntWinnerSize iWinner = 0; iWinner < winners->nbWinner; iWinner++)
	{
		printWinner(&(winners->winners[iWinner]), outputFile);
	}
}

void destroyWinners(Winners* winners)
{
	for (IntWinnerSize iWinner = 0; iWinner < winners->nbWinner; iWinner++)
	{
		free(winners->winners[iWinner].names);
		free(winners->winners[iWinner].works);
	}
	free(winners->winners);
	free(winners);
}

Winner* findWinnerOfYear(uint16_t year, FILE* inputFilename)
{
	FILE* inputFile = fopen(inputFilename, "r");

	if(!fileIsOk(inputFile))
	{
		printf("File error\n");
		return EXIT_FAILURE;
	}

	Winners* winners = readWinners(inputFile);

	fclose(inputFile);


	destroyWinners(winners); // :)
	winners = NULL;

	return EXIT_SUCCESS;
}

Winners* getWinnersFromFile(char* filename)
{
	FILE* inputFile = fopen(filename, "r");
	if(!fileIsOk(inputFile))
	{
		printf("File error\n");
		return NULL;
	}

	Winners* winners = readWinners(inputFile);

	fclose(inputFile);
	return winners;
}

void copyWinnersIntoFile(Winners* winners, char* outputFilename)
{
	FILE* outputFile = fopen(outputFilename, "w");
	if(!fileIsOk(outputFile))
	{
		printf("File error\n");
		return;
	}

	printWinners(winners, outputFile);

	fclose(outputFile);
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MAIN
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main(int argc, char** argv)
{
	if(argc == 3)
	{
		char* filename = argv[1];
		char* outputFilename = argv[2];

		Winners* winners = getWinnersFromFile(filename);
		if(winners == NULL)
		{
			return EXIT_FAILURE;
		}

		copyWinnersIntoFile(winners, outputFilename);

		destroyWinners(winners);
		winners = NULL;
		return EXIT_SUCCESS;
	}
	if(argc == 4)
	{
		if(!strcmp(argv[1], "--info"))
		{
			printf("Unkown argument\n");
			return EXIT_FAILURE;
		}
		uint16_t yearToFind = argv[2];
		char* inputFilename = argv[1];
		Winner* winnerFound= findWinnerOfYear(yearToFind, inputFilename);
		if(winnerFound == NULL)
		{
			printf("Year not found\n");
		 	return EXIT_FAILURE;
		}
		printWinner(winnerFound);
		return EXIT_SUCCESS;
	}

	printf("Arguments missing\n");
	return EXIT_FAILURE;
}
