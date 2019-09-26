#pragma once


class CCSVFile
{
public:
	CCSVFile();
	~CCSVFile();

public:
	enum LOADTYPE
	{
		READ = 0,
		WRITE = 1
	};
public:

	bool loadCSVFile(string fileName, LOADTYPE _loadType = READ);

	void unloadCSVFile();

	bool fileLoad(LOADTYPE _loadType = READ);

	ifstream& inStream();
	
	ofstream& outStream();

	static vector<string> csv_read_row(istream& file, char delimiter);

	static vector<int> csv_read_row_int(istream& file, char delimiter);


private:
	ifstream infile;
	bool infileLoad;
	ofstream outfile;
	bool outfileLoad;
	LOADTYPE loadType;
};