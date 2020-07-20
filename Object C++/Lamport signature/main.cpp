#include <iostream>
#include <sodium.h>
#include <sodium/crypto_hash_sha512.h>
#include <sodium/randombytes_internal_random.h>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/array.hpp>

struct Lamport_public_key{
    std::array<std::array<std::byte, 512>, 256> public_key_0;
    std::array<std::array<std::byte, 512>, 256> public_key_1;

};

struct Lamport_secret_key{
    std::array<std::array<std::byte, 512>, 256> secret_key_0;
    std::array<std::array<std::byte, 512>, 256> secret_key_1;

};

struct Lamport_key_pair{
    Lamport_public_key pub_key;
    Lamport_secret_key secret_key;
};

class Lamport{
public:
    Lamport_key_pair key_pair;
    std::string version;
    Lamport_key_pair save_key_pair(Lamport_key_pair k_pair, std::string secret_file, std::string public_file);
    void save_public_key(Lamport_public_key pub_key, std::string filename, const char* ver);
    void save_secret_key(Lamport_secret_key sec_key, std::string filename, const char* ver);
    void sign(std::string filename, std::string signature_file, std::string sec_file);
    void create_signature_file(std::array<std::array<std::byte, 512>, 256> signature, std::string filename);
    std::array<std::array<std::byte, 512>, 256> create_signature(std::array<std::byte, 512> hash_of_file, Lamport_secret_key sec_key);
    std::array<std::array<std::byte, 512>, 256> create_Bob_signature(std::array<std::byte, 512> hash_of_file, Lamport_public_key pub_key);
    std::array<std::array<std::byte, 512>, 256> open_signature_file(std::string filename);
    std::array<std::array<std::byte, 512>, 256> create_hashes_from_Alice_signature(std::array<std::array<std::byte, 512>, 256> signature_tab);
    bool compare_hashes(std::array<std::array<std::byte, 512>, 256> hash_from_alice_signature, std::array<std::array<std::byte, 512>, 256> hash_from_bob_signature);
    bool verify_sign(std::string filename, std::string signature_file, std::string file_pub);
    Lamport_public_key open_public_key(std::string filename);
    Lamport_secret_key open_secret_key(std::string filename);
    std::array<std::byte, 512> create_hash_of_file(std::string filename);
    Lamport_key_pair generate_key_pair();
private:
    Lamport_secret_key generate_secret_key();
    Lamport_public_key generate_public_key(Lamport_secret_key secret_key);
};

Lamport_secret_key Lamport::generate_secret_key() { //generating user Lamport secret key
    Lamport_secret_key secret_key;
    for (auto &i : secret_key.secret_key_0) {
        randombytes_buf(i.data(), i.size());
    }
    for (auto &t : secret_key.secret_key_1) {
        randombytes_buf(t.data(), t.size());
    }
    return secret_key;
}

Lamport_public_key Lamport::generate_public_key(Lamport_secret_key secret_key) { //generating user Lamport public key
    Lamport_public_key public_key;
    for (auto i = 0; i < secret_key.secret_key_0.size(); ++i) {
        std::array<std::byte, 512> tmp_pub;
        unsigned char *out = reinterpret_cast<unsigned char*>(tmp_pub.data());
        unsigned char *tmp_i = reinterpret_cast<unsigned char*>(secret_key.secret_key_0.data());
        crypto_hash_sha256(out, tmp_i, secret_key.secret_key_0.at(i).size());
        public_key.public_key_0.at(i) = tmp_pub;
    }
    for (auto i = 0; i < secret_key.secret_key_1.size(); ++i) {
        std::array<std::byte, 512> tmp_pub;
        unsigned char *out = reinterpret_cast<unsigned char*>(tmp_pub.data());
        unsigned char *tmp_i = reinterpret_cast<unsigned char*>(secret_key.secret_key_1.data());
        crypto_hash_sha256(out, tmp_i, secret_key.secret_key_1.at(i).size());
        public_key.public_key_1.at(i) = tmp_pub;
    }
    return public_key;
}

Lamport_key_pair Lamport::generate_key_pair() { //using generate_secret_key() and generate_public_key() to create key pair
    Lamport_key_pair key_pair;
    key_pair.secret_key = generate_secret_key();
    key_pair.pub_key = generate_public_key(key_pair.secret_key);
    return key_pair;
}

void Lamport::save_public_key(Lamport_public_key pub_key, std::string filename, const char* ver) {
    std::ofstream file_pub;
    file_pub.open(filename, std::ios::binary);
    file_pub.write(ver, sizeof (ver));
    for (auto &i : pub_key.public_key_0) {
        char *out = reinterpret_cast<char*>(i.data());
        file_pub.write(out, i.size());
    }
    for (auto &i : pub_key.public_key_1) {
        char *out = reinterpret_cast<char*>(i.data());
        file_pub.write(out, i.size());
    }
    file_pub.close();
}

void Lamport::save_secret_key(Lamport_secret_key sec_key, std::string filename, const char* ver) {
    std::ofstream file_sec;
    file_sec.open(filename, std::ios::binary);
    file_sec.write(ver, sizeof(ver));
    for (auto &i : sec_key.secret_key_0) {
        char *out = reinterpret_cast<char*>(i.data());
        file_sec.write(out, i.size());
    }
    for (auto &i : sec_key.secret_key_1) {
        char *out = reinterpret_cast<char*>(i.data());
        file_sec.write(out, i.size());
    }
    file_sec.close();
}

Lamport_key_pair Lamport::save_key_pair(Lamport_key_pair k_pair, std::string secret_file, std::string public_file) { //writing secret & public keys to separate files
    const char* ver = "1.0 sha256";
    save_public_key(k_pair.pub_key, public_file, ver);
    save_secret_key(k_pair.secret_key, secret_file, ver);
    return k_pair;
}

Lamport_public_key Lamport::open_public_key(std::string filename) {
    std::ifstream public_key_file;
    Lamport_public_key public_key;
    public_key_file.open(filename, std::ios::binary);
    char* ver;
    public_key_file.read(ver, 11);
    for(auto &i : public_key.public_key_0){
        char *in = reinterpret_cast<char*>(i.data());
        public_key_file.read(in, i.size());
    }
    for(auto &i : public_key.public_key_1){
        char *in = reinterpret_cast<char*>(i.data());
        public_key_file.read(in, i.size());
    }
    return public_key;
}

Lamport_secret_key Lamport::open_secret_key(std::string filename) {
    std::ifstream secret_key_file;
    Lamport_secret_key sec_key;
    secret_key_file.open(filename, std::ios::binary);
    char* ver;
    secret_key_file.read(ver, 11);
    for (auto &i : sec_key.secret_key_0){
        char *in = reinterpret_cast<char*>(i.data());
        secret_key_file.read(in, i.size());
    }
    for (auto &i : sec_key.secret_key_1){
        char *in = reinterpret_cast<char*>(i.data());
        secret_key_file.read(in, i.size());
    }
    return sec_key;
}

std::array<std::byte, 512> Lamport::create_hash_of_file(std::string filename){
    std::ifstream hashed_file;
    crypto_hash_sha512_state state;
    crypto_hash_sha512_init(&state);
    std::array<std::byte, 10> tmp_message;
    std::array<std::byte, 512> hash_of_file;
    unsigned char* out = reinterpret_cast<unsigned char*>(hash_of_file.data());
    hashed_file.open(filename, std::ios::in | std::ios::binary);
    do{
        char *in = reinterpret_cast<char*>(tmp_message.data());
        hashed_file.read(in, tmp_message.size());
        unsigned char *in_for_tab = reinterpret_cast<unsigned char*>(tmp_message.data());
        crypto_hash_sha512_update(&state, in_for_tab, tmp_message.size());
    } while (!hashed_file.eof());
    crypto_hash_sha512_final(&state, out);
    return hash_of_file;
}

void Lamport::create_signature_file(std::array<std::array<std::byte, 512>, 256> signature, std::string filename){
    std::ofstream file_sign;
    file_sign.open(filename, std::ios::binary);
    for (auto &i : signature) {
        char *out = reinterpret_cast<char*>(i.data());
        file_sign.write(out, i.size());
    }
    file_sign.close();
}

std::array<std::array<std::byte, 512>, 256> Lamport::create_signature(std::array<std::byte, 512> hash_of_file, Lamport_secret_key sec_key) {
    std::array<std::array<std::byte, 512>, 256> signature;
    std::byte zero{0};
    int index = 0;
    for(auto &i : hash_of_file) {
        if(i == zero) { //jeśli byte == 0, to wpisz do signature pierwszy ciąg z pary
            signature.at(index) = sec_key.secret_key_0.at(index);
        }
        else { //jeśli nie, to wpisz do signature drugi ciąg z pary
            signature.at(index) = sec_key.secret_key_1.at(index);
        }
        ++index;
    }
    return signature;
}

void Lamport::sign(std::string filename, std::string signature_file, std::string sec_file){
    Lamport_secret_key sec_key;
    sec_key = open_secret_key(sec_file);
    std::array<std::byte, 512> hash_of_file;
    hash_of_file = create_hash_of_file(filename);
    std::array<std::array<std::byte, 512>, 256> signature;
    signature = create_signature(hash_of_file, sec_key);
    create_signature_file(signature, signature_file);
}

std::array<std::array<std::byte, 512>, 256> Lamport::create_Bob_signature(std::array<std::byte, 512> hash_of_file, Lamport_public_key pub_key){
    std::array<std::array<std::byte, 512>, 256> signature;
    std::byte zero{0};
    int index = 0;
    for(auto &i : hash_of_file) {
        if(i == zero) { //jeśli byte == 0, to wpisz do signature pierwszy ciąg z pary
            signature.at(index) = pub_key.public_key_0.at(index);
        }
        else { //jeśli nie, to wpisz do signature drugi ciąg z pary
            signature.at(index) = pub_key.public_key_1.at(index);
        }
        ++index;
    }
    return signature;
}

std::array<std::array<std::byte, 512>, 256> Lamport::open_signature_file(std::string filename) {
    std::array<std::array<std::byte, 512>, 256> hash_tab;
    std::ifstream signature_file;
    signature_file.open(filename, std::ios::binary | std::ios::in);
    for(auto &i : hash_tab){
        char *in = reinterpret_cast<char*>(i.data());
        signature_file.read(in, i.size());
    }
    return hash_tab;
}

std::array<std::array<std::byte, 512>, 256> Lamport::create_hashes_from_Alice_signature(std::array<std::array<std::byte, 512>, 256> signature_tab) {
    std::array<std::array<std::byte, 512>, 256> hashes_from_alice_signature;
    for (auto i = 0; i < signature_tab.size(); ++i) {
        std::array<std::byte, 512> tmp_pub;
        unsigned char *out = reinterpret_cast<unsigned char*>(tmp_pub.data());
        unsigned char *tmp_i = reinterpret_cast<unsigned char*>(signature_tab.data());
        crypto_hash_sha256(out, tmp_i, signature_tab.at(i).size());
        hashes_from_alice_signature.at(i) = tmp_pub;
    }
    return hashes_from_alice_signature;
}

bool Lamport::compare_hashes(std::array<std::array<std::byte, 512>, 256> hash_from_alice_signature, std::array<std::array<std::byte, 512>, 256> hash_from_bob_signature) {
    for (auto i = 0; i < hash_from_alice_signature.size(); ++i) {
        unsigned char *hash_alice = reinterpret_cast<unsigned char*>(hash_from_alice_signature.data()->at(i));
        unsigned char *hash_bob = reinterpret_cast<unsigned char*>(hash_from_bob_signature.data()->at(i));
        if(hash_bob != hash_alice) return false;
        else return true;
    }
}

bool Lamport::verify_sign(std::string filename, std::string signature_file, std::string file_pub){
    Lamport_public_key pub_key;
    pub_key = open_public_key(file_pub);
    std::array<std::byte, 512> hash_of_message;
    hash_of_message = create_hash_of_file(filename);
    std::array<std::array<std::byte, 512>, 256> bob_signature, hashes_from_Alice_signature, alice_signature;
    bob_signature = create_Bob_signature(hash_of_message, pub_key);
    alice_signature = open_signature_file(signature_file);
    hashes_from_Alice_signature = create_hashes_from_Alice_signature(alice_signature);
    if(!compare_hashes(hashes_from_Alice_signature, bob_signature)) return false;
    else return true;
}

int main(int argc, char* argv[])
{
    if (sodium_init() == 0){
        try {
            if (!boost::filesystem::is_directory("myLamport/")){
                boost::filesystem::create_directory("myLamport/");
            }
        } catch (boost::filesystem::filesystem_error &err){
            std::cout << err.what() << std::endl;
        }
        Lamport lamport;
        try{
            if(argc == 4) {
                if(std::strcmp(argv[1], "1")) lamport.save_key_pair(lamport.key_pair, argv[2], argv[3]);
                if(std::strcmp(argv[1], "3")) {
                    if(!lamport.verify_sign(argv[1], argv[2], argv[3])) return 16;
                }
            }
            else if (argc == 5) {
                if(std::strcmp(argv[1], "2")) lamport.sign(argv[2], argv[3], argv[4]);
            }
        }
        catch(int err){
            std::cout << "Error" << err << std::endl;
        }
    }
    return 0;
}
