//
//  HTTP_Socket.hpp
//  Sponsole
//
//  Created by Alec Adair on 12/15/16.
//  Copyright © 2016 Alec Adair. All rights reserved.
//

#ifndef HTTP_Socket_hpp
#define HTTP_Socket_hpp

#include <stdio.h>
#include <string>

class HTTP_Socket{
private:

    
public:
    char send_request(std::string);
    std::string receive_message();
};
#endif /* HTTP_Socket_hpp */
