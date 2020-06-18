
#include <uhf.h>


uint16_t a;
uint16_t b;
uint16_t c;
uint16_t d;
uint16_t x;
uint16_t y;
uint16_t j;
uint16_t e;

uint16_t gol1 = 237 -12;
uint16_t gol2 = gol2;
uint16_t gol3 = gol3;
uint16_t gol4 = gol4;
uint16_t gol5 = gol5;
uint16_t gol6 = gol6;
uint16_t gol7 = gol7;
uint16_t gol8 = gol8;
uint16_t notag, notag2;
bool ai1;

String UHFclass :: getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}


  /*notag2     notag     hsl
    255         255      0
    255         253      1
    255         251      2
    ...         ...     ...
    255         237      9
    -------------------------
    253         255      81
    251         255      82
    ...         ...     ...
    -------------------------
    253         253     161
    253         251     162
    ...         ...     ...
    -------------------------

  */
 void UHFclass :: kelompok()
 {
 if (notag != 255 && notag2 == 255)
 {
      ai1 =true;
    if(notag > gol1)
    {
        a = 255 -notag;
        hitungan(&a);
    }

    else if(notag <gol1 && notag > gol2)
    {
        a = 237 - notag;
        hitungan(&a);
    }

    else if(notag <gol2 && notag > gol3)
    {
        a = gol1 -notag;
        hitungan(&a);
    }
     
      else if(notag <gol3 && notag > gol4)
    {
        a = gol2 -notag;
        hitungan(&a);
    }

     else if(notag <gol4 && notag > gol5)
    {
        a = gol3 -notag;
        hitungan(&a);
    }

     else if(notag <gol5 && notag > gol6)
    {
        a = gol4 -notag;
        hitungan(&a);
    }

     else if(notag <gol6 && notag > gol7)
    {
        a = gol5 -notag;
        hitungan(&a);
    }

     else if(notag <gol7 && notag > gol8)
    {
        a = gol6 -notag;
        hitungan(&a);
    }
 }

 else if(notag == 255 && notag2 != 255)
 {
     ai1 =false;
    if(notag2 > gol1)
    {
         a = 255 -notag2;
        hitungan(&a);
    }

    else if(notag2 <gol1 && notag2 > gol2)
    {
        a = 237 - notag2;
        hitungan(&a);
    }

    else if(notag2 <gol2 && notag2 > gol3)
    {
        a = gol1 -notag2;
        hitungan(&a);
    }
     
      else if(notag2 <gol3 && notag2 > gol4)
    {
        a = gol2 -notag;
        hitungan(&a);
    }

     else if(notag2 <gol4 && notag2 > gol5)
    {
        a = gol3 -notag;
        hitungan(&a);
    }

     else if(notag2 <gol5 && notag2 > gol6)
    {
        a = gol4 -notag;
        hitungan(&a);
    }

     else if(notag2 <gol6 && notag2 > gol7)
    {
        a = gol5 -notag2;
        hitungan(&a);
    }

     else if(notag2 <gol7 && notag2 > gol8)
    {
        a = gol6 -notag2;
        hitungan(&a);
    }  
 }
 else if(notag != 253 && notag2 == 253 && notag>=253)
 {
     
      ai1 =true;
    if(notag > gol1)
    {
        a = 255 -notag;
        hitungan(&a);
    }

    else if(notag <gol1 && notag > gol2)
    {
        a = 237 - notag;
        hitungan(&a);
    }

    else if(notag <gol2 && notag > gol3)
    {
        a = gol1 -notag;
        hitungan(&a);
    }
     
      else if(notag <gol3 && notag > gol4)
    {
        a = gol2 -notag;
        hitungan(&a);
    }

     else if(notag <gol4 && notag > gol5)
    {
        a = gol3 -notag;
        hitungan(&a);
    }

     else if(notag <gol5 && notag > gol6)
    {
        a = gol4 -notag;
        hitungan(&a);
    }

     else if(notag <gol6 && notag > gol7)
    {
        a = gol5 -notag;
        hitungan(&a);
    }

     else if(notag <gol7 && notag > gol8)
    {
        a = gol6 -notag;
        hitungan(&a);
    }
    }
 }

 void UHFclass :: hitungan(uint16_t *a)
 {
     if(ai1)
     {
     b = a;
     j = b*2;
     y = 255 - j;
       
    }

    else
    {
     c = 255-notag2;
     d = c;
     e = d*2;
     x = 255-e;
     
    }
     
 }