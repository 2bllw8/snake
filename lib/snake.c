#include "directions.h"
#include "display.h"
#include "snake.h"
#include "tail.h"

#include <stdbool.h>
#include <stdlib.h>

struct snake_t {
	direction_t direction;
	uint8_t max_x;
	uint8_t max_y;
	tail_t *head;
};

bool _next_step_valid(snake_t *snake, uint8_t next_x, uint8_t next_y)
{
	return snake && snake->head && snake->max_x > tail_x(snake->head) &&
	       snake->max_y > tail_y(snake->head) &&
	       !tail_contains(snake->head, next_x, next_y);
}

snake_t *snake_new(uint8_t x, uint8_t y, uint8_t max_x, uint8_t max_y)
{
	snake_t *snake = (snake_t *)malloc(sizeof(snake_t));
	if (!snake) {
		return 0;
	}

	snake->direction = DIRECTION_UP;
	snake->max_x = max_x;
	snake->max_y = max_y;
	snake->head = tail_new(x, y, 0);
	return snake;
}

void snake_destroy(snake_t *snake)
{
	if (!snake) {
		return;
	}
	tail_destroy(snake->head);
}

bool snake_step(snake_t *snake)
{
	if (!snake || !snake->head) {
		return false;
	}

	tail_t *next_tail = tail_prepend(snake->head, snake->direction);
	if (!next_tail ||
	    !_next_step_valid(snake, tail_x(next_tail), tail_y(next_tail))) {
		return false;
	}

	snake->head = next_tail;
	return true;
}

void snake_turn_left(snake_t *snake)
{
	switch (snake->direction) {
	case DIRECTION_UP:
		snake->direction = DIRECTION_LEFT;
		break;
	case DIRECTION_RIGHT:
		snake->direction = DIRECTION_UP;
		break;
	case DIRECTION_DOWN:
		snake->direction = DIRECTION_RIGHT;
		break;
	case DIRECTION_LEFT:
		snake->direction = DIRECTION_DOWN;
		break;
	}
}

void snake_turn_right(snake_t *snake)
{
	switch (snake->direction) {
	case DIRECTION_UP:
		snake->direction = DIRECTION_RIGHT;
		break;
	case DIRECTION_RIGHT:
		snake->direction = DIRECTION_DOWN;
		break;
	case DIRECTION_DOWN:
		snake->direction = DIRECTION_LEFT;
		break;
	case DIRECTION_LEFT:
		snake->direction = DIRECTION_UP;
		break;
	}
}

uint8_t snake_x(snake_t *snake)
{
	return tail_x(snake->head);
}

uint8_t snake_y(snake_t *snake)
{
	return tail_y(snake->head);
}

void snake_increase_length(snake_t *snake)
{
	if (!snake) {
		return;
	}
	tail_increase_max_depth(snake->head);
}

game_display_t snake_display(snake_t *snake, uint8_t x, uint8_t y)
{
	if (!snake) {
		return DISPLAY_NONE;
	}
	if (x == tail_x(snake->head) && y == tail_y(snake->head)) {
		return DISPLAY_SNAKE_HEAD;
	}
	return tail_display(snake->head, x, y);
}
