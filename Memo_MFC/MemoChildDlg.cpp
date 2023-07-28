// MemoChildDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "Memo_MFC.h"
#include "afxdialogex.h"
#include "MemoChildDlg.h"

#include "Memo_MFCDlg.h"

//--------------------------
CWnd* pWnd;
//CMenu* pMenu;
//int MenuBar_Height;
//--------------------------


// MemoChildDlg ダイアログ

IMPLEMENT_DYNAMIC(MemoChildDlg, CDialogEx)

MemoChildDlg::MemoChildDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHILD_MEMO, pParent)
{
	
}

MemoChildDlg::~MemoChildDlg()
{
}

void MemoChildDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MEMO_EDIT, m_MemoEdit);
	
}
BOOL MemoChildDlg::OnInitDialog()
{
	if (!CDialogEx::OnInitDialog())
	{
		return FALSE;
	}
	// TODO: 初期化をここに追加します。
	pWnd = this;
	HWND hWnd = pWnd->GetSafeHwnd();



	
	menubar.CreateMenu();
	menuSet.CreateMenu();

	//背景色
	menuBGcolor.CreatePopupMenu();
	menuBGcolor.AppendMenu(MF_STRING, ID_SETTING_BGCOLOR_1, L"赤色");
	menuBGcolor.AppendMenu(MF_STRING, ID_SETTING_BGCOLOR_2, L"青色");
	menuBGcolor.AppendMenu(MF_STRING, ID_SETTING_BGCOLOR_3, L"黄色");
	menuBGcolor.AppendMenu(MF_STRING, ID_SETTING_BGCOLOR_4, L"緑色");
	menuBGcolor.AppendMenu(MF_STRING, ID_SETTING_BGCOLOR_5, L"白色");
	menuBGcolor.AppendMenu(MF_STRING, ID_SETTING_BGCOLOR_6, L"黒色");

	//文字色
	menuTXcolor.CreatePopupMenu();
	menuTXcolor.AppendMenu(MF_STRING, ID_SETTING_TCOLOR_1, L"赤色");
	menuTXcolor.AppendMenu(MF_STRING, ID_SETTING_TCOLOR_2, L"青色");
	menuTXcolor.AppendMenu(MF_STRING, ID_SETTING_TCOLOR_3, L"黄色");
	menuTXcolor.AppendMenu(MF_STRING, ID_SETTING_TCOLOR_4, L"緑色");
	menuTXcolor.AppendMenu(MF_STRING, ID_SETTING_TCOLOR_5, L"白色");
	menuTXcolor.AppendMenu(MF_STRING, ID_SETTING_TCOLOR_6, L"黒色");
	
	//文字サイズ
	menuTXsize.CreatePopupMenu();
	menuTXsize.AppendMenu(MF_STRING, ID_SETTING_TSIZE_1, L"8");
	menuTXsize.AppendMenu(MF_STRING, ID_SETTING_TSIZE_2, L"10");
	menuTXsize.AppendMenu(MF_STRING, ID_SETTING_TSIZE_3, L"12");
	menuTXsize.AppendMenu(MF_STRING, ID_SETTING_TSIZE_4, L"14");
	menuTXsize.AppendMenu(MF_STRING, ID_SETTING_TSIZE_5, L"16");
	menuTXsize.AppendMenu(MF_STRING, ID_SETTING_TSIZE_6, L"18");
	menuTXsize.AppendMenu(MF_STRING, ID_SETTING_TSIZE_7, L"20");
	menuTXsize.AppendMenu(MF_STRING, ID_SETTING_TSIZE_8, L"22");
	menuTXsize.AppendMenu(MF_STRING, ID_SETTING_TSIZE_9, L"24");
	menuTXsize.AppendMenu(MF_STRING, ID_SETTING_TSIZE_10, L"26");

	//各メニューをセット
	menuSet.AppendMenu(MF_POPUP, (UINT_PTR)menuBGcolor.m_hMenu, L"背景色");
	menuSet.AppendMenu(MF_POPUP, (UINT_PTR)menuTXcolor.m_hMenu, L"文字色");
	menuSet.AppendMenu(MF_POPUP, (UINT_PTR)menuTXsize.m_hMenu, L"文字サイズ");
	menuSet.AppendMenu(MF_STRING, ID_SETTING_END, L"終了");

	menubar.AppendMenu(MF_POPUP, (UINT_PTR)menuSet.m_hMenu, L"設定");

	SetMenu(&menubar);


	//pMenu = pWnd->GetMenu();


	//ModifyStyle(WS_BORDER, 0);

	//pWnd->SetMenu(NULL); // メニューバーを非表示にする
	if (m_MemoEdit)
	{
		editflag = true;
	}


	// ウィンドウスタイルを設定するコード
	ModifyStyle(0, WS_CAPTION);

	// フレームスタイルを設定するコード
	//ModifyStyleEx(0, WS_EX_DLGMODALFRAME);


	//----------------------------------------------------------------------------
	Edit_Fontsize = 120;
	Edit_BGcolor.CreateSolidBrush(RGB(255, 255, 255));	// エディットコントロール背景(黒)
	EditText_BGcolor = RGB(255, 255, 255);	// テキストバックグラウンド背景
	EditText_color= RGB(0, 0, 0);		//テキスト色
	Memofont.CreatePointFont(Edit_Fontsize, _T("Arial"));	//12pt

	return TRUE;
}

BEGIN_MESSAGE_MAP(MemoChildDlg, CDialogEx)
	ON_EN_SETFOCUS(IDC_MEMO_EDIT, &MemoChildDlg::OnEnSetfocusMemoEdit)
	ON_EN_KILLFOCUS(IDC_MEMO_EDIT, &MemoChildDlg::OnEnKillfocusMemoEdit)
	ON_WM_SIZE()
	ON_COMMAND_RANGE(ID_SETTING_BGCOLOR_0, ID_SETTING_END,&MemoChildDlg::OnMenuComand)
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// MemoChildDlg メッセージ ハンドラー


void MemoChildDlg::OnEnSetfocusMemoEdit()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	//ModifyStyle(0, WS_BORDER);
	ModifyStyle(0, WS_CAPTION);
	//ModifyStyle(0, WS_BORDER);


	SetMenu(&menubar);
	//pWnd->SetMenu(pMenu); // メニューバーを表示する
	
}


void MemoChildDlg::OnEnKillfocusMemoEdit()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	//ModifyStyle(WS_BORDER, 0);
	ModifyStyle(WS_CAPTION, 0);
	SetMenu(NULL); // メニューバーを非表示にする
	//DrawMenuBar();

}
void MemoChildDlg::OnCancel()
{
	DestroyWindow();
	//CDialog::OnCancel();
}


void MemoChildDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	CRect menuRect;
	GetClientRect(&menuRect);
	if (editflag)
	{
		//最初からアクティブにしてるとm_MemoEdit==NULLのときにエラー落ち
		m_MemoEdit.MoveWindow(&menuRect);
		
		
	}
	
	// TODO: ここにメッセージ ハンドラー コードを追加します。
}

void MemoChildDlg::OnMenuComand(UINT nID)
{
	int i = 0;
	switch (nID)
	{
	//背景色の変更
	case ID_SETTING_BGCOLOR_1:
	case ID_SETTING_BGCOLOR_2:
	case ID_SETTING_BGCOLOR_3:
	case ID_SETTING_BGCOLOR_4:
	case ID_SETTING_BGCOLOR_5:
	case ID_SETTING_BGCOLOR_6:
		Edit_BGcolor.DeleteObject(); // 既存のCBrushを破棄

		if (nID == ID_SETTING_BGCOLOR_1)	//赤
		{
			Edit_BGcolor.CreateSolidBrush(RGB(255, 0, 0));	// エディットコントロール背景
			EditText_BGcolor = RGB(255, 0, 0);	// テキストバックグラウンド背景
		}
		else if (nID == ID_SETTING_BGCOLOR_2) { Edit_BGcolor.CreateSolidBrush(RGB(0, 0, 255)); EditText_BGcolor = RGB(0, 0, 255); }		//青色
		else if (nID == ID_SETTING_BGCOLOR_3) { Edit_BGcolor.CreateSolidBrush(RGB(255, 255, 0)); EditText_BGcolor = RGB(255, 255, 0); }	//黄色
		else if (nID == ID_SETTING_BGCOLOR_4) { Edit_BGcolor.CreateSolidBrush(RGB(0, 255, 0)); EditText_BGcolor = RGB(0, 255, 0); }		//緑色
		else if (nID == ID_SETTING_BGCOLOR_5) { Edit_BGcolor.CreateSolidBrush(RGB(255, 255, 255)); EditText_BGcolor = RGB(255, 255, 255); }	//白色
		else if (nID == ID_SETTING_BGCOLOR_6) { Edit_BGcolor.CreateSolidBrush(RGB(0, 0, 0)); EditText_BGcolor = RGB(0, 0, 0); }		//黒色

		m_MemoEdit.Invalidate();	//エディットコントロールの再描画
		break;
	//文字色の変更
	case ID_SETTING_TCOLOR_0:
	case ID_SETTING_TCOLOR_1:
	case ID_SETTING_TCOLOR_2:
	case ID_SETTING_TCOLOR_3:
	case ID_SETTING_TCOLOR_4:
	case ID_SETTING_TCOLOR_5:
	case ID_SETTING_TCOLOR_6:
		if (nID == ID_SETTING_TCOLOR_1)	{ EditText_color = RGB(255, 0, 0); }	//赤
		else if (nID == ID_SETTING_TCOLOR_2) { EditText_color = RGB(0, 0, 255); }		//青色
		else if (nID == ID_SETTING_TCOLOR_3) { EditText_color = RGB(255, 255, 0); }	//黄色
		else if (nID == ID_SETTING_TCOLOR_4) { EditText_color = RGB(0, 255, 0); }		//緑色
		else if (nID == ID_SETTING_TCOLOR_5) { EditText_color = RGB(255, 255, 255); }	//白色
		else if (nID == ID_SETTING_TCOLOR_6) { EditText_color = RGB(0, 0, 0); }		//黒色
		m_MemoEdit.Invalidate();	//エディットコントロールの再描画
		break;

	case ID_SETTING_TSIZE_0:
	case ID_SETTING_TSIZE_1:
	case ID_SETTING_TSIZE_2:
	case ID_SETTING_TSIZE_3:
	case ID_SETTING_TSIZE_4:
	case ID_SETTING_TSIZE_5:
	case ID_SETTING_TSIZE_6:
	case ID_SETTING_TSIZE_7:
	case ID_SETTING_TSIZE_8:
	case ID_SETTING_TSIZE_9:
	case ID_SETTING_TSIZE_10:
		Memofont.DeleteObject();
		if (nID == ID_SETTING_TSIZE_1) { Edit_Fontsize = 80; }			// 8pt
		else if (nID == ID_SETTING_TSIZE_2) { Edit_Fontsize = 100; }	// 10pt
		else if (nID == ID_SETTING_TSIZE_3) { Edit_Fontsize = 120; }	// 12pt
		else if (nID == ID_SETTING_TSIZE_4) { Edit_Fontsize = 140; }	// 14pt
		else if (nID == ID_SETTING_TSIZE_5) { Edit_Fontsize = 160; }	// 16pt
		else if (nID == ID_SETTING_TSIZE_6) { Edit_Fontsize = 180; }	// 18pt
		else if (nID == ID_SETTING_TSIZE_7) { Edit_Fontsize = 200; }	// 20pt
		else if (nID == ID_SETTING_TSIZE_8) { Edit_Fontsize = 220; }	// 22pt
		else if (nID == ID_SETTING_TSIZE_9) { Edit_Fontsize = 240; }	// 24pt
		else if (nID == ID_SETTING_TSIZE_10) { Edit_Fontsize = 260; }	// 26pt
		Memofont.CreatePointFont(Edit_Fontsize, _T("Arial"));

		m_MemoEdit.SetFont(&Memofont);
		
		break;

	case ID_SETTING_FONT_0:
	case ID_SETTING_FONT_1:
	case ID_SETTING_FONT_2:
	case ID_SETTING_FONT_3:
	case ID_SETTING_FONT_4:
	case ID_SETTING_FONT_5:
	case ID_SETTING_FONT_6:
	case ID_SETTING_FONT_7:
		
		break;
	case ID_SETTING_END:
		OnCancel();
		break;
		// 他のメニューアイテムに対する処理をここに追加します

	default:
		break;
	}
}



HBRUSH MemoChildDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	int editControlID = IDC_MEMO_EDIT; // IDC_EDIT_CONTROL_IDにはCEditコントロールのIDを入れてください

	if (pWnd->GetDlgCtrlID() == editControlID)
	{
		pDC->SetBkColor(EditText_BGcolor); // 文字の背景色を黄色に設定
		pDC->SetTextColor(EditText_color); // 文字の色を設定
		hbr = (HBRUSH)Edit_BGcolor; // エディットコントロールの背景ブラシを設定
	}

	return hbr;
}
void MemoChildDlg::NotifyParentDialogClosed()
{
	CMemoMFCDlg* pParent = static_cast<CMemoMFCDlg*>(GetParent());
	if (pParent)
		pParent->OnMemoChildDlgClosed(this); // 親ダイアログに通知
}

void MemoChildDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: ここにメッセージ ハンドラー コードを追加します。
	// メニューバーを破棄
	CMenu* pMenu = GetMenu();
	if (pMenu)
	{
		pMenu->DestroyMenu();
		//menuBGcolor.DestroyMenu();
		//menuTXcolor.DestroyMenu();
		//menuTXsize.DestroyMenu();
		//menuSet.DestroyMenu();
		//menubar.DestroyMenu();
		SetMenu(nullptr);
	}
}
