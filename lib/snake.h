#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include "display.h"
#include "tail.h"

#include <stdbool.h>
#include <stdint.h>

typedef struct snake_t snake_t;

snake_t *snake_new(uint8_t x, uint8_t y, uint8_t max_x, uint8_t max_y);
void snake_destroy(snake_t *);

bool snake_step(snake_t *);
void snake_turn_left(snake_t *);
void snake_turn_right(snake_t *);

uint8_t snake_x(snake_t *);
uint8_t snake_y(snake_t *);

void snake_on_score_increased(snake_t *);
game_display_t snake_display(snake_t *, uint8_t x, uint8_t y);

#endif