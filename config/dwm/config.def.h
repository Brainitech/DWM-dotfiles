/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 0;        /* 0 means no systray */
static const unsigned int gappx     = 10;       /* gaps between windows */
static const unsigned int borderalpha = OPAQUE;
static const unsigned int baralpha  = 0xd3;
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int usealtbar          = 1;        /* 1 means use non-dwm status bar */
static const char *altbarclass      = "Polybar"; /* Alternate bar class name */
static const char *altbarcmd        = "$HOME/.config/polybar/launch.sh"; /* Alternate bar launch command */
static const char *barlayout        = "tln|s";
static const char *fonts[]          = { "monospace:size=16" };
static const char dmenufont[]       = "monospace:size=16";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *mutecmd[] = { "pactl", "set-sink-mute", "0", "toggle", NULL };
static const char *volupcmd[] = { "pactl", "set-sink-volume", "0", "+5%", NULL };
static const char *voldowncmd[] = { "pactl", "set-sink-volume", "0", "-5%", NULL };
static const char *brupcmd[] = { "sudo", "xbacklight", "-inc", "10", NULL };
static const char *brdowncmd[] = { "sudo", "xbacklight", "-dec", "10", NULL };
static const char *lockcmd[] = { "dm-tool", "switch-to-greeter", NULL };
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Pavucontrol",    NULL,       NULL,       0,            1,           -1 },
};
	

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const float cfact     = 1.0;    
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ KeyPress,   MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ KeyPress,   MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ KeyPress,   MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ KeyPress,   MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#include <X11/XF86keysym.h>
/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };

/* custom comands */
static const char *rofi[] = { "rofi", "-show", "drun", "-show-emojis", "-show-icons", NULL };
static const char *fmcmd[] = { "thunar", NULL };
static const char *brcmd[] = { "firefox", NULL };
static const char *mpcmd[] = { "spotify", NULL };
static const char *cbcmd[] = { "copyq", NULL };
static const char *prtsc[] = { "flameshot", "gui", NULL };
static const char *chwin[] = { "chwin", NULL };
static const Key keys[] = {
	/* keystate   modifier                     key        function        argument */
	{ KeyPress,   MODKEY,                       XK_q,      spawn,          {.v = rofi } },
	{ KeyPress,   MODKEY,                       XK_t,      spawn,          {.v = termcmd } },
	{ KeyPress,   MODKEY,			            XK_e,	   spawn,	       {.v = fmcmd } },
	{ KeyPress,   MODKEY,                       XK_f,      spawn,          {.v = brcmd } },
	{ KeyPress,   MODKEY,                       XK_s,      spawn,          {.v = mpcmd } },
	{ KeyPress,   0,                          XK_Print,    spawn,          {.v = prtsc } },
	{ KeyPress,   MODKEY,                       XK_x,      spawn,          {.v = lockcmd } },
	{ KeyPress,   MODKEY,                       XK_v,      spawn,          {.v = cbcmd } }, 
	{ KeyPress,   MODKEY|ShiftMask,             XK_Tab,    spawn,          {.v = chwin } },
	{ KeyPress,   MODKEY,                       XK_b,      togglebar,      {0} },
	{ KeyPress,   MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ KeyPress,   MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ KeyPress,   MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ KeyPress,   MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ KeyPress,   MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ KeyPress,   MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ KeyPress,   MODKEY,              	    XK_u,      setcfact,       {.f = +0.25} },
	{ KeyPress,   MODKEY,          		    XK_m,      setcfact,       {.f = -0.25} },
	{ KeyPress,   MODKEY,                       XK_o,      setcfact,       {.f =  0.00} },
	{ KeyPress,   MODKEY,                       XK_Return, zoom,           {0} },
	{ KeyPress,   MODKEY,                       XK_Tab,    view,           {0} },
	{ KeyPress,   MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ KeyPress,   MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ KeyPress,   MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ KeyPress,   MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
	{ KeyPress,   MODKEY|ShiftMask,             XK_u,      setlayout,      {.v = &layouts[3]} },
	{ KeyPress,   MODKEY|ShiftMask,             XK_o,      setlayout,      {.v = &layouts[4]} },
	{ KeyPress,   MODKEY,                       XK_space,  setlayout,      {0} },
	{ KeyPress,   MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ KeyPress,   MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ KeyPress,   MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ KeyPress,   MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ KeyPress,   MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ KeyPress,   MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ KeyPress,   MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ KeyPress,   MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ KeyPress,   MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ KeyPress,   MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	{ KeyPress,     0,			        XF86XK_AudioMute,  spawn,          {.v = mutecmd } },
	{ KeyPress,     0,                            XF86XK_AudioLowerVolume, spawn, {.v = voldowncmd } },
	{ KeyPress,     0,                            XF86XK_AudioRaiseVolume, spawn, {.v = volupcmd } },
	{ KeyPress,     0,                            XF86XK_MonBrightnessUp, spawn, {.v = brupcmd} },
	{ KeyPress,     0,                            XF86XK_MonBrightnessDown, spawn, {.v = brdowncmd} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ KeyPress,  MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
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

static const char *ipcsockpath = "/tmp/dwm.sock";
static IPCCommand ipccommands[] = {
  IPCCOMMAND(  view,                1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggleview,          1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tag,                 1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggletag,           1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tagmon,              1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  focusmon,            1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  focusstack,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  zoom,                1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  incnmaster,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  killclient,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  togglefloating,      1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  setmfact,            1,      {ARG_TYPE_FLOAT}  ),
  IPCCOMMAND(  setlayoutsafe,       1,      {ARG_TYPE_PTR}    ),
  IPCCOMMAND(  quit,                1,      {ARG_TYPE_NONE}   )
};

