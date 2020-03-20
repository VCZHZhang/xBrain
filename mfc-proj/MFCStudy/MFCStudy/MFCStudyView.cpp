
// MFCStudyView.cpp : CMFCStudyView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MFCStudy.h"
#endif

#include "MFCStudyDoc.h"
#include "MFCStudyView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCStudyView

IMPLEMENT_DYNCREATE(CMFCStudyView, CView)

BEGIN_MESSAGE_MAP(CMFCStudyView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCStudyView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCStudyView ����/����

CMFCStudyView::CMFCStudyView()
{
	// TODO:  �ڴ˴���ӹ������

}

CMFCStudyView::~CMFCStudyView()
{
}

BOOL CMFCStudyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMFCStudyView ����

void CMFCStudyView::OnDraw(CDC* /*pDC*/)
{
	CMFCStudyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMFCStudyView ��ӡ


void CMFCStudyView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCStudyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMFCStudyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMFCStudyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}

void CMFCStudyView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCStudyView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCStudyView ���

#ifdef _DEBUG
void CMFCStudyView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCStudyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCStudyDoc* CMFCStudyView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCStudyDoc)));
	return (CMFCStudyDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCStudyView ��Ϣ�������
