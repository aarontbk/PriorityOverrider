// Overrider.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <stdio.h>
#include "..\PriorityOverrider\PriorityOverriderCommon.h"

int Error(const char* message) {
    printf("%s (error=%d)\n", message, GetLastError());
    return 1;
}

int main(int argc, const char* argv[])
{
    if (argc < 3) {
        printf("Usage: Overrider <threadid> <priority>\n");
        return 0;
    }

    HANDLE hDevice = CreateFile(L"\\\\.\\PriorityOverrider", GENERIC_WRITE,
        FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, 0, nullptr);
    if (hDevice == INVALID_HANDLE_VALUE)
        return Error("Failed to open device");

    ThreadData data;
    data.ThreadId = atoi(argv[1]); // command line first argument
    data.Priority = atoi(argv[2]); // command line second argument

    DWORD returned;
	BOOL success = DeviceIoControl(hDevice, IOCTL_PRIORITY_OVERRIDER_SET_PRIORITY,
		&data, sizeof(data), nullptr, 0, &returned, nullptr);
	if (!success)
		return Error("Failed to set priority");
	printf("Priority change succeeded\n");
    CloseHandle(hDevice);
	return 0;
}