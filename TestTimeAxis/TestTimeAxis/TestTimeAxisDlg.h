
// TestTimeAxisDlg.h : header file
//

#pragma once
#include "TimeAxis.h"
using namespace TimeAxis;

// CTestTimeAxisDlg dialog
class CTestTimeAxisDlg : public CDialogEx
{
protected:
	CTimeAxis		m_theTimeAxisCtrl;
// Construction
public:
	CTestTimeAxisDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TESTTIMEAXIS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg LRESULT OnTimeAxisMessage(WPARAM wp,LPARAM lp);
};
