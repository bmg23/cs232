/* Homework 02: Using system calls from a C program
 * 
 * Goal: 
 *  Write a program in C that copies 
 *  the contents of one file to 
 *  another. 
 * 
 * Author: Brian Goins (bmg23) 
 * Date: 2/11/2020
 */  

/* References: 
 *  https://www.geeksforgeeks.org/c-program-copy-contents-one-file-another-file/
 *  https://www.gnu.org/software/libc/manual/html_node/Testing-File-Access.html
 * 
 */ 

/* Tests: 
 *  3 args in command line only
 *  Check if src file is readable
 *  Check if src and dest exist
 *  Check if file was opened 
 */ 


#include <stdio.h> 
#include <stdlib.h> // For exit() 
#include <unistd.h> //access
#include <sys/stat.h>
#include <errno.h>

  
int main(int argc, char* argv[]) 
{ 
    //ERROR 1: Check for too many or too little commands
    if (argc != 3) {
        fprintf(stderr, "Command line argument, failure. Usage: ./copy <src> <dest>\n"); 
        exit(-1); 
    }

    //ERROR 2: Command arguments are the same
    if( argv[1] == argv[2] ) {
        fprintf(stderr, "Source file and destination file are the same\n"); 
        exit(-1); 
    } 


    //ERROR 3: Does the src file exist? 
    if( access( argv[1], F_OK ) == -1 ) {
        fprintf(stderr, "Source file does not exist\n"); 
        exit(-1); 
    } 


    //ERROR 4: Check if normal file
    struct stat sb;
    stat(argv[1], &sb);
    if (!S_ISREG(sb.st_mode)) {
        fprintf(stderr, "Is not a regular file\n"); 
        exit(-1); 
    }


    //ERROR 5: Does the destination file exist? 
    if( access( argv[2], F_OK ) == 0 ) {
        fprintf(stderr, "Destination file already exists\n"); 
        exit(-1); 
    } 

        
    FILE *src, *dest;   

    if(stat(argv[1], &sb) == 0 && sb.st_mode & S_IXUSR) { //FIle is an executable

        char buff[BUFSIZ]; 
        src = fopen(argv[1], "rb"); 
        dest = fopen(argv[2], "wb");
        size_t n; 


        //ERROR 6: Cannot open file  
        if (src == NULL) 
        { 
            fprintf(stderr, "Source file can not be opened/n");
            exit(-1); 
        } 
    
        if (dest == NULL) 
        { 
            fprintf(stderr, "Destination file can not be opened/n");
            exit(-1); 
        } 


        while( (n=fread(buff,1,BUFSIZ, src)) != 0) {
            fwrite( buff, 1, n, dest); 
        }
        
        fclose(src); 
        fclose(dest); 

    } else { //Is a text file

        src = fopen(argv[1], "r"); 
        dest = fopen(argv[2], "w");

        //ERROR 6: Cannot open file  
        if (src == NULL) 
        { 
            fprintf(stderr, "Source file can not be opened/n");
            exit(-1); 
        } 
    
        if (dest == NULL) 
        { 
            fprintf(stderr, "Destination file can not be opened/n");
            exit(-1); 
        } 
        
        // Read contents from file 
        char c; 
        c = fgetc(src); 
        while (c != EOF) 
        { 
            fputc(c, dest); 
            c = fgetc(src); 
        } 
    
    
        fclose(src); 
        fclose(dest); 
    }

    return 0; 


}