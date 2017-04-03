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

/**
  * @author Georg Nebehay
  */

#include "Main.h"
#include "ImAcq.h"
#include "Gui.h"



/*
#define LOG_LEVEL 0

#define PRINT_LOG_LEVEL_0(m) (0>=LOG_LEVEL)?fprintf(#m)
#define PRINT_LOG_LEVEL_1(m) (1>=LOG_LEVEL)?fprintf(#m)
#define PRINT_LOG_LEVEL_2(m) (2>=LOG_LEVEL)?fprintf(#m)
#define PRINT_LOG_LEVEL_3(m) (3>=LOG_LEVEL)?fprintf(#m)
*/




using tld::Gui;
//   ./opentld debug p1 p2 p3 p4
int main(int argc, char **argv)
{
    int debug_mode = atoi(argv[1]);
    

    // main.cpp 안에는 doWork()가있다.
    Main *main = new Main();

    // 장치 읽기 캠캠캠 imread()같은 것을 모아둠!
    ImAcq *imAcq = imAcqAlloc();
    // cv 윈도우창을 사용하는데 옛날버전이네
    Gui *gui = new Gui();

    //main에 gui끼워넣기 && main에 카메라장치 끼워넣기
    main->gui = gui;
    main->imAcq = imAcq;

    imAcqInit(imAcq);
    gui->init();
    main->doWork(debug_mode);

    delete main;
    main = NULL;
    delete gui;
    gui = NULL;

    return EXIT_SUCCESS;
}
