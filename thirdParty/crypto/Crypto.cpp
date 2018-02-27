
#include "Crypto.h"
#include "xxtea/xxtea.h"
extern "C" {
//#include "crypto/base64/libb64.h"
#include "base64/libbase64.h"
#include "md5/md5.h"
}

//NS_CC_EXTRA_BEGIN

//const string Crypto::encryptXXTEA(const char* plaintext,
//                                      int plaintextLength,
//                                      const char* key,
//                                      int keyength)
//{
//    xxtea_long len;
//    unsigned char* result = xxtea_encrypt((unsigned char *)plaintext, (xxtea_long)plaintextLength, (unsigned char *)key, (xxtea_long)keyLength, &len);
//    
//    return unsignedcharToString(result, len);
//}
//
//const string Crypto::decryptXXTEA(const char* ciphertext,
//                                      int ciphertextLength,
//                                      const char* key,
//                                      int keyLength)
//{
//    xxtea_long len;
//    unsigned char* result = xxtea_decrypt((unsigned char *)ciphertext, (xxtea_long)ciphertextLength, (unsigned char *)key, (xxtea_long)keyLength, &len);
//
//    return unsignedcharToString(result, len);
//}

int Crypto::encodeBase64Len(const char* input, int inputLength)
{
    return Base64encode_len(inputLength);
}

const string Crypto::encodeBase64(const char* input,
                           int inputLength,
                           int outputBufferLength)
{
    CCAssert(Base64encode_len(inputLength) <= outputBufferLength, "Crypto::encodeBase64() - outputBufferLength too small");
    
    char output[outputBufferLength];
    Base64encode(output, input, inputLength);
    
    return unsignedcharToString((unsigned char*)output, outputBufferLength);
    
}

int Crypto::decodeBase64Len(const char* input)
{
    return Base64decode_len(input);
}

const string Crypto::decodeBase64(const char* input,
                           int outputBufferLength)
{
    CCAssert(Base64decode_len(input) <= outputBufferLength, "Crypto::decodeBase64() - outputBufferLength too small");
    
    char output[outputBufferLength];
    Base64decode(output, input);
    
    return unsignedcharToString((unsigned char*)output, outputBufferLength);
}

void Crypto::MD5(void* input, int inputLength, unsigned char* output)
{
    MD5_CTX ctx;
    MD5_Init(&ctx);
    MD5_Update(&ctx, input, inputLength);
    MD5_Final(output, &ctx);
}

const char* Crypto::MD5File(const char* path)
{
    
    unsigned char buff[MD5_BUFFER_LENGTH];
    Data filedata = FileUtils::getInstance()->getDataFromFile(path); //for Android assert
    Crypto::MD5(filedata.getBytes(), int(filedata.getSize()), buff);
    char *ch = Crypto::bin2hex(buff, MD5_BUFFER_LENGTH);
    
    return ch;
}


char* Crypto::bin2hex(unsigned char* bin, int binLength)
{
    static const char* hextable = "0123456789abcdef";
    
    int hexLength = binLength * 2 + 1;
    char* hex = new char[hexLength];
    memset(hex, 0, sizeof(char) * hexLength);
    
    int ci = 0;
    for (int i = 0; i < 16; ++i)
    {
        unsigned char c = bin[i];
        hex[ci++] = hextable[(c >> 4) & 0x0f];
        hex[ci++] = hextable[c & 0x0f];
    }
    
    return hex;
}

const string Crypto::unsignedcharToString(unsigned char* ch, int Length)
{
    char* strTemp = new char[Length];
    memcpy(strTemp, ch, Length);
    std::string ret = strTemp;
    delete[] strTemp;
    return ret;
}

//NS_CC_EXTRA_END
