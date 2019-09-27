#pragma once


class CCSVFile
{
public:
	CCSVFile();
	~CCSVFile();

public:
	//CSV open Type ����
	enum LOADTYPE
	{
		NONELOAD = 0,
		READLOAD,
		WRITELOAD
	};
public:
	//CSV load stream ��ü ����(open ����Ʈ Ÿ�� READ)
	bool loadCSVFile(string fileName, LOADTYPE _loadType = READLOAD);

	//CSV unload ��ü �ı�
	bool unloadCSVFile();

	//CSV ������ load �Ǿ� �ֳ� �˻�
	bool fileLoad(LOADTYPE _loadType = READLOAD);

	//�б� ��Ʈ�� ��ü
	ifstream& inStream();
	
	//���� ��Ʈ�� ��ü
	ofstream& outStream();

	//�б� ��Ʈ�� ��ü�� �о� ����(string ��ü ����)
	static vector<string> csv_read_row(istream& file, char delimiter);

	//�б� ��Ʈ�� ��ü�� �о� ����(int ��ü ����)
	static vector<int> csv_read_row_int(istream& file, char delimiter);


private:
	//�б� ��Ʈ�� ��ü
	ifstream infile;
	//���� ��Ʈ�� ��ü
	ofstream outfile;
	//��Ʈ�� load Ÿ��
	LOADTYPE loadType;
};