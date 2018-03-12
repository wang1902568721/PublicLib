#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include "timeoper.h"
#include "logfunction.h"

#define		_ERRLOG_C_

#ifdef		TPIS_LIB
#endif

#include	"errlog.h"

void ErrorLog (const char *src_file, int src_line, int type, const char *fmt, ...)
{
	va_list	args;
	char now[19] = {0};
	FILE	* fp;
	char	* file;
	char    sLogDate[11] = {0};

	memset(sLogDate, 0, sizeof(sLogDate));

	switch (type)
	{
#if	(BUILD_DEBUG != 0)

		case	ERRLOG_DEBUG:
			if (ErrlogBuildDebug)
			{
				file = ERRLOG_D_FILE;
				break;
			}
			else
			{
				return;
			}
#endif

		case	ERRLOG_ERROR:	file = ERRLOG_E_FILE; break;
		case	ERRLOG_TRACE:	file = ERRLOG_T_FILE; break;
		case	ERRLOG_WARNING:	file = ERRLOG_W_FILE; break;
		case	ERRLOG_MONILOG:	file = ERRLOG_M_FILE; break;
		default:		return;
	}

#ifdef	TPIS_LIB
	fp = open_by (file, -1, NULL, "a");
#else
	{
		char	path[MAX_PATH] = {0};
		GetTime(sLogDate,"yymmdd");
		//sprintf (path, "%s%s%s", getenv ("WORKDIR"),file,sLogDate);
		sprintf(path, "D:%s%s", file, sLogDate);
		fp = fopen(path, "a");
	}
#endif

	fp = (fp ? fp : stderr);

	GetTime(now, "mm/dd hh24:mi:ss.fff");
	if(type == ERRLOG_MONILOG)
	{
	}
	else
	{
		fprintf (fp, "%18s %s[%d]\t",now, src_file, src_line);
	}

	va_start (args, fmt);
	vfprintf (fp, fmt, args);
	va_end	 (args);

	fprintf (fp, "\n");

	fflush (fp);

	if (stderr != fp)
	{
		fclose(fp);
	}
	return;
}

void write_hd_log (char *filename, unsigned char *buffer, int len)
{
	int	i, j ,maxlen;
	FILE	*log_file;
	char	date[11] = { 0 }, time[11] = { 0 }, tmp[40] = { 0 }, path[80] = {0};

	maxlen = 1;

	GetTime(date,"yymmdd");
	GetTime(time, "hh24:mi:ss");

	sprintf (tmp, "/log/%s%s", filename, date);
	sprintf(path, "D:%s", tmp);
	//sprintf ( path, "%s%s", getenv ( "WORKDIR" ), tmp );

	log_file = fopen (path, "a+");

	if (log_file != NULL)
	{
		fprintf(log_file, "%s %s		%s:\n", date, time, filename);
		fprintf(log_file, DEVIDE_LINE);

		for  (i = 0; i <= (len/LINE_LEN); i ++) 
		{
			for (j = 0; j < LINE_LEN; j ++)
			{
				if (i == len / LINE_LEN && j >= (len - 1) % LINE_LEN + 1)
				{
					fprintf(log_file, "   ");
				}
				else if (i == len / LINE_LEN && (i * LINE_LEN + j) == len)
				{
					break;
				}
				else
				{
					fprintf(log_file, "%02X ", buffer[i*LINE_LEN + j]);
				}
			}
			for (j = 0; j < LINE_LEN; j ++)
			{
				if (i == len / LINE_LEN && j >= (len - 1) % LINE_LEN + 1)
				{
					;
				}
				else if (isprint(buffer[i*LINE_LEN + j]))
				{
					fputc(buffer[i*LINE_LEN + j], log_file);
				}
				else
				{
					fputc('.', log_file);
				}
			}
			fprintf(log_file, "\n");
		}

		fprintf(log_file, DEVIDE_LINE);
		fprintf(log_file, "\n\n");
		fclose	(log_file);
	}
}