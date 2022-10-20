/*
    Simple test program for libcrypto (OpenSSL) CMAC
    gcc test_cmac.c -lcrypto

	What CMAC is:
		https://en.wikipedia.org/wiki/CMAC
*/

#include <stdio.h>
#include <assert.h>

#include <openssl/evp.h>
#include <openssl/cmac.h>

#define _(x) assert((x))

/*
	Generate CMAC for a given key and message of a certain length.

	@param key:		secret key which is used to generate the cmac for the message (@param data)
	@parma data:	the message itself which needs to be tagged i.e. generated a CMAC for
	@param len:		length of the message (@param data) in bytes
	@param out:		the tag/CMAC itself as the output
	@param poutlen:	the length of the CMAC (@param out) in bytes
*/
void generate_cmac(unsigned char* key, unsigned char* data, size_t len, unsigned char* out, size_t *poutlen) {
	/*
	 	CMAC_CTX * CMAC_CTX_new(void);

		Allocates a new CMAC_CTX object, initializes the embedded 
		EVP_CIPHER_CTX object, and marks the object itself as uninitialized.
	*/
    CMAC_CTX *ctx = CMAC_CTX_new();
    _(ctx);

	/*
		int CMAC_Init(CMAC_CTX *ctx, const void *key, size_t key_len, const EVP_CIPHER *cipher, ENGINE *impl);

		Selects the given block cipher for use by ctx. Functions to obtain 
		suitable EVP_CIPHER objects are listed in the CIPHER LISTING section 
		of the EVP_Cipher(3) manual page. Unless key is NULL, CMAC_Init() 
		also initializes ctx for use with the given symmetric key that is 
		key_len bytes long. In particular, it calculates and internally stores 
		the two subkeys and initializes ctx for subsequently feeding in data 
		with CMAC_Update(). To use the default cipher implementations provided 
		by the library, pass NULL as the impl argument.
	*/
    _(CMAC_Init(ctx, key, 32, EVP_aes_256_cbc(), 0));

	/*
		int CMAC_Update(CMAC_CTX *ctx, const void *in_data, size_t in_len);

		Processes in_len bytes of input data pointed to by in_data. Depending 
		on the number of input bytes already cached in ctx, on in_len, and on
		the block size, this may encrypt zero or more blocks. Unless in_len 
		is zero, this function leaves at least one byte and at most one block
		of input cached but unprocessed inside the ctx object.
	*/
    _(CMAC_Update(ctx, data, len));

	/*
		int CMAC_Final(CMAC_CTX *ctx, unsigned char *out_mac, size_t *out_len);

		Stores the length of the message authentication code in bytes, 
		which equals the cipher block size, into *out_len. Unless out_mac
		is NULL, it encrypts the last block, padding it if required, and
		copies the resulting message authentication code to out_mac. The
		caller is responsible for providing a buffer of sufficient size.
	*/
    _(CMAC_Final(ctx, out, poutlen));

	/*
		void CMAC_CTX_free(CMAC_CTX *ctx);

		Zeros out both subkeys and all temporary data in ctx and in the
		embedded EVP_CIPHER_CTX object, frees all allocated memory
		associated with it, except for ctx itself, and marks it as
		uninitialized, such that it can be reused for subsequent CMAC_Init().
		Then frees ctx itself. If ctx is NULL, no action occurs.
	*/
    CMAC_CTX_free(ctx);
}

/*
	Compare equality for two byte arrays of a certain length.

	@param res:		byte array 1, the resultant array
	@param exp:		byte array 2, the expected array
*/
void validate_result(unsigned char* res, unsigned char* exp, size_t len) {
    for (int i = 0; i < len; i++) {
        _(res[i] == exp[i]);
    }
}

/*
	Print a byte array of a certain length in hex format
	
	@param buf:		byte array
	@param len:		length
*/
void print_bytes(unsigned char *buf, size_t len) {
    for (int i = 0; i < len; i++) {
        printf("%02x ", buf[i]);
    }
    printf("\n");
}

int main() {
    /*
        ref: https://csrc.nist.gov/publications/detail/sp/800-38b/archive/2005-05-01
        pdf: https://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-38b.pdf
        Appendix D: Examples
            D.3: AES-256
            Example 12: Mlen = 512
            K(key):
                603deb10 15ca71be 2b73aef0 857d7781
                1f352c07 3b6108d7 2d9810a3 0914dff4
            M(data):
                6bc1bee2 2e409f96 e93d7e11 7393172a
                ae2d8a57 1e03ac9c 9eb76fac 45af8e51
                30c81c46 a35ce411 e5fbc119 1a0a52ef
                f69f2445 df4f9b17 ad2b417b e66c3710
            T(cmac):
                e1992190 549f6ed5 696a2c05 6c315410
    */

    unsigned char key[] = {
        0x60, 0x3d, 0xeb, 0x10, 
        0x15, 0xca, 0x71, 0xbe, 
        0x2b, 0x73, 0xae, 0xf0, 
        0x85, 0x7d, 0x77, 0x81, 
        0x1f, 0x35, 0x2c, 0x07, 
        0x3b, 0x61, 0x08, 0xd7, 
        0x2d, 0x98, 0x10, 0xa3, 
        0x09, 0x14, 0xdf, 0xf4
    };

    unsigned char data[] = {
        0x6b, 0xc1, 0xbe, 0xe2, 
        0x2e, 0x40, 0x9f, 0x96, 
        0xe9, 0x3d, 0x7e, 0x11, 
        0x73, 0x93, 0x17, 0x2a, 
        0xae, 0x2d, 0x8a, 0x57, 
        0x1e, 0x03, 0xac, 0x9c, 
        0x9e, 0xb7, 0x6f, 0xac, 
        0x45, 0xaf, 0x8e, 0x51, 
        0x30, 0xc8, 0x1c, 0x46, 
        0xa3, 0x5c, 0xe4, 0x11, 
        0xe5, 0xfb, 0xc1, 0x19, 
        0x1a, 0x0a, 0x52, 0xef, 
        0xf6, 0x9f, 0x24, 0x45, 
        0xdf, 0x4f, 0x9b, 0x17, 
        0xad, 0x2b, 0x41, 0x7b, 
        0xe6, 0x6c, 0x37, 0x10
    };

    unsigned len = sizeof(data);

    unsigned char expected_result[] = {
        0xe1, 0x99, 0x21, 0x90, 
        0x54, 0x9f, 0x6e, 0xd5, 
        0x69, 0x6a, 0x2c, 0x05, 
        0x6c, 0x31, 0x54, 0x10
    };

    unsigned char result[16];
    size_t resultlen = 16;

    generate_cmac(key, data, len, result, &resultlen);

    _(sizeof(expected_result) == resultlen);
    validate_result(result, expected_result, resultlen);
    
    printf("CMAC: ");
    print_bytes(result, resultlen);

    return 0;
}
