#include <stdexcept>
#include <cstring>
#include "helpers.h"

// Debug
#include <iostream>

UP<BIO> getUpper(UP<BIO> lower, UP<BIO> upper)
{
    BIO_push(upper, lower.release());
    return upper;
}

[[noreturn]] 
void print_errors_and_exit(const char* message)
{
    fprintf(stderr, "%s\n", message);
    ERR_print_errors_fp(stderr);
    exit(1);
}

[[noreturn]] 
void print_errors_and_throw(const char* message)
{
    fprintf(stderr, "%s\n", message);
    ERR_print_errors_fp(stderr);
    throw std::runtime_error(std::string(message) + "\n" + message);
}

std::string receive_some_data(BIO* bio)
{
    char buffer[1024];
    int  len = BIO_read(bio, buffer, sizeof(buffer));
    if (len < 0) {
        print_errors_and_throw("error in BIO_read");
    }
    else if (len > 0) {
        return std::string(buffer, len);
    }
    else if (BIO_should_retry(bio)) {
        return receive_some_data(bio);
    }
    else {
        print_errors_and_throw("empty BIO_read");
    }
}

std::vector<std::string> split_headers(const std::string& text)
{
    std::vector<std::string> lines;
    const char*              start = text.c_str();
    while (const char* end = strstr(start, "\r\n")) {
        lines.push_back(std::string(start, end));
        start = end + 2;
    }
    return lines;
}

UP<BIO> accept_new_tcp_connection(BIO* accept_bio)
{
    if (BIO_do_accept(accept_bio) <= 0) {
        return UP<BIO>(nullptr);
    }
    return UP<BIO>(BIO_pop(accept_bio));
}

std::pair<std::string, std::string> receive_http_message(BIO* bio)
{
    std::string headers        = receive_some_data(bio);
    char*       end_of_headers = strstr(&headers[0], "\r\n\r\n");
    while (end_of_headers == nullptr) {
        headers += receive_some_data(bio);
        end_of_headers = strstr(&headers[0], "\r\n\r\n");
    }

    std::string body = std::string(end_of_headers + 4, &headers[headers.size()]);
    headers.resize(end_of_headers + 2 - &headers[0]);
    size_t content_length = 0;
    for (const std::string& line : split_headers(headers)) {
        if (const char* colon = strchr(line.c_str(), ':')) {
            auto header_name = std::string(&line[0], colon);
            if (header_name == "Content-Length") {
                content_length = std::stoul(colon + 1);
            }
        }
    }
    while (body.size() < content_length) {
        body += receive_some_data(bio);
    }

    return std::make_pair(headers, body);
}

void send_http_response(BIO* bio, const std::string& header, const std::string& body)
{
    BIO_write(bio, header.data(), header.size());
    BIO_write(bio, body.data(), body.size());
    BIO_flush(bio);
}

void send_http_response(BIO* bio, const std::string& header, const std::vector<u_int8_t>& body)
{
    BIO_write(bio, header.data(), header.size());
    BIO_write(bio, body.data(), body.size());
    BIO_flush(bio);
}
