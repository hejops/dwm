// patches to try: regex rules, focusadjacenttag, focusonnetactive, swapfocus,
// switchtotag, zoomswap
// diff -u [old] [new] > [diff]
// patch < [diff] overwrites the file specified in [diff]
// passable conflicts -> "fuzz"
// serious conflicts -> generates [old].rej -> change specified files manually
// patch -R < [diff]		undo changes (also manual ones?)

// https://github.com/bakkeby/dwm-flexipatch

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

static const unsigned int borderpx = 1; // border pixel of windows
static const unsigned int snap = 32;    // snap pixel
static const int showbar = 1;           // 0 means no bar
static const int topbar = 1;            // 0 means bottom bar
static const char *fonts[] = {
    "source code pro:size=8",
    "source han sans cn:size=8",
    "source han sans jp:size=8",
    "source han sans kr:size=8",
    "haskplex:size=8",
    "symbola:size=8"
};
// static const char dmenufont[]		= "monaco:size=8";

// static const char green[] = "#00cc7a";
// static const char lightgray[] = "#383838";
// static const char red[] = "#ff5454";
// static const char white2[] = "#ebdbb2";
static const char blue[] = "#00bfff"; // citruszest
static const char gray[] = "#121212";
static const char white[] = "#bfbfbf";

static const char *colors[][3] = {
    [SchemeNorm] = {white, gray, gray}, // fg, bg, border
    [SchemeSel] = {blue, gray, blue},
};

// tag names
// https://github.com/meinwald/DWM-config/blob/master/config.h#L16
// https://libredd.it/r/suckless/comments/id0q64/how_to_get_more_than_9_tags_in_dwm/g26yhdl/?context=3
static const char *tags[] = {
    // "main", "work", "muse", "win7", "jack", "6", "7", "8", "cal",
    // i've come to realise i don't ever need more than 3 or 4 tags
    "term", "gui", "???",
};

static const Rule rules[] = {
    // xprop(1):
    // WM_CLASS(STRING) = instance, class;	reversed!
    // WM_NAME(STRING) = title
    // regex is hardly needed:
    // https://github.com/ericpruitt/edge/blob/master/patches/dwm-00-regex-rules.diff
    // https://www.tutorialspoint.com/c_standard_library/c_function_strstr.htm

    // switchtag definitions:
    // https://github.com/bakkeby/patches/wiki/switchtag#rules
    // 0 is default behaviour, view is not changed
    // 1 automatically moves you to the tag of the newly opened application
    // 3 as 1, but closing that window reverts the view back to what it was
    // before opening the client *
    // 2 enables the tag of the newly opened application in addition to your
    // existing enabled tags
    // 4 as 2, but closing that window reverts the view back to what it was
    // before opening the client *
    // (* except if the client has been moved between tags or to another
    // monitor)

    // https://github.com/laur89/dwm-setup/blob/603f8b26d5bba806c195e6f82a2370fd51c6faf7/.dwm/w0ngBuild/source6.0/config.h#L114

    // class	    instance    title   tag     switch	float	monitor

    // a tag of '1 << x' means the window will be opened in tag x. to have the
    // window open in the current tag, simply declare '0' (without '1 << ')

    // main programs
    {"firefox",	        NULL,	NULL,	1 << 1,	1,	0, -1},
    {"kitty",	        NULL,	NULL,	1 << 0,	1,	0,	1},
    {"wezterm",	        NULL,	NULL,	1 << 0,	1,	0,	1},

    // common one-off programs
    // might be better to just set tag to 0
    {"Chromium",	NULL,	NULL,	1 << 2,	4,	0,	0},
    {"Nicotine",	NULL,	NULL,	1 << 1,	1,	0,	1},
    {"Zathura",	        NULL,	NULL,	1 << 1,	1,	0,	0},
    {"feh",	        NULL,	NULL,	1 << 1,	3,	0,	0},
    {"mpv",	        NULL,	NULL,	1 << 1,	3,	0,	1},

    // floats
    {"Display",	        NULL,	NULL,	0,	0,	1,	0},	// PIL
    {"Gpick",       "gpick",	NULL,	0,	0,	1, -1},
    {"PPSSPPQt",	NULL,	NULL,	0,	0,	1,	1},
    {"Pavucontrol",	NULL,	NULL,	0,	0,	1, -1},
    {"TelegramDesktop",	NULL,	NULL,	0,	0,	1, -1}, // bad at resizing
    {"discord",	        NULL,	NULL,	0,	0,	1,	0},
    {"mednafen",	NULL,	NULL,	0,	0,	1,	1},

    {"App.py",	        NULL,	NULL,	1 << 2,	1,	1,	0},	// playitslowly
    {"VirtualBox Machine",	NULL,	NULL,	1 << 2,	1,	0,	0},
    {"VirtualBox Manager",	NULL,	NULL,	1 << 2,	1,	1,	0},
    {"Virtualbox",	NULL,	NULL,	1 << 2,	1,	1,	0},	// idk
    {"virtualbox",	NULL,	NULL,	1 << 2,	1,	1,	0},
    {"VirtualBox Machine",	"VirtualBox Machine",	NULL,	1 << 2,	1,	1,	0},
    {"VirtualBox Manager",	"VirtualBox Manager",	NULL,	1 << 2,	1,	1,	0},

    // {"Com.github.xournalpp.xournalpp",	NULL,	NULL,	1 << 1,	1,	0,	0},
    // {"MuseScore4",	NULL,	NULL,	1 << 4,	3,	0,	1},
    // {"QjackCtl",	NULL,	NULL,	1 << 5,	3,	0,	1},
    // {"Qsynth",	        NULL,	NULL,	1 << 5,	3,	0,	1},
    // {"TuxGuitar",	NULL,		NULL,		1 << 4,		1, 0, 1 },
    // {"libreoffice-calc",	NULL,	NULL,	1 << 0,	1,	0,	0},
    // {"ripcord",	        NULL,	NULL,	1 << 0,	1,	0,	0},
    // {"yuzu",	        NULL,	NULL,	1 << 0,	3,	0,	0},

};

/* layouts */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints = 1; /* 0 = force terminals to use up all extra space */

static const Layout layouts[] = {
    {"[+]", tile}, // 0
    {"[ ]", monocle}, // 1
    {"[|]", deck}, // 2
};

// setxkbmap compose:rctrl seems to remove rctrl entirely (according to
// xmodmap), which is why we want to use multi... but idk how to specify the
// keycode in dwm terms

// keycode 105 (keysym 0xff20, Multi_key)

// https://github.com/chriskmanx/qmole/blob/0c14fa363f174b38a6ec5c6f5ffc75960add7c05/QMOLEDEV/x11vnc-0.9.13/rfb/keysym.h#L138

// attempting to use a non-modifier key (e.g. XK_Multi_key) as a modifier is a
// runtime error (not caught at compile time)
// {XK_Multi_key, KEY, toggleview, {.ui = 1 << TAG}},                    \

#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                               \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                \
  {Mod1Mask, KEY, toggleview, {.ui = 1 << TAG}},                        \
  {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},
// the last trailing comma is required!

// {Mod1Mask, KEY, toggletag, {.ui = 1 << TAG}},                            \
// toggleview = activate (in addition), tag = send to, toggletag = duplicate to

#include <X11/XF86keysym.h> // https://cgit.freedesktop.org/xorg/proto/x11proto/tree/XF86keysym.h

#define SHCMD(cmd) { .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL } }
// https://github.com/TaylanTatli/dwm/blob/master/config.h#L15
// https://wiki.archlinux.org/title/backlight#External_monitors
// https://wiki.archlinux.org/title/backlight#xbacklight
// note: xbacklight/light may not work for all displays; ddcutil may be needed
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *brightdown[] = {"xbacklight", "-dec", "10", NULL};
static const char *brightup[] = {"xbacklight", "-inc", "10", NULL }; // acpilight needs root
static const char *dmenucmd[] = {"rofi", "-show", "run", NULL};
static const char *termcmd[] = {"wezterm", "start", NULL};
// static const char *termcmd[] = {"$TERMINAL", NULL};
static const char *voldown[] = {"vol", "-5", NULL};
static const char *volup[] = {"vol", "+5", NULL};

static Key keys[] = {
    /* {0} just means no arg */
    /* modifier		key		function	argument */

    // home row, 1 adjacent (up/down): asdfjkl; weruio xcvm,.
    // 2 down: -([])=
    // index, pinky: ghtybn z/`'qp

    // windowing
    {MODKEY, XK_i, zoom, {0}}, // switch master/stack, focus master
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY, XK_l, focusmaster,    {0} },

    // terminal
    {MODKEY, XK_d, spawn, SHCMD("o")},
    {MODKEY, XK_e, spawn, {.v = termcmd}},
    {MODKEY, XK_s, spawn, SHCMD("$TERMINAL search")},

    // {MODKEY, XK_a, spawn, SHCMD("$TERMINAL neomutt")},
    {MODKEY, XK_a, spawn, SHCMD("$TERMINAL bash -c 'TERM=xterm-direct neomutt'")},
    {MODKEY, XK_r, spawn, SHCMD("nicotine")},
    {MODKEY, XK_w, spawn, SHCMD("firefox")},

    {MODKEY, XK_o, spawn, SHCMD("$TERMINAL ~/plaque/plaque")},
    {MODKEY, XK_semicolon, spawn, SHCMD("kitty")}, // backup, in case of wezterm config crash
    {MODKEY, XK_u, spawn, SHCMD("playerctl play-pause")},

    {MODKEY, XK_c, setlayout, {.v = &layouts[0]}}, // default
    {MODKEY, XK_v, setlayout, {.v = &layouts[2]}}, // deck
    {MODKEY, XK_x, setlayout, {.v = &layouts[1]}}, // fullscreen

    // m,.
    {MODKEY, XK_comma, spawn, SHCMD("book")},
    {MODKEY, XK_m, spawn, SHCMD("telegram-desktop")},

    // ghtybn z/`'qp

    // TAGKEYS(XK_g, 0)
    // TAGKEYS(XK_h, 1)
    TAGKEYS(XK_3, 0)
    TAGKEYS(XK_7, 2)
    TAGKEYS(XK_8, 1)

    // gtk binds this by default, so this is only to 'enforce' nicotine's
    // exitdialog setting (which only applies to quitting via GUI, not external
    // events)
    {ControlMask, XK_q, killclient, {0}},

    // {MODKEY | ControlMask | ShiftMask, XK_q, quit, {1}}, // restart, rarely used
    {MODKEY | ShiftMask, XK_q, quit, {0}},
    {MODKEY, XK_Tab, view, {0}}, // 'alt-tab'

    // hardware buttons
    {0, 0x1008ff2d, spawn, SHCMD("slock")}, // XF86XK_ScreenSaver; laptop only? -- https://developer.mozilla.org/en-US/docs/Web/API/UI_Events/Keyboard_event_key_values
    {0, XF86XK_AudioLowerVolume, spawn, {.v = voldown}},
    {0, XF86XK_AudioNext, spawn, SHCMD("playerctl next")},
    {0, XF86XK_AudioPlay, spawn, SHCMD("playerctl play-pause")},
    {0, XF86XK_AudioPrev, spawn, SHCMD("playerctl previous")},
    {0, XF86XK_AudioRaiseVolume, spawn, {.v = volup}},
    {0, XF86XK_MonBrightnessDown, spawn, {.v = brightdown}},
    {0, XF86XK_MonBrightnessUp, spawn, {.v = brightup}},

    // screenshot
    // scrot syntax is garbage since it doesn't support true piping
    {MODKEY, XK_p, spawn, SHCMD("maim --hidecursor --quality=10 --select | xclip -selection " "clipboard -t image/png")},
    {MODKEY|ControlMask, XK_p, spawn, SHCMD("maim --hidecursor --quality=10 --select | xclip -selection " "clipboard -t image/png")},
    {MODKEY|ShiftMask, XK_p, spawn, SHCMD("maim --hidecursor --quality=10 --window=$(xdotool getactivewindow) " "| xclip -selection clipboard -t image/png")},
    {MODKEY|ShiftMask|ControlMask, XK_p, spawn, SHCMD("flameshot gui")},

    // {MODKEY, XK_a, spawn, SHCMD("musescore")},
    // {MODKEY, XK_h, spawn, SHCMD("$TERMINAL htop -u $USER")},
    {MODKEY | ShiftMask, XK_v, spawn, SHCMD("vb")}, // hacky

    // // simulate middle click (etc), in conjunction with -option caps:menu. the
    // // ideal case would be to simply continue registering Caps_Lock keypresses,
    // // while disabling the actual caps lock function. however, this does not
    // // appear to be possible -- you either get both the keybind + caps lock as
    // // side effect, or nothing at all. my solution is to replace caps lock with
    // // menu. the original menu key is somehow unaffected (even that isn't that
    // // useful), and caps lock acts as a "dummy" key for middle click.
    // {0, XK_Menu, spawn, SHCMD("caps")},

    // note: dwm 6.3 has a new 'lockfullscreen' const, which i have not added yet
    // https://git.suckless.org/dwm/commit/138b405f0c8aa24d8a040cc1a1cf6e3eb5a0ebc7.html
    // https://old.reddit.com/r/suckless/comments/ox4nls/im_trying_to_build_dwm_with_swallow_patch_but/hznb3cu/
    // https://old.reddit.com/r/suckless/comments/ux2vku/losefullscreen_patches_are_not_working_in_dwm_63/i9yujig/

    // window
    // { MODKEY,		XK_grave,	togglefloating,	{0} },
    // {MODKEY, XK_h, pushup, {0}},
    // {MODKEY, XK_l, pushdown, {0}},

    // tag -- unnecessary, since i focus tags directly
    // {MODKEY, XK_o, shiftviewclients, {.i = +1}}, // next/prev tag
    // {MODKEY, XK_y, shiftviewclients, {.i = -1}},

    // mon -- mostly unnecessary, since windows should just be spawned in the
    // correct mon and remain there
    // {MODKEY, XK_i, focusmon, {.i = +1}},           // focus next mon
    // {MODKEY|ShiftMask, XK_i,     tagmon, {.i = +1}}, // send to next mon

    // functions that i have no use for
    // { MODKEY,		XK_0,		view,		{.ui = ~0 } }, // focus all workspaces
    // { MODKEY,		XK_Left,	setmfact,	{.f = -0.05} }, // widen master
    // { MODKEY,		XK_Right,	setmfact, {.f = +0.05} },
    // { MODKEY,		XK_b,		togglebar,	{0} },
    // { MODKEY|ShiftMask,	XK_0,		tag,		{.ui = ~0 } }, // make tag "sticky"
    // { MODKEY|ShiftMask,	XK_Down,	incnmaster, {.i = -1 } },
    // { MODKEY|ShiftMask,	XK_Tab, setlayout,	{0} },		// toggle between last 2 layouts
    // { MODKEY|ShiftMask,      XK_Up,		incnmaster,	{.i = +1 } }, // add horiz split to master

};

/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static Button buttons[] = {

    // click		event mask	button		function	argument
    // { ClkTagBar,		0,		Button3,	toggleview, {0} },
    // { ClkTagBar,		0,		Button4, shiftviewclients, { .i = -1 } },
    // { ClkTagBar,		0,		Button5, shiftviewclients, { .i = +1 } },
    // { ClkTagBar,		MODKEY,		Button3,	toggletag, {0} }, // duplicate to
    // { ClkWinTitle,	0,		Button2,	zoom,		{0} }, // togglefloating?
    // { ClkWinTitle,	0,		Button4,	focusstack,	{.i = -1 }},
    // { ClkWinTitle,	0,		Button5,	focusstack,	{.i = +1 }}, // might seem useless but good for vbox
    // {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    // {ClkStatusText, 0, Button3, toggleview, {0}}, // TESTING
    {ClkClientWin, MODKEY, 8, view, {0}},
    {ClkClientWin, MODKEY, 9, tagmon, {.i = +1}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}}, // anywhere in window
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkClientWin, MODKEY, Button4, focusstack, {.i = -1}}, // mostly for fullscreen; otherwise focus never travels beyond one window from the current mouse pos
    {ClkClientWin, MODKEY, Button5, focusstack, {.i = +1}},
    {ClkLtSymbol, 0, Button1, setlayout, {0}},                // toggle layouts
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[1]}}, // fullscreen
    {ClkStatusText, 0, Button4, shiftviewclients, {.i = -1}},
    {ClkStatusText, 0, Button5, shiftviewclients, {.i = +1}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button2, toggleview, {0}}, // activate
    {ClkTagBar, ControlMask, Button1, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},       // send to tag
    {ClkWinTitle, 0, Button2, tagmon, {.i = -1}}, // send to mon
    {ClkWinTitle, 0, Button4, shiftviewclients, {.i = -1}},
    {ClkWinTitle, 0, Button5, shiftviewclients, {.i = +1}},
};

static const char *const autostart[] = {
    // cool_autostart
    // anything programs that strictly require a display must be placed here
    // (not .xinitrc)

    // anything that isn't an executable (i.e. longer than 1 word) needs the
    // full syntax

    // TODO: https://wiki.archlinux.org/title/PostgreSQL#Upgrading_PostgreSQL

    // to debug slow startup:
    // journalctl -S today -o short-delta | awk '$4 > 10' | grep '^\[' | less

    "dunst", NULL,
    "udiskie", NULL, // automount all devices

    "sh", "-c", "pkill picom; picom --daemon", NULL,

    "sh", "-c", "pkill dwmstatus; ~/gripts/dwmstatus/dwmstatus", NULL,
    "sh", "-c", "~/gripts/wall/wall", NULL,
    "sh", "-c", "~/scripts/mail", NULL,
    "sh", "-c", "~/scripts/reds &", NULL, // too short to warrant rewrite
    // ~ is only expanded by shell

    "sh", "-c", "~/.config/session.sh", NULL,

    NULL
};
