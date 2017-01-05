//
//  Printer.cpp
//  :
//
//  Created by Alec Adair on 1/3/17.
//  Copyright © 2017 Alec Adair. All rights reserved.
//

#include "Printer.hpp"

void Printer::print_intro(){
    std::cout << "================================================" << std::endl;
    std::cout << "< Sponsole - The Spotify interface for hackers >" << std::endl;
    std::cout << "================================================" << std::endl;
    std::cout << "    \\ " << std::endl;
    std::cout << "     \\   <`--'\\>______     Author: Alec Adair " <<std::endl;
    std::cout << "      \\  /* *  `'     \\"<<std::endl;
    std::cout << "        (oo)  ,        @@@      for usage type help" << std::endl;
    std::cout << "         `-._,        /'" << std::endl;
    std::cout << "            ( )_/--( )  '" << std::endl;
    std::cout << "            '''    '''  '" << std::endl;
  //  std::cout << "\n\tfor usage type help" << std::endl;
}

void Printer::print_status(){
    std::string play_state =  "osascript -e 'tell application \"Spotify\" to player state as string'";
    std::string cur_artist = "osascript -e 'tell application \"Spotify\" to artist of current track as string'";
    FILE* fd;
    fd = popen(play_state.c_str(),"r");
    char buff[512];
    if(fd){
        while(fgets(buff,sizeof(buff),fd)!= NULL){
            std::string result(buff);
            std::cout << result;
        }
    }else{
        std::cout << "Print Fail" << std::endl;
    }
    for(int i = 0; i < sizeof(buff); i ++){
        buff[i] = 0;
    }
    fd = popen(cur_artist.c_str(),"r");
    while(fgets(buff,sizeof(buff),fd)!= NULL){
        std::string result(buff);
        std::cout << result;
    }
    return;
}