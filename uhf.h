#ifndef uhf_h
#define uhf_h

#include <inttypes.h>
#include <Stream.h>
#include <Arduino.h>

class UHFclass
{
    public:
        
        void hitungan(uint16_t* a);
        void kelompok();
        bool ai1; 

    private:
    String getValue(String data, char separator, int index);
};

#endif