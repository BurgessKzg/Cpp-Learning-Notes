# 1. API

## 1.1. CopyFilePP
> - "bool CopyFilePP(const string &strDestFile, const string &strSrcFile)"
> - Description:
>   - Copy the contents of a file in a specified directory to a file in another specified directory.The directory can be either a decision path or a relative path, <font color=red>and the destination file is created if it does not exist.</font>
> - Para :
>   - strDestFile : copy after file(destination file) 
>   - strSrcFile : copy before file(source file)
> - Return :
>   - true : copy success
>   - false : copy failed

## 1.2. CopyFileNPP
> - bool CopyFileNPP(const string &strCopyFileName,const string &strDestPath, const string &strSrcPath)
> - Description:
> 	- Only Copy.
> - Para :
> 	- strCopyFileName ： File name
> 	- strDestPath : Destination path 
> 	- strSrcPath : Source path
> - Return :
> 	- true : copy success.
> 	- false : copy failed.

# 2. Compile
> - make(You can modify the Makefile to add a PRINTF_INFORMATION macro)

# 3. Example
**The test code is as follows**
```C++
#include "CopyFile.h"

int main(int argc,char* argv[])
{
    if(3 == argc)
    {
		 printf("Call CopyFilePP().\n");
         CopyFilePP(argv[1],argv[2]);

    }else if(4 == argc)
    {
		printf("Call CopyFileNPP().\n");
        CopyFileNPP(argv[1],argv[2],argv[3]);
    }else
    {
        printf("Please enter parameters correctly.\n");      
    }
	
	return 0;	
}
```
**Test method**
```C++
 1.  ./CopyFile CppCopy.bck CppCopy.cpp
 2.  ./CopyFile abc ~ abcPath
```
**Test result**
> An additional destination file appears in the destination directory.

# 4. Other
- Recommend to use "CopyFileNPP".
# 5. PS:
"%%" : The method that prints "%" in the printf function.
```C++
printf("\rloading...%d%%\t",int8CurrPercent);
```