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
	for (Winner* iWinner = winners->winners; iWinner < winners->winners + winners->nbWinner; iWinner++)
	{
		readWinner(iWinner, inputFile);
	}
	return winners;
}

void printWinnerIntoFile(Winner* winner, FILE* outputFile)
{
	fprintf(outputFile, "%"PRIu16";%s;%s\n", winner->year, winner->names, winner->works);
}

void printWinner(Winner* winner)
{
	printf("Winner(s) of year %"PRIu16": %s for their works in %s\n", winner->year, winner->names, winner->works);
}

void printWinners(Winners* winners, FILE* outputFile)
{
	// iteration over each winner of winners struct
	for (Winner* iWinner = winners->winners; iWinner < winners->winners + winners->nbWinner; iWinner++)
	{
		printWinnerIntoFile(iWinner, outputFile);
	}
}

void destroyWinners(Winners* winners)
{
	// iteration over each winner of winners struct
	for (Winner* iWinner = winners->winners; iWinner < winners->winners + winners->nbWinner; iWinner++)
	{
		free(iWinner->names);
		free(iWinner->works);
	}
	free(winners->winners);
	free(winners);
}

void sortWinners(Winners* winners)
{
	Winner temp;
	bool isSorted;
	do
	{
		isSorted = true;
		// iteration over each winner of winners struct
		for (Winner* iWinner = winners->winners; iWinner < winners->winners + winners->nbWinner - 1; iWinner++)
		{
			if (iWinner->year > (iWinner+1)->year)
			{
				isSorted = false;
				temp = *iWinner;
				*iWinner = *(iWinner+1);
				*(iWinner+1) = temp;
			}
		}
	} while (!isSorted);
}

// return the adress of corresponding winner, NULL if not found
Winner* findWinnerOfYear(uint16_t year, Winners* winners)
{
	// iteration over each winner of winners struct
	for (Winner* iWinner = winners->winners; iWinner < winners->winners + winners->nbWinner; iWinner++)
	{
		if (iWinner->year == year)
		{
			return iWinner;
		}
	}
	return NULL;
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
	// basic copy
	if(argc == 3)
	{
		char* inputFilename = argv[1];
		char* outputFilename = argv[2];

		Winners* winners = getWinnersFromFile(inputFilename);
		if(winners == NULL)
		{
			return EXIT_FAILURE;
		}

		copyWinnersIntoFile(winners, outputFilename);

		destroyWinners(winners);
		winners = NULL;
		return EXIT_SUCCESS;
	}

	// search for year
	if(argc == 4)
	{
		if(strcmp(argv[1], "--info"))
		{
			printf("Unkown argument: %s\n"
				"Try: --info\n", argv[1]);
			return EXIT_FAILURE;
		}
		uint16_t yearToFind = (uint16_t) strtoul(argv[2], NULL, 10); //convert char* to unsigned long
		char* inputFilename = argv[3];

		Winners* winners = getWinnersFromFile(inputFilename);

		Winner* winnerFound = findWinnerOfYear(yearToFind, winners);
		if(winnerFound == NULL)
		{
			printf("Year not found\n");
		 	return EXIT_FAILURE;
		}

		printWinner(winnerFound);

		destroyWinners(winners);
		return EXIT_SUCCESS;
	}

	// copy with sort
	if(argc == 5)
	{
		if(strcmp(argv[1], "--sort"))
		{
			printf("Unkown argument: %s\n"
				"Try: --sort\n", argv[1]);
			return EXIT_FAILURE;
		}

		if(strcmp(argv[2], "-o"))
		{
			printf("Unkown argument: %s\n"
				"Try: -o\n", argv[1]);
			return EXIT_FAILURE;
		}

		char* inputFilename = argv[4];
		char* outputFilename = argv[3];

		Winners* winners = getWinnersFromFile(inputFilename);
		if(winners == NULL)
		{
			return EXIT_FAILURE;
		}
		sortWinners(winners);
		copyWinnersIntoFile(winners, outputFilename);

		destroyWinners(winners);
		winners = NULL;
		return EXIT_SUCCESS;
	}

	printf("Arguments missing\n");
	return EXIT_FAILURE;
}
