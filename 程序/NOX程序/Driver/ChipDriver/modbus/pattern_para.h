#ifndef _pattern_para_H_
#define _pattern_para_H_


#ifdef   pattern_para_globals
#define  pattern_para_ext
#else
#define  pattern_para_ext  extern   
#endif

#define prg_line 1000
/********************
*   �� �� �� �� ��  *
********************/
 typedef struct{
               uint16 pcmd;//��ΰ����-���� 
               uint16 step;//������к�
               uint16 feelers;//Ͷΰ����ΰ�� 
              }pattern;
    
//pattern_para_ext pattern  prg[prg_line];
pattern_para_ext pattern  prg[1][prg_line];
#endif
