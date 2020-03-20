#include "mfc.h"
MyApp app;
BOOL MyApp::InitInstance()
{
	// 创建窗口
	MyFrame* frame = new MyFrame();
	frame->ShowWindow(SW_SHOWNORMAL);
	frame->UpdateWindow();
	m_pMainWnd = frame;
	return TRUE;
}

BEGIN_MESSAGE_MAP(MyFrame, CFrameWnd)
	ON_WM_LBUTTONDOWN()//鼠标左键按下
	END_MESSAGE_MAP()
MyFrame::MyFrame()
{
	Create(NULL, TEXT("MFC"));
}

void MyFrame::OnLButtonDown(UINT, CPoint point)
{
	CString str;
	str.Format(TEXT("x=%d,,, y=%d"), point.x, point.y);
	MessageBox(str);
}
