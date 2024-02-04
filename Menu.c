#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Program.h"
#include "Menu.h"
#include "GUI.h"

void StartTest()
{
	void* containers = CreateContainers();
	SetFrequencyPos(containers);
	ReadFile(containers);
	PrintAllContainers(containers);
	Reboot(containers);
	PrintAllContainers(containers);
	DeleteCards(containers);
	PrintAllContainers(containers);
	ExitProgram(containers);
}
void Start()
{
	void* containers = CreateContainers();
	int run = 8;
	while (run != 0)
	{
		if (EmptyContainers(containers))
		{
			MenuEmptyCont(&run, containers);
		}
		else
		{
			if (EndLearning(containers)) PrintText("End of learning, all cards are in the last container");
			MenuFullCont(&run, containers);
		}
	}
}
void MenuEmptyCont(int* run, void* containers)
{
	EnterInt(run, "No cards in the container\nType 0 if you want to exit\nType 1 if you want to add cards using the console or type 2 using input file\nType 3 if you want to load saved sesion", NULL);
	switch (*run)
	{
		case 1: /*add from console*/
		{
			ReadConsole(containers);
			SetFrequencyPos(containers);
			PrintAllContainers(containers);
			*run = 8;
			break;
		}
		case 2: /*add from inputfile*/
		{
			ReadFile(containers);
			SetFrequencyPos(containers);
			PrintAllContainers(containers);
			*run = 8;
			break;
		}
		case 3: /*load session*/
		{
			LoadScene(containers);
			SetFrequencyPos(containers);
			PrintAllContainers(containers);
			*run = 8;
			break;
		}
		case 0:
		{
			ExitProgram(containers);
			*run = 0;
			break;
		}
		default:
		{
			*run = 8;
			PrintText("Invalid command, please, try again");
			break;
		}
	}
}
void MenuFullCont(int* run, void* containers)
{
	EnterInt(run, "Type 0 if you want to exit\nType 1 if you want to continue learning\nType 2 if you want to start over and move all the cards to the first container\nType 3 if you want to add cards using the console\nOr Type 4 using input file\nType 5 If you want to delete the selected cards by number\nType 6 If you want to save current session\nType 7 If you want to load saved session (the current session will be cleared!)", NULL);
	switch (*run)
	{
		case 0: /*exit*/
		{
			ExitProgram(containers);
			break;
		}
		case 1: /*learning*/
		{
			Learning(containers);
			//PrintAllContainers(containers);
			break;
		}
		case 2: /*reboot*/
		{
			Reboot(containers);
			PrintAllContainers(containers);
			break;
		}
		case 3: /*add from console*/
		{
			ReadConsole(containers);
			PrintAllContainers(containers);
			break;
		}
		case 4: /*add from inputfile*/
		{
			ReadFile(containers);
			PrintAllContainers(containers);
			break;
		}
		case 5: /*delete cards*/
		{
			DeleteCards(containers);
			PrintAllContainers(containers);
			break;
		}
		case 6: /*save session*/
		{
			SaveScene(containers);
			PrintAllContainers(containers);
			break;
		}
		case 7: /*load session*/
		{
			LoadScene(containers);
			PrintAllContainers(containers);
			break;
		}
		default:
		{
			*run = 8;
			PrintText("Invalid command, please, try again");
			break;
		}
	}
}