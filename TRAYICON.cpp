//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
HINSTANCE g_hinst;
//---------------------------------------------------------------------------
USEFORM("traymain.cpp", FormMain);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE hInstance, LPSTR, int)
{
    Application->Initialize();
    g_hinst = hInstance;
    Application->CreateForm(__classid(TFormMain), &FormMain);
                 Application->Run();
    return 0;
}
//---------------------------------------------------------------------------

