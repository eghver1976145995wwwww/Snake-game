#pragma once


// CMyDlg �Ի���

class CMyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDlg)

public:
	CMyDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_num;
	afx_msg void OnEnChangeEdit1();
};
