
// rbs_viewerDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include <iostream>
#include <windows.h>
#include <io.h>
#include <fstream>
#include <..\include\LibZ\zlib.h>
#include "json\reader.h"
#include "json\json.h"
#include "afxcmn.h"
#include <locale.h>

#pragma warning(disable : 4996)  


// Crbs_viewerDlg 대화 상자
class Crbs_viewerDlg : public CDialogEx
{
// 생성입니다.
public:
	Crbs_viewerDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RBS_VIEWER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	int  m_SortedColumn;
	BOOL m_Ascending;
	BOOL bDoColoring = FALSE;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit ed_folder_path_var;
	afx_msg void OnBnClickedselectpath();
	afx_msg void OnBnClickedextrct();
	CTreeCtrl hw_os_info_var;
	CListCtrl list_prog_info_var;
	static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParam);
//	afx_msg void OnLvnColumnclickproginfo(NMHDR *pNMHDR, LRESULT *pResult);
	void UpdateArrow(void);
	CListCtrl list_process_info_var;
	afx_msg void OnLvnColumnclickprocessinfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawproginfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedcsv();
	afx_msg void OnLvnColumnclickproginfo(NMHDR *pNMHDR, LRESULT *pResult);
};
