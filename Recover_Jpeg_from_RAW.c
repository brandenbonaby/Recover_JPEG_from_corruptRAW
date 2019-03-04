/* Program to recover jpeg files that are stored contiguously in a memory card. This assumes that the blocksize that
 * was used to store the files are 512 blocks apart. Also for this to work input should be a raw file. It is also assumed
 * that the jpeg file headers are at the start of the files and not at the end. Lastly place the .raw file in the same directory
 * as this file and note that the recovered files will appear in the current directory*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{

    //only allow 2 cmdline arguments
    if (argc != 2){
        fprintf(stderr,"Usage: ./recover image \n"); //print error message
        return 1;
    }
    //open the file for reading
    FILE *file = fopen(argv[1],"r");

    if (file == NULL){//confirm if file exists, if not print error
        fprintf(stderr,"Usage: ./recover image \n"); //print error message
        return 2;
    }

    FILE* jpeg = NULL;  // initialization of buffer for output file

    int a = 0;  //intializing a value to be used for outputfile

    char filename [8]; // create array of characters for output filename

    //allocate in memory signed int to hold value up to 512 bytes for blocks, needed to cover 4th block of jpeg
    unsigned  char *jpg = malloc(512);

    // create loop that will not stop until it gets to the end of the file
    while (!feof(file)){
        //start reading 512 byte block from input file
        if (a == 0){
            fread(jpg, 512, 1, file);
        }

        //when the first 4 bytes of the block looks like a jpeg block write to output file
        if (jpg[0] == 0xff && jpg[1] == 0xd8 && jpg[2] && (jpg[3] & 0xf0) == 0xe0){

            //create name for output file and make it writeable
            sprintf(filename,"%03i.jpg",a);
            jpeg = fopen(filename, "w");

            //write the block to the output file and continue to read next block from input file
            fwrite(jpg, 512, 1, jpeg);
            fread(jpg, 512, 1, file);

            //loop all blocks after currect jpeg starting block until the start of another jpeg file
            while(!(jpg[0] == 0xff && jpg[1] == 0xd8 && jpg[2] && (jpg[3] & 0xf0) == 0xe0)){

                if (feof(file)){ //stop loop if you hit the end of the file{
                    break;
                }
                //write the block to the output file and continue to read next block from input file
                fwrite(jpg, 512, 1, jpeg);
                fread(jpg, 512, 1, file);
            }

            //close output file and increment a value for next out put file name
            fclose(jpeg);
            a++;
        }
    }

    // clear memory in heap
    free(jpg);

    //close input file
    fclose(file);


    //program finished with no errors
    return 0;
}
