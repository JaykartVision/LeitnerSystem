#ifndef _GUI_H_
#define _GUI_H_

//program gui
void PrintText(char* text);
void PrintInt(int* digit);
void EnterChar(char* letter, char* text, int* extraData);
void EnterInt(int* digit, char* text, int* extraData);
void EnterString(char* string, char* text);

//debug gui
void PrintAllContainers(void* classContainers);
void PrintFrequency(void* classContainers);
void PrintSettings(void* classContainers);
void PrintContainer(void* classContainers, int pos);
void PrintFlashCard(void* extraData1, void* extraData2, void* inputData, void* inputKey);

#endif