
#include <vcl.h>
#pragma hdrstop

#include <dbtables.hpp>
#include <axctrls.hpp>


TAdHcDM *AdHcDM;

__fastcall TFormMain::TAdHcDM(TComponent* Owner) : TCRemoteDataModule(Owner)
{
}
//----------------------------------------------------------------------------
STDMETHODIMP TFormMain::GetDBNames(IStringsPtr* Value)
{
  TPtr<TStringList> Names = new TStringList();
  int i, Temp;
  HRESULT hr;

  __try
  {
    try
    {
      Session->GetDatabaseNames(Names);
      for (i = 0; i < Names->Count-1; i++)
        (*Value)->Add(WideString(Names->Strings[i]), Temp);
      hr = S_OK;
    }
    catch (...)
    {
      hr = E_FAIL;
    }
  }
  __finally
  {
    return hr;
  }
}
//----------------------------------------------------------------------------
STDMETHODIMP TFormMain::GetTableNames(BSTR sAlias,
  IStringsPtr* TableNames)
{
  TPtr<TStringList> Names = new TStringList();
  int i, Temp;

  try
  {

    Session->GetTableNames(sAlias, "", true, true, Names);

    for (i = 0; i < Names->Count-1; i++)
      (*TableNames)->Add(WideString(Names->Strings[i]), Temp);
    return S_OK;
  }
  catch (...)
  {
    return E_FAIL;
  }
}


STDMETHODIMP TAdHcDMImpl::SetTable(BSTR DB, BSTR Table)
{
  __try
  {
    m_DataModule->Table->Close();
    m_DataModule->Table->DatabaseName = DB;
    m_DataModule->Table->TableName = Table;
    m_DataModule->Table->Open();
    return S_OK;
  }
  catch (...)
  {
    return E_FAIL;
  }
}


