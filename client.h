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
    void PageNumber(int page_location);
    void Bresenham(int x1, int y1, int x2, int y2, unsigned int color);
    //void AntiAliased(int x1, int y1, int x2, int y2, unsigned int color);
    void PolygonRenderer (float xx1, float yy1, float xx2, float yy2, float xx3, float yy3, unsigned int color);
    void PolygonRendererOpacity (float x1, float y1, float x2, float y2, float x3, float y3, unsigned int opacity);
    int Distance(int x1, int y1, int x2, int y2);
};

#endif // CLIENT_H
