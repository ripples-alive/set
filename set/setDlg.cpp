
// setDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "set.h"
#include "setDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "setCalc.h"


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CsetDlg 对话框




CsetDlg::CsetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CsetDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CsetDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_INPUT, inputFrame);
    DDX_Control(pDX, IDC_EDIT_OUTPUT, showFrame);
    DDX_Control(pDX, IDC_COMBO_SET, chooseSet);
    DDX_Control(pDX, IDC_STATIC_INFO, infoStatic);
    DDX_Control(pDX, IDC_STATIC_COPY, copyStatic);
}

BEGIN_MESSAGE_MAP(CsetDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDOK, &CsetDlg::OnBnClickedOk)
    ON_EN_UPDATE(IDC_EDIT_INPUT, &CsetDlg::OnEnUpdateEditInput)
//    ON_BN_CLICKED(IDC_MFCLINK_COPY, &CsetDlg::OnBnClickedMfclinkCopy)
ON_STN_CLICKED(IDC_STATIC_COPY, &CsetDlg::OnStnClickedStaticCopy)
ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CsetDlg::OnBnClickedButtonClear)
END_MESSAGE_MAP()


// CsetDlg 消息处理程序

BOOL CsetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    //为下拉菜单添加项目
    for (TCHAR c = TCHAR('A'); c <= TCHAR('Z'); c++)
    {
        chooseSet.AddString(CString(c));
    }
    chooseSet.SetCurSel(0);

    //为copy按钮加上下划线
    LOGFONT lf;
    copyStatic.GetFont()->GetLogFont(&lf);
    lf.lfUnderline = true;
    CFont *pFont = new CFont();
    pFont->CreateFontIndirect(&lf);
    copyStatic.SetFont(pFont);

    //提示框
    MessageBox(CString("为方便输入，输入时，可用：\r\n ") + OP_INPUT_UNION + _T("     代替   ") + OP_UNION + 
        _T("\r\n ") + OP_INPUT_INTERSECTION + _T("   代替   ") + OP_INTERSECTION +
        _T("\r\n ") + OP_INPUT_SYM_DIFFERENCE + _T("   代替   ") + OP_SYMMETRIC_DIFFERENCE +
        _T("\r\n ") + OP_INPUT_DESCARTES + _T("    代替   ") + OP_DESCARTES +
        _T("\r\n ") + OP_INPUT_COMPOUND + _T("     代替   ") + OP_COMPOUND +
        _T("\r\n ") + OP_INPUT_LIMIT + _T("  代替   ") + OP_LIMIT +
        _T("\r\n ") + OP_INPUT_EMPTY_SET + _T("    代替   ") + OP_EMPTY_SET, 
        _T("Important Notification"), MB_ICONEXCLAMATION);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CsetDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CsetDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CsetDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CsetDlg::OnBnClickedOk()
{
    // TODO: 在此添加控件通知处理程序代码
    //CDialogEx::OnOK();
    CString sInput;
    inputFrame.GetWindowTextW(sInput);

    CString sChoose;
    chooseSet.GetLBText(chooseSet.GetCurSel(), sChoose);
    CString sResult;
    if (CalcExpression(sInput, sResult, sChoose[0]))
    {
        infoStatic.SetWindowTextW(CString(_T("已将 ")) + sChoose[0] + _T(" 赋值为："));
        showFrame.SetWindowTextW(sResult);
    }
    else
    {
        MessageBox(_T("Input expression is invalid."));
    }
}


void CsetDlg::OnEnUpdateEditInput()
{
    // TODO:  如果该控件是 RICHEDIT 控件，它将不
    // 发送此通知，除非重写 CDialogEx::OnInitDialog()
    // 函数，以将 EM_SETEVENTMASK 消息发送到该控件，
    // 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。

    // TODO:  在此添加控件通知处理程序代码
    DWORD pos = inputFrame.GetSel();
    CString sInput;
    inputFrame.GetWindowTextW(sInput);
    
    //将输入字符串中的全角运算符替换成半角运算符
    sInput.Replace(OP_FULL_LEFT_BRACE, OP_LEFT_BRACE);
    sInput.Replace(OP_FULL_RIGHT_BRACE, OP_RIGHT_BRACE);
    sInput.Replace(OP_FULL_LEFT_ANGLE_BKT, OP_LEFT_ANGLE_BKT);
    sInput.Replace(OP_FULL_RIGHT_ANGLE_BKT, OP_RIGHT_ANGLE_BKT);
    sInput.Replace(OP_FULL_LEFT_BRACKET, OP_LEFT_BRACKET);
    sInput.Replace(OP_FULL_RIGHT_BRACKET, OP_RIGHT_BRACKET);
    sInput.Replace(OP_FULL_LEFT_PARENTHESIS, OP_LEFT_PARENTHESIS);
    sInput.Replace(OP_FULL_RIGHT_PARENTHESIS, OP_RIGHT_PARENTHESIS);
    sInput.Replace(OP_FULL_COMMA, OP_COMMA);
    sInput.Replace(OP_FULL_COMPOUND, OP_COMPOUND);
    sInput.Replace(OP_FULL_EMPTY_SET, OP_EMPTY_SET);
    //替换各种运算符
    sInput.Replace(OP_INPUT_UNION, OP_UNION);
    sInput.Replace(OP_INPUT_INTERSECTION, OP_INTERSECTION);
    sInput.Replace(OP_INPUT_SYM_DIFFERENCE, OP_SYMMETRIC_DIFFERENCE);
    sInput.Replace(OP_INPUT_DESCARTES, OP_DESCARTES);
    sInput.Replace(OP_INPUT_COMPOUND, OP_COMPOUND);
    sInput.Replace(OP_INPUT_LIMIT, OP_LIMIT);
    sInput.Replace(OP_INPUT_EMPTY_SET, OP_EMPTY_SET);
    //去除输入字符串中的换行与空格
    sInput.Replace(_T("\r\n"), _T(""));
    sInput.Replace(_T("\r"), _T(""));
    sInput.Replace(_T("\n"), _T(""));
    sInput.Replace(_T(" "), _T(""));
    sInput.Replace(_T("　"), _T(""));//全角空格

    inputFrame.SetWindowTextW(sInput);
    inputFrame.SetSel(pos);
}


//void CsetDlg::OnBnClickedMfclinkCopy()
//{
//    // TODO: 在此添加控件通知处理程序代码
//    inputFrame.SetSel(0, -1);
//    inputFrame.Copy();
//    MessageBox(_T("已复制到剪切板"));
//}


void CsetDlg::OnStnClickedStaticCopy()
{
    // TODO: 在此添加控件通知处理程序代码
    showFrame.SetSel(0, -1);
    showFrame.Copy();
    MessageBox(_T("已复制到剪切板"));
}


void CsetDlg::OnBnClickedButtonClear()
{
    inputFrame.SetWindowTextW(_T(""));
    showFrame.SetWindowTextW(_T(""));
    // TODO: 在此添加控件通知处理程序代码
}
