#pragma once

#include <afxwin.h>
#include <iostream>
#include <tchar.h>

#define MAX_MEMO 5
class MemoData
{
public:
    MemoData();
    ~MemoData();

    MemoData(CString filename);	//引数ありコンストラクタ

    void SaveData();
    void LoadData();

    // セッター、ゲッター
    void SetWindowRect(CRect rect);
    CRect GetWindowRect() const;
    void SetFontSize(int fontSize);
    int GetFontSize() const;
    void SetTextColor(COLORREF textColor);
    COLORREF GetTextColor() const;
    void SetBackgroundColor(COLORREF bgColor);
    COLORREF GetBackgroundColor() const;
    void SetText(const CString& text);
    CString GetText() const;

    //iniファイルの操作関数
    void CheckAndCreateIniFile();
    BOOL CreateIniFile(const CString& filePath);
    BOOL FileExists(const CString& filePath);
    void MemoData::Deleteini();
    //
    unsigned int HexStringToUInt(const TCHAR* hexString);
private:
    //メンバ変数
    CString m_fileName;             //iniファイルパス
    CRect m_windowRect;             //画面位置(サイズ)
    int m_fontSize;                 //文字の大きさ
    COLORREF m_textColor;           //文字色
    COLORREF m_backgroundColor;     //背景色
    CString m_text;                 //メモの内容
    //iniファイルの操作関数
    BOOL WritePrivateProfileInt(LPCTSTR lpAppName, LPCTSTR lpKeyName, int value);
    int GetPrivateProfileInt(LPCTSTR lpAppName, LPCTSTR lpKeyName, int defaultValue);
    BOOL WritePrivateProfileColor(LPCTSTR lpAppName, LPCTSTR lpKeyName, COLORREF color);
    COLORREF GetPrivateProfileColor(LPCTSTR lpAppName, LPCTSTR lpKeyName, COLORREF defaultColor);
    BOOL WritePrivateProfileCString(LPCTSTR lpAppName, LPCTSTR lpKeyName, const CString& str);
    CString GetPrivateProfileCString(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpDefault);
};