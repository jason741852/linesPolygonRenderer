#ifndef CLIENT_H
#define CLIENT_H
#include "drawable.h"
#include "pageturner.h"

class Client : public PageTurner
{
public:
    Client(Drawable *drawable);
    void nextPage();

private:
    Drawable *drawable;
    void draw_rect(int x1, int y1, int x2, int y2, unsigned int color);
    void DDA(float x1, float y1, float x2, float y2, unsigned int color);
    void starburstPoints(int panel_location);
    void Bresenham(int x1, int y1, int x2, int y2, unsigned int color);
    //void AntiAliased(int x1, int y1, int x2, int y2, unsigned int color);
    void PolygonRenderer (int xx1, int yy1, int xx2, int yy2, int xx3, int yy3, unsigned int color);
    int Distance(int x1, int y1, int x2, int y2);
};

#endif // CLIENT_H
