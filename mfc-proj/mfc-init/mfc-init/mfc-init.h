
// mfc-init.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CmfcinitApp: 
// �йش����ʵ�֣������ mfc-init.cpp
//

class CmfcinitApp : public CWinApp
{
public:
	CmfcinitApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CmfcinitApp theApp;