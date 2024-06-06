
// 062201View.cpp : CMy062201View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
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

// CMy062201View ����/����

CMy062201View::CMy062201View()
{
	// TODO: �ڴ˴���ӹ������
	snake.SetSize(1);
	snake.SetAt(0,CPoint(300,50));
	snake.Add(CPoint(250,50));
	snake.Add(CPoint(200,50));
	snake.Add(CPoint(150,50));
	snake.Add(CPoint(100,50));
	food.x=800;
	food.y=50;
	dir=4;
	
	//����λͼ��Դ����λͼ��Ϣ
	BITMAP BM;
	m_Bitmap_snake.LoadBitmap(IDB_BITMAP3);//IDB_BITMAP3��ͷλͼID��
	m_Bitmap_snake.GetBitmap(&BM);
	m_nWidth_snake=BM.bmWidth;
	m_nHeight_snake=BM.bmHeight;

	m_Bitmap_snake1.LoadBitmap(IDB_BITMAP2);//IDB_BITMAP2����λͼID
	m_Bitmap_snake1.GetBitmap(&BM);
	m_nWidth_snake1=BM.bmWidth;
	m_nHeight_snake1=BM.bmHeight;

	m_Bitmap_snake2.LoadBitmap(IDB_BITMAP5);//IDB_BITMAP5��ͷλͼID��
	m_Bitmap_snake2.GetBitmap(&BM);
	m_nWidth_snake2=BM.bmWidth;
	m_nHeight_snake2=BM.bmHeight;

	m_Bitmap_snake3.LoadBitmap(IDB_BITMAP7);//IDB_BITMAP7��ͷλͼID��
	m_Bitmap_snake3.GetBitmap(&BM);
	m_nWidth_snake3=BM.bmWidth;
	m_nHeight_snake3=BM.bmHeight;

	m_Bitmap_snake4.LoadBitmap(IDB_BITMAP6);//IDB_BITMAP6��ͷλͼID��
	m_Bitmap_snake4.GetBitmap(&BM);
	m_nWidth_snake4=BM.bmWidth;
	m_nHeight_snake4=BM.bmHeight;

	m_Bitmap_snake5.LoadBitmap(IDB_BITMAP4);//IDB_BITMAP4����
	m_Bitmap_snake5.GetBitmap(&BM);
	m_nWidth_snake5=BM.bmWidth;
	m_nHeight_snake5=BM.bmHeight;

	m_Bitmap_food.LoadBitmap(IDB_BITMAP1);//IDB_BITMAP1ʳ��
	m_Bitmap_food.GetBitmap(&BM);
	m_nWidth_food=BM.bmWidth;
	m_nHeight_food=BM.bmHeight;
	m_level=1;
	score=0;


	// �ڹ��캯���д����Զ����������
    m_Font.CreateFont(70, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
    OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
    DEFAULT_PITCH | FF_SWISS, _T("Arial"));
}

CMy062201View::~CMy062201View()
{
}

BOOL CMy062201View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMy062201View ����

void CMy062201View::OnDraw(CDC* pDC)
{
	CMy062201Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
 
		
    CClientDC dc(this);
    CRect rect1; 
    GetClientRect(&rect1); //�õ�����Ĵ�С 
    CDC dcMem; 
    dcMem.CreateCompatibleDC(&dc); 
    CBitmap bmpBackground; 
    bmpBackground.LoadBitmap(IDB_BITMAP4);//���ر���ͼƬ 
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

            // ����ͷ������ѡ��ͬ��λͼ
            if (dir == 1) {
                MemDC_snake.SelectObject(&m_Bitmap_snake3); // ��
            } else if (dir == 2) {
                MemDC_snake.SelectObject(&m_Bitmap_snake4); // ��
            } else if (dir == 3) {
                MemDC_snake.SelectObject(&m_Bitmap_snake2);   // ��
            } else if (dir == 4) {
                MemDC_snake.SelectObject(&m_Bitmap_snake); // ��
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
	// ��OnDraw()�����л��Ƶ÷���Ϣ
    CFont* pOldFont = pDC->SelectObject(&m_Font);
    COLORREF textColor = RGB(159,43,104); // �����ı���ɫΪ��ɫ
    pDC->SetTextColor(textColor);
    pDC->SetBkMode(TRANSPARENT); // ���ñ���͸��
    CString strScore;
    strScore.Format(_T("Score: %d"), score);
    pDC->TextOut(10, 40, strScore);
    pDC->SelectObject(pOldFont); // �ָ�ԭ���������
  
	   // �����������������������
    CFont font1;
    font1.CreatePointFont(120, _T("Arial"));  // ���������СΪ 12������Ϊ Arial
	COLORREF textColor1 = RGB(199,33,124); // �����ı���ɫΪ��ɫ
    pDC->SetTextColor(textColor1);
    pDC->SetBkMode(TRANSPARENT); // ���ñ���͸��
    // ������������豸�����������
    CFont* pOldFont1 = pDC->SelectObject(&font1);

   	CString text1 =_T("��������Ҽ�����ѡ��ɰ��ߵ��ٶ��ϣ�");
    pDC->TextOut(1000, 10, text1);

	CString text =_T("С�Ŀɰ��������߽��die��Ŷ");
    pDC->TextOut(1200, 50, text);

	CString text2 =_T("�Ե�1��ʳ��+5�֣�����");
    pDC->TextOut(1300, 90, text2);
    // �ָ�ԭ�����������
    pDC->SelectObject(pOldFont1);

} 


// CMy062201View ��ӡ

BOOL CMy062201View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMy062201View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMy062201View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CMy062201View ���

#ifdef _DEBUG
void CMy062201View::AssertValid() const
{
	CView::AssertValid();
}

void CMy062201View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy062201Doc* CMy062201View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy062201Doc)));
	return (CMy062201Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy062201View ��Ϣ�������


void CMy062201View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	CView::OnLButtonDown(nFlags, point);
}


void CMy062201View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
			MessageBox(_T("��Ϸ����������һ�ΰɣ�����"), _T("����"), MB_OK | MB_ICONWARNING);
		}
		else
		{
			// �ƶ�̰����
			for (int i = snake.GetSize() - 1; i > 0; i--)
			{
				snake[i] = snake[i - 1];
			}
			switch (dir)
			{
			case 1: // ��
				snake[0].y -= m_nHeight_snake;
				break;
			case 2: // ��
				snake[0].y += m_nHeight_snake;
				break;
			case 3: // ��
				snake[0].x -= m_nWidth_snake;
				break;
			case 4: // ��
				snake[0].x += m_nWidth_snake;
				break;
			default:
				break;
			}

			// �ж��Ƿ�Ե�ʳ��
			if (snake[0] == food)
			{
				snake.Add(CPoint(-1, -1)); // ����µ�̰��������
				generateNewFood(); // �����µ�ʳ��λ��
				 score += 5; // ���ӵ÷�
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nChar)
	{
	case VK_UP: // ��
		if (dir != 2) dir = 1;
		break;
	case VK_DOWN: // ��
		if (dir != 1) dir = 2;
		break;
	case VK_LEFT: // ��
		if (dir != 4) dir = 3;
		break;
	case VK_RIGHT: // ��
		if (dir != 3) dir = 4;
		break;
	default:
		break;
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMy062201View::OnEnd()
{
	// TODO: �ڴ���������������
	KillTimer(1);
	//ֹͣ���ų����е������ļ�
	sndPlaySound(NULL,SND_SYNC);
	MessageBox(_T("��Ϸ����������һ�ΰɣ�����"));
	score=0;
}


void CMy062201View::OnStart()
{
	// TODO: �ڴ���������������
	    isPaused = false;
	SetTimer(1,500/m_level,NULL);
	//�첽ģʽ���ţ�����ѭ�����ţ�
	sndPlaySound(L"res\\music1.wav",SND_ASYNC|SND_LOOP);
	//*****
		snake.RemoveAll(); // ���̰��������
	snake.Add(CPoint(125, 125));
	snake.Add(CPoint(125, 150));
	snake.Add(CPoint(125, 175));
	generateNewFood(); // ����ʳ��λ��
	//*****
}
//********
void CMy062201View::generateNewFood()
{
    // ���������ʳ��λ��
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
	// TODO: �ڴ���������������
	   
   KillTimer(1);
         isPaused = true;
    // ��ʾ��ͣ�������ʾ��Ϣ
    MessageBox(L"��Ϸ����ͣ", L"��ʾ", MB_OK | MB_ICONINFORMATION);
}


void CMy062201View::OnJixv()
{
	// TODO: �ڴ���������������
	   if (isPaused) {
        SetTimer(1, 500 / m_level, NULL);
        isPaused = false;
        
        // ��Ӵ����Իָ���Ϸ״̬
        MessageBox(L"��Ϸ�ѻָ�", L"��ʾ", MB_OK | MB_ICONINFORMATION);
    }
}
