
// 062201View.cpp : CMy062201View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "062201.h"
#endif

#include "062201Doc.h"
#include "062201View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy062201View

IMPLEMENT_DYNCREATE(CMy062201View, CView)

BEGIN_MESSAGE_MAP(CMy062201View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_END, &CMy062201View::OnEnd)
	ON_COMMAND(ID_START, &CMy062201View::OnStart)
	ON_COMMAND(ID_ting, &CMy062201View::OnTing)
	ON_COMMAND(ID_jixv, &CMy062201View::OnJixv)
END_MESSAGE_MAP()

// CMy062201View 构造/析构

CMy062201View::CMy062201View()
{
	// TODO: 在此处添加构造代码
	snake.SetSize(1);
	snake.SetAt(0,CPoint(300,50));
	snake.Add(CPoint(250,50));
	snake.Add(CPoint(200,50));
	snake.Add(CPoint(150,50));
	snake.Add(CPoint(100,50));
	food.x=800;
	food.y=50;
	dir=4;
	
	//载入位图资源，读位图信息
	BITMAP BM;
	m_Bitmap_snake.LoadBitmap(IDB_BITMAP3);//IDB_BITMAP3蛇头位图ID右
	m_Bitmap_snake.GetBitmap(&BM);
	m_nWidth_snake=BM.bmWidth;
	m_nHeight_snake=BM.bmHeight;

	m_Bitmap_snake1.LoadBitmap(IDB_BITMAP2);//IDB_BITMAP2蛇身位图ID
	m_Bitmap_snake1.GetBitmap(&BM);
	m_nWidth_snake1=BM.bmWidth;
	m_nHeight_snake1=BM.bmHeight;

	m_Bitmap_snake2.LoadBitmap(IDB_BITMAP5);//IDB_BITMAP5蛇头位图ID左
	m_Bitmap_snake2.GetBitmap(&BM);
	m_nWidth_snake2=BM.bmWidth;
	m_nHeight_snake2=BM.bmHeight;

	m_Bitmap_snake3.LoadBitmap(IDB_BITMAP7);//IDB_BITMAP7蛇头位图ID上
	m_Bitmap_snake3.GetBitmap(&BM);
	m_nWidth_snake3=BM.bmWidth;
	m_nHeight_snake3=BM.bmHeight;

	m_Bitmap_snake4.LoadBitmap(IDB_BITMAP6);//IDB_BITMAP6蛇头位图ID下
	m_Bitmap_snake4.GetBitmap(&BM);
	m_nWidth_snake4=BM.bmWidth;
	m_nHeight_snake4=BM.bmHeight;

	m_Bitmap_snake5.LoadBitmap(IDB_BITMAP4);//IDB_BITMAP4背景
	m_Bitmap_snake5.GetBitmap(&BM);
	m_nWidth_snake5=BM.bmWidth;
	m_nHeight_snake5=BM.bmHeight;

	m_Bitmap_food.LoadBitmap(IDB_BITMAP1);//IDB_BITMAP1食物
	m_Bitmap_food.GetBitmap(&BM);
	m_nWidth_food=BM.bmWidth;
	m_nHeight_food=BM.bmHeight;
	m_level=1;
	score=0;


	// 在构造函数中创建自定义字体对象
    m_Font.CreateFont(70, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
    OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
    DEFAULT_PITCH | FF_SWISS, _T("Arial"));
}

CMy062201View::~CMy062201View()
{
}

BOOL CMy062201View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy062201View 绘制

void CMy062201View::OnDraw(CDC* pDC)
{
	CMy062201Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
 
		
    CClientDC dc(this);
    CRect rect1; 
    GetClientRect(&rect1); //得到窗体的大小 
    CDC dcMem; 
    dcMem.CreateCompatibleDC(&dc); 
    CBitmap bmpBackground; 
    bmpBackground.LoadBitmap(IDB_BITMAP4);//加载背景图片 
    BITMAP bitMap; 
    bmpBackground.GetBitmap(&bitMap); 
    CBitmap *pbmpOld=dcMem.SelectObject(&bmpBackground); 
    dc.StretchBlt(0,0,rect1.Width(),rect1.Height(),&dcMem,0,0,bitMap.bmWidth,bitMap.bmHeight,SRCCOPY);


	for(int i=0;i<snake.GetSize();i++)
	{
        if (i == 0)
        {
            CDC MemDC_snake;
            MemDC_snake.CreateCompatibleDC(NULL);

            // 根据头部方向选择不同的位图
            if (dir == 1) {
                MemDC_snake.SelectObject(&m_Bitmap_snake3); // 上
            } else if (dir == 2) {
                MemDC_snake.SelectObject(&m_Bitmap_snake4); // 下
            } else if (dir == 3) {
                MemDC_snake.SelectObject(&m_Bitmap_snake2);   // 左
            } else if (dir == 4) {
                MemDC_snake.SelectObject(&m_Bitmap_snake); // 右
            }

            pDC->StretchBlt(snake[i].x - 25, snake[i].y - 25, 50, 50, &MemDC_snake, 0, 0, m_nWidth_snake, m_nHeight_snake, SRCCOPY);
        }
		
		else
		{
			CDC MemDC_snake1;
			MemDC_snake1.CreateCompatibleDC(NULL);
			MemDC_snake1.SelectObject(&m_Bitmap_snake1);
			pDC->StretchBlt(snake[i].x-25,snake[i].y-25,50,50,&MemDC_snake1,0,0,m_nWidth_snake1,m_nHeight_snake1,SRCCOPY);
		}
			
	}
	CDC MemDC_food;
	MemDC_food.CreateCompatibleDC(NULL);
	MemDC_food.SelectObject(&m_Bitmap_food);
	pDC->StretchBlt(food.x-25,food.y-25,50,50,&MemDC_food,0,0,m_nWidth_food,m_nHeight_food,SRCCOPY);
	// 在OnDraw()函数中绘制得分信息
    CFont* pOldFont = pDC->SelectObject(&m_Font);
    COLORREF textColor = RGB(159,43,104); // 设置文本颜色为红色
    pDC->SetTextColor(textColor);
    pDC->SetBkMode(TRANSPARENT); // 设置背景透明
    CString strScore;
    strScore.Format(_T("Score: %d"), score);
    pDC->TextOut(10, 40, strScore);
    pDC->SelectObject(pOldFont); // 恢复原有字体对象
  
	   // 创建字体对象并设置字体属性
    CFont font1;
    font1.CreatePointFont(120, _T("Arial"));  // 设置字体大小为 12，字体为 Arial
	COLORREF textColor1 = RGB(199,33,124); // 设置文本颜色为红色
    pDC->SetTextColor(textColor1);
    pDC->SetBkMode(TRANSPARENT); // 设置背景透明
    // 将字体对象与设备上下文相关联
    CFont* pOldFont1 = pDC->SelectObject(&font1);

   	CString text1 =_T("单机鼠标右键可以选择可爱蛇的速度呦！");
    pDC->TextOut(1000, 10, text1);

	CString text =_T("小心可爱蛇碰到边界就die了哦");
    pDC->TextOut(1200, 50, text);

	CString text2 =_T("吃到1个食物+5分！！！");
    pDC->TextOut(1300, 90, text2);
    // 恢复原来的字体对象
    pDC->SelectObject(pOldFont1);

} 


// CMy062201View 打印

BOOL CMy062201View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy062201View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMy062201View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMy062201View 诊断

#ifdef _DEBUG
void CMy062201View::AssertValid() const
{
	CView::AssertValid();
}

void CMy062201View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy062201Doc* CMy062201View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy062201Doc)));
	return (CMy062201Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy062201View 消息处理程序


void CMy062201View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	CView::OnLButtonDown(nFlags, point);
}


void CMy062201View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
		CMyDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		m_level=dlg.m_num;
		Invalidate();
	}
	CView::OnRButtonDown(nFlags, point);
}


void CMy062201View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case 1:
	{
		CRect rect;
		GetClientRect(rect);
		if (snake[0].x <= rect.left || snake[0].x >= rect.right - m_nWidth_snake ||
			snake[0].y <= rect.top || snake[0].y >= rect.bottom - m_nHeight_snake)
		{
			KillTimer(1);
			MessageBox(_T("游戏结束，再玩一次吧！！！"), _T("警告"), MB_OK | MB_ICONWARNING);
		}
		else
		{
			// 移动贪吃蛇
			for (int i = snake.GetSize() - 1; i > 0; i--)
			{
				snake[i] = snake[i - 1];
			}
			switch (dir)
			{
			case 1: // 上
				snake[0].y -= m_nHeight_snake;
				break;
			case 2: // 下
				snake[0].y += m_nHeight_snake;
				break;
			case 3: // 左
				snake[0].x -= m_nWidth_snake;
				break;
			case 4: // 右
				snake[0].x += m_nWidth_snake;
				break;
			default:
				break;
			}

			// 判断是否吃到食物
			if (snake[0] == food)
			{
				snake.Add(CPoint(-1, -1)); // 添加新的贪吃蛇身体
				generateNewFood(); // 生成新的食物位置
				 score += 5; // 增加得分
			}

			Invalidate();
		}
	}
	break;
	default:
		break;
	}


	CView::OnTimer(nIDEvent);
}


void CMy062201View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nChar)
	{
	case VK_UP: // 上
		if (dir != 2) dir = 1;
		break;
	case VK_DOWN: // 下
		if (dir != 1) dir = 2;
		break;
	case VK_LEFT: // 左
		if (dir != 4) dir = 3;
		break;
	case VK_RIGHT: // 右
		if (dir != 3) dir = 4;
		break;
	default:
		break;
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMy062201View::OnEnd()
{
	// TODO: 在此添加命令处理程序代码
	KillTimer(1);
	//停止播放程序中的声音文件
	sndPlaySound(NULL,SND_SYNC);
	MessageBox(_T("游戏结束，再玩一次吧！！！"));
	score=0;
}


void CMy062201View::OnStart()
{
	// TODO: 在此添加命令处理程序代码
	    isPaused = false;
	SetTimer(1,500/m_level,NULL);
	//异步模式播放，并且循环播放，
	sndPlaySound(L"res\\music1.wav",SND_ASYNC|SND_LOOP);
	//*****
		snake.RemoveAll(); // 清空贪吃蛇身体
	snake.Add(CPoint(125, 125));
	snake.Add(CPoint(125, 150));
	snake.Add(CPoint(125, 175));
	generateNewFood(); // 生成食物位置
	//*****
}
//********
void CMy062201View::generateNewFood()
{
    // 生成随机的食物位置
    CRect rect;
    GetClientRect(rect);
    int maxX = rect.right - 50;
    int maxY = rect.bottom - 50;

    srand(time(NULL));
    int x = (rand() % (maxX / 50)) * 50 + 25;
    int y = (rand() % (maxY / 50)) * 50 + 25;

    food = CPoint(x, y);
}


void CMy062201View::OnTing()
{
	// TODO: 在此添加命令处理程序代码
	   
   KillTimer(1);
         isPaused = true;
    // 显示暂停界面或提示信息
    MessageBox(L"游戏已暂停", L"提示", MB_OK | MB_ICONINFORMATION);
}


void CMy062201View::OnJixv()
{
	// TODO: 在此添加命令处理程序代码
	   if (isPaused) {
        SetTimer(1, 500 / m_level, NULL);
        isPaused = false;
        
        // 添加代码以恢复游戏状态
        MessageBox(L"游戏已恢复", L"提示", MB_OK | MB_ICONINFORMATION);
    }
}
