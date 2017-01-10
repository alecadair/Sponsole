//
//  main.cpp
//  Sponsole
//
//  Created by Alec Adair on 12/15/16.
//  Copyright © 2016 Alec Adair. All rights reserved.
//

#include <stdlib.h>
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <sstream>
#include <regex>
#include <vector>
#include "HTTP_Socket.hpp"
#include "CurlClass.hpp"
#include "Printer.hpp"

#define TRACK 0
#define ALBUM 1
#define ARTIST 2
#define PLAYLIST 3
#define PAUSED 1
#define PLAYING 0

using namespace std;

void parse_command(vector<string>);
static void play_song(string);
static void play_artist(string artist);
static void play_album(string album);
static void vol_up();
static void vol_down();
static void print_intro();
static void print_usage();
static void initiate_curl();
static string create_search_url(string,int);
static int get_volume();
static void set_volume(int);
static bool is_paused();
static void display_status();

//global variables
static CURL* my_handle;
static CURLcode result;
static int current_volume;
static bool paused;
int test = 0;

static bool is_paused(){
    FILE* fd;
    string command = "osascript -e 'tell application \"Spotify\" to player state as string'";
    char buff[512];
    fd = popen(command.c_str(),"r");
    if(fd){
        while(fgets(buff,sizeof(buff),fd) != NULL){
            string result(buff);
            if(!result.compare("paused\n"))
                return true;
            else if (!result.compare("playing\n"))
               return false;
            break;
        }
        return 0;
    }else{ cout << "could not create file descriptor"<<endl;
        return 0;}
}
static void set_volume(int vol){
    FILE* fd;
    string command = "osascript -e 'tell application \"Spotify\" to set sound volume to ";
    command.append(to_string(vol));
    command.append("'");
    char buff[512];
    fd = popen(command.c_str(),"r");
    if(fd)
        pclose(fd);
    current_volume = get_volume();
}

static int get_volume(){
    FILE* fp;
    string command_string = "osascript -e 'tell application \"Spotify\" to sound volume as integer'";
    char buff[512];
    int vol = 0;
    if(!(fp = popen(command_string.c_str(),"r"))){
        cout << "could not create file descriptor (popen)" << endl;
    }else{
      //  int vol = 0;
        while(fgets(buff,sizeof(buff),fp) != NULL){
            vol = atoi(buff);
            pclose(fp);
            break;
        }
      //  pclose(fp);
    }
    return vol;
}

static void vol_up(){
    if(current_volume < 90){
        current_volume += 10;
        set_volume(current_volume);
    }else{
        set_volume(100);
    }
}

static void vol_down(){
    if(current_volume > 10){
        current_volume -= 10;
        set_volume(current_volume);
    }else{
        set_volume(0);
        current_volume = 0;
    }
}
static string create_search_url(string query, int type){
    string url = "https://api.spotify.com/v1/search?q=";
    url.append(query);
    if(type == TRACK){
        url.append("&type=track&limit=1&offset=0");
    }else if(type == ARTIST){
        url.append("&type=artist&limit=1&offset=0");
    }else if (type == ALBUM){
        url.append("&type=album&limit=1&offset=0");
    }
    return url;
}

void parse_command(vector<string> command_line){
    if(!command_line[0].compare("help")){
        print_usage();
        return;
    }
    if(!command_line[0].compare("play")){
        if(command_line.size() == 1){
            if(paused){
                string play ="osascript -e 'tell application \"Spotify\" to playpause'";
                system(play.c_str());
                paused = PLAYING;
            }
            return;
        }
        if(!command_line[1].compare("artist")){
            string artist = "";
            for(int i = 2; i < command_line.size(); i++){
                artist.append(command_line[i]);
                if(i != (command_line.size() - 1)){
                    //artist.append("%20");
                    artist.append("+");
                }
            }
            play_artist(artist);
            return;
        }else if(!command_line[1].compare("album")){
            string album = "";
            for(int i = 2; i < command_line.size(); i++){
                album.append(command_line[i]);
                if(i != (command_line.size() -1)){
                    album.append("+");
                }
            }
            play_album(album);
            return;
        }else{
            string song = "";
        //string song = "\"";//command_line[1];
            for(int i = 1; i < command_line.size(); i++){
                song.append(command_line[i]);
                if(i != (command_line.size() - 1)){
                    //song.append(" ");
                    song.append("+");
                }
            }
            play_song(song);
        }
        return;
    }else if((!command_line[0].compare("next")) || (!command_line[0].compare("n"))){
        string play_next = "osascript -e 'tell app \"Spotify\" to next track'";
        system(play_next.c_str());
    }else if((!command_line[0].compare("prev"))/*|| (!command_line[0].compare("p"))*/){
        string play_prev = "osascript -e 'tell application \"Spotify\" to set player position to 0 previous track'";
        system(play_prev.c_str());
    }else if(!command_line[0].compare("q")
                            || !command_line[0].compare("quit")){
        exit(0);
        
    }else if (!command_line[0].compare("up")){
        vol_up();
    }else if(!command_line[0].compare("down")){
        vol_down();
    }else if(!command_line[0].compare("pause")){
        if(!paused){
            string pause = "osascript -e 'tell application \"Spotify\" to playpause'";
            system(pause.c_str());
            paused = PAUSED;
        }
    }else if(!command_line[0].compare("p")){
        if(paused == PAUSED)
            paused = PLAYING;
        else
            paused = PAUSED;
        string pauseplay = "osascript -e 'tell application \"Spotify\" to playpause'";
        system(pauseplay.c_str());
    }else if((!command_line[0].compare("stats")) || (!command_line[0].compare("stat"))
                                || (!command_line[0].compare("status"))){
        Printer p;
        p.print_status();
        return;
    }else if(!command_line[0].compare("vol")){
        //get_volume();
        if(command_line.size() > 1){
            if(!command_line[1].compare("up")){
                vol_up();
            }else if(!command_line[1].compare("down")){
                vol_down();
            }else{
                try{
                    int new_vol = stoi(command_line[1]);
                    current_volume = new_vol;
                    set_volume(current_volume);
                }catch(const invalid_argument& ia){
                    cerr<<"Invalid argument"<< endl;
                }
            }
        }
    }
}

static void play_album(string album){
    string search_query = create_search_url(album,ALBUM);
    CurlClass query_response;
    query_response.request_url((char*) search_query.c_str());
    cout << query_response.curl_msg;
    string response = query_response.curl_msg;
    regex rgx("spotify:album:[a-zA-Z0-9]+");
    smatch match;
    if(regex_search(response.cbegin(),response.cend(),match,rgx)){
        string result = match[0];
        cout << match[0] << endl;
    }else{
        cout << "Query Fault" << endl;
    }
    string result = "\"";
    result.append(match[0]);
    result.append("\"");
    string sys_command = "osascript -e 'tell app \"Spotify\" to play track ";
    sys_command.append(result);
    sys_command.append("'");
    system(sys_command.c_str());
    
}
static void play_song(string song){
  //  CurlClass song_query;
    string search_query = create_search_url(song, TRACK);
    CurlClass query_response;
    query_response.request_url((char*)search_query.c_str());
    cout << query_response.curl_msg;
    string response = query_response.curl_msg;
    regex rgx("spotify:track:[a-zA-Z0-9]+");
    smatch match;
    if(regex_search(response.cbegin(),response.cend(),match,rgx)){
        string result = match[0];
        cout << match[0] << endl;
    }else{
        cout << "Query Fault" << endl;
        return;
    }
    //regex reg("spotify:track:([a-zA-Z0-9]+)");
    //smatch mtch;
    string result = "\"";
    result.append(match[0]);
    result.append("\"");
    string sys_command = "osascript -e 'tell app \"Spotify\" to play track ";
    sys_command.append(result);
    sys_command.append("'");
    system(sys_command.c_str());   
}
static void play_artist(string artist){
    CurlClass query_response;
    string url = create_search_url(artist, ARTIST);
    query_response.request_url((char*)url.c_str());
    cout << query_response.curl_msg;
    string response = query_response.curl_msg;
    regex rgx("spotify:artist:[a-zA-Z0-9]+");
    smatch match;
    string artist_uri;
    if(regex_search(response.cbegin(),response.cend(),match,rgx)){
        string result = match[0];
        cout << match[0] << endl;
        artist_uri = match[0];
        //uri.append(match[0]);
    }else{
        cout << "Query Fault" << endl;
        return;
    }
    istringstream is(artist_uri);
    string token;
    for(int i = 0; i < 3; i ++){
        getline(is,token,':');
    }
    string result = "\"";
    result.append(artist_uri);
    result.append("\"");
    string sys_command = "osascript -e 'tell app \"Spotify\" to play track ";
    sys_command.append(result);
    sys_command.append("'");
    
    system(sys_command.c_str());
}
void print_usage(){
    cout << "Sponsole Usage"<< endl;
    cout << "play <Artist>\t\t//play artist starting with number one hit"<<endl;
    cout << "play <Song>\t//play Song, first query given by spotify will play"<<endl;;
    cout << "play <Artist> <Song>\t\t//play Song by Artist"<<endl;
    cout << "play <Album>\t\t//play Album, first query given by spotify will play"<<endl;
    cout << "play <Artist> <Album>\t//play Album by Artist"<<endl;
    cout << "play\t\t\\play current song if paused" << endl;
    cout << "pause\t\t//pause current song if playing" << endl;
    cout << "vol <up/down> or up/down\t\tturns the volume up and down respectively." << endl;
    cout << "vol <0-100>\t\tsets Spotify's volume to given level (only works for Spotify in Desktop Mode)."<< endl;
    cout << "next/prev\t\tplays the next or previous tracks in the Spotify queue."<< endl;
}

void initiate_curl(){
    curl_global_init(CURL_GLOBAL_ALL);
    my_handle = curl_easy_init();
    curl_easy_setopt(my_handle,CURLOPT_URL,"https://www.google.com");
    result = curl_easy_perform(my_handle);
    curl_easy_cleanup(my_handle);
}

void print_intro(){
    cout <<"Welcome to Sponsole\n"<<
    "Do you want to login using your Spotify login? (y/n)" << endl;
    
}

static void display_status(){
    
}

int main(int argc, const char * argv[]) {
    //sys init
    paused = is_paused();
    current_volume = get_volume();
    
    if(argc > 1){
        vector<string> argument;
        for(int i =1; i < argc; i ++){
            string toke = argv[i];
            argument.push_back(toke);
        }
        parse_command(argument);
        return 0;
    }
    Printer printer;
    //current_volume = get_volume();
    //cout << current_volume << endl;
    print_intro();
    string login;
    getline(cin,login);
    if((!login.compare("y")) || (!login.compare("yes"))){
        string user_name, password;
        cout << "Enter Spotify user name." <<endl;
        getline(cin,user_name);
        cout <<"Enter Spotify password."<<endl;
        getline(cin,password);
    }else if((!login.compare("n")) || (!login.compare("no"))){
       // cout << "will not login" << endl;
    }else{
       // cout << "did not answer correctly will not login" << endl;
    }
    //main loop
   // if(system("CLS"))
        system("clear");
    printer.print_intro();
    while(1){
        cout << "Sponsole > ";
        vector<string> command_line;
        string command;
        getline(cin,command);
        stringstream ss(command);
        string token;
        while(ss >> token){
            command_line.push_back(token);
        }
        if(command_line.size() > 0){
            parse_command(command_line);
        }
       // }
    }
    return 0;
}
