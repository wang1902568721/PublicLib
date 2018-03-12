/*
日志相关函数声明
*/
#pragma once
#ifndef __LOG_FUNCTION__
#define __LOG_FUNCTION__

#ifndef LOGLIB
#define LOGLIB_OPER __declspec( dllimport )
#else
#define LOGLIB_OPER __declspec( dllexport )
#endif

#define ERRLOG_ERROR   	0
#define ERRLOG_WARNING 	1
#define ERRLOG_TRACE   	2
#define ERRLOG_DEBUG   	3
#define ERRLOG_MONILOG	4

#define ERROR		__FILE__, __LINE__, ERRLOG_ERROR
#define WARNING		__FILE__, __LINE__, ERRLOG_WARNING
#define TRACE		__FILE__, __LINE__, ERRLOG_TRACE
#define DEBUG		__FILE__, __LINE__, ERRLOG_DEBUG
#define MONILOG		__FILE__, __LINE__, ERRLOG_MONILOG


extern "C"
{
	void LOGLIB_OPER ErrorLog(const char *src_file, int src_line, int type, const char *fmt, ...);
	void LOGLIB_OPER write_hd_log(char *filename, unsigned char *buffer, int len);
}

#endif