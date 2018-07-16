// EnterName.cpp: 实现文件
//

#include "stdafx.h"
#include "PlaneGame.h"
#include "EnterName.h"
#include "afxdialogex.h"
#include "resource.h"
#include "cctype"
// CEnterName 对话框

IMPLEMENT_DYNAMIC(CEnterName, CDialogEx)

CEnterName::CEnterName(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ENTERNAME, pParent)
{
 
}

CEnterName::~CEnterName()
{
}

void CEnterName::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);



}


BEGIN_MESSAGE_MAP(CEnterName, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &CEnterName::OnEnChangeEdit1)
	ON_WM_CHAR()
END_MESSAGE_MAP()


// CEnterName 消息处理程序


void CEnterName::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO: 在此添加控件通知处理程序代码  



	//显示对话框，提示用户设定量   
	CString str;
	GetDlgItemText(IDC_EDIT1, str);//获得           
	name = str;
}


void CEnterName::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	TCHAR ch = nChar;

	if (!(ch >= _T('0') && ch <= _T('9') || ch >= _T('A') && ch <= _T('Z') || ch >= _T('a') && ch <= _T('z') || ch == VK_BACK))
	{

		return;

	}

	CDialogEx::OnChar(nChar, nRepCnt, nFlags);
}
