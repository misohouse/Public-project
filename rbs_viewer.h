
// rbs_viewer.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// Crbs_viewerApp:
// �� Ŭ������ ������ ���ؼ��� rbs_viewer.cpp�� �����Ͻʽÿ�.
//

class Crbs_viewerApp : public CWinApp
{
public:
	Crbs_viewerApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern Crbs_viewerApp theApp;