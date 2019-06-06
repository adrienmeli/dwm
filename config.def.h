#include <X11/XF86keysym.h>
/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 18;       /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Source Code Pro:size=12:antialias=true:autohint=true" };
static const char dmenufont[]       = "Source Code Pro:size=12:antialias=true:autohint=true";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_green[]       = "#b8d68c";
static const char col_yellow[]      = "#e1aa5d";
static const char col_black[]       = "#000000";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_black, col_green,  col_green  },
	[SchemeTitle]  = { col_black, col_yellow,  col_yellow  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   isterminal noswallow monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           0,         0,        -1 },
	{ "Firefox",  "firefox",       NULL,       0,            0,           0,         0,        -1 },
	{ "Chromium",  "chromium",       NULL,       0,            0,           0,         0,        -1 },
	{ "St",       "st",       NULL,       0,            0,           1,         1,        -1 },
};

/* layout(s) */
static const float mfact     = 0.66; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "focusmaster.c"
#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
//	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "HHH",      grid },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define MODKEY2 Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_green, "-sf", col_black, NULL };
static const char *termcmd[]  = { "st", NULL };

#include "focusurgent.c"
static const char *vifmcmd[]  = { "st", "-e", "vifm", NULL};
static const char *chrocmd[]  = { "/home/adrien/bin/alttab.sh", "chromium",NULL};
static const char *alttab[]  = {  "/home/adrien/bin/alttab.sh", NULL};
static const char *vimcmd[]  = {  "/home/adrien/bin/alttab.sh", "vim", NULL };
static const char *praatcmd[]  = {  "/home/adrien/bin/alttab.sh", "praat", NULL };
static const char *mocpcmd[]  = { "st", "-e", "mocp", NULL};
static const char *arandr[]  = { "arandr",NULL};
static const char *amixer[]  = { "st", "-e", "alsamixer", NULL};
static const char *calendar[]  = { "st", "-e", "vim", "-c", "autocmd VimEnter * Calendar'", NULL};
static const char *mplayerback[] = {"/home/adrien/scripts/system/mplayer","seek","-5",NULL};
static const char *mplayerforw[] = {"/home/adrien/scripts/system/mplayer","seek","+5",NULL};
static const char *mplayerpaus[] = {"/home/adrien/scripts/system/mplayer","pause",NULL};
static const char *mplayerquit[] = {"/home/adrien/scripts/system/mplayer","quit",NULL};
static const char *volumedown[] = { "amixer", "-q", "set", "Master", "2%-", "unmute", NULL };
static const char *volumeup[]   = { "amixer", "-q", "set", "Master", "2%+", "unmute", NULL };
static const char *mute[]       = { "amixer", "-q", "set", "Master", "toggle", NULL };
static const char *bup[]       = { "xbacklight","-inc","2",NULL };
static const char *bdown[]       = { "xbacklight","-dec","2",NULL };
static const char *longman[] = { "wine", "/home/adrien/.lpd/LPD/lpd.exe",NULL};
#include "zoomswap.c"
#include "push.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY2,                      XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_comma,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_semicolon,  incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_m,      focusmaster,    {0} },
	{ MODKEY|ShiftMask,				XK_j,      pushdown,       {0} },
	{ MODKEY|ShiftMask,				XK_k,      pushup,         {0} },
	{ MODKEY,                       XK_Escape, zoom,           {0} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_u,      focusurgent,    {0} },
	{ MODKEY,                       XK_Tab,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_x,      killclient,     {0} },
    //my keys
	{ MODKEY2,                      XK_f,      spawn,          {.v = vifmcmd } },
	{ MODKEY2,                      XK_w,      spawn,          {.v = chrocmd } },
	{ MODKEY2,                      XK_Tab,    spawn,          {.v = alttab } },
	{ MODKEY2,                      XK_v,      spawn,          {.v = vimcmd } },
	{ MODKEY2,                      XK_p,      spawn,          {.v = praatcmd } },
	{ MODKEY2,                      XK_m,      spawn,          {.v = mocpcmd } },
	{ MODKEY2,                      XK_a,      spawn,          {.v = arandr } },
	{ MODKEY2,                      XK_n,      spawn,          {.v = amixer } },
	{ MODKEY2,                      XK_c,      spawn,          {.v = calendar } },
	{ MODKEY2,		                XK_F1,      spawn,	       {.v = mplayerback } },
	{ MODKEY2,		                XK_F2,      spawn,	       {.v = mplayerpaus } },
	{ MODKEY2,		                XK_F3,      spawn,	       {.v = mplayerforw } },
	{ MODKEY2,		                XK_F4,      spawn,	       {.v = mplayerquit } },
	{ MODKEY2,                      XK_l,      spawn,          {.v = longman } },
	{ 0,                            XF86XK_MonBrightnessUp,   spawn,    { .v = bup } },
	{ 0,                            XF86XK_MonBrightnessDown, spawn,    { .v = bdown } },
	{ 0,                            XF86XK_AudioLowerVolume,  spawn,    { .v = volumedown } },
	{ 0,                            XF86XK_AudioRaiseVolume,  spawn,    { .v = volumeup } }, 
	{ 0,                            XF86XK_AudioMute,         spawn,    { .v = mute } }, 
	{ MODKEY,                       XK_agrave, view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_agrave, tag,            {.ui = ~0 } },
    // end of my keys
	{ MODKEY,                       XK_space,  cyclelayout,     {.i = +1} },
	{ MODKEY2,                      XK_j,      focusmon,       {.i = -1 } },
	{ MODKEY2,                      XK_k,      focusmon,       {.i = +1 } },
	{ MODKEY2|ShiftMask,            XK_j,      tagmon,         {.i = -1 } },
	{ MODKEY2|ShiftMask,            XK_k,      tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_ampersand,              0)
    TAGKEYS(                        XK_eacute,                 1)
    TAGKEYS(                        XK_quotedbl,               2)
    TAGKEYS(                        XK_apostrophe,             3)
    TAGKEYS(                        XK_parenleft,              4)
    TAGKEYS(                        XK_minus,                  5)
    TAGKEYS(                        XK_egrave,                 6)
    TAGKEYS(                        XK_underscore,             7)
    TAGKEYS(                        XK_ccedilla,               8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} }
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
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

static const char *dwmfifo = "/home/adrien/dwm.fifo";
static Command commands[] = {
	{ "focusurgent",     focusurgent,      {0} },
    /*
	{ "dmenu",           spawn,          {.v = dmenucmd} },
	{ "term",            spawn,          {.v = termcmd} },
	{ "quit",            quit,           {0} },
	{ "togglebar",       togglebar,      {0} },
	{ "focusstack+",     focusstack,     {.i = +1} },
	{ "focusstack-",     focusstack,     {.i = -1} },
	{ "incnmaster+",     incnmaster,     {.i = +1} },
	{ "incnmaster-",     incnmaster,     {.i = -1} },
	{ "setmfact+",       setmfact,       {.f = +0.05} },
	{ "setmfact-",       setmfact,       {.f = -0.05} },
	{ "zoom",            zoom,           {0} },
	{ "view",            view,           {0} },
	{ "killclient",      killclient,     {0} },
	{ "setlayout-tiled", setlayout,      {.v = &layouts[0]} },
	{ "setlayout-float", setlayout,      {.v = &layouts[1]} },
	{ "setlayout-mono",  setlayout,      {.v = &layouts[2]} },
	{ "togglelayout",    setlayout,      {0} },
	{ "togglefloating",  togglefloating, {0} },
	{ "viewall",         view,           {.ui = ~0} },
	{ "tag",             tag,            {.ui = ~0} },
	{ "focusmon+",       focusmon,       {.i = +1} },
	{ "focusmon-",       focusmon,       {.i = -1} },
	{ "tagmon+",         tagmon,         {.i = +1} },
	{ "tagmon-",         tagmon,         {.i = -1} },
	{ "view1",           view,           {.ui = 1 << 0} },
	{ "view2",           view,           {.ui = 1 << 1} },
	{ "view3",           view,           {.ui = 1 << 2} },
	{ "view4",           view,           {.ui = 1 << 3} },
	{ "view5",           view,           {.ui = 1 << 4} },
	{ "view6",           view,           {.ui = 1 << 5} },
	{ "view7",           view,           {.ui = 1 << 6} },
	{ "view8",           view,           {.ui = 1 << 7} },
	{ "view9",           view,           {.ui = 1 << 8} },
	{ "toggleview1",     toggleview,     {.ui = 1 << 0} },
	{ "toggleview2",     toggleview,     {.ui = 1 << 1} },
	{ "toggleview3",     toggleview,     {.ui = 1 << 2} },
	{ "toggleview4",     toggleview,     {.ui = 1 << 3} },
	{ "toggleview5",     toggleview,     {.ui = 1 << 4} },
	{ "toggleview6",     toggleview,     {.ui = 1 << 5} },
	{ "toggleview7",     toggleview,     {.ui = 1 << 6} },
	{ "toggleview8",     toggleview,     {.ui = 1 << 7} },
	{ "toggleview9",     toggleview,     {.ui = 1 << 8} },
	{ "tag1",            tag,            {.ui = 1 << 0} },
	{ "tag2",            tag,            {.ui = 1 << 1} },
	{ "tag3",            tag,            {.ui = 1 << 2} },
	{ "tag4",            tag,            {.ui = 1 << 3} },
	{ "tag5",            tag,            {.ui = 1 << 4} },
	{ "tag6",            tag,            {.ui = 1 << 5} },
	{ "tag7",            tag,            {.ui = 1 << 6} },
	{ "tag8",            tag,            {.ui = 1 << 7} },
	{ "tag9",            tag,            {.ui = 1 << 8} },
	{ "toggletag1",      toggletag,      {.ui = 1 << 0} },
	{ "toggletag2",      toggletag,      {.ui = 1 << 1} },
	{ "toggletag3",      toggletag,      {.ui = 1 << 2} },
	{ "toggletag4",      toggletag,      {.ui = 1 << 3} },
	{ "toggletag5",      toggletag,      {.ui = 1 << 4} },
	{ "toggletag6",      toggletag,      {.ui = 1 << 5} },
	{ "toggletag7",      toggletag,      {.ui = 1 << 6} },
	{ "toggletag8",      toggletag,      {.ui = 1 << 7} },
	{ "toggletag9",      toggletag,      {.ui = 1 << 8} },
    */
};
