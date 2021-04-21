// patches to try: regex rules, focusadjacenttag, focusonnetactive, swapfocus, switchtotag, zoomswap
// diff -u [old] [new] > [diff]
// patch < [diff]		overwrites the file specified in [diff]
//				passable conflicts -> "fuzz"
//				serious conflicts -> generates [old].rej -> change specified files manually
// patch -R < [diff]		undo changes (also manual ones?)

// set up dwm for xdm (ubuntu)
// https://medium.com/hacker-toolbelt/dwm-windows-manager-in-ubuntu-14958224a782
// echo dwm > .xsession
//
// set up dwm for lightdm
// https://forum.manjaro.org/t/dwm-not-showing-in-lightdm-log-in-screen/98220/4
// /usr/share/xsessions/dwm.desktop
// [Desktop Entry]
// Encoding=UTF-8
// Name=dwm
// Comment=dwm window manager
// Exec=/usr/local/bin/dwm
// Type=Application

static const unsigned int borderpx	= 1;	// border pixel of windows
static const unsigned int snap		= 32;	// snap pixel
static const int showbar		= 1;	// 0 means no bar
static const int topbar			= 1;	// 0 means bottom bar -- testing
static const char *fonts[]		= { "fira mono:size=8",
	/* "ia writer mono s:size=8", */
	/* "monaco:size=8", */
	"symbola:size=8" };	// may require font-awesome
// static const char dmenufont[]		= "monaco:size=8";

// https://camo.githubusercontent.com/cdb2f2e986c564b515c0c698e6c45b4ab5d725a9/687474703a2f2f692e696d6775722e636f6d2f776136363678672e706e67
static const char blue[]		= "#458688";
static const char gray[]		= "#131313";
static const char green[]		= "#98971a";
static const char lightgray[]		= "#282828";
static const char red[]			= "#cc241d";
static const char white2[]		= "#ebdbb2";
static const char white[]		= "#bbbbbb";

static const char *colors[][3]		= {
//			fg	bg	border
	[SchemeNorm] = { white2,gray,	gray },
	[SchemeSel]  = { blue,	gray,	blue },
};

// tag names -- testing
// https://github.com/meinwald/DWM-config/blob/master/config.h#L16
static const char *tags[] = { "main", "work", "down", "vbox", "tab", "6", "7", "8", "9" };

static const Rule rules[] = {
	// xprop(1):
	// WM_CLASS(STRING) = instance, class;	reversed!
	// WM_NAME(STRING) = title
	// regex is hardly needed: https://github.com/ericpruitt/edge/blob/master/patches/dwm-00-regex-rules.diff
	// https://www.tutorialspoint.com/c_standard_library/c_function_strstr.htm
	// switch = switchtotag (not switchtag), float = isfloating

	// class	instance	title		tags mask	switch	float	monitor
	// switchtag definitions: https://github.com/bakkeby/patches/wiki/switchtag
	{ "Chromium",	NULL,		NULL,		1 << 0,		0,	0,	1 },
	{ "Display",	NULL,		NULL,		0,		0,	1,	1 },	// PIL
	{ "FLTK",	NULL,		NULL,		0,		0,	1,	1 },	// vmd
	{ "PPSSPPQt",	NULL,		NULL,		0,		0,	1,	1 },
	{ "discord",	NULL,		NULL,		0,		0,	1,	1 },
	{ "firefox",	NULL,		NULL,		0,		3,	0,	1 },
	{ "libreoffice-calc",	NULL,	NULL,		0,		0,	0,	1 },
	{ "libreoffice-writer",	NULL,	NULL,		0,		0,	0,	1 },
	{ "mednafen",	NULL,		NULL,		0,		0,	1,	1 },
	{ "mpv",	NULL,		NULL,		1 << 0,		1,	0,	1 },
	{ NULL,		"libreoffice",	NULL,		0,		0,	0,	1 },
	{ NULL,		NULL,		"LibreOffice",	0,		0,	0,	1 },	// this doesn't work
	{ NULL,		NULL,		"ncmpcpp",	1 << 0,		0,	0,	1 },	// yes, this works

	{ "Com.github.xournalpp.xournalpp",	NULL,	NULL,	1 << 1,	1,	0,	1 },
	{ "Evince",	NULL,		NULL,		1 << 1,		3,	0,	1 },
	{ "MestReNova",	NULL,		NULL,		1 << 1,		1,	0,	1 },
	{ "Zathura",	NULL,		NULL,		1 << 1,		3,	0,	1 },
	{ "zoom",	NULL,		NULL,		1 << 1,		1,	0,	-1 },

	{ "SoulseekQt",	NULL,		NULL,		1 << 2,		1,	1,	1 },	// not sure which mon these should go to
	{ "Transmission-gtk",	NULL,	NULL,		1 << 2,		1,	0,	1 },
	{ NULL,		NULL,		"deeznuts",	1 << 2,		0,	0,	1 },	// why doesn't this work like ncmpcpp?

	{ "App.py",	NULL,		NULL,		1 << 3,		1,	1,	1 },	// playitslowly
	{ "VirtualBox Machine",	NULL,	NULL,		1 << 3,		1,	0,	1 },	// rule not triggered; WM_CLASS:  not found
	{ "VirtualBox Manager",	NULL,	NULL,		1 << 3,		1,	1,	1 },
	{ "virtualbox",	NULL,		NULL,		1 << 3,		1,	1,	1 },	// idk
	{ "Virtualbox",	NULL,		NULL,		1 << 3,		1,	1,	1 },	// this better work gdi
	// https://github.com/laur89/dwm-setup/blob/603f8b26d5bba806c195e6f82a2370fd51c6faf7/.dwm/w0ngBuild/source6.0/config.h

	{ "TuxGuitar",	NULL,		NULL,		1 << 4,		1,	0,	1 },
	{ "MuseScore3",	NULL,		NULL,		1 << 4,		1,	0,	1 },

	{ "Gimp",	NULL,		NULL,		0,		0,	1,	-1 },
	{ "Gpick",	"gpick",	NULL,		0,		0,	1,	-1 },
	{ "matplotlib",	NULL,		NULL,		0,		0,	1,	-1 },
	{ "Pavucontrol",	NULL,	NULL,		0,		0,	1,	-1 },
	{ "TelegramDesktop",	NULL,	NULL,		0,		0,	1,	-1 },
	{ "Thunar",	NULL,		NULL,		0,		0,	1,	-1 },

};

/* layout(s) */
static const float mfact	= 0.55;  /* factor of master area size [0.05..0.95] */
static const int nmaster	= 1;	 /* number of clients in master area */
static const int resizehints	= 1;	 /* 0 = force terminals to use up all extra space */

static const Layout layouts[] = {
	{ "DEF",	tile },
	{ "FUL",	monocle },
	{ "DEC",	deck },
//	{ "BST",	bstack },
//	{ "><>",	  NULL },
};

#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,			KEY,	  view,		{.ui = 1 << TAG} }, \
	{ Mod1Mask,			KEY,	  toggleview,	{.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,		KEY,	  tag,		{.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,	  toggletag,	{.ui = 1 << TAG} },
// toggleview = activate (in addition), tag = send to, toggletag = duplicate to
// these combinations are all unwieldy
// alt+\d might cause conflicts with some programs, but i haven't noticed any yet

#include <X11/XF86keysym.h>	// https://cgit.freedesktop.org/xorg/proto/x11proto/tree/XF86keysym.h

#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "rofi", "-show", "run", NULL };
static const char *termcmd[]	= { "urxvt", NULL };
static const char *brightup[]	= { "xbacklight", "-inc", "10", NULL};	// acpilight needs root
static const char *brightdown[]	= { "xbacklight", "-dec", "10", NULL};
static const char *volup[]	= { "pactl", "set-sink-volume", "0", "+10%", NULL};
static const char *voldown[]	= { "pactl", "set-sink-volume", "0", "-10%", NULL};
// https://github.com/TaylanTatli/dwm/blob/master/config.h#L15

static Key keys[] = {		/* {0} just means no arg */
	/* modifier		key		function	argument */

	// still unbound: b=:"{}; backspace (reserved: focus master), backslash
	// { MODKEY,		XK_y,		spawn,		SHCMD("urxvt -e sh -i mpvopen") },	// uncommonly used
	// { Mod1Mask|ControlMask|ShiftMask,	XK_d,	spawn,	SHCMD("urxvt -e sh -i deeznuts") },	// unwieldy, might deprecate
	{ 0,			0x1008ff2d,	spawn,		SHCMD("i3lock -c 000000") },	// try some other screen lockers
	{ 0,			XF86XK_AudioLowerVolume,	spawn,		{.v = voldown } },
	{ 0,			XF86XK_AudioRaiseVolume,	spawn,		{.v = volup } },
	{ 0,			XF86XK_MonBrightnessDown,	spawn,		{.v = brightdown } },
	{ 0,			XF86XK_MonBrightnessUp,		spawn,		{.v = brightup } },	// xbacklight doesn't work on asus
	{ 0,			XK_Print,	spawn,		SHCMD("maim -m 10 -s | xclip -selection clipboard -t image/png") }, // scrot syntax is garbage since it doesn't support true piping
	{ ControlMask,		XK_Print,	spawn,		SHCMD("maim -m 10 -i $(xdotool getactivewindow) | xclip -selection clipboard -t image/png") },
	{ MODKEY,		XK_Delete,	spawn,		SHCMD("i3lock -c 000000") },
	{ MODKEY,		XK_Print,	spawn,		SHCMD("flameshot gui") },
	{ MODKEY,		XK_Return,	spawn,		SHCMD("urxvt -e sh -i deeznuts") },
	{ MODKEY,		XK_a,		spawn,		SHCMD("localc") },
	{ MODKEY,		XK_c,		spawn,		SHCMD("NOTMUCH_CONFIG=$HOME/.config/notmuch/config urxvt -e neomutt") },
	{ MODKEY,		XK_d,		spawn,		{.v = dmenucmd } },
	{ MODKEY,		XK_e,		spawn,		{.v = termcmd } },
	{ MODKEY,		XK_minus,	spawn,		SHCMD("sh -i nordtog --toggle") },	// sh -i respects $PATH
	{ MODKEY,		XK_n,		spawn,		SHCMD("urxvt -e newsboat") },	// printf '\e]710;%s\007' "xft:monaco:pixelsize=16"
	{ MODKEY,		XK_q,		spawn,		SHCMD("soulseekqt") },
	{ MODKEY,		XK_t,		spawn,		SHCMD("telegram-desktop") },
	{ MODKEY,		XK_w,		spawn,		SHCMD("firefox") },
	{ MODKEY|ShiftMask,	XK_d,		spawn,		SHCMD("discord-ptb") },
	{ MODKEY|ShiftMask,	XK_e,		spawn,		SHCMD("kitty") },
	{ MODKEY|ShiftMask,	XK_f,		spawn,		SHCMD("urxvt -e sh -i ranga") },
	{ MODKEY|ShiftMask,	XK_h,		spawn,		SHCMD("urxvt -e htop") },
	{ MODKEY|ShiftMask,	XK_l,		spawn,		SHCMD("lastgrep") },
	{ MODKEY|ShiftMask,	XK_m,		spawn,		SHCMD("urxvt -e ncmpcpp") },	// dropped priority
	{ MODKEY|ShiftMask,	XK_t,		spawn,		SHCMD("sh -i nordtog --on; transmission-gtk") },
	{ MODKEY|ShiftMask,	XK_v,		spawn,		SHCMD("sh -i vb") },	// hacky
	{ MODKEY|ShiftMask,	XK_w,		spawn,		SHCMD("wttr") },
	{ ShiftMask,		XK_Print,	spawn,		SHCMD("maim -m 10 | xclip -selection clipboard -t image/png") },

	// $HOME/.SoulseekQt/wishlist
	// 4chan boards
	// firefox tabs
	// notmuch search date:today | awk '{print substr($0, index($0, $5))}' | rofi -dmenu -> open in neomutt?
	// rofi
	// rofi -show calc -modi calc -no-show-match -no-sort
	// { MODKEY,		XK_apostrophe,	spawn,		SHCMD("sh -i rmpc -s") },	// search artist/album
	// { MODKEY|ShiftMask,	XK_r,		spawn,		SHCMD("sh -i vex") },	// will probably deprecate
	// { Mod1Mask|ControlMask,	XK_Delete,	spawn,		SHCMD("sh rofi -show power-menu -modi power-menu:rofi-power-menu -lines 6") },
	{ MODKEY,		XK_m,		spawn,		SHCMD("sh -i rmpc -s") },
	{ MODKEY,		XK_p,		spawn,		SHCMD("sh -i rmpc -n") },	// now playing
	{ MODKEY,		XK_r,		spawn,		SHCMD("sh o") },
	{ MODKEY,		XK_s,		spawn,		SHCMD("sh -i search") },
	{ MODKEY,		XK_semicolon,	spawn,		SHCMD("sh -i rmpc") },	// prompt
	{ MODKEY|ShiftMask,	XK_p,		spawn,		SHCMD("sh -i rmpc --rym") },
	{ MODKEY|ShiftMask,	XK_r,		spawn,		SHCMD("sh o -s") },		// show dirs first

	// media control
	{ 0,			XF86XK_AudioNext,	spawn,	SHCMD("sh -i rmpv -f") },
	{ 0,			XF86XK_AudioPlay,	spawn,	SHCMD("sh -i rmpv -t") },
	{ 0,			XF86XK_AudioPrev,	spawn,	SHCMD("sh -i rmpv -b") },
	{ MODKEY,		XK_comma,	spawn,		SHCMD("sh -i rmpv -b") },	// seek backward
	{ MODKEY,		XK_period,	spawn,		SHCMD("sh -i rmpv -t") },	// toggle
	{ MODKEY,		XK_slash,	spawn,		SHCMD("sh -i rmpv -f") },	// seek forward
	{ MODKEY,		XK_x,		spawn,		SHCMD("sh -i rmpv -q") },	// quit
	{ MODKEY,		XK_z,		spawn,		SHCMD("sh -i rmpv -d") },	// search deezer

	// layout
	{ MODKEY,		XK_g,		setlayout,	{.v = &layouts[0]} },	// default
	{ MODKEY,		XK_f,		setlayout,	{.v = &layouts[1]} },	// fullscreen
	{ MODKEY,		XK_v,		setlayout,	{.v = &layouts[2]} },	// deck
	// { MODKEY,		XK_b,		setlayout,	{.v = &layouts[3]} },	// bstack -- deprecated

	// window
	{ ControlMask,		XK_q,		killclient,	{0} },
	{ MODKEY,		XK_grave,	togglefloating,	{0} },
	{ MODKEY,		XK_h,		pushup,         {0} },
	{ MODKEY,		XK_j,		focusstack,	{.i = +1 } },
	{ MODKEY,		XK_k,		focusstack,	{.i = -1 } },
	{ MODKEY,		XK_l,		pushdown,       {0} },
	{ MODKEY,		XK_space,	zoom,		{0} },	// switch master/stack, focus master
	{ MODKEY|ControlMask|ShiftMask,	XK_q,	quit,		{1} },	// restart
	{ MODKEY|ShiftMask,	XK_q,		quit,		{0} },

	// workspace
	// { MODKEY,		XK_bracketleft, shiftviewclients,	{ .i = -1 } },
	// { MODKEY,		XK_bracketright,shiftviewclients,	{ .i = +1 } },	// cycle tag focus
	TAGKEYS(		XK_1,				0)
	TAGKEYS(		XK_2,				1)
	TAGKEYS(		XK_3,				2)
	TAGKEYS(		XK_4,				3)
	TAGKEYS(		XK_5,				4)
	TAGKEYS(		XK_6,				5)
	TAGKEYS(		XK_7,				6)
	TAGKEYS(		XK_8,				7)
	TAGKEYS(		XK_9,				8)
	{ MODKEY,		XK_Tab,		view,		{0} },	// i often use this one-handed
	{ MODKEY,		XK_o,		shiftviewclients,	{ .i = +1 } },	// cycle tag focus
	{ MODKEY,		XK_u,		view,		{0} },	// intuitive with mod+i
	{ MODKEY,		XK_y,		shiftviewclients,	{ .i = -1 } },

	// monitor
	// { MODKEY,		XK_BackSpace,	spawn,		SHCMD("pkill picom; picom -b --config .picom.conf; notify-send 'Restarted picom'") },	// it's just a phase mom
	// { MODKEY|ShiftMask,	XK_space,	tagmon,		{.i = +1 } },
	{ MODKEY,		XK_0,		spawn,		SHCMD("sh -ix mon --on > mon.log") },
	{ MODKEY,		XK_i,		focusmon,	{.i = +1 } },	// switch mon
	{ MODKEY|ShiftMask,	XK_i,		tagmon,		{.i = +1 } },	// send to mon

	// gimmicks that i don't use
	// { MODKEY,		XK_0,		view,		{.ui = ~0 } },	// merge all workspaces
	// { MODKEY,		XK_Left,	setmfact,	{.f = -0.05} }, // widen master
	// { MODKEY,		XK_Right,	setmfact,	{.f = +0.05} },
	// { MODKEY,		XK_b,		togglebar,	{0} },
	// { MODKEY|ShiftMask,	XK_0,		tag,		{.ui = ~0 } },	// "sticky"
	// { MODKEY|ShiftMask,	XK_Down,	incnmaster,	{.i = -1 } },	// +1 horiz in master
	// { MODKEY|ShiftMask,	XK_Tab,		setlayout,	{0} },		// toggle between last 2 layouts
	// { MODKEY|ShiftMask,	XK_Up,		incnmaster,	{.i = +1 } },

};

/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {

	// click		event mask	button		function	argument
	// { ClkTagBar,		0,		Button3,	toggleview,	{0} },
	// { ClkTagBar,		0,		Button4,	shiftviewclients,	{ .i = -1 } },
	// { ClkTagBar,		0,		Button5,	shiftviewclients,	{ .i = +1 } },
	// { ClkTagBar,		MODKEY,		Button3,	toggletag,	{0} },	// duplicate to
	// { ClkWinTitle,	0,		Button2,	zoom,		{0} },	// togglefloating?
	// { ClkWinTitle,	0,		Button4,	focusstack,	{.i = -1 }},
	// { ClkWinTitle,	0,		Button5,	focusstack,	{.i = +1 }},	// might seem useless but good for vbox
	{ ClkClientWin,		MODKEY,		8,		view,		{0}},
	{ ClkClientWin,		MODKEY,		9,		tagmon,		{.i = +1 }},
	{ ClkClientWin,		MODKEY,		Button1,	movemouse,	{0} },	// anywhere in window
	{ ClkClientWin,		MODKEY,		Button2,	togglefloating, {0} },
	{ ClkClientWin,		MODKEY,		Button3,	resizemouse,	{0} },
	{ ClkClientWin,		MODKEY,		Button4,	focusstack,	{.i = -1 }},	// mostly for fullscreen
	{ ClkClientWin,		MODKEY,		Button5,	focusstack,	{.i = +1 }},
	{ ClkLtSymbol,		0,		Button1,	setlayout,	{0} },	// toggle layouts
	{ ClkLtSymbol,		0,		Button3,	setlayout,	{.v = &layouts[1]} },	// fullscreen
	{ ClkStatusText,	0,		Button2,	spawn,		{.v = termcmd } },
	{ ClkStatusText,	0,		Button3,	toggleview,	{0} },	// TESTING
	{ ClkStatusText,	0,		Button4,	shiftviewclients,	{.i = -1 }},
	{ ClkStatusText,	0,		Button5,	shiftviewclients,	{.i = +1 }},
	{ ClkTagBar,		0,		Button1,	view,		{0} },
	{ ClkTagBar,		0,		Button2,	toggleview,	{0} },	// activate
	{ ClkTagBar,		MODKEY,		Button1,	tag,		{0} },	// send to
	{ ClkWinTitle,		0,		Button2,	tagmon,		{.i = -1}},
	{ ClkWinTitle,		0,		Button4,	shiftviewclients,	{.i = -1 }},
	{ ClkWinTitle,		0,		Button5,	shiftviewclients,	{.i = +1 }},
};

static const char *const autostart[] = {	// cool_autostart

	"dunst", NULL,		// anything that isn't an executable (i.e. longer than 1 word) needs the full sh syntax
	"mpd", NULL,		// very slow on cold boot -- "Cannot assign requested address"
	"sh", "-c", "cup",		NULL,
	"sh", "-c", "pkill mpdscribble; mpdscribble",	NULL,
	"sh", "-c", "pkill picom; picom -b",	NULL,	// -b = daemon; run order (wrt mon) doesn't really matter
	"sh", "-c", "redshift -x; redshift -b 1",	NULL,	// redshift cannot be pkilled!
	"sh", "-c", "setxkbmap -layout us -option compose:rctrl", NULL,		// all setxkbmap options must be declared at once
	"sh", "-c", "sleep 1; mon --on",	NULL,	// not using sleep will produce a black or misconfigured screen
	"sh", "-c", "udisksctl mount -b /dev/sdb1",	NULL,	// takes a while, don't panic
	"udiskie", NULL,
	// "sh", "-c", "mouse",		NULL,
	// "sh", "-c", "wallset",		NULL,
	// "sh", "-c", "notify-send 'dwm started'", NULL,

	NULL
};
