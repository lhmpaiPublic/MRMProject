#pragma once


#define MAKEMIL4(a, b, c, d)      ((DWORD)(((BYTE)((DWORD_PTR)(a))) & 0xff)) | ((DWORD)(((BYTE)((DWORD_PTR)(b)) & 0xff) << 8 )) | ((DWORD)(((BYTE)((DWORD_PTR)(c)) & 0xff) << 16 )) | ((DWORD)(((BYTE)((DWORD_PTR)(d)) & 0xff) << 24 ))
#define MAKEMIL3(a, b, c)      ((DWORD)(((BYTE)((DWORD_PTR)(a))) & 0xff)) | ((DWORD)(((BYTE)((DWORD_PTR)(b)) & 0xff) << 8 )) | ((DWORD)(((BYTE)((DWORD_PTR)(c)) & 0xff) << 16 ))
#define MAKEMIL2(a, b)      ((DWORD)(((BYTE)((DWORD_PTR)(a))) & 0xff)) | ((DWORD)(((BYTE)((DWORD_PTR)(b)) & 0xff) << 8 ))
#define MAKEMIL1(a)      ((DWORD)(((BYTE)((DWORD_PTR)(a))) & 0xff))

typedef struct _SVecCompIdxVal
{
	static bool compare(_SVecCompIdxVal val1, _SVecCompIdxVal val2)
	{
		return val1.val > val2.val;
	}
	int idx;
	float val;
}SVeCoIdVa;

typedef struct _SVecStringInt
{
	_SVecStringInt()
	{
		clearVal();
	}
	void clearVal()
	{
		size = 0;
		iValue.clear();
		sValue.clear();
	}

	bool deleteVal(DWORD idx)
	{
		bool b = false;
		if(sValue.size() > idx && iValue.size() > idx)
		{
			b = true;
			sValue.erase(sValue.begin()+idx);
			iValue.erase(iValue.begin()+idx);
		}
		return b;
	}

	void setVal(CString _sVal, int _iVal)
	{
		sValue.push_back(_sVal);
		iValue.push_back(_iVal);
		size = (int) sValue.size();
	}

	bool modifyVal(DWORD idx, CString _sVal, int _iVal)
	{
		bool b = false;
		if(sValue.size() > idx && iValue.size() > idx)
		{
			b = true;
			sValue[idx] = _sVal;
			iValue[idx] = _iVal;
		}
		return b;
	}

	CString getSVal(DWORD idx)
	{
		CString rVal = _T("");
		if(sValue.size() > idx)
		{
			rVal = sValue[idx];
		}
		return rVal;
	}

	vector<CString> getSVal()
	{
		return sValue;
	}

	int getIVal(DWORD idx)
	{
		int rVal = -1;
		if(sValue.size() > idx)
		{
			rVal = iValue[idx];
		}
		return rVal;
	}

	vector<int> getIVal()
	{
		return iValue;
	}

	bool getIVal(DWORD idx, CString& sVal, int& iVal)
	{
		bool b = false;
		if(sValue.size() > idx && iValue.size() > idx)
		{
			b = true;
			sVal = sValue[idx];
			iVal = iValue[idx];
		}
		return b;
	}

	int getSize()
	{
		return size;
	}
private:
	int size;
	vector<int> iValue;
	vector<CString> sValue;
}SVeStIn;

typedef struct _SProductColumnName
{
	enum LOWCOLUMNNAME
	{
		LMN_00 = 0,				//자산 이름
		LMN_01 = 1,				//모체 설정량
		LMN_02 = 2,				//모체 인가량
		LMN_03 = 3,			//본부개체 보유량
		LMN_04 = 4,			//본부개체 인가량
		LMN_05 = 5,				//1개체 보유량
		LMN_06 = 6,				//1개체 인가량
		LMN_07 = 7,				//2개체 보유량
		LMN_08 = 8,				//2개체 인가량
		LMN_09 = 9,				//3개체 보유량
		LMN_10 = 10,				//3개체 인가량
		LMN_SIZE = 11
	};

	enum HICOLUMNNAME
	{
		HMN_00 = 0,				//모체 자산 이름
		HMN_01 = 1,					//자산 이름
		HMN_02 = 2,					//변환개체 보유량
		HMN_03 = 3,					//변환개체 인가량
		HMN_04 = 4,				//본부개체 보유량
		HMN_05 = 5,				//본부개체 인가량
		HMN_06 = 6,					//1개체 보유량
		HMN_07 = 7,					//1개체 인가량
		HMN_08 = 8,					//2개체 보유량
		HMN_09 = 9,					//2개체 인가량
		HMN_10 = 10,					//3개체 보유량
		HMN_11 = 11,					//3개체 인가량
		HMN_SIZE = 12
	};
}SPrCoNa;

typedef struct _SProductModelType
{
	enum MODELTYPE
	{
		MTLOW = 0,				//LOW 모델
		MTHI = 1,				//HI 모델
		MT_SIZE
	};
	enum PRODUCTTYPE
	{
		TY0 = 0,				//병력
		TY1 = 1,				//전투장비(화기)
		TY2 = 2,				//전투지원장비
		TY3 = 3,				//보급품
		PROD_SIZE
	};
	enum COMBATANT
	{
		INFANTRY = 0,	//보병
		ARMORED = 1,	//전차
		ARTILLERY = 2,	//포병
		COMBATANT_SIZE = 3,
	};

	enum COMBATANTCLASS
	{
		SQUAD = 0,		//분대
		PLATOON_CENTER = 1,	//소대본부
		PLATOON = 2,	//소대
		COMPANY_CENTER = 3,	//중대본부
		COMPANY = 4,	//중대
		BATTALION_CENTER = 5,	//대대본부
		BATTALION = 6,	//대대
		COMBATANTCLASS_SIZE = 7 //크기
	};

	static CString strPRODUCTTYPE(PRODUCTTYPE em)
	{
		CString str = _T("");
		switch(em)
		{
		case TY0: str = _T("병력");
			break;
		case TY1: str = _T("전투장비(화기)");
			break;
		case TY2: str = _T("전투지원장비");
			break;
		case TY3: str = _T("보급품");
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
		strEm.push_back(_T("병력"));
		strEm.push_back(_T("전투장비(화기)"));
		strEm.push_back(_T("전투지원장비"));
		strEm.push_back(_T("보급품"));
		return strEm;
	}

	static CString strCOMBATANT(COMBATANT em)
	{
		CString str = _T("");
		switch(em)
		{
		case INFANTRY: str = _T("보병");
			break;
		case ARMORED: str = _T("전차");
			break;
		case ARTILLERY: str = _T("포병");
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
		strEm.push_back(_T("보병"));
		strEm.push_back(_T("전차"));
		strEm.push_back(_T("포병"));
		return strEm;
	}

	static CString strCOMBATANTCLASS(COMBATANTCLASS em)
	{
		CString str = _T("");
		switch(em)
		{
		case PLATOON: str = _T("소대");
			break;
		case COMPANY: str = _T("중대");
			break;
		case BATTALION: str = _T("대대");
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
			strEm.push_back(_T("중대"));
			strEm.push_back(_T("대대"));
		}
		else if (ARTILLERY == combat)
		{
			strEm.push_back(_T("대대"));
		}
		else
		{
			strEm.push_back(_T("소대"));
			strEm.push_back(_T("중대"));
			strEm.push_back(_T("대대"));
		}
		return strEm;
	}

}SPrMoTy;

//매핑키, 유일키(LOW, HI 분리)
typedef CAtlMap<int, vector<int> > ProductKeyMap;

typedef struct _SProductMappKey
{
	void setVal(SPrMoTy::MODELTYPE moType, int mappKey, int proKey)
	{
		ProductKeyMap::CPair* pair = PrMaKeVal[moType].Lookup(mappKey);
		if(pair != NULL)
		{
			pair->m_value.push_back(proKey);
		}
		else
		{
			vector<int> val;
			val.push_back(proKey);
			PrMaKeVal[moType].SetAt(mappKey, val);
		}
	}

	vector<int> getMappKey(SPrMoTy::MODELTYPE moType)
	{
		vector<int> keyVal;
		ProductKeyMap::CPair* pair = NULL;
		POSITION pos = PrMaKeVal[moType].GetStartPosition();
		while(pos)
		{
			pair = PrMaKeVal[moType].GetNext(pos);
			keyVal.push_back(pair->m_key);
		}
		sort(keyVal.begin(), keyVal.end());
		return keyVal;
	}
private:
	ProductKeyMap PrMaKeVal[SPrMoTy::MT_SIZE];
}SPrMaKe;

typedef struct _SProductNum
{
	int retention; //보유량
	int accreditation;	//인가량
	int key;	//유일 키값
	int mappingNumber;	//매핑번호
	CString strName;	//자산이름
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

//소대 분할
typedef struct _SProductSquad
{
	enum MILITARYBRANCH
	{
		MY0 = 0,				//소대본부
		MY1 = 1,				//1분대
		MY2 = 2,				//2분대
		MY3 = 3,				//3분대
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

//중대분할
typedef struct _SProductPlatoon
{
	enum MILITARYBRANCH
	{
		MY0 = 0,				//중대본부
		MY1 = 1,				//1소대
		MY2 = 2,				//2소대
		MY3 = 3,				//3소대
		MY_SIZE = 4,
		LV1 = 0,				//1소대분대
		LV2 = 1,				//2소대분대
		LV3 = 2,				//3소대분대
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

//대대분할
typedef struct _SProductCompany
{
	enum MILITARYBRANCH
	{
		MY0 = 0,				//대대본부
		MY1 = 1,				//1중대
		MY2 = 2,				//2중대
		MY3 = 3,				//3중대
		MY_SIZE = 4,
		LV1 = 0,				//1중대소대
		LV2 = 1,				//2중대소대
		LV3 = 2,				//3중대소대
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

//UNIT Type 분할
typedef struct _SProductBattalion
{
	enum MILITARYBRANCH
	{
		MY0 = 0,				//대대
		MY_SIZE = 1,
		LV1 = 0,				//대대하위
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
	int accreditation;	//인가량
	int key;		//유일 키값
	int mappKey;	//매핑 키
	CString strName;	//자산이름
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
		stm << "인가량 : " << accreditation << "	"
			<< "유일 키값 : " << key << "	"
			<< "매핑 키 : " << mappKey << "	"
			<< "자산이름 : " << CStringA(strName) << "	";
		return stm.str();
	}
}SPrVa;

typedef struct _SProductKeyMappString
{
	void setVal(CString propName)
	{
		keyStr.push_back(propName);
	}

	vector<CString> getVal()
	{
		return keyStr;
	}

	vector<CString> keyStr;
}SPrKeMaSt;

typedef struct _SProductKeyMappListIndex
{
	void setVal(int idx)
	{
		MakLidx.push_back(idx);
	}

	vector<int> getVal()
	{
		return MakLidx;
	}
private:
	vector<int> MakLidx;
}SPrKeMaLiIn;

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

//int : 매핑키(숫자), SPrMa : 매핑자산(low, hi)
typedef CAtlMap<SPrMoTy::PRODUCTTYPE, SPrMa> ProductMappingVal;

typedef struct _SProductKey
{
	void setVal(int _mappKey, int _primKey, int _colNum)
	{
		mappKey = _mappKey;
		primkey = _primKey;
		colNum = _colNum;
	}

	int getMappKey()
	{
		return mappKey;
	}

	int getPrimKey()
	{
		return primkey;
	}

	int getColNum()
	{
		return colNum;
	}
private:
	int mappKey;
	int primkey;
	int colNum;
}SPrKe;
//장비이름으로 고유키값 찾기
typedef CAtlMap<CAtlString, SPrKe, CStringElementTraits<CString> > PropNameKeyVal;

typedef CAtlMap<int, SPrKeMaSt> PropKeyMappString;

typedef CAtlMap<int, SPrKeMaLiIn> PropKeyMappListIndex;