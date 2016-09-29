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
        starburstPoints(2);
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

void Client::DDA(int x1, int y1, int x2, int y2, unsigned int color){
    int dx = x2-x1;
    int dy = y2-y1;
    float m = (float)dy/(float)dx;
    float b = y1-m*x1;
    float y;

    // check slope to see which octant
    if(dx>dy)
    {
        QTextStream(stdout)<<"in I"<<endl;
        int i = 0;
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
        QTextStream(stdout)<<"in II"<<endl;
        float x;
        for(float y=y1; y<y2; y++){
            x = (y-b)/m;
            QTextStream(stdout)<<"x= "<<x<<endl;

            drawable->setPixel(x,y,color);
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
        for (float theta=0; theta<2*PI; theta+=space){
            //QTextStream(stdout)<<theta<<endl;
            x1 = 200 + 75*cos(theta);
            y1 = 200 + 75*sin(theta);
            x2 = 200 + 75*cos(theta-PI);
            y2 = 200 + 75*sin(theta-PI);
            //QTextStream(stdout)<<x1<<" " <<x2<<" "<<y1<<" "<<y2<<endl;
            i++;

            DDA(x1,y1,x2,y2,0xffffffff);
            //QTextStream(stdout)<<"stuck"<<endl;

        }
          QTextStream(stdout)<<"number of lines: "<<i<<endl;
    }
    else if(panel_location == 2)
    {
        for(int p = 0; p<=50; p++){
            DDA(20,80+p,150,150+p,0xffffffff);
            DDA(160+p,270,240+p,40,0xffffffff);
        }
    }
}
