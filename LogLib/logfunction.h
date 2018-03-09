/*
日志相关函数声明
*/
#pragma once
#ifndef __LOG_FUNCTION__
#define __LOG_FUNCTION__


void ErrorLog(const char *src_file, int src_line, int type, const char *fmt, ...);
void write_hd_log(char *filename, unsigned char *buffer, int len);

#endif