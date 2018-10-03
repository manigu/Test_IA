#include <windows.h>
#include "T_datas.cpp"

   char m_Char[256];
   char ferst_sim;
//------------------------------------------------------
void En_Rus()
{
 char m_Char_Rus[] = "àáâãäå¸æçèéêëìíîïğñòóôõö÷øùúûüışÿÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞß\0";
 char m_Char_En[]  = "f,dult`;pbqrkvyjghcnea[wxio]sm'.zF<DULT~:PBQRKVYJGHCNEA{WXIO}SM\">Z\0";
 char Last_sim;

  for (int k =0; k != 256; k++)
     {
      m_Char[k] = k;
      };

  for (int k =0; k != 66; k++)
     {
        int k1 =0;
      while (m_Char_En[k] != m_Char[k1])
           {
             k1++;
            }
      m_Char[k1] =  m_Char_Rus[k];
     };
}
//------------------------------------------------------
void xsh_simv()
{
  for (int k =0; k != 256; k++)
     {
      ferst_sim = dp_smv;
      };
}
//------------------------------------------------------

