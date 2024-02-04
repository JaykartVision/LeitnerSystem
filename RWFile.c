#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "CardStruct.h"
#include "RWFile.h"
#include "GUI.h"

int WriteScene(void* classContainers)
{
	char fileName[64];
	EnterString(&fileName, "Enter fileName scene:");
	FILE* file = fopen(fileName, "w");
	int password = 25268;
	fwrite(&password, sizeof(int), 1, file);
	fwrite(ReturnCountCont(classContainers), sizeof(int), 1, file);
	fwrite(ReturnCountCard(classContainers), sizeof(int), 1, file);
	fwrite(ReturnStep(classContainers), sizeof(int), 1, file);
	for (int i = 0; i < SizeContainers(classContainers); i++)
	{
		IterContainer(classContainers, i, WriteFlashCard, file, NULL);
		fputc((char)1, file);
		fwrite(ReturnFrequencyPos(classContainers, i), sizeof(int), 1, file);
	}
	fclose(file);
	return 1;
}
int ReadScene(void* classContainers)
{
	char fileName[64];
	FILE* file = NULL;
	while (1)
	{
		EnterString(&fileName, "Enter fileName scene:");
		if (fileName == "000") return 0;
		fopen_s(&file, fileName, "r");
		if (file != NULL) break;
		else PrintText("The file cannot be opened");
	}
	int password = 0;
	fread(&password, sizeof(int), 1, file);
	if ((!feof(file)) && (password == 25268))
	{
		ResetContainers(classContainers);
		InitContainers(classContainers);
		fread(ReturnCountCont(classContainers), sizeof(int), 1, file);
		fread(ReturnCountCard(classContainers), sizeof(int), 1, file);
		fread(ReturnStep(classContainers), sizeof(int), 1, file);
		for (int i = 0; i < SizeContainers(classContainers); i++)
		{
			while (1)
			{
				char flag = 0;
				fread(&flag, sizeof(char), 1, file);
				if (flag == (char)1) break;
				fseek(file, -1, SEEK_CUR);
				int number = 0;
				char frontSide[256] = " ";
				char backSide[256] = " ";
				fgets(&frontSide, 256, file);
				fgets(&backSide, 256, file);
				fread(&number, sizeof(int), 1, file);
				frontSide[strcspn(frontSide, "\n")] = '\0';
				backSide[strcspn(backSide, "\n")] = '\0';
				InsertTextFlashCard(classContainers, i, &frontSide, &backSide, &number);
			}
			fread(ReturnFrequencyPos(classContainers, i), sizeof(int), 1, file);
		}
		PrintAllContainers(classContainers);
		return 1;
	}
	else return 0;
	fclose(file);
}
void WriteFlashCard(void* extraData1, void* extraData2, void* inputData, void* inputKey)
{
	fputs(ReturnFrontSideFlashCard(inputData), extraData1);
	fputc('\n', extraData1);
	fputs(ReturnBackSideFlashCard(inputData), extraData1);
	fputc('\n', extraData1);
	fwrite(inputKey, sizeof(int), 1, extraData1);
}