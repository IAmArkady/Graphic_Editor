#include <QtCore/QCoreApplication>
#include <qtextstream.h>
#include <iostream>
#include <locale>
#include <Windows.h>
#include <qlist.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <cmath>
using namespace std;
#define width 650
#define height 580
#define M_PI_2 1.57079632679489661923

class draw {
private:
	static SDL_Renderer *ren;
	static SDL_Window *win;
	static SDL_Color color;
public:


	static void init(SDL_Renderer *r, SDL_Window *w) {
		ren = r;
		win = w;
		color = { 255, 255, 255, 0 };
		SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a);
	}

	static void set_color(SDL_Color c) {
		color = c;
		SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a);
	}

	static void draw_rect(SDL_Rect rect, int k) {
		switch (k)
		{
		case 1: k = 1; break;
		case 2: k = 3; break;
		case 3: k = 7; break;
		case 4: k = 10; break;
		}
		SDL_RenderDrawRect(ren, &rect);
		for (int i = 1; i < k; i++) {
			SDL_RenderDrawLine(ren, rect.x + i, rect.y + i, rect.x + rect.w - i, rect.y + i);
			SDL_RenderDrawLine(ren, rect.x + i, rect.y + rect.h - i, rect.x + rect.w - i, rect.y + rect.h - i);
			SDL_RenderDrawLine(ren, rect.x + i, rect.y + i, rect.x + i, rect.y + rect.h - i);
			SDL_RenderDrawLine(ren, rect.x + rect.w - i, rect.y + i, rect.x + rect.w - i, rect.y + rect.h - i);
		}
	}

	static void draw_line(SDL_Rect rect, int k) {
		switch (k)
		{
		case 1: k = 1; break;
		case 2: k = 3; break;
		case 3: k = 7; break;
		case 4: k = 10; break;
		}
		int dx, dy;
		dx = rect.w;
		dy = rect.h;
		SDL_RenderDrawLine(ren, rect.x, rect.y, rect.x + rect.w, rect.y + rect.h);
		if (k > 1 && !(dx == 0 && dy == 0)) {
			double r = k, phi, ri;
			if (dy == 0)
				phi = dx > 0 ? 0 : M_PI;
			else
				if (dx == 0)
					phi = dy > 0 ? M_PI_2 : M_PI + M_PI_2;
				else
					phi = acos(dx / sqrt(dx*dx + dy * dy));
			if (dy > 0)
				phi = 2 * M_PI - phi;

			for (ri = 0; ri < r; ri += 0.1)
			{
				Sint16 px1, py1, px2, py2;
				px1 = floor(abs(rect.x) + ri * cos(phi + M_PI_2));
				py1 = floor(abs(rect.y) - ri * sin(phi + M_PI_2));
				px2 = floor(abs(rect.x + rect.w) + ri * cos(phi + M_PI_2));
				py2 = floor(abs(rect.y + rect.h) - ri * sin(phi + M_PI_2));
				SDL_RenderDrawLine(ren, px1, --py1, px2, --py2);
				SDL_RenderDrawLine(ren, px1, ++py1, px2, ++py2);
			}
		}

	}

	static void draw_triangle(SDL_Rect rect, int k) {
		int dx = rect.w, dy = rect.h;
		switch (k)
		{
		case 1: k = 1; break;
		case 2: k = 3; break;
		case 3: k = 7; break;
		case 4: k = 10; break;
		}
		SDL_RenderDrawLine(ren, rect.x, rect.y + rect.h, rect.x + rect.w, rect.y + rect.h);
		if (k > 1 && !(dx == 0 && dy == 0)) {
			double r = k, phi, ri;
			if (dy == 0)
				phi = dx > 0 ? 0 : M_PI;
			else
				if (dx == 0)
					phi = dy > 0 ? M_PI_2 : M_PI + M_PI_2;
				else
					phi = acos(dx / sqrt(dx*dx + dy * dy));
			if (dy > 0)
				phi = 2 * M_PI - phi;

			for (ri = 0; ri < r; ri += 0.1)
			{
				Sint16 px1, py1, px2, py2;
				px1 = floor(abs(rect.x) + ri * cos(phi + M_PI_2));
				py1 = floor(abs(rect.y + rect.h) + ri * sin(phi + M_PI_2));
				px2 = floor(abs(rect.x + rect.w) + ri * cos(phi + M_PI_2));
				py2 = floor(abs(rect.y + rect.h) + ri * sin(phi + M_PI_2));
				SDL_RenderDrawLine(ren, px1, --py1, px2, --py2);
				SDL_RenderDrawLine(ren, px1, ++py1, px2, ++py2);
			}
		}


		SDL_RenderDrawLine(ren, rect.x, rect.y + rect.h, (rect.x + rect.w + rect.x) / 2, rect.y);
		if (k > 1 && !(dx == 0 && dy == 0)) {
			double r = k, phi, ri;
			if (dy == 0)
				phi = dx > 0 ? 0 : M_PI;
			else
				if (dx == 0)
					phi = dy > 0 ? M_PI_2 : M_PI + M_PI_2;
				else
					phi = acos(dx / sqrt(dx*dx + dy * dy));
			if (dy > 0)
				phi = 2 * M_PI - phi;

			for (ri = 0; ri < r; ri += 0.1)
			{
				Sint16 px1, py1, px2, py2;
				px1 = floor(abs(rect.x) + ri * cos(phi + M_PI_2));
				py1 = floor(abs(rect.y + rect.h) + ri * sin(phi + M_PI_2));
				px2 = floor(abs(rect.x + rect.w + rect.x) / 2 + ri * cos(phi + M_PI_2));
				py2 = floor(abs(rect.y) + ri * sin(phi + M_PI_2));
				SDL_RenderDrawLine(ren, px1, --py1, px2, --py2);
				SDL_RenderDrawLine(ren, px1, ++py1, px2, ++py2);
			}
		}


		SDL_RenderDrawLine(ren, rect.x + rect.w, rect.y + rect.h, (rect.x + rect.w + rect.x) / 2, rect.y);
		if (k > 1 && !(dx == 0 && dy == 0)) {
			double r = k, phi, ri;
			if (dy == 0)
				phi = dx > 0 ? 0 : M_PI;
			else
				if (dx == 0)
					phi = dy > 0 ? M_PI_2 : M_PI + M_PI_2;
				else
					phi = acos(dx / sqrt(dx*dx + dy * dy));
			if (dy > 0)
				phi = 2 * M_PI - phi;

			for (ri = 0; ri < r; ri += 0.1)
			{
				Sint16 px1, py1, px2, py2;
				px1 = floor(abs(rect.x + rect.w) - ri * cos(phi + M_PI_2));
				py1 = floor(abs(rect.y + rect.h) + ri * sin(phi + M_PI_2));
				px2 = floor(abs(rect.x + rect.w + rect.x) / 2 - ri * cos(phi + M_PI_2));
				py2 = floor(abs(rect.y) + ri * sin(phi + M_PI_2));
				SDL_RenderDrawLine(ren, px1, --py1, px2, --py2);
				SDL_RenderDrawLine(ren, px1, ++py1, px2, ++py2);
			}
		}

	}

	static void draw_circle(SDL_Rect rect, int k)
	{
		switch (k)
		{
		case 1: k = 1; break;
		case 2: k = 3; break;
		case 3: k = 7; break;
		case 4: k = 10; break;
		}

		while (k != 0) {
			double error = (double)-rect.w;
			double x = (double)rect.w - 0.5;
			double y = (double)0.5;
			double cx = rect.x - 0.5;
			double cy = rect.y - 0.5;

			if (x >= y) {
				while (x >= y)
				{
					SDL_RenderDrawPoint(ren, (int)(cx + x), (int)(cy + y));
					SDL_RenderDrawPoint(ren, (int)(cx + y), (int)(cy + x));

					if (x != 0)
					{
						SDL_RenderDrawPoint(ren, (int)(cx - x), (int)(cy + y));
						SDL_RenderDrawPoint(ren, (int)(cx + y), (int)(cy - x));
					}

					if (y != 0)
					{
						SDL_RenderDrawPoint(ren, (int)(cx + x), (int)(cy - y));
						SDL_RenderDrawPoint(ren, (int)(cx - y), (int)(cy + x));
					}

					if (x != 0 && y != 0)
					{
						SDL_RenderDrawPoint(ren, (int)(cx - x), (int)(cy - y));
						SDL_RenderDrawPoint(ren, (int)(cx - y), (int)(cy - x));
					}

					error += y;
					++y;
					error += y;

					if (error >= 0)
					{
						--x;
						error -= x;
						error -= x;
					}
				}
			}
			rect.w += 1;
			--k;
		}

	}

	static void fill_circle(SDL_Rect rect, int rad) {
		switch (rad)
		{
		case 1: rad = 2; break;
		case 2: rad = 4; break;
		case 3: rad = 7; break;
		case 4: rad = 15; break;
		}

		for (double dy = 1; dy <= rad; dy += 1.0)
		{
			double dx = floor(sqrt((2.0 * rad * dy) - (dy * dy)));
			int x = rect.x + rect.w - dx;
			SDL_RenderDrawLine(ren, rect.x + rect.w - dx, rect.y + rect.h + dy - rad, rect.x + rect.w + dx, rect.y + rect.h + dy - rad);
			SDL_RenderDrawLine(ren, rect.x + rect.w - dx, rect.y + rect.h - dy + rad, rect.x + rect.w + dx, rect.y + rect.h - dy + rad);
		}
	}


	static void draw_brush(SDL_Rect rect, int k) {
		fill_circle(rect, k);
	}

	static void draw_pencil(SDL_Rect rect, int rad) {
		switch (rad)
		{
		case 1: rad = 1; break;
		case 2: rad = 2; break;
		case 3: rad = 3; break;
		case 4: rad = 5; break;
		}
		for (double dy = 1; dy <= rad; dy += 1.0)
		{
			double dx = floor(sqrt((2.0 * rad * dy) - (dy * dy)));
			int x = rect.x + rect.w - dx;
			SDL_RenderDrawLine(ren, rect.x + rect.w - dx, rect.y + rect.h + dy - rad, rect.x + rect.w + dx, rect.y + rect.h + dy - rad);
			SDL_RenderDrawLine(ren, rect.x + rect.w - dx, rect.y + rect.h - dy + rad, rect.x + rect.w + dx, rect.y + rect.h - dy + rad);
		}
	}

	static void draw_eraser(SDL_Rect rect, int k) {
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		switch (k)
		{
		case 1: k = 2; break;
		case 2: k = 4; break;
		case 3: k = 11; break;
		case 4: k = 20; break;
		}
		rect.x = rect.x - k / 2 + rect.w;
		rect.y = rect.y - k / 2 + rect.h;
		rect.w = k;
		rect.h = k;
		SDL_RenderFillRect(ren, &rect);
	}


};

SDL_Renderer* draw::ren = NULL;
SDL_Window* draw::win = NULL;
SDL_Color draw::color = { 255, 255, 255, 255 };


class Paint {
private:
	struct rect_color {
		SDL_Rect rect;
		SDL_Color color;
	};

	struct rect_figure {
		SDL_Rect rect;
		void(*func)(SDL_Rect, int);
	};

	struct bold {
		SDL_Rect rect;
		int k;
	};

	struct text {
		SDL_Rect rect;
	};

	SDL_Renderer *ren;
	SDL_Window *win;
	SDL_Texture* mainTex;
	SDL_Rect mainRect, up_rect;
	TTF_Font *font;
	QList <struct rect_color*> col_list;
	QList <struct rect_figure*>fig_list;
	QList <struct text*>text_list;
	QList <struct bold*> bold_list;

	void figure_menu() {
		int kol = 7, w = 20, tempw, tempy, tempx;
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		for (int i = 0; i < 7; i++) {
			fig_list.append(new struct rect_figure);
			fig_list.at(i)->rect = { width / 2 - w, 20, 20, 20 };
			w += 27;
		}
		tempw = fig_list.at(2)->rect.w;
		tempy = fig_list.at(2)->rect.y;
		tempx = fig_list.at(2)->rect.x;

		fig_list.at(6)->func = draw::draw_brush;
		fig_list.at(6)->rect = { width / 2 - 280, 20, 11, 10 };
		draw::fill_circle(fig_list.at(6)->rect, fig_list.at(6)->rect.w);
		fig_list.at(6)->rect = { width / 2 - 280, 20, 20, 20 };

		fig_list.at(5)->func = draw::draw_pencil;
		fig_list.at(5)->rect = { width / 2 - 245, 20, 10, 20 };
		SDL_RenderDrawLine(ren, width / 2 - 245, 20, (width / 2 - 245 + width / 2 - 245 + 10) / 2, 10);
		SDL_RenderDrawLine(ren, width / 2 - 245 + 9, 20, (width / 2 - 245 + width / 2 - 245 + 10) / 2, 10);
		SDL_RenderFillRect(ren, &fig_list.at(5)->rect);

		fig_list.at(4)->func = draw::draw_eraser;
		fig_list.at(4)->rect = { width / 2 - 220, 20, 20, 20 };
		SDL_RenderFillRect(ren, &fig_list.at(4)->rect);

		fig_list.at(3)->func = draw::draw_line;
		fig_list.at(3)->func(fig_list.at(3)->rect, 0);
		fig_list.at(2)->func = draw::draw_circle;
		fig_list.at(2)->rect.w = 12;
		fig_list.at(2)->rect.y = 29;
		fig_list.at(2)->rect.x = width / 2 - 65;
		fig_list.at(2)->func(fig_list.at(2)->rect, 1);
		fig_list.at(2)->rect.w = tempw;
		fig_list.at(2)->rect.y = tempy;
		fig_list.at(2)->rect.x = tempx;
		fig_list.at(1)->func = draw::draw_rect;
		fig_list.at(1)->func(fig_list.at(1)->rect, 0);
		fig_list.at(0)->func = draw::draw_triangle;
		fig_list.at(0)->func(fig_list.at(0)->rect, 0);
		SDL_RenderPresent(ren);
		SDL_UpdateWindowSurface(win);
	}

	void color_menu() {
		int kol = 7;
		for (int i = 0; i < kol; i++)
			col_list.append(new struct rect_color);
		col_list.at(0)->color = { 255, 255, 255, 255 };
		col_list.at(1)->color = { 255, 0, 0, 255 };
		col_list.at(2)->color = { 255, 255, 0, 255 };
		col_list.at(3)->color = { 0, 255, 0, 255 };
		col_list.at(4)->color = { 0, 0, 0, 255 };
		col_list.at(5)->color = { 0, 0, 255, 255 };
		col_list.at(6)->color = { 255, 255, 255, 255 };
		col_list.at(0)->rect = { width / 2 + 20, 10, 40, 40 };
		col_list.at(1)->rect = { width / 2 + 70, 33, 18, 18 };
		col_list.at(2)->rect = { width / 2 + 93, 10, 18, 18 };
		col_list.at(3)->rect = { width / 2 + 117, 10, 18, 18 };
		col_list.at(4)->rect = { width / 2 + 117, 33, 18, 18 };
		col_list.at(5)->rect = { width / 2 + 70, 10, 18, 18 };
		col_list.at(6)->rect = { width / 2 + 93, 33, 18, 18 };

		for (int i = 0; i < 7; i++) {
			SDL_SetRenderDrawColor(ren, col_list.at(i)->color.r, col_list.at(i)->color.g, col_list.at(i)->color.b, col_list.at(i)->color.a);
			SDL_RenderFillRect(ren, &col_list.at(i)->rect);
		}
		SDL_RenderPresent(ren);
		SDL_UpdateWindowSurface(win);
	}

	void bold_menu() {
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		int a = 5, k = 1, h = 9;
		for (int i = 0; i < 4; i++) {
			bold_list.append(new struct bold);
		}
		bold_list.at(0)->k = 1;
		bold_list.at(1)->k = 2;
		bold_list.at(2)->k = 3;
		bold_list.at(3)->k = 4;

		for (int i = 0; i < 4; i++) {
			bold_list.at(i)->rect = { 150,  a, 50, 0 };
			draw::draw_line(bold_list.at(i)->rect, bold_list.at(i)->k);
			bold_list.at(i)->rect.y -= 6;
			bold_list.at(i)->rect.h = h;
			a += 17;
			SDL_RenderPresent(ren);
			SDL_UpdateWindowSurface(win);
		}
	}

	void text_menu() {
		SDL_Surface *text;
		SDL_Color color;
		SDL_Rect rect;
		for (int i = 0; i < 3; i++) {
			text_list.append(new struct text);
		}
		rect = { width - 70, 35, 65, 25 };
		text_list.at(0)->rect = rect;
		color = { 255, 255, 255,0 };
		text = TTF_RenderText_Blended(font, "Очистить", color);
		SDL_RenderCopy(ren, SDL_CreateTextureFromSurface(ren, text), NULL, &rect);
		color = { 0, 0, 0,0 };
		SDL_RenderDrawRect(ren, &rect);


		rect = { width - 170, 35, 65, 25 };
		text_list.at(1)->rect = rect;
		color = { 255, 255, 255,0 };
		text = TTF_RenderText_Blended(font, "Сохранить", color);
		SDL_RenderCopy(ren, SDL_CreateTextureFromSurface(ren, text), NULL, &rect);
		color = { 0, 0, 0,0 };
		SDL_RenderDrawRect(ren, &rect);
		SDL_RenderPresent(ren);

		rect = { width - 120, 7, 65, 25 };
		text_list.at(2)->rect = rect;
		color = { 255, 255, 255,0 };
		text = TTF_RenderText_Blended(font, "Загрузить", color);
		SDL_RenderCopy(ren, SDL_CreateTextureFromSurface(ren, text), NULL, &rect);
		color = { 0, 0, 0,0 };
		SDL_RenderDrawRect(ren, &rect);
		SDL_RenderPresent(ren);

	}

	bool check(int x, int y, SDL_Rect place) {
		if (x - place.w <= place.x && x >= place.x && y - place.h <= place.y && y >= place.y)
			return true;
		else
			return false;
	}

public:
	Paint() :ren(NULL), win(NULL) {}
	Paint(SDL_Renderer *r, SDL_Window *w) :ren(r), win(w) {
		draw::init(ren, win);
		up_rect = { 0, 0, width, height / 9 };
		mainRect = { 0, height / 9 , width, height - height / 9 };
		mainTex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
		TTF_Init();
		font = TTF_OpenFont("hemes.ttf", 100);
	}
	void start() {
		SDL_Color color, color1;
		SDL_Event event;
		SDL_Rect rect;
		SDL_Texture* temp = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
		int x, y, fig = 0, bold = 1, mod = 0;;
		bool mouse_down = false, brush = false;
		SDL_SetRenderTarget(ren, NULL);
		SDL_SetRenderTarget(ren, temp);
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		SDL_RenderClear(ren);
		SDL_SetRenderTarget(ren, NULL);
		SDL_RenderCopy(ren, temp, NULL, NULL);
		SDL_SetRenderTarget(ren, mainTex);
		SDL_RenderCopy(ren, temp, NULL, NULL);
		SDL_SetRenderTarget(ren, NULL);
		SDL_SetRenderDrawColor(ren, 125, 125, 125, 255);
		SDL_RenderFillRect(ren, &up_rect);
		SDL_SetRenderDrawColor(ren, 90, 90, 90, 255);
		SDL_RenderDrawLine(ren, width / 2 + 10, 0, width / 2 + 10, height / 9 - 1);
		SDL_RenderDrawLine(ren, width / 2 + 145, 0, width / 2 + 145, height / 9 - 1);
		SDL_RenderDrawLine(ren, width / 2 - 110, 0, width / 2 - 110, height / 9 - 1);
		SDL_RenderDrawLine(ren, width / 2 - 185, 0, width / 2 - 185, height / 9 - 1);
		color_menu();
		figure_menu();
		bold_menu();
		text_menu();
		SDL_UpdateWindowSurface(win);


		while (1) {
			SDL_WaitEvent(&event);
			switch (event.type) {
			case SDL_QUIT:exit(0);

			case SDL_MOUSEBUTTONDOWN:
				SDL_GetMouseState(&x, &y);
				if (check(x, y, up_rect)) {
					for (int i = 1; i < 7; i++) {
						if (check(x, y, col_list.at(i)->rect)) {
							col_list.at(0)->color = col_list.at(i)->color;
							SDL_SetRenderDrawColor(ren, col_list.at(0)->color.r, col_list.at(0)->color.g, col_list.at(0)->color.b, col_list.at(0)->color.a);
							SDL_RenderFillRect(ren, &col_list.at(0)->rect);
							draw::set_color(col_list.at(0)->color);
							SDL_RenderPresent(ren);
							SDL_UpdateWindowSurface(win);
						}
					}

					for (int i = 0; i < 7; i++) {
						if (check(x, y, fig_list.at(i)->rect)) {
							fig = i;
							if (i >= 4)
								brush = true;
							else
								brush = false;
						}
					}

					for (int i = 0; i < 4; i++) {
						if (check(x, y, bold_list.at(i)->rect)) {
							bold = bold_list.at(i)->k;
						}
					}

					for (int i = 0; i < 3; i++) {
						if (check(x, y, text_list.at(i)->rect)) {
							switch (i) {
							case 0:
								SDL_SetRenderTarget(ren, mainTex);
								SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
								SDL_RenderFillRect(ren, &mainRect);
								SDL_SetRenderTarget(ren, NULL);
								SDL_RenderCopy(ren, mainTex, &mainRect, &mainRect);
								SDL_RenderPresent(ren);
								SDL_UpdateWindowSurface(win);
								SDL_SetRenderDrawColor(ren, col_list.at(0)->color.r, col_list.at(0)->color.g, col_list.at(0)->color.b, col_list.at(0)->color.a);
								break;
							case 1: {
								SDL_Window *w = SDL_CreateWindow("Path", 100, 100, width, height / 2, SDL_WINDOW_SHOWN);;
								SDL_Surface *text, *windowSurf = SDL_GetWindowSurface(w);
								string str = "";
								SDL_Rect rect1 = { 0, 0, 50, 35 };
								SDL_Color c = { 0, 0, 0, 0 };
								TTF_Font* f = TTF_OpenFont("hemes.ttf", 30);
								SDL_FillRect(windowSurf, NULL, SDL_MapRGB(windowSurf->format, 255, 255, 255));
								text = TTF_RenderText_Blended(f, "Введите имя и путь файла:", c);
								SDL_BlitSurface(text, NULL, windowSurf, &rect1);
								rect1 = { 0, 35, 50, 35 };
								SDL_UpdateWindowSurface(w);
								while (1) {
									SDL_WaitEvent(&event);
									if (event.window.windowID == SDL_GetWindowID(w)) {
										if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
											SDL_DestroyWindow(w);
											break;
										}
										if (event.window.type == SDL_KEYUP) {
											if (event.key.keysym.sym == SDLK_LSHIFT)
												mod = 0;
										}

										if (event.window.type == SDL_KEYDOWN) {
											if (event.key.keysym.sym == SDLK_BACKSPACE) {
												string t;
												if (str != "") {
													for (i = 0; i < str.length() - 1; i++)
														t += str[i];
													str = t;
													SDL_FillRect(windowSurf, &rect1, SDL_MapRGB(windowSurf->format, 255, 255, 255));
													text = TTF_RenderUTF8_Solid(f, str.c_str(), c);
													SDL_BlitSurface(text, NULL, windowSurf, &rect1);
													SDL_UpdateWindowSurface(w);
												}

											}

											if (event.key.keysym.sym == SDLK_RETURN) {
												SDL_DestroyWindow(w);
												if (str != "") {
													SDL_Texture* target = SDL_GetRenderTarget(ren);
													SDL_SetRenderTarget(ren, mainTex);
													SDL_Surface* surface = SDL_CreateRGBSurface(0, mainRect.w, mainRect.h, 32, 0, 0, 0, 0);
													SDL_RenderReadPixels(ren, &mainRect, surface->format->format, surface->pixels, surface->pitch);
													IMG_SaveJPG(surface, str.data(), 100);
													SDL_FreeSurface(surface);
													SDL_SetRenderTarget(ren, target);
												}
												break;
											}

											if (event.key.keysym.sym == SDLK_LSHIFT) {
												mod = KMOD_LSHIFT;
											}


											if (event.key.keysym.sym >= '0' && event.key.keysym.sym <= '9') {
												if (mod == KMOD_LSHIFT) {
													if (!(mod == KMOD_LSHIFT + KMOD_LALT)) {
														switch (event.key.keysym.sym) {
														case '0': str += ')'; break;
														case '1': str += '!'; break;
														case '2': str += '@'; break;
														case '3': str += '#'; break;
														case '4': str += '$'; break;
														case '5': str += '%'; break;
														case '6': str += '^'; break;
														case '7': str += '&'; break;
														case '8': str += '*'; break;
														case '9': str += '('; break;
														}
													}
													else {
														switch (event.key.keysym.sym) {
														case '0': str += ')'; break;
														case '1': str += '!'; break;
														case '2': str += '"'; break;
														case '3': str += '№'; break;
														case '4': str += ';'; break;
														case '5': str += '%'; break;
														case '6': str += ':'; break;
														case '7': str += '?'; break;
														case '8': str += '*'; break;
														case '9': str += '('; break;
														}
													}

												}

												else
													str += (char)event.key.keysym.sym;
												text = TTF_RenderUTF8_Solid(f, str.c_str(), c);
												SDL_BlitSurface(text, NULL, windowSurf, &rect1);
												SDL_UpdateWindowSurface(w);
											}
											else {

												if (event.key.keysym.sym >= 'A' && event.key.keysym.sym <= 'Z' || event.key.keysym.sym >= 'a' && event.key.keysym.sym <= 'z') {
													if (mod == KMOD_LSHIFT)
														str += (char)event.key.keysym.sym - 32;
													else
														str += (char)event.key.keysym.sym;
													text = TTF_RenderUTF8_Solid(f, str.c_str(), c);
													SDL_BlitSurface(text, NULL, windowSurf, &rect1);
													SDL_UpdateWindowSurface(w);
												}
												else {
													if (event.key.keysym.sym != SDLK_BACKSPACE && event.key.keysym.sym != SDLK_LALT && event.key.keysym.sym != SDLK_CAPSLOCK && event.key.keysym.sym != SDLK_LSHIFT && event.key.keysym.sym != SDLK_LCTRL && event.key.keysym.sym != SDLK_TAB) {
														if (mod == KMOD_LSHIFT) {
															switch (event.key.keysym.sym) {
															case'[':str += '{'; break;
															case']':str += '}'; break;
															case';':str += ':'; break;
															case',':str += '<'; break;
															case'.':str += '>'; break;
															case'/':str += '?'; break;
															case'-':str += '_'; break;
															case'=':str += '+'; break;
															case'`':str += '~'; break;
															case'\\':str += '|'; break;
															case'\'':str += '"'; break;
															}
														}
														else {
															str += (char)event.key.keysym.sym;
														}
														text = TTF_RenderUTF8_Solid(f, str.c_str(), c);
														SDL_BlitSurface(text, NULL, windowSurf, &rect1);
														SDL_UpdateWindowSurface(w);
													}
												}

											}

										}
									}
								}
							}
									break;
							case 2:
								SDL_Window *w = SDL_CreateWindow("Path", 100, 100, width, height / 2, SDL_WINDOW_SHOWN);;
								SDL_Surface *text, *windowSurf = SDL_GetWindowSurface(w);
								string str = "";
								SDL_Rect rect1 = { 0, 0, 50, 35 };
								SDL_Color c = { 0, 0, 0, 0 };
								TTF_Font* f = TTF_OpenFont("hemes.ttf", 30);
								SDL_FillRect(windowSurf, NULL, SDL_MapRGB(windowSurf->format, 255, 255, 255));
								text = TTF_RenderText_Blended(f, "Введите путь к файлу:", c);
								SDL_BlitSurface(text, NULL, windowSurf, &rect1);
								rect1 = { 0, 35, 50, 35 };
								SDL_UpdateWindowSurface(w);
								while (1) {
									SDL_WaitEvent(&event);
									if (event.window.windowID == SDL_GetWindowID(w)) {
										if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
											SDL_DestroyWindow(w);
											break;
										}
										if (event.window.type == SDL_KEYUP) {
											if (event.key.keysym.sym == SDLK_LSHIFT)
												mod = 0;
										}

										if (event.window.type == SDL_KEYDOWN) {
											if (event.key.keysym.sym == SDLK_BACKSPACE) {
												string t;
												if (str != "") {
													for (i = 0; i < str.length() - 1; i++)
														t += str[i];
													str = t;
													SDL_FillRect(windowSurf, &rect1, SDL_MapRGB(windowSurf->format, 255, 255, 255));
													text = TTF_RenderUTF8_Solid(f, str.c_str(), c);
													SDL_BlitSurface(text, NULL, windowSurf, &rect1);
													SDL_UpdateWindowSurface(w);
												}

											}

											if (event.key.keysym.sym == SDLK_RETURN) {
												SDL_DestroyWindow(w);
												if (str != "") {
													SDL_Surface* image = IMG_Load(str.data());
													SDL_SetRenderTarget(ren, mainTex);
													SDL_RenderCopy(ren, SDL_CreateTextureFromSurface(ren, image), NULL, &mainRect);
													SDL_SetRenderTarget(ren, NULL);
													SDL_RenderCopy(ren, mainTex, &mainRect, &mainRect);
													SDL_RenderPresent(ren);
													SDL_UpdateWindowSurface(win);
												}
												break;
											}

											if (event.key.keysym.sym == SDLK_LSHIFT) {
												mod = KMOD_LSHIFT;
											}


											if (event.key.keysym.sym >= '0' && event.key.keysym.sym <= '9') {
												if (mod == KMOD_LSHIFT) {
													if (!(mod == KMOD_LSHIFT + KMOD_LALT)) {
														switch (event.key.keysym.sym) {
														case '0': str += ')'; break;
														case '1': str += '!'; break;
														case '2': str += '@'; break;
														case '3': str += '#'; break;
														case '4': str += '$'; break;
														case '5': str += '%'; break;
														case '6': str += '^'; break;
														case '7': str += '&'; break;
														case '8': str += '*'; break;
														case '9': str += '('; break;
														}
													}
													else {
														switch (event.key.keysym.sym) {
														case '0': str += ')'; break;
														case '1': str += '!'; break;
														case '2': str += '"'; break;
														case '3': str += '№'; break;
														case '4': str += ';'; break;
														case '5': str += '%'; break;
														case '6': str += ':'; break;
														case '7': str += '?'; break;
														case '8': str += '*'; break;
														case '9': str += '('; break;
														}
													}

												}

												else
													str += (char)event.key.keysym.sym;
												text = TTF_RenderUTF8_Solid(f, str.c_str(), c);
												SDL_BlitSurface(text, NULL, windowSurf, &rect1);
												SDL_UpdateWindowSurface(w);
											}
											else {

												if (event.key.keysym.sym >= 'A' && event.key.keysym.sym <= 'Z' || event.key.keysym.sym >= 'a' && event.key.keysym.sym <= 'z') {
													if (mod == KMOD_LSHIFT)
														str += (char)event.key.keysym.sym - 32;
													else
														str += (char)event.key.keysym.sym;
													text = TTF_RenderUTF8_Solid(f, str.c_str(), c);
													SDL_BlitSurface(text, NULL, windowSurf, &rect1);
													SDL_UpdateWindowSurface(w);
												}
												else {
													if (event.key.keysym.sym != SDLK_BACKSPACE && event.key.keysym.sym != SDLK_LALT && event.key.keysym.sym != SDLK_CAPSLOCK && event.key.keysym.sym != SDLK_LSHIFT && event.key.keysym.sym != SDLK_LCTRL && event.key.keysym.sym != SDLK_TAB) {
														if (mod == KMOD_LSHIFT) {
															switch (event.key.keysym.sym) {
															case'[':str += '{'; break;
															case']':str += '}'; break;
															case';':str += ':'; break;
															case',':str += '<'; break;
															case'.':str += '>'; break;
															case'/':str += '?'; break;
															case'-':str += '_'; break;
															case'=':str += '+'; break;
															case'`':str += '~'; break;
															case'\\':str += '|'; break;
															case'\'':str += '"'; break;
															}
														}
														else {
															str += (char)event.key.keysym.sym;
														}
														text = TTF_RenderUTF8_Solid(f, str.c_str(), c);
														SDL_BlitSurface(text, NULL, windowSurf, &rect1);
														SDL_UpdateWindowSurface(w);
													}
												}

											}

										}
									}
								}
							}
						}
					}

				}
				else {
					draw::set_color(col_list.at(0)->color);
					rect = { x, y, 0, 0 };
					mouse_down = true;
				}
				break;

			case SDL_MOUSEBUTTONUP:
				SDL_SetRenderTarget(ren, NULL);
				SDL_SetRenderTarget(ren, temp);
				SDL_RenderCopy(ren, mainTex, &mainRect, &mainRect);
				SDL_SetRenderTarget(ren, NULL);
				mouse_down = false;
				break;

			case SDL_MOUSEMOTION:
				if (mouse_down) {
					SDL_GetMouseState(&x, &y);
					if (brush == false) {
						SDL_RenderCopy(ren, temp, &mainRect, &mainRect);
					}
					SDL_SetRenderTarget(ren, mainTex);
					rect.w = x - rect.x;
					rect.h = y - rect.y;
					fig_list.at(fig)->func(rect, bold);
					SDL_SetRenderTarget(ren, NULL);
					SDL_RenderCopy(ren, mainTex, &mainRect, &mainRect);
					SDL_SetRenderTarget(ren, mainTex);
					SDL_RenderPresent(ren);
					SDL_UpdateWindowSurface(win);
				}
				break;
			}
		}
	}
};



int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Russian");
	QCoreApplication a(argc, argv);
	SDL_Event event;

	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		cout << "Error init SDL: " << SDL_GetError() << endl;
		return 10;
	}

	if (TTF_Init()) {
		cout << "Error init TTF: " << TTF_GetError() << endl;
		return 11;
	}
	TTF_Font* font = TTF_OpenFont("font.ttf", 33);

	if (!font) {
		cout << "Error load font" << endl;
		return 12;
	}

	SDL_Window *win = SDL_CreateWindow("Window", 100, 100, width, height, SDL_WINDOW_SHOWN);
	if (!win) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED);
	if (!ren) {
		std::cout << "SDL_CreateRender Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	Paint p(ren, win);
	p.start();
	return 0;
}