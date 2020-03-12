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
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
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
bool CopyFileNPP(const string &strCopyFileName,const string &strDestPath, const string &strSrcPath)
{   
    bool bCpyFileFlag = false;
    ifstream calInFile;
    ofstream CalOutFile;
    string strDestFileAbsoPath(strDestPath);
    string strSrcFileAbsoPath(strSrcPath);
    string strOnlyCopyFileName("");
    size_t ulPos = 0;
	char ucBuff[256] = {0};
    int32_t int32Cnt = 0;
    int64_t int64TotalSize = 0;
#ifdef PRINTF_INFORMATION
    int64_t int64LoadSize = 0;
    int8_t int8CurrPercent = 0;
    int8_t int8LastPercent = 0;
#endif

	ulPos = strCopyFileName.find_last_of('/');
	if(ulPos != string::npos)
	{
		strOnlyCopyFileName = strCopyFileName.substr(ulPos + 1);
	}else
	{
		strOnlyCopyFileName = strCopyFileName;
	}

    if(strDestFileAbsoPath.find_last_of('/') != (strDestFileAbsoPath.size() - 1))
    {
        strDestFileAbsoPath += '/';
    }
    strDestFileAbsoPath += strOnlyCopyFileName;

    if(strSrcFileAbsoPath.find_last_of('/') != (strSrcFileAbsoPath.size() - 1))
    {
        strSrcFileAbsoPath += '/';
    }
    strSrcFileAbsoPath += strOnlyCopyFileName;

#ifdef PRINTF_INFORMATION
    printf("copy file %s to %s\n", strSrcFileAbsoPath.c_str(), strDestFileAbsoPath.c_str());
#endif

    do 
    {
        if (strSrcFileAbsoPath.empty() || strDestFileAbsoPath.empty()) 
        {
            printf("function:%s,%s,%d : Enter null the path and name of the source or destination file!\n",__FUNCTION__,__FILE__,__LINE__);
            break;
        }

        if (access(strSrcFileAbsoPath.c_str(), F_OK)) 
        {
            printf("function:%s,%s,%d : No source file!\n",__FUNCTION__,__FILE__,__LINE__);
            break;
        }

        if (strSrcFileAbsoPath == strDestFileAbsoPath) 
        {
            printf("function:%s,%s,%d : The path and name of the source and destination files are the same!\n",__FUNCTION__,__FILE__,__LINE__);
            break;
        }

        calInFile.open(strSrcFileAbsoPath.c_str(),ios::binary);
        if (!calInFile.is_open()) 
        {
            printf("function:%s,%s,%d : The source file open failed!\n",__FUNCTION__,__FILE__,__LINE__);
            break;
        }

        CalOutFile.open(strDestFileAbsoPath.c_str(),ios::binary|ios::trunc|ios::out);
        if (!CalOutFile.is_open()) 
        {
            printf("function:%s,%s,%d : The destination file open failed!\n",__FUNCTION__,__FILE__,__LINE__);
            calInFile.close();
            break;
        }

        calInFile.seekg(0,calInFile.end);
        int64TotalSize = calInFile.tellg();
        if (int64TotalSize <= 0) 
        {
            printf("function:%s,%s,%d : The source file size is zero!\n",__FUNCTION__,__FILE__,__LINE__);
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
		/* Modify execute file permission. */
		if(chmod(strDestFileAbsoPath.c_str(),S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH) != 0)
		{
			perror("Failed to modify file permissions.");
			break;
		}
#ifdef PRINTF_INFORMATION
    	printf("Modify execute file permission success!\n");
#endif
        bCpyFileFlag = true;
		calInFile.close();
        CalOutFile.close();
    } while (0);

    return bCpyFileFlag;
}
