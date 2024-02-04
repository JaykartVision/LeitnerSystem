#include "RBT.h"
#include "List.h"
#ifndef _CardStruct_H_
#define _CardStruct_H_

typedef struct FlashCard1 {
	char marker;
	char* frontSide;
	char* backSide;
}FlashCard1;

typedef struct Container1 {
	int frequency;
	Tree* flashCards;
}Container1;

typedef struct ClassContainers1 {
	int countCont;
	int countCard;
	int step;
	Container1** containers; /*arr: data: int frequency, Tree: key: int number, data: char marker, char* frontSide, char* backSide*/
}ClassContainers1;

void* InitClassContainers(int countCont);
void InitContainers(ClassContainers1* classContainers);

void* ReturnFrontSideFlashCard(FlashCard1* flashCard);
void* ReturnBackSideFlashCard(FlashCard1* flashCard);
void* ReturnMarkerFlashCard(FlashCard1* flashCard);
void* ReturnContainerPos(ClassContainers1* classContainers, int pos);
void* ReturnFrequencyPos(ClassContainers1* classContainers, int pos);
void* ReturnCountCont(ClassContainers1* classContainers);
void* ReturnCountCard(ClassContainers1* classContainers);
void* ReturnStep(ClassContainers1* classContainers);

int SizeContainer(ClassContainers1* classContainers, int pos);
int SizeContainers(ClassContainers1* classContainers);

void* InsertFlashCard(ClassContainers1* classContainers, int pos, void* flashCard, void* number);
void* InsertTextFlashCard(ClassContainers1* classContainers, int pos, char* frontSide, char* backSide, void* number);

char RemoveFlashCard(ClassContainers1* classContainers, int pos, void* number, char flag);

void ResetContainer(ClassContainers1* classContainers, int pos);
void ResetContainers(ClassContainers1* classContainers);

void FreeFlashCard(FlashCard1* flashCard);
void FreeContainers(ClassContainers1* classContainers);

void IterContainer(ClassContainers1* classContainers, int pos, void (*foreachFunc)(void* extraData1, void* extraData2, void* inputData, void* inputKey), void* extraData1, void* extraData2);

#endif