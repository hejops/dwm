/* https://github.com/LukeSmithxyz/dwm/blob/master/config.h
 * http://ratfactor.com/dwm 
 * https://www.youtube.com/watch?v=UEmPboaTDpQ
 * https://www.youtube.com/watch?v=fBrc_xgwQE8
 * todo: 
 * colors
 * program rules, scratchpad
 * status bar
 * perma-run (easy restart)
 * patches:
 * pertag (restrict monocle to 1 tag)
 * ws names: nametag?
 * patch --merge -i [file]
 * diff -u [old] [new] > [diff]
 * patch < [diff]		overwrites the file specified in [diff]
 *				passable conflicts -> "fuzz"
 *				serious conflicts -> generates [old].rej -> change specified files manually
 * patch -R < [diff]		undo changes (also manual ones?)
 * git diff
 * */

/* show in lightdm */
/* https://forum.manjaro.org/t/dwm-not-showing-in-lightdm-log-in-screen/98220/4 */

/* appearance */
static const unsigned int borderpx	= 0;		/* border pixel of windows */
static const unsigned int snap		= 32;		/* snap pixel */
static const int showbar		= 1;		/* 0 means no bar */
static const int topbar			= 0;		/* 0 means bottom bar */
static const char *fonts[]		= { "monaco:size=8", "symbola:size=8" };
static const char dmenufont[]		= "monaco:size=8";
static const char col_gray1[]		= "#222222";
static const char col_gray2[]		= "#444444";
static const char col_gray3[]		= "#bbbbbb";
static const char col_gray4[]		= "#eeeeee";
static const char col_cyan[]		= "#005577";	
static const char *colors[][3]		= {
	/*		fg		bg	 border	*/
/*	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  }, */
	[SchemeNorm] = { col_gray3, col_gray2, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },	/* do sth about the blue; it looks awful with a long status bar */
};

/* tagging ; custom names? */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
/* xprop(1):
 *	WM_CLASS(STRING) = instance, class;	reversed!
 *	WM_NAME(STRING) = title
 *	try to make do without regex first
 *	https://github.com/ericpruitt/edge/blob/master/patches/dwm-00-regex-rules.diff
 */
/* class	instance	title		tags mask	isfloating	 monitor */
/*	{ "Firefox",	NULL,		NULL,		1 << 8,		0,		-1 }, */
{ "Gimp",	NULL,		NULL,		0,		1,		-1 },
{ "discord",	NULL,		NULL,		0,		1,		-1 },
{ "SoulseekQt",	NULL,		NULL,		0,		1,		-1 },
{ "mpv",	NULL,		NULL,		0,		1,		-1 },
{ "Thunar",	NULL,		NULL,		1 << 4,		0,		-1 },
};

/* layout(s) */
static const float mfact	= 0.55;  /* factor of master area size [0.05..0.95] */
static const int nmaster	= 1;	 /* number of clients in master area */
static const int resizehints	= 1;	 /* 0 = force terminals to use up all extra space */

static const Layout layouts[] = {
	/* symbol	arrange function */
	{ "DEF",	tile },		/* first entry is default []= */
	{ "FUL",	monocle },	/* why [N]? */
	{ "CEN",	centeredmaster },
	{ ">M>",	centeredfloatingmaster },
	/* bstack, deck (good for latex) */
/*	{ "><>",	  NULL },	  no layout function means floating behavior */
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
/* static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL }; to change to rofi */
static const char *termcmd[]  = { "urxvt", NULL };

static Key keys[] = {		/* {0} just means no arg */
	/* modifier		key		function	argument */

	{ MODKEY,		XK_c,	   	spawn,		SHCMD("urxvt -e neomutt") },
	{ MODKEY,		XK_d,		spawn,		{.v = dmenucmd } },
	{ MODKEY,		XK_e,	   	spawn,		{.v = termcmd } },
	{ MODKEY,		XK_m,	   	spawn,		SHCMD("urxvt -e ncmpcpp") },
	{ MODKEY,		XK_t,	   	spawn,		SHCMD("telegram-desktop") },
	{ MODKEY,		XK_n,	   	spawn,		SHCMD("urxvt -e newsboat") },
	{ MODKEY,		XK_o,	   	spawn,		SHCMD("transmission-gtk") },
	{ MODKEY,		XK_p,	   	spawn,		SHCMD("mpc toggle") },
	{ MODKEY,		XK_q,	   	spawn,		SHCMD("soulseekqt") },
	{ MODKEY,		XK_s,	   	spawn,		SHCMD("sh ~/scripts/menu-surfraw") },
	{ MODKEY,		XK_w,	   	spawn,		SHCMD("firefox") },
	{ MODKEY|ShiftMask,	XK_d,	   	spawn,		SHCMD("discord") },
	{ MODKEY|ShiftMask,	XK_f,	   	spawn,		SHCMD("urxvt -e sh ~/scripts/ranga") },
	{ MODKEY|ShiftMask,	XK_h,	   	spawn,		SHCMD("urxvt -e htop") },
/*	{ MODKEY|ShiftMask,	XK_Return,	spawn,		{.v = termcmd } }, */

/*	{ MODKEY,		XK_b,	   	togglebar,	{0} },			*/
	{ ControlMask,		XK_q,	   	killclient,	{0} },  /* close window */
	{ MODKEY,		XK_j,	   	focusstack,	{.i = +1 } }, /* cycle focus */
	{ MODKEY,		XK_k,	   	focusstack,	{.i = -1 } },
	{ MODKEY|ShiftMask,	XK_j,	   	incnmaster,	{.i = -1 } },
	{ MODKEY|ShiftMask,	XK_k,	   	incnmaster,	{.i = +1 } }, /* +1 horiz in master */
	{ MODKEY,		XK_h,	   	setmfact,	{.f = -0.05} }, /* widen master */
	{ MODKEY,		XK_l,	   	setmfact,	{.f = +0.05} }, /* might just remove this */
	{ MODKEY,		XK_Return, 	zoom,		{0} },	/* switch master/stack, focus master */
	{ MODKEY,		XK_Tab,  	setlayout,	{0} },	/* toggle between last 2 layouts */
	{ MODKEY|ShiftMask,	XK_Tab,    	view,		{0} },	/* back and forth workspace */
	{ MODKEY|ShiftMask,	XK_grave,  	togglefloating,	{0} },
	{ MODKEY,		XK_0,	   	view,		{.ui = ~0 } }, /* merge all workspaces, use mod+N to go back */
	{ MODKEY|ShiftMask,	XK_0,	   	tag,		{.ui = ~0 } }, /* "sticky" */

	{ MODKEY,		XK_space,   	setlayout,	{.v = &layouts[0]} },	/* default; think of sensible keybinds - maybe ;':" */
	{ MODKEY,		XK_f,	   	setlayout,	{.v = &layouts[1]} },	/* fullscreen */
	{ MODKEY|ControlMask,	XK_space,	setlayout,	{.v = &layouts[2]} },	/* centmast */
	{ MODKEY|ShiftMask,	XK_space,	setlayout,	{.v = &layouts[3]} },	/* centmast float */
/*	{ MODKEY|ShiftMask,	XK_f,	   	setlayout,	{.v = &layouts[1]} },	 all-float */

	TAGKEYS(		XK_1,				0)
	TAGKEYS(		XK_2,			        1)
	TAGKEYS(		XK_3,			        2)
	TAGKEYS(		XK_4,			        3)
	TAGKEYS(		XK_5,			        4)
	TAGKEYS(		XK_6,			        5)
	TAGKEYS(		XK_7,				6)
	TAGKEYS(		XK_8,				7)
	TAGKEYS(		XK_9,				8)
	{ MODKEY,		XK_comma,  	focusmon,	{.i = -1 } }, /* multi-monitor stuff */
	{ MODKEY,		XK_period, 	focusmon,	{.i = +1 } },
	{ MODKEY|ShiftMask,	XK_comma,  	tagmon,		{.i = -1 } },
	{ MODKEY|ShiftMask,	XK_period, 	tagmon,		{.i = +1 } },
	{ MODKEY|ShiftMask,	XK_q,	   	quit,		{0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click		event mask      button		function	argument */
	{ ClkLtSymbol,		0,	       	Button1,	setlayout,	{0} },
	{ ClkLtSymbol,		0,	       	Button3,	setlayout,	{.v = &layouts[2]} },
	{ ClkWinTitle,		0,	       	Button2,	zoom,		{0} },
	{ ClkStatusText,	0,	       	Button2,	spawn,		{.v = termcmd } },
	{ ClkClientWin,		MODKEY,	        Button1,	movemouse,	{0} },
	{ ClkClientWin,		MODKEY,	        Button2,	togglefloating, {0} },
	{ ClkClientWin,		MODKEY,	        Button3,	resizemouse,	{0} },
	{ ClkTagBar,		0,	       	Button1,	view,		{0} },
	{ ClkTagBar,		0,	       	Button3,	toggleview,	{0} },
	{ ClkTagBar,		MODKEY,	        Button1,	tag,		{0} },
	{ ClkTagBar,		MODKEY,	        Button3,	toggletag,	{0} },
};

/* remind nm-applet ncmpcpp */
static const char *const autostart[] = {	/* cool_autostart */
	"sh", "-c", "xinput --set-prop 9 287 -0.8", NULL,
	"mpd", NULL,
	"mpdscribble", NULL,	/* seems to end up with multi-instance; set up if cond */
	"dunst", NULL,
	"udiskie", NULL,
	"sh", "-c", "pidof mpdscribble || mpdscribble", NULL,
	"sh", "-c", "~/dwm/dwm_status_kai.sh", NULL,
	"sh", "-c", "udisksctl mount -b /dev/sdb1", NULL,	/* takes a while, don't panic */
	"sh", "-c", "while :; do feh -r --randomize --bg-fill '/run/media/joseph/My Passport/files/wg/'; sleep 10m; done", NULL,
	/*
	   pkill remind; remind -z10 '-kdunstify %s &' /home/joseph/.reminders/.reminders.rem

	   "hsetroot", "-center", "/usr/home/bit6tream/pic/wallapper.png", NULL,
	   "xrdb", "/usr/home/bit6tream/.config/X/Xresources", NULL,
	   "sh", "-c", "while :; do dwmstatus.sh -; sleep 60; done", NULL,
	   "picom", NULL, */
	NULL
};
