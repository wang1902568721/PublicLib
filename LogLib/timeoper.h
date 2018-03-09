#pragma once
#ifndef __TIME_OPER__
#define __TIME_OPER__

int TokenStr(char * const strSource, char * const strResult, const char *tokenStr);
int GetDate(char * const strDate);
int GetTime(char *  strTime, const char * strFormat);


#endif