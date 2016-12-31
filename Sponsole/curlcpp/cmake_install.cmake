# Install script for directory: /Users/alecadair/Documents/SponsoleApp/Sponsole/Sponsole/curlcpp

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/Users/alecadair/Documents/SponsoleApp/Sponsole/Sponsole/curlcpp/include/cookie.h"
    "/Users/alecadair/Documents/SponsoleApp/Sponsole/Sponsole/curlcpp/include/cookie_date.h"
    "/Users/alecadair/Documents/SponsoleApp/Sponsole/Sponsole/curlcpp/include/cookie_datetime.h"
    "/Users/alecadair/Documents/SponsoleApp/Sponsole/Sponsole/curlcpp/include/cookie_time.h"
    "/Users/alecadair/Documents/SponsoleApp/Sponsole/Sponsole/curlcpp/include/curl_config.h"
    "/Users/alecadair/Documents/SponsoleApp/Sponsole/Sponsole/curlcpp/include/curl_cookie.h"
    "/Users/alecadair/Documents/SponsoleApp/Sponsole/Sponsole/curlcpp/include/curl_easy.h"
    "/Users/alecadair/Documents/SponsoleApp/Sponsole/Sponsole/curlcpp/include/curl_easy_info.h"
    "/Users/alecadair/Documents/SponsoleApp/Sponsole/Sponsole/curlcpp/include/curl_exception.h"
    "/Users/alecadair/Documents/SponsoleApp/Sponsole/Sponsole/curlcpp/include/curl_form.h"
    "/Users/alecadair/Documents/SponsoleApp/Sponsole/Sponsole/curlcpp/include/curl_global.h"
    "/Users/alecadair/Documents/SponsoleApp/Sponsole/Sponsole/curlcpp/include/curl_header.h"
    "/Users/alecadair/Documents/SponsoleApp/Sponsole/Sponsole/curlcpp/include/curl_info.h"
    "/Users/alecadair/Documents/SponsoleApp/Sponsole/Sponsole/curlcpp/include/curl_interface.h"
    "/Users/alecadair/Documents/SponsoleApp/Sponsole/Sponsole/curlcpp/include/curl_ios.h"
    "/Users/alecadair/Documents/SponsoleApp/Sponsole/Sponsole/curlcpp/include/curl_multi.h"
    "/Users/alecadair/Documents/SponsoleApp/Sponsole/Sponsole/curlcpp/include/curl_option.h"
    "/Users/alecadair/Documents/SponsoleApp/Sponsole/Sponsole/curlcpp/include/curl_pair.h"
    "/Users/alecadair/Documents/SponsoleApp/Sponsole/Sponsole/curlcpp/include/curl_receiver.h"
    "/Users/alecadair/Documents/SponsoleApp/Sponsole/Sponsole/curlcpp/include/curl_sender.h"
    "/Users/alecadair/Documents/SponsoleApp/Sponsole/Sponsole/curlcpp/include/curl_share.h"
    "/Users/alecadair/Documents/SponsoleApp/Sponsole/Sponsole/curlcpp/include/curl_utility.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/alecadair/Documents/SponsoleApp/Sponsole/Sponsole/curlcpp/src/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/alecadair/Documents/SponsoleApp/Sponsole/Sponsole/curlcpp/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
