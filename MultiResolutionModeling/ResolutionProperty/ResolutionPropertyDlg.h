// ResolutionPropertyDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
//�ڻ� ǥ�� ��ü
class CResolutionPropertyDlg : public CDialogImpl<CResolutionPropertyDlg>, public CUpdateUI<CResolutionPropertyDlg>,
		public CMessageFilter, public CIdleHandler
{
	//������ ���콺 �̵� ��ü
	CRect winPos;
	CPoint startPoint;
	bool bLClick;

	//�ڻ����� ��� ��ü
	CListCtrl m_lowModelList;
	CListCtrl m_lowModelRatio;
	CListCtrl m_hiModelList;
	CListCtrl m_hiModelRatio;

	//�̹��� ��ü
	CImageList m_ilItemImages;
	//��Ʈ ���� ��ü
	CFont m_fntCustomFont1;
	CFont m_fntCustomFont2;

	//�ڻ����� ��� ���� ��ü
	CComboBox inUnitType;
	CComboBox inUnitScale;
	CComboBox propertyDiv;

	//�ڻ����� ��� ��ü �̺�Ʈ ���� ���� ����
	bool bEditHiRatio;
	int hiRatioSelectNum;
	//�ڻ����� ��� ��ü �̺�Ʈ ���� ���� ����
	bool bEditLowRatio;
	int lowRatioSelectNum;

	//��/���ػ� ���� �ڻ� ���� �ε��� ����
	PropKeyMappListIndex itemListIndex[SPrMoTy::MT_SIZE];
	//��/���ػ� ���� �ڻ� Ű ����
	PropNameKeyVal itemKey[SPrMoTy::MT_SIZE];
	//��/���ػ� ���� �ڻ� �� ����
	PropKeyMappString itemMappStr[SPrMoTy::MT_SIZE];

	//CListCtrl ����
	//CListCtrl ����� ���ػ� �ΰ��� COL ����
	static vector<SPrCoNa::HICOLUMNNAME> setHiRetenListNum;
	//CListCtrl ����� ���ػ� �ΰ��� COL ����
	static vector<SPrCoNa::HICOLUMNNAME> setHiAccListNum;

	//CListCtrl ����� ���ػ� ������ COL ����
	static vector<SPrCoNa::LOWCOLUMNNAME> setLowRetenListNum;
	//CListCtrl ����� ���ػ� �ΰ��� COL ����
	static vector<SPrCoNa::LOWCOLUMNNAME> setLowAccListNum;

	//CListCtrl ���ػ� ����� ���ػ� ������ COL ����
	static vector<SPrCoNa::HIRATIOCOLUMNNAME> setHiRetenRitioNum;
	//CListCtrl ���ػ� ����� ���ػ� ������ COL ����
	static vector<SPrCoNa::HIRATIOCOLUMNNAME> setHiLimtRitioNum;

	//CListCtrl ���ػ� ����� ���ػ� ������ COL ����
	static vector<SPrCoNa::LOWRATIOCOLUMNNAME> setLowRetenRitioNum;
	//CListCtrl ���ػ� ����� ���ػ� ������ COL ����
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
	//���콺 �̺�Ʈ ó��
	LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);
	LRESULT OnLMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);
	LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	//�δ����� ���� �̺�Ʈ
	LRESULT OnCbnSelchangePptyInunittype(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	//�δ�Ը� ���� �̺�Ʈ
	LRESULT OnCbnSelchangePptyInunitscale(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	//�ڻ걸�� ���� �̺�Ʈ
	LRESULT OnCbnSelchangePptyPropertydiv(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	//���ػ� CListCtrl ���� �̺�Ʈ
	LRESULT OnLowModelListSelected( LPNMHDR lpNMHDR );
	//���ػ� CListCtrl ���ʸ��콺 ���� �̺�Ʈ
	LRESULT OnLowModelListSelectedLeft( LPNMHDR lpNMHDR );
	//���ػ� CListCtrl ������ ���콺 ���� �̺�Ʈ
	LRESULT OnLowModelListSelectedRight( LPNMHDR lpNMHDR );
	//���ػ� CListCtrl ���� ���� �̺�Ʈ
	LRESULT OnLowModelListModify( LPNMHDR lpNMHDR );

	//���ػ� CListCtrl ���� �̺�Ʈ
	LRESULT OnHiModelListSelected( LPNMHDR lpNMHDR );
	//���ػ� CListCtrl ���� ���콺 ���� �̺�Ʈ
	LRESULT OnHiModelListSelectedLeft( LPNMHDR lpNMHDR );

	//���ػ� ���� CListCtrl ���� �̺�Ʈ
	LRESULT OnHiModelRatioSelected( LPNMHDR lpNMHDR );
	//���ػ� ���� CListCtrl ���� ���콺 ���� �̺�Ʈ
	LRESULT OnHiModelRatioSelectedLeft( LPNMHDR lpNMHDR );
	//���ػ� ���� CListCtrl ������ ���콺 ���� �̺�Ʈ
	LRESULT OnHiModelRatioSelectedRight( LPNMHDR lpNMHDR );
	//���ػ� ���� CListCtrl ���� ���� �̺�Ʈ
	LRESULT OnHiModelRatioModify( LPNMHDR lpNMHDR );

	//���ػ� ���� CListCtrl ���� �̺�Ʈ
	LRESULT OnLowModelRatioSelected( LPNMHDR lpNMHDR );
	//���ػ� ���� CListCtrl ���� ���콺 ���� �̺�Ʈ
	LRESULT OnLowModelRatioSelectedLeft( LPNMHDR lpNMHDR );
	//���ػ� ���� CListCtrl ������ ���콺 ���� �̺�Ʈ
	LRESULT OnLowModelRatioSelectedRight( LPNMHDR lpNMHDR );
	//���ػ� ���� CListCtrl ���� ���� �̺�Ʈ
	LRESULT OnLowModelRatioModify( LPNMHDR lpNMHDR );

	//�ػ� ��ȯ ���� �̺�Ʈ
	LRESULT OnBnClickedPptyResolutionchange(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	//���ػ� ���� �ڻ� CListCtrl ����
	void lowPropertyItem(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);
	//���ػ� ���� ���� CListCtrl ����
	void lowPropertyIRatio(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);
	//���ػ� ���� �ڻ� CListCtrl ����
	void hiPropertyItem(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);
	//���ػ� ���� ���� CListCtrl ����
	void hiPropertyRatio(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);
	//�ػ� ��ȯ�� ���� ���� ����
	void resolutionChangeProperty(CListCtrl* listCtrlLowRatio, CListCtrl* listCtrlLow, CListCtrl* listCtrlHiRatio, CListCtrl* listCtrlHi, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);


	//����Ű�� ��/���ػ� ���� �ڻ�� ����
	void setPropKeyMappString(int mappKey, SPrMoTy::MODELTYPE modelType, CString propName);
	//����Ű�� ��/���ػ� ���� �ڻ�� �䱸
	bool getPropKeyMappString(int mappKey, SPrMoTy::MODELTYPE modelType, vector<CString>& strProp);
	//����Ű�� ��/���ػ� ���� �ε��� ����
	void setPropKeyMappListIndex(int mappKey, SPrMoTy::MODELTYPE modelType, int idx);
	//����Ű�� ��/���ػ� ���� �ε��� �䱸
	bool getPropKeyMappListIndex(int mappKey, SPrMoTy::MODELTYPE modelType, vector<int>& idxVal);
};

//��ü�� �� ����
#define STPL_LOWR CResolutionPropertyDlg::setLowRetenListNum
#define STPL_LOWA CResolutionPropertyDlg::setLowAccListNum
#define STPL_HIR CResolutionPropertyDlg::setHiRetenListNum
#define STPL_HIA CResolutionPropertyDlg::setHiAccListNum
#define STPL_HIRR CResolutionPropertyDlg::setHiRetenRitioNum
#define STPL_HIRL CResolutionPropertyDlg::setHiLimtRitioNum