
// setDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CsetDlg 对话框
class CsetDlg : public CDialogEx
{
// 构造
public:
	CsetDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SET_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    CEdit inputFrame;
    CEdit showFrame;
    afx_msg void OnBnClickedOk();
    afx_msg void OnEnUpdateEditInput();
    CComboBox chooseSet;
//    afx_msg void OnBnClickedMfclinkCopy();
    CStatic infoStatic;
    afx_msg void OnStnClickedStaticCopy();
    CStatic copyStatic;
    afx_msg void OnBnClickedButtonClear();
};
