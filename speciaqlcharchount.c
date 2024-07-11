/*
 * specialcharcount.c - this file implements the specialcharcount function.
 */


#include <stdio.h>
#include "count.h"
#include <ctype.h>
#include <dirent.h>
#include <string.h>

void specialcharcount(char *path, char *filetowrite, long charfreq[]) {
    // open the directory
    DIR *d;
    struct dirent *dir;
    d = opendir(path);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (strstr(dir->d_name, ".txt")) {
                // Open the file
                char filepath[1024];
                snprintf(filepath, sizeof(filepath), "%s/%s", path, dir->d_name);
                FILE *file = fopen(filepath, "r");
                if (file) {
                    // Count the frequency of the special characters
                    char ch;
                    while ((ch = fgetc(file)) != EOF) {
                        switch (ch) {
                            case ',': charfreq[0]++; break;
                            case '.': charfreq[1]++; break;
                            case ':': charfreq[2]++; break;
                            case ';': charfreq[3]++; break;
                            case '!': charfreq[4]++; break;
                            default: break; // Ignore other characters
                        }
                    }
                    fclose(file);
                }
            }
        }
        closedir(d);
    }

    FILE *outfile = fopen(filetowrite, "w");
    if (outfile) {
        // Writing the frequencies in the specified format
        fprintf(outfile, ", -> %ld\n", charfreq[0]);
        fprintf(outfile, ". -> %ld\n", charfreq[1]);
        fprintf(outfile, ": -> %ld\n", charfreq[2]);
        fprintf(outfile, "; -> %ld\n", charfreq[3]);
        fprintf(outfile, "! -> %ld\n", charfreq[4]);
        fclose(outfile);
    }
}
/**
  The specialcharcount function counts the frequency of the following 5 special characters:
  ','   '.'   ':'    ';'    '!'
   
  in all the .txt files under directory of the given path and write the results to a file named as filetowrite.
  
  Input: 
  
      path - a pointer to a char string [a character array] specifying the path of the directory; and
      filetowrite - a pointer to a char string [a character array] specifying the file where results should be written in.
      alphabetfreq - a pointer to a long array storing the frequency of the above 5 special characters
      
      charfreq[0]: the frequency of ','
      charfreq[1]: the frequency of '.'
      charfreq[2]: the frequency of ':'
      charfreq[3]: the frequency of ';'
      charfreq[4]: the frequency of '!'

  
  Output: a new file named as filetowrite with the frequency of the above special characters written in
  
  Steps recommended to finish the function:
  1) Find all the files ending with .txt and store in filelist.
  2) Read all files in the filelist one by one and count the frequency of each alphabet letter only (a - z). The array 
  long alphabetfreq[] always has the up-to-date frequencies of alphabet letters counted so far. If the letter is upper case, convert
  it to lower case first. 
  3) Write the result in the output file: filetowrite in following format: 
  
     character -> frequency
     
     example:
     , -> 20
     . -> 11
     : -> 20
     ; -> 11
     ! -> 12     
     
  Assumption:  
  1) You can assume there is no sub-directory under the given path so you don't have to search the files 
  recursively.    
  2) Only .txt files are counted and other types of files should be ignored.
  
*/

