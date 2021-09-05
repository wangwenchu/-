// Copyright 2021 Tencent Inc.  All rights reserved.

#pragma once
#include <windows.h>
#include <wlanapi.h>
#include <objbase.h>
#include <wtypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <atlstr.h>
#include <vector>
#include <algorithm>
#pragma comment(lib, "wlanapi.lib")
#pragma comment(lib, "ole32.lib")

namespace SDK_HELPER {
	struct WIFI_SSID_MAC_INFO {
		CAtlString wifiname;
		CAtlString wifimac;
	};

	struct BssidQulity {
		int qulity;
		CAtlString bssid;
	};

	void GetWifiInfo(WIFI_SSID_MAC_INFO& wifiref) {
		static WIFI_SSID_MAC_INFO wifi_info;
		if (!wifi_info.wifiname.IsEmpty() && !wifi_info.wifimac.IsEmpty()) {
			wifiref = wifi_info;
			return;
		}
		BssidQulity tmp;
		std::vector<BssidQulity>bssiditems;

		PWLAN_INTERFACE_INFO_LIST pIfList = NULL;
		PWLAN_INTERFACE_INFO pIfInfo = NULL;
		PWLAN_AVAILABLE_NETWORK_LIST pBssList = NULL;
		PWLAN_AVAILABLE_NETWORK pBssEntry = NULL;
		HANDLE hClient = NULL;
		DWORD dwMaxClient = 2;
		DWORD dwCurVersion = 0;
		DWORD dwResult = 0;
		DWORD dwRetVal = 0;
		dwResult = WlanOpenHandle(dwMaxClient, NULL, &dwCurVersion, &hClient);
		if (dwResult != ERROR_SUCCESS) return;
		dwResult = WlanEnumInterfaces(hClient, NULL, &pIfList);
		if (dwResult != ERROR_SUCCESS) return;
		for (int i = 0; i < (int)pIfList->dwNumberOfItems; i++) {
			pIfInfo = (WLAN_INTERFACE_INFO*)&pIfList->InterfaceInfo[i];
			dwResult = WlanGetAvailableNetworkList(hClient, &pIfInfo->InterfaceGuid, 0,
				NULL, &pBssList);
			if (dwResult != ERROR_SUCCESS) continue;
			for (int j = 0; j < static_cast<int>(pBssList->dwNumberOfItems); j++) {
				pBssEntry = (WLAN_AVAILABLE_NETWORK*)&pBssList->Network[j];
				//printf("%5d\n", pBssEntry->wlanSignalQuality);
				if (pBssEntry->dwFlags & WLAN_AVAILABLE_NETWORK_CONNECTED) {
					CAtlString strName = pBssEntry->strProfileName;
					wifi_info.wifiname = strName;

					PWLAN_BSS_LIST ppWlanBssList;
					dwResult = WlanGetNetworkBssList(
						hClient, &pIfInfo->InterfaceGuid, &pBssEntry->dot11Ssid,
						pBssEntry->dot11BssType, pBssEntry->bSecurityEnabled, NULL,
						&ppWlanBssList);
			
					int itemSize = static_cast<int>(ppWlanBssList->dwNumberOfItems);
					for (int k = 0; k < itemSize; k++) {
						WLAN_BSS_ENTRY bssEntry = ppWlanBssList->wlanBssEntries[k];
						CString strBssid;
						strBssid.Format(_T("%02x:%02x:%02x:%02x:%02x:%02x"),
							bssEntry.dot11Bssid[0], bssEntry.dot11Bssid[1],
							bssEntry.dot11Bssid[2], bssEntry.dot11Bssid[3],
							bssEntry.dot11Bssid[4], bssEntry.dot11Bssid[5]);
						tmp.qulity = static_cast<int>(bssEntry.uLinkQuality);
						tmp.bssid = strBssid;
						bssiditems.push_back(tmp);
					}
				}
			}
		}
		sort(bssiditems.begin(), bssiditems.end(), [&](const BssidQulity& x, const BssidQulity& y) {
			return x.qulity > y.qulity; });
		int bssidSize = static_cast<int>(bssiditems.size());
	
		for (int i = 0; i < bssidSize; ++i) {
			wifi_info.wifimac += bssiditems[i].bssid;
			//std::wcout << bssiditems[i].bssid.GetString() << " " << bssiditems[i].qulity <<  std::endl;
			if (i != bssidSize - 1) {
				wifi_info.wifimac += ";";
			}
		}
		wifiref = wifi_info;
	}

	WIFI_SSID_MAC_INFO WifiInfohelper() {
		static WIFI_SSID_MAC_INFO strwifi;
		if (strwifi.wifiname.IsEmpty() && strwifi.wifimac.IsEmpty()) {
			GetWifiInfo(strwifi);
		}
		return strwifi;
	}

	static CAtlString GetWifiName() {
		static CAtlString strwifiname;
		if (strwifiname.IsEmpty()) {
			WIFI_SSID_MAC_INFO strwifi_name_mac = WifiInfohelper();
			strwifiname = strwifi_name_mac.wifiname;
		}
		return  strwifiname;
	}

	static CAtlString GetWifiMac() {
		static CAtlString strwifimac;
		if (strwifimac.IsEmpty()) {
			WIFI_SSID_MAC_INFO strwifi_name_mac = WifiInfohelper();
			strwifimac = strwifi_name_mac.wifimac;
		}
		return strwifimac;
	}
};
