
#ifndef _key_H
#define _key_H

#ifdef   key_globals
#define  key_ext
#else
#define  key_ext  extern
#endif
	
key_ext uint8 key_flag;
key_ext uint16 key_timer_count;	 
key_ext void keyboard_init(void);//°´¼ü³õÊ¼»¯
key_ext uint8 key_scan_wait(void);
key_ext uint8 key_scan_nowait(void);

#endif
