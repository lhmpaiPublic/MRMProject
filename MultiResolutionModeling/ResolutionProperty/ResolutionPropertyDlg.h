// ResolutionPropertyDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
//자산 표현 객체
class CResolutionPropertyDlg : public CDialogImpl<CResolutionPropertyDlg>, public CUpdateUI<CResolutionPropertyDlg>,
		public CMessageFilter, public CIdleHandler
{
	//윈도우 마우스 이동 객체
	CRect winPos;
	CPoint startPoint;
	bool bLClick;

	//자산정보 출력 객체
	CListCtrl m_lowModelList;
	CListCtrl m_lowModelRatio;
	CListCtrl m_hiModelList;
	CListCtrl m_hiModelRatio;

	//이미지 객체
	CImageList m_ilItemImages;
	//폰트 정보 객체
	CFont m_fntCustomFont1;
	CFont m_fntCustomFont2;

	//자산정보 출력 선택 객체
	CComboBox inUnitType;
	CComboBox inUnitScale;
	CComboBox propertyDiv;

	//자산정보 출력 객체 이벤트 상태 저장 변수
	bool bEditHiRatio;
	int hiRatioSelectNum;
	//자산정보 출력 객체 이벤트 상태 저장 변수
	bool bEditLowRatio;
	int lowRatioSelectNum;

	//고/저해상도 구분 자산 매핑 인덱스 정보
	PropKeyMappListIndex itemListIndex[SPrMoTy::MT_SIZE];
	//고/저해상도 구분 자산 키 정보
	PropNameKeyVal itemKey[SPrMoTy::MT_SIZE];
	//고/저해상도 구분 자산 명 정보
	PropKeyMappString itemMappStr[SPrMoTy::MT_SIZE];

	//CListCtrl 정보
	//CListCtrl 계산할 고해상도 인가량 COL 정보
	static vector<SPrCoNa::HICOLUMNNAME> setHiRetenListNum;
	//CListCtrl 계산할 고해상도 인가량 COL 정보
	static vector<SPrCoNa::HICOLUMNNAME> setHiAccListNum;

	//CListCtrl 계산할 저해상도 보유량 COL 정보
	static vector<SPrCoNa::LOWCOLUMNNAME> setLowRetenListNum;
	//CListCtrl 계산할 저해상도 인가량 COL 정보
	static vector<SPrCoNa::LOWCOLUMNNAME> setLowAccListNum;

	//CListCtrl 저해상도 계산할 고해상도 보유량 COL 정보
	static vector<SPrCoNa::HIRATIOCOLUMNNAME> setHiRetenRitioNum;
	//CListCtrl 저해상도 계산할 고해상도 설정량 COL 정보
	static vector<SPrCoNa::HIRATIOCOLUMNNAME> setHiLimtRitioNum;

	//CListCtrl 저해상도 계산할 저해상도 보유량 COL 정보
	static vector<SPrCoNa::LOWRATIOCOLUMNNAME> setLowRetenRitioNum;
	//CListCtrl 저해상도 계산할 저해상도 설정량 COL 정보
	static vector<SPrCoNa::LOWRATIOCOLUMNNAME> setLowLimtRitioNum;
public:
	CResolutionPropertyDlg();

	~CResolutionPropertyDlg();

	enum { IDD = IDD_RESOLUTIONPROPERTY };

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();

	BEGIN_UPDATE_UI_MAP(CResolutionPropertyDlg)

	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CResolutionPropertyDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnLMouseMove)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		COMMAND_HANDLER(IDCC_PPTY_INUNITTYPE, CBN_SELCHANGE, OnCbnSelchangePptyInunittype)
		COMMAND_HANDLER(IDCC_PPTY_INUNITSCALE, CBN_SELCHANGE, OnCbnSelchangePptyInunitscale)
		COMMAND_HANDLER(IDCC_PPTY_PROPERTYDIV, CBN_SELCHANGE, OnCbnSelchangePptyPropertydiv)

		//NOTIFY_HANDLER_EX(IDCCUST_LOWMODELLIST, LCN_SELECTED, OnLowModelListSelected)
		NOTIFY_HANDLER_EX(IDCCUST_LOWMODELLIST, LCN_LEFTCLICK, OnLowModelListSelectedLeft)
		//NOTIFY_HANDLER_EX(IDCCUST_LOWMODELLIST, LCN_RIGHTCLICK, OnLowModelListSelectedRight)
		NOTIFY_HANDLER_EX(IDCCUST_LOWMODELLIST, LCN_MODIFIED, OnLowModelListModify)
		//NOTIFY_HANDLER_EX(IDCCUST_HIMODELLIST, LCN_SELECTED, OnHiModelListSelected)
		NOTIFY_HANDLER_EX(IDCCUST_HIMODELLIST, LCN_LEFTCLICK, OnHiModelListSelectedLeft)
		//NOTIFY_HANDLER_EX(IDCCUST_HIMODELRATIO, LCN_SELECTED, OnHiModelRatioSelected)
		NOTIFY_HANDLER_EX(IDCCUST_HIMODELRATIO, LCN_LEFTCLICK, OnHiModelRatioSelectedLeft)
		//NOTIFY_HANDLER_EX(IDCCUST_HIMODELRATIO, LCN_RIGHTCLICK, OnHiModelRatioSelectedRight)
		NOTIFY_HANDLER_EX(IDCCUST_HIMODELRATIO, LCN_MODIFIED, OnHiModelRatioModify)

		//NOTIFY_HANDLER_EX(IDCCUST_LOWMODELRATIO, LCN_SELECTED, OnLowModelRatioSelected)
		NOTIFY_HANDLER_EX(IDCCUST_LOWMODELRATIO, LCN_LEFTCLICK, OnLowModelRatioSelectedLeft)
		//NOTIFY_HANDLER_EX(IDCCUST_LOWMODELRATIO, LCN_RIGHTCLICK, OnLowModelRatioSelectedRight)
		NOTIFY_HANDLER_EX(IDCCUST_LOWMODELRATIO, LCN_MODIFIED, OnLowModelRatioModify)

		COMMAND_HANDLER(IDCB_PPTY_RESOLUTIONCHANGE, BN_CLICKED, OnBnClickedPptyResolutionchange)
		REFLECT_NOTIFICATIONS()		
		
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	void CloseDialog(int nVal);
	//마우스 이벤트 처리
	LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);
	LRESULT OnLMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);
	LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	//부대유형 변경 이벤트
	LRESULT OnCbnSelchangePptyInunittype(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	//부대규모 변경 이벤트
	LRESULT OnCbnSelchangePptyInunitscale(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	//자산구분 변경 이벤트
	LRESULT OnCbnSelchangePptyPropertydiv(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	//저해상도 CListCtrl 선택 이벤트
	LRESULT OnLowModelListSelected( LPNMHDR lpNMHDR );
	//저해상도 CListCtrl 왼쪽마우스 선택 이벤트
	LRESULT OnLowModelListSelectedLeft( LPNMHDR lpNMHDR );
	//저해상도 CListCtrl 오른쪽 마우스 선택 이벤트
	LRESULT OnLowModelListSelectedRight( LPNMHDR lpNMHDR );
	//저해상도 CListCtrl 내용 변경 이벤트
	LRESULT OnLowModelListModify( LPNMHDR lpNMHDR );

	//고해상도 CListCtrl 선택 이벤트
	LRESULT OnHiModelListSelected( LPNMHDR lpNMHDR );
	//고해상도 CListCtrl 왼쪽 마우스 선택 이벤트
	LRESULT OnHiModelListSelectedLeft( LPNMHDR lpNMHDR );

	//고해상도 비율 CListCtrl 선택 이벤트
	LRESULT OnHiModelRatioSelected( LPNMHDR lpNMHDR );
	//고해상도 비율 CListCtrl 왼쪽 마우스 선택 이벤트
	LRESULT OnHiModelRatioSelectedLeft( LPNMHDR lpNMHDR );
	//고해상도 비율 CListCtrl 오른쪽 마우스 선택 이벤트
	LRESULT OnHiModelRatioSelectedRight( LPNMHDR lpNMHDR );
	//고해상도 비율 CListCtrl 내용 변경 이벤트
	LRESULT OnHiModelRatioModify( LPNMHDR lpNMHDR );

	//저해상도 비율 CListCtrl 선택 이벤트
	LRESULT OnLowModelRatioSelected( LPNMHDR lpNMHDR );
	//저해상도 비율 CListCtrl 왼쪽 마우스 선택 이벤트
	LRESULT OnLowModelRatioSelectedLeft( LPNMHDR lpNMHDR );
	//저해상도 비율 CListCtrl 오른쪽 마우스 선택 이벤트
	LRESULT OnLowModelRatioSelectedRight( LPNMHDR lpNMHDR );
	//저해상도 비율 CListCtrl 내용 변경 이벤트
	LRESULT OnLowModelRatioModify( LPNMHDR lpNMHDR );

	//해상도 변환 실행 이벤트
	LRESULT OnBnClickedPptyResolutionchange(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	//저해상도 구분 자산 CListCtrl 세팅
	void lowPropertyItem(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);
	//저해상도 구분 비율 CListCtrl 세팅
	void lowPropertyIRatio(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);
	//고해상도 구분 자산 CListCtrl 세팅
	void hiPropertyItem(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);
	//고해상도 구분 비율 CListCtrl 세팅
	void hiPropertyRatio(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);
	//해상도 변환을 위한 정보 세팅
	void resolutionChangeProperty(CListCtrl* listCtrlLowRatio, CListCtrl* listCtrlLow, CListCtrl* listCtrlHiRatio, CListCtrl* listCtrlHi, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);


	//매핑키와 고/저해상도 구분 자산명 설정
	void setPropKeyMappString(int mappKey, SPrMoTy::MODELTYPE modelType, CString propName);
	//매핑키와 고/저해상도 구분 자산명 요구
	bool getPropKeyMappString(int mappKey, SPrMoTy::MODELTYPE modelType, vector<CString>& strProp);
	//매핑키와 고/저해상도 구분 인덱스 설정
	void setPropKeyMappListIndex(int mappKey, SPrMoTy::MODELTYPE modelType, int idx);
	//매핑키와 고/저해상도 구분 인덱스 요구
	bool getPropKeyMappListIndex(int mappKey, SPrMoTy::MODELTYPE modelType, vector<int>& idxVal);
};

//개체명 재 정의
#define STPL_LOWR CResolutionPropertyDlg::setLowRetenListNum
#define STPL_LOWA CResolutionPropertyDlg::setLowAccListNum
#define STPL_HIR CResolutionPropertyDlg::setHiRetenListNum
#define STPL_HIA CResolutionPropertyDlg::setHiAccListNum
#define STPL_HIRR CResolutionPropertyDlg::setHiRetenRitioNum
#define STPL_HIRL CResolutionPropertyDlg::setHiLimtRitioNum