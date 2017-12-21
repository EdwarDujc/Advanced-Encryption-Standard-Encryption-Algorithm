/*C*****************************************************************************
* NAME:         main.c
* AES(Advanced Encryption Standard)Encryption Algorithm 
* NOTES:        Running Mode£ºCBC (Ciphertext Block Chaining)
*				plaintext£º128000 bits
*				ciphertext£º128000 bits
* File:			plaintext.txt		
*				ciphertext.txt	
*				decry.txt	
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "AES_Lib.h"
#include <time.h>

 AES_U8 key[16];
 AES_U8 M[1000][16];		//a 1000*16 array for keeping plaintext
 AES_U8 C[1000][16];		//a 1000*16 array for keeping ciphertext
 AES_U8 Mr[1000][16];		//a 1000*16 array for keeping decrypted plaintext

int main(int argc, char *argv[])
{   
    AES_U8  expKey[4 * Nc * (Nr + 1)];  //a 4*4*(10+1) array for keeping expanded keys
	AES_U8 temp[16];
	int i,j;
	
	FILE *fc =NULL;
	FILE *fp =NULL;
	FILE *fd =NULL;
	fopen_s ( &fc,"ciphertext.txt","wb" );
	fopen_s ( &fp,"plaintext.txt","wb" );
	fopen_s ( &fd,"decry.txt","wb" );
    
	printf("Please input keys: (16 hexadecimal numbers, splitted by space)\n\n");	//user input keys manually
	for ( i = 0 ; i < 16 ; i ++ )
		scanf_s( "%x",&key[i] );
	
	AES_ExpandKey (key, expKey);	//key expansion
	srand((unsigned)time(NULL));	
	for(j=0;j<=15;j++)				//array random initialization
		C[0][j]=rand()%256;			
	for(i=0;i<1000;i++)				//loop 1000 times£¬generate 128 bits plaintext each time£¬encrypt in CBC mode
	{
		for(j=0;j<=15;j++)
		{
			M[i][j]=rand()%256;
			fprintf( fp,"%x",M[i][j]);	//write plaintext into plaintext.txt
			temp[j]=M[i][j]^C[i-1][j];
		}
		fprintf( fp,"\n");
		AES_Encrypt (temp, expKey, C[i]);
		for(j=0;j<=15;j++)				//write ciphertext into ciphertext.txt
			fprintf( fc,"%x",C[i][j]);	
		fprintf( fc,"\n");
	}
	
	for(i=0;i<1000;i++)				//loop 1000 times£¬read ciphertext in array C[][]£¬decrypt in CBC mode
	{
		AES_Decrypt (C[i], expKey, Mr[i]);
		for(j=0;j<=15;j++)
		{
			Mr[i][j]=Mr[i][j]^C[i-1][j];
			fprintf( fd,"%x",Mr[i][j]);	//write decrypted plaintext into decry.txt	
		}
		fprintf( fd,"\n");
	}
  fclose(fp);
  fclose(fc);
  fclose(fd);
  system("PAUSE");	
  return 0;
} 
