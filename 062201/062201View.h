
// 062201View.h : CMy062201View ��Ľӿ�
//
//����5��Ϊ���
#include<afxtempl.h>
#include"MyDlg.h"
#include"mmsystem.h"
//****
#include <random> // ����������������ͷ�ļ�
#include <ctime>  // ���ʱ��ͷ�ļ�
//*****
#include <afxwin.h>

#pragma once

class CMy062201View : public CView
{
protected: // �������л�����
	CMy062201View();
	DECLARE_DYNCREATE(CMy062201View)

// ����
public:
	CMy062201Doc* GetDocument() const;
	//******

	bool isPaused;
	CFont m_Font;
	//̰�����������ݽṹ
   CArray <CPoint,CPoint&> snake;
   //ʳ�����ݽṹ
    CPoint food;
	//�˶�����
	int dir;
	//�÷����
	int score;
	//����CBitmap������Լ�λͼ�ĸ߶ȺͿ�ȱ���
	CBitmap m_Bitmap_snake,m_Bitmap_food,m_Bitmap_snake1,m_Bitmap_snake2,m_Bitmap_snake3,m_Bitmap_snake4,m_Bitmap_snake5;
	int m_nHeight_snake,m_nHeight_food;
	int m_nWidth_snake,m_nWidth_food;
	int m_nWidth_snake1,m_nHeight_snake1;
	int m_nWidth_snake2,m_nHeight_snake2;
	int m_nWidth_snake3,m_nHeight_snake3;
	int m_nWidth_snake4,m_nHeight_snake4;
	int m_nWidth_snake5,m_nHeight_snake5;
	int m_level; 
// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//*****
	// �����µ����ʳ��λ��
	void generateNewFood();
	
// ����ȫ�ֱ���
	

// ʵ��
public:
	virtual ~CMy062201View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:


// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEnd();
	afx_msg void OnStart();

	afx_msg void OnTing();
	afx_msg void OnJixv();
};

#ifndef _DEBUG  // 062201View.cpp �еĵ��԰汾
inline CMy062201Doc* CMy062201View::GetDocument() const
   { return reinterpret_cast<CMy062201Doc*>(m_pDocument); }
#endif

