#ifdef _WIN32
#include <tchar.h>
#endif
#include <windows.h>
#pragma once
#pragma pack(push,1)

 typedef struct
{
	BYTE skip1[3];
	char OEM_Name[8];
	USHORT BytesPerSector;
	BYTE SectorsPerCluster;
	BYTE skip2[10];
	UINT16 SectorsPerTrack;
	UINT16 NumberOfHeads;
	BYTE skip3[12];
	ULONGLONG TotalSectors;
	ULONGLONG MFTClusterNumber;
	ULONGLONG CopyMFTClusterNumber;
	UINT MFTSize;
	UINT BufferSize;
	BYTE skip4[3];
	ULONGLONG VolumeSerialNumber;
	USHORT Checksum;
} NTFS_BootRecord;
# pragma pack(pop)


