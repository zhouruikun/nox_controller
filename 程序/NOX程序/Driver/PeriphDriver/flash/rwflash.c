#define	 rwflash_globals
#include "stm32f10x.h"
#include "datatype.h"
#include "pattern_para.h"
#include "rwflash.h"






void read_from_flash(uint8 patnum , pattern *ptr)
{
    uint8 j,i=0;
    switch(patnum)
    {
    case 0: 
        for(j=0;j<50;j++)
        {
            ptr[j].pcmd = buffer0[i++];
            ptr[j].step = buffer0[i++];
            ptr[j].feelers = buffer0[i++];
        }
        break;

    case 1:
        for(j=0;j<50;j++)
        {
            ptr[j].pcmd = buffer1[i++];
            ptr[j].step = buffer1[i++];
            ptr[j].feelers = buffer1[i++];

        }
    break;

    case 2:
        for(j=0;j<50;j++)
        {
            ptr[j].pcmd = buffer2[i++];
            ptr[j].step = buffer2[i++];
            ptr[j].feelers = buffer2[i++];

        }
    break;
    }
}



void write_to_flash(uint8 patnum , pattern *ptr)
{
    uint8 j,i=0;
    switch(patnum)
    {
    case 0:
        for(j=0;j<50;j++)
        {
            buffer0[i++] = ptr[j].pcmd;
            buffer0[i++] = ptr[j].step;
            buffer0[i++] = ptr[j].feelers;
        }
        break;

    case 1:
        for(j=0;j<50;j++)
        {
            buffer1[i++] = ptr[j].pcmd;
            buffer1[i++] = ptr[j].step;
            buffer1[i++] = ptr[j].feelers;
        }
        break;

    case 2:
        for(j=0;j<50;j++)
        {
            buffer2[i++] = ptr[j].pcmd;
            buffer2[i++] = ptr[j].step;
            buffer2[i++] = ptr[j].feelers;
        }
        break;
    }
}

