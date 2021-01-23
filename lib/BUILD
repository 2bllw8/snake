load("@rules_cc//cc:defs.bzl", "cc_library")

# Game implementation
cc_library(
	name = "game",
	srcs = [
		"game.c"
	],
	hdrs = [
		"game.h",
	],
	deps = [
		":component_base",
		":component_apple",
		":component_snake",
	],
	visibility = [
		"//cli:__pkg__",
		"//main:__pkg__",
	],
)

# Base component
cc_library(
	name = "component_base",
	hdrs = [
		"display.h",
		"directions.h",
	],
	deps = [
	],
	visibility = [
		"//lib:__pkg__",
	],
)

# Apple component
cc_library(
	name = "component_apple",
	srcs = [
		"apple.c",
	],
	hdrs = [
		"apple.h",
	],
	deps = [
		":component_base",
	],
	visibility = [
		"//lib/__pkg__",
	],
)

# Snake component
cc_library(
	name = "component_snake",
	srcs = [
		"snake.c",
		"tail.c",
	],
	hdrs = [
		"snake.h",
		"tail.h",
	],
	deps = [
		":component_base"
	],
	visibility = [
		"//lib:__pkg__",
	],
)
