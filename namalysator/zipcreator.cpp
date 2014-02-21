/*
	Portions based on minizip:
    Version 1.01e, February 12th, 2005
    Copyright (C) 1998-2005 Gilles Vollant
*/

#include "zipcreator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>

#ifdef unix
# include <unistd.h>
# include <utime.h>
# include <sys/types.h>
# include <sys/stat.h>
#else
# include <direct.h>
# include <io.h>
#endif

#ifdef WIN32
#define USEWIN32IOAPI
#include "minizip/iowin32.h"
#endif

/******************************************/
/* General purpose functions as needed    */

#define WRITEBUFFERSIZE (16384)
#define MAXFILENAME (256)

#ifdef WIN32
uLong filetime(const char *f, tm_zip *tmzip, uLong *dt)
{
  int ret = 0;
  {
      FILETIME ftLocal;
      HANDLE hFind;
      WIN32_FIND_DATAA  ff32;

      hFind = FindFirstFileA(f,&ff32);
      if (hFind != INVALID_HANDLE_VALUE)
      {
        FileTimeToLocalFileTime(&(ff32.ftLastWriteTime),&ftLocal);
        FileTimeToDosDateTime(&ftLocal,((LPWORD)dt)+1,((LPWORD)dt)+0);
        FindClose(hFind);
        ret = 1;
      }
  }
  return ret;
}

void timenow(tm_zip *tmzip, uLong *dt)
{
	SYSTEMTIME st;
	memset(&st, 0, sizeof(st));
	GetLocalTime(&st);
	tmzip->tm_year = st.wYear;
	tmzip->tm_mon = st.wMonth;
	tmzip->tm_mday = st.wDay;
	tmzip->tm_hour = st.wHour;
	tmzip->tm_min = st.wMinute;
	tmzip->tm_sec = st.wSecond;

	FILETIME ft;
	memset(&ft, 0, sizeof(ft));
	SystemTimeToFileTime(&st, &ft);
	FileTimeToDosDateTime(&ft, ((LPWORD)dt)+1,((LPWORD)dt)+0);
}
#else
#ifdef unix
uLong filetime(f, tmzip, dt)
    char *f;               /* name of file to get info on */
    tm_zip *tmzip;         /* return value: access, modific. and creation times */
    uLong *dt;             /* dostime */
{
  int ret=0;
  struct stat s;        /* results of stat() */
  struct tm* filedate;
  time_t tm_t=0;

  if (strcmp(f,"-")!=0)
  {
    char name[MAXFILENAME+1];
    int len = strlen(f);
    if (len > MAXFILENAME)
      len = MAXFILENAME;

    strncpy(name, f,MAXFILENAME-1);
    /* strncpy doesnt append the trailing NULL, of the string is too long. */
    name[ MAXFILENAME ] = '\0';

    if (name[len - 1] == '/')
      name[len - 1] = '\0';
    /* not all systems allow stat'ing a file with / appended */
    if (stat(name,&s)==0)
    {
      tm_t = s.st_mtime;
      ret = 1;
    }
  }
  filedate = localtime(&tm_t);

  tmzip->tm_sec  = filedate->tm_sec;
  tmzip->tm_min  = filedate->tm_min;
  tmzip->tm_hour = filedate->tm_hour;
  tmzip->tm_mday = filedate->tm_mday;
  tmzip->tm_mon  = filedate->tm_mon ;
  tmzip->tm_year = filedate->tm_year;

  return ret;
}
#else
uLong filetime(f, tmzip, dt)
    char *f;                /* name of file to get info on */
    tm_zip *tmzip;             /* return value: access, modific. and creation times */
    uLong *dt;             /* dostime */
{
    return 0;
}
#endif
#endif

/* calculate the CRC32 of a file,
   because to encrypt a file, we need known the CRC32 of the file before */
int getFileCrc(const char* filenameinzip,void*buf,unsigned long size_buf,unsigned long* result_crc)
{
   unsigned long calculate_crc=0;
   int err=ZIP_OK;
   FILE * fin = fopen(filenameinzip,"rb");
   unsigned long size_read = 0;
   unsigned long total_read = 0;
   if (fin==NULL)
   {
       err = ZIP_ERRNO;
   }

    if (err == ZIP_OK)
        do
        {
            err = ZIP_OK;
            size_read = (int)fread(buf,1,size_buf,fin);
            if (size_read < size_buf)
                if (feof(fin)==0)
            {
                printf("error in reading %s\n",filenameinzip);
                err = ZIP_ERRNO;
            }

            if (size_read>0)
                calculate_crc = crc32(calculate_crc, (Bytef *)buf,size_read);
            total_read += size_read;

        } while ((err == ZIP_OK) && (size_read>0));

    if (fin)
        fclose(fin);

    *result_crc=calculate_crc;
    printf("file %s crc %x\n",filenameinzip,calculate_crc);
    return err;
}

int getMemCrc(const void *buf, unsigned long size_buf, unsigned long* result_crc)
{
	unsigned long calculate_crc=0;
	calculate_crc = crc32(calculate_crc, (Bytef *)buf, size_buf);
	*result_crc=calculate_crc;
	return ZIP_OK;
}

void zip_creator::reset()
{
	buf.resize(WRITEBUFFERSIZE);
}

bool zip_creator::open_zip(const std::string &name)
{
#ifdef USEWIN32IOAPI
    zlib_filefunc_def ffunc;
    fill_win32_filefunc(&ffunc);
    zf = zipOpen2(name.c_str(), APPEND_STATUS_CREATE, NULL, &ffunc);
#else
    zf = zipOpen(name.c_str(), APPEND_STATUS_CREATE);
#endif
	if (zf == NULL) {
		return false;
	} else {
		return true;
	}
}

bool zip_creator::add_directory(const std::string &name)
{
    unsigned long crcFile = 0;
    zip_fileinfo zi;
	int err;

    zi.tmz_date.tm_sec = zi.tmz_date.tm_min = zi.tmz_date.tm_hour =
    zi.tmz_date.tm_mday = zi.tmz_date.tm_mon = zi.tmz_date.tm_year = 0;
    zi.dosDate = 0;
    zi.internal_fa = 0;
	zi.external_fa = FILE_ATTRIBUTE_DIRECTORY;
    filetime(name.c_str(), &zi.tmz_date, &zi.dosDate);
    err = getFileCrc(name.c_str(), &buf[0], WRITEBUFFERSIZE, &crcFile);
	err = zipOpenNewFileInZip3(zf, name.c_str(), &zi,
					 NULL, 0, NULL, 0, NULL,
					 0,
					 0,0,
					 -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY,
					 NULL, crcFile);
	if (err != ZIP_OK) {
		return false;
	} else {
		err = zipCloseFileInZip(zf);
		return true;
	}
}

bool zip_creator::add_file(const std::string &file_inzip, const std::string &filename)
{
    int opt_compress_level=Z_DEFAULT_COMPRESSION;
    unsigned long crcFile = 0;
    zip_fileinfo zi;
	int err;

    zi.tmz_date.tm_sec = zi.tmz_date.tm_min = zi.tmz_date.tm_hour =
    zi.tmz_date.tm_mday = zi.tmz_date.tm_mon = zi.tmz_date.tm_year = 0;
    zi.dosDate = 0;
    zi.internal_fa = 0;
	zi.external_fa = FILE_ATTRIBUTE_ARCHIVE;
    filetime(filename.c_str(), &zi.tmz_date, &zi.dosDate);
    err = getFileCrc(filename.c_str(), &buf[0], WRITEBUFFERSIZE, &crcFile);
	if (err != ZIP_OK) {
		return false;
	}
	err = zipOpenNewFileInZip3(zf, file_inzip.c_str(), &zi,
					 NULL, 0, NULL, 0, NULL,
					 (opt_compress_level != 0) ? Z_DEFLATED : 0,
					 opt_compress_level, 0,
					 -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY,
					 NULL, crcFile);
	if (err != ZIP_OK) {
		printf("error in opening %s in zipfile\n", file_inzip.c_str());
	} else {
		FILE *fin = fopen(filename.c_str(),"rb");
		if (!fin) {
			err = zipCloseFileInZip(zf);
			return false;
		} else {
			size_t size_read;
			do
			{
				err = ZIP_OK;
				size_read = fread(&buf[0], 1, WRITEBUFFERSIZE, fin);
				if (size_read < WRITEBUFFERSIZE) {
					if (feof(fin) == 0) {
						printf("error in reading %s\n", filename.c_str());
					}
				}
				if (size_read > 0) {
					err = zipWriteInFileInZip(zf, &buf[0], size_read);
					if (err<0) {
						printf("error in writing %s in the zipfile\n", file_inzip.c_str());
					}
				}
			} while ((err == ZIP_OK) && (size_read > 0));
			fclose(fin);
		}
		err = zipCloseFileInZip(zf);
		if (err != ZIP_OK) {
			printf("error in closing %s in the zipfile\n", file_inzip.c_str());
		}
	}
	return true;
}

bool zip_creator::add_memfile(const std::string &file_inzip, const std::string &data)
{
    int opt_compress_level=Z_DEFAULT_COMPRESSION;
    unsigned long crcFile = 0;
    zip_fileinfo zi;
	int err;

    zi.tmz_date.tm_sec = zi.tmz_date.tm_min = zi.tmz_date.tm_hour =
    zi.tmz_date.tm_mday = zi.tmz_date.tm_mon = zi.tmz_date.tm_year = 0;
    zi.dosDate = 0;
    zi.internal_fa = 0;
	zi.external_fa = FILE_ATTRIBUTE_ARCHIVE;
	timenow(&zi.tmz_date, &zi.dosDate);
    err = getMemCrc(data.c_str(), data.length(), &crcFile);
	if (err != ZIP_OK) {
		return false;
	}
	err = zipOpenNewFileInZip3(zf, file_inzip.c_str(), &zi,
					 NULL, 0, NULL, 0, NULL,
					 (opt_compress_level != 0) ? Z_DEFLATED : 0,
					 opt_compress_level, 0,
					 -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY,
					 NULL, crcFile);
	if (err != ZIP_OK) {
		printf("error in opening %s in zipfile\n", file_inzip.c_str());
	} else {
		err = zipWriteInFileInZip(zf, data.c_str(), data.length());
		if (err<0) {
			printf("error in writing %s in the zipfile\n", file_inzip.c_str());
		}
		err = zipCloseFileInZip(zf);
		if (err != ZIP_OK) {
			printf("error in closing %s in the zipfile\n", file_inzip.c_str());
		}
	}
	return true;
}

bool zip_creator::close()
{
    int errclose = zipClose(zf, NULL);
	if (errclose != ZIP_OK) {
        printf("error in closing\n");
		return false;
	} else {
		return true;
	}
}