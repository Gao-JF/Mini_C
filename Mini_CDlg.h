
// Mini_CDlg.h: 头文件
//
/**************************************************************
 *                                                            *
 *   Copyright (c) 2021 Gaojunfeng All rights reserved.       *
 *   Version: 1.0                                             *
 *   Author: Gaojunfeng                                       *
 *                                                            *
 *   最后修改日期：2021.04.30                                 *
 *                                                            *
 *   此类是MFC图形界面对应的类                                *
 *                                                            *
 *                                                            *
 **************************************************************/


#pragma once
#include "word_analysis_dialog.h"
#include"grammer_analysis_dialog.h"
// CMiniCDlg 对话框
class CMiniCDlg : public CDialogEx
{
// 构造
public:
	CMiniCDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MINI_C_DIALOG };
#endif

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
	afx_msg void OnBnClickedtest();
	afx_msg void OnBnClickedBtnTest();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeGetCode();
	CEdit edit;
	CString code_text;
	CString word_analysis_ans;


	afx_msg void OnBnClickedCompile();
	CTabCtrl m_tab;
	word_analysis_dialog m_word_analysis_dialog;
	grammer_analysis_dialog m_grammer_analysis_dialog;

	afx_msg void OnTcnSelchangeTab2(NMHDR* pNMHDR, LRESULT* pResult);
	
};
