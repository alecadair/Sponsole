//
//  CurlClass.cpp
//  Sponsole
//
//  Created by Alec Adair on 12/15/16.
//  Copyright © 2016 Alec Adair. All rights reserved.
//

#include "CurlClass.hpp"

CurlClass::CurlClass(){
    this->curl_msg = 0;
    this->msg_size = 0;
    curl_global_init(CURL_GLOBAL_ALL);
    my_handle = curl_easy_init();
    curl_easy_setopt(my_handle,CURLOPT_WRITEFUNCTION,(void*) CurlClass::write_to_curl_buffer);
    curl_easy_setopt(my_handle,CURLOPT_WRITEDATA,(void*)this);
}

void CurlClass::clean(CURL* handle){
   // curl_easy_cleanup(handle);
}

size_t CurlClass::write_to_curl_buffer(char* ptr, size_t size,
                            size_t nmemb, void* data){
    size_t adj_size = size*nmemb;
    CurlClass* mem = (CurlClass*) data;
  //  mem->curl_msg = std::realloc();
    if(mem->curl_msg)
        mem->curl_msg = (char*)realloc(mem->curl_msg, mem->msg_size + adj_size + 1);
    else
        mem->curl_msg = (char*)malloc(mem->msg_size + adj_size + 1);
    
    if(mem->curl_msg){
        memcpy(&(mem->curl_msg[mem->msg_size]),ptr,adj_size);
        mem->msg_size += adj_size;
        mem->curl_msg[mem->msg_size] = 0;
    }
    return adj_size;
}

void CurlClass::request_url(char* url){
    curl_easy_setopt(my_handle,CURLOPT_URL,url);
    result = curl_easy_perform(my_handle);
    /*may not need this line*/
    curl_easy_cleanup(my_handle);
}