#include <windows.h>
#include <iostream>
#include <gdiplus.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <Audioclient.h>
#include <conio.h>

//NOTE: none of this is actually my code. Credit goes to Athenian on rohitab.com: http://www.rohitab.com/discuss/topic/43988-increasedecreasemute-the-master-volume-in-windows/
using namespace Gdiplus;

#pragma comment(lib,"gdiplus")
#pragma comment(lib,"Msimg32.lib")

#define SAFE_RELEASE(punk)  \
if ((punk) != NULL)  \
{ (punk)->Release(); (punk) = NULL; }

int main() {
    //FreeConsole();
    //("Volum: ", doubleToString((double)vol), NULL)
    HRESULT hr;
    IMMDeviceEnumerator* pEnumerator = NULL;
    IMMDevice* pDevice = NULL;
    IAudioMeterInformation* pMeterInfo = NULL;
    IAudioEndpointVolume* endpointVolume = NULL;

    CoInitialize(NULL);

    // Get enumerator for audio endpoint devices.
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator),
        NULL, CLSCTX_INPROC_SERVER,
        __uuidof(IMMDeviceEnumerator),
        (void**)&pEnumerator);

    // Get peak meter for default audio-rendering device.
    hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);

    hr = pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, 0, (void**)&endpointVolume);

    endpointVolume->SetMasterVolumeLevelScalar(0, NULL);
	endpointVolume->SetMute(TRUE, NULL);
	
    SAFE_RELEASE(pEnumerator)
    SAFE_RELEASE(pDevice)
    SAFE_RELEASE(pMeterInfo)
    SAFE_RELEASE(endpointVolume)
    CoUninitialize();
}