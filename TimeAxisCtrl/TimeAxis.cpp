#include "stdafx.h"
#include "TimeAxis.h"

namespace TimeAxis
{

	VOID	ChangeCursor(UINT uCursorResourceID)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		SetCursor(LoadCursor(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(uCursorResourceID)));
	}
	DWORD	CTATime::m_dwTimeRateArray[]=
	{
		1,2,5,
		10,20,50,
		100,200,500,
		1000,2000,5000,
		10000,20000,50000,
		100000,
	};
	CTATime::CTATime()
	{
		m_dwCurTime				=0;
		m_dwStartTime			=0;
		m_dwEndTime				=1000*10000;
		m_dwUnitSize			=15;
		m_dwTimePerUnit			=100;
		m_dwWidth				=0;
		m_dwUnitMaxSize			=20;
		m_dwUnitMinSize			=3;
	}
	LONG		CTATime::GetCurrentPos()
	{
		return TimeToOffset(m_dwCurTime);
	}
	LONG		CTATime::TimeToOffset(DWORD IN dwTime)
	{
		if(dwTime < m_dwStartTime)
			return -1;
		if(dwTime == m_dwStartTime)
			return 0;
		return (DWORD)(((float)(dwTime-m_dwStartTime)/(float)m_dwTimePerUnit)*(float)m_dwUnitSize);
	}
	DWORD		CTATime::OffsetToTime(LONG IN lOffset)
	{
		if(lOffset==0)
			return 0;
		LONG	time =(LONG)((float)m_dwStartTime + (float)((float)lOffset/(float)m_dwUnitSize)*(float)m_dwTimePerUnit);
		if(time < 0)
			time=0;
		return time;
	}
	BOOL		CTATime::TimeRateUpdate(WORD IN wKey,LONG IN zDelta)
	{
		if(wKey == MK_CONTROL)
		{
			DWORD	OldSize =m_dwUnitSize;

			m_dwUnitSize +=zDelta;
			if(m_dwUnitSize > m_dwUnitMaxSize)
				m_dwUnitSize =m_dwUnitMaxSize;
			if(m_dwUnitSize < m_dwUnitMinSize)
				m_dwUnitSize = m_dwUnitMinSize;
			if(OldSize == m_dwUnitSize )
				return FALSE;
			return TRUE;
		}
		int		index =0,i=0;
		for(i=0;i<TIME_RATE_ARRAY_SIZE;i++)
		{
			if(m_dwTimeRateArray[i] == m_dwTimePerUnit)
			{
				index =i;
				break;
			}
		}

		index -= zDelta;
		if(index >= TIME_RATE_ARRAY_SIZE)
			index =TIME_RATE_ARRAY_SIZE-1;
		if(index < 0)
			index =0;
		if(index == i)//没有变化
			return FALSE;

		m_dwTimePerUnit		=m_dwTimeRateArray[index];
		if(m_dwStartTime < m_dwTimePerUnit)
			m_dwStartTime =0;
		return TRUE;
	}
	//---------------------------------------------
	CTAAnchorStyle::CTAAnchorStyle()
	{
		m_dwAnchorSize			=16;
		m_SelectedFrameColor	=RGB(255,100,200);
		m_hSelectedFramePen		=NULL;
		m_hAnchorFont			=NULL;
		m_lSelectedFrameSpace	=1;
		m_strAnchorFontName		=_T("宋体");


		m_LinkLineColor			=RGB(0,0,0);
		m_LinkLineActiveColor	=RGB(255,255,100);
		m_LinkLineWidth			=1;
		m_LinkLineStyle			=PS_DOT;
		m_hLinkPen				=NULL;
		m_hLinkActivePen		=NULL;
		m_hTimeRangePen			=NULL;
		m_TimeRangeColor		=RGB(125,125,125);
		m_hTimeRangeActivePen	=NULL;
		m_TimeRangeActiveColor	=RGB(200,255,100);

		m_DisableColor			=RGB(255,0,0);
	}
	CTAAnchorStyle::~CTAAnchorStyle()
	{
		Safe_DeleteObject(m_hSelectedFramePen);
		Safe_DeleteObject(m_hLinkPen);
		Safe_DeleteObject(m_hTimeRangePen);
		Safe_DeleteObject(m_hTimeRangeActivePen);
		Safe_DeleteObject(m_hAnchorFont);
	}
	VOID	CTAAnchorStyle::InitGDIObject()
	{
		Safe_DeleteObject(m_hSelectedFramePen);
		Safe_DeleteObject(m_hAnchorFont);
		Safe_DeleteObject(m_hLinkPen);
		Safe_DeleteObject(m_hTimeRangeActivePen);
		Safe_DeleteObject(m_hTimeRangePen);
		Safe_DeleteObject(m_hDisablePen);

		m_hSelectedFramePen		=CreatePen(PS_SOLID,1,m_SelectedFrameColor);
		m_hLinkPen				=CreatePen(m_LinkLineStyle,m_LinkLineWidth,m_LinkLineColor);
		m_hLinkActivePen		=CreatePen(m_LinkLineStyle,m_LinkLineWidth,m_LinkLineActiveColor);

		LOGFONT		lf;
		ZeroMemory(&lf,sizeof(lf));
		lf.lfCharSet	=GB2312_CHARSET;
		strcpy(lf.lfFaceName,m_strAnchorFontName.GetBuffer(0));
		lf.lfHeight		=m_dwAnchorSize;
		m_hAnchorFont	=CreateFontIndirect(&lf);

		m_hTimeRangePen				=CreatePen(PS_DOT,1,m_TimeRangeColor);
		m_hTimeRangeActivePen		=CreatePen(PS_SOLID,1,m_TimeRangeActiveColor);
		m_hDisablePen				=CreatePen(PS_SOLID,2,m_DisableColor);



	}

	//---------------------------------------------
	CTAScrollStyle::CTAScrollStyle()
	{
		m_dwWidth		=9;

		m_BkColor		=RGB(210,210,210);
		m_BarColor		=RGB(50,150,250);
		m_BarBorderColor=RGB(0,50,50);

	}
	CTAScrollStyle::~CTAScrollStyle()
	{
		Safe_DeleteObject(m_hBkPen);
		Safe_DeleteObject(m_hBkBrush);
		Safe_DeleteObject(m_hBarBorderPen);
		Safe_DeleteObject(m_hBarBrush);
	}
	VOID	CTAScrollStyle::InitGDIObject()
	{
		Safe_DeleteObject(m_hBkPen);
		Safe_DeleteObject(m_hBkBrush);
		Safe_DeleteObject(m_hBarBorderPen);
		Safe_DeleteObject(m_hBarBrush);

		m_hBkPen		=CreatePen(PS_SOLID,1,m_BkColor);
		m_hBkBrush		=CreateSolidBrush(m_BkColor);
		m_hBarBorderPen	=CreatePen(PS_SOLID,1,m_BarBorderColor);
		m_hBarBrush		=CreateSolidBrush(m_BarColor);
	}
	//---------------------------------------------
	CTAFrameStyle::CTAFrameStyle()
	{
		m_dwLeftMargin		=4;
		m_BorderColor		=RGB(50,50,100);
		m_BkColor1			=RGB(150,180,200);
		m_BkColor2			=RGB(200,200,200);
		m_ActiveBkColor		=RGB(100,150,255);
		m_DisableBkColor	=RGB(90,90,90);

		m_strNameFontName	=_T("宋体");
		m_dwNameFontNameSize=12;
		m_NameColor			=RGB(50,50,200);

		m_RootLineColor		=RGB(100,100,180);
		m_RootBorderColor	=RGB(150,150,200);
		m_RootFlagColor		=RGB(0,0,200);


		m_hNameFont			=NULL;
		m_hBorderPen		=NULL;
		m_hNormalBkBrush1	=NULL;
		m_hNormalBkBrush2	=NULL;
		m_hActiveBkBrush	=NULL;

		m_hRootLinePen		=NULL;
		m_hRootBorderPen	=NULL;
		m_hRootFlagPen		=NULL;


	}
	CTAFrameStyle::~CTAFrameStyle()
	{
		Safe_DeleteObject(m_hNameFont);
		Safe_DeleteObject(m_hBorderPen);
		Safe_DeleteObject(m_hNormalBkBrush1);
		Safe_DeleteObject(m_hNormalBkBrush2);
		Safe_DeleteObject(m_hActiveBkBrush);
		Safe_DeleteObject(m_hDisableBkBrush);

		Safe_DeleteObject(m_hRootLinePen);
		Safe_DeleteObject(m_hRootBorderPen);
		Safe_DeleteObject(m_hRootFlagPen);

	}
	VOID	CTAFrameStyle::InitGDIObject()
	{
		Safe_DeleteObject(m_hNameFont);
		Safe_DeleteObject(m_hBorderPen);
		Safe_DeleteObject(m_hNormalBkBrush1);
		Safe_DeleteObject(m_hNormalBkBrush2);
		Safe_DeleteObject(m_hActiveBkBrush);
		Safe_DeleteObject(m_hRootLinePen);
		Safe_DeleteObject(m_hRootBorderPen);
		Safe_DeleteObject(m_hRootFlagPen);
		Safe_DeleteObject(m_hDisableBkBrush);

		LOGFONT		lf;
		ZeroMemory(&lf,sizeof(lf));
		lf.lfCharSet		=GB2312_CHARSET;
		strcpy(lf.lfFaceName,m_strNameFontName.GetBuffer(0));
		lf.lfHeight			=m_dwNameFontNameSize;
		m_hNameFont			=CreateFontIndirect(&lf);

		m_hBorderPen		=CreatePen(PS_SOLID,1,m_BorderColor);
		m_hNormalBkBrush1	=CreateSolidBrush(m_BkColor1);
		m_hNormalBkBrush2	=CreateSolidBrush(m_BkColor2);
		m_hActiveBkBrush	=CreateSolidBrush(m_ActiveBkColor);		
		m_hDisableBkBrush	=CreateSolidBrush(m_DisableBkColor);		

		m_hRootLinePen		=CreatePen(PS_DOT,1,m_RootLineColor);
		m_hRootBorderPen	=CreatePen(PS_SOLID,1,m_RootBorderColor);
		m_hRootFlagPen		=CreatePen(PS_SOLID,1,m_RootFlagColor);
	}
	//---------------------------------------------
	CTAStyle::CTAStyle()
	{
		m_lFirstColumnWidth	=200;
		m_dwTitleHeight		=25;
		m_dwRowHeight		=20;
		m_dwLeftMargin		=2;
		m_dwRightMargin		=5;
		m_dwLevelSpace		=20;

		m_BkColor			=RGB(200,210,250);
		m_BorderColor		=RGB(50,50,80);

		m_TitleBkColor		=RGB(120,155,165);
		m_TitleColor		=RGB(0,0,50);
		m_TitleFontName		=_T("宋体");
		m_TitleFontSize		=16;

		m_CoordColor		=RGB(80,80,80);
		m_CoordTextColor	=RGB(150,150,255);
		m_CoordTextFontName =_T("宋体");
		m_CoordTextFontSize =12;

		m_TimeLineColor		=RGB(50,255,50);
		m_TimeLineTextColor	=RGB(150,255,150);



		m_hBackgroundBrush	=NULL;
		m_hTitleBkBrush		=NULL;
		m_hBorderPen		=NULL;
		m_hDragLinePen		=NULL;
		m_hTitleFont		=NULL;
		m_hCoordFont		=NULL;
		m_hTimeLinePen		=NULL;
		m_hCoordPen			=NULL;




		InitGDIObject();
	}
	CTAStyle::~CTAStyle()
	{
		Safe_DeleteObject(m_hBackgroundBrush);
		Safe_DeleteObject(m_hTitleBkBrush);
		Safe_DeleteObject(m_hBorderPen);
		Safe_DeleteObject(m_hDragLinePen);
		Safe_DeleteObject(m_hTimeLinePen);
		Safe_DeleteObject(m_hCoordPen);
		Safe_DeleteObject(m_hTitleFont);
		Safe_DeleteObject(m_hCoordFont);
	}
	VOID	CTAStyle::InitGDIObject()
	{
		Safe_DeleteObject(m_hBackgroundBrush);
		Safe_DeleteObject(m_hTitleBkBrush);
		Safe_DeleteObject(m_hBorderPen);
		Safe_DeleteObject(m_hDragLinePen);
		Safe_DeleteObject(m_hTimeLinePen);
		Safe_DeleteObject(m_hCoordPen);
		Safe_DeleteObject(m_hTitleFont);
		Safe_DeleteObject(m_hCoordFont);

		m_hBackgroundBrush	=CreateSolidBrush(m_BkColor);
		m_hTitleBkBrush		=CreateSolidBrush(m_TitleBkColor);
		m_hBorderPen		=CreatePen(PS_SOLID,1,m_BorderColor);
		m_hDragLinePen		=CreatePen(PS_DOT,1,m_BorderColor);
		m_hTimeLinePen		=CreatePen(PS_SOLID,2,m_TimeLineColor);
		m_hCoordPen			=CreatePen(PS_SOLID,1,m_CoordColor);


		LOGFONT		lf;
		ZeroMemory(&lf,sizeof(lf));
		lf.lfCharSet	=GB2312_CHARSET;
		lf.lfHeight		=m_TitleFontSize;
		strcpy(lf.lfFaceName,m_TitleFontName.GetBuffer(0));
		m_hTitleFont		=CreateFontIndirect(&lf);

		lf.lfHeight		=m_CoordTextFontSize;
		strcpy(lf.lfFaceName,m_CoordTextFontName.GetBuffer(0));
		m_hCoordFont		=CreateFontIndirect(&lf);


		m_theFrameStyle.InitGDIObject();
		m_theAnchorStyle.InitGDIObject();
		m_theScrollStyle.InitGDIObject();
	}
	//---------------------------------------------
	//---------------------------------------------
	//---------------------------------------------
	//---------------------------------------------

	//---------------------------------------------
	CTAObject::CTAObject(CTATime*	pTime,CTAStyle* pStyle)			
	{
		m_pTime			=pTime;
		m_pStyle		=pStyle;
		m_lRefCount		=1;	
		m_Type			=TAOT_Object;
		m_SubType		=TAOST_Unknown;
		m_UserData		=0;
		m_pParent		=NULL;
		m_bInvalidate	=TRUE;
		m_lLevel		=0;
		m_dwID			=(DWORD)(DWORD_PTR)this;
		m_pName			=new CHAR[1];
		m_pName[0]		=0;
		m_pDesc			=new CHAR[1];
		m_pDesc[0]		=0;
	}
	CTAObject::~CTAObject()
	{
		Safe_DeleteArray(m_pName);
		Safe_DeleteArray(m_pDesc);
	}
	VOID			CTAObject::Release()
	{
		--m_lRefCount;
		if(m_lRefCount ==0 )
			delete this;
	}

	CTAObjectList::CTAObjectList(CTATime*pTime,CTAStyle*pStyle):
		CTAObject(pTime,pStyle)
	{
		m_lMaxSize			=0;
		m_ppObj				=NULL;
		m_lCount			=0;
		m_Type				=TAOT_ObjectList;
	}

	CTAObjectList::~CTAObjectList(void)
	{
		Clear(TRUE);
	}
	inline LONG			CTAObjectList::GetCount()
	{
		return m_lCount;
	}
	VOID			CTAObjectList::Clear(BOOL IN bDestroyMem)
	{
		for(LONG i=0;i<m_lCount;i++)
		{
			m_ppObj[i]->Release();
			m_ppObj[i]=NULL;
		}
		m_lCount		=0;
		if(bDestroyMem )
		{
			Safe_DeleteArray(m_ppObj);
			m_lMaxSize		=0;
		}
	}
	inline CTAObject*	CTAObjectList::GetObj(LONG IN lIndex)
	{
		if(lIndex < 0 || lIndex >= m_lCount || m_ppObj == NULL)
			return NULL;

		return m_ppObj[lIndex];
	}
	inline LONG			CTAObjectList::FindObj(CTAObject* IN pObj)
	{
		if(pObj == NULL)
			return -1;
		LONG lIndex =0;
		for(lIndex =0 ;lIndex<m_lCount;lIndex++)
		{
			if(m_ppObj[lIndex]==pObj)
				return lIndex;
		}
		return -1;
	}
	
	inline BOOL			CTAObjectList::DelObj(LONG IN lIndex)
	{
		if(lIndex < 0 || lIndex >= m_lCount || m_ppObj == NULL)
			return FALSE;
		m_ppObj[lIndex]->Release();
		--m_lCount;
		LONG i=0;
		for(i=lIndex;i<m_lCount;i++)
		{
			m_ppObj[i]=m_ppObj[i+1];
		}
		m_ppObj[i]=0;

		return TRUE;
	}

	inline BOOL			CTAObjectList::DelObj(CTAObject* IN pObj)
	{
		return DelObj(FindObj(pObj));
	}

	inline VOID			CTAObjectList::AddObj(CTAObject* IN pObj)
	{
		if(pObj == NULL)
			return;
		OverflowCheck();
		m_ppObj[m_lCount]=pObj;
		pObj->AddRef();
		m_lCount++;
	}
	inline BOOL			CTAObjectList::InsertObj(LONG IN lIndex,CTAObject* IN pObj)
	{
		if(pObj == NULL)
			return FALSE;
		if(lIndex > m_lCount || lIndex < 0)
			return FALSE;
		OverflowCheck();

		for(LONG i=m_lCount;i>lIndex;i--)
		{
			m_ppObj[i]	=m_ppObj[i-1];
		}
		m_ppObj[lIndex]=pObj;
		pObj->AddRef();
		m_lCount++;
		return TRUE;
	}
	inline BOOL			CTAObjectList::SetAt(LONG IN lIndex,CTAObject* IN pObj)
	{
		if(pObj == NULL)
			return FALSE;
		if(lIndex >= m_lCount || lIndex < 0)
			return FALSE;

		m_ppObj[lIndex]->Release();
		m_ppObj[lIndex]=pObj;
		pObj->AddRef();
		return TRUE;
	}


	BOOL			CTAObjectList::Swap(LONG IN lIndex1,LONG IN lIndex2)
	{
		if(lIndex1 <0 || lIndex1 >= m_lCount||
			lIndex2 <0 || lIndex2 >= m_lCount)
			return FALSE;

		CTAObject*	pTmp	=m_ppObj[lIndex1];

		m_ppObj[lIndex1]		=m_ppObj[lIndex2];

		m_ppObj[lIndex2]		=pTmp;

		return TRUE;
	}

	BOOL			CTAObjectList::Swap(CTAObject* IN pObj1,CTAObject* IN pObj2)
	{
		return Swap(FindObj(pObj1),FindObj(pObj2));
	}
	VOID	CTAObjectList::Invalidate(BOOL IN bInvalidate,BOOL IN bIncludeChild)
	{
		m_bInvalidate	=bInvalidate;
		if(bIncludeChild)
		{
			for(LONG lIndex =0 ;lIndex<m_lCount;lIndex++)
			{
				m_ppObj[lIndex]->Invalidate(bInvalidate);
			}
		}

	}

	VOID			CTAObjectList::OverflowCheck(LONG IN lStep)
	{
		if( (m_lCount+lStep) >= m_lMaxSize || m_ppObj == NULL)
		{
			m_lMaxSize += max(lStep,16);

			CTAObject**	ppObj	= new CTAObject*[m_lMaxSize];

			LONG i=0;
			for( i=0;i<m_lCount;i++)
				ppObj[i] = m_ppObj[i];
			for(i=m_lCount;i<m_lMaxSize;i++)
				ppObj[i] = 0;

			delete []m_ppObj;
			m_ppObj		= ppObj;
		}

	}

	CTAObjectList&CTAObjectList::operator=(CTAObjectList& v)
	{
		Clear();
		for(LONG i=0;i<v.m_lCount;i++)
			AddObj(v.GetObj(i));
		return *this;
	}
	//------------------------------------------------------------
	CTATips::CTATips(CTATime*pTime,CTAStyle*pStyle):CTAObject(pTime,pStyle)
	{
		m_Type			=TAOT_TIPS;
		m_Pos.x			=0;
		m_Pos.y			=0;
		m_pText			=NULL;
		m_Color			=RGB(50,50,55);
		m_BorderColor	=RGB(0,0,0);
		m_BkColor		=RGB(250,250,180);

		LOGFONT		lf;
		ZeroMemory(&lf,sizeof(lf));
		lf.lfCharSet	=GB2312_CHARSET;
		strcpy(lf.lfFaceName,"宋体");
		lf.lfHeight		=12;
		m_hFont			=CreateFontIndirect(&lf);
	
		m_hBkBrush		=CreateSolidBrush(m_BkColor);
		m_hBorderPen	=CreatePen(PS_SOLID,1,m_BorderColor);

		m_bShow			=FALSE;
	}


	CTATips::~CTATips()
	{
		Safe_DeleteArray(m_pText);
		Safe_DeleteObject(m_hFont);
		Safe_DeleteObject(m_hBkBrush);
		Safe_DeleteObject(m_hBorderPen);
	}
	BOOL		CTATips::Create(LPSTR IN pText,COLORREF IN clr,COLORREF IN bkClr,COLORREF IN borderClr)
	{
		Safe_DeleteObject(m_hBkBrush);
		Safe_DeleteObject(m_hBorderPen);
		m_BkColor		=bkClr;
		m_BorderColor	=borderClr;
		m_hBorderPen	=CreatePen(PS_SOLID,1,borderClr);
		m_hBkBrush		=CreateSolidBrush(bkClr);
		m_Color			=clr;
		SetText(pText);
		m_bShow			=TRUE;
		return TRUE;

	}
	VOID		CTATips::SetPos(LONG IN x,LONG IN y)
	{
		m_Pos.x		=x;
		m_Pos.y		=y;
	}
	VOID		CTATips::SetText(LPCSTR IN pText)
	{
		Safe_DeleteArray(m_pText);
		m_pText		=new CHAR[strlen(pText)+1];
		strcpy(m_pText,pText);
	}

	VOID		CTATips::OnDraw(HDC IN hDC)
	{
		if(m_pText == NULL || !m_bShow)
			return;
		RECT		TextRect;
		HFONT		hOldFont	=(HFONT)SelectObject(hDC,m_hFont);
		COLORREF	OldColor	=SetTextColor(hDC,m_Color);
		HBRUSH		hOldBrush	=(HBRUSH)SelectObject(hDC,m_hBkBrush);
		INT			OldMode		=SetBkMode(hDC,TRANSPARENT);

		TEXTMETRIC	tm;
		GetTextMetrics(hDC,&tm);
		TextRect.left	=m_Pos.x;
		TextRect.top	=m_Pos.y;
		TextRect.right =TextRect.left + strlen(m_pText)*tm.tmAveCharWidth +10;
		TextRect.bottom=TextRect.top  + tm.tmHeight +3;


		Rectangle(hDC,TextRect.left,TextRect.top,TextRect.right,TextRect.bottom);

		DrawText(hDC,m_pText,strlen(m_pText),&TextRect,DT_SINGLELINE|DT_VCENTER|DT_CENTER);

		SelectObject(hDC,hOldFont);
		SetTextColor(hDC,OldColor);
		SelectObject(hDC,hOldBrush);
		SetBkMode(hDC,OldMode);
	}

	//------------------------------------------------------------

	CTAAnchor::CTAAnchor(CTATime*pTime,CTAStyle*pStyle):CTAObject(pTime,pStyle)
	{
		m_Type				=TAOT_Anchor;
		m_Color				=RGB(0,0,0);
		m_dwTime			=0;
		m_dwEndTime			=0;
		m_bDraging			=FALSE;
		m_bSelected			=FALSE;
		m_StartDragPoint.x	=0;
		m_StartDragPoint.y	=0;
		m_DragOffset.x		=0;
		m_DragOffset.y		=0;
		m_pPrevLink			=NULL;
		m_pNextLink			=NULL;
		m_bShowTimeRange	=TRUE;
		m_bEnable			=TRUE;
		m_pTips				=new CHAR[8];
		m_pTips[0]			=0;
	}
	CTAAnchor::~CTAAnchor()
	{
		if(this == m_pStyle->m_pTimeAxis->GetActiveAnchor())
			m_pStyle->m_pTimeAxis->SetActiveAnchor(NULL);

		SetPrev(NULL);
		SetNext(NULL);
		m_theImageList.DeleteImageList();
		Safe_DeleteArray(m_pTips);
	}
	BOOL	CTAAnchor::Create(TAOST_TYPE IN type,COLORREF IN clr,DWORD IN dwTime,DWORD IN dwEndTime)
	{
		if(type < TAOST_Anchor_CircleReal || type >= TAOST_Anchor_Icon)
			return FALSE;
		SetSubType(type);
		m_Color		=clr;
		m_dwTime	=dwTime;
		m_dwEndTime =dwEndTime;
		return TRUE;
	}
	BOOL	CTAAnchor::Create(UINT IN uIconResourceID,DWORD IN dwTime,DWORD IN dwEndTime)
	{
		SetSubType(TAOST_Anchor_Icon);
		m_dwTime	=dwTime;
		m_dwEndTime =dwEndTime;
		m_theImageList.Create(m_pStyle->m_theAnchorStyle.m_dwAnchorSize,m_pStyle->m_theAnchorStyle.m_dwAnchorSize,ILC_COLOR24|ILC_MASK,0,1);
		m_theImageList.Add(LoadIcon(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(uIconResourceID)));
		return TRUE;
	}
	VOID		CTAAnchor::SetTips(LPCSTR IN pTips)
	{
		Safe_DeleteArray(m_pTips);
		
		DWORD	len		=0;
		if(pTips!=NULL)
			len		=strlen(pTips);
		m_pTips		=new CHAR[len+1];
		m_pTips[len]=0;

		if(pTips!=NULL)
			strcpy(m_pTips,pTips);
	}
	VOID		CTAAnchor::SetSelected(BOOL IN bSelected)
	{
		if(m_bSelected == bSelected)
			return;
		m_bSelected		=bSelected;
		
		if(m_bSelected)
		{
			UpdateTips();
		}
		else
		{
			m_pStyle->m_pTimeAxis->HideTips();
		}
		Invalidate(TRUE);
		CTAFrame*	pFrame =GetFrame();
		if(pFrame!=NULL)
			pFrame->Invalidate(TRUE,FALSE);
	}
	VOID		CTAAnchor::Enable(BOOL IN bEnable)
	{
		if(m_bEnable == bEnable)
			return;
		m_bEnable		=bEnable;
		Invalidate(TRUE);
		CTAFrame*	pFrame =GetFrame();
		if(pFrame!=NULL)
			pFrame->Invalidate(TRUE,FALSE);
	}



	LONG		CTAAnchor::NeedDraw()
	{
		DWORD	minTime		=m_pTime->m_dwStartTime;
		DWORD	maxTime		=m_pTime->m_dwStartTime + (m_pTime->m_dwWidth/m_pTime->m_dwUnitSize)*m_pTime->m_dwTimePerUnit;
		if(m_dwTime < minTime )
			return -1;
		if(m_dwTime > maxTime)
			return 1;
		return 0;
	}
	CTAFrame*	CTAAnchor::GetFrame()
	{
		CTAObject*	pParent =GetParent();
		if(pParent == NULL)
			return NULL;
		if(pParent->GetType() != TAOT_Frame)
			return NULL;
		return (CTAFrame*)pParent;
	}
	VOID		CTAAnchor::SetPrev(CTAAnchor* IN pPrev,BOOL IN bResetOld)
	{
		if(m_pPrevLink == pPrev)
			return;
		if(pPrev!=NULL)
		{
			if(pPrev->GetParent() != GetParent())
				return;
		}
		if(bResetOld && m_pPrevLink != NULL)
		{
			m_pPrevLink->SetNext(NULL,FALSE);
		}

		m_pPrevLink		=pPrev;
		
		if(bResetOld && m_pPrevLink != NULL)
		{
			m_pPrevLink->SetNext(this,FALSE);
		}
		
		if(m_pPrevLink != NULL)
		{
			if(m_dwTime < m_pPrevLink->GetTime())
			{
				m_dwTime = m_pPrevLink->GetTime()+m_pTime->m_dwTimePerUnit;
			}
		}

		if(bResetOld)
		{
			Invalidate(TRUE);
			CTAFrame*	pFrame =GetFrame();
			if(pFrame!=NULL)
				pFrame->Invalidate(TRUE,FALSE);
		}
	}
	VOID		CTAAnchor::SetNext(CTAAnchor* IN pNext,BOOL IN bResetOld)
	{
		if(m_pNextLink == pNext)
			return;
		if(pNext!=NULL)
		{
			if(pNext->GetParent() != GetParent())
				return;
		}
		if(bResetOld && m_pNextLink != NULL)
		{
			m_pNextLink->SetPrev(NULL,FALSE);
		}

		m_pNextLink		=pNext;

		if(bResetOld && m_pNextLink != NULL)
		{
			m_pNextLink->SetPrev(this,FALSE);
		}
		if(m_pNextLink != NULL)
		{
			if(m_pNextLink->GetTime() < m_dwTime )
			{
				m_pNextLink->SetTime(m_dwTime+m_pTime->m_dwTimePerUnit);
			}
		}
	
		if(bResetOld )
		{
			Invalidate(TRUE);
			CTAFrame*	pFrame =GetFrame();
			if(pFrame!=NULL)
				pFrame->Invalidate(TRUE,FALSE);
		}
	}
	VOID		CTAAnchor::SetTime(DWORD IN dwTime)
	{
		if(m_dwTime == dwTime)
			return;
		m_dwTime=dwTime;
		Invalidate(TRUE);


	}

	VOID		CTAAnchor::GetRect(RECT& OUT rect)
	{
		LONG	offset		=m_pTime->TimeToOffset(m_dwTime);
		LONG	FontSize	=m_pStyle->m_theAnchorStyle.m_dwAnchorSize;

		LONG	left		=m_pStyle->m_lFirstColumnWidth + m_pStyle->m_dwLeftMargin;
		rect.left		= left + offset - FontSize/2;
		if(rect.left < left)
			rect.left =left;
		rect.top		= (LONG)(m_pStyle->m_dwRowHeight/2) - (LONG)(FontSize/2);
		if(rect.top < 0)rect.top =0;

		rect.right		= rect.left + FontSize;
		rect.bottom		= rect.top + FontSize;
	}
	BOOL		CTAAnchor::GetRangeRect(RECT& OUT rect)
	{
		LONG	left_offset		=m_pTime->TimeToOffset(m_dwTime);
		LONG	right_offset		=m_pTime->TimeToOffset(m_dwTime + m_dwEndTime);
		if(right_offset < 0)
			return FALSE;
		LONG	FontSize			=m_pStyle->m_theAnchorStyle.m_dwAnchorSize;
		LONG	left		=m_pStyle->m_lFirstColumnWidth + m_pStyle->m_dwLeftMargin;		
		rect.left		= left + left_offset - FontSize/2;	
		

		if(rect.left < left)
			rect.left =left;

		rect.top		= (LONG)(m_pStyle->m_dwRowHeight/2) - (LONG)(FontSize/4);
		if(rect.top < 0)
			rect.top =0;

		rect.bottom		= rect.top + FontSize/2;
		rect.right		=left +right_offset;

		return TRUE;
	}

	LONG		CTAAnchor::GetPos()
	{
		LONG	offset		=m_pTime->TimeToOffset(m_dwTime);
		LONG	left		=m_pStyle->m_lFirstColumnWidth + m_pStyle->m_dwLeftMargin;
		LONG	pos			=left + offset;
		if(pos < left)
			pos =left;
		return pos;
	}
	VOID		CTAAnchor::DrawTimeRange(HDC IN hDC,LONG IN lNeedDraw)
	{
		if(!IsShowTimeRange() || m_dwEndTime == 0 || lNeedDraw>0)
			return;
		RECT		rect;
		if(!GetRangeRect(rect))
			return;
		INT oldMode =SetBkMode(hDC,TRANSPARENT);
		HPEN		hOldPen		=NULL;
		if(IsSelected())
			hOldPen =(HPEN)SelectObject(hDC,m_pStyle->m_theAnchorStyle.m_hTimeRangeActivePen);
		else
			hOldPen =(HPEN)SelectObject(hDC,m_pStyle->m_theAnchorStyle.m_hTimeRangePen);

		MoveToEx(hDC,rect.left,rect.top,NULL);

		LineTo(hDC,rect.right,rect.top);
		LineTo(hDC,rect.right,rect.bottom);
		LineTo(hDC,rect.left,rect.bottom);
		if(lNeedDraw==0)
			LineTo(hDC,rect.left,rect.top);
		SelectObject(hDC,hOldPen);
		SetBkMode(hDC,oldMode);
	}

	VOID		CTAAnchor::OnDraw(HDC IN hDC)
	{
		LONG	lNeedDraw		=NeedDraw();
		
		DrawTimeRange(hDC,lNeedDraw);



		BOOL	bNeedDrawLink	=lNeedDraw==0;
		if(m_pNextLink != NULL && lNeedDraw!=0)
		{
			if( (lNeedDraw<0 && m_pNextLink->NeedDraw()>0) || m_pNextLink->NeedDraw()==0 )
			{//需要画出链接线
				bNeedDrawLink =TRUE;
			}
		}

		RECT		rect;
		GetRect(rect);
		if(m_pNextLink != NULL && bNeedDrawLink)
		{
			RECT	NextRect;
			m_pNextLink->GetRect(NextRect);
			HPEN	hOldPen		=NULL;
			if(IsSelected()||m_pNextLink->IsSelected())
				hOldPen =(HPEN)SelectObject(hDC,m_pStyle->m_theAnchorStyle.m_hLinkActivePen);
			else
				hOldPen =(HPEN)SelectObject(hDC,m_pStyle->m_theAnchorStyle.m_hLinkPen);
			if(lNeedDraw<0)
				MoveToEx(hDC,rect.left,m_pStyle->m_dwRowHeight/2,NULL);
			else
				MoveToEx(hDC,rect.right,m_pStyle->m_dwRowHeight/2,NULL);

			LineTo(hDC,NextRect.left,m_pStyle->m_dwRowHeight/2);
			SelectObject(hDC,hOldPen);
		}

		if(lNeedDraw != 0)
			return;

		HFONT		hOldFont	=(HFONT)SelectObject(hDC,m_pStyle->m_theAnchorStyle.m_hAnchorFont);
		COLORREF	OldColor	=SetTextColor(hDC,m_Color);
		INT			OldMode		=SetBkMode(hDC,TRANSPARENT);
		CHAR		Text[32];


		
		switch(GetSubType())
		{
		case TAOST_Anchor_CircleReal:		//圆形实心●
			{
				strcpy(Text,"●");
				DrawText(hDC,Text,strlen(Text),&rect,DT_VCENTER|DT_SINGLELINE|DT_CENTER);
			}
			break;
		case TAOST_Anchor_CircleNull:		//圆形空心○
			{
				strcpy(Text,"○");
				DrawText(hDC,Text,strlen(Text),&rect,DT_VCENTER|DT_SINGLELINE|DT_CENTER);
			}
			break;
		case TAOST_Anchor_DoubleCircle:		//双圆形◎
			{
				strcpy(Text,"◎");
				DrawText(hDC,Text,strlen(Text),&rect,DT_VCENTER|DT_SINGLELINE|DT_CENTER);
			}
			break;
		case TAOST_Anchor_RectangleReal:	//正方形实心■
			{
				strcpy(Text,"■");
				DrawText(hDC,Text,strlen(Text),&rect,DT_VCENTER|DT_SINGLELINE|DT_CENTER);
			}
			break;
		case TAOST_Anchor_RectangleNull:	//正方形空心□
			{
				strcpy(Text,"□");
				DrawText(hDC,Text,strlen(Text),&rect,DT_VCENTER|DT_SINGLELINE|DT_CENTER);
			}
			break;
		case TAOST_Anchor_StarReal:				//五角星实心★
			{
				strcpy(Text,"★");
				DrawText(hDC,Text,strlen(Text),&rect,DT_VCENTER|DT_SINGLELINE|DT_CENTER);
			}
			break;
		case TAOST_Anchor_StarNull:				//五角星空心☆
			{
				strcpy(Text,"☆");
				DrawText(hDC,Text,strlen(Text),&rect,DT_VCENTER|DT_SINGLELINE|DT_CENTER);
			}
			break;
		case TAOST_Anchor_ArrisReal:			//棱形实心◆
			{
				strcpy(Text,"◆");
				DrawText(hDC,Text,strlen(Text),&rect,DT_VCENTER|DT_SINGLELINE|DT_CENTER);
			}
			break;
		case TAOST_Anchor_ArrisNull:			//棱形空心◇
			{
				strcpy(Text,"◇");
				DrawText(hDC,Text,strlen(Text),&rect,DT_VCENTER|DT_SINGLELINE|DT_CENTER);
			}
			break;
		case TAOST_Anchor_TriangleReal:			//三角实心▲
			{
				strcpy(Text,"▲");
				DrawText(hDC,Text,strlen(Text),&rect,DT_VCENTER|DT_SINGLELINE|DT_CENTER);
			}
			break;
		case TAOST_Anchor_TriangleNull:			//三角空心△
			{
				strcpy(Text,"△");
				DrawText(hDC,Text,strlen(Text),&rect,DT_VCENTER|DT_SINGLELINE|DT_CENTER);
			}
			break;
		case TAOST_Anchor_Icon:			//图标
			{
				CDC		dc;
				dc.Attach(hDC);
				POINT	pt;
				pt.x	=rect.left;
				pt.y	=rect.top;
				m_theImageList.Draw(&dc,0,pt,ILD_TRANSPARENT);
				dc.Detach();
				
			}
			break;
		default:
			break;
		}
	
		if(!IsEnable())
		{
			HPEN	hOldPen		=(HPEN)SelectObject(hDC,m_pStyle->m_theAnchorStyle.m_hDisablePen);

			MoveToEx(hDC,rect.left,rect.top,NULL);
			LineTo(hDC,rect.right,rect.bottom);

			MoveToEx(hDC,rect.right,rect.top,NULL);
			LineTo(hDC,rect.left,rect.bottom);

			SelectObject(hDC,hOldPen);

		}

		if(IsSelected())
		{
			HPEN	hOldPen		=(HPEN)SelectObject(hDC,m_pStyle->m_theAnchorStyle.m_hSelectedFramePen);

			InflateRect(&rect,m_pStyle->m_theAnchorStyle.m_lSelectedFrameSpace,m_pStyle->m_theAnchorStyle.m_lSelectedFrameSpace);

			HBRUSH	hOldBrush	=(HBRUSH)SelectObject(hDC,GetStockObject(NULL_BRUSH));

			Rectangle(hDC,rect.left,rect.top,rect.right,rect.bottom);

			SelectObject(hDC,hOldBrush);
			SelectObject(hDC,hOldPen);

			UpdateTips();
		}

		SelectObject(hDC,hOldFont);
		SetTextColor(hDC,OldColor);
		SetBkMode(hDC,OldMode);
	}
	BOOL		CTAAnchor::PreTranslateMessage(MSG* IN pMsg)
	{
		RECT	rect;

		switch(pMsg->message)
		{
		case WM_LBUTTONDOWN:
			{
				GetRect(rect);

				if( (pMsg->wParam & MK_SHIFT) == MK_SHIFT)
				{
					if(ProcessStartDrag(&rect,pMsg->pt))
						return TRUE;
				}
				else
				{
					if(ProcessSelected(&rect,pMsg->pt))
						return TRUE;
				}

				if(IsSelected() && m_pStyle->m_pTimeAxis->GetActiveAnchor() == this)
				{
					m_pStyle->m_pTimeAxis->SetActiveAnchor(NULL);
				}
				
			}
			break;
		case WM_LBUTTONUP:
			{
				if(ProcessEndDrag(pMsg->pt))
					return TRUE;
			}
			break;
		case WM_MOUSEMOVE:
			{
				if(ProcessDrag(pMsg->pt))
					return TRUE;

			}
			break;
		case WM_LBUTTONDBLCLK:
			{
				GetRect(rect);
				if(PtInRect(&rect,pMsg->pt))
				{

					TAMsg	msg;
					msg.message		=TAMSG_LDCLICKED;
					msg.pObject		=this;
					msg.time		=GetTime();
					SendMessage(m_pStyle->m_pTimeAxis->GetWnd(),TAMSG_ID,(WPARAM)&msg,0);
					return TRUE;
				}
			}
			break;
		case WM_RBUTTONDOWN:
			{
				GetRect(rect);
				if(PtInRect(&rect,pMsg->pt))
				{

					if(!IsSelected())
					{	
						m_pStyle->m_pTimeAxis->SetActiveAnchor(this);
					}

					TAMsg	msg;
					msg.message		=TAMSG_RCLICKED;
					msg.pObject		=this;
					msg.time		=GetTime();
					SendMessage(m_pStyle->m_pTimeAxis->GetWnd(),TAMSG_ID,(WPARAM)&msg,0);
					return TRUE;
				}
				else
				{
					if(m_pNextLink != NULL)
					{
						if(IsSelected() || m_pNextLink->IsSelected())
						{
							RECT	rc;
							rc.left		=rect.right;
							rc.top		=(m_pStyle->m_dwRowHeight/2)-2;
							rc.right	=m_pNextLink->GetPos();
							rc.bottom	=rc.top+4;
							if(PtInRect(&rc,pMsg->pt))
							{
								TAMsg	msg;
								msg.message		=TAMSG_RCLICKED_LINKLINE;
								msg.pObject		=this;
								msg.time		=GetTime();
								SendMessage(m_pStyle->m_pTimeAxis->GetWnd(),TAMSG_ID,(WPARAM)&msg,0);
								return TRUE;
							}
						}
					}
				}
			}
			break;
		}

		return FALSE;
	}
	BOOL		CTAAnchor::ProcessSelected(RECT* IN pRect,POINT IN pt)
	{
		if(PtInRect(pRect,pt))
		{
			m_pStyle->m_pTimeAxis->SetActiveAnchor(this);
			return TRUE;
		}
		return FALSE;
	}
	BOOL				CTAAnchor::ProcessStartDrag(RECT* IN pRect,POINT IN pt)
	{
		if(!IsSelected())
			return FALSE;
		if(PtInRect(pRect,pt))
		{
			m_bDraging			=TRUE;
			m_StartDragPoint	=pt;
			
			POINT	center;
			center.x	=pRect->left + (pRect->right-pRect->left)/2;
			center.y	=pRect->top + (pRect->bottom-pRect->top)/2;

			m_DragOffset.x	=center.x-pt.x;
			m_DragOffset.y	=center.y-pt.y;


			SetCapture(m_pStyle->m_pTimeAxis->GetWnd());

			ChangeCursor(IDC_SELECT_MOVE);

			return TRUE;
		}

		return FALSE;
	}
	BOOL				CTAAnchor::ProcessDrag(POINT IN pt)
	{
		if(m_bDraging)
		{
			CTAFrame*	pFrame =GetFrame();
			if(pFrame == NULL)
				return FALSE;

			POINT	taPos		=m_pStyle->m_pTimeAxis->GetPos();
			POINT	framePos	=pFrame->GetPos();

			LONG minX=taPos.x + m_pStyle->m_dwLeftMargin + m_pStyle->m_lFirstColumnWidth ;
			LONG maxX=min( (minX + m_pTime->m_dwWidth),minX + (m_pTime->m_dwEndTime-m_pTime->m_dwStartTime)/m_pTime->m_dwTimePerUnit*m_pTime->m_dwUnitSize);

			if(m_pNextLink != NULL)
			{
				LONG	pos		=taPos.x+m_pNextLink->GetPos()-m_pTime->m_dwUnitSize;
				if(maxX > pos)
					maxX	=pos;
			}
			if(m_pPrevLink != NULL)
			{
				LONG	pos		=taPos.x+m_pPrevLink->GetPos()+m_pTime->m_dwUnitSize;
				if(minX < pos)
					minX	=pos;
			}



			POINT worldPoint,tmp;
			worldPoint.x =pt.x+taPos.x+framePos.x;
			worldPoint.y =pt.y+taPos.y+framePos.y;

			if(worldPoint.x < minX )
			{
				worldPoint.x=minX;
				tmp =worldPoint;

				ClientToScreen(m_pStyle->m_pTimeAxis->GetWnd(),&tmp);
				SetCursorPos(tmp.x,tmp.y);
			}
			if(worldPoint.x > maxX)
			{
				worldPoint.x=maxX;
				tmp =worldPoint;
				ClientToScreen(m_pStyle->m_pTimeAxis->GetWnd(),&tmp);
				SetCursorPos(tmp.x,tmp.y);
			}

			pt.x =worldPoint.x - taPos.x - framePos.x;



			ChangeCursor(IDC_SELECT_MOVE);
			LONG	left		=m_pStyle->m_lFirstColumnWidth + m_pStyle->m_dwLeftMargin;

			m_dwTime	=m_pTime->OffsetToTime(pt.x+m_DragOffset.x - left);
			
			pFrame->Invalidate(TRUE);
			m_pStyle->m_pTimeAxis->Invalidate(TRUE);


			TAMsg	 msg;
			msg.message		=TAMSG_CHANGED;
			msg.pObject		=this;
			msg.time		=GetTime();
			SendMessage(m_pStyle->m_pTimeAxis->GetWnd(),TAMSG_ID,(WPARAM)&msg,0);

			return TRUE;
		}
		return FALSE;
	}
	BOOL				CTAAnchor::ProcessEndDrag(POINT IN pt)
	{
		if(m_bDraging)
		{
			ReleaseCapture();
			LONG	left		=m_pStyle->m_lFirstColumnWidth + m_pStyle->m_dwLeftMargin;

			m_dwTime	=m_pTime->OffsetToTime(pt.x+m_DragOffset.x-left);


			CTAFrame*	pFrame =GetFrame();
			if(pFrame != NULL)
				pFrame->Invalidate(TRUE);
			m_pStyle->m_pTimeAxis->Invalidate(TRUE);

			m_bDraging	=FALSE;


			TAMsg	 msg;
			msg.message		=TAMSG_CHANGED;
			msg.pObject		=this;
			msg.time		=GetTime();
			SendMessage(m_pStyle->m_pTimeAxis->GetWnd(),TAMSG_ID,(WPARAM)&msg,0);

			return TRUE;
		}
		return FALSE;
	}
	VOID				CTAAnchor::UpdateTips()
	{
		CTAFrame*	pFrame =GetFrame();
		if(pFrame==NULL)
			return;

		CHAR	tips[1024];
		if(m_dwEndTime != 0)
			sprintf(tips,"[ %d ms -- %d ms ]%s",m_dwTime,m_dwTime+m_dwEndTime,m_pTips);
		else
			sprintf(tips,"[ %d ms ]%s",m_dwTime,m_pTips);
		POINT	framePos	=pFrame->GetPos();
		RECT	rect;
		GetRect(rect);
		LONG x =rect.right		+framePos.x +2;
		LONG y =rect.bottom		+framePos.y ;
		m_pStyle->m_pTimeAxis->ShowTips(tips,x,y);
	}

	

	//------------------------------------------------------------

	CTAFrame::CTAFrame(CTATime*pTime,CTAStyle*pStyle):CTAObjectList(pTime,pStyle)
	{
		m_Type				=TAOT_Frame;
		m_Pos.x				=0;
		m_Pos.y				=0;
		m_Size.cx			=100;
		m_Size.cy			=50;
		m_hCanvasDC			=NULL;
		m_hCanvas			=NULL;
		m_hPaintDC			=NULL;
		m_bExpand			=FALSE;
		m_bNeedResetCanvas	=FALSE;
		m_bActived			=FALSE;
		m_rectRoot.left		=0;
		m_rectRoot.top		=0;
		m_rectRoot.right	=0;
		m_rectRoot.bottom	=0;
		m_bSetTextColor		=FALSE;
		m_TextColor			=RGB(255,0,0);


		m_pAnchorList		=new CTAObjectList(pTime,pStyle);
		m_pAnchorList->SetParent(this);

		m_bEnable			=TRUE;
	}
	CTAFrame::~CTAFrame()
	{
		if(this == m_pStyle->m_pTimeAxis->GetActiveFrame())
			m_pStyle->m_pTimeAxis->SetActiveFrame(NULL);

		Safe_DeleteObject(m_hCanvas);
		Safe_DeleteDC(m_hCanvasDC);
		Safe_Release(m_pAnchorList);
	}
	VOID		CTAFrame::SetPos(LONG IN x,LONG IN y)
	{
		m_Pos.x		=x;
		m_Pos.y		=y;

	}
	VOID		CTAFrame::SetNameTextColor(COLORREF IN clr)
	{
		m_bSetTextColor		=TRUE;
		m_TextColor			=clr;
	}
	COLORREF	CTAFrame::GetNameTextColor()
	{
		if(m_bSetTextColor)
			return m_TextColor;
		return m_pStyle->m_theFrameStyle.m_NameColor;
	}


	VOID		CTAFrame::SetSize(LONG IN cx,LONG IN cy)
	{
		if(m_Size.cx == cx && m_Size.cy == cy)
			return;

		m_Size.cx			=cx;
		m_Size.cy			=cy;
		m_bNeedResetCanvas	=TRUE;
	}
	VOID				CTAFrame::Expand(BOOL IN bExpand)
	{
		if(m_bExpand	== bExpand)
			return;
		m_bExpand =bExpand;
		m_pStyle->m_pTimeAxis->UpdateScrollBar();

		Invalidate(TRUE);
	}
	VOID				CTAFrame::Active(BOOL IN bActive)
	{
		if(m_bActived == bActive)
			return;
		m_bActived=bActive;
		Invalidate(TRUE);
	}
	VOID				CTAFrame::Enable(BOOL IN bEnable)
	{
		if(m_bEnable == bEnable)
			return;
		m_bEnable	=bEnable;
		Invalidate(TRUE);
	}

	VOID		CTAFrame::OnDraw(HDC IN hDC,INT IN iStartRows,INT IN iMaxRows,INT& IN OUT iRowIndex,CTAObjectList* IN pDrawFrameList)
	{
		if(m_hPaintDC != hDC || m_bNeedResetCanvas)
		{
			m_hPaintDC			=hDC;
			m_bNeedResetCanvas	=FALSE;
			ResetCanvas();
		}

		if(iRowIndex >= iStartRows)
		{
			pDrawFrameList->AddObj(this);
			if(IsInvalidate())
				Draw(iRowIndex);
			Invalidate(FALSE,FALSE);
			//-------------------------------------------
			BitBlt(m_hPaintDC,
				m_Pos.x,m_Pos.y,
				m_Size.cx,m_Size.cy,
				m_hCanvasDC,
				0,0,
				SRCCOPY);
			//-------------------------------------------
		}

		iRowIndex++;
		DrawChild(iStartRows,iMaxRows,iRowIndex,pDrawFrameList);
	

	}
	BOOL		CTAFrame::SelectProcess(POINT IN pt)
	{
		if(!PointSelected(pt))
			return FALSE;
		m_pStyle->m_pTimeAxis->SetActiveFrame(this);
		return TRUE;
	}
	BOOL		CTAFrame::ExpandProcess(POINT IN pt)
	{
		if(GetCount()<=0)
			return FALSE;
		POINT	point =pt;
		POINT	Center;
		Center.x	=m_rectRoot.left + (m_rectRoot.right-m_rectRoot.left)/2-1;
		Center.y	=m_rectRoot.top + (m_rectRoot.bottom-m_rectRoot.top)/2-1;

		RECT	BorderRect;
		LONG	size_x		=(LONG)((float)(m_rectRoot.right-m_rectRoot.left)*0.6f);
		LONG	size_y		=(LONG)((float)(m_rectRoot.bottom-m_rectRoot.top)*0.6f);
		LONG	size		=min(size_x,size_y)/2;

		BorderRect.left	=Center.x-size;
		BorderRect.top		=Center.y-size;
		BorderRect.right	=Center.x+size+1;
		BorderRect.bottom	=Center.y+size+1;

		if(PtInRect(&BorderRect,point))
		{
			Expand(!m_bExpand);
			m_pStyle->m_pTimeAxis->Invalidate(TRUE,TRUE);
			return TRUE;
		}
		return FALSE;
	}

	BOOL		CTAFrame::PreTranslateMessage(MSG* IN pMsg)
	{
		MSG		LocalMsg =*pMsg;
		LocalMsg.pt.x -=m_Pos.x;
		LocalMsg.pt.y -=m_Pos.y;




		CTAAnchor*	pAnchor =NULL;
		for(LONG i=0;i<m_pAnchorList->GetCount();i++)
		{
			pAnchor =(CTAAnchor*)m_pAnchorList->GetObj(i);
			if(pAnchor->PreTranslateMessage(&LocalMsg))
				return TRUE;
		}


		switch(LocalMsg.message)
		{
		case WM_LBUTTONDOWN:
			{
				if(ExpandProcess(LocalMsg.pt))
					return TRUE;
				if(SelectProcess(LocalMsg.pt))
					return TRUE;

			}
			break;
		case WM_LBUTTONDBLCLK:
			{
				if(PointSelected(LocalMsg.pt))
				{
					TAMsg		msg;
					msg.message		=TAMSG_LDCLICKED;
					msg.pObject		=this;
					msg.time		=m_pTime->OffsetToTime(LocalMsg.pt.x - (m_pStyle->m_lFirstColumnWidth+m_pStyle->m_dwLeftMargin));
					SendMessage(m_pStyle->m_pTimeAxis->GetWnd(),TAMSG_ID,(WPARAM)&msg,0);
					return TRUE;
				}
			}
			break;
		case WM_RBUTTONDOWN:
			{
				if(!IsActived())
					break;

				RECT	rect;
				rect.left		=0 + m_pStyle->m_lFirstColumnWidth + m_pStyle->m_dwLeftMargin;
				rect.top		=0;
				rect.right		=m_Size.cx;
				rect.bottom		=m_Size.cy;
				
				if(PtInRect(&rect,LocalMsg.pt))
				{
					TAMsg		msg;
					msg.message		=TAMSG_RCLICKED;
					msg.pObject		=this;
					msg.time		=m_pTime->OffsetToTime(LocalMsg.pt.x - rect.left);
					SendMessage(m_pStyle->m_pTimeAxis->GetWnd(),TAMSG_ID,(WPARAM)&msg,0);
					return TRUE;
				}
			}
			break;
		}
		return FALSE;
	}
	VOID		CTAFrame::Draw(INT IN iRowIndex)
	{

		RECT	CanvasRect;
		CanvasRect.left		=0;
		CanvasRect.top			=0;
		CanvasRect.right		=m_Size.cx;
		CanvasRect.bottom		=m_Size.cy;
		HPEN		hOldPen		=(HPEN)SelectObject(m_hCanvasDC,m_pStyle->m_theFrameStyle.m_hBorderPen);
		HFONT		hOldFont	=(HFONT)SelectObject(m_hCanvasDC,m_pStyle->m_theFrameStyle.m_hNameFont);
		COLORREF	OldColor	=SetTextColor(m_hCanvasDC,GetNameTextColor());
		int			OldMode		=SetBkMode(m_hCanvasDC,TRANSPARENT);

		if(m_bEnable)
		{
			if(IsActived())
			{
				FillRect(m_hCanvasDC,&CanvasRect,m_pStyle->m_theFrameStyle.m_hActiveBkBrush);
			}
			else
			{
				if(iRowIndex % 2 == 0)
				{
					FillRect(m_hCanvasDC,&CanvasRect,m_pStyle->m_theFrameStyle.m_hNormalBkBrush1);
				}
				else
				{
					FillRect(m_hCanvasDC,&CanvasRect,m_pStyle->m_theFrameStyle.m_hNormalBkBrush2);
				}
			}
		}
		else
		{
			FillRect(m_hCanvasDC,&CanvasRect,m_pStyle->m_theFrameStyle.m_hDisableBkBrush);
		}


		MoveToEx(m_hCanvasDC,m_pStyle->m_lFirstColumnWidth,m_Size.cy-1,NULL);
		LineTo(m_hCanvasDC,m_Size.cx,m_Size.cy-1);
		
		DrawRootLine();

		RECT	RectText;
		RectText.left	=m_pStyle->m_theFrameStyle.m_dwLeftMargin + m_pStyle->m_dwLevelSpace*m_lLevel + m_pStyle->m_dwLevelSpace;
		RectText.top	=0;
		RectText.right =m_pStyle->m_lFirstColumnWidth-1;
		RectText.bottom=m_Size.cy-1;

		DrawText(m_hCanvasDC,m_pName,strlen(m_pName),&RectText,DT_SINGLELINE|DT_VCENTER|DT_LEFT);

		SelectObject(m_hCanvasDC,hOldPen);
		SelectObject(m_hCanvasDC,hOldFont);
		SetTextColor(m_hCanvasDC,OldColor);
		SetBkMode(m_hCanvasDC,OldMode);

		DrawAnchors();
	}
	VOID				CTAFrame::DrawChild(INT IN iStartRows,INT IN iMaxRows,INT& IN OUT iRowIndex,CTAObjectList* IN pDrawFrameList)
	{
		if(!IsExpand())
			return;
		POINT		StartPt;

		StartPt.x		=m_Pos.x;
		StartPt.y		=m_pStyle->m_dwTitleHeight+1;

		CTAFrame*	pFrame	=NULL;
		for(LONG i =0;i<GetCount();i++)
		{
			pFrame	=(CTAFrame*)GetObj(i);
			
			pFrame->SetPos(StartPt.x,StartPt.y + (iRowIndex-iStartRows)*m_Size.cy)				;
			pFrame->SetSize(m_Size.cx,m_Size.cy);

			pFrame->OnDraw(m_hPaintDC,iStartRows,iMaxRows,iRowIndex,pDrawFrameList);
			if(iRowIndex-iStartRows>=iMaxRows)
				break;
		}
	}

	VOID		CTAFrame::DrawAnchors()
	{
		CTAAnchor*	pAnchor		=NULL;
		for(LONG i=0;i<m_pAnchorList->GetCount();i++)
		{
			pAnchor		=(CTAAnchor*)m_pAnchorList->GetObj(i);
			pAnchor->OnDraw(m_hCanvasDC);
		}
		
	}

	VOID		CTAFrame::DrawRootLine()
	{
		m_rectRoot.left		=m_pStyle->m_theFrameStyle.m_dwLeftMargin + m_pStyle->m_dwLevelSpace*m_lLevel;
		m_rectRoot.top		=0;
		m_rectRoot.right	=m_rectRoot.left + m_pStyle->m_dwLevelSpace;
		m_rectRoot.bottom	=m_Size.cy;

		POINT	pt;
		SelectObject(m_hCanvasDC,m_pStyle->m_theFrameStyle.m_hRootLinePen);
		pt.x	=m_rectRoot.left + (m_rectRoot.right-m_rectRoot.left)/2-1;
		pt.y	=m_rectRoot.top + (m_rectRoot.bottom-m_rectRoot.top)/2-1;
		
		for(LONG i=0;i<=m_lLevel;i++)
		{
			LONG	x =m_pStyle->m_theFrameStyle.m_dwLeftMargin + m_pStyle->m_dwLevelSpace*i;
			x+=(m_rectRoot.right-m_rectRoot.left)/2-1;
			MoveToEx(m_hCanvasDC,x,0,NULL);
			LineTo(m_hCanvasDC,x,m_Size.cy);

		}

		MoveToEx(m_hCanvasDC,pt.x,pt.y,NULL);
		LineTo(m_hCanvasDC,m_rectRoot.right,pt.y);

		if(GetCount() > 0)
		{
			RECT	BorderRect;
			LONG	size_x		=(LONG)((float)(m_rectRoot.right-m_rectRoot.left)*0.6f);
			LONG	size_y		=(LONG)((float)(m_rectRoot.bottom-m_rectRoot.top)*0.6f);
			LONG	size		=min(size_x,size_y)/2;

			BorderRect.left	=pt.x-size;
			BorderRect.top		=pt.y-size;
			BorderRect.right	=pt.x+size;
			BorderRect.bottom	=pt.y+size;
			SelectObject(m_hCanvasDC,m_pStyle->m_theFrameStyle.m_hRootBorderPen);
			SelectObject(m_hCanvasDC, GetStockObject(WHITE_BRUSH)); 
			
			Rectangle(m_hCanvasDC,BorderRect.left,BorderRect.top,BorderRect.right+1,BorderRect.bottom+1);
			//Ellipse(m_hCanvasDC,BorderRect.left,BorderRect.top,BorderRect.right+1,BorderRect.bottom+1);
			
			SelectObject(m_hCanvasDC,m_pStyle->m_theFrameStyle.m_hRootFlagPen);
			MoveToEx(m_hCanvasDC,pt.x-size/2,pt.y,NULL);
			LineTo(m_hCanvasDC,pt.x+size/2+1,pt.y);
			if(!IsExpand())
			{
				MoveToEx(m_hCanvasDC,pt.x,pt.y-size/2,NULL);
				LineTo(m_hCanvasDC,pt.x,pt.y+size/2+1);
			}
		}
	}

	VOID		CTAFrame::ResetCanvas()
	{
		if(m_hCanvas != NULL)
			DeleteObject(m_hCanvas);
		if(m_hCanvasDC != NULL)
			DeleteDC(m_hCanvasDC);
		m_hCanvasDC	=CreateCompatibleDC(m_hPaintDC);
		if(m_hCanvasDC == NULL)
			return;
		m_hCanvas	=CreateCompatibleBitmap(m_hPaintDC,m_Size.cx,m_Size.cy);
		if(m_hCanvas == NULL)
			return;
		SelectObject(m_hCanvasDC,m_hCanvas);
		Invalidate(TRUE);
	}
	VOID		CTAFrame::EnsureVisible()
	{
		m_pStyle->m_pTimeAxis->EnsureFrameVisible(this);
	}
	LONG		CTAFrame::GetFramesCount()
	{
		if(!IsExpand())
		{
			return 1;
		}
		LONG count =1;
		
		CTAFrame*	pChild;
		for(LONG i=0;i<GetCount();i++)
		{
			pChild =(CTAFrame*)GetObj(i);
			count += pChild->GetFramesCount();
		}
		return count;

	}

	BOOL		CTAFrame::PointSelected(POINT IN pt)
	{
		RECT	rect;
		rect.left		=0;
		rect.top		=0;
		rect.right		=m_Size.cx;
		rect.bottom		=m_Size.cy;
		if(PtInRect(&rect,pt))
			return TRUE;
		return FALSE;
	}
	BOOL				CTAFrame::ProcessClickedExpandButton(POINT IN pt)
	{
		if(GetCount()<=0)
			return FALSE;
		pt.x-=m_Pos.x;
		pt.y-=m_Pos.y;


		POINT	Center;
		Center.x	=m_rectRoot.left + (m_rectRoot.right-m_rectRoot.left)/2-1;
		Center.y	=m_rectRoot.top + (m_rectRoot.bottom-m_rectRoot.top)/2-1;

		RECT	BorderRect;
		LONG	size_x		=(LONG)((float)(m_rectRoot.right-m_rectRoot.left)*0.6f);
		LONG	size_y		=(LONG)((float)(m_rectRoot.bottom-m_rectRoot.top)*0.6f);
		LONG	size		=min(size_x,size_y)/2;

		BorderRect.left	=Center.x-size;
		BorderRect.top		=Center.y-size;
		BorderRect.right	=Center.x+size+1;
		BorderRect.bottom	=Center.y+size+1;

		if(PtInRect(&BorderRect,pt))
		{
			m_bExpand = !m_bExpand;
			Invalidate(TRUE);
			m_pStyle->m_pTimeAxis->Invalidate(TRUE,TRUE);
			return TRUE;
		}
		return FALSE;
	}

	CTAFrame*			CTAFrame::AddFrame(TAOST_TYPE IN type,LPCSTR IN pFrameName,LPCSTR IN pFrameDesc,UINT_PTR IN UserData)
	{
		CTAFrame*	pFrame =NULL;

		pFrame	=new CTAFrame(m_pTime,m_pStyle);
		pFrame->SetName(pFrameName);
		pFrame->SetDesc(pFrameDesc);
		pFrame->SetSubType(type);
		pFrame->SetUserData(UserData);
		pFrame->SetParent(this);
		pFrame->SetLevel(GetLevel()+1);

		AddObj(pFrame);


		pFrame->Release();
		return pFrame;
	}
	BOOL				CTAFrame::DelFrame(CTAFrame* IN pFrame)
	{
		CTAFrame*	p	=NULL;
		for(LONG i=0;i<GetCount();i++)
		{
			p =(CTAFrame*)GetObj(i);
			if(p == pFrame)
			{
				if(p == m_pStyle->m_pTimeAxis->GetActiveFrame())
					m_pStyle->m_pTimeAxis->SetActiveFrame(NULL);
				////////////////////////////////////////////////////////////////////////
				if(m_pStyle != NULL)
				{
					TAMsg	msg;
					msg.message		=TAMSG_DELETED;
					msg.pObject		=p;
					msg.time		=0;
					SendMessage(m_pStyle->m_pTimeAxis->GetWnd(),TAMSG_ID,(WPARAM)&msg,0);
				}
				////////////////////////////////////////////////////////////////////////

				DelObj(i);
				return TRUE;
			}
			//-------------------------
			if(p->DelFrame(pFrame))
				return TRUE;
		}
		return FALSE;
	}
	BOOL				CTAFrame::DelFrame(LPCSTR IN pFrameName)
	{
		CTAFrame*	p	=NULL;
		for(LONG i=0;i<GetCount();i++)
		{
			p =(CTAFrame*)GetObj(i);
			if(strcmp(p->GetName() , pFrameName) == 0)
			{
				if(p == m_pStyle->m_pTimeAxis->GetActiveFrame())
					m_pStyle->m_pTimeAxis->SetActiveFrame(NULL);
				////////////////////////////////////////////////////////////////////////
				if(m_pStyle != NULL)
				{
					TAMsg	msg;
					msg.message		=TAMSG_DELETED;
					msg.pObject		=p;
					msg.time		=0;
					SendMessage(m_pStyle->m_pTimeAxis->GetWnd(),TAMSG_ID,(WPARAM)&msg,0);
				}
				////////////////////////////////////////////////////////////////////////

				DelObj(i);
				return TRUE;
			}
			//-------------------------
			if(p->DelFrame(pFrameName))
				return TRUE;
		}
		return FALSE;
	}
	CTAFrame*			CTAFrame::FindFrame(LPCSTR IN pFrameName)
	{
		CTAFrame*	pFrame =NULL;
		CTAFrame*	pFind	=NULL;
		for(LONG i=0;i<GetCount();i++)
		{
			pFrame =(CTAFrame*)GetObj(i);
			if(strcmp(pFrame->GetName() , pFrameName) == 0)
				return pFrame;
			//-------------------------
			pFind =pFrame->FindFrame(pFrameName);
			if(pFind != NULL)
				return pFind;
		}
		return NULL;
	}
	BOOL				CTAFrame::GetFrameSequence(CTAFrame* IN pFrame,LONG& lSequence)
	{
		lSequence++;
		if(!IsExpand())
			return FALSE;
		CTAFrame*	p	=NULL;
		for(LONG i=0;i<GetCount();i++)
		{
			p =(CTAFrame*)GetObj(i);
			if(p == pFrame)
				return TRUE;
			//-------------------------
			if(p->GetFrameSequence(pFrame,lSequence))
					return TRUE;
		}
		return FALSE;
	}

	VOID				CTAFrame::ClearFrame()
	{
		Clear(TRUE);
	}

	CTAAnchor*			CTAFrame::AddAnchor(DWORD IN dwTime,TAOST_TYPE IN type,COLORREF IN clr,UINT_PTR IN UserData)
	{
		CTAAnchor*	pAnchor		=new CTAAnchor(m_pTime,m_pStyle);
		if(!pAnchor->Create(type,clr,dwTime))
		{
			Safe_Release(pAnchor);
			return NULL;
		}

		pAnchor->SetUserData(UserData);
		pAnchor->SetParent(this);

		m_pAnchorList->AddObj(pAnchor);

		pAnchor->Release();
		
		Invalidate(TRUE,FALSE);
		return pAnchor;
	}
	CTAAnchor*			CTAFrame::AddAnchor(DWORD IN dwTime,UINT IN uResourceID,UINT_PTR IN UserData)
	{
		CTAAnchor*	pAnchor		=new CTAAnchor(m_pTime,m_pStyle);
		if(!pAnchor->Create(uResourceID,dwTime))
		{
			Safe_Release(pAnchor);
			return NULL;
		}
		pAnchor->SetUserData(UserData);
		pAnchor->SetParent(this);

		m_pAnchorList->AddObj(pAnchor);

		pAnchor->Release();
		Invalidate(TRUE,FALSE);
		return pAnchor;
	}
	VOID				CTAFrame::AddAnchor(CTAAnchor* IN pNewAnchor)
	{
		m_pAnchorList->AddObj(pNewAnchor);
		pNewAnchor->SetParent(this);

		Invalidate(TRUE,FALSE);
	}

	BOOL				CTAFrame::DelAnchor(CTAAnchor* IN pAnchor)
	{
		Invalidate(TRUE,FALSE);

		////////////////////////////////////////////////////////////////////////
		if(m_pStyle != NULL)
		{
			TAMsg	msg;
			msg.message		=TAMSG_DELETED;
			msg.pObject		=pAnchor;
			msg.time		=pAnchor->GetTime();
			SendMessage(m_pStyle->m_pTimeAxis->GetWnd(),TAMSG_ID,(WPARAM)&msg,0);
		}
		////////////////////////////////////////////////////////////////////////
		pAnchor->SetPrev(NULL);
		pAnchor->SetNext(NULL);
		return m_pAnchorList->DelObj(pAnchor);
	}
	VOID				CTAFrame::ClearAnchor()
	{
		Invalidate(TRUE,FALSE);

		CTAAnchor*	pAnchor =NULL;
		for(INT i=0;i<m_pAnchorList->GetCount();i++)
		{
			pAnchor =(CTAAnchor*)m_pAnchorList->GetObj(i);
			////////////////////////////////////////////////////////////////////////
			if(m_pStyle != NULL)
			{
				TAMsg	msg;
				msg.message		=TAMSG_DELETED;
				msg.pObject		=pAnchor;
				msg.time		=pAnchor->GetTime();
				SendMessage(m_pStyle->m_pTimeAxis->GetWnd(),TAMSG_ID,(WPARAM)&msg,0);
			}
			////////////////////////////////////////////////////////////////////////
		}
		
		m_pAnchorList->Clear(TRUE);
	}
	LONG				CTAFrame::GetAnchorCount()
	{
		return m_pAnchorList->GetCount();
	}
	CTAAnchor*			CTAFrame::GetAnchor(LONG IN lIndex)
	{
		return (CTAAnchor*)m_pAnchorList->GetObj(lIndex);
	}
	//------------------------------------------------------------
	CTAScrollBar::CTAScrollBar(CTATime*pTime,CTAStyle*pStyle):CTAObject(pTime,pStyle)
	{
		m_Type				=TAOT_ScrollBar;
		m_Pos.x				=0;
		m_Pos.y				=0;
		
		m_lLength			=100;
		m_lMaxCount			=1;
		m_lPageCount		=10;
		m_lScrollPos		=0;
		m_lBarSize			=m_lLength;

		m_lWidth			=10;


		m_bDraging			=FALSE;
		m_DragStartPoint.x	=0;
		m_DragStartPoint.y	=0;


		m_BarRect.left		=0;
		m_BarRect.right		=0;
		m_BarRect.top		=0;
		m_BarRect.bottom	=0;
		m_ScrollBarRect.left		=0;
		m_ScrollBarRect.right		=0;
		m_ScrollBarRect.top			=0;
		m_ScrollBarRect.bottom		=0;

		m_DragOffset.x		=0;
		m_DragOffset.y		=0;

		m_bHaveBackBar		=FALSE;

	}
	CTAScrollBar::~CTAScrollBar()
	{

	}
	VOID			CTAScrollBar::SetPos(LONG IN x,LONG IN y)
	{
		m_Pos.x		=x;
		m_Pos.y		=y;
		Update();
	}
	VOID			CTAScrollBar::SetLength(LONG IN length)
	{
		m_lLength			=length;
		Update();
	}
	VOID			CTAScrollBar::SetMaxCount(LONG IN lCount)
	{
		m_lMaxCount		=lCount;

		Update();
	}
	VOID			CTAScrollBar::SetPerPageCount(LONG IN lCount)
	{
		m_lPageCount	=lCount;
		Update();
	}

	LONG			CTAScrollBar::GetScrollPos()
	{
		return m_lScrollPos;
	}

	VOID			CTAScrollBar::SetScrollPos(LONG IN lPos)
	{
		m_lScrollPos	=lPos;
		Update();
	}
	VOID			CTAScrollBar::Update()
	{

		if(m_lScrollPos >= m_lMaxCount)
		{
			if(m_lPageCount < m_lMaxCount)
				m_lScrollPos =m_lMaxCount-m_lPageCount;
			else 
				m_lScrollPos =0;
		}
		if(m_lPageCount < m_lMaxCount)
		{
			if(m_lScrollPos > m_lMaxCount-m_lPageCount)
			{
				m_lScrollPos = m_lMaxCount-m_lPageCount;
			}
		}



		m_BarRect.left	=m_Pos.x;
		m_BarRect.top	=m_Pos.y;
		m_BarRect.right	=m_Pos.x + m_pStyle->m_theScrollStyle.m_dwWidth +1;
		m_BarRect.bottom=m_Pos.y + m_lLength;

		if(m_lMaxCount <= m_lPageCount)
			m_lBarSize = m_lLength;
		else
		{
			m_lBarSize		=(long)((float)m_lPageCount/(float)m_lMaxCount * (float)m_lLength);
		}


		float	fPercent =(float)m_lScrollPos/(float)m_lMaxCount;
		m_ScrollBarRect.left	=m_BarRect.left ;
		m_ScrollBarRect.top		=m_BarRect.top  + (LONG)(fPercent*m_lLength);
		m_ScrollBarRect.right	=m_ScrollBarRect.left + m_pStyle->m_theScrollStyle.m_dwWidth ;
		m_ScrollBarRect.bottom	=m_ScrollBarRect.top + m_lBarSize;



	}

	VOID			CTAScrollBar::OnDraw(HDC IN hDC)
	{
		if(m_lPageCount >= m_lMaxCount)
			return;
		
		HPEN	hOldPen			=(HPEN)SelectObject(hDC,GetStockObject(NULL_PEN));
		HBRUSH	hOldBrush		=(HBRUSH)SelectObject(hDC,m_pStyle->m_theScrollStyle.m_hBkBrush);

		if(m_bHaveBackBar)
		{
			Rectangle(hDC,m_BarRect.left,m_BarRect.top,m_BarRect.right,m_BarRect.bottom);
		}
		else
		{
			LONG x	=m_BarRect.left + (m_BarRect.right -m_BarRect.left)/2;

			SelectObject(hDC,m_pStyle->m_theScrollStyle.m_hBkPen);
			MoveToEx(hDC,x,m_BarRect.top,NULL);
			LineTo(hDC,x,m_BarRect.bottom);

		}

		

		RECT	barRect		=m_ScrollBarRect;
		InflateRect(&barRect,-1,-1);
		
		if(barRect.bottom-barRect.top < 4)
		{
			barRect.top =barRect.top + (barRect.bottom-barRect.top)/2 -2;
			barRect.bottom =barRect.top+4;
		}

		SelectObject(hDC,m_pStyle->m_theScrollStyle.m_hBarBorderPen);
		SelectObject(hDC,m_pStyle->m_theScrollStyle.m_hBarBrush);
		RoundRect(hDC,barRect.left,barRect.top,barRect.right,barRect.bottom, m_pStyle->m_theScrollStyle.m_dwWidth,m_pStyle->m_theScrollStyle.m_dwWidth);
		
		SelectObject(hDC,hOldPen);
		SelectObject(hDC,hOldBrush);

	}
	BOOL			CTAScrollBar::PreTranslateMsg(MSG* IN pMsg)
	{
		switch(pMsg->message)
		{
		case WM_LBUTTONDOWN:
			{
				if(OnStartDrag(pMsg->pt))
					return TRUE;
			}
			break;
		case WM_LBUTTONUP:
			{
				if(OnEndDrag(pMsg->pt))
					return TRUE;
			}
			break;
		case WM_MOUSEMOVE:
			{
				if(OnProcessDrag(pMsg->pt))
					return TRUE;
			}
			break;
		}
		return FALSE;
	}
	BOOL			CTAScrollBar::OnStartDrag(POINT IN pt)
	{
		if(m_lPageCount >= m_lMaxCount)
			return FALSE;
		if(PtInRect(&m_ScrollBarRect,pt))
		{
			SetCapture(m_pStyle->m_pTimeAxis->GetWnd());
			m_bDraging				=TRUE;
			m_DragStartPoint		=pt;
			m_DragOffset.x			=m_ScrollBarRect.left	-pt.x;
			m_DragOffset.y			=m_ScrollBarRect.top	-pt.y;
			return TRUE;
		}

		return FALSE;
	}
	BOOL			CTAScrollBar::OnEndDrag(POINT IN pt)
	{
		if(m_bDraging)
		{
			ReleaseCapture();
			m_bDraging	=FALSE;

			float fPercent =(float)(m_ScrollBarRect.top-m_BarRect.top)/(float)m_lLength;
			m_lScrollPos	= fPercent*m_lMaxCount;

			m_pStyle->m_pTimeAxis->Invalidate(TRUE);
			return TRUE;
		}
		return FALSE;
	}
	BOOL			CTAScrollBar::OnProcessDrag(POINT IN pt)
	{
		if(!m_bDraging)
			return FALSE;

		POINT point =pt;


		LONG	y0		=pt.y + m_DragOffset.y;
		LONG	y1		=y0 + (m_ScrollBarRect.bottom-m_ScrollBarRect.top);
		LONG	minY	=m_BarRect.top;
		LONG	maxY	=m_BarRect.bottom;


		if(y0 < minY)
		{
			point.y =minY-m_DragOffset.y;
			
			POINT	worldPt;
			worldPt.x =point.x + m_pStyle->m_pTimeAxis->GetPos().x;
			worldPt.y =point.y + m_pStyle->m_pTimeAxis->GetPos().y;
			ClientToScreen(m_pStyle->m_pTimeAxis->GetWnd(),&worldPt);

			SetCursorPos(worldPt.x ,worldPt.y);
		}
		if(y1 > maxY)
		{
			point.y =maxY -((m_ScrollBarRect.bottom-m_ScrollBarRect.top) + m_DragOffset.y);

			POINT	worldPt;
			worldPt.x =point.x + m_pStyle->m_pTimeAxis->GetPos().x;
			worldPt.y =point.y + m_pStyle->m_pTimeAxis->GetPos().y;
			ClientToScreen(m_pStyle->m_pTimeAxis->GetWnd(),&worldPt);

			SetCursorPos(worldPt.x ,worldPt.y);
		}

		m_ScrollBarRect.left	=m_BarRect.left ;
		m_ScrollBarRect.top		=m_DragOffset.y + point.y;
		m_ScrollBarRect.right	=m_ScrollBarRect.left + m_pStyle->m_theScrollStyle.m_dwWidth ;
		m_ScrollBarRect.bottom	=m_ScrollBarRect.top + m_lBarSize;

		float fPercent =(float)(m_ScrollBarRect.top-m_BarRect.top)/(float)m_lLength;
		m_lScrollPos	= fPercent*m_lMaxCount;

		m_pStyle->m_pTimeAxis->Invalidate(TRUE);
		return TRUE;
	}




	//------------------------------------------------------------


	CTimeAxis::CTimeAxis()
	{
		m_pTime					=new CTATime();
		m_pStyle				=new CTAStyle();
		m_pStyle->m_pTimeAxis	=this;
		m_pFrameList			=new CTAObjectList(m_pTime,m_pStyle);
		m_pDrawFrameList		=new CTAObjectList(m_pTime,m_pStyle);
		m_pTips					=new CTATips(m_pTime,m_pStyle);
		m_pScrollbar			=new CTAScrollBar(m_pTime,m_pStyle);

		m_hWnd					=NULL;
		m_hPaintDC				=NULL;
		m_hCanvas				=NULL;
		m_hCanvasDC				=NULL;
		m_Size.cx				=0;
		m_Size.cy				=0;
		m_Pos.x					=0;
		m_Pos.y					=0;

		m_bDragingSplitter		=FALSE;
		m_bDragingTimeLine		=FALSE;
		m_bDragingTitle			=FALSE;
	
		m_iFirstFrameIndex		=0;
		m_pActiveFrame			=NULL;
		m_pActiveAnchor			=NULL;
		m_bRedraw				=TRUE;

	}
	CTimeAxis::~CTimeAxis()
	{
		Safe_Release(m_pDrawFrameList);
		Safe_Release(m_pFrameList);
		if(m_hPaintDC != NULL)
		{
			ReleaseDC(m_hWnd,m_hPaintDC);
			m_hPaintDC =NULL;
		}
		Safe_DeleteObject(m_hCanvas);
		Safe_DeleteDC(m_hCanvasDC);
		Safe_Delete(m_pStyle);
		Safe_Delete(m_pTime);
		Safe_Delete(m_pTips);
		Safe_Release(m_pScrollbar);
	}
	BOOL			CTimeAxis::Create(HWND IN hWnd,LONG IN cx,LONG IN cy,CTAStyle* IN style)
	{
		if(m_hPaintDC != NULL)
		{
			ReleaseDC(m_hWnd,m_hPaintDC);
			m_hPaintDC =NULL;
		}
		Safe_DeleteObject(m_hCanvas);
		Safe_DeleteDC(m_hCanvasDC);

		m_hWnd			=hWnd;
		m_hPaintDC		=GetDC(m_hWnd);
		if(style != NULL)
		{
			Safe_Delete(m_pStyle);
			m_pStyle	=style;
		}
		
		ResetCanvas(cx,cy);
		m_pScrollbar->SetPos(m_pStyle->m_lFirstColumnWidth - m_pStyle->m_theScrollStyle.m_dwWidth,m_pStyle->m_dwTitleHeight+1);
		UpdateScrollBar();
		return TRUE;
	}
	VOID			CTimeAxis::SetSize(LONG IN cx,LONG IN cy,BOOL IN bDraw)
	{
		if(cx<=100||cy<=50)
			return;

		ResetCanvas(cx,cy);
		UpdateScrollBar();

		if(bDraw)
			Invalidate(TRUE);
	}
	VOID			CTimeAxis::SetPos(LONG IN x,LONG IN y,BOOL IN bDraw)
	{
		m_Pos.x		=x;
		m_Pos.y		=y;
		if(bDraw)
			Invalidate(FALSE);
	}
	VOID			CTimeAxis::Invalidate(BOOL bRedraw,BOOL IN bInvalidateAllChild)
	{
		m_bRedraw	=bRedraw;

		if(bInvalidateAllChild)
		{
			for(LONG i=0;i<m_pFrameList->GetCount();i++)
			{
				m_pFrameList->GetObj(i)->Invalidate(bRedraw);
			}
		}
		//-------------------------------------
		RECT rect;
		rect.left	=m_Pos.x;
		rect.top	=m_Pos.y;
		rect.right	=m_Pos.x + m_Size.cx;
		rect.bottom	=m_Pos.y + m_Size.cy;
		InvalidateRect(m_hWnd,&rect,FALSE);
	}
	VOID			CTimeAxis::ShowTips(LPCSTR IN pText,LONG IN x,LONG IN y)
	{
		m_pTips->SetText(pText);
		m_pTips->SetPos(x,y);
		m_pTips->Show();
	}
	VOID			CTimeAxis::HideTips()
	{
		m_pTips->Hide();
	}
	VOID			CTimeAxis::SetStyle(CTAStyle* IN pStyle)
	{
		if(pStyle == NULL)
			return;
		Safe_Delete(m_pStyle);
		m_pStyle	=pStyle;
	}

	VOID			CTimeAxis::Redraw()
	{
		RECT	CanvasRect;
		CanvasRect.left		=0;
		CanvasRect.top			=0;
		CanvasRect.right		=m_Size.cx;
		CanvasRect.bottom		=m_Size.cy;
		FillRect(m_hCanvasDC,&CanvasRect,m_pStyle->m_hBackgroundBrush);
		RECT	TitleRect;
		TitleRect			=CanvasRect;
		TitleRect.bottom	=TitleRect.top+m_pStyle->m_dwTitleHeight;
		FillRect(m_hCanvasDC,&TitleRect,m_pStyle->m_hTitleBkBrush);
		
		HideTips();
		DrawFrames();



		HPEN	hOldPen		=(HPEN)SelectObject(m_hCanvasDC,m_pStyle->m_hBorderPen);
		
		MoveToEx(m_hCanvasDC,CanvasRect.left,CanvasRect.top,NULL);
		LineTo(m_hCanvasDC,CanvasRect.right-1,CanvasRect.top);
		LineTo(m_hCanvasDC,CanvasRect.right-1,CanvasRect.bottom-1);
		LineTo(m_hCanvasDC,CanvasRect.left,CanvasRect.bottom-1);
		LineTo(m_hCanvasDC,CanvasRect.left,CanvasRect.top);

		MoveToEx(m_hCanvasDC,CanvasRect.left+m_pStyle->m_lFirstColumnWidth,CanvasRect.top,NULL);
		LineTo(m_hCanvasDC,CanvasRect.left+m_pStyle->m_lFirstColumnWidth,CanvasRect.bottom-1);

		MoveToEx(m_hCanvasDC,CanvasRect.left,CanvasRect.top+m_pStyle->m_dwTitleHeight,NULL);
		LineTo(m_hCanvasDC,CanvasRect.right-1,CanvasRect.top+m_pStyle->m_dwTitleHeight);

		SelectObject(m_hCanvasDC,hOldPen);

		int			OldMode		=SetBkMode(m_hCanvasDC,TRANSPARENT);
		COLORREF	OldClr		=SetTextColor(m_hCanvasDC,m_pStyle->m_TitleColor);
		HFONT		hOldFont	=(HFONT)SelectObject(m_hCanvasDC,m_pStyle->m_hTitleFont);
		RECT		TextRect;

		TextRect.left	=1;
		TextRect.top	=1;
		TextRect.right =m_pStyle->m_lFirstColumnWidth-1;
		TextRect.bottom=m_pStyle->m_dwTitleHeight-1;

		DrawText(m_hCanvasDC,"对象",4,&TextRect,DT_SINGLELINE|DT_VCENTER|DT_CENTER);


		SetBkMode(m_hCanvasDC,OldMode);
		SetTextColor(m_hCanvasDC,OldClr);
		SelectObject(m_hCanvasDC,hOldFont);


		DrawCoordinate();
		
		m_pTips->OnDraw(m_hCanvasDC);
		m_pScrollbar->OnDraw(m_hCanvasDC);

	}
	VOID			CTimeAxis::Draw(BOOL IN bRedraw)
	{
		if(bRedraw || m_bRedraw)
		{
			Redraw();
			m_bRedraw	=FALSE;
		}
		BitBlt(m_hPaintDC,
			m_Pos.x,m_Pos.y,
			m_Size.cx,m_Size.cy,
			m_hCanvasDC,
			0,0,
			SRCCOPY);

		if(m_bDragingSplitter)
			DrawDragLine();
		DrawTimeLine();
	}
	BOOL			CTimeAxis::PreTranslateMessage(MSG* IN pMsg)
	{
		switch(pMsg->message)
		{
		//case WM_KEYDOWN:
		//	{
		//		if(OnProcessDeleteAnchor(pMsg->wParam))
		//			return TRUE;
		//	}
		//	break;
		case WM_MOUSEMOVE:
			{
				POINT	pt =pMsg->pt;
				ScreenToClient(m_hWnd,&pt);
				if(OnProcessDragTimeLine(pt))
					return TRUE;
				if(OnProcessDragSplitter(pt))
					return TRUE;
				if(OnProcessDragTitle(pt))
					return TRUE;

				//------------------------------------------------------
				if(OnMouseOverTimeLine(pt))
					return TRUE;
				if(OnMouseOverSplitter(pt))
					return TRUE;
				//------------------------------------------------------


			}
			break;
		case WM_LBUTTONDOWN:
			{
				POINT	pt =pMsg->pt;
				ScreenToClient(m_hWnd,&pt);
				
				RECT	rect;
				rect.left		=m_Pos.x;
				rect.top		=m_Pos.y;
				rect.right		=rect.left	+m_Size.cx;
				rect.bottom		=rect.top	+m_Size.cy;
				if(!PtInRect(&rect,pt))
					return FALSE;

				if(OnStartDragTimeLine(pt))
					return TRUE;
				if(OnStartDragSplitter(pt))
					return TRUE;
				if(OnStartDragTitle(pt))
					return TRUE;


			}
			break;
		case WM_LBUTTONUP:
			{
				POINT	pt =pMsg->pt;
				ScreenToClient(m_hWnd,&pt);

				if(OnEndDragTimeLine(pt))
					return TRUE;
				if(OnEndDragSplitter(pt))
					return TRUE;
				if(OnEndDragTitle(pt))
					return TRUE;

			}
			break;
		case WM_MOUSEWHEEL:
			{
				SHORT	zDelta	= GET_WHEEL_DELTA_WPARAM(pMsg->wParam)/WHEEL_DELTA;
				WORD	key		= GET_KEYSTATE_WPARAM(pMsg->wParam);

				POINT	pt		=pMsg->pt;
				ScreenToClient(m_hWnd,&pt);

				if(OnProcessZoomTitle(pt,key,zDelta))
					return TRUE;

				if(OnProcessScrollFrames(pt,key,zDelta))
					return TRUE;

			}
			break;
		case WM_LBUTTONDBLCLK:
			{
				POINT	pt =pMsg->pt;
				ScreenToClient(m_hWnd,&pt);
				RECT	rect;
				rect.left		=m_Pos.x;
				rect.top		=m_Pos.y;
				rect.right		=rect.left	+m_Size.cx;
				rect.bottom		=rect.top	+m_Size.cy;
				if(!PtInRect(&rect,pt))
					return FALSE;


				if(OnLocateTimeLine(pt))
					return TRUE;
			}
			break;
		}

		//----------------------------------------
		MSG		frameMsg =*pMsg;
		ScreenToClient(m_hWnd,&frameMsg.pt);
		frameMsg.pt.x	-= m_Pos.x;
		frameMsg.pt.y	-= m_Pos.y;

		if(m_pScrollbar->PreTranslateMsg(&frameMsg))
			return TRUE;
		if(FramePretranslateMsg(&frameMsg))
			return TRUE;
		//----------------------------------------



		return FALSE;
	}
	VOID			CTimeAxis::ResetCanvas(LONG IN cx,LONG IN cy)
	{
		m_Size.cx	=cx;
		m_Size.cy	=cy;
		if(m_hCanvas != NULL)
			DeleteObject(m_hCanvas);
		if(m_hCanvasDC != NULL)
			DeleteDC(m_hCanvasDC);
		m_hCanvasDC	=CreateCompatibleDC(m_hPaintDC);
		if(m_hCanvasDC == NULL)
			return;

		m_hCanvas	=CreateCompatibleBitmap(m_hPaintDC,cx,cy);
		if(m_hCanvas == NULL)
			return;
		SelectObject(m_hCanvasDC,m_hCanvas);

		m_pTime->m_dwWidth		=m_Size.cx - m_pStyle->m_lFirstColumnWidth - m_pStyle->m_dwLeftMargin-m_pStyle->m_dwRightMargin;
		m_bRedraw				=TRUE;
	}
	
	VOID			CTimeAxis::DrawDragLine()
	{
		HPEN	hOldPen		=(HPEN)SelectObject(m_hPaintDC,m_pStyle->m_hDragLinePen);
		MoveToEx(m_hPaintDC,m_DragCurPoint.x,m_Pos.y,NULL);
		LineTo(m_hPaintDC,m_DragCurPoint.x,m_Pos.y+m_Size.cy);
		SelectObject(m_hPaintDC,hOldPen);
	}
	VOID			CTimeAxis::DrawCoordinate()
	{

		POINT	startPt,pt;
		startPt.x	=0+m_pStyle->m_lFirstColumnWidth+m_pStyle->m_dwLeftMargin;
		startPt.y	=0+m_pStyle->m_dwTitleHeight-1;

		HPEN		hOldPen		=(HPEN)SelectObject(m_hCanvasDC,m_pStyle->m_hCoordPen);
		RECT		TextRect;
		CHAR		Text[32];
		DWORD		dwTime		=0;
		HFONT		hOldFont	=(HFONT)SelectObject(m_hCanvasDC,m_pStyle->m_hCoordFont);
		COLORREF	OldColor	=SetTextColor(m_hCanvasDC,m_pStyle->m_TitleColor);
		int			OldMode		=SetBkMode(m_hCanvasDC,TRANSPARENT);

		DWORD		dwPrevCount	=m_pTime->m_dwStartTime%(m_pTime->m_dwTimePerUnit*10);
		dwPrevCount =dwPrevCount/m_pTime->m_dwTimePerUnit;
		
	

		for(int i=0;;i++)
		{
			pt.x	=startPt.x + i*m_pTime->m_dwUnitSize;
			pt.y	=startPt.y;
			if(pt.x > m_Size.cx-m_pStyle->m_dwRightMargin)
				break;
			dwTime	=m_pTime->m_dwStartTime + i*m_pTime->m_dwTimePerUnit;
			if(dwTime > m_pTime->m_dwEndTime)
				break;

			MoveToEx(m_hCanvasDC,pt.x,pt.y,NULL);
			if((i+dwPrevCount)%10==0)
			{
				pt.y=0;
				TextRect.left	=pt.x+2;
				TextRect.top	=pt.y+2;
				TextRect.right =pt.x+m_pTime->m_dwUnitSize*10;
				TextRect.bottom=pt.y+m_pStyle->m_dwTitleHeight-1;

				if(dwTime%10 != 0)
				{
					sprintf(Text,"%.3f",(float)dwTime/1000.0f);
				}
				else if(dwTime%100 != 0)
				{
					sprintf(Text,"%.2f",(float)dwTime/1000.0f);
				}
				else if(dwTime%1000 != 0)
				{
					sprintf(Text,"%.1f",(float)dwTime/1000.0f);
				}
				else
				{
					sprintf(Text,"%.0f",(float)dwTime/1000.0f);
				}
				DrawText(m_hCanvasDC,Text,strlen(Text),&TextRect,DT_SINGLELINE|DT_LEFT|DT_TOP);
			}
			else if((i+dwPrevCount)%5==0)
			{
				pt.y-=10;
			}
			else
			{
				pt.y-=5;
			}
			LineTo(m_hCanvasDC,pt.x,pt.y);
		}
		SetTextColor(m_hCanvasDC,OldColor);
		SetBkMode(m_hCanvasDC,OldMode);
		SelectObject(m_hCanvasDC,hOldPen);
		SelectObject(m_hCanvasDC,hOldFont);
	}
	VOID			CTimeAxis::DrawTimeLine()
	{
		LONG	lOffset		=m_pTime->GetCurrentPos();
		if(lOffset < 0)
			return;
		if(lOffset > m_pTime->m_dwWidth)
			return;

		POINT	pt;
		pt.x	=m_Pos.x + m_pStyle->m_dwLeftMargin + m_pStyle->m_lFirstColumnWidth + lOffset ;
		pt.y	=m_Pos.y;

		HPEN	hOldPen		=(HPEN)SelectObject(m_hPaintDC,m_pStyle->m_hTimeLinePen);


		MoveToEx(m_hPaintDC,pt.x,pt.y,NULL);
		LineTo(m_hPaintDC,pt.x,pt.y+m_Size.cy-1);

		SelectObject(m_hPaintDC,hOldPen);

		HFONT		hOldFont	=(HFONT)SelectObject(m_hPaintDC,m_pStyle->m_hCoordFont);
		COLORREF	OldColor	=SetTextColor(m_hPaintDC,m_pStyle->m_TimeLineTextColor);
		int			OldMode		=SetBkMode(m_hPaintDC,OPAQUE);
		COLORREF	OldBkColor	=SetBkColor(m_hPaintDC,~m_pStyle->m_TimeLineTextColor);

		RECT	TextRect;

		TextRect.left	= pt.x+1;
		TextRect.right	= pt.x+m_pTime->m_dwUnitSize*10;
		TextRect.top	= m_Pos.y + 1;
		TextRect.bottom= m_Pos.y + m_pStyle->m_dwTitleHeight-2;

		if(TextRect.right > m_Pos.x+m_Size.cx)
			TextRect.right = m_Pos.x+m_Size.cx;
		
		CHAR	Text[32];
		
		if(m_pTime->m_dwCurTime%10 != 0)
		{
			sprintf(Text,"%.3fs",(float)m_pTime->m_dwCurTime/1000.0f);
		}
		else if(m_pTime->m_dwCurTime%100 != 0)
		{
			sprintf(Text,"%.2fs",(float)m_pTime->m_dwCurTime/1000.0f);
		}
		else if(m_pTime->m_dwCurTime%1000 != 0)
		{
			sprintf(Text,"%.1fs",(float)m_pTime->m_dwCurTime/1000.0f);
		}
		else
		{
			sprintf(Text,"%.0fs",(float)m_pTime->m_dwCurTime/1000.0f);
		}

		DrawText(m_hPaintDC,Text,strlen(Text),&TextRect,DT_SINGLELINE|DT_BOTTOM|DT_LEFT);


		SelectObject(m_hPaintDC,hOldFont);
		SetTextColor(m_hPaintDC,OldColor);
		SetBkMode(m_hPaintDC,OldMode);
		SetBkColor(m_hPaintDC,OldBkColor);


	}
	INT				CTimeAxis::GetMaxFrameRows()
	{
		return (m_Size.cy-m_pStyle->m_dwTitleHeight)/m_pStyle->m_dwRowHeight;
	}
	LONG			CTimeAxis::GetFramesCount()
	{
		LONG		lCount=0;
		CTAFrame*	pFrame;
		for(int i=0;i<m_pFrameList->GetCount();i++)
		{
			pFrame =(CTAFrame*)m_pFrameList->GetObj(i);

			lCount += pFrame->GetFramesCount();
		}
		return lCount;
	}
	VOID			CTimeAxis::UpdateScrollBar()
	{
		m_pScrollbar->SetLength(m_Size.cy - (m_pStyle->m_dwTitleHeight+1));
		m_pScrollbar->SetPerPageCount(GetMaxFrameRows());
		m_pScrollbar->SetMaxCount(GetFramesCount());
	}

	VOID			CTimeAxis::DrawFrames()
	{
		INT			iRowIndex	=0;
		INT			iMaxRows	=GetMaxFrameRows();
		SIZE		FrameSize;
		POINT		StartPt;

		FrameSize.cx	=m_Size.cx-m_pStyle->m_dwRightMargin;
		FrameSize.cy	=m_pStyle->m_dwRowHeight;
		StartPt.x		=1;
		StartPt.y		=m_pStyle->m_dwTitleHeight+1;

		m_pDrawFrameList->Clear();
		INT			iStartRow	=m_pScrollbar->GetScrollPos();

		if(iMaxRows >= m_pScrollbar->GetMaxCount())
			iStartRow =0;


		CTAFrame*	pFrame;
		for(int i=0;i<m_pFrameList->GetCount();i++)
		{
			pFrame =(CTAFrame*)m_pFrameList->GetObj(i);

			pFrame->SetPos(StartPt.x,StartPt.y + (iRowIndex-iStartRow)*FrameSize.cy);
			pFrame->SetSize(FrameSize.cx,FrameSize.cy);
			pFrame->OnDraw(m_hCanvasDC,iStartRow,iMaxRows,iRowIndex,m_pDrawFrameList);
			
			if(iRowIndex-iStartRow >= iMaxRows)
				break;
		}



	}
	BOOL			CTimeAxis::OnMouseOverSplitter(POINT IN pt)
	{
		RECT	rect;
		rect.top		=m_Pos.y+0;
		rect.bottom		=m_Pos.y+m_Size.cy;
		rect.left		=m_Pos.x+m_pStyle->m_lFirstColumnWidth-1;
		rect.right		=m_Pos.x+m_pStyle->m_lFirstColumnWidth+1;
		if(PtInRect(&rect,pt))
		{
			ChangeCursor(IDC_SIZE_EW);
			return TRUE;
		}
		return FALSE;

	}
	BOOL			CTimeAxis::OnMouseOverTimeLine(POINT IN pt)
	{
		RECT	rect;
		rect.top		=m_Pos.y+0;
		rect.bottom		=m_Pos.y+m_Size.cy;
		
		LONG	lOffset		=m_pTime->GetCurrentPos();
		if(lOffset >= 0 || lOffset<m_pTime->m_dwWidth)
		{
			LONG x=m_Pos.x + m_pStyle->m_dwLeftMargin + m_pStyle->m_lFirstColumnWidth + lOffset ;
			rect.left	=x-1;
			rect.right	=x+1;
			if(PtInRect(&rect,pt))
			{
				ChangeCursor(IDC_MOVELINE);
				return TRUE;
			}
		}
		return FALSE;
	}

	BOOL			CTimeAxis::OnProcessDragSplitter(POINT IN pt)
	{
		if(m_bDragingSplitter)
		{ 


			ChangeCursor(IDC_SIZE_EW);


			LONG	minX =m_Pos.x+5+m_pStyle->m_dwLevelSpace*4;
			LONG	maxX =m_Pos.x+m_Size.cx-20;

			if(pt.x < minX )
			{
				pt.x=minX;
				ClientToScreen(m_hWnd,&pt);
				SetCursorPos(pt.x,pt.y);
			}
			if(pt.x > maxX)
			{
				pt.x=maxX;
				ClientToScreen(m_hWnd,&pt);
				SetCursorPos(pt.x,pt.y);
			}
			m_DragCurPoint =pt;
			Invalidate(FALSE,FALSE);
			return TRUE;
		}
		return FALSE;
	}
	BOOL			CTimeAxis::OnStartDragSplitter(POINT IN pt)
	{
		RECT	rect;
		rect.top		=m_Pos.y+0;
		rect.bottom		=m_Pos.y+m_Size.cy;
		rect.left		=m_Pos.x+m_pStyle->m_lFirstColumnWidth-1;
		rect.right		=m_Pos.x+m_pStyle->m_lFirstColumnWidth+1;
		if(PtInRect(&rect,pt))
		{
			SetCapture(m_hWnd);

			ChangeCursor(IDC_SIZE_EW);
			m_DragPoint				=pt;
			m_DragCurPoint			=pt;
			m_bDragingSplitter	=TRUE;
			return TRUE;
		}
		return FALSE;
	}
	BOOL			CTimeAxis::OnEndDragSplitter(POINT IN pt)
	{
		if(m_bDragingSplitter)
		{
			ReleaseCapture();
			m_bDragingSplitter	=FALSE;
			m_pStyle->m_lFirstColumnWidth =m_DragCurPoint.x-m_Pos.x;

			m_pScrollbar->SetPos(m_pStyle->m_lFirstColumnWidth - m_pStyle->m_theScrollStyle.m_dwWidth,m_pStyle->m_dwTitleHeight+1);

			m_pTime->m_dwWidth	=m_Size.cx-m_pStyle->m_lFirstColumnWidth - m_pStyle->m_dwLeftMargin -m_pStyle->m_dwRightMargin;

			Invalidate(TRUE,TRUE);
			return TRUE;
		}
		return FALSE;
	}

	BOOL			CTimeAxis::OnProcessDragTimeLine(POINT IN pt)
	{
		if(m_bDragingTimeLine)
		{

			ChangeCursor(IDC_MOVELINE);
			LONG minX=m_Pos.x + m_pStyle->m_dwLeftMargin + m_pStyle->m_lFirstColumnWidth ;
			LONG maxX=min( (minX + m_pTime->m_dwWidth),minX + (m_pTime->m_dwEndTime-m_pTime->m_dwStartTime)/m_pTime->m_dwTimePerUnit*m_pTime->m_dwUnitSize);

			if(pt.x < minX )
			{
				pt.x=minX;
				ClientToScreen(m_hWnd,&pt);
				SetCursorPos(pt.x,pt.y);
			}
			if(pt.x > maxX)
			{
				pt.x=maxX;
				ClientToScreen(m_hWnd,&pt);
				SetCursorPos(pt.x,pt.y);
			}
			m_pTime->m_dwCurTime	=m_pTime->OffsetToTime(pt.x-(m_Pos.x+m_pStyle->m_dwLeftMargin+m_pStyle->m_lFirstColumnWidth));

			m_DragCurPoint =pt;
			Invalidate();
			return TRUE;
		}
		return FALSE;
	}
	BOOL			CTimeAxis::OnStartDragTimeLine(POINT IN pt)
	{
		RECT	rect;
		rect.top	=m_Pos.y+0;
		rect.bottom =m_Pos.y+m_Size.cy;
		LONG	lOffset		=m_pTime->GetCurrentPos();
		if(lOffset >= 0 || lOffset<m_pTime->m_dwWidth)
		{
			LONG x=m_Pos.x + m_pStyle->m_dwLeftMargin + m_pStyle->m_lFirstColumnWidth + lOffset ;
			rect.left	=x-1;
			rect.right	=x+1;
			if(PtInRect(&rect,pt))
			{
				SetCapture(m_hWnd);

				ChangeCursor(IDC_MOVELINE);
				m_DragPoint			=pt;
				m_bDragingTimeLine	=TRUE;
				return TRUE;
			}
		}
		return FALSE;
	}
	BOOL			CTimeAxis::OnEndDragTimeLine(POINT IN pt)
	{
		if(m_bDragingTimeLine)
		{
			ReleaseCapture();
			m_bDragingTimeLine	=FALSE;

			////////////////////////////////////////////////////////////////////////
			
				TAMsg	msg;
				msg.message		=TAMSG_TIMELINE_CHANGED;
				msg.pObject		=NULL;
				msg.time		=m_pTime->m_dwCurTime;
				SendMessage(GetWnd(),TAMSG_ID,(WPARAM)&msg,0);
			
			////////////////////////////////////////////////////////////////////////

			Invalidate();
			return TRUE;
		}
		return FALSE;
	}

	BOOL			CTimeAxis::OnProcessDragTitle(POINT IN pt)
	{
		if(m_bDragingTitle)
		{

			ChangeCursor(IDC_MOVE_CURSOR);
			LONG minX=m_Pos.x + m_pStyle->m_dwLeftMargin + m_pStyle->m_lFirstColumnWidth ;
			LONG maxX=minX + m_pTime->m_dwWidth;

			if(pt.x < minX )
			{
				pt.x=minX;
				ClientToScreen(m_hWnd,&pt);
				SetCursorPos(pt.x,pt.y);
			}
			if(pt.x > maxX)
			{
				pt.x=maxX;
				ClientToScreen(m_hWnd,&pt);
				SetCursorPos(pt.x,pt.y);
			}
			LONG	OffsetTime	=((pt.x - m_DragPoint.x)/(LONG)m_pTime->m_dwUnitSize)*(LONG)m_pTime->m_dwTimePerUnit;
			if(OffsetTime >= m_pTime->m_dwTimePerUnit)
			{
				OffsetTime =(LONG)((float)OffsetTime/(float)m_pTime->m_dwTimePerUnit) * (LONG)m_pTime->m_dwTimePerUnit;

				LONG	NewTime		=m_lDragStartTime - OffsetTime;
				if(NewTime<0)NewTime=0;
				m_pTime->m_dwStartTime=NewTime;

				DWORD	count			=m_pTime->m_dwWidth/m_pTime->m_dwUnitSize;
				if(count>10)
				{
					count-=10;
				}
				else
				{
					if(count>1)
						count-=1;
				}


				DWORD	LastStartTime	=m_pTime->m_dwEndTime - m_pTime->m_dwTimePerUnit*count;

				if(m_pTime->m_dwStartTime > LastStartTime)
					m_pTime->m_dwStartTime =LastStartTime;
				
				Invalidate(TRUE,TRUE);

			}
			m_DragCurPoint =pt;
			return TRUE;
		}
		return FALSE;
	}
	BOOL			CTimeAxis::OnStartDragTitle(POINT IN pt)
	{
		RECT rect;
		rect.left		=m_Pos.x +m_pStyle->m_lFirstColumnWidth + m_pStyle->m_dwLeftMargin;
		rect.right		=rect.left + m_pTime->m_dwWidth;
		rect.top		=m_Pos.y;
		rect.bottom		=m_Pos.y + m_pStyle->m_dwTitleHeight;
		if(PtInRect(&rect,pt))
		{
			SetCapture(m_hWnd);

			ChangeCursor(IDC_MOVE_CURSOR);
			m_DragPoint			=pt;
			m_bDragingTitle		=TRUE;
			m_lDragStartTime	=m_pTime->m_dwStartTime;
			return TRUE;
		
		}
		return FALSE;

	}
	BOOL			CTimeAxis::OnEndDragTitle(POINT IN pt)
	{
		if(m_bDragingTitle)
		{
			ReleaseCapture();
			m_bDragingTitle		=FALSE;
			Invalidate(TRUE,TRUE);
			return TRUE;
		}
		return FALSE;
	}
	BOOL			CTimeAxis::OnLocateTimeLine(POINT IN pt)
	{
		RECT rect;
		rect.left		=m_Pos.x +m_pStyle->m_lFirstColumnWidth + m_pStyle->m_dwLeftMargin;
		rect.right		=min( (rect.left + m_pTime->m_dwWidth),rect.left + (m_pTime->m_dwEndTime-m_pTime->m_dwStartTime)/m_pTime->m_dwTimePerUnit*m_pTime->m_dwUnitSize);
		rect.top		=m_Pos.y;
		rect.bottom		=m_Pos.y + m_pStyle->m_dwTitleHeight;
		if(PtInRect(&rect,pt))
		{
			DWORD	dwCurTime	=m_pTime->m_dwStartTime + ( ((pt.x-rect.left)/m_pTime->m_dwUnitSize) * m_pTime->m_dwTimePerUnit);
			
			m_pTime->m_dwCurTime =dwCurTime;
			

			////////////////////////////////////////////////////////////////////////
			
				TAMsg	msg;
				msg.message		=TAMSG_TIMELINE_CHANGED;
				msg.pObject		=NULL;
				msg.time		=dwCurTime;
				SendMessage(GetWnd(),TAMSG_ID,(WPARAM)&msg,0);
			
			////////////////////////////////////////////////////////////////////////

			Invalidate(FALSE);
			return TRUE;
		}
		return FALSE;
	}

	BOOL			CTimeAxis::OnProcessZoomTitle(POINT IN pt,WORD IN wKey,LONG IN lZDelta)
	{
		RECT rect;
		rect.left		=m_Pos.x +m_pStyle->m_lFirstColumnWidth + m_pStyle->m_dwLeftMargin;
		rect.right		=rect.left + m_pTime->m_dwWidth;
		rect.top		=m_Pos.y;
		rect.bottom		=m_Pos.y + m_pStyle->m_dwTitleHeight;
		if(PtInRect(&rect,pt))
		{
			if(m_pTime->TimeRateUpdate(wKey,lZDelta))
			{
				Invalidate(TRUE,TRUE);
			}			
			return TRUE;
		}
		return FALSE;
	}
	BOOL			CTimeAxis::OnProcessScrollFrames(POINT IN pt,WORD IN wKey,LONG IN lZDelta)
	{
		RECT rect;
		rect.left		=m_Pos.x;
		rect.right		=rect.left + m_Size.cx;
		rect.top		=m_Pos.y + m_pStyle->m_dwTitleHeight;
		rect.bottom		=m_Pos.y + m_Size.cy;
		if(PtInRect(&rect,pt))
		{
			LONG	pos		=m_pScrollbar->GetScrollPos();
			LONG	maxPos	=m_pScrollbar->GetMaxCount()-1;

			pos -= lZDelta;
			if(pos > maxPos)
				pos =maxPos;
			if(pos < 0)
				pos =0;
			m_pScrollbar->SetScrollPos(pos);

			Invalidate(TRUE);
			return TRUE;
		}
		return FALSE;
	}
	BOOL			CTimeAxis::OnProcessDeleteAnchor(DWORD IN dwKey)
	{
		if(dwKey == VK_DELETE)
		{
			if(m_pActiveAnchor != NULL)
			{
				CTAFrame*	pFrame =m_pActiveAnchor->GetFrame();
				if(pFrame!=NULL)
					pFrame->DelAnchor(m_pActiveAnchor);
				return TRUE;
			}
		}
		return FALSE;
	}

	CTAFrame*		CTimeAxis::AddFrame(TAOST_TYPE IN type,LPCSTR IN pFrameName,LPCSTR IN pFrameDesc,UINT_PTR IN UserData)
	{
		CTAFrame*	pFrame =NULL;

		pFrame	=new CTAFrame(m_pTime,m_pStyle);
		pFrame->SetName(pFrameName);
		pFrame->SetDesc(pFrameDesc);
		pFrame->SetSubType(type);
		pFrame->SetUserData(UserData);
		pFrame->SetLevel(0);
		pFrame->SetParent(NULL);

		m_pFrameList->AddObj(pFrame);
		pFrame->Release();

		return pFrame;

	}
	BOOL			CTimeAxis::DelFrame(CTAFrame* IN pFrame)
	{
		CTAFrame*	pFind	=NULL;
		for(LONG i=0;i<m_pFrameList->GetCount();i++)
		{
			pFind =(CTAFrame*)m_pFrameList->GetObj(i);
			if(pFind == pFrame)
			{
				////////////////////////////////////////////////////////////////////////
			
				TAMsg	msg;
				msg.message		=TAMSG_DELETED;
				msg.pObject		=pFrame;
				msg.time		=0;
				SendMessage(GetWnd(),TAMSG_ID,(WPARAM)&msg,0);
				////////////////////////////////////////////////////////////////////////
				m_pDrawFrameList->DelObj(pFind);
				m_pFrameList->DelObj(i);
				return TRUE;
			}
			if(pFind->DelFrame(pFrame))
				return TRUE;
		}
		return FALSE;
	}
	BOOL			CTimeAxis::DelFrame(LPCSTR IN pFrameName)
	{
		CTAFrame*	pFind	=NULL;
		for(LONG i=0;i<m_pFrameList->GetCount();i++)
		{
			pFind =(CTAFrame*)m_pFrameList->GetObj(i);
			if(strcmp(pFind->GetName(),pFrameName)==0)
			{
				////////////////////////////////////////////////////////////////////////

				TAMsg	msg;
				msg.message		=TAMSG_DELETED;
				msg.pObject		=pFind;
				msg.time		=0;
				SendMessage(GetWnd(),TAMSG_ID,(WPARAM)&msg,0);
				
				////////////////////////////////////////////////////////////////////////
				m_pDrawFrameList->DelObj(pFind);
				m_pFrameList->DelObj(i);
				return TRUE;
			}
			if(pFind->DelFrame(pFrameName))
				return TRUE;
		}
		return FALSE;
	}
	CTAFrame*		CTimeAxis::FindFrame(LPCSTR IN pFrameName)
	{
		CTAFrame*	pFrame =NULL;
		CTAFrame*	pFind	=NULL;
		for(LONG i=0;i<m_pFrameList->GetCount();i++)
		{
			pFrame =(CTAFrame*)m_pFrameList->GetObj(i);
			if(strcmp(pFrame->GetName(),pFrameName)==0)
			{
				return pFrame;
			}
			pFind =pFrame->FindFrame(pFrameName);
			if(pFind != NULL)
				return pFind;
		}
		return NULL;
	}

	VOID			CTimeAxis::ClearFrame()
	{
		m_pFrameList->Clear(TRUE);
	}
	VOID			CTimeAxis::SetActiveFrame(CTAFrame* IN pFrame)
	{
		if(m_pActiveFrame == pFrame )
			return;
		if(m_pActiveFrame != NULL)
		{
			////////////////////////////////////////////////////////////////////////
			TAMsg	msg;
			msg.message		=TAMSG_UNSELECT;
			msg.pObject		=m_pActiveFrame;
			msg.time		=0;
			SendMessage(GetWnd(),TAMSG_ID,(WPARAM)&msg,0);
			////////////////////////////////////////////////////////////////////////
			m_pActiveFrame->Active(FALSE);
		}
		m_pActiveFrame	=pFrame;
		if(m_pActiveFrame != NULL)
		{
			////////////////////////////////////////////////////////////////////////
			
			TAMsg	msg;
			msg.message		=TAMSG_SELECTED;
			msg.pObject		=m_pActiveFrame;
			msg.time		=0;
			SendMessage(GetWnd(),TAMSG_ID,(WPARAM)&msg,0);
			
			////////////////////////////////////////////////////////////////////////

			m_pActiveFrame->Active(TRUE);
		}
		Invalidate(TRUE);
	}
	VOID			CTimeAxis::SetActiveAnchor(CTAAnchor* IN pAnchor)
	{
		if(m_pActiveAnchor == pAnchor )
			return;
		if(m_pActiveAnchor != NULL)
		{
			////////////////////////////////////////////////////////////////////////
			
			TAMsg	msg;
			msg.message		=TAMSG_UNSELECT;
			msg.pObject		=m_pActiveAnchor;
			msg.time		=0;
			SendMessage(GetWnd(),TAMSG_ID,(WPARAM)&msg,0);
			
			////////////////////////////////////////////////////////////////////////

			m_pActiveAnchor->SetSelected(FALSE);
		}
		m_pActiveAnchor	=pAnchor;
		
		if(m_pActiveAnchor != NULL)
		{
			////////////////////////////////////////////////////////////////////////
			
			TAMsg	msg;
			msg.message		=TAMSG_SELECTED;
			msg.pObject		=m_pActiveAnchor;
			msg.time		=0;
			SendMessage(GetWnd(),TAMSG_ID,(WPARAM)&msg,0);
			
			////////////////////////////////////////////////////////////////////////

			m_pActiveAnchor->SetSelected(TRUE);
		}
		Invalidate(TRUE);
	}

	BOOL			CTimeAxis::FramePretranslateMsg(MSG* IN pMsg)
	{
		CTAFrame*	pFrame	=NULL;
		for(LONG i=0;i<m_pDrawFrameList->GetCount();i++)
		{
			pFrame	=(CTAFrame*)m_pDrawFrameList->GetObj(i);
			if(pFrame->PreTranslateMessage(pMsg))
				return TRUE;
		}
		return FALSE;
	}
	VOID			CTimeAxis::SetEndTime(DWORD IN dwTime)
	{
		m_pTime->m_dwEndTime =dwTime;
		if(m_pTime->m_dwCurTime > dwTime)
		{
			m_pTime->m_dwCurTime =dwTime;
			////////////////////////////////////////////////////////////////////////
			TAMsg	msg;
			msg.message		=TAMSG_TIMELINE_CHANGED;
			msg.pObject		=NULL;
			msg.time		=dwTime;
			SendMessage(GetWnd(),TAMSG_ID,(WPARAM)&msg,0);
			////////////////////////////////////////////////////////////////////////
		}
		Invalidate(TRUE,TRUE);
	}
	DWORD			CTimeAxis::GetEndTime()
	{
		return m_pTime->m_dwEndTime;
	}

	BOOL			CTimeAxis::SetCurTime(DWORD IN dwTime)
	{
		if(m_pTime->m_dwCurTime == dwTime)
			return TRUE;

		if(dwTime > m_pTime->m_dwEndTime)
			return FALSE;
		BOOL	bInvalidateChild	=FALSE;
		m_pTime->m_dwCurTime =dwTime;
		
		if(m_pTime->m_dwStartTime > dwTime)
		{
			m_pTime->m_dwStartTime	=dwTime;
			bInvalidateChild		=TRUE;
		}

		DWORD	right =m_pTime->m_dwStartTime + (m_pTime->m_dwWidth/m_pTime->m_dwUnitSize*m_pTime->m_dwTimePerUnit);
		if(dwTime >= right )
		{
			m_pTime->m_dwStartTime	=right;
			bInvalidateChild		=TRUE;
		}
		////////////////////////////////////////////////////////////////////////
		
		TAMsg	msg;
		msg.message		=TAMSG_TIMELINE_CHANGED;
		msg.pObject		=NULL;
		msg.time		=dwTime;
		SendMessage(GetWnd(),TAMSG_ID,(WPARAM)&msg,0);
		
		////////////////////////////////////////////////////////////////////////


		Invalidate(TRUE,bInvalidateChild);
		return TRUE;

	}
	BOOL			CTimeAxis::StepTime(DWORD IN dwIntervalTime)
	{
		return SetCurTime(m_pTime->m_dwCurTime + dwIntervalTime);
	}
	VOID			CTimeAxis::EnsureFrameVisible(CTAFrame* IN pFrame)
	{
		if(pFrame == NULL)
			return;

		CTAObject*	pParent =pFrame->GetParent();
		while(pParent!=NULL)
		{
			if(pParent->GetType()==TAOT_Frame)
				((CTAFrame*)pParent)->Expand(TRUE);
			pParent =pParent->GetParent();
		}

		LONG lIndex=0;
		GetFrameSequence(pFrame,lIndex);

		if(lIndex > GetScrollPos() && lIndex< ( GetScrollPos()+m_pScrollbar->GetPerPageCount()) )
			return;
		lIndex-=1;
		if(lIndex<0)lIndex=0;
		SetScrollPos(lIndex);
	}

	BOOL			CTimeAxis::GetFrameSequence(CTAFrame* IN pFrame,LONG& lSequence)
	{
		lSequence =0;
		CTAFrame*	p	=NULL;
		for(LONG i=0;i<m_pFrameList->GetCount();i++)
		{
			p =(CTAFrame*)m_pFrameList->GetObj(i);
			if(p == pFrame)
				return TRUE;
			//-------------------------
			if(p->GetFrameSequence(pFrame,lSequence))
				return TRUE;
		}
		return FALSE;
	}
	VOID			CTimeAxis::SetScrollPos(LONG IN lPos)
	{
		m_pScrollbar->SetScrollPos(lPos);
	}
	LONG			CTimeAxis::GetScrollPos()
	{
		return m_pScrollbar->GetScrollPos();
	}
}