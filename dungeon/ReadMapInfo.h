#pragma once
#include"GameManager.h"
#include<string>

using namespace std;

class MapInfo
{
private:
	Room* targetRoom;
	string path;

	int CountFile();
	void SetPath();
	void FillInList();
public:
	void SetRoom(Room * target);
	void SetRoom(Room * target, char * roomName);
};