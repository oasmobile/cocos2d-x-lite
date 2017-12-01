
#ifndef __Crypto_H__
#define __Crypto_H__

#include "cocos2d.h"
#include <string>

using namespace std;
using namespace cocos2d;


USING_NS_CC;

class Crypto
{
public:
    static const int MD5_BUFFER_LENGTH = 32;
    
//    /** @brief Encrypt data with XXTEA algorithm, return ciphertext, free ciphertext after used */
//    static const std::string encryptXXTEA(const char* plaintext,
//                                       int plaintextLength,
//                                       const char* key,
//                                       int keyLength);
//    
//    /** @brief Decrypt data with XXTEA algorithm, return plaintext, free plaintext after used */
//    static const std::string decryptXXTEA(const char* ciphertext,
//                                       int ciphertextLength,
//                                       const char* key,
//                                       int keyLength);

    /** @brief Get length of encoding data with Base64 algorithm */
    static int encodeBase64Len(const char* input, int inputLength);
    
    /** @brief Encoding data with Base64 algorithm, return encoded string length */
    static const std::string encodeBase64(const char* input, int inputLength, int outputBufferLength);
    
    /** @brief Get length of Decoding Base 64 */
    static int decodeBase64Len(const char* input);

    /** @brief Decoding Base64 string to data, return decoded data length */
    static const std::string decodeBase64(const char* input, int outputBufferLength);
    
    /** @brief Calculate MD5, get MD5 code (not string) */
    static void MD5(void* input, int inputLength,
                    unsigned char* output);
    
    static const char* MD5File(const char* path);
    
//    static std::string Crypto::md5_string(const std::string &inputStr, bool rawOutput/* = false*/);
//    static const std::string MD5String(void* input, int inputLength);
    
    static char* bin2hex(unsigned char* bin, int binLength);

    
private:
    Crypto(void) {}
    
    static const std::string unsignedcharToString(unsigned char* ch, int Length);
    
};


#endif // __Crypto_H__
