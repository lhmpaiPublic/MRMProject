#pragma once


#define MAKEMIL4(a, b, c, d)      ((DWORD)(((BYTE)((DWORD_PTR)(a))) & 0xff)) | ((DWORD)(((BYTE)((DWORD_PTR)(b)) & 0xff) << 8 )) | ((DWORD)(((BYTE)((DWORD_PTR)(c)) & 0xff) << 16 )) | ((DWORD)(((BYTE)((DWORD_PTR)(d)) & 0xff) << 24 ))
#define MAKEMIL3(a, b, c)      ((DWORD)(((BYTE)((DWORD_PTR)(a))) & 0xff)) | ((DWORD)(((BYTE)((DWORD_PTR)(b)) & 0xff) << 8 )) | ((DWORD)(((BYTE)((DWORD_PTR)(c)) & 0xff) << 16 ))
#define MAKEMIL2(a, b)      ((DWORD)(((BYTE)((DWORD_PTR)(a))) & 0xff)) | ((DWORD)(((BYTE)((DWORD_PTR)(b)) & 0xff) << 8 ))
#define MAKEMIL1(a)      ((DWORD)(((BYTE)((DWORD_PTR)(a))) & 0xff))

typedef struct _SProductNum
{
	int retention; //������
	int accreditation;	//�ΰ���
	int key;	//���� Ű��
	int mappingNumber;	//���ι�ȣ
	CString strName;	//�ڻ��̸�
	bool compareMappingNumber(int mappingNum)
	{
		return mappingNumber == mappingNum;
	}
	bool compareKey(int _key)
	{
		return key == _key;
	}
	void modifyVal(_SProductNum val)
	{
		retention = val.retention;
		accreditation = val.accreditation;
		key = val.key;
		mappingNumber = val.mappingNumber;
		strName = val.strName;
	}
}SPrNu;

typedef struct _SProductClassKind
{
	void setVal(SPrNu val)
	{
		prNu.push_back(val);
	}

	void clearVal()
	{
		prNu.clear();
	}

	vector<SPrNu> getVal(int mappingNum)
	{
		vector<SPrNu> val;
		for (int i = 0; i < (int)prNu.size(); i++)
		{
			if(prNu[i].compareMappingNumber(mappingNum))
			{
				val.push_back(prNu[i]);
			}
		}
		return val;
	}

	void modifyVal(SPrNu val)
	{
		for (int i = 0; i < (int)prNu.size(); i++)
		{
			if(prNu[i].compareKey(val.key))
			{
				prNu[i].modifyVal(val);
			}
		}
	}

private:
	vector<SPrNu> prNu;
}SPrClKi;

//�Ҵ� ����
typedef struct _SProductSquad
{
	enum MILITARYBRANCH
	{
		MY0 = 0,				//�Ҵ뺻��
		MY1 = 1,				//1�д�
		MY2 = 2,				//2�д�
		MY3 = 3,				//3�д�
		MY_SIZE = 4
	};
	
	_SProductSquad()
	{
		mySPrSq.resize(MY_SIZE);
	}
	void setValSquad(DWORD mil, SPrClKi val)
	{
		mySPrSq[mil&0xff] = val;
	}
	SPrClKi getValSquad(DWORD mil)
	{
		return mySPrSq[mil&0xff];
	}

private:
	vector<SPrClKi> mySPrSq;
}SPrSq;

//�ߴ����
typedef struct _SProductPlatoon
{
	enum MILITARYBRANCH
	{
		MY0 = 0,				//�ߴ뺻��
		MY1 = 1,				//1�Ҵ�
		MY2 = 2,				//2�Ҵ�
		MY3 = 3,				//3�Ҵ�
		MY_SIZE = 4,
		LV1 = 0,				//1�Ҵ�д�
		LV2 = 1,				//2�Ҵ�д�
		LV3 = 2,				//3�Ҵ�д�
		LV_SIZE = 3
	};
	
	_SProductPlatoon()
	{
		lvSPrPl.resize(LV_SIZE);
		mySPrPl.resize(MY_SIZE);
	}
	void setValSquad(DWORD mil, SPrClKi val)
	{
		lvSPrPl[(mil>>8)&0xff].setValSquad(mil, val);
	}
	SPrClKi getValSquad(DWORD mil)
	{
		return lvSPrPl[(mil>>8)&0xff].getValSquad(mil);
	}
	void setValPlatoon(DWORD mil, SPrClKi val)
	{
		mySPrPl[mil&0xff] = val;
	}
	SPrClKi getValPlatoon(DWORD mil)
	{
		return mySPrPl[mil&0xff];
	}

private:
	vector<SPrSq> lvSPrPl;
	vector<SPrClKi> mySPrPl;
}SPrPl;

//������
typedef struct _SProductCompany
{
	enum MILITARYBRANCH
	{
		MY0 = 0,				//��뺻��
		MY1 = 1,				//1�ߴ�
		MY2 = 2,				//2�ߴ�
		MY3 = 3,				//3�ߴ�
		MY_SIZE = 4,
		LV1 = 0,				//1�ߴ�Ҵ�
		LV2 = 1,				//2�ߴ�Ҵ�
		LV3 = 2,				//3�ߴ�Ҵ�
		LV_SIZE = 3
	};

	_SProductCompany()
	{
		lvSPrCo.resize(LV_SIZE);
		mySPrCo.resize(MY_SIZE);
	}
	void setValSquad(DWORD mil, SPrClKi val)
	{
		lvSPrCo[(mil>>16)&0xff].setValSquad(mil, val);
	}
	SPrClKi getValSquad(DWORD mil)
	{
		return lvSPrCo[(mil>>16)&0xff].getValSquad(mil);
	}
	void setValPlatoon(DWORD mil, SPrClKi val)
	{
		lvSPrCo[(mil>>8)&0xff].setValPlatoon(mil, val);
	}
	SPrClKi getValPlatoon(DWORD mil)
	{
		return lvSPrCo[(mil>>8)&0xff].getValPlatoon(mil);
	}
	void setValCompany(DWORD mil, SPrClKi val)
	{
		mySPrCo[mil&0xff] = val;
	}
	SPrClKi getValCompany(DWORD mil)
	{
		return mySPrCo[mil&0xff];
	}

private:
	vector<SPrPl> lvSPrCo;
	vector<SPrClKi> mySPrCo;
}SPrCo;

//UNIT Type ����
typedef struct _SProductBattalion
{
	enum MILITARYBRANCH
	{
		MY0 = 0,				//���
		MY_SIZE = 1,
		LV1 = 0,				//�������
		LV_SIZE = 1
	};
	enum MODELTYPE
	{
		MTLOW = 0,				//LOW ��
		MTHI = 1,				//HI ��
		MT_SIZE
	};
	enum PRODUCTTYPE
	{
		TY0 = 0,				//����
		TY1 = 1,				//�������(ȭ��)
		TY2 = 2,				//�����������
		TY3 = 3,				//����ǰ
		PROD_SIZE
	};
	enum COMBATANT
	{
		INFANTRY = 0,	//����
		ARMORED = 1,	//����
		ARTILLERY = 2,	//����
		COMBATANT_SIZE = 3,
	};
	_SProductBattalion()
	{
		lvSPrBa.resize(LV_SIZE);
		mySPrBa.resize(MY_SIZE);
	}

	void setValSquad(DWORD mil, SPrClKi val)
	{
		lvSPrBa[(mil>>24)&0xff].setValSquad(mil, val);
	}
	SPrClKi getValSquad(DWORD mil)
	{
		return lvSPrBa[(mil>>24)&0xff].getValSquad(mil);
	}

	void setValPlatoon(DWORD mil, SPrClKi val)
	{
		lvSPrBa[(mil>>16)&0xff].setValPlatoon(mil, val);
	}
	SPrClKi getValPlatoon(DWORD mil)
	{
		return lvSPrBa[(mil>>16)&0xff].getValPlatoon(mil);
	}

	void setValCompany(DWORD mil, SPrClKi val)
	{
		lvSPrBa[(mil>>8)&0xff].setValCompany(mil, val);
	}
	SPrClKi getValCompany(DWORD mil)
	{
		return lvSPrBa[(mil>>8)&0xff].getValCompany(mil);
	}

	void setValBattalion(DWORD mil, SPrClKi val)
	{
		mySPrBa[mil&0xff] = val;
	}
	SPrClKi getValBattalion(DWORD mil)
	{
		return mySPrBa[mil&0xff];
	}
private:
	vector<SPrCo> lvSPrBa;
	vector<SPrClKi> mySPrBa;
}SPrBa;

typedef CAtlMap<SPrBa::PRODUCTTYPE, SPrBa> SPrBaMap;


typedef struct _SProductValue
{
	int accreditation;	//�ΰ���
	int key;	//���� Ű��
	CString strName;	//�ڻ��̸�
}SPrVa;

typedef struct _SProductMapping
{
	enum COMBATANTCLASS
	{
		SQUAD = 0,		//�д�
		PLATOON_CENTER = 1,	//�Ҵ뺻��
		PLATOON = 2,	//�Ҵ�
		COMPANY_CENTER = 3,	//�ߴ뺻��
		COMPANY = 4,	//�ߴ�
		BATTALION_CENTER = 5,	//��뺻��
		BATTALION = 6,	//���
		COMBATANTCLASS_SIZE = 7 //ũ��
	};
	enum MODELTYPE
	{
		MTLOW = 0,				//LOW ��
		MTHI = 1,				//HI ��
		MT_SIZE
	};
	enum PRODUCTTYPE
	{
		TY0 = 0,				//����
		TY1 = 1,				//�������(ȭ��)
		TY2 = 2,				//�����������
		TY3 = 3,				//����ǰ
		PROD_SIZE
	};

	void setVal(MODELTYPE modelType, COMBATANTCLASS combatClass, SPrVa val)
	{
		prVa[modelType][combatClass].push_back(val);
	}

	void clearVal()
	{
		for (int i = 0; i < (int)MT_SIZE; i++)
		{
			for (int j = 0; j < (int)COMBATANTCLASS_SIZE; j++)
			{
				prVa[i][j].clear();
			}
		}
	}
	vector<SPrVa> prVa[MT_SIZE][COMBATANTCLASS_SIZE];
}SPrMa;

//int : ����Ű(����), SPrMa : �����ڻ�(low, hi)
typedef CAtlMap<SPrMa::PRODUCTTYPE, SPrMa> ProductMappingVal;