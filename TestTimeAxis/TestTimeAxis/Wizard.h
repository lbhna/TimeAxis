#pragma once



// CWizard
#include "page1.h"
#include "page2.h"

class CWizard : public CPropertySheet
{
	DECLARE_DYNAMIC(CWizard)
	CPage1 thePage1;
	CPage2 thePage2;

public:
	CWizard(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CWizard(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CWizard();

protected:
	DECLARE_MESSAGE_MAP()
};


