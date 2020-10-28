// https://github.com/LukeSmithxyz/dwm/blob/master/config.h
// http://ratfactor.com/dwm 
// https://www.youtube.com/watch?v=UEmPboaTDpQ
// https://www.youtube.com/watch?v=fBrc_xgwQE8

// patches to try: regex rules, focusadjacenttag, focusonnetactive, swapfocus, switchtotag, zoomswap
// patch --merge -i [file]
// diff -u [old] [new] > [diff]
// patch < [diff]		overwrites the file specified in [diff]
//				passable conflicts -> "fuzz"
//				serious conflicts -> generates [old].rej -> change specified files manually
// patch -R < [diff]		undo changes (also manual ones?)
// git diff

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
static const int topbar			= 0;	// 0 means bottom bar
static const char *fonts[]		= { "monaco:size=8", "symbola:size=8" };	// requires font-awesome, apparently
static const char dmenufont[]		= "monaco:size=8";

// https://camo.githubusercontent.com/cdb2f2e986c564b515c0c698e6c45b4ab5d725a9/687474703a2f2f692e696d6775722e636f6d2f776136363678672e706e67
static const char blue[]		= "#458688";
static const char gray[]		= "#131313";
static const char green[]		= "#98971a";
static const char lightgray[]		= "#282828";
static const char red[]			= "#cc241d";
static const char white2[]		= "#ebdbb2";
static const char white[]		= "#bbbbbb";

static const char *colors[][3]		= {
//			fg	bg	 border
	[SchemeNorm] = { white2, gray, gray },
	[SchemeSel]  = { blue, gray, blue },
};

// tag names -- testing
// https://github.com/meinwald/DWM-config/blob/master/config.h#L16
static const char *tags[] = { "main", "down", "work", "vbox", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	// xprop(1):
	// WM_CLASS(STRING) = instance, class;	reversed!
	// WM_NAME(STRING) = title
	// try to make do without regex first
	// https://github.com/ericpruitt/edge/blob/master/patches/dwm-00-regex-rules.diff
	// https://www.tutorialspoint.com/c_standard_library/c_function_strstr.htm
	// switch = switchtotag (not switchtag), float = isfloating

	// class	instance	title		tags mask	switch	float	monitor
	// switchtotag doesn't seem to handle windows spawned on new monitor -- can send to mon 1, but cannot switch to tag 9
	// why does tag 0 mon 0 create a new tag?
	{ "mednafen",	NULL,		NULL,		0,		0,	1,	1 },
	{ "mpv",	NULL,		NULL,		0,		0,	1,	1 },
	{ "PPSSPPQt",	NULL,		NULL,		0,		0,	1,	1 },

	{ "discord",	NULL,		NULL,		0,		0,	1,	-1 },
	{ "Gimp",	NULL,		NULL,		0,		0,	1,	-1 },
	{ "Gpick",	"gpick",	NULL,		0,		0,	1,	-1 },
	{ "matplotlib",	NULL,		NULL,		0,		0,	1,	-1 },
	{ "Pavucontrol",	NULL,	NULL,		0,		0,	1,	-1 },
	{ "TelegramDesktop", NULL,	NULL,		0,		0,	1,	-1 },
	{ "Thunar",	NULL,		NULL,		0,		0,	1,	-1 },

	{ "SoulseekQt",	NULL,		NULL,		1 << 1,		1,	1,	-1 },	// very strange behaviour; spawns empty tags and prevents switching to tag 1 -- or is it shiftview?
	{ "Transmission-gtk",	NULL,	NULL,		1 << 1,		1,	0,	-1 },
	{ "URxvt",	"urxvt",	"deeznu",	1 << 1,		0,	0,	-1 },	// unreliable
	{ NULL,		NULL,		"deeznuts",	1 << 1,		0,	0,	-1 },	// unreliable

	{ "zoom",	NULL,		NULL,		1 << 2,		1,	0,	-1 },

	{ "App.py",	NULL,		NULL,		1 << 3,		1,	1,	-1 },	// playitslowly
	{ "TuxGuitar",	NULL,		NULL,		1 << 3,		1,	0,	-1 },
	{ "VirtualBox Machine",	NULL,	NULL,		1 << 3,		1,	0,	-1 },
	{ "VirtualBox Manager",	NULL,	NULL,		1 << 3,		1,	1,	-1 },
};

/* layout(s) */
static const float mfact	= 0.55;  /* factor of master area size [0.05..0.95] */
static const int nmaster	= 1;	 /* number of clients in master area */
static const int resizehints	= 1;	 /* 0 = force terminals to use up all extra space */

static const Layout layouts[] = {
	{ "DEF",	tile },
	{ "FUL",	monocle },
	{ "DEC",	deck },
	{ "BST",	bstack },
//	{ "><>",	  NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,			KEY,	  view,		{.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,		KEY,	  toggleview,	{.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,		KEY,	  tag,		{.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,	  toggletag,	{.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "rofi", "-show", "run", NULL }; 
/* static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", white, "-sb", col_cyan, "-sf", col_gray4, NULL }; to change to rofi */
static const char *termcmd[]  = { "urxvt", NULL };
static const char *brightup[]	    = { "xbacklight", "-inc", "10", NULL};	// acpilight needs root
static const char *brightdown[]     = { "xbacklight", "-dec", "10", NULL};

static Key keys[] = {		/* {0} just means no arg */
	/* modifier		key		function	argument */

	// misc: rofimoji
	// still unbound: airu-=; zx (shiftview?); backspace (focus master), backslash
	// virtualbox "/home/joseph/VirtualBox VMs/7/7.vbox"
	// virtualbox "/home/joseph/VirtualBox VMs/xp/xp.vbox" -- what keybind?
	{ 0,			0x1008ff02,	spawn,		{.v = brightup } },
	{ 0,			0x1008ff03,	spawn,		{.v = brightdown } },
	{ 0,			XK_Print,	spawn,		SHCMD("sleep 0.2; scrot -s /tmp/screenshot-$(date +%F_%T).png -e 'xclip -selection c -t image/png < $f'") },
	{ ControlMask,		XK_Print,	spawn,		SHCMD("scrot -u /tmp/screenshot-$(date +%F_%T).png -e 'xclip -selection c -t image/png < $f'") },
	{ Mod1Mask|ControlMask|ShiftMask,	XK_d,	spawn,	SHCMD("urxvt -e bash ~/scripts/deeznuts") },
	{ MODKEY,		XK_a,		spawn,		SHCMD("localc") },
	{ MODKEY,		XK_c,		spawn,		SHCMD("urxvt -e neomutt") },
	{ MODKEY,		XK_d,		spawn,		{.v = dmenucmd } },
	{ MODKEY,		XK_e,		spawn,		{.v = termcmd } },
	{ MODKEY,		XK_m,		spawn,		SHCMD("urxvt -e ncmpcpp") },
	{ MODKEY,		XK_minus,	spawn,		SHCMD("sh ~/scripts/not") },
	{ MODKEY,		XK_n,		spawn,		SHCMD("urxvt -e newsboat") },
	{ MODKEY,		XK_o,		spawn,		SHCMD("transmission-gtk") },
	{ MODKEY,		XK_p,		spawn,		SHCMD("mpc toggle") },
	{ MODKEY,		XK_Print,	spawn,		SHCMD("flameshot gui") },
	{ MODKEY,		XK_q,		spawn,		SHCMD("soulseekqt") },
	{ MODKEY,		XK_s,		spawn,		SHCMD("sh ~/scripts/menu-surfraw") },
	{ MODKEY,		XK_t,		spawn,		SHCMD("telegram-desktop") },
	{ MODKEY,		XK_w,		spawn,		SHCMD("firefox") },
	{ MODKEY,		XK_y,		spawn,		SHCMD("urxvt -e sh ~/scripts/nobrow") },
	{ MODKEY|ShiftMask,	XK_d,		spawn,		SHCMD("discord-ptb") },
	{ MODKEY|ShiftMask,	XK_f,		spawn,		SHCMD("urxvt -e sh ~/scripts/ranga") },
	{ MODKEY|ShiftMask,	XK_h,		spawn,		SHCMD("urxvt -e htop") },
	{ MODKEY|ShiftMask,	XK_p,		spawn,		SHCMD("sh ~/scripts/mpcrym") },
	{ ShiftMask,		XK_Print,	spawn,		SHCMD("scrot /tmp/screenshot-$(date +%F_%T).png -e 'xclip -selection c -t image/png < $f'") },

// https://dwm.suckless.org/patches/keypressrelease/
// https://gitlab.com/rafa_99/dwm/blob/master/config.h#L152

//	{ MODKEY,		XK_b,		togglebar,	{0} },
	{ ControlMask,		XK_q,		killclient,	{0} },	// close window
	{ MODKEY,		XK_j,		focusstack,	{.i = +1 } },	// cycle window focus
	{ MODKEY,		XK_k,		focusstack,	{.i = -1 } },
	{ MODKEY,		XK_l,		pushdown,       {0} },
	{ MODKEY,		XK_h,		pushup,         {0} },
	{ MODKEY,		XK_bracketright,shiftviewclients,	{ .i = +1 } },	// cycle tag focus
	{ MODKEY,		XK_bracketleft, shiftviewclients,	{ .i = -1 } },
	{ MODKEY,		XK_space,	zoom,		{0} },	// switch master/stack, focus master
	{ MODKEY,		XK_Tab,		view,		{0} },	// back and forth workspace
	{ MODKEY|ShiftMask,	XK_Tab,		setlayout,	{0} },	// toggle between last 2 layouts
	{ MODKEY,		XK_grave,	togglefloating,	{0} },
//	{ MODKEY,		XK_0,		view,		{.ui = ~0 } }, // merge all workspaces; i almost never use this
	{ MODKEY|ShiftMask,	XK_0,		tag,		{.ui = ~0 } }, // "sticky"

	// rarely used
	{ MODKEY|ShiftMask,	XK_Down,	incnmaster,	{.i = -1 } },	// +1 horiz in master
	{ MODKEY|ShiftMask,	XK_Up,		incnmaster,	{.i = +1 } }, 
	{ MODKEY,		XK_Left,	setmfact,	{.f = -0.05} }, // widen master
	{ MODKEY,		XK_Right,	setmfact,	{.f = +0.05} }, 

	{ MODKEY,		XK_g,		setlayout,	{.v = &layouts[0]} },	// default
	{ MODKEY,		XK_f,		setlayout,	{.v = &layouts[1]} },	// fullscreen
	{ MODKEY,		XK_v,		setlayout,	{.v = &layouts[2]} },	// deck -- v? weird but neat...
	{ MODKEY,		XK_b,		setlayout,	{.v = &layouts[3]} },	// bstack

	TAGKEYS(		XK_1,				0)
	TAGKEYS(		XK_2,				1)
	TAGKEYS(		XK_3,				2)
	TAGKEYS(		XK_4,				3)
	TAGKEYS(		XK_5,				4)
	TAGKEYS(		XK_6,				5)
	TAGKEYS(		XK_7,				6)
	TAGKEYS(		XK_8,				7)
	TAGKEYS(		XK_9,				8)
	{ MODKEY,		XK_0,		spawn,		SHCMD("sh ~/scripts/mon") },	// toggle 2nd mon
	{ MODKEY,		XK_comma,	focusmon,	{.i = -1 } }, // change focus; cursor unaffected
	{ MODKEY,		XK_period,	focusmon,	{.i = +1 } },
	{ MODKEY|ShiftMask,	XK_comma,	tagmon,		{.i = -1 } }, // move window to mon
	{ MODKEY|ShiftMask,	XK_period,	tagmon,		{.i = +1 } },
	{ MODKEY|ShiftMask,	XK_q,		quit,		{0} },
	{ MODKEY|ControlMask|ShiftMask,	XK_q,	quit,		{1} },
};

/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {

	//click			event mask	button		function	argument
	{ ClkClientWin,		MODKEY,		Button1,	movemouse,	{0} },	// anywhere in window
	{ ClkClientWin,		MODKEY,		Button2,	togglefloating, {0} },
	{ ClkClientWin,		MODKEY,		Button3,	resizemouse,	{0} },
	{ ClkLtSymbol,		0,		Button1,	setlayout,	{0} },	// layout symbol
	{ ClkLtSymbol,		0,		Button3,	setlayout,	{.v = &layouts[1]} },
	{ ClkStatusText,	0,		Button2,	spawn,		{.v = termcmd } },
	{ ClkTagBar,		0,		Button1,	view,		{0} },
	{ ClkTagBar,		MODKEY,		Button1,	tag,		{0} },
	{ ClkTagBar,		MODKEY,		Button3,	toggletag,	{0} },	// move to tag
	{ ClkWinTitle,		0,		Button1,	focusstack,	{.i = +1 }},	// might seem useless but good for vbox
	{ ClkWinTitle,		0,		Button2,	zoom,		{0} },	// togglefloating?
	{ ClkWinTitle,		0,		Button3,	focusstack,	{.i = -1 }},
//	{ ClkTagBar,		0,		Button3,	toggleview,	{0} },	very strange
};

static const char *const autostart[] = {	// cool_autostart

	"dunst", NULL,		// any command longer than 1 word needs the long syntax, apparently
	"mpd", NULL,		// can be pretty slow on cold boot; e.g. "Cannot assign requested address"
	"sh", "-c", "picom -b --config .picom.conf",	NULL,
	"sh", "-c", "pkill mpdscribble; mpdscribble",	NULL,	// pidof || method -> running, but inactive
	"sh", "-c", "redshift -x; redshift -b 1",	NULL,		// pkill doesn't affect redshift!
	"sh", "-c", "setxkbmap -option compose:rctrl",	NULL,
	"sh", "-c", "udisksctl mount -b /dev/sdb1",	NULL,	// takes a while, don't panic
	"sh", "-c", "while :; do feh -r --randomize --bg-fill '/run/media/joseph/My Passport/files/wg/'; sleep 10m; done", NULL,	// 1st 10 min will fail; waiting to mount
	"sh", "-c", "~/dwm/dwm_status_kai.sh",	NULL,	// unreliable; start manually, kill, then can autostart again
	"sh", "-c", "~/scripts/mon",		NULL,	// needs work
	"udiskie", NULL,
	//"sh", "-c", "notify-send \"dwm started\"", NULL,
	//"sh", "-c", "~/scripts/mouse",		NULL,
	NULL

//	"hsetroot", "-center", "/usr/home/bit6tream/pic/wallapper.png", NULL,
//	pkill remind; remind -z10 '-kdunstify %s &' /home/joseph/.reminders/.reminders.rem
};
