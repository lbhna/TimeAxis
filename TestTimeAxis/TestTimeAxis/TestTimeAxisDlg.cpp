
// TestTimeAxisDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestTimeAxis.h"
#include "TestTimeAxisDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestTimeAxisDlg dialog




CTestTimeAxisDlg::CTestTimeAxisDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestTimeAxisDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestTimeAxisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestTimeAxisDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_MESSAGE(TAMSG_ID,OnTimeAxisMessage)
END_MESSAGE_MAP()


// CTestTimeAxisDlg message handlers
// CTimeAxisWnd message handlers
LRESULT CTestTimeAxisDlg::OnTimeAxisMessage(WPARAM wp,LPARAM lp)
{
	LPTAMsg			pMsg =(LPTAMsg)wp;
	DWORD			menuID=0;
	POINT	pt;
	GetCursorPos(&pt);
	switch(pMsg->message)
	{
	case TAMSG_LDCLICKED:
		{
			switch(pMsg->pObject->GetType())
			{
			case TAOT_Anchor:
				{
					CString str;
					str.Format("◊Ûº¸À´ª˜¡À[ %s ] °£°£°£",pMsg->pObject->GetName());
					AfxMessageBox(str);
				}
				break;
			case TAOT_Frame:
				{
					CString str;
					str.Format("◊Ûº¸À´ª˜¡À[ %s ] °£°£°£",pMsg->pObject->GetName());
					AfxMessageBox(str);
				}
				break;
			}		
		}
		break;
	case TAMSG_RCLICKED:
		{
			CMenu	menu;
			menu.LoadMenu(IDR_RBUTTON_MENU);

			switch(pMsg->pObject->GetType())
			{
			case TAOT_Anchor:
				{
					menuID=menu.GetSubMenu(1)->TrackPopupMenu(TPM_RIGHTBUTTON|TPM_NONOTIFY|TPM_RETURNCMD,pt.x,pt.y,this);

				}
				break;
			case TAOT_Frame:
				{
					menuID=menu.GetSubMenu(0)->TrackPopupMenu(TPM_RIGHTBUTTON|TPM_NONOTIFY|TPM_RETURNCMD,pt.x,pt.y,this);
				}
				break;
			}
		}
		break;
	case TAMSG_RCLICKED_LINKLINE:
		{
			CMenu	menu;
			menu.LoadMenu(IDR_RBUTTON_MENU);
			menuID=menu.GetSubMenu(2)->TrackPopupMenu(TPM_RIGHTBUTTON|TPM_NONOTIFY|TPM_RETURNCMD,pt.x,pt.y,this);

		}
		break;

	}
	return 0;
}
#include "Wizard.h"
BOOL CTestTimeAxisDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	


	m_theTimeAxisCtrl.Create(m_hWnd,100,100);
	m_theTimeAxisCtrl.SetPos(0,50);
	CRect rect;
	GetClientRect(rect);
	m_theTimeAxisCtrl.SetSize(rect.Width(),rect.Height()-50);

	

	CTAFrame*	pRootFrame	=m_theTimeAxisCtrl.AddFrame(TAOST_OBJECT	,"F16"	,"...");
	CTAFrame*	pFrame	=pRootFrame->AddFrame(TAOST_OBJECT	,"ª˙…Ì"	,"...");
	CTAAnchor*	pPrev=NULL,*pThis;
	for(int i=0;i<20;i++)
	{
		pThis =pFrame->AddAnchor(300*(i+1),TAOST_Anchor_DoubleCircle,	RGB(10,0,255),0);
		pThis->SetName("Anchor");
		pThis->SetEndTime(200);

		if(pPrev != NULL && i%3==0)
		{
			pThis->SetPrev(pPrev);
		}
		pPrev =pThis;
	}




	pFrame->AddFrame(TAOST_OBJECT	,"◊Ûª˙“Ì"	,"...");

	pFrame->AddFrame(TAOST_OBJECT	,"◊Ûª˙“Ì"	,"...");
	pFrame->AddFrame(TAOST_OBJECT	,"◊Û¬÷"	,"...")->AddFrame(TAOST_OBJECT	,"÷·"	,"...");
	pFrame->AddFrame(TAOST_OBJECT	,"”“¬÷"	,"...")->AddFrame(TAOST_OBJECT	,"÷·"	,"...");
	pFrame->AddFrame(TAOST_OBJECT	,"«∞¬÷"	,"...")->AddFrame(TAOST_OBJECT	,"÷·"	,"...");
	pRootFrame->Expand(TRUE);
	pFrame->Expand(TRUE);
	
	pFrame	=pRootFrame->AddFrame(TAOST_OBJECT	,"µºµØ1"	,"...")->AddFrame(TAOST_OBJECT	,"µØÕ∑"	,"...");
	pFrame	=pRootFrame->AddFrame(TAOST_OBJECT	,"µºµØ2"	,"...")->AddFrame(TAOST_OBJECT	,"µØÕ∑"	,"...");
	pFrame	=pRootFrame->AddFrame(TAOST_OBJECT	,"µºµØ3"	,"...")->AddFrame(TAOST_OBJECT	,"µØÕ∑"	,"...");
	pFrame	=pRootFrame->AddFrame(TAOST_OBJECT	,"µºµØ4"	,"...")->AddFrame(TAOST_OBJECT	,"µØÕ∑"	,"...");
	pFrame	=pRootFrame->AddFrame(TAOST_OBJECT	,"µºµØ5"	,"...")->AddFrame(TAOST_OBJECT	,"µØÕ∑"	,"...");
	pFrame	=pRootFrame->AddFrame(TAOST_OBJECT	,"µºµØ6"	,"...")->AddFrame(TAOST_OBJECT	,"µØÕ∑"	,"...");

	pFrame	=pRootFrame->AddFrame(TAOST_OBJECT	,"Œ≤“Ì"	,"...");
	//for(int i=0;i<20;i++)
	//{
	//	pFrame->AddAnchor(300*(i+1),TAOST_Anchor_CircleReal,	RGB(10,0,255),0)->SetName("Anchor");
	//}

	m_theTimeAxisCtrl.UpdateScrollBar();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestTimeAxisDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestTimeAxisDlg::OnPaint()
{

	CDialogEx::OnPaint();
	
	m_theTimeAxisCtrl.Draw(FALSE);
	
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestTimeAxisDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestTimeAxisDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);



	CRect rect;
	GetClientRect(rect);
	m_theTimeAxisCtrl.SetSize(rect.Width(),rect.Height()-50);

	
}


BOOL CTestTimeAxisDlg::PreTranslateMessage(MSG* pMsg)
{

	if(m_theTimeAxisCtrl.PreTranslateMessage(pMsg))
		return FALSE;


	return CDialogEx::PreTranslateMessage(pMsg);
}
