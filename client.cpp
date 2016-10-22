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

    switch(pageNumber % 5) {
    case 1:
        draw_rect(0, 0, 750, 750, 0xffff0080);
        draw_rect( 50,  50, 350, 350, 0xff00ff40);
        draw_rect(400,  50, 700, 350, 0xff40ff00);
        draw_rect( 50, 400, 350, 700, 0xffff8000);
        draw_rect(400, 400, 700, 700, 0xffffff00);
        PageNumber(4);
        drawable->updateScreen();   // you must call this to make the display change.
        break;
    case 2:
        draw_rect(0, 0, 750, 750, 0xffff0080);
        draw_rect( 50,  50, 350, 350, 0xff00ff40);
        draw_rect(400,  50, 700, 350, 0xff40ff00);
        draw_rect( 50, 400, 350, 700, 0xffff8000);
        draw_rect(400, 400, 700, 700, 0xffffff00);
        PageNumber(4);
        drawable->updateScreen();
        break;
    case 3:
        draw_rect(0, 0, 750, 750, 0xffff0080);
        draw_rect( 50,  50, 350, 350, 0xff00ff40);
        draw_rect(400,  50, 700, 350, 0xff40ff00);
        draw_rect( 50, 400, 350, 700, 0xffff8000);
        draw_rect(400, 400, 700, 700, 0xffffff00);
        PageNumber(4);
        drawable->updateScreen();
        break;
    case 4:
        draw_rect(0, 0, 750, 750, 0xffff0080);
        draw_rect( 50,  50, 350, 350, 0xff00ff40);
        draw_rect(400,  50, 700, 350, 0xff40ff00);
        draw_rect( 50, 400, 350, 700, 0xffff8000);
        draw_rect(400, 400, 700, 700, 0xffffff00);
        PageNumber(4);
        drawable->updateScreen();
        // fall through...
        break;

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
    if(abs(m)<1)
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

    //QTextStream(stdout)<<"(x1,y1)=("<<x1<<","<<y1<<"),(x2,y2)=("<<x2<<","<<y2<<")"<<endl;
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


void Client::PolygonRenderer (float xx1, float yy1, float xx2, float yy2, float xx3, float yy3, unsigned int color){
    // initialize edge case for vertical lines
    bool VertLine_p1p2 = false;
    bool VertLine_p1p3 = false;
    bool VertLine_p2p3 = false;
    float x1,y1,x2,y2,x3,y3;

    // Assigning parameters to p1,p2,p3
    // (x1,y1)->(x2,y2) is assigned to be the longest line
    if(Distance(xx1,yy1,xx2,yy2)>=Distance(xx1,yy1,xx3,yy3) && Distance(xx1,yy1,xx2,yy2)>=Distance(xx2,yy2,xx3,yy3)){
        x1 = xx1;
        y1 = yy1;
        x2 = xx2;
        y2 = yy2;
        x3 = xx3;
        y3 = yy3;
        QTextStream(stdout)<<"longest line is (p1,p2)"<<endl;

    }
    else if(Distance(xx2,yy2,xx3,yy3)>=Distance(xx1,yy1,xx2,yy2) && Distance(xx2,yy2,xx3,yy3)>=Distance(xx1,yy1,xx3,yy3)){
        x1 = xx2;
        y1 = yy2;
        x2 = xx3;
        y2 = yy3;
        x3 = xx1;
        y3 = yy1;
        QTextStream(stdout)<<"longest line is (p2,p3)"<<endl;
    }
    else{
        x1 = xx1;
        y1 = yy1;
        x2 = xx3;
        y2 = yy3;
        x3 = xx2;
        y3 = yy2;
        QTextStream(stdout)<<"longest line is (p1,p3)"<<endl;
    }

    QTextStream(stdout)<<"(x,y)= "<<x1<<","<<y1<<" ->  "<<x2<<","<<y2<<endl;



    // Declaration for the longest line p1p2
    float long_dx = x2-x1;
    float long_dy = y2-y1;
    float long_m = (float)long_dy/(float)long_dx;
    float long_b = y1-long_m*x1;
    float long_y;
    float long_x;

    // Declaration for line p1p3
    float a_dx = x3-x1;
    float a_dy = y3-y1;
    float a_m = (float)a_dy/(float)a_dx;
    float a_b = y1-a_m*x1;
    float a_x;
    float a_y;

    // Declaration for line p2p3
    float b_dx = x3-x2;
    float b_dy = y3-y2;
    float b_m = (float)b_dy/(float)b_dx;
    float b_b = y2-b_m*x2;
    float b_x;
    float b_y;

    QTextStream(stdout)<<"b_m= "<<b_m<<endl;

    //Check for vertical slope (m = infinity)
    if((x1-x2)==0){
        VertLine_p1p2 = true;
        QTextStream(stdout)<<"p1p2 inf slope"<<endl;
    }
    if((x1-x3)==0){
        VertLine_p1p3 = true;
        QTextStream(stdout)<<"p1p3 inf slope"<<endl;
    }
    if((x2-x3)==0){
        VertLine_p2p3 = true;
        QTextStream(stdout)<<"p2p3 inf slope"<<endl;
    }

    //QTextStream(stdout)<<"(y,x)= "<<x1<<","<<y1<<" ->  "<<x2<<","<<y2<<endl;
    //QTextStream(stdout)<<"Slope= "<<long_m<<" || x1,y1="<<x1<<","<<y1<<"|| x2,y2="<<x2<<","<<y2<<"|| x3,y3="<<x3<<","<<y3<<endl;

    if(abs(long_m)<1){
        if(long_dx>0){// x1<x2
            for(float x = x1;x<=x2;x++){
                long_y=long_m*x+long_b;
                if(x<=x3){
                    if(!VertLine_p1p3){
                        a_y=a_m*x+a_b;
                    }
                    else{
                        a_y=y3;
                    }
                    Bresenham(x,long_y,x,a_y,color);
                }
                else{
                    if(!VertLine_p2p3){
                        b_y=b_m*x+b_b;
                    }
                    else{
                        b_y=y2;
                    }
                    Bresenham(x,long_y,x,b_y,color);
                }

            }
        }
        else{
            for(float x=x1;x>=x2;x--){
                long_y=long_m*x+long_b;
                if(x>=x3){
                    if(!VertLine_p1p3){
                        a_y=a_m*x+a_b;
                    }
                    else{
                        a_y=y3;
                    }
                    Bresenham(x,long_y,x,a_y,color);
                }
                else{
                    if(!VertLine_p2p3){
                        b_y=b_m*x+b_b;
                    }
                    else{
                        b_y=y2;
                    }
                    Bresenham(x,long_y,x,b_y,color);
                }
            }
        }
    }
    else{
        if(long_dy>0){
            for(float y=y1;y<=y2;y++){
                long_x=(y-long_b)/long_m;
                if(y<=y3){
                    if(!VertLine_p1p3){
                        a_x= (y-a_b)/a_m;
                    }
                    else{
                        a_x=x1;
                    }
                    Bresenham(long_x,y,a_x,y,color);
                }
                else{
                    if(!VertLine_p2p3){
                        b_x=(y-b_b)/b_m;
                    }
                    else{
                        b_x=x2;
                    }
                    Bresenham(long_x,y,b_x,y,color);
                }
            }
        }
        else{
            for(float y=y1; y>=y2; y--){
                long_x=(y-long_b)/long_m;
                if(y>=y3){
                    if(!VertLine_p1p3){
                        a_x= (y-a_b)/a_m;
                    }
                    else{
                        a_x=x1;
                    }
                    Bresenham(long_x,y,a_x,y,color);
                }
                else{
                    if(!VertLine_p2p3){
                        b_x=(y-b_b)/b_m;
                    }
                    else{
                        b_x=x2;
                    }
                    Bresenham(long_x,y,b_x,y,color);
                }
            }
        }
    }

}

void Client::PageNumber(int page_position){
    //////////////////////
    // PAGE1: Starburst //
    //////////////////////
    if(page_position == 1)
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
    else if(page_position == 2)
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
                Bresenham(70,480+p,200,550+p,0xffffffff);
                Bresenham(210+p,670,290+p,440,0xffffffff);
            }
            else{
                DDA(70,480+p,200,550+p,0xffffffff);
                DDA(210+p,670,290+p,440,0xffffffff);
            }
            i++;
        }
    }
    else if (page_position == 3){
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
    else if(page_position == 4){
//        float x1=200;
//        float y1=200;
//        float x2=220;
//        float y2=200;
//        float x3=220;
//        float y3=180;
//        PolygonRenderer(x1,y1,x2,y2,x3,y3,0xffffffff);
        float x1 = 400;
        float y1 = 400;
        float x2 = 600;
        float y2 = 400;
        float x3, y3;
        int i = 0;
//        x3 = 250;
//        y3 = 80;
//        PolygonRenderer(x1,y1,x2,y2,x3,y3,0xffffffff);



        qsrand(time(NULL));

        for (float theta = 2*PI/90; i<90; theta= theta + (2*PI/90)){
            //if(i>45){
                int r = qrand() % 256;
                int g = qrand() % 256;
                int b = qrand() % 256;
                QTextStream(stdout)<<"i= "<<i<<endl;

                unsigned int colour = (0xff<<24)+((r&0xff)<<16)+((g&0xff)<<8)+(b&0xff);
                x3 = 400 + 200*cos(theta);
                y3 = 400 + 200*sin(theta);
                PolygonRenderer(x1,y1,x2,y2,x3,y3,colour);
                QTextStream(stdout)<<"(x2,y2)=("<<x2<<","<<y2<<"), (x3,y3)=("<<x3<<","<<y3<<")"<<endl;
                x2=x3;
                y2=y3;
            //}
//            int r = qrand() % 256;
//            int g = qrand() % 256;
//            int b = qrand() % 256;
//            QTextStream(stdout)<<"theta= "<<theta<<endl;

//            unsigned int colour = (0xff<<24)+((r&0xff)<<16)+((g&0xff)<<8)+(b&0xff);
//            x3 = 200 + 125*cos(theta);
//            y3 = 200 + 125*sin(theta);
//            PolygonRenderer(x1,y1,x2,y2,x3,y3,colour);
//            //QTextStream(stdout)<<"(x2,y2)=("<<x2<<","<<y2<<"), (x3,y3)=("<<x3<<","<<y3<<")"<<endl;
//            x2=x3;
//            y2=y3;
            i++;
        }

//        int grid_data_x[9];
//        int grid_data_y[9];
//        for (int i=0; i<=8; i++){
//            //QTextStream(stdout)<<"(x2,y2)=("<<grid_data_x[i]<<",";
//            grid_data_x[i] = 420+28*i;
//            grid_data_y[i] = 70+28*i;
//            //QTextStream(stdout)<<grid_data_y[i]<<")  ";

//            //QTextStream(stdout)<<""<<endl;
//        }

//        for (int i=0; i<=8; i++){
//            for (int j=0; j<=8; j++){
//                int r1 = qrand() % 256;
//                int g1 = qrand() % 256;
//                int b1 = qrand() % 256;
//                int r2 = qrand() % 256;
//                int g2 = qrand() % 256;
//                int b2 = qrand() % 256;

//                float x1 = grid_data_x[j];
//                float y1 = grid_data_y[i];
//                float x2 = grid_data_x[j]+20;
//                float y2 = grid_data_y[i];
//                float x3 = grid_data_x[j];
//                float y3 = grid_data_y[i]+20;
//                float x4 = grid_data_x[j]+20;
//                float y4 = grid_data_y[i]+20;

//                QTextStream(stdout)<<"(x1,y1)=("<<x1<<","<<y1<<"),"<<"(x2,y2)=("<<x2+20<<","<<y2<<"), (x3,y3)=("<<x3<<","<<y3<<")"<<endl;

//                unsigned int colour1 = (0xff<<24)+((r1&0xff)<<16)+((g1&0xff)<<8)+(b1&0xff);
//                unsigned int colour2 = (0xff<<24)+((r2&0xff)<<16)+((g2&0xff)<<8)+(b2&0xff);
//                PolygonRenderer(x1,y1,x2,y2,x3,y3,colour1);
//                PolygonRenderer(x2,y2,x3,y3,x4,y4,colour2);
//            }
//        }


//        for (int i=0; i<=8; i++){
//            //QTextStream(stdout)<<"(x2,y2)=("<<grid_data_x[i]<<",";
//            grid_data_x[i] = 70+28*i;
//            grid_data_y[i] = 420+28*i;
//            //QTextStream(stdout)<<grid_data_y[i]<<")  ";

//            //QTextStream(stdout)<<""<<endl;
//        }

//        for(int i=0; i<=8; i++){
//            for (int j=0; j<=8; j++){
//                int r1 = qrand() % 256;
//                int g1 = qrand() % 256;
//                int b1 = qrand() % 256;
//                int r2 = qrand() % 256;
//                int g2 = qrand() % 256;
//                int b2 = qrand() % 256;
//                int shift_x = qrand() % (13+13)-13;
//                int shift_y = qrand() % (13+13)-13;

//                float x1 = grid_data_x[j]+shift_x;
//                float y1 = grid_data_y[i]+shift_y;
//                float x2 = grid_data_x[j]+20+shift_x;
//                float y2 = grid_data_y[i]+shift_y;
//                float x3 = grid_data_x[j]+shift_x;
//                float y3 = grid_data_y[i]+20+shift_y;
//                float x4 = grid_data_x[j]+20+shift_x;
//                float y4 = grid_data_y[i]+20+shift_y;


//                unsigned int colour1 = (0xff<<24)+((r1&0xff)<<16)+((g1&0xff)<<8)+(b1&0xff);
//                unsigned int colour2 = (0xff<<24)+((r2&0xff)<<16)+((g2&0xff)<<8)+(b2&0xff);


//                PolygonRenderer(x1,y1,x2,y2,x3,y3,colour1);
//                PolygonRenderer(x2,y2,x3,y3,x4,y4,colour2);

//            }
//        }

//        for(int i=0; i<120; i++){
//            int x1 = qrand() % 260 + 400;
//            int y1 = qrand() % 260 + 400;
//            //int x2 = qrand() % 25 + x1;
//            int x2 = x1 + 30;
//            //int y2 = qrand() % 10 + 20 + y1;
//            int y2 = y1;
//            //int x3 = qrand() % 20 + qrand() % (5+5) -5  + x1;
//            int x3 = x1 + 30;
//            //int y3 = qrand() % 20 + 20 + y1;
//            int y3 = y1 + 30;

//            int r1 = qrand() % 256;
//            int g1 = qrand() % 256;
//            int b1 = qrand() % 256;
//            int r2 = qrand() % 256;
//            int g2 = qrand() % 256;
//            int b2 = qrand() % 256;
//            unsigned int colour1 = (0xff<<24)+((r1&0xff)<<16)+((g1&0xff)<<8)+(b1&0xff);

//            PolygonRenderer(x1,y1,x2,y2,x3,y3,colour1);

//        }

    }
}

int Client::Distance(int x1, int y1, int x2, int y2)
{
    return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}
