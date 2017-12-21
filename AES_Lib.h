#ifndef AES_LIB_H
#define AES_LIB_H

#include <string.h>

typedef unsigned char AES_U8;
typedef unsigned int  AES_U16;

#define CODE_MEM_TYP  code

#define Nc (4)          // state table and expandkey table column number
#define Nr (10)         // encryption round numbers


/*_____ D E F I N I T I O N __________________________________________________*/

/*_____ D E C L A R A T I O N ________________________________________________*/

void AES_ExpandKey(AES_U8 *key, AES_U8 *expKey);  //expand key
void AES_Encrypt(AES_U8 *in, AES_U8 *expKey, AES_U8 *out);  //128 bytes encryption
void AES_Decrypt(AES_U8 *in, AES_U8 *expKey, AES_U8 *out);	//128 bytes decryption

#endif /*AES_LIB_H*/
