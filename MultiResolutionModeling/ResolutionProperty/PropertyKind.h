#pragma once


#define MAKEMIL4(a, b, c, d)      ((DWORD)(((BYTE)((DWORD_PTR)(a))) & 0xff)) | ((DWORD)(((BYTE)((DWORD_PTR)(b)) & 0xff) << 8 )) | ((DWORD)(((BYTE)((DWORD_PTR)(c)) & 0xff) << 16 )) | ((DWORD)(((BYTE)((DWORD_PTR)(d)) & 0xff) << 24 ))
#define MAKEMIL3(a, b, c)      ((DWORD)(((BYTE)((DWORD_PTR)(a))) & 0xff)) | ((DWORD)(((BYTE)((DWORD_PTR)(b)) & 0xff) << 8 )) | ((DWORD)(((BYTE)((DWORD_PTR)(c)) & 0xff) << 16 ))
#define MAKEMIL2(a, b)      ((DWORD)(((BYTE)((DWORD_PTR)(a))) & 0xff)) | ((DWORD)(((BYTE)((DWORD_PTR)(b)) & 0xff) << 8 ))
#define MAKEMIL1(a)      ((DWORD)(((BYTE)((DWORD_PTR)(a))) & 0xff))

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
	int accreditation;	//인가량
	int key;	//유일 키값
	CString strName;	//자산이름
}SPrVa;

typedef struct _SProductMapping
{
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

//int : 매핑키(숫자), SPrMa : 매핑자산(low, hi)
typedef CAtlMap<SPrMa::PRODUCTTYPE, SPrMa> ProductMappingVal;