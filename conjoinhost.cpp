//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "conjoinhost.h"
#include "dockform.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TConjoinDockHost *ConjoinDockHost;
//---------------------------------------------------------------------------
__fastcall TConjoinDockHost::TConjoinDockHost(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void TConjoinDockHost::DoFloat(TControl* AControl)
{
  Types::TPoint TopLeft = AControl->ClientToScreen(Point(0, 0));
  Types::TPoint BottomRight = AControl->ClientToScreen(Point(AControl->UndockWidth,
                       AControl->UndockHeight));

  AControl->ManualFloat(Types::TRect(TopLeft, BottomRight));
}
//---------------------------------------------------------------------------

void TConjoinDockHost::UpdateCaption(TControl* Exclude)
{
  int I;
  Caption = "";
  for (I = 0; I < DockClientCount; I++)
    if (DockClients[I]->Visible && (DockClients[I] != Exclude))
      Caption = Caption + static_cast<TDockableForm*>(DockClients[I])->Caption + " ";
}
//---------------------------------------------------------------------------

void __fastcall TConjoinDockHost::FormClose(TObject *Sender, TCloseAction &Action)
{
  if (DockClientCount == 1)
  {
    DoFloat(DockClients[0]);
    Action = caFree;
  }
  else
    Action = caHide;
}
//---------------------------------------------------------------------------

void __fastcall TConjoinDockHost::FormDockDrop(TObject *Sender,
      TDragDockObject *Source, int X, int Y)
{
  UpdateCaption(NULL);
  DockManager->ResetBounds(true);
}
//---------------------------------------------------------------------------

void __fastcall TConjoinDockHost::FormDockOver(TObject *Sender,
      TDragDockObject *Source, int X, int Y, TDragState State,
      bool &Accept)
{
  Accept = (dynamic_cast<TDockableForm*>(Source->Control) != NULL);
}
//---------------------------------------------------------------------------

void __fastcall TConjoinDockHost::FormGetSiteInfo(TObject *Sender,
      TControl *DockClient, TRect &InfluenceRect, TPoint &MousePos,
      bool &CanDock)
{
  CanDock = (dynamic_cast<TDockableForm*>(DockClient) != NULL);
}
//---------------------------------------------------------------------------

void __fastcall TConjoinDockHost::FormUnDock(TObject *Sender, TControl *Client,
      TWinControl *NewTarget, bool &Allow)
{
  if (dynamic_cast<TDockableForm*>(Client) != NULL)
    (static_cast<TDockableForm*>(Client))->DockSite = true;

  if ((DockClientCount == 2) && (NewTarget != this))
    PostMessage(this->Handle, WM_CLOSE, 0, 0);
  UpdateCaption(Client);
}
//---------------------------------------------------------------------------


