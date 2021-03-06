#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <vector>

#include <iostream>

#include "helpers.h"
#include "parser.h"

int main(int argc, char **argv)
{
    if (argc < 2) {
        print_errors_and_exit("Need at least port");
    }

    std::string port{argv[1]};

    // For now following docRoot structure expected:
    // .
    // ├── server-certificate.pem
    // ├── server-private-key.pem
    // ├── server-public-key.pem
    // └── html
    //     ├── favicon.ico
    //     ├── miki.css
    //     ├── miki.html
    //     ├── miki.js
    //     ├── miki.wasm
    //     └── pages/

    std::string siteRoot{"./"};

    // TODO: Do it nicely
    // Site root must be ALWAYS normalized, i.e. end with '/'
    if (argc > 2) {
        siteRoot.assign(argv[2]);
        if (siteRoot[siteRoot.length() - 1] != '/')
           siteRoot += '/';
    }

    std::string certificatePath{"server-certificate.pem"};
    std::string privateKeyPath{"server-private-key.pem"};

    certificatePath.insert(0, siteRoot);
    privateKeyPath.insert(0, siteRoot);

#if OPENSSL_VERSION_NUMBER < 0x10100000L
    SSL_library_init();
    SSL_load_error_strings();
    auto ctx = UP<SSL_CTX>(SSL_CTX_new(SSLv23_method()));
#else
    auto ctx = UP<SSL_CTX>(SSL_CTX_new(TLS_method()));
    SSL_CTX_set_min_proto_version(ctx, TLS1_2_VERSION);
#endif

    if (SSL_CTX_use_certificate_file(ctx, certificatePath.c_str(), SSL_FILETYPE_PEM) <= 0) {
        print_errors_and_exit("Error loading server certificate");
    }
    if (SSL_CTX_use_PrivateKey_file(ctx,  privateKeyPath.c_str(), SSL_FILETYPE_PEM) <= 0) {
        print_errors_and_exit("Error loading server private key");
    }

    auto acceptBio = UP<BIO>(BIO_new_accept(port.c_str()));
    if (BIO_do_accept(acceptBio) <= 0) {
        print_errors_and_exit("Error in BIO_do_accept (binding to port 8080)");
    }

    static auto shutdown_the_socket = [fd = BIO_get_fd(acceptBio, nullptr)]() {
        close(fd);
    };
    signal(SIGINT, [](int) { shutdown_the_socket(); });

    while (auto bio = accept_new_tcp_connection(acceptBio)) {
        auto connectionBio = getUpper(std::move(bio), UP<BIO>(BIO_new_ssl(ctx, 0)));

        try {
            std::pair<std::string, std::string> request = receive_http_message(connectionBio);

            std::unique_ptr<Parser> pParser(new Parser(siteRoot + "html"));
            const auto [success, data] = pParser->parse(std::move(request));

            // Response
            if (std::holds_alternative<std::string>(data)) {
                send_http_response(connectionBio, success, std::get<std::string>(data));
            }
            else {
                send_http_response(connectionBio, success, std::get<std::vector<uint8_t>>(data));
            }
        }
        catch (const std::exception& ex) {
            printf("Worker exited with exception:\n%s\n", ex.what());
        }
    }
    printf("\nClean exit!\n");
}


