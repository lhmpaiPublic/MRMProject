// CSVFile.cpp
//

#include "stdafx.h"
#include "CSVFile.h"

CCSVFile::CCSVFile()
{
	loadType=NONELOAD;
}
CCSVFile::~CCSVFile()
{

}

bool CCSVFile::loadCSVFile(string fileName, LOADTYPE _loadType)
{
	bool b = false;
	//Load 타입
	loadType = _loadType;
	//Load 타입이 현재와 같다면..
	if(fileLoad(_loadType))
	{
		unloadCSVFile();
	}
	//Load 타입에 맞게 스트림 생성
	switch (_loadType)
	{
	case WRITELOAD: outfile.open(fileName.c_str());
		b = true;
		break;
	case READLOAD: infile.open(fileName.c_str());
		b = true;
		break;
	case NONELOAD: b = unloadCSVFile();
	default:
		break;
	}
	return b;
}

bool CCSVFile::fileLoad(LOADTYPE _loadType)
{
	bool b = false;
	switch (_loadType)
	{
	case WRITELOAD: b = (WRITELOAD == loadType) ? true : false;
		break;
	case READLOAD:  b = (READLOAD == loadType) ? true : false;
		break;
	case NONELOAD:
	default: b = (NONELOAD == loadType) ? true : false;
		break;
	}
	return b;
}

bool CCSVFile::unloadCSVFile()
{
	bool b = false;
	switch (loadType)
	{
	case WRITELOAD:outfile.close();
		b = true;
		break;
	case READLOAD:infile.close();
		b = true;
		break;
	case NONELOAD:
	default: b = false;
		break;
	}
	loadType = NONELOAD;
	return b;
}

ifstream& CCSVFile::inStream()
{
	return infile;
}

ofstream& CCSVFile::outStream()
{
	return outfile;
}


vector<int> CCSVFile::csv_read_row_int(istream& file, char delimiter)
{
	stringstream ss;
	bool inquotes = false;
	vector<int> row;
	row.clear();
	while (file.good())
	{
		char c = file.get();
		if (!inquotes && c == '"')
		{
			inquotes = true;
		}
		else if (inquotes && c == '"') {
			if (file.peek() == '"')
			{
				ss << (char)file.get();
			}
			else
			{
				inquotes = false;
			}
		}
		else if (!inquotes && c == delimiter)
		{
			row.push_back(strtoul(ss.str().c_str(), NULL, 10));
			ss.str("");
		}
		else if (!inquotes && (c == '\r' || c == '\n'))
		{
			if (file.peek() == '\n') { file.get(); }
			if ('#' == ss.get())
			{
				ss.clear();
				continue;
			}
			row.push_back(strtoul(ss.str().c_str(), NULL, 10));
			return row;
		}
		else
		{
			ss << c;
		}

	}
	return row;
}

vector<string> CCSVFile::csv_read_row(istream& file, char delimiter)
{
	stringstream ss;
	bool inquotes = false;
	vector<string> row;
	row.clear();
	while (file.good())
	{
		char c = file.get();
		if (!inquotes && c == '"')
		{
			inquotes = true;
		}
		else if (inquotes && c == '"') {
			if (file.peek() == '"')
			{
				ss << (char)file.get();
			}
			else
			{
				inquotes = false;
			}
		}
		else if (!inquotes && c == delimiter)
		{
			row.push_back(ss.str());
			ss.str("");
		}
		else if (!inquotes && (c == '\r' || c == '\n'))
		{
			if (file.peek() == '\n') { file.get(); }
			if ('#' == ss.get())
			{
				ss.clear();
				continue;
			}
			row.push_back(ss.str());
			return row;
		}
		else
		{
			ss << c;
		}

	}
	return row;
}