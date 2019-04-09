// TimeAxisCtrl.h : main header file for the TimeAxisCtrl DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTimeAxisCtrlApp
// See TimeAxisCtrl.cpp for the implementation of this class
//

class CTimeAxisCtrlApp : public CWinApp
{
public:
	CTimeAxisCtrlApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
