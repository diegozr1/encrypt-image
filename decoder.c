/*                      ITESM Campus Queretaro                           */
/* This program makes an exact copy of a digital file writing the result */
/* in a second one.   The user is prompted to insert the source and      */
/* destination files' name with their respective extension.              */
/* Author: Oscar Hernandez                                               */

# include <stdio.h>
# include <stdlib.h>

/* Label that defines a maximum value that controls the length of a string*/
# define MaxStr 256

/* The main function does not receive arguments as inputs. */
int main ()
{
FILE *SourceFile;
FILE *KeyFile;
FILE *DestFile;
unsigned char Buffer;
unsigned char Key;
unsigned char Header[54];

// Definition of string variables type that will store file's name
char SourceName [MaxStr];
char DestName [MaxStr];
char KeyName [MaxStr];
unsigned char highNibble;
unsigned char lowerNibble;
int pos=0;

  printf ("\nSource file name? ");
  gets (SourceName); 

	printf ("\nSource KEY file name? ");
  	gets (KeyName); 
  SourceFile=fopen (SourceName,"r+b");
  KeyFile=fopen (KeyName,"r+b");
  // Does the source file exist? Can the program open the content of the file?
  if ( SourceFile != NULL && KeyFile != NULL ) {
    // If the source file has been opened then open the destination file
    printf ("\nDestination file name? ");
    gets (DestName); 
    
    DestFile = fopen (DestName,"w+b");
    if ( DestFile != NULL ) {
      // while the end of the source file has not been reached, read one byte
      // at the time from the source file and then write it into the 
      // destination file.

	fseek(SourceFile, 0, SEEK_END); // seek to end of file
	int size = ftell(SourceFile)-53; // get current file pointer
	fseek(SourceFile, 0, SEEK_SET);

	fread (&Header,54,1,SourceFile);
	fwrite (&Header,54,1,DestFile);
	fread (&Header,54,1,KeyFile);

	unsigned char confussion[size];
      while ( fread (&Buffer,1,1,SourceFile) != 0 ) {
	
		
	
	if(fread (&Key,1,1,KeyFile) == 0 ){

		fseek(KeyFile, 0, SEEK_SET);
		fread (&Header,54,1,SourceFile);
		fread (&Key,1,1,KeyFile);
			
	}

	highNibble=Buffer >> 4;
	lowerNibble=Buffer & 0x0F;

	highNibble^=lowerNibble;
	lowerNibble^=(Key & 0x0F);
	
	highNibble=highNibble << 4;
	
	Buffer=highNibble+lowerNibble;

	confussion[pos]=Buffer;
	pos++;
	
		
        //fwrite (&Buffer,1,1,DestFile);
      }

	for(int i=0; i<size; i++){

		if(size%2==0){

			unsigned char aux=confussion[i];
			confussion[i]=confussion[i+1];
			confussion[i+1]=aux;
		
			fwrite (&confussion[i],1,1,DestFile);
		}
		else{
			size--;
		}			
	}
      fclose (DestFile);  // Close destination file to save its content.
    }
    else
      printf ("\nError: Destination file has not been created!!!");
    fclose (SourceFile); // Never leave a file open
    fclose (KeyFile); // Never leave a file open
  }
  else
    printf ("\nError: Source file does not exist !!");  
  printf ("\n\n\n");    
  system ("PAUSE");
  return (0);
}




