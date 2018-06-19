#ifndef _rwflash_H
#define _rwflash_H


#ifdef   rwflash_globals
#define  rwflash_ext
#else
#define  rwflash_ext  extern
#endif



rwflash_ext uint16 buffer0[150];
rwflash_ext uint16 buffer1[150],buffer2[150];
rwflash_ext void read_from_flash(uint8 patnum , pattern *ptr);
rwflash_ext void write_to_flash(uint8 patnum , pattern *ptr);



#endif
