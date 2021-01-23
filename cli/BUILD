load("@rules_cc//cc:defs.bzl", "cc_library")

# Game implementation
cc_library(
	name = "gui",
	srcs = [
		"gui.c"
	],
	hdrs = [
		"gui.h",
	],
	deps = [
		"//lib:game",
		"@ncurses//:main",
	],
	visibility = [
		"//main:__pkg__",
	],
)

