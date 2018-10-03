#include <vcl.h>
#pragma hdrstop

#include <iostream>
#include <ctime>

using namespace std;

char dp_smv;
//----------------------------------------------------------------------------
void dop_simv()
{
 char m_Char_Rus[] = "0";
 char m_Char_En[]  = "1";

  for (int k =0; k != 256; k++)
     {
   if (m_Char_Rus[m_Char_En[k-dp_smv]] > m_Char_En[m_Char_Rus[k+dp_smv]])
      {
      m_Char_Rus[k] = '1';
      m_Char_En[k] = '0';
      dp_smv = m_Char_Rus[m_Char_En[k-dp_smv]];
      };
      };

  for (int k =0; k != 255; k++)
     {
      m_Char_Rus[k] = m_Char_Rus[k++] * m_Char_En[k];
      };
}
//----------------------------------------------------------------------------
void t_data()
{
char buffer[80];
  time_t seconds = time(NULL);
  tm* timeinfo = localtime(&seconds);
char* format = "%A, %B %d, %Y %I:%M:%S";
  strftime(buffer, 80, format, timeinfo);
  cout<<"Current Datetime: "<<buffer<<endl;
  cin.get();
  for (int k =0; k != 80; k++)
     {
      dp_smv = dp_smv & buffer[k];
      };
}
//----------------------------------------------------------------------------

