// CriticalProcess.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <stdio.h>
#include <Windows.h>
#include <winternl.h>
#include <conio.h>


#pragma comment(lib,"ntdll.lib")

EXTERN_C NTSTATUS NTAPI RtlAdjustPrivilege(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
EXTERN_C NTSTATUS NTAPI NtSetInformationProcess(HANDLE, ULONG, PVOID, ULONG);

void SetProcessAsCritical() {

	ULONG BreakOnTermination;
	NTSTATUS status;

	BreakOnTermination = 1;

	status = NtSetInformationProcess((HANDLE)-1, 0x1d, &BreakOnTermination, sizeof(ULONG));

	if (status != 0)
	{
		printf("NtSetInformationProcess failed with status %#x\n\n", status);
	}

	else
	{
		printf("Enabled Successfully.\n");
	}
}

void UnSetProcessAsCritical() {

	ULONG BreakOnTermination;
	NTSTATUS status;

	BreakOnTermination = 0;

	status = NtSetInformationProcess((HANDLE)-1, 0x1d, &BreakOnTermination, sizeof(ULONG));

	if (status != 0)
	{
		printf("NtSetInformationProcess failed with status %#x\n", status);
	}

	else
	{
		printf("Canceled Successfully\n");
	}

}

BOOL EnableSeDebugPrivilege() {
	BOOLEAN bl;
	if (!NT_SUCCESS(RtlAdjustPrivilege(20, TRUE, FALSE, &bl)))
	{
		printf("Error enabling SeDebugPrivilege. You have to run this program in an elevated console.");
		return FALSE;
	}
	return TRUE;
}


int main()
{
	if (EnableSeDebugPrivilege())
	{
		SetProcessAsCritical();
	}

	// UnSetProcessAsCritical();

	printf("Press Enter :)))))");

	_getch();

	return 0;
}