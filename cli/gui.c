#include "gui.h"

#include <ncurses.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdint.h>

#define FRAME_INTERVAL 200

typedef enum {
	STATUS_READY,
	STATUS_PLAYING,
	STATUS_OVER,
	STATUS_END,
} status_t;

typedef struct {
	status_t *status;
	game_t *game;
} key_listener_args;

atomic_bool listen_keys;

void print_line_divider(uint8_t width)
{
	printw("+");
	for (uint8_t x = 0; x < width; x++) {
		printw("-");
	}
	printw("+\n");
}

status_t game_play(game_t *game)
{
	move(0, 0);
	printw("Your score: %u\n", game_score(game));
	print_line_divider(game->width);
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
	print_line_divider(game->width);

	return game_frame(game) ? STATUS_PLAYING : STATUS_OVER;
}

status_t game_start()
{
	clear();
	printw("The snake game\n");
	printw("Press\n - 's' to start\n - 'q' to quit\n\n ? ");
	char c = getch();
	switch (c) {
	case 's':
		return STATUS_PLAYING;
	case 'q':
		return STATUS_END;
	default:
		return STATUS_READY;
	}
}

status_t game_over(game_t *game)
{
	clear();
	printw("Game over!\n");
	printw("Your score: %d\n\n", game_score(game));
	printw("Press\n - 's' to play again\n - 'q' to quit\n ? ");
	switch (getch()) {
	case 's':
		game_reset(game);
		return STATUS_PLAYING;
	case 'q':
		return STATUS_END;
	default:
		return STATUS_OVER;
	}
}

void *keys_listener(void *extra)
{
	key_listener_args *args = (key_listener_args *) extra;
	while (listen_keys) {
		if (*args->status != STATUS_PLAYING) {
			continue;
		}
		switch (getch()) {
		case KEY_LEFT:
			game_turn_left(args->game);
			break;
		case KEY_RIGHT:
			game_turn_right(args->game);
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
	status_t status = STATUS_READY;

	key_listener_args args = {.status = &status, .game = game};
	// Listen for keys in another thread
	pthread_t keys_thread;
	listen_keys = true;
	pthread_create(&keys_thread, 0, keys_listener, (void *)&args);

	while (status != STATUS_END) {
		if (status == STATUS_READY) {
			status = game_start();
		} else if (status == STATUS_PLAYING) {
			status = game_play(game);
		} else if (status == STATUS_OVER) {
			status = game_over(game);
		}
		napms(FRAME_INTERVAL);
	}
	
	listen_keys = false;
	pthread_join(keys_thread, 0);
	screen_teardown();
}