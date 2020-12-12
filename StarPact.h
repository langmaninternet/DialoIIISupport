#ifndef QBT_STARPACT_HEADER
#define QBT_STARPACT_HEADER
#include <Windows.h>




/************************************************************************/
/* Win32GDI                                                             */
/************************************************************************/
class Win32GDI
{
protected:
private:
	HBITMAP		hBitmap;
	HDC			hMemDC;
	RECT		rectDesktop;
public:
	/*Constructor*/		Win32GDI();
	void				CaptureDesktop(void);
	int					GetPixel(int x, int y);
	bool				ValidMode(void);
	bool				D3IsViewMap(void);
	bool				D3IsOpenSkillTable(void);
	bool				D3IsOpenKadala(void);
	bool				D3IsOpenUrshi(void);
	bool				D3IsOpenStash(void);
	bool				D3Skill01IsLightningBlastReady(void);
	bool				D3Skill01IsShadowPowerAndReady(void);
	bool				D3Skill02IsArchonSlowTimeAndReady(void);
	bool				D3Skill02IsShadowPowerAndReady(void);
	bool				D3Skill03IsShadowPowerAndReady(void);
	bool				D3Skill03IsEpiphanyAndReady(void);
	bool				D3Skill04IsShadowPowerAndReady(void);
	bool				D3Skill04IsVegeanceAndReady(void);
	bool				D3Skill04IsSweepingWindReady(void);
	bool				D3Skill01KeyIs1(void);
	bool				D3Skill03KeyIs2(void);
	bool				D3Skill03KeyIs3(void);
	bool				D3Skill04KeyIs4(void);
	bool				D3Skill01KeyIsQ(void);
	bool				D3Skill02KeyIsW(void);
	bool				D3Skill03KeyIsE(void);
	bool				D3Skill04KeyIsR(void);
	/*Desstructor*/		~Win32GDI();
};


/************************************************************************/
/* StarPact Engine                                                      */
/************************************************************************/
void		ArchonStarPactSCycle(const wchar_t blackHoleKey, wchar_t wayOfForceKey, wchar_t meteorKey, wchar_t archonKey, wchar_t primaryKey, wchar_t secondaryKey, wchar_t forceStandKey);

void		ArchonStarPactFullCycle(const wchar_t blackHoleKey, wchar_t wayOfForceKey, wchar_t meteorKey, wchar_t archonKey, wchar_t primaryKey, wchar_t secondaryKey, wchar_t forceStandKey);
void		StartStarPact(void);
void		StopStarPact(void);
void		StarPactDumpData(void);



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct DiabloIIIStatusStruct
{
	bool	flagInAttackMode;
	bool	flagPotionReady;
	bool	flagIsOpenMap;
	bool	flagIsOpenSkillTable;
	bool	flagIsOpenKadala;
	bool	flagIsOpenUrshi;
	bool	flagIsOpenStash;
	bool	flagIsWizard;
	bool	flagIsDemonHunter;
	bool	flagIsMonk;
	bool	flagInArchonMode;
	bool	flagSkill01IsReadyToAndNeedAutoPress;
	bool	flagSkill02IsReadyToAndNeedAutoPress;
	bool	flagSkill03IsReadyToAndNeedAutoPress;
	bool	flagSkill04IsReadyToAndNeedAutoPress;
	int		skill01Key;
	int		skill02Key;
	int		skill03Key;
	int		skill04Key;
	int		healingKey;

#ifdef _DEBUG
	int		getStatusTime;
#endif
};
extern		DiabloIIIStatusStruct d3GameStatus;
void		GetCurrentDiabloIIStatus(void);
void		PreloadSalvageItem(int *preloadSalvageSlot, int preloadSalvageSlotSize);


/************************************************************************/
/*                                                                      */
/************************************************************************/

void					CreateOverlay(void);
void					DestroyOverlay(void);
#endif