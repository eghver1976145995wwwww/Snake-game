// MyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "062201.h"
#include "MyDlg.h"
#include "afxdialogex.h"


// CMyDlg �Ի���

IMPLEMENT_DYNAMIC(CMyDlg, CDialogEx)

CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyDlg::IDD, pParent)
{

	m_num = 0;
}

CMyDlg::~CMyDlg()
{
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_num);
	DDV_MinMaxInt(pDX, m_num, 1, 10);

}


BEGIN_MESSAGE_MAP(CMyDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyDlg ��Ϣ�������
