/* See LICENSE file for copyright and license details. */
/* da minimalist toolkit
 * single* header SDL2 version
 * *including unifont would be a PITA
 * Copyright 2020,2021,2022,2023,2024 evv42.
*/
# ifndef __DMTK_H__
# define __DMTK_H__
#ifdef __cplusplus
extern "C" {
#endif
/*old dmtkgui.h*/

//Standard keys, based on X11

//Editing keys

#define SK_BackSpace                     SDLK_BACKSPACE
#define SK_Return                        SDLK_RETURN
#define SK_Insert                        SDLK_INSERT
#define SK_Delete                        SDLK_DELETE

//System keys

#define SK_Escape                        SDLK_ESCAPE
#define SK_Menu                          SDLK_MENU
#define SK_Super_L                       SDLK_LGUI  //Super or Command or Windows
#define SK_Super_R                       SDLK_RGUI  //Super or Command or Windows
#define SK_Print                         SDLK_PRINTSCREEN
#define SK_Sys_Req                       SDLK_SYSREQ
#define SK_Pause                         SDLK_PAUSE  //Pause

//Navigation keys

#define SK_Tab                           SDLK_TAB
#define SK_Home                          SDLK_HOME
#define SK_End                           SDLK_END
#define SK_Page_Up                       SDLK_PAGEUP
#define SK_Page_Down                     SDLK_PAGEDOWN
#define SK_Left                          SDLK_LEFT
#define SK_Up                            SDLK_UP
#define SK_Right                         SDLK_RIGHT
#define SK_Down                          SDLK_DOWN

//Keypad

#define SK_Num_Lock                      SDLK_NUMLOCKCLEAR
#define SK_KP_Enter                      SDLK_KP_ENTER
#define SK_KP_Home                       SDLK_HOME
#define SK_KP_Left                       SDLK_LEFT
#define SK_KP_Up                         SDLK_UP
#define SK_KP_Right                      SDLK_RIGHT
#define SK_KP_Down                       SDLK_DOWN
#define SK_KP_Page_Up                    SDLK_PAGEUP
#define SK_KP_Page_Down                  SDLK_PAGEDOWN
#define SK_KP_End                        SDLK_END
#define SK_KP_Insert                     SDLK_INSERT
#define SK_KP_Delete                     SDLK_DELETE
#define SK_KP_Equal                      SDLK_KP_EQUALS
#define SK_KP_Multiply                   SDLK_KP_MULTIPLY
#define SK_KP_Add                        SDLK_KP_PLUS
#define SK_KP_Separator                  SDLK_KP_COMMA  //Comma or dot
#define SK_KP_Subtract                   SDLK_KP_MINUS
#define SK_KP_Decimal                    SDLK_KP_DECIMAL
#define SK_KP_Divide                     SDLK_KP_DIVIDE

#define SK_KP_0                          SDLK_KP_0
#define SK_KP_1                          SDLK_KP_1
#define SK_KP_2                          SDLK_KP_2
#define SK_KP_3                          SDLK_KP_3
#define SK_KP_4                          SDLK_KP_4
#define SK_KP_5                          SDLK_KP_5
#define SK_KP_6                          SDLK_KP_6
#define SK_KP_7                          SDLK_KP_7
#define SK_KP_8                          SDLK_KP_8
#define SK_KP_9                          SDLK_KP_9

//Function keys

#define SK_F1                            SDLK_F1
#define SK_F2                            SDLK_F2
#define SK_F3                            SDLK_F3
#define SK_F4                            SDLK_F4
#define SK_F5                            SDLK_F5
#define SK_F6                            SDLK_F6
#define SK_F7                            SDLK_F7
#define SK_F8                            SDLK_F8
#define SK_F9                            SDLK_F9
#define SK_F10                           SDLK_F10
#define SK_F11                           SDLK_F11
#define SK_F12                           SDLK_F12

//Modifiers

#define SK_Shift_L                       SDLK_LSHIFT
#define SK_Shift_R                       SDLK_RSHIFT
#define SK_Control_L                     SDLK_LCTRL
#define SK_Control_R                     SDLK_RCTRL
#define SK_Scroll_Lock                   SDLK_SCROLLLOCK
#define SK_Caps_Lock                     SDLK_CAPSLOCK
#define SK_Alt_L                         SDLK_LALT
#define SK_Alt_R                         SDLK_RALT


#include <stdint.h>
#if !(__STDC_NO_ATOMICS__)
#include <stdatomic.h>
#endif

//This will affect memory usage.
//A bigger buffer means faster draws of images.
#define MTK_IMAGE_CHUNK_SIZE 4*1024*4*256

#define PIXEL_RQ 0
#define RECTANGLE_RQ 1
#define WNAME_RQ 2
#define FLUSH_RQ 3
#define MOVE_RQ 4
struct DrawRequest{
	char type;
	int h, v;
	int sx, sy;
	int dx, dy;
	char* data;
	unsigned char r, g, b;
};
typedef struct DrawRequest DrawRequest;

#define KEYB_RQ 0
#define MOUSE_RQ 1
#define RESIZE_RQ 2
#define CLOSE_RQ 3
#define NO_RQ 4
struct GUIRequest{
	char type;
	uint32_t data;
	char utfkey[4];//Only for KEYB_RQ, 0-terminated character, including ASCII control.
	int x;
	int y;
};
typedef struct GUIRequest GUIRequest;

struct DWindow{
	int rx;
	int ry;
#if !(__STDC_NO_ATOMICS__)
	atomic_char drawrq;
	DrawRequest drq;
	atomic_char guirq;
#else
	char drawrq;
	DrawRequest drq;
	char guirq;
#endif
	GUIRequest grq;
	char alive;
};
typedef struct DWindow DWindow;

/* Creates a window. */
DWindow* DInit(int x, int y, char* name);

/* Creates a window that starts in the corner, without border. */
DWindow* DInitBorderless(int x, int y, char* name);

void DDrawPixels(DWindow* win, int h, int v, int sx, int sy, unsigned char* data);

void DDrawRectangle(DWindow* win, int h, int v, int sx, int sy, unsigned char r, unsigned char g, unsigned char b);

void DChangeName(DWindow* win, char* str);

void DFlush(DWindow* win);

void DMove(DWindow* win, int h, int v, int sx, int sy, int dx, int dy);

GUIRequest DGetRequest(DWindow* win);

/* Deletes a window */
void DEndProcess(DWindow* win);

/*old dmtk.h*/
//Default colors: You may use them.
#define BG 222,223,224        //Default window background
#define FG 0,0,0              //Default foreground (text)
#define BORDER 99,99,99       //Default window border
#define SEP 189,189,189       //Default window separation
#define BTN 236,237,238       //Default button
#define BTNTOP 245,245,245    //Default button top border
#define BTNBCK 180,180,180    //Default button back border
#define BGB 192,192,192       //Default Z-1 background
#define BGBTOP 100,100,100    //Default Z-1 top border
#define BGBBCK 245,245,245    //Default Z-1 back border

//Aliases
#define BLK 0,0,0
#define WHT 255,255,255
#define RED 255,0,0
#define CYN 0,255,255
#define PUR 255,0,255
#define GRN 0,255,0
#define BLU 0,0,255
#define YEL 255,255,0

struct Anchor{
	int hxanchor;//Right
	int hyanchor;
	int vxanchor;//Down
	int vyanchor;
};
typedef struct Anchor Anchor;

// Image related functions

#define OIOI_HANDLED 0
#define STBI_HANDLED 1
#define MIMA_HANDLED 2
#define ERROR 3
struct Image{
	unsigned char* data;
	int width;
	int height;
	char handler;
};
typedef struct Image Image;

Anchor mtk_put_image_buffer(DWindow* win, int h, int v, Image img);

Image mtk_load_image(char* img);

void mtk_free_image(Image img);

//Put image from file using functions above
Anchor mtk_put_image(DWindow* win, int h, int v, char* file);

/* Drawing funtions */

Anchor mtk_put_rectangle(DWindow* win, int h, int v, int sx, int sy, unsigned char r, unsigned char g, unsigned char b);

//Put Z-1 box
Anchor mtk_put_backbox(DWindow* win, int h, int v, int sx, int sy, int border);


/* Text rendering functions
 * For simplicity sake, MTK does use a single monospaced font.
 */

//Return character max width
unsigned char mtk_font_width();

//Return width of string
int mtk_str_width(char* string);

//Return character height
unsigned char mtk_font_height();

//Put a string over the existing background
Anchor mtk_put_astring(DWindow* win, int h, int v, char* string, char r, char g, char b);

//Put a backgrounded string
Anchor mtk_put_string(DWindow* win, int h, int v, char* string, char rb, char gb, char bb, char rf, char gf, char bf);

/* Button functions */

struct Button{
    int ax;
    int ay;
    int bx;
    int by;
    int border;
    char* text;
	int hxanchor;//Anchor for next button (right)
	int hyanchor;
	int vxanchor;//Anchor for next button (down)
	int vyanchor;
	unsigned char r;
	unsigned char g;
	unsigned char b;
};
typedef struct Button Button;

struct ButtonArray{
    Button** bts;
    int last_button;
};
typedef struct ButtonArray ButtonArray;

ButtonArray* mtk_init_buttons();

void mtk_free_buttons(ButtonArray* a);

void mtk_redraw_buttonarray(DWindow* win, ButtonArray* ba);

Button* mtk_add_button(DWindow* win, ButtonArray* buttons, int h, int v, char* str, int border);

Button* mtk_add_coloured_button(DWindow* win, ButtonArray* buttons, int h, int v, char* str, int border, char r, char g, char b);

int mtk_get_button(DWindow* win, ButtonArray* buttons, int x, int y);

#ifdef __cplusplus
}
#endif
#endif //DMTK_H

#ifdef DMTK_IMPLEMENTATION

/*old dmtkgui.c*/

#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

#define TYPE_NORMAL 0
#define TYPE_DESKAPP 1 //Makes the window spawn at the top-left of the screen, without border.

typedef struct{
	SDL_Window* win;
	SDL_Renderer* renderer;
	SDL_Texture* rsave;
	char* drawbuf;
} SDLWin;

static void DGUIProcess(DWindow* win, char type, char* name);

void DEndProcess(DWindow* win){
	win->guirq = 1;
	win->grq.type = CLOSE_RQ;
}

static DWindow* DInitGen(int x, int y, char type, char* name){
	int protection = PROT_READ | PROT_WRITE;
	int visibility = MAP_SHARED | MAP_ANONYMOUS;
    DWindow* w = mmap(NULL, sizeof(DWindow), protection, visibility, -1, 0);
    if(w == MAP_FAILED){
        perror("mmap");
        exit(1);
    }
	w->rx = x;
	w->ry = y;
	w->guirq = 0;
	w->drawrq = 0;
	w->alive = 0;
	w->drq.data = mmap(NULL, MTK_IMAGE_CHUNK_SIZE, protection, visibility, -1, 0);
	if(w->drq.data == MAP_FAILED){
        perror("mmap");
        exit(1);
    }
    
	int pid = fork();
    
	if (pid == 0) {
		DGUIProcess(w,type,name);
	}
	while(!w->alive)usleep(10);
	return w;
}

DWindow* DInit(int x, int y, char* name){
	return DInitGen(x, y, TYPE_NORMAL, name);
}

DWindow* DInitBorderless(int x, int y, char* name){
	return DInitGen(x, y, TYPE_DESKAPP, name);
}

static SDLWin init_sdl(int rx, int ry, int type, char* name){   
	SDLWin sdlw = {0};
	sdlw.drawbuf = malloc(MTK_IMAGE_CHUNK_SIZE);
	if(sdlw.drawbuf == NULL){
        perror("malloc");
        exit(1);
    }
    
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0){
		perror("sdl_init");
		exit(1);
	}

	sdlw.win = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, rx, ry, \
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if(sdlw.win == NULL){
		perror("sdl_window");
		exit(1);
	}
    
	sdlw.renderer = SDL_CreateRenderer(sdlw.win, -1, SDL_RENDERER_ACCELERATED);
	if(sdlw.renderer == NULL){
		perror("sdl_window");
		exit(1);
	}

	SDL_SetRenderDrawBlendMode(sdlw.renderer,SDL_BLENDMODE_BLEND);

	sdlw.rsave = SDL_CreateTexture(sdlw.renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, rx, ry);

	SDL_SetTextureBlendMode(sdlw.rsave, SDL_BLENDMODE_BLEND);
	
	if(type == TYPE_DESKAPP){
		SDL_SetWindowBordered(sdlw.win, SDL_FALSE);
	}

	SDL_SetRenderTarget(sdlw.renderer, sdlw.rsave);
	SDL_SetRenderDrawColor(sdlw.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(sdlw.renderer);
	SDL_SetRenderTarget(sdlw.renderer, NULL);
	SDL_RenderCopy(sdlw.renderer, sdlw.rsave, NULL, NULL);
	SDL_RenderPresent(sdlw.renderer);
	SDL_SetRenderTarget(sdlw.renderer, sdlw.rsave);

	SDL_StartTextInput();

	return sdlw;
}

static void close_sdl(SDLWin sdlw) {
	free(sdlw.drawbuf);
	SDL_DestroyRenderer(sdlw.renderer);
	SDL_DestroyWindow(sdlw.win);
	SDL_Quit();
	exit(0);
}

static void DAcceptDrawRequest(SDLWin sdlw, DWindow* win){
	//Check if the user has been silly, and have not waited for the redraw to RESIZE_RQ
	//If the request is a name change, we can however let it pass
	if(win->guirq == 1 && win->grq.type == RESIZE_RQ && win->drq.type != WNAME_RQ){
		//printf("DRAW INTERRUPTED !\n");
		win->drawrq = 0;
		return;
	}
	
	//WARNING: This does not make a copy of the data buffer.
	//Set win->drawrq to 0 only when the data buffer has been used.
	DrawRequest drq = win->drq;
	
	switch(drq.type){
		case PIXEL_RQ:
		{
			memcpy(sdlw.drawbuf,drq.data,drq.sx*drq.sy*4);
			SDL_Rect rect;
			rect.w = drq.sx;
			rect.h = drq.sy;
			rect.x = drq.h;
			rect.y = drq.v;
			SDL_UpdateTexture(sdlw.rsave, &rect, sdlw.drawbuf, drq.sx*4);
			SDL_SetRenderTarget(sdlw.renderer, NULL);
			SDL_RenderCopy(sdlw.renderer, sdlw.rsave, NULL, NULL);
			SDL_RenderPresent(sdlw.renderer);
			SDL_SetRenderTarget(sdlw.renderer, sdlw.rsave);
			win->drawrq = 0;
			return;
		}
		case RECTANGLE_RQ:
			{
				SDL_Rect rect;
				rect.w = drq.sx;
				rect.h = drq.sy;
				rect.x = drq.h;
				rect.y = drq.v;
				SDL_SetRenderDrawColor(sdlw.renderer, drq.r, drq.g, drq.b, SDL_ALPHA_OPAQUE);
				SDL_RenderFillRect(sdlw.renderer, &rect);
				SDL_SetRenderTarget(sdlw.renderer, NULL);
				SDL_RenderCopy(sdlw.renderer, sdlw.rsave, NULL, NULL);
				SDL_RenderPresent(sdlw.renderer);
				SDL_SetRenderTarget(sdlw.renderer, sdlw.rsave);
			}
			win->drawrq = 0;
			return;
		case WNAME_RQ:
			win->drawrq = 0;
			SDL_SetWindowTitle(sdlw.win, drq.data);
			return;
		case FLUSH_RQ:
			SDL_SetRenderTarget(sdlw.renderer, NULL);
			SDL_RenderCopy(sdlw.renderer, sdlw.rsave, NULL, NULL);
			SDL_RenderPresent(sdlw.renderer);
			SDL_SetRenderTarget(sdlw.renderer, sdlw.rsave);
			SDL_RenderFlush(sdlw.renderer);
			win->drawrq = 0;
			return;
		case MOVE_RQ:
			win->drawrq = 0;
			//TODO: Implement or remove from API
			return;
		default:
			return;
	}
}

static void DEmitResizeRequest(DWindow* win, int x, int y){
	if(x>=0)win->rx = x;
	if(y>=0)win->ry = y;
	win->grq.type = RESIZE_RQ;
	win->guirq = 1;
}

static void DGUIProcess(DWindow* win, char type, char* name){
	SDLWin sdlw = init_sdl(win->rx, win->ry, type, name);
	//usleep(50000);

	win->alive = 1;
	//resize on start
	DEmitResizeRequest(win, win->rx, win->ry);
	while(1) {
		usleep(5000);
		SDL_Event e;
		while(SDL_PollEvent(&e)){
			if( e.type == SDL_QUIT || (win->guirq && win->grq.type == CLOSE_RQ)){
				win->guirq = 0;
				win->drawrq = 0;
				win->alive = 0;
				close_sdl(sdlw);
			}else if(e.type == SDL_WINDOWEVENT){
				int nx,ny;
				switch (e.window.event){
					case SDL_WINDOWEVENT_EXPOSED:
						DEmitResizeRequest(win, win->rx, win->ry);
						break;
					case SDL_WINDOWEVENT_RESIZED:
					case SDL_WINDOWEVENT_SIZE_CHANGED:
						nx = e.window.data1;
						ny = e.window.data2;
						//Destroy previous texture
						SDL_SetRenderTarget(sdlw.renderer, NULL);
						SDL_DestroyTexture(sdlw.rsave);
						//Create new texture, clear it and update
						sdlw.rsave = SDL_CreateTexture(sdlw.renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, nx, ny);
						SDL_SetTextureBlendMode(sdlw.rsave, SDL_BLENDMODE_BLEND);
						SDL_SetRenderTarget(sdlw.renderer, sdlw.rsave);
						SDL_SetRenderDrawColor(sdlw.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
						SDL_RenderClear(sdlw.renderer);
						SDL_SetRenderTarget(sdlw.renderer, NULL);
						SDL_RenderCopy(sdlw.renderer, sdlw.rsave, NULL, NULL);
						SDL_RenderPresent(sdlw.renderer);
						SDL_SetRenderTarget(sdlw.renderer, sdlw.rsave);
						DEmitResizeRequest(win, nx, ny);
						break;
					default:
						break;
				}
			}else if(e.type == SDL_KEYDOWN){
				int tries = 100;
				while(win->guirq && tries > 0){usleep(2500);tries--;}
				if(!win->guirq){
					win->grq.type = KEYB_RQ;
					win->grq.data = e.key.keysym.sym;
					memset(win->grq.utfkey, 0, 4);
					win->guirq = 1;
				}
			}else if(e.type == SDL_TEXTINPUT){
				int tries = 100;
				while(win->guirq && tries > 0){usleep(2500);tries--;}
				if(!win->guirq){
					win->grq.type = KEYB_RQ;
					win->grq.data = 0;
					memset(win->grq.utfkey, 0, 4);
					memcpy(win->grq.utfkey, e.text.text, 4);
					win->guirq = 1;
				}
			}else if(e.type == SDL_MOUSEBUTTONDOWN){
				if(!win->guirq){
					win->grq.type = MOUSE_RQ;
					switch(e.button.button){
						case SDL_BUTTON_LEFT:
							win->grq.data = 1;break;
						case SDL_BUTTON_MIDDLE:
							win->grq.data = 2;break;
						case SDL_BUTTON_RIGHT:
							win->grq.data = 3;break;
						case SDL_BUTTON_X1:
							win->grq.data = 4;break;
						case SDL_BUTTON_X2:
							win->grq.data = 5;break;
						default:
							win->grq.data = 0;break;
					}
					win->grq.x = e.button.x;
					win->grq.y = e.button.y;
					win->guirq = 1;
				}
				break;
			}
		}
		if(win->drawrq){
			while(win->drq.type != FLUSH_RQ)if(win->drawrq)DAcceptDrawRequest(sdlw, win);
			DAcceptDrawRequest(sdlw, win);
		}
	}
}

//Main process functions

void DDrawPixels(DWindow* win, int h, int v, int sx, int sy, unsigned char* data){
	if(sx*sy*4 < MTK_IMAGE_CHUNK_SIZE){
		win->drq.type = PIXEL_RQ;
		win->drq.h = h;
		win->drq.v = v;
		win->drq.sx = sx;
		win->drq.sy = sy;
		memcpy(win->drq.data,data,sx*sy*4);
		win->drawrq = 1;
		while(win->alive && win->drawrq);
	}else{
		//how many lines can we store in the buffer ?
		int lines = MTK_IMAGE_CHUNK_SIZE / (sx*4);
		unsigned int vshift = 0; //shift for data
		//while there is lines to draw
		while(sy > 0){
			win->drq.type = PIXEL_RQ;
			win->drq.h = h;
			win->drq.v = v;
			win->drq.sx = sx;
			win->drq.sy = sy < lines ? sy : lines;
			memcpy(win->drq.data,data+vshift,win->drq.sx*win->drq.sy*4);
			//printf("%d,%d %dx%d %d\n",win->drq.h,win->drq.v,win->drq.sx,win->drq.sy,vshift);
			//fflush(stdout);
			win->drawrq = 1;
			while(win->alive && win->drawrq);
			v += win->drq.sy;
			vshift += win->drq.sy*sx*4;
			sy -= win->drq.sy;
		}
	}
}

void DDrawRectangleReal(DWindow* win, int h, int v, int sx, int sy, unsigned char r, unsigned char g, unsigned char b){
	win->drq.type = RECTANGLE_RQ;
	win->drq.h = h;
	win->drq.v = v;
	win->drq.sx = sx;
	win->drq.sy = sy;
	win->drq.r = r;
	win->drq.g = g;
	win->drq.b = b;
	win->drawrq = 1;
	while(win->alive && win->drawrq);
}

//FIXME: Figure out why SDL needs that, and if it really can't be fixed
void DDrawRectangle(DWindow* win, int h, int v, int sx, int sy, unsigned char r, unsigned char g, unsigned char b){
	DDrawRectangleReal(win, h, v, sx, sy, r, g, b);
	DDrawRectangleReal(win, h, v, sx, sy, r, g, b);
	DDrawRectangleReal(win, h, v, sx, sy, r, g, b);
}

void DChangeName(DWindow* win, char* str){
	win->drq.type = WNAME_RQ;
	strcpy(win->drq.data,str);
	win->drawrq = 1;
	while(win->alive && win->drawrq);
}

void DFlush(DWindow* win){
	win->drq.type = FLUSH_RQ;
	win->drawrq = 1;
	while(win->alive && win->drawrq);
}

void DMove(DWindow* win, int h, int v, int sx, int sy, int dx, int dy){
	win->drq.type = MOVE_RQ;
	win->drq.h = h;
	win->drq.v = v;
	win->drq.sx = sx;
	win->drq.sy = sy;
	win->drq.dx = dx;
	win->drq.dy = dy;
	win->drawrq = 1;
	while(win->alive && win->drawrq);
}

GUIRequest DGetRequest(DWindow* win){
	GUIRequest grq = {0};
	if(win->guirq){
		grq.type = win->grq.type;
		grq.data = win->grq.data;
		memcpy(grq.utfkey, win->grq.utfkey,4);
		grq.x = win->grq.x;
		grq.y = win->grq.y;
		win->guirq = 0;
	}else{
		grq.type = NO_RQ;
	}
	return grq;
}



/*old dmtk.c*/

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ASSERT(x)
#define STBI_FAILURE_USERMSG
#define STBI_NO_HDR
#define STBI_NO_PSD
#define STBI_NO_TGA
#define STBI_NO_PIC
#define STBI_NO_PNM
#include "stb_image.h"
#define OIOI_IMPLEMENTATION
#include "oioi.h"
#include "unifont.h"
#include <string.h>
#include <stdio.h>

#define MTK_MAX_BUTTONS 64

static void crash(char* thingthatcrashed){
	perror(thingthatcrashed);
	exit(thingthatcrashed[0]);
}

Anchor mtk_put_image_buffer(DWindow* win, int h, int v, Image img){
	DDrawPixels(win, h, v, img.width, img.height, img.data);
	return (Anchor){.hxanchor = h + img.width+1, .hyanchor = v, .vxanchor = h, .vyanchor = v + img.height+1};
}

Image mtk_load_image(char* img){
    int sn;
	int x,y;
	char h = OIOI_HANDLED;
	unsigned char* d = oioi_read(img, &x, &y, 4);

	if(d == NULL){
		h = STBI_HANDLED;
		d = stbi_load(img, &x, &y, &sn, 4);
	}
	
	if(d == NULL){
		unsigned char* reason = malloc(strlen(stbi_failure_reason()));
		if(reason == NULL)crash("malloc");
		strcpy((char*)reason,stbi_failure_reason());
        return (Image){.data=reason, .width=-1, .height=-1, .handler = ERROR};
    }
    
	return (Image){.data=d, .width=x, .height=y, .handler = h};
}

void mtk_free_image(Image img){
	switch(img.handler){
		case STBI_HANDLED:
			stbi_image_free(img.data);break;
		case OIOI_HANDLED:
			free(img.data);break;
		default:
			break;
	}
}

Anchor mtk_put_image(DWindow* win, int h, int v, char* file){
    Image img = mtk_load_image(file);
    
    Anchor a = mtk_put_image_buffer(win, h, v, img);
    mtk_free_image(img);
	return a;
}

Anchor mtk_put_rectangle(DWindow* win, int h, int v, int sx, int sy, unsigned char r, unsigned char g, unsigned char b){
	DDrawRectangle(win, h, v, sx, sy, r, g, b);
	return (Anchor){.hxanchor = h + sx+1, .hyanchor = v, .vxanchor = h, .vyanchor = v + sy+1};
}

Anchor mtk_put_backbox(DWindow* win, int h, int v, int sx, int sy, int border){
	int db = 2 * border;
	DDrawRectangle(win, h-border, v-border, sx+db, sy+db, BGBTOP);
	Anchor a = mtk_put_rectangle(win, h, v, sx+border, sy+border, BGBBCK);
	DDrawRectangle(win, h, v, sx, sy, BGB);
	return a;
}
//STRING STUFF
unsigned char mtk_font_width(){return dfont.width;}

unsigned char mtk_font_height(){return dfont.height;}

int comp_index(const unsigned short* a, const unsigned short* b){
	return *a-*b;
}

int lookup_index(unsigned short c){
	unsigned short* p = bsearch(&c, dfont.index, dfont.chars, sizeof(unsigned short), (int (*)(const void *, const void *))comp_index);
    if(p == NULL)return lookup_index(' ');
	return p-dfont.index;
}

//Get Unicode codepoint of UTF-8 character
static unsigned int codepoint(char* str){
	if(*str & 128 && *str & 64){
		if(*str & 32){
			if(*str & 16)return (str[3] & 63) + ((str[2] & 63)<<6) + ((str[1] & 63)<<12) + ((str[0] & 7)<<18);
			return (str[2] & 63) + ((str[1] & 63)<<6) + ((str[0] & 15)<<12);
		}
		return (str[1] & 63) + ((str[0] & 31)<<6); 
	}
	return str[0];
}

//Get next UTF-8 character
static char* nextchar(char* str){
	if(*str & 128 && *str & 64){
		if(*str & 32){
			if(*str & 16)return str+4;
			return str+3;
		}
		return str+2; 
	}
	return str+1;
}

//Copy character bitmap to string bitmap
static char* copy_bitmap(char* bitmap, int offset, int bytes_per_line){
	for(int i = 0; i<((dfont.widths[offset]/8)*dfont.height); i++){
		*bitmap = dfont.bitmap[(offset*dfont.height*bytes_per_line)+ ((i%dfont.height)*bytes_per_line)+(i/dfont.height)];
		bitmap++;
	}
	return bitmap;
}

static char ispix(char* bitmap, int x, int y){
	return bitmap[((x/8)*dfont.height)+y] & (128 >> (x%8));
}

static unsigned char* render_str(char* bitmap, char* be, char r, char g, char b, int* x, int* y){
	char pix[4] = {r,g,b,255};
	char npix[4] = {0,0,0,0};
	
	*y = dfont.height;
	*x = ((be-bitmap)/dfont.height)*8;
	
	unsigned char* buf = malloc(*x * *y * 4);
	for(int py = 0; py < *y; py++){
		for(int px = 0; px < *x; px++){
			memcpy(buf + 4 *( (py * *x) + px), ispix(bitmap, px, py)? pix:npix,4);
		}
	}
	free(bitmap);
	return buf;
}

int mtk_str_width(char* string){
	int y = 0;
	while(*string != 0){
		y += dfont.widths[lookup_index(codepoint(string))];
		string = nextchar(string);
	}
	return y;
}

Anchor mtk_put_astring(DWindow* win, int h, int v, char* string, char r, char g, char b){
	if(*string == 0)return (Anchor){.hxanchor = h+1, .hyanchor = v, .vxanchor = h, .vyanchor = v+1};
	int bytes_per_line = (dfont.width/8);
	char* bitmap = malloc(strlen(string)*dfont.height*bytes_per_line);
	char* bend = bitmap;
	while(*string != 0){
		unsigned int unicode = codepoint(string);
		
		int offset = lookup_index(unicode);
		
		bend = copy_bitmap(bend,offset,bytes_per_line);
		
		string = nextchar(string);
	}
	int x,y;
	unsigned char* final = render_str(bitmap, bend, r, g, b, &x, &y);
	DDrawPixels(win, h, v, x , y, final);
	free(final);
	return (Anchor){.hxanchor = h + x+1, .hyanchor = v, .vxanchor = h, .vyanchor = v+y+1};
}

Anchor mtk_put_string(DWindow* win, int h, int v, char* string, char rb, char gb, char bb, char rf, char gf, char bf){
    Anchor a = mtk_put_rectangle(win, h, v, mtk_str_width(string), dfont.height, rb, gb, bb);
    mtk_put_astring(win, h, v, string, rf, gf, bf);
	return a;
}
//BUTTON STUFF
ButtonArray* mtk_init_buttons(){
    ButtonArray* a = malloc(sizeof(ButtonArray));
    if(a == NULL)crash("malloc");
    a->bts = malloc(MTK_MAX_BUTTONS*sizeof(Button*));
    if(a->bts == NULL)crash("malloc");
    a->last_button = -1;
    return a;
}

void mtk_free_buttons(ButtonArray* a){
    for(int i=0; i<a->last_button; i++)free(a->bts[i]);
    free(a->bts);
    free(a);
}

void mtk_draw_button(DWindow* win, Button button){
    DDrawRectangle(win, button.ax, button.ay, button.bx-button.ax, button.by-button.ay, BTNTOP);
    DDrawRectangle(win, button.ax+1, button.ay+1, button.bx-button.ax-1, button.by-button.ay-1, BTNBCK);
    DDrawRectangle(win, button.ax+1, button.ay+1, button.bx-button.ax-2, button.by-button.ay-2, button.r, button.g, button.b);
    mtk_put_astring(win, button.ax+button.border, button.ay+button.border, button.text, 0, 0, 0);
}

void mtk_redraw_buttonarray(DWindow* win, ButtonArray* ba){
	for(int i = 0; i<=ba->last_button; i++)mtk_draw_button(win,*(ba->bts[i]));
}

int mtk_get_button(DWindow* win, ButtonArray* buttons, int x, int y){
    for(int i = 0; i<=buttons->last_button; i++){
        if(x>=buttons->bts[i]->ax && x<=buttons->bts[i]->bx && y>=buttons->bts[i]->ay && y<=buttons->bts[i]->by)return i;
    }
    return -1;
}

Button* mtk_add_coloured_button(DWindow* win, ButtonArray* buttons, int h, int v, char* str, int border, char r, char g, char b){
	//realloc?
	if((buttons->last_button+1)%MTK_MAX_BUTTONS == 0 && buttons->last_button > 0){
		buttons->bts = realloc(buttons->bts,(buttons->last_button+1+MTK_MAX_BUTTONS)*sizeof(Button*));
		if(buttons->bts == NULL)crash("realloc");
	}
	
    // Spaces + Border + Character size
    int sx = border*2 + mtk_str_width(str);
    int sy = border*2 + dfont.height;
    buttons->last_button += 1;
	buttons->bts[buttons->last_button] = malloc(sizeof(Button));
	if(buttons->bts[buttons->last_button] == NULL)crash("malloc");
    *(buttons->bts[buttons->last_button]) = (Button){.ax = h, .ay = v, .bx = h + sx, .by = v + sy, .border=border, .text = str, .hxanchor = h + sx + 1, .hyanchor = v, .vxanchor = h, .vyanchor = v + sy + 1, .r = r, .g = g, .b = b};
    mtk_draw_button(win, *(buttons->bts[buttons->last_button]));
    return buttons->bts[buttons->last_button];
}

Button* mtk_add_button(DWindow* win, ButtonArray* buttons, int h, int v, char* str, int border){
    return mtk_add_coloured_button(win, buttons, h, v, str, border, BTN);
}
# endif //DMTK_IMPLEMENTATION
