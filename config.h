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
static const int topbar = 1;            // 0 means bottom bar -- testing
static const char *fonts[] = {"haskplex:size=8",
                              /* "fira mono:size=8", */
                              /* "ia writer mono s:size=8", */
                              /* "monaco:size=8", */
                              "symbola:size=8"
                             }; // may require font-awesome
// static const char dmenufont[]		= "monaco:size=8";

// https://camo.githubusercontent.com/cdb2f2e986c564b515c0c698e6c45b4ab5d725a9/687474703a2f2f692e696d6775722e636f6d2f776136363678672e706e67
static const char blue[] = "#458688";
static const char gray[] = "#131313";
static const char green[] = "#98971a";
static const char lightgray[] = "#282828";
static const char red[] = "#cc241d";
static const char white2[] = "#ebdbb2";
static const char white[] = "#bbbbbb";

static const char *colors[][3] = {
    //			fg	bg	border
    [SchemeNorm] = {white2, gray, gray},
    [SchemeSel] = {blue, gray, blue},
};

// tag names -- testing
// https://github.com/meinwald/DWM-config/blob/master/config.h#L16
// https://libredd.it/r/suckless/comments/id0q64/how_to_get_more_than_9_tags_in_dwm/g26yhdl/?context=3
static const char *tags[] = {
    "main", "work", "muse", "win7", "jack", "6", "7", "8", "cal",
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

    // class	instance	title		tags mask	switch	float
    // monitor

    // main screen
    // note: (physically) larger monitor must be secondary (1)
    // { "MuseScore3",	NULL,		NULL,		1 << 4,		1, 0, 1 },
    // { "TuxGuitar",	NULL,		NULL,		1 << 4,		1, 0, 1 },
    {"Nicotine", NULL, NULL, 1 << 0, 1, 0, 1},
    {"firefox", NULL, NULL, 1 << 0, 1, 0, -1}, // drag tab to monitor only works if the correct workspace is active
    // (otherwise goes back to original monitor...)
    {"mpv", NULL, NULL, 1 << 0, 1, 0, 1},

    {"MuseScore4", NULL, NULL, 1 << 4, 3, 0, 1},
    {"QjackCtl", NULL, NULL, 1 << 5, 3, 0, 1},
    {"Qsynth", NULL, NULL, 1 << 5, 3, 0, 1},
    {NULL, NULL, "calcurse", 1 << 8, 3, 0, 1},

    // floats
    {"Display", NULL, NULL, 0, 0, 1, 0}, // PIL
    {"Gimp", NULL, NULL, 0, 0, 1, -1},
    {"Gpick", "gpick", NULL, 0, 0, 1, -1},
    {"PPSSPPQt", NULL, NULL, 0, 0, 1, 1},
    {"Pavucontrol", NULL, NULL, 0, 0, 1, -1},
    {"TelegramDesktop", NULL, NULL, 0, 0, 1, -1},
    {"discord", NULL, NULL, 0, 0, 1, 0},
    {"mednafen", NULL, NULL, 0, 0, 1, 1},

    // slave screen
    // switch should generally be 1
    // { "libreoffice-writer",	NULL,	NULL,		0,		0, 0, 1 },
    // { NULL,		"libreoffice",	NULL,		1 << 0,		1, 0, 0 }, // doesn't work

    {"Chromium", NULL, NULL, 1 << 1, 3, 0, 0},
    {"Com.github.xournalpp.xournalpp", NULL, NULL, 1 << 1, 1, 0, 0},
    {"Evince", NULL, NULL, 1 << 1, 1, 0, 0},
    {"Matplotlib", NULL, NULL, 1 << 0, 1, 0, 0},
    {"Zathura", NULL, NULL, 1 << 0, 3, 0, 0},
    {"feh", NULL, NULL, 1 << 0, 1, 0, 0},
    {"imv", NULL, NULL, 1 << 0, 1, 0, 0},
    {"libreoffice-calc", NULL, NULL, 1 << 0, 1, 0, 0},
    {"ripcord", NULL, NULL, 1 << 0, 1, 0, 0},
    {"teams-for-linux", NULL, NULL, 1 << 1, 3, 0, 0},
    {"yuzu", NULL, NULL, 1 << 0, 3, 0, 0},
    {"zoom", NULL, NULL, 1 << 1, 1, 0, 0},

    {"App.py", NULL, NULL, 1 << 3, 1, 1, 0}, // playitslowly
    {"VirtualBox Machine", NULL, NULL, 1 << 3, 1, 0, 0},
    {"VirtualBox Machine", "VirtualBox Machine", NULL, 1 << 3, 1, 1, 0},
    {"VirtualBox Manager", NULL, NULL, 1 << 3, 1, 1, 0},
    {"VirtualBox Manager", "VirtualBox Manager", NULL, 1 << 3, 1, 1, 0},
    {"Virtualbox", NULL, NULL, 1 << 3, 1, 1, 0}, // idk
    {"virtualbox", NULL, NULL, 1 << 3, 1, 1, 0},

    // TODO:
    // WM_NAME(STRING) = "win7 on QEMU/KVM User session"
    // _NET_WM_ICON_NAME(UTF8_STRING) = "win7 on QEMU/KVM User session"
    // _NET_WM_NAME(UTF8_STRING) = "win7 on QEMU/KVM User session"
    // { "FLTK",	NULL,		NULL,		0,		0, 1, 1 }, // vmd
    // { "MestReNova",	NULL,		NULL,		1 << 1,		1, 0, 1 },
    // { "Thunar",	NULL,		NULL,		0,		0, 1, -1 },
    // { "Virt-manager",	NULL,	NULL,		1 << 3,		1, 0, 1 },
    // { NULL,		NULL,		"artemis",	1 << 2,		3, 0, 1 },
    // { NULL,		NULL,		"oceanids",	1 << 2,		3, 0, 1 },
    // { NULL,		NULL,		"shux",		1 << 2,		3, 0, 1 },
    // { NULL,		NULL,	"win7 on QEMU/KVM User session",1 << 3,	1, 0, 1 }, // idk

};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    1; /* 0 = force terminals to use up all extra space */

static const Layout layouts[] = {
    {"DEF", tile}, {"FUL", monocle}, {"DEC", deck},
    //	{ "BST",	bstack },
    //	{ "><>",	  NULL },
};

#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {Mod1Mask, KEY, toggletag, {.ui = 1 << TAG}},                            \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggleview, {.ui = 1 << TAG}},
/* { MODKEY|ShiftMask,		KEY,	  tag,		{.ui = 1 << TAG} }, \ */
// toggleview = activate (in addition), tag = send to, toggletag = duplicate to
// these combinations are all unwieldy
// alt+\d is unreliable
// TODO: toggletag + view simultaneously

#include <X11/XF86keysym.h> // https://cgit.freedesktop.org/xorg/proto/x11proto/tree/XF86keysym.h

#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {"rofi", "-show", "run", NULL};
// static const char *termcmd[]	= { "urxvt", NULL };
static const char *termcmd[] = {"kitty", NULL};
// https://wiki.archlinux.org/title/backlight#xbacklight
// note: xbacklight/light may not work for all displays; ddcutil may be needed
// https://wiki.archlinux.org/title/backlight#External_monitors
static const char *brightup[] = {"xbacklight", "-inc", "10",
                                 NULL
                                }; // acpilight needs root
static const char *brightdown[] = {"xbacklight", "-dec", "10", NULL};
static const char *volup[] = {"vol", "+5", NULL};
static const char *voldown[] = {"vol", "-5", NULL};
// https://github.com/TaylanTatli/dwm/blob/master/config.h#L15

static Key keys[] = {
    /* {0} just means no arg */
    /* modifier		key		function	argument */

    {MODKEY, XK_d, spawn, {.v = dmenucmd}},
    {MODKEY, XK_e, spawn, {.v = termcmd}},

    // unbound: ahinopuxyz

    /* {0, 0x1008ff2d, spawn, SHCMD("i3lock -c 000000")}, */
    // // kitty has poor compatibility { MODKEY,		XK_b,
    // < ~/dwm/config.h grep -P '^\s+\{\s*MODKEY,\s+XK_[a-z],' | sort | cut -f4-
    // {MODKEY | ShiftMask, XK_e, spawn, SHCMD("kitty")},
    // {MODKEY | ShiftMask, XK_t, spawn, SHCMD("transmission-gtk")},
    // {MODKEY, XK_a, spawn, SHCMD("musescore")},
    // {MODKEY, XK_h, spawn, SHCMD("kitty -e htop")},
    {0, 0x1008ff2d, spawn, SHCMD("slock")},
    {MODKEY | ShiftMask, XK_v, spawn, SHCMD("vb")}, // hacky
    {MODKEY | ShiftMask, XK_w, spawn, SHCMD("wttr")},
    {MODKEY, XK_Delete, spawn, SHCMD("i3lock -c 000000")},
    {MODKEY, XK_Print, spawn, SHCMD("flameshot gui")},
    {MODKEY, XK_b, spawn, SHCMD("book")},
    {MODKEY, XK_c, spawn, SHCMD("kitty -e neomutt")},
    {MODKEY, XK_q, spawn, SHCMD("nicotine")},
    {MODKEY, XK_t, spawn, SHCMD("telegram-desktop")},
    {MODKEY, XK_w, spawn, SHCMD("firefox")},

    // hardware buttons
    {0, XF86XK_AudioLowerVolume, spawn, {.v = voldown}},
    {0, XF86XK_AudioRaiseVolume, spawn, {.v = volup}},
    {0, XF86XK_MonBrightnessDown, spawn, {.v = brightdown}},
    {0, XF86XK_MonBrightnessUp, spawn, {.v = brightup}}, // xbacklight doesn't work on asus

    // simulate middle click (etc), in conjunction with -option caps:menu. the
    // ideal case would be to simply continue registering Caps_Lock keypresses,
    // while disabling the actual caps lock function. however, this does not
    // appear to be possible -- you either get both the keybind + caps lock as
    // side effect, or nothing at all. my solution is to replace caps lock with
    // menu. the original menu key is somehow unaffected (even that isn't that
    // useful), and caps lock acts as a "dummy" key for middle click.
    {0, XK_Menu, spawn, SHCMD("caps")},

    // screenshot
    // scrot syntax is garbage since it doesn't support true piping
    {0, XK_Print, spawn, SHCMD("maim --hidecursor --quality=10 --select | xclip -selection " "clipboard -t image/png")},
    {MODKEY | ShiftMask, XK_p, spawn, SHCMD("maim --hidecursor --quality=10 --select | xclip -selection " "clipboard -t image/png")},
    {ControlMask, XK_Print, spawn, SHCMD("maim --hidecursor --quality=10 --window=$(xdotool getactivewindow) " "| xclip -selection clipboard -t image/png")},
    {MODKEY | ControlMask, XK_p, spawn, SHCMD("maim --hidecursor --quality=10 --window=$(xdotool getactivewindow) " "| xclip -selection clipboard -t image/png")},
    {ShiftMask, XK_Print, spawn, SHCMD("maim --hidecursor --quality=10 | tee ~/$(date -Iseconds).png | " "xclip -selection clipboard -t image/png")},

    // rofi
    {MODKEY, XK_m, spawn, SHCMD("kitty -e pmp --queue")},
    {MODKEY, XK_r, spawn, SHCMD("o")},
    {MODKEY, XK_s, spawn, SHCMD("kitty --hold search")}, // --hold is necessary for rust
    {MODKEY, XK_semicolon, spawn, SHCMD("kitty -e pmp")}, // prompt

    // media control
    // {MODKEY, XK_comma, spawn, SHCMD("rmpv -b")},  // seek backward
    // {MODKEY, XK_slash, spawn, SHCMD("rmpv -f")},  // seek forward
    // {MODKEY, XK_x, spawn, SHCMD("rmpv -q")},      // quit
    {0, XF86XK_AudioNext, spawn, SHCMD("rmpv -f")},
    {0, XF86XK_AudioPlay, spawn, SHCMD("rmpv -t")},
    {0, XF86XK_AudioPrev, spawn, SHCMD("rmpv -b")},
    {MODKEY, XK_comma, spawn, SHCMD("rmpv -t")}, // toggle

    // layout
    {MODKEY, XK_f, setlayout, {.v = &layouts[1]}}, // fullscreen
    {MODKEY, XK_g, setlayout, {.v = &layouts[0]}}, // default
    {MODKEY, XK_v, setlayout, {.v = &layouts[2]}}, // deck

    // note: dwm 6.3 has a new 'lockfullscreen' const, which i have not added yet
    // https://git.suckless.org/dwm/commit/138b405f0c8aa24d8a040cc1a1cf6e3eb5a0ebc7.html
    // https://old.reddit.com/r/suckless/comments/ox4nls/im_trying_to_build_dwm_with_swallow_patch_but/hznb3cu/
    // https://old.reddit.com/r/suckless/comments/ux2vku/losefullscreen_patches_are_not_working_in_dwm_63/i9yujig/

    // window
    // { MODKEY,		XK_grave,	togglefloating,	{0} },
    // { MODKEY,           XK_h,  focusmaster,    {0} },
    // {MODKEY, XK_h, pushup, {0}},
    // {MODKEY, XK_l, pushdown, {0}},
    {ControlMask, XK_q, killclient, {0}},
    {MODKEY | ControlMask | ShiftMask, XK_q, quit, {1}}, // restart, rarely used
    {MODKEY | ShiftMask, XK_q, quit, {0}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY, XK_l,  focusmaster,    {0} },
    {MODKEY, XK_space, zoom, {0}}, // switch master/stack, focus master

    // workspace
    // { MODKEY,		XK_bracketleft, shiftviewclients,	{ .i = -1 } },
    // { MODKEY,		XK_bracketright,shiftviewclients,	{ .i = +1 } }, // cycle tag focus
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
    TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
    TAGKEYS(XK_9, 8)
    {
        MODKEY, XK_Tab, view, {0}
    }, // i often use this one-handed

    // // i am increasingly living in a single tag (and enjoying it!)
    // {MODKEY, XK_o, shiftviewclients, {.i = +1}}, // cycle tag focus
    // {MODKEY, XK_u, view, {0}},                   // intuitive with mod+i
    // {MODKEY, XK_y, shiftviewclients, {.i = -1}},

    // i don't have a second monitor right now; and might not need one anymore, thanks to kvm
    // { ControlMask,		XK_grave,	spawn,		SHCMD("mond --toggle") }, // i just use a kvm nowadays
    // { MODKEY,		XK_0,		spawn,		SHCMD("mon --on > mon.log") },
    // { MODKEY,		XK_b,		spawn, SHCMD("mond --on") },
    // { MODKEY|ShiftMask,	XK_space,	tagmon,		{.i = +1 } },
    // {MODKEY | ShiftMask, XK_i, tagmon, {.i = +1}}, // send to mon
    // {MODKEY, XK_i, focusmon, {.i = +1}},           // switch mon

    // 60% keyboard workarounds
    // { MODKEY,		XK_bracketleft,	spawn,		SHCMD("") },
    // {MODKEY | ControlMask, XK_comma, spawn, {.v = voldown}},
    // {MODKEY | ControlMask, XK_period, spawn, {.v = volup}},
    // {MODKEY | Mod1Mask, XK_c, spawn, {.v = volup}},
    // {MODKEY | Mod1Mask, XK_x, spawn, {.v = voldown}},
    // {MODKEY, XK_equal, spawn, {.v = volup}},
    // {MODKEY, XK_minus, spawn, {.v = voldown}},

    // // gimmicks that i don't use
    // { MODKEY,		XK_0,		view,		{.ui = ~0 } }, // merge all workspaces
    // { MODKEY,		XK_Left,	setmfact,	{.f = -0.05} }, // widen master
    // { MODKEY,		XK_Right,	setmfact, {.f = +0.05} },
    // { MODKEY,		XK_b,		togglebar,	{0} },
    // { MODKEY|ShiftMask,	XK_0,		tag,		{.ui = ~0 } }, // "sticky"
    // { MODKEY|ShiftMask,	XK_Down,	incnmaster, {.i = -1 } },	// +1 horiz in master
    // { MODKEY|ShiftMask,	XK_Tab, setlayout,	{0} },		// toggle between last 2 layouts
    // { MODKEY|ShiftMask, XK_Up,		incnmaster,	{.i = +1 } },

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
    {ClkClientWin, MODKEY, 8, view, {0}},
    {ClkClientWin, MODKEY, 9, tagmon, {.i = +1}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}}, // anywhere in window
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkClientWin, MODKEY, Button4, focusstack, {.i = -1}}, // mostly for fullscreen; otherwise focus never travels beyond one window from the current mouse pos
    {ClkClientWin, MODKEY, Button5, focusstack, {.i = +1}},
    {ClkLtSymbol, 0, Button1, setlayout, {0}},                // toggle layouts
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[1]}}, // fullscreen
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkStatusText, 0, Button3, toggleview, {0}}, // TESTING
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

    "sh", "-c", "pkill picom; picom -b", NULL, // -b = daemon; run order (wrt mon) doesn't really matter
    "sh", "-c", "sleep 1; ~/scripts/wallset", NULL,
    "sh", "-c", "~/dwm/dwmstatus", NULL,
    "sh", "-c", "~/scripts/mon.py", NULL,
    "sh", "-c", "~/scripts/reds &", NULL,

    NULL
};
