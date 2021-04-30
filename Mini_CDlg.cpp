
// Mini_CDlg.cpp: 实现文件
//
/**************************************************************/
/*                                                            */
/*   Copyright (c) 2021 Gaojunfeng All rights reserved.       */
/*   Version: 1.0                                             */
/*   Author: Gaojunfeng                                       */
/*                                                            */
/*   最后修改日期：2021.04.30                                 */
/*                                                            */
/*   此类是MFC图形界面的实现文件                              */
/*                                                            */
/*                                                            */
/**************************************************************/


#include "pch.h"
#include "framework.h"
#include "Mini_C.h"
#include "Mini_CDlg.h"
#include "afxdialogex.h"
#include "word_analysis.h"
#include "grammer_analysis.h"
#include "grammer_tree.h"
#include "resource.h"
#include<queue>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()


};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMiniCDlg 对话框



CMiniCDlg::CMiniCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MINI_C_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMiniCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GET_CODE, edit);

}

BEGIN_MESSAGE_MAP(CMiniCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_BN_CLICKED(IDC_BUTTON2, &CMiniCDlg::OnBnClickedCompile)
	ON_NOTIFY(TCN_SELCHANGE,10000 , &CMiniCDlg::OnTcnSelchangeTab2)
END_MESSAGE_MAP()


// CMiniCDlg 消息处理程序

BOOL CMiniCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_tab.Create(TCS_TABS | WS_CHILD | WS_VISIBLE, CRect(620, 10, 1150, 605), this, 10000);
	m_tab.InsertItem(0, _T("词法分析"));
	m_tab.InsertItem(1, _T("语法分析"));

	m_tab.SetCurSel(0);

	m_word_analysis_dialog.Create(IDD_DIALOGBAR_WORD_ANALYSIS, &m_tab);
	m_grammer_analysis_dialog.Create(IDD_GRAMMER_ANALYSIS, &m_tab);

	m_word_analysis_dialog.ShowWindow(true);

	CRect rcTab;
	m_tab.GetClientRect(rcTab);
	rcTab.DeflateRect(0, 25, 0, 0);

	m_word_analysis_dialog.MoveWindow(rcTab);
	m_grammer_analysis_dialog.MoveWindow(rcTab);


	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMiniCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMiniCDlg::OnPaint()
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
HCURSOR CMiniCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMiniCDlg::OnBnClickedCompile()
{
	// TODO: 在此添加控件通知处理程序代码
	CString Code;
	edit.GetWindowText(Code);
	code_text = Code;
	string str = CT2A(Code.GetBuffer());
	word_analysis wa;
	wa.get_code(str);
	wa.scan();
	
	

	grammer_analysis ga(wa);
	grammer_tree* root=new grammer_tree();
	root = ga.program(root);

	

	

/*-------层序遍历树，将树的内容放进CTreeCtrl--------------------*/

	//放入用于层序遍历的队列中的数据结构
	struct tree_node
	{
		HTREEITEM father;//父节点
		grammer_tree* node;//当前结点
		tree_node()
		{
		}
		tree_node(HTREEITEM f, grammer_tree* t)
		{
			father = f;
			node = t;
		}
	};
	
	if (ga.get_flag() == 1) //如果没有语法错误，层序遍历树
	{
		m_grammer_analysis_dialog.tree.DeleteAllItems();
		//显示词法分析结果
		str = wa.output();
		CString word(str.c_str());
		word_analysis_ans = word;
		m_word_analysis_dialog.wa_edit.SetWindowText(word_analysis_ans);



		HTREEITEM item[100000];//树最多100000个结点
		int u = 0;//用于标志第几个结点

		tree_node start(NULL, root);//树的根节点
		queue<tree_node>q;
		q.push(start);

		while (!q.empty())
		{
			tree_node temp = q.front();
			q.pop();
			CString name(temp.node->get_data().c_str());
			item[u] = m_grammer_analysis_dialog.tree.InsertItem(name, temp.father);

			vector<grammer_tree*>c = temp.node->get_child();

			for (int i = 0; i < c.size(); i++)
			{
				if (c[i] != NULL)
				{
					tree_node t(item[u], c[i]);
					q.push(t);
				}
			}
			u++;

		}
		/*---------------层序遍历结束--------------------------------*/

		//把树的结点都展开
		for (int i = 0; i < u; i++)
		{
			m_grammer_analysis_dialog.tree.Expand(item[i], TVE_EXPAND);
		}
		
		AfxMessageBox(_T("编译成功！"));
	}
	else
		AfxMessageBox(_T("编译失败，请检查语法"));
}


void CMiniCDlg::OnTcnSelchangeTab2(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	int CurSel = m_tab.GetCurSel();
	switch (CurSel)
	{
	case 0:
		m_word_analysis_dialog.ShowWindow(true);
		m_grammer_analysis_dialog.ShowWindow(false);
		break;
	case 1:
		m_word_analysis_dialog.ShowWindow(false);
		m_grammer_analysis_dialog.ShowWindow(true);
		break;

	}
	*pResult = 0;
}
