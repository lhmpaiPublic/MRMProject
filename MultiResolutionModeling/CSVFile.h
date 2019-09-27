#pragma once


class CCSVFile
{
public:
	CCSVFile();
	~CCSVFile();

public:
	//CSV open Type 정의
	enum LOADTYPE
	{
		NONELOAD = 0,
		READLOAD,
		WRITELOAD
	};
public:
	//CSV load stream 객체 생성(open 디폴트 타입 READ)
	bool loadCSVFile(string fileName, LOADTYPE _loadType = READLOAD);

	//CSV unload 객체 파괴
	bool unloadCSVFile();

	//CSV 파일이 load 되어 있나 검사
	bool fileLoad(LOADTYPE _loadType = READLOAD);

	//읽기 스트림 객체
	ifstream& inStream();
	
	//쓰기 스트림 객체
	ofstream& outStream();

	//읽기 스트림 객체로 읽어 오기(string 객체 리턴)
	static vector<string> csv_read_row(istream& file, char delimiter);

	//읽기 스트림 객체로 읽어 오기(int 객체 리턴)
	static vector<int> csv_read_row_int(istream& file, char delimiter);


private:
	//읽기 스트림 객체
	ifstream infile;
	//쓰기 스트림 객체
	ofstream outfile;
	//스트림 load 타입
	LOADTYPE loadType;
};