// grammer_analysis_dialog.cpp: 实现文件
//

/**************************************************************/
/*                                                            */
/*   Copyright (c) 2021 Gaojunfeng All rights reserved.       */
/*   Version: 1.0                                             */
/*   Author: Gaojunfeng                                       */
/*                                                            */
/*   最后修改日期：2021.04.30                                 */
/*                                                            */
/*   此文件是显示语法树的子对话框的实现文件                   */
/*                                                            */
/**************************************************************/


#include "pch.h"
#include "Mini_C.h"
#include "grammer_analysis_dialog.h"
#include "afxdialogex.h"


// grammer_analysis_dialog 对话框

IMPLEMENT_DYNAMIC(grammer_analysis_dialog, CDialogEx)

grammer_analysis_dialog::grammer_analysis_dialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GRAMMER_ANALYSIS, pParent)
{

}

grammer_analysis_dialog::~grammer_analysis_dialog()
{
}

void grammer_analysis_dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, tree);
}


BEGIN_MESSAGE_MAP(grammer_analysis_dialog, CDialogEx)
END_MESSAGE_MAP()


// grammer_analysis_dialog 消息处理程序
