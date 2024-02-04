#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "CardStruct.h"

int CmpFuncInt(void* inputData1, void* inputData2)
{
	int* a = (int*)inputData1;
	int* b = (int*)inputData2;
	if (*a == *b)
	{
		return 2;
	}
	else
	{
		if (*a < *b)
			return 1;
		if (*a > *b)
			return 3;
	}
	return 0;
}

void* InitClassContainers(int countCont)
{
	ClassContainers1* classContainers = NULL;
	while (1)
	{
		classContainers = (ClassContainers1*)malloc(sizeof(ClassContainers1));
		if (classContainers != NULL) break;
	}
	classContainers->step = 0;
	classContainers->countCard = 0;
	classContainers->countCont = countCont;
	InitContainers(classContainers);
	return classContainers;
}
void InitContainers(ClassContainers1* classContainers)
{
	while (1)
	{
		classContainers->containers = (Container1**)malloc((classContainers->countCont) * sizeof(Container1*));
		if (classContainers->containers != NULL) break;
	}
	for (int i = 0; i < classContainers->countCont; i++)
	{
		while (1)
		{
			classContainers->containers[i] = (Container1*)malloc(sizeof(Container1));
			if (classContainers->containers[i] != NULL) break;
		}
		classContainers->containers[i]->frequency = 0;
		classContainers->containers[i]->flashCards = BstCreate(CmpFuncInt, sizeof(FlashCard1));
	}
	return;
}

void* ReturnFrontSideFlashCard(FlashCard1* flashCard)
{
	return flashCard->frontSide;
}
void* ReturnBackSideFlashCard(FlashCard1* flashCard)
{
	return flashCard->backSide;
}
void* ReturnMarkerFlashCard(FlashCard1* flashCard)
{
	return &flashCard->marker;
}
void* ReturnContainerPos(ClassContainers1* classContainers, int pos)
{
	return classContainers->containers[pos]->flashCards;
}
void* ReturnFrequencyPos(ClassContainers1* classContainers, int pos)
{
	return &classContainers->containers[pos]->frequency;
}
void* ReturnCountCont(ClassContainers1* classContainers)
{
	return &classContainers->countCont;
}
void* ReturnCountCard(ClassContainers1* classContainers)
{
	return &classContainers->countCard;
}
void* ReturnStep(ClassContainers1* classContainers)
{
	return &classContainers->step;
}

int SizeContainers(ClassContainers1* classContainers)
{
	return classContainers->countCont;
}
int SizeContainer(ClassContainers1* classContainers, int pos)
{
	return BstSize(classContainers->containers[pos]->flashCards);
}

void* InsertFlashCard(ClassContainers1* classContainers, int pos, void* flashCard, void* number)
{
	return BstInsert(classContainers->containers[pos]->flashCards, NULL, flashCard, number);
}
void* InsertTextFlashCard(ClassContainers1* classContainers, int pos, char* frontSide, char* backSide, void* number)
{
	FlashCard1 flashCard = {'0', NULL, NULL};
	while (1)
	{
		flashCard.frontSide = (char*)malloc((strlen(frontSide)+1) * sizeof(char));
		if (flashCard.frontSide != NULL) break;
	}
	while (1)
	{
		flashCard.backSide = (char*)malloc((strlen(backSide)+1) * sizeof(char));
		if (flashCard.backSide != NULL) break;
	}
	strcpy(flashCard.frontSide, frontSide);
	strcpy(flashCard.backSide, backSide);
	return BstInsert(classContainers->containers[pos]->flashCards, NULL, &flashCard, number);
}

char RemoveFlashCard(ClassContainers1* classContainers, int pos, void* number, char flag)
{
	void* flashCard = BstDelete(classContainers->containers[pos]->flashCards, number);
	if (flashCard == NULL) return 0;
	else
	{
		if (flag == 1) FreeFlashCard(flashCard);
		free(flashCard);
		return 1;
	}
}

void ResetContainer(ClassContainers1* classContainers, int pos)
{
	BstClear(classContainers->containers[pos]->flashCards, NULL);
}
void ResetContainers(ClassContainers1* classContainers)
{
	for (int i = 0; i < SizeContainers(classContainers); i++)
	{
		BstDestroy(classContainers->containers[i]->flashCards, FreeFlashCard);
		classContainers->containers[i]->flashCards = NULL;
		free(classContainers->containers[i]);
		classContainers->containers[i] = NULL;
	}
	free(classContainers->containers);
	classContainers->containers = NULL;
}

void FreeFlashCard(FlashCard1* flashCard)
{
	free(flashCard->frontSide);
	free(flashCard->backSide);
	flashCard->frontSide = NULL;
	flashCard->backSide = NULL;
}
void FreeContainers(ClassContainers1* classContainers)
{
	for (int i = 0; i < SizeContainers(classContainers); i++)
	{
		BstDestroy(classContainers->containers[i]->flashCards, FreeFlashCard);
		classContainers->containers[i]->flashCards = NULL;
		free(classContainers->containers[i]);
		classContainers->containers[i] = NULL;
	}
	free(classContainers->containers);
	classContainers->containers = NULL;
	free(classContainers);
}

void IterContainer(ClassContainers1* classContainers, int pos, void (*foreachFunc)(void* extraData1, void* extraData2, void* inputData, void* inputKey), void* extraData1, void* extraData2)
{
	BstForeachList(classContainers->containers[pos]->flashCards, foreachFunc, extraData1, extraData2);
}