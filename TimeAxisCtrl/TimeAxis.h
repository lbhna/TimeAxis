
#pragma once
/********************************************************************\
	created:	2013/03/25   10:46
	filename: 	D:\LIBO\Development Resource\自定义类\时间轴\TimeAxisCtrl\TimeAxis.h
	author:		LB
	purpose:	时间轴控件
\*********************************************************************/
#ifdef _TimeAxis_DLL
	#define TA_EXPORT			__declspec(dllexport)
#else
	#define TA_EXPORT			__declspec(dllimport)

	#ifdef _DEBUG
		#pragma comment(lib,"TimeAxis_d.lib")
	#else 
		#pragma comment(lib,"TimeAxis.lib")
	#endif
#endif



namespace TimeAxis
{
#define Safe_DeleteDC(p)		{if(p!=NULL){DeleteDC(p);p=NULL;}}
#define Safe_DeleteObject(p)	{if(p!=NULL){DeleteObject(p);p=NULL;}}
#define Safe_Delete(p)			{if(p!=NULL){delete p;p=NULL;}}
#define Safe_DeleteArray(p)		{if(p!=NULL){delete []p;p=NULL;}}
#define Safe_Release(p)			{if(p!=NULL){p->Release();p=NULL;}}
	//--------------------------------------------------------


	typedef enum TA_EXPORT _TAObjectType
	{
		TAOT_Object				=0x00,
		TAOT_ObjectList,
		TAOT_Frame,
		TAOT_Anchor,
		TAOT_ScrollBar,
		TAOT_TIPS,

		//////////////////
		TAOT_ForceDword	=0x7fffffff,
	}TAOT_TYPE;

	typedef enum TA_EXPORT _TimeAxisSubType
	{
		TAOST_Unknown				=0,
		//---------------------------------
		TAOST_Anchor_CircleReal,			//圆形实心●
		TAOST_Anchor_CircleNull,			//圆形空心○
		TAOST_Anchor_DoubleCircle,			//双圆形◎

		TAOST_Anchor_RectangleReal,			//正方形实心■
		TAOST_Anchor_RectangleNull,			//正方形空心□

		TAOST_Anchor_StarReal,				//五角星实心★
		TAOST_Anchor_StarNull,				//五角星空心☆

		TAOST_Anchor_ArrisReal,				//棱形实心◆
		TAOST_Anchor_ArrisNull,				//棱形空心◇

		TAOST_Anchor_TriangleReal,			//三角实心▲
		TAOST_Anchor_TriangleNull,			//三角空心△

		TAOST_Anchor_Icon,					//图标形式的
		
		


		//---------------------------------
		TAOST_USER			=0x10000000,

		//////////////////
		TAOST_ForceDword	=0x7fffffff,

	}TAOST_TYPE;


	//--------------------------------------------------------
	//--------------------------------------------------------
	//--------------------------------------------------------
	//--------------------------------------------------------
	//--------------------------------------------------------
	//--------------------------------------------------------
	//--------------------------------------------------------
	//--------------------------------------------------------
	//--------------------------------------------------------

#define		TIME_RATE_ARRAY_SIZE	16


	#define		TAMSG_ID				(WM_USER+1024)
	typedef enum TA_EXPORT _TAObjectMsg
	{
		TAMSG_LDCLICKED	=0,			//左键双击
		TAMSG_RCLICKED,				//右键单击
		TAMSG_CHANGED,				//属性、状态改变
		TAMSG_DELETED,				//对象被删除
		TAMSG_SELECTED,				//对象被选中
		TAMSG_UNSELECT,				//对象取消选中
	
		TAMSG_RCLICKED_LINKLINE,	//右键单击

		TAMSG_TIMELINE_CHANGED,		//当前时间线时间改变
		//////////////////////////////////
		TAMSG_FORCE_DWORD	=0x7fffffff,
	}TAMSG;


	//-----------------------------------


	class TA_EXPORT CTATime
	{
	public:
		DWORD		m_dwCurTime;		//当前时间
		DWORD		m_dwStartTime;		//刻度起始时间
		DWORD		m_dwEndTime;		//结束时间
		DWORD		m_dwTimePerUnit;	//每个刻度代表多少毫秒1,2,5,10,20,50,100,200,500,1000,2000,50000,100000,20000,50000,100000
		DWORD		m_dwUnitSize;		//当前刻度单位多少象素
		DWORD		m_dwUnitMaxSize;
		DWORD		m_dwUnitMinSize;

	public:
		DWORD		m_dwWidth;			//总宽度
	public:
		static DWORD m_dwTimeRateArray[19];
	
	public:
		CTATime();
	public:
		LONG		GetCurrentPos();
		LONG		TimeToOffset(DWORD IN dwTime);
		DWORD		OffsetToTime(LONG IN lOffset);
		BOOL		TimeRateUpdate(WORD IN wKey,LONG IN zDelta);
	};
	class TA_EXPORT CTAAnchorStyle
	{
	public:
		DWORD			m_dwAnchorSize;
		COLORREF		m_SelectedFrameColor;
		LONG			m_lSelectedFrameSpace;
		CString			m_strAnchorFontName;
		
		COLORREF		m_LinkLineColor;
		COLORREF		m_LinkLineActiveColor;
		DWORD			m_LinkLineWidth;
		DWORD			m_LinkLineStyle;

		COLORREF		m_TimeRangeColor;
		COLORREF		m_TimeRangeActiveColor;

		COLORREF		m_DisableColor;
	public:
		HPEN			m_hSelectedFramePen;
		HFONT			m_hAnchorFont;
		HPEN			m_hLinkPen;
		HPEN			m_hLinkActivePen;
		HPEN			m_hTimeRangePen;
		HPEN			m_hTimeRangeActivePen;
		HPEN			m_hDisablePen;
	public:
		CTAAnchorStyle();
		~CTAAnchorStyle();
	public:
		VOID	InitGDIObject();

	};
	class TA_EXPORT CTAScrollStyle
	{
	public:
		DWORD			m_dwWidth;
		COLORREF		m_BkColor;
		COLORREF		m_BarColor;
		COLORREF		m_BarBorderColor;
	public:
		HBRUSH			m_hBkBrush;
		HPEN			m_hBkPen;
		HPEN			m_hBarBorderPen;
		HBRUSH			m_hBarBrush;
		HPEN			m_hPastePen;
	public:
		CTAScrollStyle();
		~CTAScrollStyle();
	public:
		VOID			InitGDIObject();
	};
	class TA_EXPORT CTAFrameStyle
	{
	public:
		DWORD			m_dwLeftMargin;

		COLORREF		m_BorderColor;
		COLORREF		m_BkColor1;
		COLORREF		m_BkColor2;
		COLORREF		m_DisableBkColor;
		COLORREF		m_ActiveBkColor;
		UINT			m_BkFillStyle;
		CString			m_strNameFontName;
		DWORD			m_dwNameFontNameSize;
		COLORREF		m_NameColor;

		COLORREF		m_RootLineColor;
		COLORREF		m_RootBorderColor;
		COLORREF		m_RootFlagColor;

	public:
		HFONT			m_hNameFont;
		HPEN			m_hBorderPen;
		HBRUSH			m_hNormalBkBrush1;
		HBRUSH			m_hNormalBkBrush2;
		HBRUSH			m_hDisableBkBrush;

		HBRUSH			m_hActiveBkBrush;

		HPEN			m_hRootLinePen;
		HPEN			m_hRootBorderPen;
		HPEN			m_hRootFlagPen;
	public:
		CTAFrameStyle();
		~CTAFrameStyle();
		VOID	InitGDIObject();
	};
	
	//--------------------------------------------------------
	//--------------------------------------------------------
	//--------------------------------------------------------
	//--------------------------------------------------------
	class TA_EXPORT CTimeAxis;
	class TA_EXPORT CTAStyle
	{
	public:
		LONG			m_lFirstColumnWidth;//对象列宽度
		DWORD			m_dwRowHeight;
		DWORD			m_dwTitleHeight;
		DWORD			m_dwLeftMargin;
		DWORD			m_dwRightMargin;
		DWORD			m_dwLevelSpace;

		COLORREF		m_BkColor;
		COLORREF		m_TitleBkColor;

		COLORREF		m_TitleColor;
		CString			m_TitleFontName;
		DWORD			m_TitleFontSize;
		COLORREF		m_BorderColor;

		COLORREF		m_CoordColor;
		COLORREF		m_CoordTextColor;
		CString			m_CoordTextFontName;
		DWORD			m_CoordTextFontSize;

		COLORREF		m_TimeLineColor;
		COLORREF		m_TimeLineTextColor;

	public:
		CTAFrameStyle	m_theFrameStyle;
		CTAAnchorStyle	m_theAnchorStyle;
		CTAScrollStyle	m_theScrollStyle;

		CTimeAxis*		m_pTimeAxis;
	public:
		HBRUSH			m_hBackgroundBrush;
		HBRUSH			m_hTitleBkBrush;
		HPEN			m_hBorderPen;
		HPEN			m_hDragLinePen;
		HFONT			m_hTitleFont;
		HFONT			m_hCoordFont;
		HPEN			m_hTimeLinePen;
		HPEN			m_hCoordPen;

	public:
		CTAStyle();
		~CTAStyle();
		VOID	InitGDIObject();
	};
	//--------------------------------------------------------


	//--------------------------------------------------------
	class TA_EXPORT CTAObject
	{
	protected:
		TAOT_TYPE			m_Type;
		TAOST_TYPE			m_SubType;

		LONG				m_lRefCount;
		UINT_PTR			m_UserData;
		CTAObject*			m_pParent;
		CTATime*			m_pTime;
		CTAStyle*			m_pStyle;
	protected:
		BOOL				m_bInvalidate;
		LONG				m_lLevel;
		DWORD				m_dwID;
		LPSTR				m_pName;
		LPSTR				m_pDesc;
	public:
		CTAObject(CTATime*	pTime,CTAStyle* pStyle);
		virtual ~CTAObject();
	public:
		TAOT_TYPE			GetType()		{return m_Type;}
		VOID				SetType(TAOT_TYPE type){m_Type=type;}
		
		TAOST_TYPE			GetSubType()	{return m_SubType;}
		VOID				SetSubType(TAOST_TYPE type){m_SubType=type;}

		LONG				AddRef()		{return (++m_lRefCount);}
		VOID				Release();
		LONG				GetRefCount()	{return m_lRefCount;}
		UINT_PTR			GetUserData()	{return m_UserData;}
		VOID				SetUserData(UINT_PTR IN data){m_UserData=data;}
	public:
		virtual CTAObject*	GetParent()		{return m_pParent;}
		virtual VOID		SetParent(CTAObject* IN pParent){m_pParent=pParent;}
		virtual LONG		GetLevel()		{return m_lLevel;}
		virtual VOID		SetLevel(LONG IN lLevel){m_lLevel=lLevel;Invalidate();}
		virtual DWORD		GetID(){return m_dwID;}
		virtual VOID		SetID(DWORD IN dwID){m_dwID=dwID;}
		virtual LPCSTR		GetName(){return m_pName;}
		virtual VOID		SetName(LPCSTR IN pName){Safe_DeleteArray(m_pName);if(pName!=NULL){m_pName=new CHAR[strlen(pName)+1];strcpy(m_pName,pName);Invalidate();}}
		virtual LPCSTR		GetDesc(){return m_pDesc;}
		virtual VOID		SetDesc(LPCSTR IN pDesc){Safe_DeleteArray(m_pDesc);if(pDesc!=NULL){m_pDesc=new CHAR[strlen(pDesc)+1];strcpy(m_pDesc,pDesc);Invalidate();}}
		virtual VOID		Invalidate(BOOL IN bInvalidate=TRUE,BOOL IN bIncludeChild=TRUE){m_bInvalidate=bInvalidate;}
		virtual BOOL		IsInvalidate(){return m_bInvalidate;}


	};

	typedef struct TA_EXPORT _TAMsg
	{
		TAMSG			message;
		CTAObject*		pObject;
		DWORD			time;
	}TAMsg,*LPTAMsg;


	//--------------------------------------------------------
	class TA_EXPORT CTAObjectList:public CTAObject
	{
	protected:
		LONG			m_lMaxSize;
		LONG			m_lCount;
		CTAObject**		m_ppObj;
	public:
		CTAObjectList(CTATime*pTime,CTAStyle*pStyle);
		virtual ~CTAObjectList(void);
	public:
		LONG			GetCount();
		VOID			Clear(BOOL IN bDestroyMem=FALSE);
		CTAObject*		GetObj(LONG IN lIndex);
		CTAObject*		operator[](LONG IN lIndex){return GetObj(lIndex);}
		LONG			FindObj(CTAObject* IN pObj);
		BOOL			DelObj(LONG IN lIndex);
		BOOL			DelObj(CTAObject* IN pObj);
		VOID			AddObj(CTAObject* IN pObj);
		BOOL			InsertObj(LONG IN lIndex,CTAObject* IN pObj);
		BOOL			SetAt(LONG IN lIndex,CTAObject* IN pObj);

		BOOL			Swap(LONG IN lIndex1,LONG IN lIndex2);
		BOOL			Swap(CTAObject* IN pObj1,CTAObject* IN pObj2);

		CTAObjectList&	operator=(CTAObjectList& v);
	public:
		virtual VOID		Invalidate(BOOL IN bInvalidate=TRUE,BOOL IN bIncludeChild=TRUE);

	protected:
		VOID				OverflowCheck(LONG IN lStep=1);

	};
	//--------------------------------------------------------
	class TA_EXPORT CTATips:public CTAObject
	{
	protected:
		POINT				m_Pos;
		LPSTR				m_pText;
		COLORREF			m_Color;
		COLORREF			m_BorderColor;
		COLORREF			m_BkColor;
	protected:
		HFONT				m_hFont;
		HPEN				m_hBorderPen;
		HBRUSH				m_hBkBrush;
		BOOL				m_bShow;
	public:
		CTATips(CTATime*pTime,CTAStyle*pStyle);
		virtual ~CTATips();
	public:
		BOOL				Create(LPSTR IN pText,COLORREF IN clr,COLORREF IN bkClr=(200,200,180),COLORREF IN borderClr=RGB(0,0,100));
		VOID				SetPos(LONG IN x,LONG IN y);
		VOID				SetText(LPCSTR IN pText);
		VOID				Show(){m_bShow =TRUE;}
		VOID				Hide(){m_bShow =FALSE;}

	public:
		virtual VOID		OnDraw(HDC IN hDC);

	};
	class TA_EXPORT CTAFrame;
	class TA_EXPORT CTAAnchor:public CTAObject
	{
	protected:
		DWORD				m_dwTime;
		DWORD				m_dwEndTime;
		COLORREF			m_Color;
		BOOL				m_bDraging;
		BOOL				m_bSelected;
		POINT				m_StartDragPoint;
		POINT				m_DragOffset;
		CImageList			m_theImageList;
		BOOL				m_bShowTimeRange;

		BOOL				m_bEnable;
		LPSTR				m_pTips;	
	protected:
		CTAAnchor*			m_pPrevLink;
		CTAAnchor*			m_pNextLink;
	public:
		CTAAnchor(CTATime*pTime,CTAStyle*pStyle);
		virtual ~CTAAnchor();
	public:
		BOOL				Create(TAOST_TYPE IN type,COLORREF IN clr,DWORD IN dwTime,DWORD IN dwEndTime=0);
		BOOL				Create(UINT IN uIconResourceID,DWORD IN dwTime,DWORD IN dwEndTime=0);
	
		BOOL				IsSelected(){return m_bSelected;}
		VOID				SetSelected(BOOL IN bSelected);
		BOOL				IsEnable(){return m_bEnable;}
		VOID				Enable(BOOL IN bEnable);

		VOID				GetRect(RECT& OUT rect);
		BOOL				GetRangeRect(RECT& OUT rect);
		LONG				GetPos();
		LONG				NeedDraw();
		CTAFrame*			GetFrame();

		VOID				SetTips(LPCSTR IN pTips);
		LPCSTR				GetTips(){return m_pTips;}


	public:

		CTAAnchor*			GetPrev(){return m_pPrevLink;}
		CTAAnchor*			GetNext(){return m_pNextLink;}
		VOID				SetPrev(CTAAnchor* IN pPrev,BOOL IN bResetOld=TRUE);
		VOID				SetNext(CTAAnchor* IN pNext,BOOL IN bResetOld=TRUE);

	public:
		virtual VOID		SetTime(DWORD IN dwTime);
		virtual DWORD		GetTime(){return m_dwTime;}
		virtual VOID		SetEndTime(DWORD IN dwTime){m_dwEndTime=dwTime;Invalidate(TRUE);}
		virtual DWORD		GetEndTime(){return m_dwEndTime;}
		
		virtual BOOL		IsShowTimeRange(){return m_bShowTimeRange;}
		virtual VOID		ShowTimeRange(BOOL IN bShow){m_bShowTimeRange=bShow;Invalidate(TRUE);}

		virtual	VOID		OnDraw(HDC IN hDC);
		virtual BOOL		PreTranslateMessage(MSG* IN pMsg);

	protected:
		BOOL				ProcessSelected(RECT* IN pRect,POINT IN pt);
		BOOL				ProcessStartDrag(RECT* IN pRect,POINT IN pt);
		BOOL				ProcessDrag(POINT IN pt);
		BOOL				ProcessEndDrag(POINT IN pt);
		VOID				UpdateTips();
		VOID				DrawTimeRange(HDC IN hDC,LONG IN lNeedDraw);


	};
	class TA_EXPORT CTAScrollBar:public CTAObject
	{
	protected:
		POINT			m_Pos;
		LONG			m_lLength;
		LONG			m_lWidth;

		LONG			m_lMaxCount;
		LONG			m_lPageCount;

		LONG			m_lScrollPos;

		RECT			m_BarRect;
		RECT			m_ScrollBarRect;
		LONG			m_lBarSize;
		BOOL			m_bHaveBackBar;
	private:
		BOOL			m_bDraging;
		POINT			m_DragStartPoint;
		POINT			m_DragOffset;


	public:
		CTAScrollBar(CTATime*pTime,CTAStyle*pStyle);
		virtual ~CTAScrollBar();
	public:
		VOID			SetPos(LONG IN x,LONG IN y);

		VOID			SetLength(LONG IN length);
		LONG			GetLength(){return m_lLength;}
		VOID			SetWidth(LONG IN width);
		LONG			GetWidth(){return m_lWidth;}

	
		VOID			SetMaxCount(LONG IN lCount);
		LONG			GetMaxCount(){return m_lMaxCount;}

		VOID			SetPerPageCount(LONG IN lCount);
		LONG			GetPerPageCount(){return m_lPageCount;}

		LONG			GetScrollPos();
		VOID			SetScrollPos(LONG IN lPos);

		RECT&			GetBarRect(){return m_BarRect;}
		VOID			Update();

	public:
		VOID			OnDraw(HDC IN hDC);
		BOOL			PreTranslateMsg(MSG* IN pMsg);
	protected:
		BOOL			OnStartDrag(POINT IN pt);
		BOOL			OnEndDrag(POINT IN pt);
		BOOL			OnProcessDrag(POINT IN pt);

	};
	//--------------------------------------------------------

	class TA_EXPORT CTAFrame:public CTAObjectList
	{
	protected:

		POINT			m_Pos;
		SIZE			m_Size;
		HDC				m_hPaintDC;
		HDC				m_hCanvasDC;
		HBITMAP			m_hCanvas;
		BOOL			m_bNeedResetCanvas;
	protected:
		BOOL			m_bSetTextColor;
		COLORREF		m_TextColor;
	protected:
		BOOL			m_bExpand;		//是否展开
		BOOL			m_bActived;		//是否激活

		CTAObjectList*	m_pAnchorList;

		BOOL			m_bEnable;
		RECT			m_rectRoot;

	public:
		CTAFrame(CTATime*pTime,CTAStyle*pStyle);
		virtual ~CTAFrame();
	public:
		VOID				SetPos(LONG IN x,LONG IN y);
		VOID				SetSize(LONG IN cx,LONG IN cy);
		POINT				GetPos(){return m_Pos;}
		SIZE				GetSize(){return m_Size;}
		VOID				SetNameTextColor(COLORREF IN clr);
		COLORREF			GetNameTextColor();

		LONG				GetFramesCount();

		VOID				EnsureVisible();
		BOOL				IsExpand(){return m_bExpand;}
		VOID				Expand(BOOL IN bExpand);

		BOOL				IsActived(){return m_bActived;}
		VOID				Active(BOOL IN bActive);

		BOOL				IsEnable(){return m_bEnable;}
		VOID				Enable(BOOL IN bEnable);

	public:
		BOOL				PointSelected(POINT IN pt);
		BOOL				ProcessClickedExpandButton(POINT IN pt);

	public:
		CTAFrame*			AddFrame(TAOST_TYPE IN type,LPCSTR IN pFrameName,LPCSTR IN pFrameDesc,UINT_PTR IN UserData=0);
		BOOL				DelFrame(CTAFrame* IN pFrame);
		BOOL				DelFrame(LPCSTR IN pFrameName);
		CTAFrame*			FindFrame(LPCSTR IN pFrameName);
		VOID				ClearFrame();
		BOOL				GetFrameSequence(CTAFrame* IN pFrame,LONG& lSequence);

	public:
		CTAAnchor*			AddAnchor(DWORD IN dwTime,TAOST_TYPE IN type,COLORREF IN clr,UINT_PTR IN UserData=0);
		CTAAnchor*			AddAnchor(DWORD IN dwTime,UINT IN uResourceID,UINT_PTR IN UserData=0);
		VOID				AddAnchor(CTAAnchor* IN pNewAnchor);
		BOOL				DelAnchor(CTAAnchor* IN pAnchor);
		VOID				ClearAnchor();
		LONG				GetAnchorCount();
		CTAAnchor*			GetAnchor(LONG IN lIndex);

	public:
		virtual	VOID		OnDraw(HDC IN hDC,INT IN iStartRows,INT IN iMaxRows,INT& IN OUT iRowIndex,CTAObjectList* IN pDrawFrameList);
		virtual BOOL		PreTranslateMessage(MSG* IN pMsg);
	protected:
		VOID				Draw(INT IN iRowIndex);
		VOID				DrawChild(INT IN iStartRows,INT IN iMaxRows,INT& IN OUT iRowIndex,CTAObjectList* IN pDrawFrameList);
		VOID				DrawAnchors();

		VOID				DrawRootLine();
		VOID				ResetCanvas();
	protected:
		BOOL				SelectProcess(POINT IN pt);
		BOOL				ExpandProcess(POINT IN pt);

	};

	//--------------------------------------------------------
	//--------------------------------------------------------
	



	//--------------------------------------------------------
	class TA_EXPORT CTimeAxis
	{
	protected:
		HWND				m_hWnd;
		HDC					m_hPaintDC;
		HBITMAP				m_hCanvas;
		HDC					m_hCanvasDC;
		SIZE				m_Size;
		POINT				m_Pos;
		BOOL				m_bRedraw;
	protected:
		CTATime*			m_pTime;
		CTAStyle*			m_pStyle;
	protected:
		CTAObjectList*		m_pFrameList;		//
		CTAObjectList*		m_pDrawFrameList;
		
		INT					m_iFirstFrameIndex;
		CTAFrame*			m_pActiveFrame;
		CTAAnchor*			m_pActiveAnchor;

	protected:
		CTATips*			m_pTips;
		CTAScrollBar*		m_pScrollbar;

	private:
		BOOL				m_bDragingSplitter;
		BOOL				m_bDragingTimeLine;
		BOOL				m_bDragingTitle;

		POINT				m_DragPoint;
		POINT				m_DragCurPoint;
		LONG				m_lDragStartTime;


	public:
		CTimeAxis();
		~CTimeAxis();
	public:
		BOOL			Create(HWND IN hWnd,LONG IN cx,LONG IN cy,CTAStyle* IN style=NULL);
		VOID			SetSize(LONG IN cx,LONG IN cy,BOOL IN bDraw=TRUE);
		VOID			SetPos(LONG IN x,LONG IN y,BOOL IN bDraw=TRUE);
		SIZE			GetSize(){return m_Size;}
		POINT			GetPos(){return m_Pos;}
		VOID			Draw(BOOL IN bRedraw = FALSE);
		VOID			Redraw();
		VOID			Invalidate(BOOL bRedraw=FALSE,BOOL IN bInvalidateAllChild=FALSE);
		HWND			GetWnd(){return m_hWnd;}
		
		BOOL			SetCurTime(DWORD IN dwTime);
		VOID			SetEndTime(DWORD IN dwTime);		
		DWORD			GetEndTime();

		BOOL			StepTime(DWORD IN dwIntervalTime);

		VOID			ShowTips(LPCSTR IN pText,LONG IN x,LONG IN y);
		VOID			HideTips();

		VOID			SetStyle(CTAStyle* IN pStyle);

	public:
		BOOL			PreTranslateMessage(MSG* IN pMsg);
	public:
		CTATime*		GetTime(){return m_pTime;}
	public:
		CTAFrame*		AddFrame(TAOST_TYPE IN type,LPCSTR IN pFrameName,LPCSTR IN pFrameDesc,UINT_PTR IN UserData=0);
		BOOL			DelFrame(CTAFrame* IN pFrame);
		BOOL			DelFrame(LPCSTR IN pFrameName);
		CTAFrame*		FindFrame(LPCSTR IN pFrameName);
		VOID			ClearFrame();
		BOOL			GetFrameSequence(CTAFrame* IN pFrame,LONG& lSequence);
		VOID			EnsureFrameVisible(CTAFrame* IN pFrame);


		CTAFrame*		GetActiveFrame(){return m_pActiveFrame;}
		VOID			SetActiveFrame(CTAFrame* IN pFrame);

		CTAAnchor*		GetActiveAnchor(){return m_pActiveAnchor;}
		VOID			SetActiveAnchor(CTAAnchor* IN pAnchor);
		VOID			SetScrollPos(LONG IN lPos);
		LONG			GetScrollPos();

		LONG			GetEnableDrawFramesCount();
		INT				GetMaxFrameRows();
		LONG			GetFramesCount();
		VOID			UpdateScrollBar();

	protected:
		VOID			ResetCanvas(LONG IN cx,LONG IN cy);
		VOID			DrawDragLine();
		VOID			DrawCoordinate();
		VOID			DrawTimeLine();
		VOID			DrawFrames();
	protected:
		BOOL			OnMouseOverSplitter(POINT IN pt);
		BOOL			OnMouseOverTimeLine(POINT IN pt);
		BOOL			OnProcessDragSplitter(POINT IN pt);
		BOOL			OnStartDragSplitter(POINT IN pt);
		BOOL			OnEndDragSplitter(POINT IN pt);
		BOOL			OnProcessDragTimeLine(POINT IN pt);
		BOOL			OnStartDragTimeLine(POINT IN pt);
		BOOL			OnEndDragTimeLine(POINT IN pt);
		BOOL			OnProcessDragTitle(POINT IN pt);
		BOOL			OnStartDragTitle(POINT IN pt);
		BOOL			OnEndDragTitle(POINT IN pt);
		BOOL			OnLocateTimeLine(POINT IN pt);
		BOOL			OnProcessZoomTitle(POINT IN pt,WORD IN wKey,LONG IN lZDelta);
		BOOL			OnProcessScrollFrames(POINT IN pt,WORD IN wKey,LONG IN lZDelta);
		BOOL			OnProcessDeleteAnchor(DWORD IN dwKey);

		BOOL			FramePretranslateMsg(MSG* IN pMsg);
	};
	//--------------------------------------------------------

};

#ifndef _TimeAxis_DLL
using namespace TimeAxis;
#endif
