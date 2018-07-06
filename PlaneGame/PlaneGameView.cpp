
// PlaneGameView.cpp: CPlaneGameView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "PlaneGame.h"
#endif

#include "PlaneGameDoc.h"
#include "PlaneGameView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "Bomb.h"
#include "Enemy.h"

int CPlaneGameView::numOfEnemy = 0;
// CPlaneGameView

IMPLEMENT_DYNCREATE(CPlaneGameView, CView)

BEGIN_MESSAGE_MAP(CPlaneGameView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CPlaneGameView 构造/析构
 
CPlaneGameView::CPlaneGameView()
{
	// TODO: 在此处添加构造代码

}

CPlaneGameView::~CPlaneGameView()
{
}

BOOL CPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CPlaneGameView 绘图

void CPlaneGameView::OnDraw(CDC* pDC)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码

}


// CPlaneGameView 打印

BOOL CPlaneGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CPlaneGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CPlaneGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CPlaneGameView 诊断

#ifdef _DEBUG
void CPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneGameDoc* CPlaneGameView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneGameDoc)));
	return (CPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlaneGameView 消息处理程序


void CPlaneGameView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	//监控键盘消息
	short key = GetKeyState(VK_LEFT);
	if ((key & 0x8000) != 0)
	{
		me.SetHorMotion(-1);
	}
	key = GetKeyState(VK_RIGHT);
	if ((key & 0x8000) != 0)
	{
		me.SetHorMotion(1);
	}
	key = GetKeyState(VK_UP);
	if ((key & 0x8000) != 0)
	{
		me.SetVerMotion(-1);
	}
	key = GetKeyState(VK_DOWN);
	if ((key & 0x8000) != 0)
	{
		me.SetVerMotion(1);
	}
	key = GetKeyState(VK_SPACE);
	if ((key & 0x8000) != 0)
	{
		listObj[enBomb].AddTail(new CBomb(me.GetRect().left + 10, me.GetRect().top));
		listObj[enBomb].AddTail(new CBomb(me.GetRect().left + 30, me.GetRect().top));
	}

	//建立设备DC
	pDC = new CClientDC(this);
	//CRect rcClient;
	//GetClientRect(&rcClient);

	//创建内存DC
	pMemDC = new CDC();
	pMemDC->CreateCompatibleDC(pDC);

	//建立内存位图
	bmpMem = new CBitmap;
	bmpMem->CreateCompatibleBitmap(pDC, GAME_WIDTH, GAME_HEIGHT);

	//将位图选入内存DC
	CBitmap *pBmpOld = pMemDC->SelectObject(bmpMem);

	//背景绘制
	pMemDC->FillSolidRect(0, 0, GAME_WIDTH, GAME_HEIGHT, RGB(84, 142, 239));
	
	//战机绘制
	me.Draw(pMemDC, false);

	//导弹、爆炸、敌机、子弹 绘制&删除
	for (int i = 0; i < 4; i++)
	{
		POSITION pos1, pos2;
		for (pos1 = listObj[i].GetHeadPosition(); (pos2 = pos1) != NULL;)
		{
			CGameObject* pObj = (CGameObject*)listObj[i].GetNext(pos1);
			if (pObj->GetRect().top < 0)//或者碰撞
			{
				CObject *pa = listObj[i].GetAt(pos2);
				listObj[i].RemoveAt(pos2);
				delete pa;
			}
			else
			{
				pObj->Draw(pMemDC, true);
			}
		}
	}

	//文本绘制
	CString s;
	s.Format(_T("(%d,%d)"), me.GetRect().left, me.GetRect().top);
	pMemDC->TextOutW(10, 10, s, s.GetLength());

	//敌机绘制
	if (numOfEnemy  <= 100)
	{
		listObj[enEnemy].AddTail(new CEnemy());
		numOfEnemy++;
	}
	



	


	//复制内存DC到设备DC
	pDC->BitBlt(0, 0, GAME_WIDTH, GAME_HEIGHT, pMemDC, 0, 0, SRCCOPY);
	pMemDC->SelectObject(pBmpOld);
	pBmpOld->DeleteObject();
	bmpMem->DeleteObject();
	pMemDC->DeleteDC();
	pDC->DeleteDC();
	CView::OnTimer(nIDEvent);
}


int CPlaneGameView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	SetTimer(1, 45, NULL);
	CMe::LoadImage();
	CBomb::LoadImage();
	CEnemy::LoadImage();

	return 0;
}


void CPlaneGameView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值


	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
