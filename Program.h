#ifndef _Program_H_
#define _Program_H_

void* CreateContainers();
void SetFrequencyPos(void* classContainers);
void ElementDistrib(void* extraData1, void* extraData2, void* inputData, void* inputKey);
char ChangeMarker(char flag, void* flashCard);
void ReadFile(void* classContainers);
void ReadConsole(void* classContainers);
void DeleteCards(void* classContainers);
void Reboot(void* classContainers);
void Learning(void* classContainers);
int EmptyContainers(void* classContainers);
void LoadScene(void* classContainers);
void SaveScene(void* classContainers);
int EndLearning(void* classContainers);
void ExitProgram(void* classContainers);

#endif