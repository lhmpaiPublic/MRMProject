// ResolHiPropDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
//자산 표현 객체
class CResolHiPropDlg : public CDialogImpl<CResolHiPropDlg>, public CUpdateUI<CResolHiPropDlg>,
		public CMessageFilter, public CIdleHandler
{

	CRect winPos;
	CPoint startPoint;
	bool bLClick;
	CListCtrl m_lowModelList;
	CListCtrl m_lowModelRatio;
	CListCtrl m_hiModelList;
	CImageList m_ilItemImages;
	CFont m_fntCustomFont1;
	CFont m_fntCustomFont2;

	CComboBox inUnitType;
	CComboBox inUnitScale;
	CComboBox propertyDiv;

	bool bEditLowRatio;
	int lowRatioSelectNum;

	bool bEditHiItem;
	int hiItemSelectNum;

	//고/저해상도 구분 자산 매핑 인덱스 정보
	PropKeyMappListIndex itemListIndexHi[SPrMoTy::MT_SIZE];
	//고/저해상도 구분 자산 키 정보
	PropNameKeyVal itemKeyHi[SPrMoTy::MT_SIZE];
	//고/저해상도 구분 자산 명 정보
	PropKeyMappString itemMappStrHi[SPrMoTy::MT_SIZE];

	//CListCtrl 저해상도 계산할 저해상도 보유량 COL 정보
	static vector<SPrCoNa::LOWRATIOCOLUMNNAME> setLowRetenRitioNum;
	//CListCtrl 계산할 고해상도 인가량 COL 정보
	static vector<SPrCoNa::HICOLUMNNAME> setHiRetenListNum;
public:
	CResolHiPropDlg();

	~CResolHiPropDlg();

	enum { IDD = IDD_RESOLHIPROP };

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();

	BEGIN_UPDATE_UI_MAP(CResolHiPropDlg)

	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CResolHiPropDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnLMouseMove)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		COMMAND_HANDLER(IDCC_HPPTY_INUNITTYPE, CBN_SELCHANGE, OnCbnSelchangeHPptyInunittype)
		COMMAND_HANDLER(IDCC_HPPTY_INUNITSCALE, CBN_SELCHANGE, OnCbnSelchangeHPptyInunitscale)
		COMMAND_HANDLER(IDCC_HPPTY_PROPERTYDIV, CBN_SELCHANGE, OnCbnSelchangeHPptyPropertydiv)

		NOTIFY_HANDLER_EX(IDCCUST_HHIMODELLIST, LCN_LEFTCLICK, OnHiModelListSelectedLeft)
		NOTIFY_HANDLER_EX(IDCCUST_HHIMODELLIST, LCN_MODIFIED, OnHiModelListModify)

		NOTIFY_HANDLER_EX(IDCCUST_HLOWMODELRATIO, LCN_LEFTCLICK, OnLowModelRatioSelectedLeft)
		NOTIFY_HANDLER_EX(IDCCUST_HLOWMODELRATIO, LCN_MODIFIED, OnLowModelRatioModify)

		COMMAND_HANDLER(IDCB_HPPTY_RESOLUTIONCHANGE, BN_CLICKED, OnBnClickedHpptyResolutionchange)
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
	
	LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);

	LRESULT OnLMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);

	LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	//부대유형 변경 이벤트
	LRESULT OnCbnSelchangeHPptyInunittype(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	//부대규모 변경 이벤트
	LRESULT OnCbnSelchangeHPptyInunitscale(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	//자산구분 변경 이벤트
	LRESULT OnCbnSelchangeHPptyPropertydiv(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	//고해상도 CListCtrl 왼쪽 마우스 선택 이벤트
	LRESULT OnHiModelListSelectedLeft( LPNMHDR lpNMHDR );
	//고해상도 CListCtrl 내용 변경 이벤트
	LRESULT OnHiModelListModify( LPNMHDR lpNMHDR );

	//저해상도 비율 CListCtrl 왼쪽 마우스 선택 이벤트
	LRESULT OnLowModelRatioSelectedLeft( LPNMHDR lpNMHDR );
	//저해상도 비율 CListCtrl 내용 변경 이벤트
	LRESULT OnLowModelRatioModify( LPNMHDR lpNMHDR );

	//해상도 변환 실행 이벤트
	LRESULT OnBnClickedHpptyResolutionchange(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	//고해상도 구분 자산 CListCtrl 세팅
	void hHiPropertyItem(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);
	//저해상도 구분 자산 CListCtrl 세팅
	void hLowPropertyItem(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);
	//저해상도 구분 비율 CListCtrl 세팅
	void hLowPropertyIRatio(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);
	//해상도 변환을 위한 정보 세팅
	void resolutionChangeHiProperty(CListCtrl* listCtrlHi, CListCtrl* listCtrlLowRatio, CListCtrl* listCtrlLow, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);

	//매핑키와 고/저해상도 구분 자산명 설정
	void setPropKeyMappStringHi(int mappKey, SPrMoTy::MODELTYPE modelType, CString propName);
	//매핑키와 고/저해상도 구분 자산명 요구
	bool getPropKeyMappStringHi(int mappKey, SPrMoTy::MODELTYPE modelType, vector<CString>& strProp);
	//매핑키와 고/저해상도 구분 인덱스 설정
	void setPropKeyMappListIndexHi(int mappKey, SPrMoTy::MODELTYPE modelType, int idx);
	//매핑키와 고/저해상도 구분 인덱스 요구
	bool getPropKeyMappListIndexHi(int mappKey, SPrMoTy::MODELTYPE modelType, vector<int>& idxVal);
};
#define STPL_HHIR CResolHiPropDlg::setHiRetenListNum