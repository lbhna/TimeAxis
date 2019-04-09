// Wizard.cpp : implementation file
//

#include "stdafx.h"
#include "TestTimeAxis.h"
#include "Wizard.h"


// CWizard

IMPLEMENT_DYNAMIC(CWizard, CPropertySheet)

CWizard::CWizard(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddPage(&thePage1);
	AddPage(&thePage2);
}

CWizard::CWizard(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&thePage1);
	AddPage(&thePage2);

}

CWizard::~CWizard()
{
}


BEGIN_MESSAGE_MAP(CWizard, CPropertySheet)
END_MESSAGE_MAP()


// CWizard message handlers
