#include <iostream>
#include <math.h>
#include <QTextStream>
#include <iostream>
#include <ctime>
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
        starburstPoints(4);
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


// Digital Differential Analyzer Algorithm
// Check if the slope value is between -1 and 1
// If so increment/decrement y along x++ or x--
// Otherwise if slope is not between -1 and 1
// Increment/decrement x along y++ or y--
void Client::DDA(float x1, float y1, float x2, float y2, unsigned int color){
    float dx = x2-x1;
    float dy = y2-y1;
    float m = (float)dy/(float)dx;
    float b = y1-m*x1;
    float y;
    //QTextStream(stdout)<<"(x1,y1)=("<<x1<<","<<y1<<"),(x2,y2)=("<<x2<<","<<y2<<"), m= "<<m<<endl;
    // check slope to see which octant
    if(abs(m)>=0 && abs(m)<1)
    {
        //QTextStream(stdout)<<"in I"<<endl;
        int i = 0;
        if(dx>0){
            //QTextStream(stdout)<<"cond. 1"<<endl;
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
            //QTextStream(stdout)<<"cond. 2"<<endl;
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
            //QTextStream(stdout)<<"cond. 3"<<endl;

            //QTextStream(stdout)<<"in II"<<endl;
            float x;
            for(float y=y1; y<y2; y++){
                x = (y-b)/m;
                //QTextStream(stdout)<<"x= "<<x<<endl;

                drawable->setPixel(x,y,color);
            }
        }
        else{
            //QTextStream(stdout)<<"cond. 4"<<endl;

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

// Bresenham's algorithm
// 8 octants are set up by 3 conditional statements
// first compare dx and dy,
// then y2 and y1 or x2 and x1,
// then x2 and x1 or y2 and y1
void Client::Bresenham(int x1, int y1, int x2, int y2, unsigned int color){
    int dx = x2-x1;
    if(x1>x2) {
        dx = x1-x2;
    }

    int dy = y2-y1;
    if(y1>y2) {
        dy = y1-y2;
    }

    int two_dx = 2*dx;
    int two_dy = 2*dy;

    QTextStream(stdout)<<"(x1,y1)=("<<x1<<","<<y1<<"),(x2,y2)=("<<x2<<","<<y2<<")"<<endl;
    //int y = y1;
    drawable->setPixel(x1,y1,color);

    if(dx>dy){
        int err = two_dy-dx;
        int t2 = two_dy-two_dx;
        if(y2>y1){
            //QTextStream(stdout)<<"1st cond. "<<endl;
            int y = y1;
            if(x2>x1){
                for(int x=x1+1; x<=x2; x++){
                    if (err>=0){
                        err = err + t2;
                        y++;
                        //QTextStream(stdout)<<"y increasing"<<endl;
                    }
                    else{
                        err = err+two_dy;
                    }
                    //QTextStream(stdout)<<"1st Drawn"<<endl;
                    drawable->setPixel(x,y,color);
                }
            }
            else{
                for(int x=x1-1; x>=x2; x--){
                    if (err>=0){
                        err = err + t2;
                        y++;
                        //QTextStream(stdout)<<"y increasing"<<endl;
                    }
                    else{
                        err = err+two_dy;
                    }
                    //QTextStream(stdout)<<"1st Drawn"<<endl;
                    drawable->setPixel(x,y,color);
                }
            }
        }
        else{
            if(x2>x1){
                //QTextStream(stdout)<<"2nd cond. "<<endl;
                int y = y1;
                for(int x=x1+1; x<=x2; x++){
                    if (err>=0){
                        err = err + t2;
                        y--;
                        //QTextStream(stdout)<<"y decreasing"<<endl;
                    }
                    else{
                        err = err+two_dy;
                    }
                    //QTextStream(stdout)<<"(x,y)= ("<<x<<","<<y<<")"<<endl;
                    //QTextStream(stdout)<<"1st Drawn"<<endl;
                    drawable->setPixel(x,y,color);
                }
            }
            else{
                int y = y1;
                for(int x=x1-1; x>=x2; x--){
                    if (err>=0){
                        err = err + t2;
                        y--;
                        //QTextStream(stdout)<<"y decreasing"<<endl;
                    }
                    else{
                        err = err+two_dy;
                    }
                    //QTextStream(stdout)<<"(x,y)= ("<<x<<","<<y<<")"<<endl;
                    //QTextStream(stdout)<<"1st Drawn"<<endl;
                    drawable->setPixel(x,y,color);
                }
            }
        }
    }
    else{
        int err = two_dx-dy;
        int t2 = two_dx-two_dy;
        if(x2>x1){
                if(y2>y1){
                    //QTextStream(stdout)<<"3rd cond. "<<endl;
                    int x = x1;
                    for(int y=y1+1; y<=y2; y++){
                        if (err>=0){
                            err = err + t2;
                            x++;
                            //QTextStream(stdout)<<"x increasing"<<endl;
                        }
                        else{
                            err = err+two_dx;
                        }

                        drawable->setPixel(x,y,color);
                    }
                }
                else{
                    //QTextStream(stdout)<<"3rd cond. "<<endl;
                    int x = x1;
                    for(int y=y1+1; y>=y2; y--){
                        if (err>=0){
                            err = err + t2;
                            x++;
                            //QTextStream(stdout)<<"x increasing"<<endl;
                        }
                        else{
                            err = err+two_dx;
                        }

                        drawable->setPixel(x,y,color);
                    }
                }
        }
        else{
            if(y2>y1){
                //QTextStream(stdout)<<"4th cond. "<<endl;
                int x = x1;
                for(int y=y1+1; y<=y2; y++){
                    if (err>=0){
                        err = err + t2;
                        x--;
                        //QTextStream(stdout)<<"x decreasing"<<endl;
                    }
                    else{
                        err = err+two_dx;
                    }

                    drawable->setPixel(x,y,color);
                }
            }
            else{
                //QTextStream(stdout)<<"4th cond. "<<endl;
                int x = x1;
                for(int y=y1+1; y>=y2; y--){
                    if (err>=0){
                        err = err + t2;
                        x--;
                        //QTextStream(stdout)<<"x decreasing"<<endl;
                    }
                    else{
                        err = err+two_dx;
                    }

                    drawable->setPixel(x,y,color);
                }
            }
        }
    }
}

//void Client::AntiAliased(int x1, int y1, int x2, int y2, unsigned int color){
//    int dx = x2-x1;
//    int dy = y2-y1;
//    int du, dv, u, v;
//    if(abs(dx)>abs(dy)){
//        du = abs(dx);
//        dv = abs(dy);

//    }

//}


void Client::PolygonRenderer (int xx1, int yy1, int xx2, int yy2, int xx3, int yy3, unsigned int color){
    // find the left-most point of the triangle label it x1 and y1, call i p1
    // if p1 is the lowest vertex of the triangle (max y),
    // assign the the other vertex of the longest line to p2
    // the last point is p3

    int x1,y1,x2,y2,x3,y3;
    QTextStream(stdout)<<"(p1,p2)="<<endl;

    // Assigning parameters to p1,p2,p3
    if(Distance(xx1,yy1,xx2,yy2)>=Distance(xx1,yy1,xx3,yy3) && Distance(xx1,yy1,xx2,yy2)>=Distance(xx2,yy2,xx3,yy3)){
        x1 = xx1;
        y1 = yy1;
        x2 = xx2;
        y2 = yy2;
        x3 = xx3;
        y3 = yy3;
        QTextStream(stdout)<<"longest line is (p1,p2)"<<endl;

//        if(Distance(xx1,yy1,xx2,yy2)>=Distance(x1,y1,xx3,yy3)){
//            x2 = xx2;
//            y2 = yy2;
//            x3 = xx3;
//            y3 = yy3;
//        }
//        else{
//            x2 = xx3;
//            y2 = yy3;
//            x3 = xx2;
//            y3 = yy2;
//        }

    }
    else if(Distance(xx2,yy2,xx3,yy3)>=Distance(xx1,yy1,xx2,yy2) && Distance(xx2,yy2,xx3,yy3)>=Distance(xx1,yy1,xx3,yy3)){
        x1 = xx2;
        y1 = yy2;
        x2 = xx3;
        y2 = yy3;
        x3 = xx1;
        y3 = yy1;
        QTextStream(stdout)<<"longest line is (p2,p3)"<<endl;

//        if(Distance(xx2,yy2,xx1,yy1)>=Distance(xx2,yy2,xx3,yy3)){
//            x2 = xx1;
//            y2 = yy1;
//            x3 = xx3;
//            y3 = yy3;
//        }
//        else{
//            x2 = xx3;
//            y2 = yy3;
//            x3 = xx1;
//            y3 = yy1;
//        }
    }
    else{
        x1 = xx1;
        y1 = yy1;
        x2 = xx3;
        y2 = yy3;
        x3 = xx2;
        y3 = yy2;
        QTextStream(stdout)<<"longest line is (p1,p3)"<<endl;

//        if(Distance(xx3,yy3,xx1,yy1)>Distance(xx3,yy3,xx2,yy2)){
//            x2 = xx1;
//            y2 = yy1;
//            x3 = xx2;
//            y3 = yy2;
//        }
//        else{
//            x2 = xx2;
//            y2 = yy2;
//            x3 = xx1;
//            y3 = yy1;
//        }
    }

    // Draw the two line that are not traversed along
    Bresenham(x1,y1,x3,y3,color);
    Bresenham(x2,y2,x3,y3,color);

    // Modified Bresenham code for drawing the line p1->p2
    int dx = x2-x1;
    int dy = y2-y1;

    int two_dx = 2*dx;
    int two_dy = 2*dy;

    QTextStream(stdout)<<"(x1,y1)=("<<x1<<","<<y1<<"),(x2,y2)=("<<x2<<","<<y2<<")"<<endl;
    //int y = y1;


    if(dx>dy){
        int err = two_dy-dx;
        int t2 = two_dy-two_dx;
        if(y2>y1){
            //QTextStream(stdout)<<"1st cond. "<<endl;
            int y = y1;
            if(x2>x1){
                for(int x=x1+1; x<=x2; x++){
                    if (err>=0){
                        err = err + t2;
                        y++;
                        //QTextStream(stdout)<<"y increasing"<<endl;
                    }
                    else{
                        err = err+two_dy;
                    }
                    //QTextStream(stdout)<<"1st Drawn"<<endl;
                    drawable->setPixel(x,y,color);
                    QTextStream(stdout)<<"scanning pixels...."<<endl;

                    int px1 = x;
                    int py1 = y+1;
                    int i=0;
                    while(drawable->getPixel(px1,py1)!=color  &&  px1!=x2){
                        QTextStream(stdout)<<i<<" color= "<<drawable->getPixel(px1,py1)<<" and py1= "<<py1<<endl<<endl;
                        drawable->setPixel(px1,py1,color);
                        py1++;
                        //i++;
                    }
                }
            }
            else{
                for(int x=x1-1; x>=x2; x--){
                    if (err>=0){
                        err = err + t2;
                        y++;
                        //QTextStream(stdout)<<"y increasing"<<endl;
                    }
                    else{
                        err = err+two_dy;
                    }
                    //QTextStream(stdout)<<"1st Drawn"<<endl;
                    drawable->setPixel(x,y,color);

                    int px1 = x;
                    int py1 = y;
                    while(drawable->getPixel(px1,py1)!=color){
                        drawable->setPixel(px1,py1,color);
                        py1++;
                    }
                }
            }
        }
        else{
            if(x2>x1){
                //QTextStream(stdout)<<"2nd cond. "<<endl;
                int y = y1;
                for(int x=x1+1; x<=x2; x++){
                    if (err>=0){
                        err = err + t2;
                        y--;
                        //QTextStream(stdout)<<"y decreasing"<<endl;
                    }
                    else{
                        err = err+two_dy;
                    }
                    //QTextStream(stdout)<<"(x,y)= ("<<x<<","<<y<<")"<<endl;
                    //QTextStream(stdout)<<"1st Drawn"<<endl;
                    drawable->setPixel(x,y,color);
                    QTextStream(stdout)<<"scanning pixels...."<<endl;

                    int px1 = x;
                    int py1 = y;
                    while(drawable->getPixel(px1,py1)!=color){
                        QTextStream(stdout)<<"py1= "<<py1<<endl;
                        drawable->setPixel(px1,py1,color);
                        py1--;
                    }
                }
            }
            else{
                int y = y1;
                for(int x=x1-1; x>=x2; x--){
                    if (err>=0){
                        err = err + t2;
                        y--;
                        //QTextStream(stdout)<<"y decreasing"<<endl;
                    }
                    else{
                        err = err+two_dy;
                    }
                    //QTextStream(stdout)<<"(x,y)= ("<<x<<","<<y<<")"<<endl;
                    //QTextStream(stdout)<<"1st Drawn"<<endl;
                    drawable->setPixel(x,y,color);

                    int px1 = x;
                    int py1 = y;
                    while(drawable->getPixel(px1,py1)!=color){
                        drawable->setPixel(px1,py1,color);
                        py1--;
                    }
                }
            }
        }
    }
    else{
        int err = two_dx-dy;
        int t2 = two_dx-two_dy;
        if(x2>x1){
                if(y2>y1){
                    //QTextStream(stdout)<<"3rd cond. "<<endl;
                    int x = x1;
                    for(int y=y1+1; y<=y2; y++){
                        if (err>=0){
                            err = err + t2;
                            x++;
                            //QTextStream(stdout)<<"x increasing"<<endl;
                        }
                        else{
                            err = err+two_dx;
                        }

                        drawable->setPixel(x,y,color);

                        int px1 = x;
                        int py1 = y;
                        while(drawable->getPixel(px1,py1)!=color){
                            drawable->setPixel(px1,py1,color);
                            px1++;
                        }
                    }
                }
                else{
                    //QTextStream(stdout)<<"3rd cond. "<<endl;
                    int x = x1;
                    for(int y=y1+1; y>=y2; y--){
                        if (err>=0){
                            err = err + t2;
                            x++;
                            //QTextStream(stdout)<<"x increasing"<<endl;
                        }
                        else{
                            err = err+two_dx;
                        }

                        drawable->setPixel(x,y,color);

                        int px1 = x;
                        int py1 = y;
                        while(drawable->getPixel(px1,py1)!=color){
                            drawable->setPixel(px1,py1,color);
                            px1++;
                        }
                    }
                }
        }
        else{
            if(y2>y1){
                //QTextStream(stdout)<<"4th cond. "<<endl;
                int x = x1;
                for(int y=y1+1; y<=y2; y++){
                    if (err>=0){
                        err = err + t2;
                        x--;
                        //QTextStream(stdout)<<"x decreasing"<<endl;
                    }
                    else{
                        err = err+two_dx;
                    }

                    drawable->setPixel(x,y,color);

                    int px1 = x;
                    int py1 = y;
                    while(drawable->getPixel(px1,py1)!=color){
                        drawable->setPixel(px1,py1,color);
                        px1--;
                    }
                }
            }
            else{
                //QTextStream(stdout)<<"4th cond. "<<endl;
                int x = x1;
                for(int y=y1+1; y>=y2; y--){
                    if (err>=0){
                        err = err + t2;
                        x--;
                        //QTextStream(stdout)<<"x decreasing"<<endl;
                    }
                    else{
                        err = err+two_dx;
                    }

                    drawable->setPixel(x,y,color);

                    int px1 = x;
                    int py1 = y;
                    while(drawable->getPixel(px1,py1)!=color){
                        drawable->setPixel(px1,py1,color);
                        px1--;
                    }
                }
            }
        }
    }
}


void Client::starburstPoints(int panel_location){
    //////////////////////
    // PAGE1: Starburst //
    //////////////////////
    if(panel_location == 1)
    {
        float x1,x2,y1,y2 = 0;
        float space = 2*PI/90;
        //float theta = 0;
        int i = 0;
        //theta<2*PI

        ////////////////
        // Panel 1 DDA//
        ////////////////
        for (float theta=0; theta<2*PI; theta+=space){
            x1 = 200;
            y1 = 200;
            x2 = 200 + 75*cos(theta);
            y2 = 200 + 75*sin(theta);
            QTextStream(stdout)<<"(x2,y2)= ("<<x2<<","<<y2<<")"<<endl;
            DDA(x1,y1,x2,y2,0xffffffff);
            i++;
        }
        //////////////////////
        // Panel 2 Bresenham//
        //////////////////////
        for (float theta=0; theta<2*PI; theta+=space){
            x1 = 550;
            y1 = 200;
            x2 = 550 + 75*cos(theta);
            y2 = 200 + 75*sin(theta);
            QTextStream(stdout)<<"(x2,y2)= ("<<x2<<","<<y2<<")"<<endl;
            Bresenham(x1,y1,x2,y2,0xffffffff);
            i++;
        }
        //////////////////////////
        // Panel 3 DDA+Bresenham//
        //////////////////////////
        for (float theta=0; theta<2*PI; theta+=space){
            x1 = 200;
            y1 = 550;
            x2 = 200 + 75*cos(theta);
            y2 = 550 + 75*sin(theta);
            QTextStream(stdout)<<"(x2,y2)= ("<<x2<<","<<y2<<")"<<endl;
            if(i%2 == 1){
                Bresenham(x1,y1,x2,y2,0xffffffff);
            }
            else{
                DDA(x1,y1,x2,y2,0xffffffff);
            }
            i++;
        }
    }
    //////////////////////////
    // PAGE2: Parallelogram //
    //////////////////////////
    else if(panel_location == 2)
    {
        for(int p = 0; p<=50; p++){
            DDA(70,130+p,200,200+p,0xffffffff);
            DDA(210+p,320,290+p,90,0xffffffff);
        }
        for(int p = 0; p<=50; p++){
            Bresenham(420,130+p,550,200+p,0xffffffff);
            Bresenham(560+p,320,640+p,90,0xffffffff);
        }
        int i = 0;
        for(int p = 0; p<=50; p++){
            if(i%2 == 0){
                DDA(70,480+p,200,550+p,0xffffffff);
                Bresenham(210+p,670,290+p,440,0xffffffff);
            }
            else{
                DDA(70,480+p,200,550+p,0xffffffff);
                Bresenham(210+p,670,290+p,440,0xffffffff);
            }
            i++;
        }
    }
    else if (panel_location == 3){
        srand ( time(0) );
        for(int i=0; i<120; i++){
            int x1 = rand() % 300 + 50;
            int x2 = rand() % 300 + 50;
            int y1 = rand() % 300 + 50;
            int y2 = rand() % 300 + 50;
            int r = rand() % 256;
            int g = rand() % 256;
            int b = rand() % 256;

            unsigned int colour = (0xff<<24)+((r&0xff)<<16)+((g&0xff)<<8)+(b&0xff);
            QTextStream(stdout)<<"colour = "<<colour<<endl;
            DDA(x1,y1,x2,y2,colour);
        }
        for(int i=0; i<120; i++){
            int x1 = rand() % 300 + 400;
            int x2 = rand() % 300 + 400;
            int y1 = rand() % 300 + 50;
            int y2 = rand() % 300 + 50;
            int r = rand() % 256;
            int g = rand() % 256;
            int b = rand() % 256;

            unsigned int colour = (0xff<<24)+((r&0xff)<<16)+((g&0xff)<<8)+(b&0xff);
            QTextStream(stdout)<<"colour = "<<colour<<endl;
            Bresenham(x1,y1,x2,y2,colour);
        }
        for(int i=0; i<120; i++){
            int x1 = rand() % 300 + 50;
            int x2 = rand() % 300 + 50;
            int y1 = rand() % 300 + 400;
            int y2 = rand() % 300 + 400;
            int r = rand() % 256;
            int g = rand() % 256;
            int b = rand() % 256;

            unsigned int colour = (0xff<<24)+((r&0xff)<<16)+((g&0xff)<<8)+(b&0xff);
            QTextStream(stdout)<<"colour = "<<colour<<endl;
            if(i%2 == 0){
                Bresenham(x1,y1,x2,y2,colour);
            }
            else{
                DDA(x1,y1,x2,y2,colour);
            }
        }
    }
    else if(panel_location == 4){
        int x1 = 200;
        int y1 = 200;
        int x2 = 325;
        int y2 = 250;
        int x3, y3;
        int i = 0;
        x3 = 300;
        y3 = 280;

        PolygonRenderer(x1,y1,x2,y2,x3,y3,0xffffffff);
        //int theta = 4; // 4 degrees
//        for (float theta = 2*PI/90; i<90; theta= theta + (2*PI/90)){
//            int r = rand() % 256;
//            int g = rand() % 256;
//            int b = rand() % 256;
//            QTextStream(stdout)<<"theta= "<<theta<<endl;

//            unsigned int colour = (0xff<<24)+((r&0xff)<<16)+((g&0xff)<<8)+(b&0xff);
//            Bresenham(x1,y1,x2,y2,colour);
//            x3 = 200 + 125*cos(theta);
//            y3 = 200 + 125*cos(theta);
//            Bresenham(x1,y1,x3,y3,colour);
//            QTextStream(stdout)<<"(x2,y2)=("<<x2<<","<<y2<<"), (x3,y3)=("<<x3<<","<<y3<<")"<<endl;
//            x2=x3;
//            y2=y3;
//            i++;
//        }

    }
}

int Client::Distance(int x1, int y1, int x2, int y2)
{
    return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}
