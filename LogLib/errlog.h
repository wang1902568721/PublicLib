#ifndef _ERRLOG_H

#define _ERRLOG_H

#define	BUILD_DEBUG	1

/*
 *  如果定义 BUILD_DEBUG 且值等于 "1"，主程序需要声明此变量。
 *  其值为 "1" 时打印调试记录。
 */

#ifdef	_ERRLOG_C_
		int	ErrlogBuildDebug = 0;
#else
	extern	int	ErrlogBuildDebug;
#endif

#define	ErrLog		ERRLOG

#define ERRLOG_ERROR   	0
#define ERRLOG_WARNING 	1
#define ERRLOG_TRACE   	2
#define ERRLOG_DEBUG   	3
#define ERRLOG_MONILOG	4

#define LINE_LEN    20
#define	LINE1  	    "01=02=03=04=05=06=07=08=09=10=11=12=13=14=15=16=17=18="
#define DEVIDE_LINE LINE1"19=20=123456789ABCDEFGHIJK\n"

#define ERROR		__FILE__, __LINE__, ERRLOG_ERROR
#define WARNING		__FILE__, __LINE__, ERRLOG_WARNING
#define TRACE		__FILE__, __LINE__, ERRLOG_TRACE
#define DEBUG		__FILE__, __LINE__, ERRLOG_DEBUG
#define MONILOG		__FILE__, __LINE__, ERRLOG_MONILOG

#define WARNG		WARNING

#define ERRLOG_T_FILE		"/log/T_log"
#define ERRLOG_E_FILE		"/log/E_log"
#define ERRLOG_W_FILE		"/log/W_log"
#define ERRLOG_D_FILE		"/log/D_log"
#define ERRLOG_M_FILE		"/log/M_log"

#define _PRINT(f,x)		">> %-15s = [%"#f"]",#x,(x)

#define PRINTD(f,x)		ErrorLog (DEBUG,  _PRINT(f,x))
#define PRINTE(f,x)		ErrorLog (ERROR,  _PRINT(f,x))
#define PRINTT(f,x)		ErrorLog (TRACE,  _PRINT(f,x))
#define PRINTW(f,x)		ErrorLog (WARNING,_PRINT(f,x))
#define PRINTM(f,x)		ErrorLog (MONILOG,_PRINT(f,x))

#define MAX_PATH 256

#endif
