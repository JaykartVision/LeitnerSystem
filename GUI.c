#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "CardStruct.h"
#include "GUI.h"

void PrintText(char* text)
{
	printf("%s\n", text);
}
void PrintInt(int* digit)
{
    printf("%d\n", *digit);
}
void EnterChar(char* letter, char* text, int* extraData)
{
    if (extraData != NULL) printf("%s %d\n", text, *extraData);
    else printf("%s\n", text);
    char bufer = '0';
    if (scanf("%c", &bufer) != 1)
    {
        bufer = '0';
    }
    while (getchar() != '\n');
    *letter = bufer;
    printf("\n");
}
void EnterInt(int* digit, char* text, int* extraData)
{
    if (extraData != NULL) printf("%s %d\n", text, *extraData);
    else printf("%s\n", text);
    if (scanf_s("%d", digit) != 1)
    {
        *digit = -2147483647;
    }
    while (getchar() != '\n');
    printf("\n");
}
void EnterString(char* string, char* text)
{
    printf("%s\n", text);
    scanf("%s", string);
}

void PrintFrequency(void* classContainers)
{
    for (int i = 0; i < SizeContainers(classContainers); i++)
    {
        printf("Frequency pos %d count %d\n", i, *(int*)ReturnFrequencyPos(classContainers, i));
    }
}
void PrintSettings(void* classContainers)
{
    printf("CountCont %d CountCard %d Step %d\n", *(int*)ReturnCountCont(classContainers), *(int*)ReturnCountCard(classContainers), *(int*)ReturnStep(classContainers));
}
void PrintContainer(void* classContainers, int pos)
{
    IterContainer(classContainers, pos, PrintFlashCard, &pos, NULL);
}
void PrintFlashCard(void* extraData1, void* extraData2, void* inputData, void* inputKey)
{
    int pos = *(int*)extraData1;
    int number = *(int*)inputKey;
    FlashCard1* flashCard = inputData;
    printf("Container pos %d ", *(int*)extraData1);
    printf("Number %d ", *(int*)inputKey);
    printf("FrontSide %s ", (char*)ReturnFrontSideFlashCard(inputData));
    printf("BackSide %s ", (char*)ReturnBackSideFlashCard(inputData));
    printf("Marker %c\n", *(char*)ReturnMarkerFlashCard(inputData));
}
void PrintAllContainers(void* classContainers)
{
    PrintSettings(classContainers);
    PrintFrequency(classContainers);
    for (int i = 0; i < SizeContainers(classContainers); i++)
    {
        PrintContainer(classContainers, i);
    }
}