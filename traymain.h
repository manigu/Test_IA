//---------------------------------------------------------------------------
#ifndef traymainH
#define traymainH
//---------------------------------------------------------------------------
#include <Forms.hpp>
#include <StdCtrls.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Graphics.hpp>
#include <ComCtrls.hpp>
#include <jpeg.hpp>
#include <Winbase.h>

#define MYWM_NOTIFY (WM_APP+100)
#define IDC_MYICON   1006
extern HINSTANCE g_hinst;
LRESULT IconDrawItem(LPDRAWITEMSTRUCT lpdi);
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:
    TButton *Button1;
    TCheckBox *CheckBox1;
    TEdit *Edit1;
    TEdit *Edit2;
    TImage *Image2;
    TImage *Image1;
    TLabel *Label1;
    TLabel *Label2;
    TPopupMenu *PopupMenu1;
    TMenuItem *Properties1;
    TMenuItem *ToggleState1;
    TMenuItem *Shutdown1;
        TImage *Image3;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TGroupBox *GroupBox1;
        TImage *Image4;
        TGroupBox *GroupBox2;
        TImage *Image5;
        TPanel *Panel1;
        TCheckBox *CheckBox2;
        TImage *Image6;
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall CheckBox1Click(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall RadioButtonClick(TObject *Sender);
    void __fastcall EditKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall Properties1Click(TObject *Sender);
    void __fastcall ToggleState1Click(TObject *Sender);
    void __fastcall clear_buf(TObject *Sender);
    void __fastcall Shutdown1Click(TObject *Sender);
    void __fastcall onFormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall RadioButtonColor();

private:        // private user declarations
    void __fastcall DrawItem(TMessage& Msg);
    void __fastcall MyNotify(TMessage& Msg);
    bool __fastcall TrayMessage(DWORD dwMessage);
    HICON __fastcall IconHandle(void);
    void __fastcall ToggleState(void);
    void __fastcall Form_invetr(TObject *Sender);
    void __fastcall WMHotKey(TWMHotKey &Message);  //Для клавы
    void __fastcall PropertiFrm(TObject *Sender); //

public:         // public user declarations

    virtual __fastcall TFormMain(TComponent* Owner);

     BEGIN_MESSAGE_MAP
       MESSAGE_HANDLER(WM_DRAWITEM,TMessage,DrawItem)
       MESSAGE_HANDLER(MYWM_NOTIFY,TMessage,MyNotify)
       MESSAGE_HANDLER(WM_HOTKEY,TWMHotKey,WMHotKey);
     END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern TFormMain *FormMain;
//---------------------------------------------------------------------------

#endif
