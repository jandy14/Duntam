#include"ReadMapInfo.h"
#include<io.h>
#include<sstream>
#include<iomanip>
#include<fstream>
#include"Block.h"
#include"Enemy.h"
#include"Thing.h"

list<string>* Split(string str, char delimiter); //문자열 나누기

int MapInfo::CountFile()	//C에서 쓰던 방법이라 나랑 좀 안맞다
{
	int count = 0;
	string pathName = this->path + "*.csv";
	const char* path = pathName.c_str();

	_finddata_t fd;
	long handle;
	int result = 1;

	handle = _findfirst(path,&fd);
	
	if (handle == -1)
		return 0;
	while (result != -1)
	{
		count++;
 		result = _findnext(handle, &fd);
	}
	_findclose(handle);
	return count;
}
void MapInfo::SetPath()
{
	this->path = "MapInfo/";
	if (this->targetRoom->IsDoor(UP))
		this->path += "1";
	else
		this->path += "0";
	if (this->targetRoom->IsDoor(DOWN))
		this->path += "1";
	else
		this->path += "0";
	if (this->targetRoom->IsDoor(LEFT))
		this->path += "1";
	else
		this->path += "0";
	if (this->targetRoom->IsDoor(RIGHT))
		this->path += "1";
	else
		this->path += "0";
	this->path += "/";

	int infoNum = random(CountFile());
	stringstream roomNum;
	roomNum << setw(2) << setfill('0') << infoNum;	// 00 01 02 ...
	this->path = this->path + roomNum.str() + ".csv";
}
void MapInfo::FillInList()
{
	ifstream input;
	do
	{
		input.open(this->path.c_str());
	} while (!(input.is_open()));

	//읽어서 넣어주기
	list<string>* lineinfo;
	string line;
	for (int y = 0; y < 30; y++)
	{
		getline(input, line);
		lineinfo = Split(line, ',');
		for (int x = 0; x < 50; x++, lineinfo->pop_front())
		{
			if (targetRoom->IsDoor(UP))
			{
				if ((x == 24 || x == 25) && y == 0)
					continue;
			}
			if (targetRoom->IsDoor(DOWN))
			{
				if ((x == 24 || x == 25) && y == 29)
					continue;
			}
			if (targetRoom->IsDoor(LEFT))
			{
				if ((y == 14 || y == 15) && x == 0)
					continue;
			}
			if (targetRoom->IsDoor(RIGHT))
			{
				if ((y == 14 || y == 15) && x == 49)
					continue;
			}

			switch (stoi(lineinfo->front()))
			{
			case 0:
				break;
			case 1:
				targetRoom->objectList.push_back(new Block(x, y));
				break;
			case 2:
				targetRoom->objectList.push_back(new BreakableBlock(x, y));
				break;
			case 10:
				targetRoom->objectList.push_back(new EnemyA(x, y));
				break;
			case 11:
				targetRoom->objectList.push_back(new EnemyB(x, y));
				break;
			case 12:
				targetRoom->objectList.push_back(new EnemyC(x, y));
				break;
			case 13:
				targetRoom->objectList.push_back(new EnemyD(x, y));
				break;
			case 14:
				targetRoom->objectList.push_back(new EnemyE(x, y));
				break;
			case 20:
				targetRoom->objectList.push_back(new AltarOfLuck(x, y));
				break;
			case 21:
				targetRoom->objectList.push_back(new BulletTrap(x, y, UP));
				break;
			case 22:
				targetRoom->objectList.push_back(new BulletTrap(x, y, DOWN));
				break;
			case 23:
				targetRoom->objectList.push_back(new BulletTrap(x, y, LEFT));
				break;
			case 24:
				targetRoom->objectList.push_back(new BulletTrap(x, y, RIGHT));
				break;
			}
		}
		delete lineinfo;
	}
	

	input.close();
}
void MapInfo::SetRoom(Room * target)
{
	this->targetRoom = target;
	SetPath();
	FillInList();
}
void MapInfo::SetRoom(Room * target, char * roomName)
{
	this->targetRoom = target;
	this->path = string(roomName);
	FillInList();
}

list<string>* Split(string str, char delimiter)	//문자열 나누기
{
	list<string>* internal = new list<string>();
	stringstream ss(str); // Turn the string into a stream.
	string tok;

	while (getline(ss, tok, delimiter)) {
		internal->push_back(tok);
	}

	return internal;
}