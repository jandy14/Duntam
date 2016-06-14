#pragma once
#include"GameManager.h"
#include<string>

using namespace std;

class MapInfo
{
private:
	Room* targetRoom;
	string path;

	int CountFile();	//폴더안 파일 갯수
	void SetPath();		//파일 경로 설정
	void FillInList();	//리스트안에 맵내용 읽어서 넣어줌
public:
	~MapInfo() {}
	void SetRoom(Room * target);	//방 내용 세팅(랜덤하게)
	void SetRoom(Room * target, char * roomName);	//경로 지정
};