#ifndef __USES_HELPERS_H__
#define __USES_HELPERS_H__
#include <memory>
#include <vector>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/ssl.h>

template<typename T> 
class UP
{
    std::unique_ptr<T> upT;
public:
    UP(T){};

    operator T*() { return upT.get(); }
};

template<> 
class UP<BIO>
{
    using BIODeleterType = void (*)(BIO*);  
    std::unique_ptr<BIO, BIODeleterType> upBIO;
public:
    UP<BIO>(BIO* pBIO) 
        :upBIO(pBIO, [](BIO* pBIO) { BIO_free_all(pBIO); })
    { }

    operator BIO*() { return upBIO.get(); }
    BIO* release() { return upBIO.release(); }
};

template<>
class UP<BIO_METHOD>
{
    using BIOMethodDeleterType = void (*)(BIO_METHOD*);
    std::unique_ptr<BIO_METHOD, BIOMethodDeleterType> upBIOMethod;
public:
    UP<BIO_METHOD>(BIO_METHOD* pBIOMethod)
        : upBIOMethod(pBIOMethod, [](BIO_METHOD* bm) { BIO_meth_free(bm); })
    {}

    operator BIO_METHOD*() { return upBIOMethod.get(); }
};

template<>
class UP<SSL_CTX>
{
    using SSLCTXDeleterType = void (*)(SSL_CTX*);
    std::unique_ptr<SSL_CTX, SSLCTXDeleterType> upSSLCTX;
public:
    UP<SSL_CTX>(SSL_CTX* ctx)
        : upSSLCTX(ctx, [](SSL_CTX* ctx) { SSL_CTX_free(ctx); })
    {}

    operator SSL_CTX*() { return upSSLCTX.get(); }
};

UP<BIO> getUpper(UP<BIO> lower, UP<BIO> upper);

[[noreturn]] void print_errors_and_exit(const char* message);
[[noreturn]] void print_errors_and_throw(const char* message);

std::string receive_some_data(BIO* bio);
std::vector<std::string> split_headers(const std::string& text);

UP<BIO> accept_new_tcp_connection(BIO* accept_bio);
std::pair<std::string, std::string> receive_http_message(BIO* bio);
void send_http_response(BIO* bio, bool success, const std::string& body);

#endif
