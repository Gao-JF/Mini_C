
// Mini_C.h: PROJECT_NAME 应用程序的主头文件
//
/**************************************************************/
/*                                                            */
/*   Copyright (c) 2021 Gaojunfeng All rights reserved.       */
/*   Version: 1.0                                             */
/*   Author: Gaojunfeng                                       */
/*                                                            */
/*   最后修改日期：2021.04.30                                 */
/*                                                            */
/*    Mini_C.h: PROJECT_NAME 应用程序的主头文件               */
/*                                                            */
/*                                                            */
/**************************************************************/
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号


// CMiniCApp:
// 有关此类的实现，请参阅 Mini_C.cpp
//

class CMiniCApp : public CWinApp
{
public:
	CMiniCApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CMiniCApp theApp;
