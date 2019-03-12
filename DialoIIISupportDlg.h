
// DialoIIISupportDlg.h : header file
//

#pragma once


// CDialoIIISupportDlg dialog
class CDialoIIISupportDlg : public CDialogEx
{
// Construction
public:
	CDialoIIISupportDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOIIISUPPORT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	UINT_PTR myTimerID;
	afx_msg void OnTimer(UINT_PTR nIdEvent);
	



	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnKillfocusLeftmousetime();
	afx_msg void OnKillfocusRightmousetime();
	afx_msg void OnKillfocusSkill01time();
	afx_msg void OnKillfocusSkill02time();
	afx_msg void OnKillfocusSkill03time();
	afx_msg void OnKillfocusSkill04time();
	afx_msg void OnKillfocusHealingtime();
	afx_msg void OnClickedSkill01check();
	afx_msg void OnClickedSkill02check();
	afx_msg void OnClickedSkill03check();
	afx_msg void OnClickedSkill04check();
	afx_msg void OnClickedHealingcheck();
	afx_msg void OnClickedSpacecheck();

	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);

	afx_msg void OnHelp();
};
