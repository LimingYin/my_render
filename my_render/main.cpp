#include <memory>
#include <random>

#include <SDL.h>

#include "render.h"

using namespace std;

void handleEvents();
void handleKeyEvent(SDL_Keycode keyCode);

int main(int argc, char* args[])
{
	const int width = 640, height = 480; // window size

	SDL_Window *mainwindow = SDL_CreateWindow("my render", 100, 100, width, height, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(mainwindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_Texture *mainRt = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
	SDL_Surface *surface = SDL_GetWindowSurface(mainwindow);

	render m_render(width, height);
	m_render.setRenderColor(0x01 << 24 | 0xff << 16 | 0x00 << 8 | 0x00);

	while (true)
	{
		handleEvents();
		// draw
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, mainRt, nullptr, nullptr);

		m_render.clean();
		Point2i a(100, 350);
		Point2i b(400, 350);
		Point2i c(250, 100);

		m_render.drawTriangle(a, Color::red, b, Color::green, c, Color::blue);
		/*
		for (int i = 0; i < 10; i++)
		{
			Point2i a(rand() % width, rand() % height);
			Point2i b(rand() % width, rand() % height);
			Point2i c(rand()%width, rand() % height);

			Color colors[3];
			for (auto &c : colors)
			{
				int r = rand() % 256;
				int g = rand() % 256;
				int b = rand() % 256;
				c = Color(r, g, b);
			}
			m_render.drawTriangle(a, colors[0], b, colors[1], c, colors[2]);
		}
		*/

		void* mPixels;
		int mPitch;
		SDL_LockTexture(mainRt, NULL, &mPixels, &mPitch);
		//Copy loaded/formatted surface pixels
		memcpy(mPixels, m_render.backBuffer, 4*surface->w * surface->h);

		//Unlock texture to update
		SDL_UnlockTexture(mainRt);
		// present
		SDL_RenderPresent(renderer);
	}
	
	SDL_DestroyTexture(mainRt);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(mainwindow);
	SDL_Quit();

	return 0;
}

void handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			handleKeyEvent(event.key.keysym.sym);
			break;
		case SDL_QUIT:
			SDL_Quit();
			exit(0);
			break;
		}
	}
}

void handleKeyEvent(SDL_Keycode keyCode)
{
	switch (keyCode)
	{
	case SDLK_ESCAPE:
		SDL_Quit();
		exit(0);
		break;
	case SDLK_SPACE:
		break;
	case SDLK_F1:
		//toggle_fullscreen();
		break;
	default:
		break;
	}
}
