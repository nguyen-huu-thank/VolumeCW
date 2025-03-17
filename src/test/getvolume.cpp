#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <iostream>

int main() {
    CoInitialize(nullptr);  // Initialize COM library

    IMMDeviceEnumerator* pEnumerator = nullptr;
    IMMDevice* pDevice = nullptr;
    IAudioEndpointVolume* pVolume = nullptr;
    float volume = 0.0f;

    // Get the audio device
    CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL, IID_PPV_ARGS(&pEnumerator));
    if (pEnumerator) {
        pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);
        if (pDevice) {
            pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, nullptr, (void**)&pVolume);
            if (pVolume) {
                pVolume->GetMasterVolumeLevelScalar(&volume);  // Get volume (0.0 - 1.0)
                pVolume->Release();
            }
            pDevice->Release();
        }
        pEnumerator->Release();
    }

    CoUninitialize();
    return volume * 100;  // Convert to percentage (0 - 100)
}