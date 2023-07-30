#pragma once

#include <afxwin.h>

class MemoData
{
public:
    MemoData();
    ~MemoData();

    void SaveData();
    void LoadData();

    // プロパティ
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

private:
    CString m_fileName;
    CRect m_windowRect;
    int m_fontSize;
    COLORREF m_textColor;
    COLORREF m_backgroundColor;

    CString m_text;

    BOOL WritePrivateProfileInt(LPCTSTR lpAppName, LPCTSTR lpKeyName, int value);
    int GetPrivateProfileInt(LPCTSTR lpAppName, LPCTSTR lpKeyName, int defaultValue);
    BOOL WritePrivateProfileColor(LPCTSTR lpAppName, LPCTSTR lpKeyName, COLORREF color);
    COLORREF GetPrivateProfileColor(LPCTSTR lpAppName, LPCTSTR lpKeyName, COLORREF defaultColor);
    BOOL WritePrivateProfileCString(LPCTSTR lpAppName, LPCTSTR lpKeyName, const CString& str);
    CString GetPrivateProfileCString(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpDefault);
};