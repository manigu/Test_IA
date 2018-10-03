//---------------------------------------------------------------------------
#include <vcl.h>
#include <shellapi.h>
#include <Winbase.h>
#include <winuser.h>
#include <stdlib.h>
#include <Windows.h>
#pragma hdrstop
#include <stdio.h>
#include <tchar.h>
#include <cstring.h>
#include <conio.h>
#include <iostream.h>
#include "traymain.h"
#include "Sentax.cpp"
#include "Zamena.cpp"

//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TFormMain *FormMain;

HHOOK KeyHook;

LRESULT CALLBACK KeyboardProc(int Code, WPARAM wParam,LPARAM lParam)
{
     UINT uScanCode = MapVirtualKey(wParam,0);
     return 0;
}
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner) : TForm(Owner)
  {
 SetWindowsHookEx(WH_KEYBOARD_LL,(HOOKPROC)&KeyboardProc,GetModuleHandle(NULL),NULL);

 UnhookWindowsHookEx(KeyHook);
  }
//---------------------------------------------------------------------------
void __fastcall TFormMain::DrawItem(TMessage& Msg)
{
     IconDrawItem((LPDRAWITEMSTRUCT)Msg.LParam);
     TForm::Dispatch(&Msg);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MyNotify(TMessage& Msg)
{
    POINT MousePos;

    switch(Msg.LParam)
    {
        case WM_RBUTTONUP:
            if (GetCursorPos(&MousePos))
            {
                PopupMenu1->PopupComponent = FormMain;
                SetForegroundWindow(Handle);
                PopupMenu1->Popup(MousePos.x, MousePos.y);
            }
            else
                Show();
            break;
        case WM_LBUTTONUP:
            ToggleState();
            break;
        default:
            break;
    }
    TForm::Dispatch(&Msg);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormDestroy(TObject *Sender)
{
	TrayMessage(NIM_DELETE);
}
//---------------------------------------------------------------------------
bool __fastcall TFormMain::TrayMessage(DWORD dwMessage)
{
   NOTIFYICONDATA tnd;
   PSTR pszTip;
   PSTR psclip;
   AnsiString Astr_;

          if (RadioButton1->Checked)
           {
            Astr_ = (Edit1->Text.c_str());
            }
       else
           {
            Astr_ = (Edit2->Text.c_str());
            }
            pszTip = Astr_.c_str();

   tnd.cbSize          = sizeof(NOTIFYICONDATA);
   tnd.hWnd            = Handle;
   tnd.uID             = IDC_MYICON;
   tnd.uFlags          = NIF_MESSAGE | NIF_ICON | NIF_TIP;
   tnd.uCallbackMessage	= MYWM_NOTIFY;

   if (dwMessage == NIM_MODIFY)
    {
        tnd.hIcon		= (HICON)IconHandle();

        if (pszTip)
           lstrcpyn(tnd.szTip, pszTip, sizeof(tnd.szTip));
	    else
        tnd.szTip[0] = '\0';
    }
   else
    {
        tnd.hIcon = NULL;
        tnd.szTip[0] = '\0';
    }
   return (Shell_NotifyIcon(dwMessage, &tnd));
}
//---------------------------------------------------------------------------
HICON __fastcall TFormMain::IconHandle(void)
{
    if (RadioButton1->Checked)
        return (Image1->Picture->Icon->Handle);
    else
        return (Image2->Picture->Icon->Handle);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ToggleState(void)
{
    TrayMessage(NIM_MODIFY);
    if (RadioButton1->Checked)
    {
        RadioButton1->Checked = false;
        RadioButton2->Checked = true;
    }
    else
    {
        RadioButton2->Checked = false;
        RadioButton1->Checked = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::CheckBox1Click(TObject *Sender)
{
	if (CheckBox1->Checked)
    {
    	TrayMessage(NIM_ADD);
        TrayMessage(NIM_MODIFY);
    }
	else                    {
    	TrayMessage(NIM_DELETE);
        }

    Button1->Enabled = CheckBox1->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Button1Click(TObject *Sender)
{
    Hide();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::clear_buf(TObject *Sender)
{
    Sender->ClassName();
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::RadioButtonColor()
{
      if (RadioButton1->Checked)
       {
        RadioButton2->Color = clGreen;
        RadioButton1->Color = clLime;
        }
    else
        {
        RadioButton1->Color = clGreen;
        RadioButton2->Color = clLime;
        }  
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::RadioButtonClick(TObject *Sender)
{
       TrayMessage(NIM_MODIFY);

    if (!CheckBox1->Checked)
         return;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::EditKeyUp(TObject *Sender, WORD &Key,
    TShiftState Shift)
{
    if (!CheckBox1->Checked)
        return;

    TrayMessage(NIM_MODIFY);
}
//---------------------------------------------------------------------------
LRESULT IconDrawItem(LPDRAWITEMSTRUCT lpdi)
{
	HICON hIcon;
	hIcon = (HICON)LoadImage(g_hinst, MAKEINTRESOURCE(lpdi->CtlID), IMAGE_ICON,
		16, 16, 0);
	if (!hIcon)
		return(FALSE);

	DrawIconEx(lpdi->hDC, lpdi->rcItem.left, lpdi->rcItem.top, hIcon,
		16, 16, 0, NULL, DI_NORMAL);

	return(TRUE);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Properties1Click(TObject *Sender)
{
 try {
      PropertiFrm(NULL);
      }
catch (EAccessViolation&)
      {
       FormCreate(NULL);
       Visible = true;
       }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Form_invetr(TObject *Sender)
{
       if (RadioButton2->Checked != false)
          {
           DestroyIcon(Sender);
          }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::PropertiFrm(TObject *Sender)
{      
      CheckBox1->Checked = false;
      CheckBox1Click(NULL);
      LPCOLORREF Colorref;
      Colorref[Font->Color] = FormMain->Color;
      if (Image3->Picture->Bitmap != Image4->Picture->Bitmap)
         {
          FormCreate(NULL);
          }
      Show();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ToggleState1Click(TObject *Sender)
{
     ToggleState();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Shutdown1Click(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::WMHotKey(TWMHotKey &Message)
{
  switch (Message.HotKey) {
    case 0:
          {
      if (!RadioButton1->Checked)
         {break;}
      INPUT  inp[1];
      memset(inp, 0, sizeof(inp));

      inp[0].type = INPUT_KEYBOARD;
      inp[0].ki.wVk = 'C';
      SendInput(1,inp,sizeof(INPUT));

      Sleep(100);

      __int8 *buf = NULL;
      __int16 *buf_16 = NULL;
      OpenClipboard(GetForegroundWindow());
     (HGLOBAL)buf = (HGLOBAL)GetClipboardData(CF_TEXT);

      int i  = 0;
      while (buf[i] != 0)
         {
          buf[i] = m_Char[(byte)buf[i]];
          i++;
         }
         GlobalUnlock(buf);
         EmptyClipboard();
         SetClipboardData(CF_TEXT, buf);
         CloseClipboard();
         inp[0].type = INPUT_KEYBOARD;
         inp[0].ki.wVk = 'V';
         SendInput(1,inp,sizeof(INPUT));
         Sleep(100);
         buf = NULL;
      OpenClipboard(GetForegroundWindow());
     (HGLOBAL)buf = (HGLOBAL)GetClipboardData(CF_TEXT);
         buf[0] = ' ';
         buf[1] = 0;
         GlobalUnlock(buf);
         EmptyClipboard();
         SetClipboardData(CF_TEXT, buf);
         CloseClipboard();

         break;
        }
    case 1:
           {
           if (!RadioButton1->Checked)
              {break;}

       char Path[0x255];

        if  (GetModuleFileName(NULL, Path, sizeof(Path)))
            {
             DWORD j, i = 0;
             while  (Path[i])
                    {
                     if (Path[i] == 0x5C)
                       {
                        j = i;
                        }
                        i++;
                     };
             Path[j] = 0;
             ShellExecute(Handle, "explore", Path, NULL, NULL, SW_SHOW);
             } 
            }
    default: return;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::onFormClose(TObject *Sender, TCloseAction &Action)
{
    UnregisterHotKey(Handle,0);
    UnregisterHotKey(Handle,1);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormCreate(TObject *Sender)
{
  Image4->Picture->Bitmap = Image3->Picture->Bitmap;
  Image5->Picture->Bitmap = Image3->Picture->Bitmap;
  Image6->Picture->Bitmap = Image3->Picture->Bitmap;
  En_Rus();
  RegisterHotKey(Handle,0,MOD_CONTROL,VK_SPACE);
  RegisterHotKey(Handle,1,MOD_CONTROL,'O');
}
//---------------------------------------------------------------------------

