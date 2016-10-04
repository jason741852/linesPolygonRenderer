#include <iostream>
#include <math.h>
#include <QTextStream>
#include <iostream>
#include "client.h"

# define PI  3.14159265358979323846  /* pi */

Client::Client(Drawable *drawable)
{
    this->drawable = drawable;
}


void Client::nextPage() {
    static int pageNumber = 0;
    pageNumber++;
    std::cout << "PageNumber " << pageNumber << std::endl;

    switch(pageNumber % 4) {
    case 1:
        draw_rect(0, 0, 750, 750, 0xffff0080);
        draw_rect( 50,  50, 350, 350, 0xff00ff40);
        draw_rect(400,  50, 700, 350, 0xff40ff00);
        draw_rect( 50, 400, 350, 700, 0xffff8000);
        draw_rect(400, 400, 700, 700, 0xffffff00);
        starburstPoints(1);
        drawable->updateScreen();   // you must call this to make the display change.
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        // fall through...
    default:
        draw_rect(0, 0, 750, 750, 0xffffffff);
        draw_rect(400, 400, 700, 700, 0xff00ff40);
        drawable->updateScreen();
    }
}

void Client::draw_rect(int x1, int y1, int x2, int y2, unsigned int color) {
    for(int x = x1; x<x2; x++) {
        for(int y=y1; y<y2; y++) {
            drawable->setPixel(x, y, color);
        }
    }
}

void Client::DDA(float x1, float y1, float x2, float y2, unsigned int color){
    float dx = x2-x1;
    float dy = y2-y1;
    float m = (float)dy/(float)dx;
    float b = y1-m*x1;
    float y;
    QTextStream(stdout)<<"(x1,y1)=("<<x1<<","<<y1<<"),(x2,y2)=("<<x2<<","<<y2<<"), m= "<<m<<endl;
    // check slope to see which octant
    if(abs(m)>=0 && abs(m)<1)
    {
        //QTextStream(stdout)<<"in I"<<endl;
        int i = 0;
        if(dx>0){
            QTextStream(stdout)<<"cond. 1"<<endl;
            for(float x = x1; x<x2; x++){
                    y = m*x + b;
                    //QTextStream(stdout)<<"y= "<<y<<" x= "<<x<<" m: "<<m<<endl;
                    drawable->setPixel(x,y,color);
                    i++;
    //                if(i>40)
    //                {
    //                    QTextStream(stdout)<<"pixels drawn: "<<i<<endl;
    //                }
                }

        }
        else{
            QTextStream(stdout)<<"cond. 2"<<endl;
            for(float x = x1; x>x2; x--){
                    y = m*x + b;
                    //QTextStream(stdout)<<"y= "<<y<<" x= "<<x<<" m: "<<m<<endl;
                    drawable->setPixel(x,y,color);
                    i++;
    //                if(i>40)
    //                {
    //                    QTextStream(stdout)<<"pixels drawn: "<<i<<endl;
    //                }
                }
        }

    }
    else{
        if(dy>0){
            QTextStream(stdout)<<"cond. 3"<<endl;

            //QTextStream(stdout)<<"in II"<<endl;
            float x;
            for(float y=y1; y<y2; y++){
                x = (y-b)/m;
                //QTextStream(stdout)<<"x= "<<x<<endl;

                drawable->setPixel(x,y,color);
            }
        }
        else{
            QTextStream(stdout)<<"cond. 4"<<endl;

            //QTextStream(stdout)<<"in II"<<endl;
            float x;
            for(float y=y1; y>y2; y--){
                x = (y-b)/m;
                //QTextStream(stdout)<<"x= "<<x<<endl;

                drawable->setPixel(x,y,color);
            }
        }
    }
}

//void Client::Bresenham(int x1, int y1, int x2, int y2, unsigned int color){
//    int dx = x2-x1;
//    if(x1>x2) {
//        dx = x1-x2;
//    }

//    int dy = y2-y1;
//    if(y1>y2) {
//        dy = y1-y2;
//    }

//    int two_dx = 2*dx;
//    int two_dy = 2*(y2-y1);

//    //QTextStream(stdout)<<"(x1,y1)=("<<x1<<","<<y1<<"),(x2,y2)=("<<x2<<","<<y2<<"), err= "<<err<<endl;
//    //int y = y1;
//    drawable->setPixel(x1,y1,color);

//    if(abs(dx)>abs(dy)){
//        int err = two_dy-dx;
//        int t2 = two_dy-two_dx;
//        if(y2>y1){
//            QTextStream(stdout)<<"1st cond. t2= "<<t2<<endl;
//            int y = y1;
//            //if(x2>x1){
//                for(int x=x1+1; x<=x2; x++){
//                    if (err>=0){
//                        err = err + t2;
//                        y++;
//                        //QTextStream(stdout)<<"y increasing"<<endl;
//                    }
//                    else{
//                        err = err+two_dy;
//                    }
//                    //QTextStream(stdout)<<"1st Drawn"<<endl;
//                    drawable->setPixel(x,y,color);
//                }
//            //}
////            else{
////                for(int x=x1-1; x>=x2; x--){
////                    if (err>=0){
////                        err = err + t2;
////                        y++;
////                        //QTextStream(stdout)<<"y increasing"<<endl;
////                    }
////                    else{
////                        err = err+two_dy;
////                    }
////                    //QTextStream(stdout)<<"1st Drawn"<<endl;
////                    drawable->setPixel(x,y,color);
////                }
////            }
//        }
//        else{
//            QTextStream(stdout)<<"2nd cond. t2= "<<t2<<endl;
//            int y = y1;
//            for(int x=x1+1; x<=x2; x++){
//                if (err>=0){
//                    err = err + t2;
//                    y--;
//                    //QTextStream(stdout)<<"y increasing"<<endl;
//                }
//                else{
//                    err = err+two_dy;
//                }
//                //QTextStream(stdout)<<"1st Drawn"<<endl;
//                drawable->setPixel(x,y,color);
//            }
//        }
//    }
//    else{
//         int err = two_dx-dy;
//        int t2 = two_dx-two_dy;
//        if(x2>x1){
//            QTextStream(stdout)<<"3rd cond. t2= "<<t2<<endl;
//            int x = x1;
//            for(int y=y1+1; y<=y2; y++){
//                if (err>=0){
//                    err = err + t2;
//                    x++;
//                    //QTextStream(stdout)<<"x increasing"<<endl;
//                }
//                else{
//                    err = err+two_dx;
//                }

//                drawable->setPixel(x,y,color);
//            }
//        }
//        else{
//            QTextStream(stdout)<<"4th cond. t2= "<<t2<<endl;
//            int x = x1;
//            for(int y=y1+1; y<=y2; y++){
//                if (err>=0){
//                    err = err + t2;
//                    x--;
//                    //QTextStream(stdout)<<"x increasing"<<endl;
//                }
//                else{
//                    err = err+two_dx;
//                }

//                drawable->setPixel(x,y,color);
//            }
//        }
//    }
//}

void Client::Bresenham(int x1, int y1, int x2, int y2, unsigned int color) {

     int dx = x2-x1;
     if(x1>x2) {
         dx = x1-x2;
     }

     int dy = y2-y1;
     if(y1>y2) {
         dy = y1-y2;
     }
     int twodx = 2*dx;
     int twody = 2*dy;

     int t = twody - twodx;
     int err = twody - dx;

     int u = twodx - twody;
     int err2 = twodx - dy;

     int x = x1;
     int y = y1;
     drawable->setPixel(x1, y1, color);

     if(dx > dy) {
         if(y1 > y2) {
             for(x=x1+1; x<x2; x++) {

                 if(err>=0) {
                     err = err + t;
                     y--;
                 }
                 else {
                     err = err + twody;
                 }
                 QTextStream(stdout)<<"dx "<<dx<<" dy "<<dy<<"   ";
                 QTextStream(stdout)<<"x1 "<<x1<<" y1 "<<y1<<"   ";
                 QTextStream(stdout)<<"x2 "<<x2<<" y2 "<<y2<<endl;
                 drawable->setPixel(x, y, color);
             }
         }
         else {
             for(x=x1+1; x<x2; x++) {

                 if(err>=0) {
                     err = err + t;
                     y++;
                 }
                 else {
                     err = err + twody;
                 }
                 QTextStream(stdout)<<"dx "<<dx<<" dy "<<dy<<"   ";
                 QTextStream(stdout)<<"x1 "<<x1<<" y1 "<<y1<<"   ";
                 QTextStream(stdout)<<"x2 "<<x2<<" y2 "<<y2<<endl;
                 drawable->setPixel(x, y, color);
             }
         }
     }
     else {
         if(x1>x2){
             for(y=y1+1; y<y2; y++) {
                 if(err2>=0) {
                     err2 = err2 + u;
                     x--;
                 }
                 else {
                     err2 = err2 + twodx;
                 }
                 drawable->setPixel(x, y, color);
             }
         }
         else {
             for(y=y1+1; y<y2; y++) {
                 if(err2>=0) {
                     err2 = err2 + u;
                     x++;
                 }
                 else {
                     err2 = err2 + twodx;
                 }
                 drawable->setPixel(x, y, color);
             }
         }
     }
 }

void Client::starburstPoints(int panel_location){
    if(panel_location == 1)
    {
        float x1,x2,y1,y2 = 0;
        float space = 2*PI/90;
        //float theta = 0;
        int i = 0;
        //theta<2*PI
        for (float theta=0; i<90; theta+=space){
            x1 = 200;
            y1 = 200;
            x2 = 200 + 75*cos(theta);
            y2 = 200 + 75*sin(theta);
            QTextStream(stdout)<<"(x2,y2)= ("<<x2<<","<<y2<<")"<<endl;
            Bresenham(x1,y1,x2,y2,0xffffffff);
            i++;

//            //QTextStream(stdout)<<theta<<endl;
//            x1 = 200 + 75*cos(theta);
//            y1 = 200 + 75*sin(theta);
//            x2 = 200 + 75*cos(theta-PI);
//            y2 = 200 + 75*sin(theta-PI);
//            //QTextStream(stdout)<<x1<<" " <<x2<<" "<<y1<<" "<<y2<<endl;
//            i++;

//            DDA(x1,y1,x2,y2,0xffffffff);
//            //QTextStream(stdout)<<"stuck"<<endl;



        }
          //QTextStream(stdout)<<"number of lines: "<<i<<endl;
    }
    else if(panel_location == 2)
    {
        for(int p = 0; p<=50; p++){
            DDA(20,80+p,150,150+p,0xffffffff);
            DDA(160+p,270,240+p,40,0xffffffff);
        }
    }
}
