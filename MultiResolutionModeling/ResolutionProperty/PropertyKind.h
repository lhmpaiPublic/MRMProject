#pragma once


#define MAKEMIL4(a, b, c, d)      ((DWORD)(((BYTE)((DWORD_PTR)(a))) & 0xff)) | ((DWORD)(((BYTE)((DWORD_PTR)(b)) & 0xff) << 8 )) | ((DWORD)(((BYTE)((DWORD_PTR)(c)) & 0xff) << 16 )) | ((DWORD)(((BYTE)((DWORD_PTR)(d)) & 0xff) << 24 ))
#define MAKEMIL3(a, b, c)      ((DWORD)(((BYTE)((DWORD_PTR)(a))) & 0xff)) | ((DWORD)(((BYTE)((DWORD_PTR)(b)) & 0xff) << 8 )) | ((DWORD)(((BYTE)((DWORD_PTR)(c)) & 0xff) << 16 ))
#define MAKEMIL2(a, b)      ((DWORD)(((BYTE)((DWORD_PTR)(a))) & 0xff)) | ((DWORD)(((BYTE)((DWORD_PTR)(b)) & 0xff) << 8 ))
#define MAKEMIL1(a)      ((DWORD)(((BYTE)((DWORD_PTR)(a))) & 0xff))

typedef struct _SProductModelType
{
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

	static CString strPRODUCTTYPE(PRODUCTTYPE em)
	{
		CString str = _T("");
		switch(em)
		{
		case TY0: str = _T("����");
			break;
		case TY1: str = _T("�������(ȭ��)");
			break;
		case TY2: str = _T("�����������");
			break;
		case TY3: str = _T("����ǰ");
			break;
		default:
			break;
		}
		return str;
	}

	static PRODUCTTYPE indexPRODUCTTYPE(int idx)
	{
		PRODUCTTYPE em = TY0;
		switch(idx)
		{
		case 0: em = TY0;
			break;
		case 1: em = TY1;
			break;
		case 2: em = TY2;
			break;
		case 3: em = TY3;
			break;
		default:
			break;
		}
		return em;
	}

	static vector<CString> strPRODUCTTYPE()
	{
		vector<CString> strEm;
		strEm.clear();
		strEm.push_back(_T("����"));
		strEm.push_back(_T("�������(ȭ��)"));
		strEm.push_back(_T("�����������"));
		strEm.push_back(_T("����ǰ"));
		return strEm;
	}

	static CString strCOMBATANT(COMBATANT em)
	{
		CString str = _T("");
		switch(em)
		{
		case INFANTRY: str = _T("����");
			break;
		case ARMORED: str = _T("����");
			break;
		case ARTILLERY: str = _T("����");
			break;
		default:
			break;
		}
		return str;
	}

	static COMBATANT indexCOMBATANT(int idx)
	{
		COMBATANT em = INFANTRY;
		switch(idx)
		{
		case 0: em = INFANTRY;
			break;
		case 1: em = ARMORED;
			break;
		case 2: em = ARTILLERY;
			break;
		default:
			break;
		}
		return em;
	}


	static vector<CString> strCOMBATANT()
	{
		vector<CString> strEm;
		strEm.clear();
		strEm.push_back(_T("����"));
		strEm.push_back(_T("����"));
		strEm.push_back(_T("����"));
		return strEm;
	}

	static CString strCOMBATANTCLASS(COMBATANTCLASS em)
	{
		CString str = _T("");
		switch(em)
		{
		case PLATOON: str = _T("�Ҵ�");
			break;
		case COMPANY: str = _T("�ߴ�");
			break;
		case BATTALION: str = _T("���");
			break;
		default:
			break;
		}
		return str;
	}

	static COMBATANTCLASS indexCOMBATANTCLASS(int idx, COMBATANT combat)
	{
		COMBATANTCLASS em = PLATOON;
		if (ARMORED == combat)
		{
			switch(idx)
			{
			case 0: em = COMPANY;
				break;
			case 1: em = BATTALION;
				break;
			default:
				break;
			}
		}
		else if (ARTILLERY == combat)
		{
			switch(idx)
			{
			case 0: em = BATTALION;
				break;
			default:
				break;
			}
		}
		else
		{
			switch(idx)
			{
			case 0: em = PLATOON;
				break;
			case 1: em = COMPANY;
				break;
			case 2: em = BATTALION;
				break;
			default:
				break;
			}
		}

		return em;
	}


	static vector<CString> strCOMBATANTCLASS(COMBATANT combat)
	{
		vector<CString> strEm;
		strEm.clear();
		if (ARMORED == combat)
		{
			strEm.push_back(_T("�ߴ�"));
			strEm.push_back(_T("���"));
		}
		else if (ARTILLERY == combat)
		{
			strEm.push_back(_T("���"));
		}
		else
		{
			strEm.push_back(_T("�Ҵ�"));
			strEm.push_back(_T("�ߴ�"));
			strEm.push_back(_T("���"));
		}
		return strEm;
	}

}SPrMoTy;

//����Ű, ����Ű(LOW, HI �и�)
typedef CAtlMap<int, vector<int> > ProductKeyMap;

typedef struct _SProductMappKey
{
	void setVal(SPrMoTy::MODELTYPE moType, int mappKey, int proKey)
	{
		if(SPrMoTy::MTLOW ==  moType)
		{
			ProductKeyMap::CPair* pair = lowModel.Lookup(mappKey);
			if(pair != NULL)
			{
				pair->m_value.push_back(proKey);
			}
			else
			{
				vector<int> val;
				val.push_back(proKey);
				lowModel.SetAt(mappKey, val);
			}
		}
		else
		{
			ProductKeyMap::CPair* pair = hiModel.Lookup(mappKey);
			if(pair != NULL)
			{
				pair->m_value.push_back(proKey);
			}
			else
			{
				vector<int> val;
				val.push_back(proKey);
				hiModel.SetAt(mappKey, val);
			}
		}		
	}

	vector<int> getMappKey(SPrMoTy::MODELTYPE moType)
	{
		vector<int> keyVal;
		if(SPrMoTy::MTLOW ==  moType)
		{
			ProductKeyMap::CPair* pair = NULL;
			POSITION pos = lowModel.GetStartPosition();
			while(pos)
			{
				pair = lowModel.GetNext(pos);
				keyVal.push_back(pair->m_key);
			}
		}
		else
		{
			ProductKeyMap::CPair* pair = NULL;
			POSITION pos = hiModel.GetStartPosition();
			while(pos)
			{
				pair = hiModel.GetNext(pos);
				keyVal.push_back(pair->m_key);
			}
		}
		sort(keyVal.begin(), keyVal.end());
		return keyVal;
	}
private:
	ProductKeyMap lowModel;
	ProductKeyMap hiModel;
}SPrMaKe;

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

typedef CAtlMap<SPrMoTy::PRODUCTTYPE, SPrBa> SPrBaMap;


typedef struct _SProductValue
{
	int accreditation;	//�ΰ���
	int key;		//���� Ű��
	int mappKey;	//���� Ű
	CString strName;	//�ڻ��̸�
	bool compareMappKey(int mappingNum)
	{
		return mappKey == mappingNum;
	}
	bool compareKey(int _key)
	{
		return key == _key;
	}

	string strLogVal()
	{
		std::stringstream stm;
		stm << "�ΰ��� : " << accreditation << "	"
			<< "���� Ű�� : " << key << "	"
			<< "���� Ű : " << mappKey << "	"
			<< "�ڻ��̸� : " << CStringA(strName) << "	";
		return stm.str();
	}
}SPrVa;

typedef struct _SProductMapping
{
	void setVal(SPrMoTy::MODELTYPE modelType, SPrMoTy::COMBATANTCLASS combatClass, SPrVa val)
	{
		prVa[modelType][combatClass].push_back(val);
	}

	void clearVal()
	{
		for (int i = 0; i < (int)SPrMoTy::MT_SIZE; i++)
		{
			for (int j = 0; j < (int)SPrMoTy::COMBATANTCLASS_SIZE; j++)
			{
				prVa[i][j].clear();
			}
		}
	}

	vector<vector<SPrVa> > getVal(int mappingNum, SPrMoTy::COMBATANTCLASS combatClass)
	{
		vector<vector<SPrVa> > valvec2;
		vector<SPrVa> val;
		val.clear();
		for (int i = 0; i < (int)prVa[SPrMoTy::MTLOW][combatClass].size(); i++)
		{
			if(prVa[SPrMoTy::MTLOW][combatClass][i].compareMappKey(mappingNum))
			{
				val.push_back(prVa[SPrMoTy::MTLOW][combatClass][i]);
			}
		}
		valvec2.push_back(val);
		val.clear();
		for (int i = 0; i < (int)prVa[SPrMoTy::MTHI][combatClass].size(); i++)
		{
			if(prVa[SPrMoTy::MTHI][combatClass][i].compareMappKey(mappingNum))
			{
				val.push_back(prVa[SPrMoTy::MTHI][combatClass][i]);
			}
		}
		valvec2.push_back(val);
		return valvec2;
	}

	vector<SPrVa> getVal(int mappingNum, SPrMoTy::COMBATANTCLASS combatClass, SPrMoTy::MODELTYPE modelType)
	{
		vector<SPrVa> val;
		val.clear();
		for (int i = 0; i < (int)prVa[modelType][combatClass].size(); i++)
		{
			if(prVa[modelType][combatClass][i].compareMappKey(mappingNum))
			{
				val.push_back(prVa[modelType][combatClass][i]);
			}
		}
		return val;
	}

	SPrVa getValKey(int key, SPrMoTy::COMBATANTCLASS combatClass, SPrMoTy::MODELTYPE modelType)
	{
		SPrVa val;
		for (int i = 0; i < (int)prVa[modelType][combatClass].size(); i++)
		{
			if(prVa[modelType][combatClass][i].compareKey(key))
			{
				val = prVa[modelType][combatClass][i];
				break;
			}
		}
		return val;
	}

	vector<SPrVa> prVa[SPrMoTy::MT_SIZE][SPrMoTy::COMBATANTCLASS_SIZE];
}SPrMa;

//int : ����Ű(����), SPrMa : �����ڻ�(low, hi)
typedef CAtlMap<SPrMoTy::PRODUCTTYPE, SPrMa> ProductMappingVal;

//����̸����� ����Ű�� ã��
typedef CAtlMap<CAtlString, int, CStringElementTraits<CString> > PropNameKeyVal;