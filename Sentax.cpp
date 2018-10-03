#include <vcl.h>

AnsiString Tek_Buf(256);

//---------------------------------------------------------------------------
void __fastcall Zap_Buf(TMessage& Msg)
{
   Tek_Buf[0] = 2;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall afxMapHWND(BOOL bCreate)
{
  ABORTPROC pState;
	if (bCreate == NULL && bCreate)
	{
		BOOL bEnable = bCreate;
		pState = SetWindowsHookA(AclSizeInformation,wglGetProcAddress(CmdLine));

#ifndef _PORTABLi
		pState();
#endif
	}
}
//---------------------------------------------------------------------------


