//
//  CurlClass.hpp
//  Sponsole
//
//  Created by Alec Adair on 12/15/16.
//  Copyright © 2016 Alec Adair. All rights reserved.
//

#ifndef CurlClass_hpp
#define CurlClass_hpp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

/*Struct for receiving curl output*/
typedef struct curl_buffer{
    char* curl_msg;
    size_t size;
}curl_buffer;

class CurlClass{
public:
    //curl_buffer buffer;
    CURL* my_handle;
    CURLcode result;
    char* curl_msg;
    size_t msg_size;
    
    CurlClass();
    static size_t write_to_curl_buffer(char* ptr, size_t size,
                                       size_t nmemb, void* data);
    void request_url(char*);
    void clean(CURL*);
    
    
};
#endif /* CurlClass_hpp */
