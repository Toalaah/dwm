/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx  = 2;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int startwithgaps[]    = { 1 };	/* 1 means gaps are used by default, this can be customized for each tag */
static const unsigned int gappx[]   = { 4 };   /* default gap between windows in pixels, this can be customized for each tag */
static const int usealtbar          = 1;        /* 1 means use non-dwm status bar */
static const char *altbarclass      = "Polybar"; /* Alternate bar class name */
static const char *alttrayname      = "tray";    /* Polybar tray instance name */
static const char *altbarcmd        = "$HOME/.config/dwm/statusbar/launch.sh"; /* Alternate bar launch command */
static char font[]                = "JetBrains Mono:pixelsize=14:antialias=true:autohint=true";
static char dmenufont[]           = "JetBrains Mono:pixelsize=14:antialias=true:autohint=true";
static const char *fonts[]        = { font, "JoyPixels:pixelsize=12:antialias=true:autohint=true"};
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
  /*               fg           bg           border   */
  [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
  [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static EnvProgram envPrograms[] = {
  /*envPrograms[0] = terminal*/
  {
    "TERMINAL",
    "st"
  },
  /*envPrograms[1] = browser*/
  {
    "BROWSER",
    "chromium"
  }
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class       instance  title           tags mask  isfloating  isterminal   noswallow  monitor */
	{ "Gimp",      NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox",   NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "St",        NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ "kitty",     NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ "Chromium",  NULL,     NULL,           0,         0,          1,           1,        -1 },
	{ "Alacritty", NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,        NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-l", "20", "-c", NULL };
static const char *termcmd[]  = { envPrograms[0].value, NULL };
static const char *browsercmd[]  = { envPrograms[1].value, NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
  { "font",            STRING,  &font },
  { "dmfont",          STRING,  &dmenufont },
  { "color0",          STRING,  &normbgcolor },
  { "color0",          STRING,  &normbordercolor },
  { "color4",          STRING,  &normfgcolor },
  { "color4",          STRING,  &selbgcolor },
  { "color8",          STRING,  &selbordercolor },
  { "color0",          STRING,  &selfgcolor },
  { "borderpx",        INTEGER, &borderpx },
  { "snap",            INTEGER, &snap },
  { "showbar",         INTEGER, &showbar },
  { "topbar",          INTEGER, &topbar },
  { "nmaster",         INTEGER, &nmaster },
  { "resizehints",     INTEGER, &resizehints },
  { "mfact",           FLOAT,   &mfact },
};

#include "shiftview.c"
#define SUPERSHFTCTRL MODKEY|ShiftMask|ControlMask

static const Key keys[] = {
	/* modifier          key        function        argument */
  { MODKEY,            XK_p,      spawn,             {.v = dmenucmd } },
  { MODKEY|ShiftMask,  XK_Return, spawn,             {.v = termcmd } },
  { MODKEY,            XK_w,      spawn,             {.v = browsercmd } },
  { MODKEY|ShiftMask,  XK_p,      spawn,             SHCMD("dmenu-pass") },
  { MODKEY,            XK_F1,     spawn,             SHCMD("set-wallpaper") },
  { MODKEY,            XK_F2,     spawn,             SHCMD("dmenu-net") },
  { MODKEY,            XK_F3,     spawn,             SHCMD("dmenu-mount") },
  { MODKEY,            XK_F4,     spawn,             SHCMD("dmenu-vpn") },
  { MODKEY,            XK_F6,     spawn,             SHCMD("dmenu-logout") },
  { MODKEY|ShiftMask,  XK_e,      spawn,             SHCMD("dmenu-emoji") },
  { MODKEY|ShiftMask,  XK_b,      spawn,             SHCMD("dmenu-bookmarks") },
  { MODKEY|ShiftMask,  XK_c,      spawn,             SHCMD("edit-config") },
  { MODKEY,            XK_equal,  spawn,             SHCMD("set-volume -i; pkill -RTMIN+10 dwmblocks") },
  { MODKEY,            XK_minus,  spawn,             SHCMD("set-volume -d; pkill -RTMIN+10 dwmblocks") },
  { MODKEY,            XK_0,      spawn,             SHCMD("set-volume; pkill -RTMIN+10 dwmblocks") },
  { MODKEY,            XK_b,      togglebar,         {0} },
  { MODKEY,            XK_j,      focusstack,        {.i = +1 } },
  { MODKEY,            XK_k,      focusstack,        {.i = -1 } },
  { MODKEY,            XK_i,      incnmaster,        {.i = +1 } },
  { MODKEY,            XK_d,      incnmaster,        {.i = -1 } },
  { MODKEY,            XK_h,      setmfact,          {.f = -0.05} },
  { MODKEY,            XK_l,      setmfact,          {.f = +0.05} },
  { SUPERSHFTCTRL,     XK_l,      spawn,             SHCMD("lock")},
  { MODKEY,            XK_Return, zoom,              {0} },
  { MODKEY,            XK_Tab,    view,              {0} },
  { MODKEY,            XK_u,      shiftview,         {.i = -1 } },
  { MODKEY,            XK_o,      shiftview,         {.i = +1 } },
  { MODKEY,            XK_q,      killclient,        {0} },
  { MODKEY,            XK_t,      setlayout,         {.v = &layouts[0]} },
  { MODKEY,            XK_f,      setlayout,         {.v = &layouts[1]} },
  { MODKEY,            XK_m,      setlayout,         {.v = &layouts[2]} },
  { MODKEY|ShiftMask,  XK_r,      reload_wm,         {0} },
  { MODKEY,            XK_space,  setlayout,         {0} },
  { MODKEY|ShiftMask,  XK_space,  togglefloating,    {0} },
  { MODKEY|ShiftMask,  XK_f,      togglefullscr,     {0} },
  { MODKEY,            XK_comma,  focusmon,          {.i = -1 } },
  { MODKEY,            XK_period, focusmon,          {.i = +1 } },
  { MODKEY|ShiftMask,  XK_comma,  tagmon,            {.i = -1 } },
  { MODKEY|ShiftMask,  XK_period, tagmon,            {.i = +1 } },
  { MODKEY,            XK_F5,     reload_xresources, {.v = NULL } },
  { MODKEY|ShiftMask,  XK_j,      setgaps,           {.i = -1 } },
  { MODKEY|ShiftMask,  XK_k,      setgaps,           {.i = +1 } },
	{ MODKEY|ShiftMask,  XK_l,      setgaps,           {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,  XK_m,      setgaps,           {.i = GAP_TOGGLE} },
  { MODKEY|ShiftMask,  XK_q,      quit,              {0} },
	TAGKEYS(             XK_1,                          0)
	TAGKEYS(             XK_2,                          1)
	TAGKEYS(             XK_3,                          2)
	TAGKEYS(             XK_4,                          3)
	TAGKEYS(             XK_5,                          4)
	TAGKEYS(             XK_6,                          5)
	TAGKEYS(             XK_7,                          6)
	TAGKEYS(             XK_8,                          7)
	TAGKEYS(             XK_9,                          8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

