#include"ReadMapInfo.h"
#include<io.h>
#include<sstream>
#include<iomanip>
#include<fstream>

int MapInfo::CountFile()	//C에서 쓰던 방법이라 나랑 좀 안맞다
{
	int count = 0;
	string pathName = this->path + "*.*";
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
}
void MapInfo::FillInList()
{
	ifstream input;
	do
	{
		int infoNum = random(CountFile());	//랜덤한 방번호
		stringstream roomNum;
		roomNum << setw(2) << setfill('0') << infoNum;	// 00 01 02 ...
		string pathName = this->path + roomNum.str();
		input.open(pathName.c_str());
	} while (!(input.is_open()));

	//읽어서 넣어주기
	//targetRoom->objectList.push_back(new Player(3,3));

	input.close();
}
void MapInfo::SetRoom(Room * target)
{
	this->targetRoom = target;
	SetPath();
	FillInList();
}