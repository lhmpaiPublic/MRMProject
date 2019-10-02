
#ifndef __GASOUND_B7A15A9D01DC403996FC45F7F92F52D3_H__
#define __GASOUND_B7A15A9D01DC403996FC45F7F92F52D3_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define  _GASOUND  GASound
class GASound
{
public:
	//������
	GASound(void);
	//�Ҹ���
	~GASound(void);
	//======================================
	//���� ���� ����
	//=======================================
// 	If you want to sound volume in percents instead of number between 0 and 0xFFFF then you can use the following code for that:
// 	DWORD dwSoundVolumePercents = 50;
// 	SetSoundVolume( (DWORD)(0xFFFF*1.0*dwSoundVolumePercents/100.0) );
	static void SetSoundVolume(DWORD dwVolume);
	//===========================================
	// ���� �÷���
	//============================================
	static void SoundPlay(CString _wave);
};
#endif// __GASOUND_B7A15A9D01DC403996FC45F7F92F52D3_H__
