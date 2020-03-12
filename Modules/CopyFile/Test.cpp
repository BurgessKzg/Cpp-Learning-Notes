
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
