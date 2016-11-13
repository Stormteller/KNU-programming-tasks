#include "stdafx.h"
#ifndef SHARED_HANDLERS
#include "Modeller.h"
#endif

#include "ModellerDoc.h"
#include "ModellerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CModellerView

IMPLEMENT_DYNCREATE(CModellerView, CView)

BEGIN_MESSAGE_MAP(CModellerView, CView)
END_MESSAGE_MAP()


CModellerView::CModellerView()
{

}

CModellerView::~CModellerView()
{
}

BOOL CModellerView::PreCreateWindow(CREATESTRUCT& cs)
{

	return CView::PreCreateWindow(cs);
}


void CModellerView::OnDraw(CDC* /*pDC*/)
{
	CModellerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
}



#ifdef _DEBUG
void CModellerView::AssertValid() const
{
	CView::AssertValid();
}

void CModellerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CModellerDoc* CModellerView::GetDocument() const 
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CModellerDoc)));
	return (CModellerDoc*)m_pDocument;
}
#endif //_DEBUG