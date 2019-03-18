
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
	afx_msg void OnKillfocusProfilename();
	afx_msg void OnBnClickedProfile();
	afx_msg void OnBnClickedProfile01();
	afx_msg void OnBnClickedProfile02();
	afx_msg void OnBnClickedProfile03();
	afx_msg void OnBnClickedProfile04();
	afx_msg void OnBnClickedProfile05();
	afx_msg void OnBnClickedProfile06();
	afx_msg void OnBnClickedProfile07();
	afx_msg void OnBnClickedProfile08();
	afx_msg void OnBnClickedProfile09();
	afx_msg void OnBnClickedProfile10();
	afx_msg void OnKillfocusSkillkey01();
	afx_msg void OnKillfocusSkillkey02();
	afx_msg void OnKillfocusSkillkey03();
	afx_msg void OnKillfocusSkillkey04();
	afx_msg void OnKillfocusHealingkey();
	afx_msg void OnBnClickedHelp();
};
