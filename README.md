# Recover_JPEG_from_corruptRAW

Program to recover jpeg files that are stored contiguously from a .raw file that is corrupt. 


<h2> Usage:</h2>

After you have compiled the program, use ./Recover_Jpeg_from_RAW filename.raw to execute on the cmdline shell.  

<h2>Sample Output:</h2>

**$ ./Recover_Jpeg_from_RAW    filename.raw**

<h2> Limitations: </h2>

This program assumes that the blocksize that was used to store the files are 512 blocks apart. Also for this to work input file should be a raw file. It is also assumed that the jpeg file headers are at the start/top of the each file and not at the end/bottom. Lastly place the .raw file in the same directory as this file and note that the recovered files will appear in the current directory and should be listed as 001.jpeg, 002.jpeg etc etc until the last one.
