/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx      = 2;        /* border pixel of windows */
static const int startwithgaps[]  = { 1 };    /* 1 means gaps are used by default, this can be customized for each tag */
static const unsigned int gappx[] = { 10 };   /* default gap between windows in pixels, this can be customized for each tag */
static unsigned int snap          = 32;       /* snap pixel */
static int showbar                = 1;        /* 0 means no bar */
static const int showtitles       = 0;        /* 0 means title of the currently selected window is not shown */
static const int swallowfloating  = 0;        /* 1 means swallow floating windows by default */
static int topbar                 = 1;        /* 0 means bottom bar */
static char font[]                = "JetBrains Mono Nerd Font:pixelsize=14:antialias=true:autohint=true";
static char dmenufont[]           = "JetBrains Mono Nerd Font:pixelsize=14:antialias=true:autohint=true";
static const char *fonts[]        = { font, "JoyPixels:pixelsize=12:antialias=true:autohint=true"};
static char normbgcolor[]         = "#000000";
static char normfgcolor[]         = "#ffffff";
static char normbordercolor[]     = "#000000";
static char selbgcolor[]          = "#282828";
static char selfgcolor[]          = "#ffffff";
static char selbordercolor[]      = "#ffffff";
static char *colors[][3] = {
  [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
  [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
  [SchemeTitle]  = { selbgcolor,  selfgcolor,  selbordercolor  },
 };

static const char *tags[]     = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tagsalt[] = { "", "", "爵", "爵", "切", "ﭮ", "", "", "" };
static const int momentaryalttags = 0; /* 1 means alttags will show only when key is held down*/

static const int hidevacanttags            = 0; /* 0 means workspaces with no content are hidden*/
static const int highlightnonvacanttags    = 1; /* 1 means non-vacant workspaces are given an indicator to show they have content*/
static const unsigned int activetagpad     = 5; /* horizontal padding between the active tag indicator line and tag borders */
static const unsigned int ulinepad         = 0;  /* horizontal padding between the underline and tag */
static const unsigned int ulinestroke       = 2;  /* thickness / height of the underline */
static const unsigned int activetagstroke   = 1;  /* thickness / height of the underline */
static const unsigned int ulinevoffset     = 0;  /* how far above the bottom of the bar the line should appear */
static const int ulineall                  = 0;  /* 1 to show underline on all tags, 0 for just the active ones */
static char terminal[50];
static char browser[50];

static const Rule rules[] = {
  /* class       instance  title           tags mask  isfloating  isterminal   noswallow scratchkey    monitor */
  { "Gimp",      NULL,     NULL,           0,         1,          0,           0,        0,            -1 },
  { "Firefox",   NULL,     NULL,           1 << 8,    0,          0,          -1,        0,            -1 },
  { "St",        NULL,     NULL,           0,         0,          1,           0,        0,            -1 },
  { "kitty",     NULL,     NULL,           0,         0,          1,           0,        0,            -1 },
  { "Alacritty", NULL,     NULL,           0,         0,          1,           0,        0,            -1 },
  { "Chromium",  NULL,     NULL,           0,         0,          1,           1,        0,            -1 },
  { NULL,        NULL,     "Event Tester", 0,         0,          0,           1,        0,            -1 }, /* xev */
  { NULL,        NULL,     "scratchpad",   0,         1,          0,           0,       's',           -1 },
};

/* layout(s) */
static float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
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
static const char *termcmd[]  = { terminal, NULL };
static const char *browsercmd[]  = { browser, NULL };
static const char *fileexplorercmd[] = {terminal, "-e", "ranger", NULL};

/*First arg only serves to match against key in rules*/
static const char *scratchpadcmd[] = {"s", terminal, "-t", "scratchpad", "-e", NULL};

/* Xresources preferences to load at startup */
ResourcePref resources[] = {
  { "font",            STRING,  &font },
  { "font",            STRING,  &dmenufont },
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
  { "mfact",            FLOAT,   &mfact },
};

static Key keys[] = {
  /* modifier          key        function           argument */
  { MODKEY,            XK_p,      spawn,             {.v = dmenucmd } },
  { MODKEY|ShiftMask,  XK_Return, spawn,             {.v = termcmd } },
  { MODKEY,            XK_e,      togglescratch,     {.v = scratchpadcmd } },
  { MODKEY,            XK_r,      spawn,             {.v = fileexplorercmd } },
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
  { MODKEY,            XK_n,      togglealttag,      {0} },
  { MODKEY,            XK_b,      togglebar,         {0} },
  { MODKEY,            XK_j,      focusstack,        {.i = +1 } },
  { MODKEY,            XK_k,      focusstack,        {.i = -1 } },
  { MODKEY,            XK_i,      incnmaster,        {.i = +1 } },
  { MODKEY,            XK_d,      incnmaster,        {.i = -1 } },
  { MODKEY,            XK_h,      setmfact,          {.f = -0.05} },
  { MODKEY,            XK_l,      setmfact,          {.f = +0.05} },
  { MODKEY,            XK_Return, zoom,              {0} },
  { MODKEY,            XK_Tab,    view,              {0} },
  { MODKEY,            XK_q,      killclient,        {0} },
  { MODKEY,            XK_t,      setlayout,         {.v = &layouts[0]} },
  { MODKEY,            XK_f,      setlayout,         {.v = &layouts[1]} },
  { MODKEY,            XK_m,      setlayout,         {.v = &layouts[2]} },
  { MODKEY,            XK_c,      setlayout,         {.v = &layouts[3]} },
  { MODKEY|ShiftMask,  XK_f,      togglefullscr,     {0} },
  { MODKEY,            XK_space,  setlayout,         {0} },
  { MODKEY|ShiftMask,  XK_space,  togglefloating,    {0} },
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

