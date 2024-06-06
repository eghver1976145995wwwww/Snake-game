
// 062201View.h : CMy062201View 类的接口
//
//以下5行为添加
#include<afxtempl.h>
#include"MyDlg.h"
#include"mmsystem.h"
//****
#include <random> // 添加随机数生成器的头文件
#include <ctime>  // 添加时间头文件
//*****
#include <afxwin.h>

#pragma once

class CMy062201View : public CView
{
protected: // 仅从序列化创建
	CMy062201View();
	DECLARE_DYNCREATE(CMy062201View)

// 特性
public:
	CMy062201Doc* GetDocument() const;
	//******

	bool isPaused;
	CFont m_Font;
	//贪吃蛇身体数据结构
   CArray <CPoint,CPoint&> snake;
   //食物数据结构
    CPoint food;
	//运动方向
	int dir;
	//得分情况
	int score;
	//定义CBitmap类对象以及位图的高度和宽度变量
	CBitmap m_Bitmap_snake,m_Bitmap_food,m_Bitmap_snake1,m_Bitmap_snake2,m_Bitmap_snake3,m_Bitmap_snake4,m_Bitmap_snake5;
	int m_nHeight_snake,m_nHeight_food;
	int m_nWidth_snake,m_nWidth_food;
	int m_nWidth_snake1,m_nHeight_snake1;
	int m_nWidth_snake2,m_nHeight_snake2;
	int m_nWidth_snake3,m_nHeight_snake3;
	int m_nWidth_snake4,m_nHeight_snake4;
	int m_nWidth_snake5,m_nHeight_snake5;
	int m_level; 
// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//*****
	// 生成新的随机食物位置
	void generateNewFood();
	
// 声明全局变量
	

// 实现
public:
	virtual ~CMy062201View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:


// 生成的消息映射函数
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

#ifndef _DEBUG  // 062201View.cpp 中的调试版本
inline CMy062201Doc* CMy062201View::GetDocument() const
   { return reinterpret_cast<CMy062201Doc*>(m_pDocument); }
#endif

