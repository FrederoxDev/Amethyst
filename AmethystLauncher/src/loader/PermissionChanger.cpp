#include "PermissionChanger.h"
#include "Loader.h"
#include <Windows.h>
#include <aclapi.h>

std::wstring stringToWstring(const std::string& s)
{
    std::wstring temp(s.length(), L' ');
    std::copy(s.begin(), s.end(), temp.begin());
    return temp;
}

#include <iostream>
#include <sddl.h>
#include <string>
#include <windows.h>

bool AddALLToDirectoryPermissions()
{
    // Get the path to the amethyst folder
    auto stringPath = GetAmethystPath();
    std::wstring amethystPath(stringPath.begin(), stringPath.end()); // Assuming GetAmethystUWPFolder() returns a wide string

    LPCWSTR path = amethystPath.c_str();
    SECURITY_INFORMATION securityInfo = DACL_SECURITY_INFORMATION;
    PSECURITY_DESCRIPTOR securityDescriptor = nullptr;
    DWORD dwRes;
    PACL pOldDACL = nullptr, pNewDACL = nullptr;
    EXPLICIT_ACCESSW ea;
    PSID pAllAppPackagesSID = nullptr;

    // Create a SID for the "ALL APPLICATION PACKAGES" group.
    if (!ConvertStringSidToSidW(L"S-1-15-2-1", &pAllAppPackagesSID)) { // SID for "ALL APPLICATION PACKAGES"
        ReportIssue(L"ConvertStringSidToSid Error");
        return false;
    }

    // Initialize an EXPLICIT_ACCESSW structure for the new ACE.
    ZeroMemory(&ea, sizeof(EXPLICIT_ACCESSW));
    ea.grfAccessPermissions = GENERIC_ALL;
    ea.grfAccessMode = SET_ACCESS;
    ea.grfInheritance = CONTAINER_INHERIT_ACE | OBJECT_INHERIT_ACE;
    ea.Trustee.TrusteeForm = TRUSTEE_IS_SID;
    ea.Trustee.TrusteeType = TRUSTEE_IS_GROUP;
    ea.Trustee.ptstrName = (LPWSTR)pAllAppPackagesSID;

    // Get the DACL.
    dwRes = GetNamedSecurityInfoW(path, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, nullptr, nullptr, &pOldDACL, nullptr, &securityDescriptor);
    if (ERROR_SUCCESS != dwRes) {
        ReportIssue(L"GetNamedSecurityInfo Error");
        return false;
    }

    // Create a new ACL that merges the new ACE.
    dwRes = SetEntriesInAclW(1, &ea, pOldDACL, &pNewDACL);
    if (ERROR_SUCCESS != dwRes) {
        ReportIssue(L"SetEntriesInAcl Error");
        return false;
    }

    // Set the new DACL.
    dwRes = SetNamedSecurityInfoW((LPWSTR)path, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, nullptr, nullptr, pNewDACL, nullptr);
    if (ERROR_SUCCESS != dwRes) {
        ReportIssue(L"SetNamedSecurityInfo Error");
        return false;
    }

    if (pAllAppPackagesSID)
        LocalFree(pAllAppPackagesSID);
    if (pNewDACL)
        LocalFree(pNewDACL);
    if (securityDescriptor)
        LocalFree(securityDescriptor);

    return true;
}
