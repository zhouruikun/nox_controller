#ifndef _pattern_para_H_
#define _pattern_para_H_


#ifdef   pattern_para_globals
#define  pattern_para_ext
#else
#define  pattern_para_ext  extern   
#endif

#define prg_line 1000
/********************
*   结 构 体 定 义  *
********************/
 typedef struct{
               uint16 pcmd;//储伟器号-备用 
               uint16 step;//步骤或行号
               uint16 feelers;//投伟数或供伟数 
              }pattern;
    
//pattern_para_ext pattern  prg[prg_line];
pattern_para_ext pattern  prg[1][prg_line];
#endif
