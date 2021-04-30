#pragma once
/**************************************************************
 *                                                            *
 *   Copyright (c) 2021 Gaojunfeng All rights reserved.       *
 *   Version: 1.0                                             *
 *   Author: Gaojunfeng                                       *
 *                                                            *
 *   最后修改日期：2021.04.30                                 *
 *                                                            *
 *   此类是显示语法分析结果的子对话框对应的类                 *
 *                                                            *
 **************************************************************/

// grammer_analysis_dialog 对话框

class grammer_analysis_dialog : public CDialogEx
{
	DECLARE_DYNAMIC(grammer_analysis_dialog)

public:
	grammer_analysis_dialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~grammer_analysis_dialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRAMMER_ANALYSIS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit word_analysis_edit;
	CTreeCtrl tree;

};
