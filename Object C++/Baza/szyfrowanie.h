#ifndef SZYFROWANIE_H
#define SZYFROWANIE_H
#include <sodium/crypto_hash_sha256.h>
#include <array>
#include <string>
#include <cstddef>
#include <fstream>

class Szyfrowanie
{
private:
    std::array<std::byte, 256> shaHaslo;
public:
    Szyfrowanie(){
        otworzHaslo("haslo");
    }
    void otworzHaslo(std::string filename) {
        std::ifstream haslo;
        haslo.open(filename, std::ios::binary);
        char *in = reinterpret_cast<char*>(shaHaslo.data());
        haslo.read(in, shaHaslo.size());
        haslo.close();
    }
    bool porownajSHA(std::string haslo){
        std::array<std::byte, 256> Haslo;
        unsigned char *hasloR = reinterpret_cast<unsigned char*>(haslo.data());
        unsigned char *hashHaslo = reinterpret_cast<unsigned char*>(Haslo.data());
        crypto_hash_sha256(hashHaslo, hasloR, sizeof(hasloR));

        /* użyto reinter reinterpret_cast<unsigned char*> z powodu problemów z porównywaniem std::byte */
        unsigned char *hashHasloS = reinterpret_cast<unsigned char*>(shaHaslo.data());
        if(*hashHaslo == *hashHasloS) { return true; }
        else { throw "Brak dostępu!"; return false; }

    }
    void zapiszHaslo(std::string haslo){
        std::array<std::byte, 256> Haslo;
        unsigned char *tmp = reinterpret_cast<unsigned char*>(Haslo.data());
        unsigned char *hasloR = reinterpret_cast<unsigned char*>(haslo.data());
        crypto_hash_sha256(tmp, hasloR, sizeof(hasloR));
        std::ofstream plik;
        plik.open("haslo", std::ios::binary);
        char *out = reinterpret_cast<char*>(Haslo.data());
        plik.write(out, Haslo.size());
        plik.close();
    }

};

#endif // SZYFROWANIE_H
