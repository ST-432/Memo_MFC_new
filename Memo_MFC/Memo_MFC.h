
// Memo_MFC.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CMemoMFCApp:
// このクラスの実装については、Memo_MFC.cpp を参照してください
//

class CMemoMFCApp : public CWinApp
{
public:
	CMemoMFCApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CMemoMFCApp theApp;
