// Nathan Vahrenberg
// CSE40567 Computer Security
// Homework 3

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>

#define USAGE_STRING "Usage: cipher [mode] [key] [IV] [input file] [output file]"
#define BUFSIZE 1028

#define VERBOSE 0

using namespace std;

// encrypt(), decrypt() and handleErrors() functions from the OpenSSL wiki:
// https://wiki.openssl.org/index.php/Libcrypto_API

void handleErrors(void){

  ERR_print_errors_fp(stderr);
  abort();

}

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
  unsigned char *iv, unsigned char *ciphertext){

  EVP_CIPHER_CTX *ctx;

  int len;

  int ciphertext_len;

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

  /* Initialise the encryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher
   * In this example we are using 256 bit AES (i.e. a 256 bit key). The
   * IV size for *most* modes is the same as the block size. For AES this
   * is 128 bits */
  if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    handleErrors();

  /* Provide the message to be encrypted, and obtain the encrypted output.
   * EVP_EncryptUpdate can be called multiple times if necessary
   */
  if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
    handleErrors();
  ciphertext_len = len;

  /* Finalise the encryption. Further ciphertext bytes may be written at
   * this stage.
   */
  if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
  ciphertext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return ciphertext_len;

}

int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
  unsigned char *iv, unsigned char *plaintext){

  EVP_CIPHER_CTX *ctx;

  int len;

  int plaintext_len;

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

  /* Initialise the decryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher
   * In this example we are using 256 bit AES (i.e. a 256 bit key). The
   * IV size for *most* modes is the same as the block size. For AES this
   * is 128 bits */
  if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    handleErrors();

  /* Provide the message to be decrypted, and obtain the plaintext output.
   * EVP_DecryptUpdate can be called multiple times if necessary
   */
  if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
    handleErrors();
  plaintext_len = len;

  /* Finalise the decryption. Further plaintext bytes may be written at
   * this stage.
   */
  if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) handleErrors();
  plaintext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return plaintext_len;

}

int main( int argc, char* argv[] ){

	// check if usage is at least close to correct
	if(argc < 6){
		cout << USAGE_STRING << endl;
		return 0;
	}

	// read paramaters
	string mode = argv[1];
	unsigned char *key = (unsigned char *) argv[2];
	unsigned char *iv = (unsigned char *) argv[3];
	char* input_file_name = argv[4];
	char* output_file_name = argv[5];

  // SSL initialization
  ERR_load_crypto_strings();
  OpenSSL_add_all_algorithms();
  OPENSSL_config(NULL);
  
  // define buffers for encryption
	unsigned char ciphertext[1024];
  unsigned char decryptedtext[1024];
	int decryptedtext_len, ciphertext_len;
  
  // open input stream
  ifstream input(input_file_name);

  // read in data
  // this is ugly but it works well for mangling the data into the format encrypt() needs
  stringstream buffer;
  buffer << input.rdbuf();
  char input_buffer[buffer.str().length()];
  buffer.str().copy(input_buffer, buffer.str().length());

  // open output stream
  ofstream output;
  streampos size;

	// mode: encrypt
	if( mode.compare("e")==0 || mode.compare("encrypt")==0 ){
		
    // outputs debug info if VERBOSE is set true above
    if(VERBOSE){
      cout << input_buffer << endl;
      cout << buffer.str().length() << endl;
    }

    // open output in binary mode
    output.open(output_file_name, ios::out | ios::binary);

		// encrypt
    ciphertext_len = encrypt ((unsigned char *)input_buffer, buffer.str().length(), key, iv, ciphertext);

    // write to file, needs to cast to keep data intact
    string cipherstring(reinterpret_cast<char*>(ciphertext), ciphertext_len);
    output << cipherstring;
  
  // mode: decrypt
  }else if( mode.compare("d")==0 || mode.compare("decrypt")==0 ){

    // outputs debug info if VERBOSE is set true above
    if(VERBOSE){      
      cout << input_buffer << endl;
      cout << buffer.str().length() << endl;
    }

    // open output
    output.open(output_file_name, ios::out);

		// decrypt
    decryptedtext_len = decrypt((unsigned char *)input_buffer, buffer.str().length(), key, iv, decryptedtext);
  	decryptedtext[decryptedtext_len] = '\0';

    // write to file
    output << decryptedtext;
  
  // unknown mode
  }else{

  	cout << "Unrecognized mode: " << mode << endl;
    cout << "Use \"encrypt\" or \"e\" for encryption, or \"decrypt\" or \"d\" for decryption" << endl;

  }
  
  // iostream cleanup
  input.close();
  output.close();

	// SSL cleanup
  EVP_cleanup();
  CRYPTO_cleanup_all_ex_data();
  ERR_free_strings();

  return 0;

}
