/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx      = 4;        /* border pixel of windows */
static const int startwithgaps[]  = { 1 };	  /* 1 means gaps are used by default, this can be customized for each tag */
static const unsigned int gappx[] = { 4 };    /* default gap between windows in pixels, this can be customized for each tag */
static unsigned int snap          = 32;       /* snap pixel */
static int showbar                = 1;        /* 0 means no bar */
static int topbar                 = 1;        /* 0 means bottom bar */
static char font[]                = "Fira Code Nerd Font:pixelsize=14:antialias=true:autohint=true";
static char dmenufont[]           = "Fira Code Nerd Font:pixelsize=14:antialias=true:autohint=true";
static const char *fonts[]        = { font };
static char normbgcolor[]         = "#000000";
static char normfgcolor[]         = "#ffffff";
static char normbordercolor[]     = "#000000";
static char selbgcolor[]          = "#282828";
static char selfgcolor[]          = "#ffffff";
static char selbordercolor[]      = "#ffffff";
static char *colors[][3] = {
  [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
  [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
 };

static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const int hidevacanttags            = 0; /* 0 means workspaces with no content are hidden*/
static const int highlightnonvacanttags         = 1; /* 1 means non-vacant workspaces are given an indicator to show they have content*/
static const unsigned int activetagpad     = 5; /* horizontal padding between the active tag indicator line and tag borders */
static const unsigned int ulinepad	       = 0;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	     = 2;	/* thickness / height of the underline */
static const unsigned int activetagstroke	 = 1;	/* thickness / height of the underline */
static const unsigned int ulinevoffset     = 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		             = 0;	/* 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
  { "Gimp",     NULL,       NULL,       0,            1,           -1 },
  { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
  { "[]=",      tile },    /* first entry is default */
  { "><>",      NULL },    /* no layout function means floating behavior */
  { "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
};

/* key definitions */
#define MODKEY Mod4Mask
#define MODKEY_ALT Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
/* forward declaration of shiftview function, see bottom of file for implementation */
void shiftview(const Arg *arg); 
/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };

/* Xresources preferences to load at startup */
ResourcePref resources[] = {
  { "font",            STRING,  &font },
  { "dmenufont",       STRING,  &dmenufont },
  { "color0",          STRING,  &normbgcolor },
  { "color0",          STRING,  &normbordercolor },
  { "color4",          STRING,  &normfgcolor },
  { "color4",          STRING,  &selbgcolor },
  { "color8",          STRING,  &selbordercolor },
  { "color0",          STRING,  &selfgcolor },
  { "borderpx",        INTEGER, &borderpx },
  { "snap",          	 INTEGER, &snap },
  { "showbar",         INTEGER, &showbar },
  { "topbar",          INTEGER, &topbar },
  { "nmaster",         INTEGER, &nmaster },
  { "resizehints",     INTEGER, &resizehints },
  { "mfact",      	 	 FLOAT,   &mfact },
};

static Key keys[] = {
  /* modifier          key        function           argument */
  { MODKEY,            XK_p,      spawn,             {.v = dmenucmd } },
  { MODKEY|ShiftMask,  XK_Return, spawn,             {.v = termcmd } },
  { MODKEY,            XK_b,      togglebar,         {0} },
  { MODKEY,            XK_j,      focusstack,        {.i = +1 } },
  { MODKEY,            XK_k,      focusstack,        {.i = -1 } },
  { MODKEY,            XK_i,      incnmaster,        {.i = +1 } },
  { MODKEY,            XK_d,      incnmaster,        {.i = -1 } },
  { MODKEY,            XK_h,      setmfact,          {.f = -0.05} },
  { MODKEY,            XK_l,      setmfact,          {.f = +0.05} },
  { MODKEY,            XK_Return, zoom,              {0} },
  { MODKEY,            XK_Tab,    view,              {0} },
  { MODKEY, 	         XK_q,      killclient,        {0} },
  { MODKEY,            XK_t,      setlayout,         {.v = &layouts[0]} },
  { MODKEY,            XK_f,      setlayout,         {.v = &layouts[1]} },
  { MODKEY,            XK_m,      setlayout,         {.v = &layouts[2]} },
  { MODKEY,            XK_space,  setlayout,         {0} },
  { MODKEY|ShiftMask,  XK_space,  togglefloating,    {0} },
  { MODKEY,            XK_0,      view,              {.ui = ~0 } },
  { MODKEY|ShiftMask,  XK_0,      tag,               {.ui = ~0 } },
  { MODKEY,            XK_comma,  focusmon,          {.i = -1 } },
  { MODKEY,            XK_period, focusmon,          {.i = +1 } },
  { MODKEY,            XK_u,      shiftview,         {.i = -1 } },
  { MODKEY,            XK_o,      shiftview,         {.i = +1 } },
  { MODKEY|ShiftMask,  XK_comma,  tagmon,            {.i = -1 } },
  { MODKEY|ShiftMask,  XK_period, tagmon,            {.i = +1 } },
  { MODKEY|ShiftMask,  XK_j,      setgaps,           {.i = -1 } },
  { MODKEY|ShiftMask,  XK_k,      setgaps,           {.i = +1 } },
  { MODKEY|ShiftMask,  XK_l,      setgaps,           {.i = 0  } },
  { MODKEY,            XK_F5,     reload_xresources, {.v = NULL } },
  { MODKEY|ShiftMask,  XK_q,      quit,              {0} },

  TAGKEYS(             XK_1,                      0)
  TAGKEYS(             XK_2,                      1)
  TAGKEYS(             XK_3,                      2)
  TAGKEYS(             XK_4,                      3)
  TAGKEYS(             XK_5,                      4)
  TAGKEYS(             XK_6,                      5)
  TAGKEYS(             XK_7,                      6)
  TAGKEYS(             XK_8,                      7)
  TAGKEYS(             XK_9,                      8)
};

/* button definitions */
static Button buttons[] = {
  { ClkLtSymbol,   0,      Button1, setlayout,      {0} },
  { ClkLtSymbol,   0,      Button3, setlayout,      {.v = &layouts[2]} },
  { ClkWinTitle,   0,      Button2, zoom,           {0} },
  { ClkStatusText, 0,      Button2, spawn,          {.v = termcmd } },
  { ClkClientWin,  MODKEY, Button1, movemouse,      {0} },
  { ClkClientWin,  MODKEY, Button2, togglefloating, {0} },
  { ClkClientWin,  MODKEY, Button3, resizemouse,    {0} },
  { ClkTagBar,     0,      Button1, view,           {0} },
  { ClkTagBar,     0,      Button3, toggleview,     {0} },
  { ClkTagBar,     MODKEY, Button1, tag,            {0} },
  { ClkTagBar,     MODKEY, Button3, toggletag,      {0} },
};

void 
shiftview(const Arg *arg) 
{
	Arg shifted;
	if(arg->i > 0) // left circular shift
		shifted.ui = (selmon->tagset[selmon->seltags] << arg->i)
		   | (selmon->tagset[selmon->seltags] >> (LENGTH(tags) - arg->i));
	else // right circular shift
		shifted.ui = selmon->tagset[selmon->seltags] >> (- arg->i)
		   | selmon->tagset[selmon->seltags] << (LENGTH(tags) + arg->i);
	view(&shifted);
}

