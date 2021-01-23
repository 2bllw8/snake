#include "gui.h"

#include <ncurses.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdbool.h>

#define FRAME_INTERVAL 200

atomic_bool listen_keys;

void draw_game(game_t *game)
{
	clear();
	printw("Score: %u\n", game_score(game));

	printw("+");
	for (uint8_t x = 0; x < game->width; x++) {
		printw("-");
	}
	printw("+\n");

	for (uint8_t y = 0; y < game->height; y++) {
		printw("|");
		for (uint8_t x = 0; x < game->width; x++) {
			switch (game_display(game, x, y)) {
			case DISPLAY_NONE:
				printw(" ");
				break;
			case DISPLAY_APPLE:
				printw("*");
				break;
			case DISPLAY_SNAKE_HEAD:
				printw("@");
				break;
			case DISPLAY_SNAKE_TAIL:
				printw("#");
				break;
			}
		}
		printw("|\n");
	}

	printw("+");
	for (uint8_t x = 0; x < game->width; x++) {
		printw("-");
	}
	printw("+\n");
}

bool frame(game_t *game)
{
	draw_game(game);
	return game_frame(game);
}

void *keys_listener(void *args)
{
	game_t *game = (game_t *)args;
	while (listen_keys) {
		switch (getch()) {
		case KEY_LEFT:
			game_turn_left(game);
			break;
		case KEY_RIGHT:
			game_turn_right(game);
			break;
		}
	}
	return 0;
}

void screen_setup()
{
	initscr();
	noecho();
	scrollok(stdscr, 1);
	nodelay(stdscr, 1);
	keypad(stdscr, 1);
}

void screen_teardown()
{
	endwin();
}

void run(game_t *game)
{
	screen_setup();

	// Listen for keys in another thread
	pthread_t keys_thread;
	listen_keys = true;
	pthread_create(&keys_thread, 0, keys_listener, (void *)game);

	while (frame(game)) {
		napms(FRAME_INTERVAL);
	}

	listen_keys = false;
	screen_teardown();
}