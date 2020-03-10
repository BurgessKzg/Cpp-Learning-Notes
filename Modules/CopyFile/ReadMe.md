# CopyFile

## API
> - "bool CopyFile(const string &strDestFile, const string &strSrcFile)"
> - Description:
>   - Copy the contents of a file in a specified directory to a file in another specified directory.The directory can be either a decision path or a relative path, <font color=red>and the destination file is created if it does not exist.</font>
> - Para :
>   - strDestFile : copy after file(destination file) 
>   - strSrcFile : copy before file(source file)
> - Return :
>   - true : copy success
>   - false : copy failed
## Compile
g++ CopyFile.cpp -o CopyFile -std=c++11  
g++ CopyFile.cpp -o CopyFile -std=c++11 -D PRINTF_INFORMATION

## Example
**The test code is as follows**
```C++
int main(int argc,char* argv[])
{
	CopyFile(argv[1],argv[2]);

	return 0;
}
```
**Test method**
```C++
./CopyFile CppCopy.bck CppCopy.cpp
```
**Test result**
> An additional destination file appears in the current directory.
## PS:
"%%" : The method that prints "%" in the printf function.
```C++
printf("\rloading...%d%%\t",int8CurrPercent);
```