// word_analysis_dialog.cpp: 实现文件
//

/**************************************************************/
/*                                                            */
/*   Copyright (c) 2021 Gaojunfeng All rights reserved.       */
/*   Version: 1.0                                             */
/*   Author: Gaojunfeng                                       */
/*                                                            */
/*   最后修改日期：2021.04.30                                 */
/*                                                            */
/*   此文件是显示词法分析结果的子对话框的实现文件             */
/*                                                            */
/**************************************************************/

#include "pch.h"
#include "Mini_C.h"
#include "word_analysis_dialog.h"
#include "afxdialogex.h"


// word_analysis_dialog 对话框

IMPLEMENT_DYNAMIC(word_analysis_dialog, CDialogEx)

word_analysis_dialog::word_analysis_dialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOGBAR_WORD_ANALYSIS, pParent)
{

}

word_analysis_dialog::~word_analysis_dialog()
{
}

void word_analysis_dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, wa_edit);
}


BEGIN_MESSAGE_MAP(word_analysis_dialog, CDialogEx)
	
END_MESSAGE_MAP()


// word_analysis_dialog 消息处理程序


