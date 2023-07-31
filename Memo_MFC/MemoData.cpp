#include "pch.h"
#include "MemoData.h"

MemoData::MemoData()
{
    // ファイル名を指定
    m_fileName = _T("");
}

MemoData::MemoData(CString filename)
{
    //iniのパスをメンバ変数に登録
    CString exePath;
    ::GetModuleFileName(NULL, exePath.GetBuffer(MAX_PATH), MAX_PATH);
    exePath.ReleaseBuffer();
    int pos = exePath.ReverseFind('\\');
    CString iniPath = exePath.Left(pos + 1) + filename;
    m_fileName = iniPath;
    //iniファイルが存在しているかチェック、存在していない場合は新規作成
    CheckAndCreateIniFile();
    
}

MemoData::~MemoData()
{
}

void MemoData::SaveData()
{
    bool A=WritePrivateProfileInt(_T("Window"), _T("Left"), m_windowRect.left);
    WritePrivateProfileInt(_T("Window"), _T("Top"), m_windowRect.top);
    WritePrivateProfileInt(_T("Window"), _T("Width"), m_windowRect.Width());
    WritePrivateProfileInt(_T("Window"), _T("Height"), m_windowRect.Height());

    WritePrivateProfileInt(_T("Font"), _T("Size"), m_fontSize);
    WritePrivateProfileColor(_T("Font"), _T("Color"), m_textColor);
    WritePrivateProfileColor(_T("Background"), _T("Color"), m_backgroundColor);

    WritePrivateProfileCString(_T("Text"), _T("Content"), m_text);
}

void MemoData::LoadData()
{
    m_windowRect.left = GetPrivateProfileInt(_T("Window"), _T("Left"), 0);
    m_windowRect.top = GetPrivateProfileInt(_T("Window"), _T("Top"), 0);
    int width = GetPrivateProfileInt(_T("Window"), _T("Width"), 300);
    int height = GetPrivateProfileInt(_T("Window"), _T("Height"), 200);
    m_windowRect.right = m_windowRect.left + width;
    m_windowRect.bottom = m_windowRect.top + height;

    m_fontSize = GetPrivateProfileInt(_T("Font"), _T("Size"), 80);
    m_textColor = GetPrivateProfileColor(_T("Font"), _T("Color"), RGB(0, 0, 0)); // Default: Black
    m_backgroundColor = GetPrivateProfileColor(_T("Background"), _T("Color"), RGB(255, 255, 255)); // Default: White

    m_text = GetPrivateProfileCString(_T("Text"), _T("Content"), _T("Sample"));
}

void MemoData::SetWindowRect(CRect rect)
{
    m_windowRect = rect;
}

CRect MemoData::GetWindowRect() const
{
    return m_windowRect;
}

void MemoData::SetFontSize(int fontSize)
{
    m_fontSize = fontSize;
}

int MemoData::GetFontSize() const
{
    return m_fontSize;
}

void MemoData::SetTextColor(COLORREF textColor)
{
    m_textColor = textColor;
}

COLORREF MemoData::GetTextColor() const
{
    return m_textColor;
}

void MemoData::SetBackgroundColor(COLORREF bgColor)
{
    m_backgroundColor = bgColor;
}

COLORREF MemoData::GetBackgroundColor() const
{
    return m_backgroundColor;
}

void MemoData::SetText(const CString& text)
{
    m_text = text;
}

CString MemoData::GetText() const
{
    return m_text;
}

BOOL MemoData::WritePrivateProfileInt(LPCTSTR lpAppName, LPCTSTR lpKeyName, int value)
{
    CString strValue;
    strValue.Format(_T("%d"), value);
    return ::WritePrivateProfileString(lpAppName, lpKeyName, strValue, m_fileName);
}

int MemoData::GetPrivateProfileInt(LPCTSTR lpAppName, LPCTSTR lpKeyName, int defaultValue)
{
    return ::GetPrivateProfileInt(lpAppName, lpKeyName, defaultValue, m_fileName);
}

BOOL MemoData::WritePrivateProfileColor(LPCTSTR lpAppName, LPCTSTR lpKeyName, COLORREF color)
{
    CString strValue;
    strValue.Format(_T("%02X%02X%02X"), GetRValue(color), GetGValue(color), GetBValue(color));
    return ::WritePrivateProfileString(lpAppName, lpKeyName, strValue, m_fileName);
}

COLORREF MemoData::GetPrivateProfileColor(LPCTSTR lpAppName, LPCTSTR lpKeyName, COLORREF defaultColor)
{
    TCHAR buffer[256];
    ::GetPrivateProfileString(lpAppName, lpKeyName, _T(""), buffer, sizeof(buffer) / sizeof(buffer[0]), m_fileName);
    if (lstrlen(buffer) != 6)
        return defaultColor;
    unsigned int colorCodeInt = HexStringToUInt(buffer);
    //16進数から10進数に
    int red = (colorCodeInt >> 16) & 0xFF;
    int green = (colorCodeInt >> 8) & 0xFF;
    int blue = colorCodeInt & 0xFF;
    return RGB(red, green, blue);
}

BOOL MemoData::WritePrivateProfileCString(LPCTSTR lpAppName, LPCTSTR lpKeyName, const CString& str)
{
    return ::WritePrivateProfileString(lpAppName, lpKeyName, str, m_fileName);
}

CString MemoData::GetPrivateProfileCString(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpDefault)
{
    TCHAR buffer[512];
    ::GetPrivateProfileString(lpAppName, lpKeyName, lpDefault, buffer, sizeof(buffer) / sizeof(buffer[0]), m_fileName);
    return buffer;
}

BOOL MemoData::FileExists(const CString& filePath)
{
    CFileFind finder;
    return finder.FindFile(filePath);
}

BOOL MemoData::CreateIniFile(const CString& filePath)
{
    CStdioFile file;
    if (file.Open(filePath, CFile::modeCreate | CFile::modeWrite))
    {
        //新規作成後閉じる
        file.Close();
        return TRUE;
    }
    return FALSE;
}

void MemoData::CheckAndCreateIniFile()
{
    if (FileExists(m_fileName))
    {
        // iniファイルが存在する場合の処理
    }
    else
    {
        // iniファイルが存在しない場合の処理
        if (CreateIniFile(m_fileName))
        {
            // iniファイルの作成に成功した場合の処理
        }
        else
        {
            // iniファイルの作成に失敗した場合の処理
        }
    }
}



// TCHARを使用して16進数の文字列を整数に変換
unsigned int MemoData::HexStringToUInt(const TCHAR* hexString)
{
    unsigned int result = 0;
    _stscanf_s(hexString, _T("%x"), &result);
    return result;
}

void MemoData::Deleteini()
{
    CFile::Remove(m_fileName);
}