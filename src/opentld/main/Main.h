/*  Copyright 2011 AIT Austrian Institute of Technology
*
*   This file is part of OpenTLD.
*
*   OpenTLD is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   OpenTLD is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with OpenTLD.  If not, see <http://www.gnu.org/licenses/>.
*
*/

/*
 * main.h
 *
 *  Created on: Nov 18, 2011
 *      Author: Georg Nebehay
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "TLD.h"
#include "ImAcq.h"
#include "Gui.h"



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>

#define BUF_SIZE 25
enum Retval
{
    PROGRAM_EXIT = 0,
    SUCCESS = 1
};

class Main
{
public:

    tld::TLD *tld;
    ImAcq *imAcq;
    tld::Gui *gui;
    double threshold;
    bool showForeground;
    bool showNotConfident;
    int *initialBB;
    bool reinit;
    bool exportModelAfterRun;
    bool loadModel;


    //const char *modelPath;
    //const char *modelExportFile;
    int seed;


    char message[BUF_SIZE];
    int sock;
    int str_len;
    struct sockaddr_in serv_adr;

    Main()
    {
        tld = new tld::TLD();
        initialBB = NULL;
        showNotConfident = true;
        reinit = 0;
        loadModel = false;
        exportModelAfterRun = false;
        seed = 0;
        gui = NULL;
        imAcq = NULL;

        sock=socket(PF_INET, SOCK_STREAM, 0);
        memset(&serv_adr, 0, sizeof(serv_adr));
        serv_adr.sin_family=AF_INET;
        serv_adr.sin_addr.s_addr=inet_addr("127.0.0.1");
        serv_adr.sin_port=htons(atoi("10000"));

        if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
          printf("non connected");
        else
          puts("Connected...........");

    }
    ~Main()
    {
        delete tld;
        imAcqFree(imAcq);
    }
    void doWork(int debug_mode);
};
#endif /* MAIN_H_ */
