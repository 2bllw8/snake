#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include "display.h"
#include "tail.h"

#include <stdbool.h>
#include <stdint.h>

typedef struct snake_t snake_t;

/*
 * Make a new snake
 */
snake_t *snake_new(uint8_t x, uint8_t y, uint8_t max_x, uint8_t max_y);

/*
 * Destroy a snake
 */
void snake_destroy(snake_t *);

/*
 * Make the snake perform a step
 */
bool snake_step(snake_t *);

/*
 * Make the snake turn left
 */
void snake_turn_left(snake_t *);

/*
 * Make the snake turn right
 */
void snake_turn_right(snake_t *);

/*
 * Get the snake's head x coordinate
 */
uint8_t snake_x(snake_t *);

/*
 * Get the snake's head y coordinate
 */
uint8_t snake_y(snake_t *);

/*
 * Increase the snake length
 */
void snake_increase_length(snake_t *);

/*
 * Obtain display info for a given coordinate
 * It can be DISPLAY_SNAKE_HEAD, DISPLAY_SNAKE_TAIL or DISPLAY_NONE
 */
game_display_t snake_display(snake_t *, uint8_t x, uint8_t y);

#endif