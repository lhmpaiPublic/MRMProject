// ResolHiPropDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
//�ڻ� ǥ�� ��ü
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

	//��/���ػ� ���� �ڻ� ���� �ε��� ����
	PropKeyMappListIndex itemListIndexHi[SPrMoTy::MT_SIZE];
	//��/���ػ� ���� �ڻ� Ű ����
	PropNameKeyVal itemKeyHi[SPrMoTy::MT_SIZE];
	//��/���ػ� ���� �ڻ� �� ����
	PropKeyMappString itemMappStrHi[SPrMoTy::MT_SIZE];

	//CListCtrl ���ػ� ����� ���ػ� ������ COL ����
	static vector<SPrCoNa::LOWRATIOCOLUMNNAME> setLowRetenRitioNum;
	//CListCtrl ����� ���ػ� �ΰ��� COL ����
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
	//�δ����� ���� �̺�Ʈ
	LRESULT OnCbnSelchangeHPptyInunittype(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	//�δ�Ը� ���� �̺�Ʈ
	LRESULT OnCbnSelchangeHPptyInunitscale(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	//�ڻ걸�� ���� �̺�Ʈ
	LRESULT OnCbnSelchangeHPptyPropertydiv(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	//���ػ� CListCtrl ���� ���콺 ���� �̺�Ʈ
	LRESULT OnHiModelListSelectedLeft( LPNMHDR lpNMHDR );
	//���ػ� CListCtrl ���� ���� �̺�Ʈ
	LRESULT OnHiModelListModify( LPNMHDR lpNMHDR );

	//���ػ� ���� CListCtrl ���� ���콺 ���� �̺�Ʈ
	LRESULT OnLowModelRatioSelectedLeft( LPNMHDR lpNMHDR );
	//���ػ� ���� CListCtrl ���� ���� �̺�Ʈ
	LRESULT OnLowModelRatioModify( LPNMHDR lpNMHDR );

	//�ػ� ��ȯ ���� �̺�Ʈ
	LRESULT OnBnClickedHpptyResolutionchange(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	//���ػ� ���� �ڻ� CListCtrl ����
	void hHiPropertyItem(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);
	//���ػ� ���� �ڻ� CListCtrl ����
	void hLowPropertyItem(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);
	//���ػ� ���� ���� CListCtrl ����
	void hLowPropertyIRatio(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);
	//�ػ� ��ȯ�� ���� ���� ����
	void resolutionChangeHiProperty(CListCtrl* listCtrlHi, CListCtrl* listCtrlLowRatio, CListCtrl* listCtrlLow, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);

	//����Ű�� ��/���ػ� ���� �ڻ�� ����
	void setPropKeyMappStringHi(int mappKey, SPrMoTy::MODELTYPE modelType, CString propName);
	//����Ű�� ��/���ػ� ���� �ڻ�� �䱸
	bool getPropKeyMappStringHi(int mappKey, SPrMoTy::MODELTYPE modelType, vector<CString>& strProp);
	//����Ű�� ��/���ػ� ���� �ε��� ����
	void setPropKeyMappListIndexHi(int mappKey, SPrMoTy::MODELTYPE modelType, int idx);
	//����Ű�� ��/���ػ� ���� �ε��� �䱸
	bool getPropKeyMappListIndexHi(int mappKey, SPrMoTy::MODELTYPE modelType, vector<int>& idxVal);
};
#define STPL_HHIR CResolHiPropDlg::setHiRetenListNum