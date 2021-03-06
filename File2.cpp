#pragma hdrstop
#pragma argsused

#ifdef _WIN32
#include <tchar.h>
#else
  typedef char _TCHAR;
  #define _tmain main
#endif

#include <stdio.h>
#include <iostream>
#include <fileapi.h>
#include <windows.h>

int _tmain(int argc, _TCHAR* argv[]) 
{
	BYTE databuf[512];
	NTFS_BootRecord *pNTFS_BootRecord = (NTFS_BootRecord*)databuf;

	HANDLE filehandle = CreateFileW(
	L"\\\\.\\C:",
	GENERIC_READ,
	FILE_SHARE_READ | FILE_SHARE_WRITE,
	NULL,
	OPEN_EXISTING,
	FILE_ATTRIBUTE_NORMAL,
	NULL);

	if (filehandle == INVALID_HANDLE_VALUE) {
		std::cout << "Error: Permission Denied.\n";
		system("pause");
		exit(-1);
	}

	LARGE_INTEGER offset;
	offset.QuadPart = 0;

	unsigned long currentposition = SetFilePointer(
	filehandle,
	offset.LowPart,
	&offset.HighPart,
	FILE_BEGIN);

	if (currentposition != offset.LowPart)
	{
		std::cout << "Offset error.\n";
		system("pause");
		exit(-1);
	}

	DWORD bytestoread = 512;
	DWORD bytesread;

	bool readresult = ReadFile(
	filehandle,
	databuf,
	bytestoread,
	&bytesread,
	NULL);

	if(readresult == false || bytesread != bytestoread)
	{
		std::cout << "Error: The file cannot be read or there is a discrepancy in the number of bytes read.\nTry again. :)\n";
		system("pause");
		exit(-1);
	}

	char *OEM_Name = pNTFS_BootRecord -> OEM_Name;
	USHORT BytesPerSector = pNTFS_BootRecord -> BytesPerSector;
	BYTE SectorsPerCluster = pNTFS_BootRecord -> SectorsPerCluster;
	UINT16 SectorsPerTrack = pNTFS_BootRecord -> SectorsPerTrack;
	UINT16 NumberOfHeads = pNTFS_BootRecord -> NumberOfHeads;
	ULONGLONG TotalSectors = pNTFS_BootRecord -> TotalSectors;
	ULONGLONG MFTClusterNumber = pNTFS_BootRecord -> MFTClusterNumber;
	ULONGLONG CopyMFTClusterNumber = pNTFS_BootRecord -> CopyMFTClusterNumber;
	UINT MFTSize = pNTFS_BootRecord -> MFTSize;
	UINT BufferSize = pNTFS_BootRecord -> BufferSize;
	ULONGLONG VolumeSerialNumber = pNTFS_BootRecord -> VolumeSerialNumber;
	USHORT Checksum = pNTFS_BootRecord -> Checksum;


	int otv;
	std::cout << "NTFS File System info\n";
	std::cout << "The value of the NTFS boot sector fields:\n";
	std::cout << "OEM name: " << OEM_Name;
	std::cout << "\nNumber of bytes per sector: " << BytesPerSector;
	std::cout << "\nNumber of sectors per cluster: " << static_cast<int>(SectorsPerCluster);
	std::cout << "\nNumber of sectors per track: " << SectorsPerTrack;
	std::cout << "\nNumber of heads: " << NumberOfHeads;
	std::cout << "\nThe total number of sectors in the section: " << TotalSectors;
	std::cout << "\nThe cluster number in which the MFT table begins: " << MFTClusterNumber;
	std::cout << "\nThe cluster number in which the copy of the MFT table begins: " << CopyMFTClusterNumber;
	std::cout << "\nMFT record size in clusters: " << MFTSize;
	std::cout << "\nThe disk serial number: " << VolumeSerialNumber;
	std::cout << "\nThe checksum: " << Checksum << "\n";

	system("pause");
	CloseHandle(filehandle);
	return 0;
}
