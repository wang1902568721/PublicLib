#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <string.h>
#include <Windows.h>

/*
Function:根据格式获取日期
Parmater:
strTime		输出时间
strFormat	日期格式，选项如下
yyyy 年
mm	月
dd	日
hh  12小时
hh24 24小时
mi 分钟
ss 秒
ffff 毫秒
Note:
strTime需要有足够的存储空间
Author:
wangwei
Date:
2017/04/01
*/
int GetTime(char *  strTime, const char * strFormat)
{
	SYSTEMTIME sysTime;
	char caTemp[5] = { 0 };
	int iCount = 0;
	const char *pStrPos = NULL;

	pStrPos = NULL;
	if (NULL == strTime || NULL == strFormat)
	{
		return -1;
	}
	pStrPos = strFormat;

	//获取当前时间
	GetLocalTime(&sysTime);

	while (0 != strncmp(pStrPos, "", 1))
	{
		if ('y' == *pStrPos || 'Y' == *pStrPos)
		{
			//Year
			iCount = 0;
			while ('y' == *pStrPos || 'Y' == *pStrPos)
			{
				iCount = iCount + 1;
				pStrPos = pStrPos + 1;
			}
			if (0 != iCount)
			{
				memset(caTemp, 0x00, 5);
				sprintf(caTemp, "%04d", sysTime.wYear);
				strncat(strTime, caTemp + (4 - iCount), iCount);
			}
		}
		else if ('m' == *pStrPos || 'M' == *pStrPos)
		{
			if ('m' == *(pStrPos + 1) || 'M' == *(pStrPos + 1))
			{
				//Month
				memset(caTemp, 0x00, 5);
				sprintf(caTemp, "%04d", sysTime.wMonth);
				strncat(strTime, caTemp + (4 - 2), 2);
				pStrPos = pStrPos + 2;
			}
			else
			{
				if ('i' == *(pStrPos + 1) || 'I' == *(pStrPos + 1))
				{
					//Minute
					memset(caTemp, 0x00, 5);
					sprintf(caTemp, "%04d", sysTime.wMinute);
					strncat(strTime, caTemp + (4 - 2), 2);
					pStrPos = pStrPos + 2;
				}
				else
				{
					pStrPos = pStrPos + 1;
				}
			}
		}
		else if ('d' == *pStrPos || 'D' == *pStrPos)
		{
			if ('d' == *(pStrPos + 1) || 'D' == *(pStrPos + 1))
			{
				//Day
				memset(caTemp, 0x00, 5);
				sprintf(caTemp, "%04d", sysTime.wDay);
				strncat(strTime, caTemp + (4 - 2), 2);
				pStrPos = pStrPos + 2;
			}
			else
			{
				pStrPos = pStrPos + 1;
			}
		}
		else if ('h' == *pStrPos || 'H' == *pStrPos)
		{
			if ('h' == *(pStrPos + 1) || 'H' == *(pStrPos + 1))
			{
				//Hour
				pStrPos = pStrPos + 2;
				memset(caTemp, 0x00, 5);
				sprintf(caTemp, "%0d", sysTime.wHour);
				//24和12小时制处理
				if ('2' == *pStrPos && '4' == *(pStrPos + 1))
				{
					sprintf(caTemp, "%04d", sysTime.wHour);
					pStrPos = pStrPos + 2;
				}
				else
				{
					if (sysTime.wHour > 12)
					{
						sprintf(caTemp, "%04d", sysTime.wHour - 12);
					}
					else
					{
						sprintf(caTemp, "%04d", sysTime.wHour);
					}
				}
				strncat(strTime, caTemp + (4 - 2), 2);
			}
			else
			{
				pStrPos = pStrPos + 1;
			}
		}
		else if ('s' == *pStrPos || 'S' == *pStrPos)
		{
			//Seconds
			if ('s' == *(pStrPos + 1) || 'S' == *(pStrPos + 1))
			{
				//Seconds
				memset(caTemp, 0x00, 5);
				sprintf(caTemp, "%04d", sysTime.wSecond);
				strncat(strTime, caTemp + (4 - 2), 2);
				pStrPos = pStrPos + 2;
			}
			else
			{
				pStrPos = pStrPos + 1;
			}
		}
		else if ('f' == *pStrPos || 'F' == *pStrPos)
		{
			//Milliseconds
			iCount = 0;
			while ('f' == *pStrPos || 'F' == *pStrPos)
			{
				iCount = iCount + 1;
				pStrPos = pStrPos + 1;
			}
			if (3 == iCount)
			{
				memset(caTemp, 0x00, 5);
				sprintf(caTemp, "%04d", sysTime.wMilliseconds);
				strncat(strTime, caTemp + 1, 3);
			}
		}
		else
		{
			strncat(strTime, pStrPos, sizeof(char));
			pStrPos = pStrPos + 1;
		}
	}
	return 0;
}

//int GetTime(char * const strTime, const char * strDelimiter, const char * strFormat)
//{
//	SYSTEMTIME sysTime;
//	GetLocalTime(&sysTime);
//
//	return 0;
//}
//int TokenStr(char * const strSource, char * const strResult, const char *tokenStr)
//{
//	char *token;
//	char *nextTokenPos = NULL;
//	token = NULL;
//	token = strtok_s(strSource, tokenStr, &nextTokenPos);
//	while (NULL != token)
//	{
//		strcat(strResult, token);
//		token = strtok_s(NULL, tokenStr, &nextTokenPos);
//	}
//	return 0;
//}
//
//int GetDate(char * const strDate)
//{
//	char tmpBuf[128] = { 0 };
//
//	if (NULL == strDate)
//	{
//		return -1;
//	}
//	_strdate_s(tmpBuf, 128);
//	TokenStr(tmpBuf, strDate, "\/");
//
//	return 0;
//}