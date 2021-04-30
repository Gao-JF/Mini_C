#pragma once
/**************************************************************
 *                                                            *
 *   Copyright (c) 2021 Gaojunfeng All rights reserved.       *
 *   Version: 1.0                                             *
 *   Author: Gaojunfeng                                       *
 *                                                            *
 *   最后修改日期：2021.04.30                                 *
 *                                                            *
 *   此类是显示词法分析结果的子对话框对应的类                 *
 *                                                            *
 **************************************************************/

// word_analysis_dialog 对话框

class word_analysis_dialog : public CDialogEx
{
	DECLARE_DYNAMIC(word_analysis_dialog)

public:
	word_analysis_dialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~word_analysis_dialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGBAR_WORD_ANALYSIS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit wa_edit;
	afx_msg void OnBnClickedButton1();
};
