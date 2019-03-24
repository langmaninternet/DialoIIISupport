
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
	
	



	DECLARE_MESSAGE_MAP()

public:
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	afx_msg void OnHelp();


	afx_msg void OnTimer(UINT_PTR nIdEvent);
	afx_msg void OnLoadConfig();
	afx_msg void OnSaveConfig();
	afx_msg void OnKillFocusLeftMouseTime();
	afx_msg void OnKillFocusRightMouseTime();
	afx_msg void OnKillFocusSkill01Time();
	afx_msg void OnKillFocusSkill02Time();
	afx_msg void OnKillFocusSkill03Time();
	afx_msg void OnKillFocusSkill04Time();
	afx_msg void OnKillFocusHealingTime();


	afx_msg void OnShowSkillKey(int idW, wchar_t key);
	afx_msg void OnKillFocusSkillKey(int changeID, wchar_t & keySkill);
	afx_msg void OnKillFocusSkillKey01();
	afx_msg void OnKillFocusSkillKey02();
	afx_msg void OnKillFocusSkillKey03();
	afx_msg void OnKillFocusSkillKey04();
	afx_msg void OnKillfocusHealingKey();
	afx_msg void OnKillFocusSpaceKey();
	afx_msg void OnKillFocusForceStandKey();
	afx_msg void OnKillFocusForceMoveKey();
	afx_msg void OnKillFocusMeteorKey();
	afx_msg void OnKillFocusArchonKey();


	afx_msg void OnClickedSkill01Check();
	afx_msg void OnClickedSkill02Check();
	afx_msg void OnClickedSkill03Check();
	afx_msg void OnClickedSkill04Check();
	afx_msg void OnClickedHealingCheck();
	afx_msg void OnClickedSpaceCheck();

	afx_msg void OnKillFocusProfileName();
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




	afx_msg void OnBnClickedWizArchoncheck();
	afx_msg void OnBnClickedWizFireBridCheck();





};
