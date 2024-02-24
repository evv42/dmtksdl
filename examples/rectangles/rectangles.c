#define DMTK_IMPLEMENTATION
#include "dmtk.h"
#include <stdlib.h>//rand

int main(){

    DWindow* win = DInit(600,400,"Rectangles Speed Test");
	long unsigned int todraw = 420;

    while(win->alive && todraw > 0){
		DGetRequest(win);
        Anchor a = mtk_put_rectangle(win, rand()%(1024/2), rand()%(768/2), rand()%1024, rand()%768, rand()%256, rand()%256, rand()%256);
		mtk_put_astring(win, a.hxanchor, a.hyanchor, "nya", 0xFF, 0xFF, 0xFF);
		usleep(100000);
        DFlush(win);
		todraw--;
    }
    
    DEndProcess(win);

    return 0;
}
