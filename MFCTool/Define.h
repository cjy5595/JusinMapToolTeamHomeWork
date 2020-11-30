#pragma once

#define SAFE_DELETE(p) if(p) { delete p; p = nullptr; }

#define WINCX 1280
#define WINCY 720

#ifdef _AFX
#define ERR_MSG(msg) AfxMessageBox(msg)
#else
#define ERR_MSG(msg) MessageBox(nullptr, msg, L"System_Error", MB_OK)
#endif // _AFX

#define TILEX 72
#define TILEY 40

#define TILECX 18
#define TILECY 18