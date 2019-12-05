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
	//CListCtrl m_hiModelRatio;
	CImageList m_ilItemImages;
	CFont m_fntCustomFont1;
	CFont m_fntCustomFont2;

	CComboBox inUnitType;
	CComboBox inUnitScale;
	CComboBox propertyDiv;

	bool bEditHiRatio;
	int hiRatioSelectNum;

	bool bEditLowRatio;
	int lowRatioSelectNum;
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

		//NOTIFY_HANDLER_EX(IDCCUST_LOWMODELLIST, LCN_SELECTED, OnLowModelListSelected)
		//NOTIFY_HANDLER_EX(IDCCUST_LOWMODELLIST, LCN_LEFTCLICK, OnLowModelListSelectedLeft)
		//NOTIFY_HANDLER_EX(IDCCUST_LOWMODELLIST, LCN_RIGHTCLICK, OnLowModelListSelectedRight)
		//NOTIFY_HANDLER_EX(IDCCUST_LOWMODELLIST, LCN_MODIFIED, OnLowModelListModify)
		//NOTIFY_HANDLER_EX(IDCCUST_HIMODELLIST, LCN_SELECTED, OnHiModelListSelected)
		NOTIFY_HANDLER_EX(IDCCUST_HIMODELLIST, LCN_LEFTCLICK, OnHiModelListSelectedLeft)
		//NOTIFY_HANDLER_EX(IDCCUST_HIMODELRATIO, LCN_SELECTED, OnHiModelRatioSelected)
		//NOTIFY_HANDLER_EX(IDCCUST_HIMODELRATIO, LCN_LEFTCLICK, OnHiModelRatioSelectedLeft)
		//NOTIFY_HANDLER_EX(IDCCUST_HIMODELRATIO, LCN_RIGHTCLICK, OnHiModelRatioSelectedRight)
		//NOTIFY_HANDLER_EX(IDCCUST_HIMODELRATIO, LCN_MODIFIED, OnHiModelRatioModify)

		//NOTIFY_HANDLER_EX(IDCCUST_LOWMODELRATIO, LCN_SELECTED, OnLowModelRatioSelected)
		//NOTIFY_HANDLER_EX(IDCCUST_LOWMODELRATIO, LCN_LEFTCLICK, OnLowModelRatioSelectedLeft)
		//NOTIFY_HANDLER_EX(IDCCUST_LOWMODELRATIO, LCN_RIGHTCLICK, OnLowModelRatioSelectedRight)
		//NOTIFY_HANDLER_EX(IDCCUST_LOWMODELRATIO, LCN_MODIFIED, OnLowModelRatioModify)

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
	
	LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);

	LRESULT OnLMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);

	LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	//�δ����� ���� �̺�Ʈ
	LRESULT OnCbnSelchangeHPptyInunittype(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	//�δ�Ը� ���� �̺�Ʈ
	LRESULT OnCbnSelchangeHPptyInunitscale(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	//�ڻ걸�� ���� �̺�Ʈ
	LRESULT OnCbnSelchangeHPptyPropertydiv(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	////���ػ� CListCtrl ���� �̺�Ʈ
	//LRESULT OnLowModelListSelected( LPNMHDR lpNMHDR );
	////���ػ� CListCtrl ���ʸ��콺 ���� �̺�Ʈ
	//LRESULT OnLowModelListSelectedLeft( LPNMHDR lpNMHDR );
	////���ػ� CListCtrl ������ ���콺 ���� �̺�Ʈ
	//LRESULT OnLowModelListSelectedRight( LPNMHDR lpNMHDR );
	////���ػ� CListCtrl ���� ���� �̺�Ʈ
	//LRESULT OnLowModelListModify( LPNMHDR lpNMHDR );

	//���ػ� CListCtrl ���� �̺�Ʈ
	LRESULT OnHiModelListSelected( LPNMHDR lpNMHDR );
	//���ػ� CListCtrl ���� ���콺 ���� �̺�Ʈ
	LRESULT OnHiModelListSelectedLeft( LPNMHDR lpNMHDR );

	////���ػ� ���� CListCtrl ���� �̺�Ʈ
	//LRESULT OnHiModelRatioSelected( LPNMHDR lpNMHDR );
	////���ػ� ���� CListCtrl ���� ���콺 ���� �̺�Ʈ
	//LRESULT OnHiModelRatioSelectedLeft( LPNMHDR lpNMHDR );
	////���ػ� ���� CListCtrl ������ ���콺 ���� �̺�Ʈ
	//LRESULT OnHiModelRatioSelectedRight( LPNMHDR lpNMHDR );
	////���ػ� ���� CListCtrl ���� ���� �̺�Ʈ
	//LRESULT OnHiModelRatioModify( LPNMHDR lpNMHDR );

	////���ػ� ���� CListCtrl ���� �̺�Ʈ
	//LRESULT OnLowModelRatioSelected( LPNMHDR lpNMHDR );
	////���ػ� ���� CListCtrl ���� ���콺 ���� �̺�Ʈ
	//LRESULT OnLowModelRatioSelectedLeft( LPNMHDR lpNMHDR );
	////���ػ� ���� CListCtrl ������ ���콺 ���� �̺�Ʈ
	//LRESULT OnLowModelRatioSelectedRight( LPNMHDR lpNMHDR );
	////���ػ� ���� CListCtrl ���� ���� �̺�Ʈ
	//LRESULT OnLowModelRatioModify( LPNMHDR lpNMHDR );

	//�ػ� ��ȯ ���� �̺�Ʈ
	LRESULT OnBnClickedPptyResolutionchange(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};
