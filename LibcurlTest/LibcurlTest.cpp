// LibcurlTest.cpp : Defines the entry point for the console application.
//

#include <cstdlib>
#include <iostream>
#include <string>
#include "curl.h"
#include "json/json.h"
#include "CharacterDetail.h"
#include "JsonSerializer.h"

std::string data; //will hold the url's contents

size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up)
{ //callback must have this declaration
  //buf is a pointer to the data that curl has for us
  //size*nmemb is the size of the buffer

   for (UINT i = 0; i < (size * nmemb); ++i)
   {
      data.push_back(buf[i]);
   }
   return (size * nmemb); //tell curl how many bytes we handled
}


void parseJsonString()
{
   CharacterDetail charDetail;
   CJsonSerializer::Deserialize(&charDetail, data);
   std::cout << "Done parsing" << std::endl;
}

int main()
{
   CURL* curl; //our curl object

   curl_global_init(CURL_GLOBAL_ALL); //pretty obvious
   curl = curl_easy_init();

   curl_easy_setopt(curl, CURLOPT_URL, "http://gateway.marvel.com:80/v1/public/characters?limit=2&offset=41&apikey=a1b90cc88dd35e587205574bc1d6cc68&ts=1447555486&hash=6e43df36243a734a6779c19da819ba59");
   //curl_easy_setopt(curl, CURLOPT_URL, "http://www.example.com/path");
   curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
   curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); //tell curl to output its progress

   curl_easy_perform(curl);

   //std::cout << std::endl << data << std::endl;
   //std::cin.get();

   curl_easy_cleanup(curl);
   curl_global_cleanup();

   parseJsonString();

   return 0;
}

