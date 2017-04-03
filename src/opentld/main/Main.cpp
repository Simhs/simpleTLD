#include "Main.h"
#include "ImAcq.h"
#include "Gui.h"

using namespace tld;
using namespace cv;


void Main::doWork(int debug_mode)
{
    //이부분이 Mat 데이터 가져와도 무방하다.
    IplImage *img = imAcqGetImg(imAcq);
    Mat grey(img->height, img->width, CV_8UC1);
    cvtColor(cvarrToMat(img), grey, CV_BGR2GRAY);
    // grey 영상 바로 할당 하면 빠를듯
    tld->detectorCascade->imgWidth = grey.cols;
    tld->detectorCascade->imgHeight = grey.rows;
    /*step 은 행row과 열col에서 사용하는 Byte 수를 저장한다.*/
    tld->detectorCascade->imgWidthStep = grey.step;

    while(imAcqHasMoreFrames(imAcq))
    {
        if (debug_mode == 1){
          gui->showImage(img);
          char key = gui->getKey();
          if(key == 'q'){ break; }
          if(key == 'c'){
              tld->release();
          }
          if(key == 'r')
          {
              CvRect box;
              if(mygetBBFromUser(img, box, gui,30,40,60,80) == PROGRAM_EXIT){ break; }
              Rect r = Rect(box);
              tld->selectObject(grey, &r);
          }
        }

        //이미지를 릴리즈 해준다.
        cvReleaseImage(&img);
        //새로운 이미지를 받아온다.
        img = imAcqGetImg(imAcq);
        //이미지 받기 실패 에러반환 작업종료status
        if(img == NULL)
        {
            printf("current image is NULL, assuming end of input.\n");
            break;
        }
        //그레이로 바꾼다.
        cvtColor(cvarrToMat(img), grey, CV_BGR2GRAY);


        // 여기가 핵심인듯하오 :  프레임을 TLD에 이미지프로세스 메소드에 넘기는듯하오
        tld->processImage(cvarrToMat(img));

        CvScalar yellow = CV_RGB(255, 0, 0);
        CvScalar blue = CV_RGB(0, 0, 255);
        CvScalar black = CV_RGB(0, 0, 0);
        CvScalar white = CV_RGB(255, 255, 255);

        if(tld->currBB != NULL)
        {
            //printf("%d\n",tld->currBB->tl().y);
            //std::cout<<tld->currBB->tl().x<<std::endl;
            //std::cout<<tld->currBB->tl().y<<std::endl;
            int lx = tld->currBB->tl().x;
            int ly = tld->currBB->tl().y;
            int rx = tld->currBB->br().x;
            int ry = tld->currBB->br().y;
            snprintf(message, sizeof(message), "3333/%04d/%04d/%04d/%04d", lx,ly,rx,ry);
            //std::cout<<message<<std::endl;
            write(sock, message, strlen(message));
            //snprintf(message, sizeof(message), "%3333/04d/%04d/%04d/%04d", lx,ly,rx,ry);
            //std::cout<<message<<std::endl;
            cvRectangle(img, tld->currBB->tl(), tld->currBB->br(), yellow, 8, 8, 0);
        }
        else{
            snprintf(message, sizeof(message), "4444/0000/0000/0000/0000");
            write(sock, message, strlen(message));
            //std::cout<<"loss tracking"<<std::endl;
        }

        str_len=read(sock, message, BUF_SIZE-1);
        message[str_len]=0;
        //printf("Message from server: %s\n", message);
        char *ptr;
        int tmp[5];
        ptr = strtok(message, "/");
        int i = 0;
        while(ptr != NULL ){
                tmp[i++]=atoi(ptr);
                ptr = strtok(NULL, "/");
        }
        if(tmp[0] == 0000){
          continue;
        }
        else if(tmp[0] == 1111){
          CvRect box;
          mygetBBFromUser(img, box, gui,tmp[1],tmp[2],tmp[3],tmp[4]);
          Rect r = Rect(box);
          tld->selectObject(grey, &r);
        }
        else if(tmp[0] == 2222){
          tld->release();
        }
        else if(tmp[0] == 3333){
          break;
        }
        //해동결정
        // normal / set / clear
        // normal protocol : 0000/0000/0000/0000/0000
        // set protocol : 1111/tlx/tly/brx/bry
        // clear protocol : 2222/0000/0000/0000/0000
        // exit protocol : 3333/0000/0000/0000/0000
        //std::cout<<"tmp[0] : "<<tmp[0]<<" tmp[1] : "<<tmp[1]<<" tmp[2] : "<<tmp[2]<<" tmp[3] : "<<tmp[3]<<" tmp[4] : "<<tmp[4]<<std::endl;

    }


    //이미지 메모리 반환
    cvReleaseImage(&img);
    img = NULL;

}
