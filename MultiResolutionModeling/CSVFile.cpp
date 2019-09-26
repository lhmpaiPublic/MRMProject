// CSVFile.cpp
//

#include "stdafx.h"
#include "CSVFile.h"

CCSVFile::CCSVFile()
{
	infileLoad = false;
	outfileLoad = false;
}
CCSVFile::~CCSVFile()
{

}

bool CCSVFile::loadCSVFile(string fileName, LOADTYPE _loadType)
{
	bool b = false;
	loadType = _loadType;
	switch (loadType)
	{
	case WRITE:outfile.open(fileName.c_str());
		outfileLoad = outfile.fail() ? false : true;
		b = outfileLoad;
		break;
	case READ:
	default:infile.open(fileName.c_str());
		infileLoad = infile.fail() ? false : true;
		b = infileLoad;
		break;
	}
	return b;
}

bool CCSVFile::fileLoad(LOADTYPE _loadType)
{
	bool b = false;
	switch (loadType)
	{
	case WRITE: b = outfileLoad ? true : false;
		break;
	case READ:
	default: b = infileLoad ? true : false;
		break;
	}
	return b;
}

void CCSVFile::unloadCSVFile()
{
	switch (loadType)
	{
	case WRITE:outfile.close();
		break;
	case READ:
	default:infile.close();
		break;
	}

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