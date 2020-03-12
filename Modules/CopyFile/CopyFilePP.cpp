/*  BEGIN_FILE_HDR
************************************************************************************************
*   NOTICE
*   Copyright (c) 2020 BurgessKzg All rights reserved.
************************************************************************************************
*   Author          : BurgessKzg
************************************************************************************************
*   File Name       : 
************************************************************************************************
*   Description     :
************************************************************************************************
*   Revision History* 
*     Version       Date       Initials       CR#          Descriptions
*    ---------   -----------  ------------  ----------  ----------------------------------------
*     1.0	      
************************************************************************************************
*   END_FILE_HDR */

#include <fstream>
#include <string>
#include <unistd.h>

using namespace std;

/*************************************************
  Function:       // 函数名称
  Description:    // 函数功能、性能等的描述
  Calls:          // 被本函数调用的函数清单
  Called By:      // 调用本函数的函数清单
  Input:          // 输入参数说明，包括每个参数的作用、取值说明及参数间关系。
  Output:         // 对输出参数的说明。
  Return:         // 函数返回值的说明
  Others:         // 其它说明
*************************************************/
bool CopyFilePP(const string &strDestFile, const string &strSrcFile)
{
  bool ret = true;
  ifstream calInFile;
  ofstream CalOutFile;
  char ucBuff[128] = {0};
  int32_t int32Cnt = 0;
  int64_t int64TotalSize = 0;
#ifdef PRINTF_INFORMATION
  int64_t int64LoadSize = 0;
  int8_t int8CurrPercent = 0;
  int8_t int8LastPercent = 0;
#endif

#ifdef PRINTF_INFORMATION
  printf("copy file %s to %s\n", strSrcFile.c_str(), strDestFile.c_str());
#endif

  do 
  {
    if (strSrcFile.empty() || strDestFile.empty()) 
	{
#ifdef PRINTF_INFORMATION
  	  printf("Source or destination file empty!\n");
#endif
      ret = false;
      break;
    }

    if (access(strSrcFile.c_str(), F_OK)) 
	{
#ifdef PRINTF_INFORMATION
  	  printf("No source file!\n");
#endif
      break;
    }

    if (strSrcFile == strDestFile) 
	{
#ifdef PRINTF_INFORMATION
  	  printf("The source and destination file are the same!\n");
#endif
      break;
    }

    calInFile.open(strSrcFile.c_str(),ios::binary);
    if (!calInFile.is_open()) 
	{
#ifdef PRINTF_INFORMATION
  	  printf("The source file open failed!\n");
#endif
      ret = false;
      break;
    }

    CalOutFile.open(strDestFile.c_str(),ios::binary|ios::trunc|ios::out);
    if (!CalOutFile.is_open()) 
	{
#ifdef PRINTF_INFORMATION
  	  printf("The destination file open failed!\n");
#endif
      calInFile.close();
      ret = false;
      break;
    }

    calInFile.seekg(0,calInFile.end);
    int64TotalSize = calInFile.tellg();
    if (int64TotalSize <= 0) 
	{
#ifdef PRINTF_INFORMATION
  	  printf("The source file size is null!\n");
#endif
      ret = false;
      break;
    }
    calInFile.seekg(0, calInFile.beg);

    while (!calInFile.eof()) 
	{
      calInFile.read(ucBuff, sizeof(ucBuff));
      int32Cnt = calInFile.gcount();
      CalOutFile.write(ucBuff,int32Cnt);
#ifdef PRINTF_INFORMATION
      int64LoadSize += int32Cnt;
      int8CurrPercent = ((int64LoadSize * 100) / int64TotalSize);
      if (int8LastPercent != int8CurrPercent)
	  {
        int8LastPercent = int8CurrPercent;
        printf("\rloading...%d%%\t",int8CurrPercent);
        if (int64LoadSize > 1024) 
		{
          printf("%dkB done.\n", (int32_t)(int64LoadSize/1024));
        } else 
		{
          printf("%dB done.\n", (int32_t)int64LoadSize);
        }
      }
#endif
    }

    calInFile.close();
    CalOutFile.close();

  } while (0);

  return ret;
}
