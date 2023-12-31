﻿
// Memo_MFCDlg.h : ヘッダー ファイル
//
#include "MemoChildDlg.h"
#pragma once


// CMemoMFCDlg ダイアログ
class CMemoMFCDlg : public CDialogEx
{
// コンストラクション
public:
	CMemoMFCDlg(CWnd* pParent = nullptr);	// 標準コンストラクター

//デストラクタ	
	virtual ~CMemoMFCDlg();

	void CMemoMFCDlg::OnMemoChildDlgClosed(MemoChildDlg* pClosedDialog);

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MEMO_MFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

protected:
	CPtrArray  m_MemoDialogArray; // MemoChildDlgを保持するCArray

public:
	afx_msg void OnBnClickedButton1();
};
