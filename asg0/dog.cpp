#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <err.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    int fileDescriptor;
    char buff[32768] = "";
    size_t bytes = 1;
    size_t endOfFile = 1;
    int fileNumber = 1;
    //Changes fileNumber only if ./dog is typed
    if(argc == 1)
    {
    	fileNumber = 0;
    }
    //Checks the stdin for the key char "-" and then prints user input to stdout   
    while(argv[fileNumber] != NULL)
    {
        fileDescriptor = open(argv[fileNumber], O_RDONLY);
        if(strncmp(argv[fileNumber],"-", 1) == 0 || argc == 1)
        {
            while(true)
            {
                memset(buff, 0, sizeof buff);
                endOfFile = read(0, buff, sizeof(buff) - 1);
                //If the user types ctrl-D, stop reading from stdin
                if(endOfFile != 0)
                {
                    write(1, buff, sizeof(buff) - 1);
                }
                else
                {
                    break;
                }
            }
        }
        //If the the name is not a file and is not "-" print an error
        else if(fileDescriptor < 0 && strncmp(argv[fileNumber],"-", 1) != 0)
        {
           warn("%s", argv[fileNumber]); 
        }
        //If the file does exist print out the contents.
        else
        {
            while(bytes != 0)
            {
                memset(buff, 0, sizeof buff);
                bytes = read(fileDescriptor, buff, sizeof(buff) - 1);
                write(1, buff, bytes);
            }
            bytes = 1;
            close(fileDescriptor); 
        }
        fileNumber++;	
    }
    return 0;        
}
