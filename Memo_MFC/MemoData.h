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

    MemoData(CString filename);	//��������R���X�g���N�^

    void SaveData();
    void LoadData();

    // �Z�b�^�[�A�Q�b�^�[
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

    //ini�t�@�C���̑���֐�
    void CheckAndCreateIniFile();
    BOOL CreateIniFile(const CString& filePath);
    BOOL FileExists(const CString& filePath);
    void MemoData::Deleteini();
    //
    unsigned int HexStringToUInt(const TCHAR* hexString);
private:
    //�����o�ϐ�
    CString m_fileName;             //ini�t�@�C���p�X
    CRect m_windowRect;             //��ʈʒu(�T�C�Y)
    int m_fontSize;                 //�����̑傫��
    COLORREF m_textColor;           //�����F
    COLORREF m_backgroundColor;     //�w�i�F
    CString m_text;                 //�����̓��e
    //ini�t�@�C���̑���֐�
    BOOL WritePrivateProfileInt(LPCTSTR lpAppName, LPCTSTR lpKeyName, int value);
    int GetPrivateProfileInt(LPCTSTR lpAppName, LPCTSTR lpKeyName, int defaultValue);
    BOOL WritePrivateProfileColor(LPCTSTR lpAppName, LPCTSTR lpKeyName, COLORREF color);
    COLORREF GetPrivateProfileColor(LPCTSTR lpAppName, LPCTSTR lpKeyName, COLORREF defaultColor);
    BOOL WritePrivateProfileCString(LPCTSTR lpAppName, LPCTSTR lpKeyName, const CString& str);
    CString GetPrivateProfileCString(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpDefault);
};