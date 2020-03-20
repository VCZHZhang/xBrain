#include <afxwin.h>// mfc м╥нд╪Ч

class MyApp: public CWinApp{
public:
	virtual BOOL InitInstance();

};

class MyFrame : public CFrameWnd
{
public:
	MyFrame();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT, CPoint);
};