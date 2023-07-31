#pragma once
#include "afxdialogex.h"
#include "MemoData.h"

// MemoChildDlg ダイアログ

class MemoChildDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MemoChildDlg)

public:
	MemoChildDlg(int number, CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~MemoChildDlg();
	void NotifyParentDialogClosed();
// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHILD_MEMO };
#endif
	//virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//DECLARE_MESSAGE_MAP()

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	int m_number;	//メモの番号
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnSetfocusMemoEdit();
	afx_msg void OnEnKillfocusMemoEdit();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMenuComand(UINT nID);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CEdit m_MemoEdit;
	COLORREF EditText_BGcolor;	//文字背景色
	COLORREF EditText_color;	//文字色
	CBrush Edit_BGcolor;		//エディットコントロール背景色
	CFont Memofont;				//フォント
	int Edit_Fontsize;			//フォントサイズ
	CRect Memo_windowRect;		//ウィンドウ位置
	CString Memotext;			//メモの内容
	bool editflag = false;
	bool deleteflag = false;	//trueでメニューバーからの終了、iniに書き出しなし
	CMenu menubar;
	CMenu menuSet;
	CMenu menuBGcolor;
	CMenu menuTXcolor;
	CMenu menuTXsize;
	MemoData data_M;

	afx_msg void OnDestroy();
};
