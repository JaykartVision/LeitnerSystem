#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Program.h"
#include "CardStruct.h"
#include "GUI.h"
#include "RWFile.h"

void* CreateContainers()
{
	int countCont = 0;
	while (1)
	{
		EnterInt(&countCont, "Enter the quantity of containers more than 1:", NULL);
		if (countCont > 1) break;
	}
	return InitClassContainers(countCont);
}
void SetFrequencyPos(void* classContainers)
{
	for (int i = 0; i < SizeContainers(classContainers); i++)
	{
		EnterInt(ReturnFrequencyPos(classContainers, i), "Enter the repetition frequency of the container pos", &i);
	}
}
void ElementDistrib(void* extraData1, void* extraData2, void* inputData, void* inputKey)
{
	if (ChangeMarker('0', inputData) == '0')
	{
		int numberContainer = *(int*)extraData2;
		PrintText("Question");
		PrintInt(inputKey);
		PrintText(ReturnFrontSideFlashCard(inputData));
		char answer[256];
		EnterString(&answer, "Print answer:");
		PrintText("Your answer is");
		PrintText(&answer);
		if (strcmp(answer, ReturnBackSideFlashCard(inputData)) == 0)
		{
			PrintText("Correct");
			if (numberContainer < (SizeContainers(extraData1) - 1))
			{
				int step = *(int*)ReturnStep(extraData1);
				int freq = *(int*)ReturnFrequencyPos(extraData1, numberContainer + 1);
				if (step % freq == 0)
				{
					ChangeMarker('1', inputData);
				}
				InsertFlashCard(extraData1, numberContainer + 1, inputData, inputKey);
				RemoveFlashCard(extraData1, numberContainer, inputKey, 0);
				PrintText("Move Right\n");
			}
		}
		else
		{
			PrintText("Wrong. Correct answer is");
			PrintText(ReturnBackSideFlashCard(inputData));
			if (numberContainer > 0)
			{
				InsertFlashCard(extraData1, numberContainer - 1, inputData, inputKey);
				RemoveFlashCard(extraData1, numberContainer, inputKey, 0);
				PrintText("Move Left");
			}
		}
		PrintText(" ");
	}
}
char ChangeMarker(char flag, void* flashCard)
{
	if (flag == '0')
	{
		if (*(char*)ReturnMarkerFlashCard(flashCard) == '1') 
		{
			*(char*)ReturnMarkerFlashCard(flashCard) = '0';
			return '1';
		}
		if (*(char*)ReturnMarkerFlashCard(flashCard) == '0') 
		{
			return *(char*)ReturnMarkerFlashCard(flashCard);
		}
	}
	else 
	{
		*(char*)ReturnMarkerFlashCard(flashCard) = '1';
		return ' ';
	}
	return ' ';
}
void ReadFile(void* classContainers)
{
	PrintText("Each card has a unique key equal to the order of insertion");
	PrintText("The file should be presented as\nfrontSide\nbackSide\nfrontSide\nbackSide\nfrontSide\nbackSide\nand more");
	char* fileName[64];
	FILE* inputFile = NULL;
	while (1)
	{
		EnterString(&fileName, "Enter fileName:");
		fopen_s(&inputFile, fileName, "r");
		if (inputFile != NULL) break;
		else PrintText("The file cannot be opened");
	}
	if (inputFile == NULL) return;
	while (!feof(inputFile))
	{ 
		char frontSide[256] = " ";
		char backSide[256] = " ";
		fgets(&frontSide, 256, inputFile);
		fgets(&backSide, 256, inputFile);
		frontSide[strcspn(frontSide, "\n")] = '\0';
		backSide[strcspn(backSide, "\n")] = '\0';
		InsertTextFlashCard(classContainers, 0, &frontSide, &backSide, ReturnCountCard(classContainers));
		*(int*)ReturnCountCard(classContainers) = *(int*)ReturnCountCard(classContainers) + 1;
	}
	fclose(inputFile);
}
void ReadConsole(void* classContainers)
{
	PrintText("Each card has a unique key equal to the order of insertion");
	PrintText("Enter the frontSide and backSide cards, then enter 000:");
	while (1)
	{
		char frontSide[256] = " ";
		char backSide[256] = " ";
		fgets(frontSide, 256, stdin);
		frontSide[strcspn(frontSide, "\n")] = '\0';
		if (strcmp(frontSide, "000") == 0) break;
		fgets(backSide, 256, stdin);
		backSide[strcspn(backSide, "\n")] = '\0';
		PrintText("frontSide backSide number");
		printf("%s %s %d\n", frontSide, backSide, *(int*)ReturnCountCard(classContainers));
		InsertTextFlashCard(classContainers, 0, &frontSide, &backSide, ReturnCountCard(classContainers));
		*(int*)ReturnCountCard(classContainers) = *(int*)ReturnCountCard(classContainers) + 1;
	}
}
void DeleteCards(void* classContainers)
{
	int key = -1;
	while (1)
	{
		EnterInt(&key, "Enter the number of the item to be deleted or -1 to exit:", NULL);
		if (key == -1)
		{
			break;
		}
		else
		{
			char flag = 0;
			for (int i = 0; (i < SizeContainers(classContainers))&&(flag==0); i++)
			{
				flag = RemoveFlashCard(classContainers, i, &key, 1);
			}
			if (flag == 1)
			{
				printf("The Card key %d was deleted\n", key);
				*(int*)ReturnCountCard(classContainers) = *(int*)ReturnCountCard(classContainers) - 1;
			}
			else
			{
				printf("Card %d was not found\n", key);
			}
		}
	}
}
void Reboot(void* classContainers)
{
	EnterInt(ReturnFrequencyPos(classContainers, 0), "Enter the repetition frequency of the 1 container:", NULL);
	for (int i = 1; i < SizeContainers(classContainers); i++)
	{
		IterContainer(classContainers, i, BstInsert, ReturnContainerPos(classContainers, 0), NULL);
		ResetContainer(classContainers, i);
		EnterInt(ReturnFrequencyPos(classContainers, i), "Enter the repetition frequency of the container", &i);
	}
	*(int*)ReturnStep(classContainers) = 0;
	printf("The reboot has been completed\n");
}
void Learning(void* classContainers)
{
	for (int i = 0; i < SizeContainers(classContainers); i++)
	{
		int step = *(int*)ReturnStep(classContainers);
		int freq = *(int*)ReturnFrequencyPos(classContainers, i);
		if (step%freq==0)
		{
			PrintText("Print of the container");
			PrintInt(&i);
			IterContainer(classContainers, i, ElementDistrib, classContainers, &i);
		}
	}
	*(int*)ReturnStep(classContainers) = *(int*)ReturnStep(classContainers) + 1;
}
int EmptyContainers(void* classContainers)
{
	int count = 0;
	for (int i = 0; i < SizeContainers(classContainers); i++)
	{
		if (SizeContainer(classContainers, i) > 0) return 0;
	}
	return 1;
}
void LoadScene(void* classContainers)
{
	if (ReadScene(classContainers)) PrintText("The saved session has been uploaded");
	else PrintText("Error load scene");
}
void SaveScene(void* classContainers)
{
	WriteScene(classContainers);
	PrintText("The current session has been saved");
}
int EndLearning(void* classContainers)
{
	if (SizeContainer(classContainers, (SizeContainers(classContainers) - 1)) != 0)
	{
		for (int i = 0; i < (SizeContainers(classContainers) - 1); i++)
		{
			if (SizeContainer(classContainers, i) != 0) return 0;
		}
		return 1;
	}
	else return 0;
}
void ExitProgram(void* classContainers)
{
	PrintText("Shutting down");
	FreeContainers(classContainers);
}