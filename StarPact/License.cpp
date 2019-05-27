#include "stdafx.h"
#include <Windows.h>
#include <Wingdi.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <list>
#include "StarPact.h"
extern bool					flagValidateStarPact;

static const int			realLicenseLength = 5;
static const int			randomLicenseLength = 0;

static wchar_t				deviceID[100] = { 0 };
static wchar_t				licPath[3000] = { 0 };
static wchar_t				licOldPath[3000] = { 0 };
static const int			licStringSize = 100;
static wchar_t				licString[licStringSize / sizeof(wchar_t) + 10] = { 0 };

/************************************************************************/
/* Public - License                                                     */
/************************************************************************/
static bool		ValidateLicenseString(const wchar_t * licenseID)
{
	if (licenseID)
	{
		if (deviceID[0] == NULL)
		{
			void GenDeviceIdentification(wchar_t * bufferDeviceID, int bufferDeviceIDSize);
			GenDeviceIdentification(deviceID, 99);
		}
		for (int iChar = 0; iChar < realLicenseLength; iChar++)
		{
			if (licenseID[iChar] != 'A' + (('Z' - deviceID[iChar]) % 10)) return false;
		}
		flagValidateStarPact = true;
		return true;
	}
	return false;
}
void			GenLicenseString(const wchar_t * deviceID, wchar_t * bufferLicenseID, int bufferLicenseSize)
{
	if (deviceID != NULL && bufferLicenseID != NULL && bufferLicenseSize > 0)
	{
		for (int iChar = 0; iChar < bufferLicenseSize && deviceID[iChar] != NULL && iChar < realLicenseLength; iChar++)
		{
			if (deviceID[iChar] >= 'A' && deviceID[iChar] <= 'Z')
			{
				bufferLicenseID[iChar] = 'A' + (('Z' - deviceID[iChar]) % 10);
				bufferLicenseID[iChar + 1] = 0;
			}

		}
		for (int iChar = realLicenseLength; iChar < bufferLicenseSize && iChar < realLicenseLength + randomLicenseLength; iChar++)
		{
			bufferLicenseID[iChar] = 'A' + rand() % 26;
			bufferLicenseID[iChar + 1] = 0;
		}
	}
}
void			GenDeviceIdentification(wchar_t * bufferDeviceID, int bufferDeviceIDSize)
{
	if (bufferDeviceID && bufferDeviceIDSize > 0)
	{
		const int nHardDiskIdent = 0;
		srand((unsigned int)time((time_t*)NULL));
		for (int iChar = 0; iChar < bufferDeviceIDSize && iChar < realLicenseLength; iChar++)
		{
			bufferDeviceID[iChar] = 'Q';
			bufferDeviceID[iChar + 1] = 0;
		}
		for (int iChar = realLicenseLength; iChar < bufferDeviceIDSize && iChar < realLicenseLength + randomLicenseLength; iChar++)
		{
			bufferDeviceID[iChar] = 'A' + rand() % 26;
			bufferDeviceID[iChar + 1] = 0;
		}


		// Format physical drive path (may be '\\.\PhysicalDrive0', '\\.\PhysicalDrive1' and so on).
		wchar_t bufferstrDrivePath[1000] = { 0 };
		swprintf_s(bufferstrDrivePath, L"\\\\.\\PhysicalDrive%d", nHardDiskIdent);

		// call CreateFile to get a handle to physical drive
		HANDLE hDevice = ::CreateFileW(bufferstrDrivePath, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
		if (hDevice != INVALID_HANDLE_VALUE)
		{
			// set the input STORAGE_PROPERTY_QUERY data structure
			STORAGE_PROPERTY_QUERY storagePropertyQuery;
			ZeroMemory(&storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY));
			storagePropertyQuery.PropertyId = StorageDeviceProperty;
			storagePropertyQuery.QueryType = PropertyStandardQuery;

			// get the necessary output buffer size
			STORAGE_DESCRIPTOR_HEADER storageDescriptorHeader = { 0 };
			DWORD dwBytesReturned = 0;
			if (::DeviceIoControl(hDevice, IOCTL_STORAGE_QUERY_PROPERTY, &storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY), &storageDescriptorHeader, sizeof(STORAGE_DESCRIPTOR_HEADER), &dwBytesReturned, NULL))
			{
				// allocate the necessary memory for the output buffer
				BYTE* pOutBuffer = (BYTE*)calloc(storageDescriptorHeader.Size + 10/*safe*/, sizeof(BYTE));
				if (pOutBuffer)
				{
					// get the storage device descriptor
					if (::DeviceIoControl(hDevice, IOCTL_STORAGE_QUERY_PROPERTY, &storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY), pOutBuffer, storageDescriptorHeader.Size, &dwBytesReturned, NULL))
					{
						// Now, the output buffer points to a STORAGE_DEVICE_DESCRIPTOR structure
						// followed by additional info like vendor ID, product ID, serial number, and so on.
						STORAGE_DEVICE_DESCRIPTOR* pDeviceDescriptor = (STORAGE_DEVICE_DESCRIPTOR*)pOutBuffer;
						if (pDeviceDescriptor->SerialNumberOffset != 0)
						{
							// finally, get the serial number
							for (int iChar = 0, bufferIndex = 0; iChar < bufferDeviceIDSize && bufferIndex < realLicenseLength && (pOutBuffer + pDeviceDescriptor->SerialNumberOffset)[iChar] != NULL; iChar++)
							{
								wchar_t wch = (pOutBuffer + pDeviceDescriptor->SerialNumberOffset)[iChar];
								if (wch >= '0' && wch <= '9') wch = 'A' + wch - '0';
								if (wch >= 'a' && wch <= 'z') wch = 'A' + wch - 'a';
								if (wch >= 'A' && wch <= 'Z') bufferDeviceID[bufferIndex++] = wch;
							}
						}
					}
					free(pOutBuffer);
				}
			}
			::CloseHandle(hDevice);
		}
	}
}
bool			InitStarPactEngine(const wchar_t * licenseID)
{
#ifndef _DEBUG
	if (IsDebuggerPresent())
	{
		exit(EXIT_SUCCESS);
	}
#endif
	/************************************************************************/
	/* Init                                                                 */
	/************************************************************************/
	if (flagValidateStarPact == false && licPath[0] == 0)
	{
		wchar_t appdataPath[2000] = { 0 };
		GetEnvironmentVariable(L"AppData", appdataPath, 1999);
		wchar_t bufferDir[2000] = { 0 };
		swprintf_s(bufferDir, L"%ls\\DiabloIIISupport\\", appdataPath);
		CreateDirectoryW(bufferDir, 0);
		swprintf_s(licPath, L"%ls\\DiabloIIISupport\\DiabloIIISupport.lic", appdataPath);

		std::ifstream fileInputStream(licPath, std::ifstream::in | std::ifstream::binary);
		if (fileInputStream.is_open())
		{
			fileInputStream.seekg(0, std::ios_base::end);
			int fileSize = int(fileInputStream.tellg());
			fileInputStream.seekg(0, std::ios_base::beg);
			if (fileSize > licStringSize) fileSize = licStringSize;
			fileInputStream.read((char*)licString, fileSize);
			fileInputStream.close();
		}
		ValidateLicenseString(licString);
	}
	if (flagValidateStarPact == false && licOldPath[0] == 0)
	{
		wchar_t appdataPath[2000] = { 0 };
		GetEnvironmentVariable(L"AppData", appdataPath, 1999);
		wchar_t bufferDir[2000] = { 0 };
		swprintf_s(bufferDir, L"%ls\\DialoIIISupport\\", appdataPath);
		CreateDirectoryW(bufferDir, 0);
		swprintf_s(licOldPath, L"%ls\\DialoIIISupport\\DialoIIISupport.lic", appdataPath);

		std::ifstream fileInputStream(licOldPath, std::ifstream::in | std::ifstream::binary);
		if (fileInputStream.is_open())
		{
			fileInputStream.seekg(0, std::ios_base::end);
			int fileSize = int(fileInputStream.tellg());
			fileInputStream.seekg(0, std::ios_base::beg);
			if (fileSize > licStringSize) fileSize = licStringSize;
			fileInputStream.read((char*)licString, fileSize);
			fileInputStream.close();
		}
		ValidateLicenseString(licString);
	}
	if (flagValidateStarPact == false && licenseID != NULL && licenseID[0] != NULL)
	{
		ValidateLicenseString(licenseID);
		if (flagValidateStarPact && licPath[0] != 0)
		{
			wcscpy_s(licString, licenseID);
			std::ofstream fileHandle(licPath, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
			if (fileHandle.is_open())
			{
				fileHandle.write((char*)licString, licStringSize);
				fileHandle.close();
			}
		}
	}
	return flagValidateStarPact;
}