
// Memo_MFCDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "Memo_MFC.h"
#include "Memo_MFCDlg.h"
#include "afxdialogex.h"
#include"MemoData.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//MemoChildDlg child;

// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMemoMFCDlg ダイアログ



CMemoMFCDlg::CMemoMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MEMO_MFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CMemoMFCDlg::~CMemoMFCDlg()
{
	//// CArray内の全てのMemoChildDlgのインスタンスを削除
	//for (int i = 0; i < m_MemoDialogArray.GetSize(); i++)
	//{
	//	delete m_MemoDialogArray[i];
	//}
}

void CMemoMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMemoMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMemoMFCDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMemoMFCDlg メッセージ ハンドラー

BOOL CMemoMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。

	//前回保存してあるiniファイルからメモを作成。(iniファイルの個数分)
	CString name = _T("MemoData");
	CString num = _T("");
	CString ex = _T(".ini");
	CString exePath;
	::GetModuleFileName(NULL, exePath.GetBuffer(MAX_PATH), MAX_PATH);
	exePath.ReleaseBuffer();
	int pos = exePath.ReverseFind('\\');
	CFileFind finder;
	for (int i = 0; i < MAX_MEMO; i++)
	{
		num.Format(_T("%d"), i+1);
		CString iniPath = exePath.Left(pos + 1) + name+ num+ ex;
		if (finder.FindFile(iniPath))
		{
			MemoChildDlg* pDlgB = new MemoChildDlg(i + 1, this);
			if (pDlgB->Create(IDD_CHILD_MEMO, this))
			{
				// MemoChildDlgが正常にCreateされた場合
				m_MemoDialogArray.Add(pDlgB); // ポインタをCPtrArrayに追加
				pDlgB->ShowWindow(SW_SHOW);   // MemoChildDlgを表示
			}
			else
			{
				// Createに失敗した場合のエラー処理
				delete pDlgB; // メモリリークを防ぐために削除する
			}
		}
		else
		{
			//ない場合はスルー
		}

	}


	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CMemoMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CMemoMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CMemoMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMemoMFCDlg::OnBnClickedButton1()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。

	//保存してある番号以外でiniファイルを作成
	CString name = _T("MemoData");
	CString num = _T("");
	CString ex = _T(".ini");
	CString exePath;
	::GetModuleFileName(NULL, exePath.GetBuffer(MAX_PATH), MAX_PATH);
	exePath.ReleaseBuffer();
	int pos = exePath.ReverseFind('\\');
	CFileFind finder;
	for (int i = 0; i < MAX_MEMO; i++)
	{
		num.Format(_T("%d"), i + 1);
		CString iniPath = exePath.Left(pos + 1) + name + num + ex;
		if (finder.FindFile(iniPath))
		{
			//ある場合は上書きになってしまうのでスルー
			if (i == MAX_MEMO - 1)
			{
				//メモがMAX_MEMO分すでに存在している場合は作らせない
				AfxMessageBox(_T("メモの個数が上限値です(5)"));
			}
		}
		else
		{
			MemoChildDlg* pDlgB = new MemoChildDlg(i + 1, this);
			if (pDlgB->Create(IDD_CHILD_MEMO, this))
			{
				// MemoChildDlgが正常にCreateされた場合
				m_MemoDialogArray.Add(pDlgB); // ポインタをCPtrArrayに追加
				pDlgB->ShowWindow(SW_SHOW);   // MemoChildDlgを表示
			}
			else
			{
				// Createに失敗した場合のエラー処理
				delete pDlgB; // メモリリークを防ぐために削除する
			}
			break;
		}

	}
}
void CMemoMFCDlg::OnMemoChildDlgClosed(MemoChildDlg* pClosedDialog)
{
	//リークが起きないようにMemoChildDlg削除時通知が来てリストから削除
	for (int i = 0; i < m_MemoDialogArray.GetSize(); i++)
	{
		if (m_MemoDialogArray[i] == pClosedDialog)
		{
			m_MemoDialogArray.RemoveAt(i);
			break;
		}
	}
}