#include "passwd.h"

void PASSWD::show_hex_buff(unsigned char buf[])
{
    int i;
    for (uint8_t i=0; i < crypto_secretstream_xchacha20poly1305_KEYBYTES; i++) 
        printf("%02X ", buf[i]);
    printf("\n");
}

const unsigned char* PASSWD::hash(QString password)
{
    /*std::string data = password.toStdString();
    
    unsigned char hash[crypto_generichash_BYTES];

    crypto_generichash(hash, sizeof hash,
                    (const unsigned char*)data.c_str(), data.size(),
                    NULL, 0);

    //qDebug() << PASSWD::convertToHexString(hash);
    return (const unsigned char*)hash;*/

    int length = password.length();
     
    char *sequence = NULL;
    sequence = new char[length+1];
    strncpy(sequence, password.toLocal8Bit(), length +1);

    #define MESSAGE ((const unsigned char *) sequence)
    #define MESSAGE_LEN length

    qDebug()<<"Generating cryptographic key from password: " <<sequence;
    unsigned char * sha256hash = new unsigned char[crypto_hash_sha256_BYTES];
    unsigned char * blacke2hash = new unsigned char[crypto_generichash_KEYBYTES];
    unsigned char * hash = new unsigned char[crypto_secretstream_xchacha20poly1305_KEYBYTES];

    crypto_hash_sha256(sha256hash, MESSAGE, MESSAGE_LEN);
    crypto_generichash(blacke2hash, sizeof hash, MESSAGE, MESSAGE_LEN, NULL, 0);

    for(uint8_t i = 0; i < crypto_secretstream_xchacha20poly1305_KEYBYTES/2; i++)
        hash[i] = blacke2hash[i];

    for(uint8_t i = crypto_secretstream_xchacha20poly1305_KEYBYTES/2; i < crypto_secretstream_xchacha20poly1305_KEYBYTES; i++)
        hash[i] = sha256hash[i];

    delete[] sha256hash;
    delete[] blacke2hash;
    qDebug()<<"secret key generated:\n";
    PASSWD::show_hex_buff(hash);
    return hash;
}