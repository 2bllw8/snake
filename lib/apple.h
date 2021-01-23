#ifndef SNAKE_APPLE_H
#define SNAKE_APPLE_H

#include "display.h"

#include <stdbool.h>
#include <stdint.h>

typedef struct apple_t apple_t;

/*
 * Make a new apple
 */
apple_t *apple_new(uint8_t width, uint8_t height);

/*
 * Reset apple status
 */
void apple_reset(apple_t *);

/*
 * Get the score / how many times the apple was eaten
 */
uint16_t apple_score(apple_t *);

/*
 * Callback for snake movement. Returns true, if the apple was eaten
 */
bool apple_on_game_move(apple_t *, uint8_t x, uint8_t y);

/*
 * Display information about the apple for a given point.
 * It can be DISPLAY_NONE or DISPLAY_APPLE
 */
game_display_t apple_display(apple_t *, uint8_t x, uint8_t y);

#endif