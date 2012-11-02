#ifndef COREDEFINITIONS_H
#define COREDEFINITIONS_H

#pragma once
#include <Windows.h>

namespace Zillya
{
	typedef DWORD __stdcall TUnpackingInfoCallBack(DWORD CoreHandle,LPCWSTR FileName,CHAR Status,LPCSTR VirusName);
	typedef TUnpackingInfoCallBack *PUnpackingInfoCallBack;

	typedef DWORD __stdcall TRegInfoCallBack(DWORD CoreHandle,LPCSTR VirusName);
	typedef TRegInfoCallBack *PRegInfoCallBack;

	#pragma pack(1) //��������� ������������ �������� � 1 ����

	typedef struct TCoreUnpackMode
	{
		DWORD MaxArchSize; //������������� ������ ���������������� ����������
		DWORD MaxArchDept; //������������ ������� ���������� ����������
		UINT64 ArchMode; // ����� ������������� ������������� �������
		UINT64 InstMode; // ����� ������������� ������������� �������������
		UINT64 ContMode; // ����� ������������� ������������� �����������
		UINT64 Reserved1;
		UINT64 Reserved2;
		UINT64 Reserved3;
		UINT64 Reserved4;
		UINT64 Flags;  // �������������� ����� 0x00000001 - ���������� ��� ������
	} *PCoreUnpackMode;

	typedef struct TCoreData
	{
		DWORD AVEVers;  //������ ������������� ����
		DWORD AVERecCount;  //���������� ������������ �������
	} *PCoreData;

	typedef struct TCoreResult
	{
		DWORD FilesCount;  //���������� ����������� �������� (� ������ ���������� >1)
		DWORD VirCount;  //���������� ������������ ��� �������
		DWORD InfectionType;  //�������������� �������� ��� ������: 1 - �������, 2 - ��������
		DWORD ActionRes;  //����������� ��� ������ ��������: 0 - �������, 1 - �������, 2 - ��������
		DWORD IsContainer;  //���� ����������� ����������: 0 - ���, 1 - ��
	} *PCoreResult;

	#define CORE_INIT_OPTION_BREAKARCHSCAN	0x00000001 //���������� �������� ������ ��� ����������� ������
	#define CORE_INIT_OPTION_DEBUGMODE		0x00000002 //Debug ����� (������ � ���� �������� ����������)
	#define CORE_INIT_OPTION_LOADSIMPLE		0x00000004 //��������� ����������� ������ ���

	typedef struct TCoreInit_Interface
	{
		LPCWSTR EPath; //���� � ����� ������������� ����
		LPCWSTR VPath; //���� � ����� ������������ ���
		DWORD Options; //�������������� ���������:
		//   0x00000001 - ���������� �������� ������ ��� ����������� ������
		//   0x00000002 - Debug ����� (������ � ���� �������� ����������)
		//	 0x00000004 - ��������� ����������� ������ ���
		PUnpackingInfoCallBack UnpackingCallBack;
		PRegInfoCallBack RegCallBack;
		LPCWSTR LogFPath; // ���� � ����� �� �������
		PCoreData CoreData;
	} *PCoreInit_Interface;

	typedef struct TCoreFScan_Interface
	{
		LPCWSTR FName;  // ��� ����� ��� ��������
		DWORD ToDo;  // ����� ��������� �����: 0 - ������ ����, 1 - �������, 2 - ��������
		DWORD BaseMode;  // ����� ������������� �������� ���
		PCoreUnpackMode UnpackMode;
		//������������ ��������
		LPSTR VName;  // ����� ��� ����� ������ (�� 64 ��������)
		PCoreResult CoreResult; // ��������� �� ������ ������������ ��������
	} *PCoreFScan_Interface;

	typedef struct TCoreOptions_Interface
	{
		DWORD Options; //�������������� ���������:
		LPCSTR LogFPath; // ���� � ����� �� �������
		DWORD R1, R2, R3, R4, R5; // ���������������
	} *PCoreOptions_Interface;

	typedef struct TCoreMScan_interface
	{
		LPCVOID MemPointer;// ��������� �� ������� ������
		DWORD MemSize;  // ������ ������� ������
		DWORD BaseMode;  // ����� ������������� �������� ���
		PCoreUnpackMode UnpackMode;
		//������������ ��������
		LPSTR VName;  // ����� ��� ����� ������ (�� 64 ��������)
		PCoreResult AVEResult;      // ��������� �� ������ ������������ ��������
	} *PCoreMScan_interface;

	typedef struct TCoreRScan_interface
	{
		LPCSTR RegKey;
	} *PCoreRScan_interface;

	#pragma pack()

	typedef DWORD _stdcall TCoreInit(const PCoreInit_Interface params);
	typedef TCoreInit *PCoreInit;

	typedef DWORD _stdcall TCoreInitMerge(const PCoreInit_Interface params);
	typedef TCoreInitMerge *PCoreInitMerge;

	typedef int _stdcall TCoreFScan(DWORD CoreHandle, const PCoreFScan_Interface params);
	typedef TCoreFScan *PCoreFScan;
	// 0 - ������; 1 - ��������������, 2 - ��������������

	typedef DWORD _stdcall TCoreOptions(DWORD CoreHandle, const PCoreOptions_Interface OPTIONS);
	typedef TCoreOptions *PCoreOptions;

	typedef int _stdcall TCoreMScan(DWORD CoreHandle, const PCoreMScan_interface params);
	typedef TCoreMScan *PCoreMScan;
	// 0 - ������; 1 - ��������������, 2 - ��������������

	typedef int _stdcall TCoreRScan(DWORD CoreHandle, const PCoreRScan_interface params);
	typedef TCoreRScan *PCoreRScan;
	// 0 - ������; 1 - ��������������, 2 - ��������������

	typedef int _stdcall TCoreFree(DWORD CoreHandle);
	typedef TCoreFree *PCoreFree;

	typedef DWORD _stdcall TCoreStopScan(DWORD CoreHandle);
	typedef TCoreStopScan *PCoreStopScan;
}

#endif //COREDEFINITIONS_H