#pragma once


class CModellerView : public CView
{
protected: 
	CModellerView();
	DECLARE_DYNCREATE(CModellerView)

public:
	CModellerDoc* GetDocument() const;

public:

public:
	virtual void OnDraw(CDC* pDC);  
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

public:
	virtual ~CModellerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  
inline CModellerDoc* CModellerView::GetDocument() const
   { return reinterpret_cast<CModellerDoc*>(m_pDocument); }
#endif

