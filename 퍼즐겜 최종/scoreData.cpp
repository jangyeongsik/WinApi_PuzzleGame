#include "stdafx.h"
#include "scoreData.h"

void scoreData::saveData(string fileName, int score)
{
	HANDLE file;
	DWORD write;

	file = CreateFile(fileName.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, to_string(score).c_str(), to_string(score).size(), &write, NULL);

	CloseHandle(file);

}

int scoreData::loadData(string fileName)
{
	HANDLE file;
	DWORD read;

	file = CreateFile(fileName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	char str[128];


	ReadFile(file, str, 126, &read, NULL);
	


	CloseHandle(file);

	return 	atoi(str);
}
