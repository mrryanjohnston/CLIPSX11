   /*******************************************************/
   /*      "C" Language Integrated Production System      */
   /*                                                     */
   /*            CLIPS Version 6.40  07/30/16             */
   /*                                                     */
   /*                USER FUNCTIONS MODULE                */
   /*******************************************************/

/*************************************************************/
/* Purpose:                                                  */
/*                                                           */
/* Principal Programmer(s):                                  */
/*      Gary D. Riley                                        */
/*                                                           */
/* Contributing Programmer(s):                               */
/*                                                           */
/* Revision History:                                         */
/*                                                           */
/*      6.24: Created file to seperate UserFunctions and     */
/*            EnvUserFunctions from main.c.                  */
/*                                                           */
/*      6.30: Removed conditional code for unsupported       */
/*            compilers/operating systems (IBM_MCW,          */
/*            MAC_MCW, and IBM_TBC).                         */
/*                                                           */
/*            Removed use of void pointers for specific      */
/*            data structures.                               */
/*                                                           */
/*************************************************************/

/***************************************************************************/
/*                                                                         */
/* Permission is hereby granted, free of charge, to any person obtaining   */
/* a copy of this software and associated documentation files (the         */
/* "Software"), to deal in the Software without restriction, including     */
/* without limitation the rights to use, copy, modify, merge, publish,     */
/* distribute, and/or sell copies of the Software, and to permit persons   */
/* to whom the Software is furnished to do so.                             */
/*                                                                         */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS */
/* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF              */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT   */
/* OF THIRD PARTY RIGHTS. IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY  */
/* CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES */
/* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN   */
/* ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF */
/* OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.          */
/*                                                                         */
/***************************************************************************/

#include "clips.h"
#include <string.h>
#include <X11/cursorfont.h>
#include <X11/Xlib.h>
#include <X11/Xos.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <alloca.h>

void UserFunctions(Environment *);

void XOpenDisplayFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	UDFValue theArg;
	if (UDFHasNextArgument(context))
	{
		UDFNextArgument(context,LEXEME_BITS,&theArg);
		if (!(display = XOpenDisplay(theArg.lexemeValue->contents))) {
			WriteString(theEnv,STDERR,"Could not open display '");
			WriteString(theEnv,STDERR,theArg.lexemeValue->contents);
			WriteString(theEnv,STDERR,"'.\n");
			returnValue->lexemeValue = FalseSymbol(theEnv);
			return;
		}
	} else if (!(display = XOpenDisplay(NULL))) {
		WriteString(theEnv,STDERR,"Could not open display.\n");
		returnValue->lexemeValue = FalseSymbol(theEnv);
		return;
	}
	returnValue->externalAddressValue = CreateCExternalAddress(theEnv, (void*)display);
}

void XCloseDisplayFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	XCloseDisplay(display);
}

void DefaultScreenFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	returnValue->integerValue = CreateInteger(theEnv, DefaultScreen(display));
}

void DefaultScreenOfDisplayFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	returnValue->externalAddressValue = CreateCExternalAddress(theEnv, (void*)DefaultScreenOfDisplay(display));
}

void DefaultRootWindowFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	returnValue->integerValue = CreateInteger(theEnv, (int)DefaultRootWindow(display));
}

void RootWindowFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	int screen;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	screen = theArg.integerValue->contents;

	returnValue->integerValue = CreateInteger(theEnv, (int)RootWindow(display, screen));
}

void XCreateSimpleWindowFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	Window parent;
	int x, y;
	unsigned int width, height;
	unsigned int border_width;
	unsigned long border;
	unsigned long background;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	parent = (Window)theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	x = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	y = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	width = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	height = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	border_width = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	border = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	background = theArg.integerValue->contents;

	returnValue->integerValue = CreateInteger(theEnv, (int)XCreateSimpleWindow(display, parent, x, y, width, height, border_width, 
                             border, background));
}

void XCreateWindowFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	Window parent;
	int x, y;
	unsigned int width, height;
	unsigned int border_width;
	int depth;
	unsigned int class;
	Visual *visual;
	unsigned long valuemask;
	XSetWindowAttributes *attributes;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	parent = (Window)theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	x = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	y = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	width = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	height = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	border_width = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	depth = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	class = theArg.integerValue->contents;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	visual = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	valuemask = theArg.integerValue->contents;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	attributes = theArg.externalAddressValue->contents;

	returnValue->integerValue = CreateInteger(theEnv, (int)XCreateWindow(display, parent, x, y, width, height, border_width, depth, class, visual, valuemask, attributes));
}

void XDestroyWindowFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	int window;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	window = theArg.integerValue->contents;

	XDestroyWindow(display, window);
}

void XCreateFontCursorFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	int shape;

	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,SYMBOL_BIT,&theArg);
	if (0 == strcmp(theArg.lexemeValue->contents, "XC_X_cursor"))
	{
		shape = XC_X_cursor;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_arrow"))
	{
		shape = XC_arrow;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_based_arrow_down"))
	{
		shape = XC_based_arrow_down;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_based_arrow_up"))
	{
		shape = XC_based_arrow_up;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_boat"))
	{
		shape = XC_boat;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_bogosity"))
	{
		shape = XC_bogosity;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_bottom_left_corner"))
	{
		shape = XC_bottom_left_corner;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_bottom_right_corner"))
	{
		shape = XC_bottom_right_corner;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_bottom_side"))
	{
		shape = XC_bottom_side;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_bottom_tee"))
	{
		shape = XC_bottom_tee;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_box_spiral"))
	{
		shape = XC_box_spiral;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_center_ptr"))
	{
		shape = XC_center_ptr;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_circle"))
	{
		shape = XC_circle;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_clock"))
	{
		shape = XC_clock;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_coffee_mug"))
	{
		shape = XC_coffee_mug;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_cross"))
	{
		shape = XC_cross;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_cross_reverse"))
	{
		shape = XC_cross_reverse;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_crosshair"))
	{
		shape = XC_crosshair;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_diamond_cross"))
	{
		shape = XC_diamond_cross;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_dot"))
	{
		shape = XC_dot;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_dotbox"))
	{
		shape = XC_dotbox;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_double_arrow"))
	{
		shape = XC_double_arrow;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_draft_large"))
	{
		shape = XC_draft_large;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_draft_small"))
	{
		shape = XC_draft_small;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_draped_box"))
	{
		shape = XC_draped_box;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_exchange"))
	{
		shape = XC_exchange;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_fleur"))
	{
		shape = XC_fleur;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_gobbler"))
	{
		shape = XC_gobbler;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_gumby"))
	{
		shape = XC_gumby;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_hand1"))
	{
		shape = XC_hand1;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_hand2"))
	{
		shape = XC_hand2;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_heart"))
	{
		shape = XC_heart;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_icon"))
	{
		shape = XC_icon;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_iron_cross"))
	{
		shape = XC_iron_cross;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_left_ptr"))
	{
		shape = XC_left_ptr;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_left_side"))
	{
		shape = XC_left_side;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_left_tee"))
	{
		shape = XC_left_tee;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_leftbutton"))
	{
		shape = XC_leftbutton;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_ll_angle"))
	{
		shape = XC_ll_angle;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_lr_angle"))
	{
		shape = XC_lr_angle;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_man"))
	{
		shape = XC_man;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_middlebutton"))
	{
		shape = XC_middlebutton;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_mouse"))
	{
		shape = XC_mouse;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_pencil"))
	{
		shape = XC_pencil;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_pirate"))
	{
		shape = XC_pirate;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_plus"))
	{
		shape = XC_plus;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_question_arrow"))
	{
		shape = XC_question_arrow;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_right_ptr"))
	{
		shape = XC_right_ptr;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_right_side"))
	{
		shape = XC_right_side;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_right_tee"))
	{
		shape = XC_right_tee;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_rightbutton"))
	{
		shape = XC_rightbutton;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_rtl_logo"))
	{
		shape = XC_rtl_logo;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_sailboat"))
	{
		shape = XC_sailboat;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_sb_down_arrow"))
	{
		shape = XC_sb_down_arrow;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_sb_h_double_arrow"))
	{
		shape = XC_sb_h_double_arrow;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_sb_left_arrow"))
	{
		shape = XC_sb_left_arrow;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_sb_right_arrow"))
	{
		shape = XC_sb_right_arrow;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_sb_up_arrow"))
	{
		shape = XC_sb_up_arrow;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_sb_v_double_arrow"))
	{
		shape = XC_sb_v_double_arrow;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_shuttle"))
	{
		shape = XC_shuttle;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_sizing"))
	{
		shape = XC_sizing;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_spider"))
	{
		shape = XC_spider;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_spraycan"))
	{
		shape = XC_spraycan;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_star"))
	{
		shape = XC_star;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_target"))
	{
		shape = XC_target;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_tcross"))
	{
		shape = XC_tcross;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_top_left_arrow"))
	{
		shape = XC_top_left_arrow;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_top_left_corner"))
	{
		shape = XC_top_left_corner;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_top_right_corner"))
	{
		shape = XC_top_right_corner;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_top_side"))
	{
		shape = XC_top_side;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_top_tee"))
	{
		shape = XC_top_tee;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_trek"))
	{
		shape = XC_trek;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_ul_angle"))
	{
		shape = XC_ul_angle;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_umbrella"))
	{
		shape = XC_umbrella;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_ur_angle"))
	{
		shape = XC_ur_angle;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_watch"))
	{
		shape = XC_watch;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "XC_xterm"))
	{
		shape = XC_xterm;
	}
	else
	{
		WriteString(theEnv,STDERR,"Shape '");
		WriteString(theEnv,STDERR,theArg.lexemeValue->contents);
		WriteString(theEnv,STDERR,"' not supported.\n");
		returnValue->lexemeValue = FalseSymbol(theEnv);
		return;
	}

	returnValue->integerValue = CreateInteger(theEnv, (int)XCreateFontCursor(display, shape));
}

void XMapWindowFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	Window window;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	window = theArg.integerValue->contents;

	XMapWindow(display, window);
}

void XUnmapWindowFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	Window window;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	window = theArg.integerValue->contents;

	XUnmapWindow(display, window);
}

void XReparentWindowFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	Window window, parent;
	int x, y;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	window = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	parent = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	x = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	y = theArg.integerValue->contents;

	XReparentWindow(display, window, parent, x, y);
}

void XMoveResizeWindowFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	Window w;
	int x, y;
	unsigned int width, height;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	w = (Window)theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	x = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	y = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	width = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	height = theArg.integerValue->contents;

	returnValue->integerValue = CreateInteger(theEnv, (int)XMoveResizeWindow(display, w, x, y, width, height));
}

void XCirculateSubwindowsUpFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	Window window;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	window = theArg.integerValue->contents;

	returnValue->integerValue = CreateInteger(theEnv, XCirculateSubwindowsUp(display, window));
}

void XRaiseWindowFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	Window window;
	UDFValue theArg;

	UDFNextArgument(context, EXTERNAL_ADDRESS_BIT, &theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context, INTEGER_BIT, &theArg);
	window = (Window) theArg.integerValue->contents;

	XRaiseWindow(display, window);
}

void XLowerWindowFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	Window   window;
	UDFValue theArg;

	UDFNextArgument(context, EXTERNAL_ADDRESS_BIT, &theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context, INTEGER_BIT, &theArg);
	window = (Window) theArg.integerValue->contents;

	XLowerWindow(display, window);
}

const char* BoolToStr(bool b)
{
	if (b)
	{
		return "TRUE";
	}
	else
	{
		return "FALSE";
	}
}

const char *WindowPropertyMapStateToStr(int map_state)
{
	switch(map_state)
	{
		case IsUnmapped:
			return "IsUnmapped";
		case IsUnviewable:
			return "IsUnviewable";
		case IsViewable:
			return "IsViewable";
		default:
			return "";
	}
}

const char *EventMaskToString(long mask)
{
	switch (mask)
	{
		case KeyPressMask:
			return "KeyPressMask";
		case KeyReleaseMask:
			return "KeyReleaseMask";
		case ButtonPressMask:
			return "ButtonPressMask";
		case ButtonReleaseMask:
			return "ButtonReleaseMask";
		case EnterWindowMask:
			return "EnterWindowMask";
		case LeaveWindowMask:
			return "LeaveWindowMask";
		case PointerMotionMask:
			return "PointerMotionMask";
		case PointerMotionHintMask:
			return "PointerMotionHintMask";
		case Button1MotionMask:
			return "Button1MotionMask";
		case Button2MotionMask:
			return "Button2MotionMask";
		case Button3MotionMask:
			return "Button3MotionMask";
		case Button4MotionMask:
			return "Button4MotionMask";
		case Button5MotionMask:
			return "Button5MotionMask";
		case ButtonMotionMask:
			return "ButtonMotionMask";
		case KeymapStateMask:
			return "KeymapStateMask";
		case ExposureMask:
			return "ExposureMask";
		case VisibilityChangeMask:
			return "VisibilityChangeMask";
		case StructureNotifyMask:
			return "StructureNotifyMask";
		case ResizeRedirectMask:
			return "ResizeRedirectMask";
		case SubstructureNotifyMask:
			return "SubstructureNotifyMask";
		case SubstructureRedirectMask:
			return "SubstructureRedirectMask";
		case FocusChangeMask:
			return "FocusChangeMask";
		case PropertyChangeMask:
			return "PropertyChangeMask";
		case ColormapChangeMask:
			return "ColormapChangeMask";
		case OwnerGrabButtonMask:
			return "OwnerGrabButtonMask";
		default:
			return NULL;
	}
}

void EventMaskToSymbolFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	const char *sym;
	UDFValue theArg;

	UDFNextArgument(context,INTEGER_BIT,&theArg);

	sym = EventMaskToString(theArg.integerValue->contents);
	if (sym != NULL)
	{
		returnValue->lexemeValue = CreateSymbol(theEnv, sym);
	}
	else
	{
		WriteInteger(theEnv,STDERR,theArg.integerValue->contents);
		WriteString(theEnv,STDERR," is not a valid event mask\n");
		returnValue->voidValue = VoidConstant(theEnv);
	}
}

Multifield *EventMaskToMultifield(long mask, MultifieldBuilder *mb)
{
	if (mask & KeyPressMask)           MBAppendSymbol(mb, "KeyPressMask");
	if (mask & KeyReleaseMask)         MBAppendSymbol(mb, "KeyReleaseMask");
	if (mask & ButtonPressMask)        MBAppendSymbol(mb, "ButtonPressMask");
	if (mask & ButtonReleaseMask)      MBAppendSymbol(mb, "ButtonReleaseMask");
	if (mask & EnterWindowMask)        MBAppendSymbol(mb, "EnterWindowMask");
	if (mask & LeaveWindowMask)        MBAppendSymbol(mb, "LeaveWindowMask");
	if (mask & PointerMotionMask)      MBAppendSymbol(mb, "PointerMotionMask");
	if (mask & PointerMotionHintMask)  MBAppendSymbol(mb, "PointerMotionHintMask");
	if (mask & Button1MotionMask)      MBAppendSymbol(mb, "Button1MotionMask");
	if (mask & Button2MotionMask)      MBAppendSymbol(mb, "Button2MotionMask");
	if (mask & Button3MotionMask)      MBAppendSymbol(mb, "Button3MotionMask");
	if (mask & Button4MotionMask)      MBAppendSymbol(mb, "Button4MotionMask");
	if (mask & Button5MotionMask)      MBAppendSymbol(mb, "Button5MotionMask");
	if (mask & ButtonMotionMask)       MBAppendSymbol(mb, "ButtonMotionMask");
	if (mask & KeymapStateMask)        MBAppendSymbol(mb, "KeymapStateMask");
	if (mask & ExposureMask)           MBAppendSymbol(mb, "ExposureMask");
	if (mask & VisibilityChangeMask)   MBAppendSymbol(mb, "VisibilityChangeMask");
	if (mask & StructureNotifyMask)    MBAppendSymbol(mb, "StructureNotifyMask");
	if (mask & ResizeRedirectMask)     MBAppendSymbol(mb, "ResizeRedirectMask");
	if (mask & SubstructureNotifyMask) MBAppendSymbol(mb, "SubstructureNotifyMask");
	if (mask & SubstructureRedirectMask) MBAppendSymbol(mb, "SubstructureRedirectMask");
	if (mask & FocusChangeMask)        MBAppendSymbol(mb, "FocusChangeMask");
	if (mask & PropertyChangeMask)     MBAppendSymbol(mb, "PropertyChangeMask");
	if (mask & ColormapChangeMask)     MBAppendSymbol(mb, "ColormapChangeMask");
	if (mask & OwnerGrabButtonMask)    MBAppendSymbol(mb, "OwnerGrabButtonMask");

	return MBCreate(mb);
}

void ReportIBMakeError(
		Environment *theEnv)
{
	switch(IBError(theEnv))
	{
		case IBE_NO_ERROR:
			WriteString(theEnv,STDERR,"No error occurred\n");
			break;
		case IBE_NULL_POINTER_ERROR:
			WriteString(theEnv,STDERR,"The InstanceBuilder does not have an associated defclass\n");
			break;
		case IBE_DEFCLASS_NOT_FOUND_ERROR:
			WriteString(theEnv,STDERR,"IBE_DEFCLASS_NOT_FOUND_ERROR: This error should not happen as a result of an IBMake...\n");
			break;
		case IBE_COULD_NOT_CREATE_ERROR:
			WriteString(theEnv,STDERR,"The Instance could not be created (such as when pattern matching of a fact or instance is already occurring)\n");
			break;
		case IBE_RULE_NETWORK_ERROR:
			WriteString(theEnv,STDERR,"An error occurred while the instance was being processed in the rule network\n");
			break;
		default:
			WriteString(theEnv,STDERR,"The result of IBError was something unexpected...\n");
			break;
	}
}

void XGetWindowAttributesToInstanceFunction(
		Environment *theEnv,
		UDFContext   *context,
		UDFValue     *returnValue)
{
	Display *display;
	Window   window;
	XWindowAttributes wa;
	UDFValue theArg;
	InstanceBuilder *ib;
	MultifieldBuilder *mb;
	const char *name;

	UDFNextArgument(context, EXTERNAL_ADDRESS_BIT, &theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context, INTEGER_BIT, &theArg);
	window = (Window) theArg.integerValue->contents;

	name = NULL;
	if (UDFHasNextArgument(context))
	{
		UDFNextArgument(context,LEXEME_BITS,&theArg);
		name = theArg.lexemeValue->contents;
	}


	if (XGetWindowAttributes(display, window, &wa) != 0)
	{
		ib = CreateInstanceBuilder(theEnv, "X-WINDOW-ATTRIBUTES");
		IBPutSlotInteger(ib, "x", wa.x);
		IBPutSlotInteger(ib, "y", wa.y);
		IBPutSlotInteger(ib, "width", wa.width);
		IBPutSlotInteger(ib, "height", wa.height);
		IBPutSlotInteger(ib, "border-width", wa.border_width);
		IBPutSlotInteger(ib, "depth", wa.depth);
		IBPutSlotExternalAddress(ib, "visual", CreateCExternalAddress(theEnv, wa.visual));
		IBPutSlotInteger(ib, "root", wa.root);
		IBPutSlotInteger(ib, "class", wa.class);
		IBPutSlotInteger(ib, "bit-gravity", wa.bit_gravity);
		IBPutSlotInteger(ib, "win-gravity", wa.win_gravity);
		IBPutSlotInteger(ib, "backing-store", wa.backing_store);
		IBPutSlotInteger(ib, "backing-planes", wa.backing_planes);
		IBPutSlotInteger(ib, "backing-pixel", wa.backing_pixel);
		IBPutSlotSymbol(ib, "save-under", BoolToStr(wa.save_under));
		IBPutSlotInteger(ib, "colormap", wa.colormap);
		IBPutSlotSymbol(ib, "map-installed", BoolToStr(wa.map_installed));
		IBPutSlotSymbol(ib, "map-state", WindowPropertyMapStateToStr(wa.map_state));
		mb = CreateMultifieldBuilder(theEnv, 0);
		IBPutSlotMultifield(ib, "all-event-masks", EventMaskToMultifield(wa.all_event_masks, mb));
		MBDispose(mb);
		mb = CreateMultifieldBuilder(theEnv, 0);
		IBPutSlotMultifield(ib, "your-event-mask", EventMaskToMultifield(wa.your_event_mask, mb));
		MBDispose(mb);
		mb = CreateMultifieldBuilder(theEnv, 0);
		IBPutSlotMultifield(ib, "do-not-propagate-mask", EventMaskToMultifield(wa.do_not_propagate_mask, mb));
		MBDispose(mb);
		IBPutSlotSymbol(ib, "override-redirect", BoolToStr(wa.override_redirect));
		IBPutSlotExternalAddress(ib, "screen", CreateCExternalAddress(theEnv, wa.screen));
		returnValue->instanceValue = IBMake(ib, name);
		IBDispose(ib);
		if (returnValue->instanceValue == NULL)
		{
			WriteString(theEnv,STDERR,"Could not make X-WINDOW-ATTRIBUTES instance\n");
			ReportIBMakeError(theEnv);
		}
	}
}

void ReportFBAssertError(
		Environment *theEnv)
{
	switch(FBError(theEnv))
	{
		case FBE_NO_ERROR:
			WriteString(theEnv,STDERR,"No error occurred\n");
			break;
		case FBE_NULL_POINTER_ERROR:
			WriteString(theEnv,STDERR,"The FactBuilder does not have an associated deftemplate\n");
			break;
		case FBE_DEFTEMPLATE_NOT_FOUND_ERROR:
			WriteString(theEnv,STDERR,"FBE_DEFTEMPLATE_NOT_FOUND_ERROR: This error should not happen as a result of an FBAssert...\n");
			break;
		case FBE_IMPLIED_DEFTEMPLATE_ERROR:
			WriteString(theEnv,STDERR,"FBE_IMPLIED_DEFTEMPLATE_ERROR: This error should not happen as a result of an FBAssert...\n");
			break;
		case FBE_COULD_NOT_ASSERT_ERROR:
			WriteString(theEnv,STDERR,"The Fact could not be asserted (such as when pattern matching of a fact or instance is already occurring)\n");
			break;
		case FBE_RULE_NETWORK_ERROR:
			WriteString(theEnv,STDERR,"An error occurred while the assertion was being processed in the rule network\n");
			break;
		default:
			WriteString(theEnv,STDERR,"The result of FBError was something unexpected...\n");
			break;
	}
}

void XGetWindowAttributesToFactFunction(
		Environment *theEnv,
		UDFContext   *context,
		UDFValue     *returnValue)
{
	Display *display;
	Window   window;
	XWindowAttributes wa;
	UDFValue theArg;
	FactBuilder *fb;
	MultifieldBuilder *mb;

	UDFNextArgument(context, EXTERNAL_ADDRESS_BIT, &theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context, INTEGER_BIT, &theArg);
	window = (Window) theArg.integerValue->contents;

	if (XGetWindowAttributes(display, window, &wa) != 0)
	{
		fb = CreateFactBuilder(theEnv, "x-window-attributes");
		FBPutSlotInteger(fb, "x", wa.x);
		FBPutSlotInteger(fb, "y", wa.y);
		FBPutSlotInteger(fb, "width", wa.width);
		FBPutSlotInteger(fb, "height", wa.height);
		FBPutSlotInteger(fb, "border-width", wa.border_width);
		FBPutSlotInteger(fb, "depth", wa.depth);
		FBPutSlotCLIPSExternalAddress(fb, "visual", CreateCExternalAddress(theEnv, wa.visual));
		FBPutSlotInteger(fb, "root", wa.root);
		FBPutSlotInteger(fb, "class", wa.class);
		FBPutSlotInteger(fb, "bit-gravity", wa.bit_gravity);
		FBPutSlotInteger(fb, "win-gravity", wa.win_gravity);
		FBPutSlotInteger(fb, "backing-store", wa.backing_store);
		FBPutSlotInteger(fb, "backing-planes", wa.backing_planes);
		FBPutSlotInteger(fb, "backing-pixel", wa.backing_pixel);
		FBPutSlotSymbol(fb, "save-under", BoolToStr(wa.save_under));
		FBPutSlotInteger(fb, "colormap", wa.colormap);
		FBPutSlotSymbol(fb, "map-installed", BoolToStr(wa.map_installed));
		FBPutSlotSymbol(fb, "map-state", WindowPropertyMapStateToStr(wa.map_state));
		mb = CreateMultifieldBuilder(theEnv, 0);
		FBPutSlotMultifield(fb, "all-event-masks", EventMaskToMultifield(wa.all_event_masks, mb));
		MBDispose(mb);
		mb = CreateMultifieldBuilder(theEnv, 0);
		FBPutSlotMultifield(fb, "your-event-mask", EventMaskToMultifield(wa.your_event_mask, mb));
		MBDispose(mb);
		mb = CreateMultifieldBuilder(theEnv, 0);
		FBPutSlotMultifield(fb, "do-not-propagate-mask", EventMaskToMultifield(wa.do_not_propagate_mask, mb));
		MBDispose(mb);
		FBPutSlotSymbol(fb, "override-redirect", BoolToStr(wa.override_redirect));
		FBPutSlotCLIPSExternalAddress(fb, "screen", CreateCExternalAddress(theEnv, wa.screen));
		returnValue->factValue = FBAssert(fb);
		FBDispose(fb);
		if (returnValue->factValue == NULL)
		{
			WriteString(theEnv,STDERR,"Could not assert x-window-attributes fact\n");
			ReportFBAssertError(theEnv);
		}
	}
}

void XGetWindowAttributesFunction(
		Environment *theEnv,
		UDFContext   *context,
		UDFValue     *returnValue)
{
	Display *display;
	Window   window;
	XWindowAttributes wa;
	UDFValue theArg;
	MultifieldBuilder *mb;

	UDFNextArgument(context, EXTERNAL_ADDRESS_BIT, &theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context, INTEGER_BIT, &theArg);
	window = (Window) theArg.integerValue->contents;

	if (XGetWindowAttributes(display, window, &wa) != 0)
	{
		mb = CreateMultifieldBuilder(theEnv, 23);
		MBAppendInteger(mb, wa.x);
		MBAppendInteger(mb, wa.y);
		MBAppendInteger(mb, wa.width);
		MBAppendInteger(mb, wa.height);
		MBAppendInteger(mb, wa.border_width);
		MBAppendInteger(mb, wa.depth);
		MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, wa.visual));
		MBAppendInteger(mb, wa.root);
		MBAppendInteger(mb, wa.class);
		MBAppendInteger(mb, wa.bit_gravity);
		MBAppendInteger(mb, wa.win_gravity);
		MBAppendInteger(mb, wa.backing_store);
		MBAppendInteger(mb, wa.backing_planes);
		MBAppendInteger(mb, wa.backing_pixel);
		MBAppendSymbol(mb, BoolToStr(wa.save_under));
		MBAppendInteger(mb, wa.colormap);
		MBAppendSymbol(mb, BoolToStr(wa.map_installed));
		MBAppendSymbol(mb, WindowPropertyMapStateToStr(wa.map_state));
		MBAppendInteger(mb, wa.all_event_masks);
		MBAppendInteger(mb, wa.your_event_mask);
		MBAppendInteger(mb, wa.do_not_propagate_mask);
		MBAppendSymbol(mb, BoolToStr(wa.override_redirect));
		MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, wa.screen));
		returnValue->multifieldValue = MBCreate(mb);
		MBDispose(mb);
	}
}

void EventMaskToMultifieldFunction(
		Environment *theEnv,
		UDFContext   *context,
		UDFValue     *returnValue)
{
	long mask;
	MultifieldBuilder *mb;
	UDFValue theArg;

	UDFNextArgument(context, INTEGER_BIT, &theArg);
	mask = theArg.integerValue->contents;

	mb = CreateMultifieldBuilder(theEnv, 0);

	returnValue->multifieldValue = EventMaskToMultifield(mask, mb);
	MBDispose(mb);
}

void XQueryTreeFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	Window window;
	Window root_ret, parent_ret;
	Window *children;
	unsigned int nchildren;
	MultifieldBuilder *mb;
	UDFValue theArg;

	UDFNextArgument(context, EXTERNAL_ADDRESS_BIT, &theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context, INTEGER_BIT, &theArg);
	window = (Window)theArg.integerValue->contents;

	if (XQueryTree(display, window, &root_ret, &parent_ret, &children, &nchildren) == 0)
	{
		WriteString(theEnv,STDERR,"x-query-tree failed\n");
		return;
	}

	mb = CreateMultifieldBuilder(theEnv, nchildren+2);
	MBAppendInteger(mb, (long long)root_ret);
	MBAppendInteger(mb, (long long)parent_ret);
	for (unsigned int i = 0; i < nchildren; i++)
	{
		MBAppendInteger(mb, (long long)children[i]);
	}
	returnValue->multifieldValue = MBCreate(mb);
	MBDispose(mb);

	XFree(children);
}

void XKillClientFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	unsigned long resource;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	resource = theArg.integerValue->contents;

	returnValue->integerValue = CreateInteger(theEnv, XKillClient(display, (XID)resource));
}

const char *ScreenBackingStoreToStr(int backing_store)
{
	switch(backing_store)
	{
		case NotUseful:
			return "NotUseful";
		case WhenMapped:
			return "WhenMapped";
		case Always:
			return "Always";
		default:
			return "";
	}
}

void ScreenToFactFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Screen *screen;
	FactBuilder *fb;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	screen = theArg.externalAddressValue->contents;

	fb = CreateFactBuilder(theEnv, "screen");
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, screen));
	FBPutSlotCLIPSExternalAddress(fb, "ext-data", CreateCExternalAddress(theEnv, screen->ext_data));
	FBPutSlotCLIPSExternalAddress(fb, "display", CreateCExternalAddress(theEnv, screen->display));
	FBPutSlotInteger(fb, "root", screen->root);
	FBPutSlotInteger(fb, "width", screen->width);
	FBPutSlotInteger(fb, "height", screen->height);
	FBPutSlotInteger(fb, "mwidth", screen->mwidth);
	FBPutSlotInteger(fb, "mheight", screen->mheight);
	FBPutSlotInteger(fb, "ndepths", screen->ndepths);
	FBPutSlotInteger(fb, "root-depth", screen->root_depth);
	FBPutSlotInteger(fb, "white-pixel", screen->white_pixel);
	FBPutSlotInteger(fb, "black-pixel", screen->black_pixel);
	FBPutSlotInteger(fb, "max-maps", screen->max_maps);
	FBPutSlotInteger(fb, "min-maps", screen->min_maps);
	FBPutSlotSymbol(fb, "backing-store", ScreenBackingStoreToStr(screen->backing_store));
	if (screen->save_unders)
	{
		FBPutSlotSymbol(fb, "save-unders", "TRUE");
	}
	else
	{
		FBPutSlotSymbol(fb, "save-unders", "FALSE");
	}
	FBPutSlotInteger(fb, "root-input-mask", screen->root_input_mask);
	returnValue->factValue = FBAssert(fb);
	if (returnValue->factValue == NULL)
	{
		WriteString(theEnv,STDERR,"Could not assert screen fact\n");
		ReportFBAssertError(theEnv);
	}

	FBDispose(fb);
}

void ScreenToInstanceFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Screen *screen;
	InstanceBuilder *ib;
	UDFValue theArg;
	const char *name;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	screen = theArg.externalAddressValue->contents;

	name = NULL;
	if (UDFHasNextArgument(context))
	{
		UDFNextArgument(context,LEXEME_BITS,&theArg);
		name = theArg.lexemeValue->contents;
	}

	ib = CreateInstanceBuilder(theEnv, "SCREEN");
	IBPutSlotExternalAddress(ib, "c-pointer", CreateCExternalAddress(theEnv, screen));
	IBPutSlotExternalAddress(ib, "ext-data", CreateCExternalAddress(theEnv, screen->ext_data));
	IBPutSlotExternalAddress(ib, "display", CreateCExternalAddress(theEnv, screen->display));
	IBPutSlotInteger(ib, "root", screen->root);
	IBPutSlotInteger(ib, "width", screen->width);
	IBPutSlotInteger(ib, "height", screen->height);
	IBPutSlotInteger(ib, "mwidth", screen->mwidth);
	IBPutSlotInteger(ib, "mheight", screen->mheight);
	IBPutSlotInteger(ib, "ndepths", screen->ndepths);
	IBPutSlotInteger(ib, "root-depth", screen->root_depth);
	IBPutSlotInteger(ib, "white-pixel", screen->white_pixel);
	IBPutSlotInteger(ib, "black-pixel", screen->black_pixel);
	IBPutSlotInteger(ib, "max-maps", screen->max_maps);
	IBPutSlotInteger(ib, "min-maps", screen->min_maps);
	IBPutSlotSymbol(ib, "backing-store", ScreenBackingStoreToStr(screen->backing_store));
	if (screen->save_unders)
	{
		IBPutSlotSymbol(ib, "save-unders", "TRUE");
	}
	else
	{
		IBPutSlotSymbol(ib, "save-unders", "FALSE");
	}
	IBPutSlotInteger(ib, "root-input-mask", screen->root_input_mask);
	returnValue->instanceValue = IBMake(ib, name);
	if (returnValue->instanceValue == NULL)
	{
		WriteString(theEnv,STDERR,"Could not make screen instance\n");
		ReportIBMakeError(theEnv);
	}

	IBDispose(ib);
}

void ScreenToMultifieldFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Screen *screen;
	MultifieldBuilder *mb = CreateMultifieldBuilder(theEnv, 0);
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	screen = theArg.externalAddressValue->contents;

	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, screen));
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, screen->ext_data));
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, screen->display));
	MBAppendInteger(mb, screen->root);
	MBAppendInteger(mb, screen->width);
	MBAppendInteger(mb, screen->height);
	MBAppendInteger(mb, screen->mwidth);
	MBAppendInteger(mb, screen->mheight);
	MBAppendInteger(mb, screen->ndepths);
	MBAppendInteger(mb, screen->root_depth);
	MBAppendInteger(mb, screen->white_pixel);
	MBAppendInteger(mb, screen->black_pixel);
	MBAppendInteger(mb, screen->max_maps);
	MBAppendInteger(mb, screen->min_maps);
	MBAppendSymbol(mb, ScreenBackingStoreToStr(screen->backing_store));
	if (screen->save_unders)
	{
		MBAppendSymbol(mb, "TRUE");
	}
	else
	{
		MBAppendSymbol(mb, "FALSE");
	}
	MBAppendInteger(mb, screen->root_input_mask);
	returnValue->multifieldValue = MBCreate(mb);
}

void RemoveHintsFlagsFromWindowFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	Window window;
	XSizeHints *hints = XAllocSizeHints();
	long supplied;
	long flags = 0;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	window = theArg.integerValue->contents;

	while (UDFHasNextArgument(context))
	{
		UDFNextArgument(context,SYMBOL_BIT,&theArg);
		if (0 == strcmp(theArg.lexemeValue->contents, "USPosition"))
		{
			flags |= USPosition;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "USSize"))
		{
			flags |= USSize;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "PPosition"))
		{
			flags |= PPosition;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "PSize"))
		{
			flags |= PSize;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "PMinSize"))
		{
			flags |= PMinSize;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "PMaxSize"))
		{
			flags |= PMaxSize;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "PResizeInc"))
		{
			flags |= PResizeInc;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "PAspect"))
		{
			flags |= PAspect;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "PBaseSize"))
		{
			flags |= PBaseSize;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "PWinGravity"))
		{
			flags |= PWinGravity;
		}
	}

	if (XGetWMNormalHints(display, window, hints, &supplied)) {
		hints->flags &= ~flags;
		XSetWMNormalHints(display, window, hints);
	}

	XFree(hints);
}

void SetWindowGravityFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	Window window;
	XSizeHints *hints = XAllocSizeHints();
	long supplied;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	window = theArg.integerValue->contents;

	UDFNextArgument(context,SYMBOL_BIT,&theArg);

	if (XGetWMNormalHints(display, window, hints, &supplied)) {

		if (0 == strcmp(theArg.lexemeValue->contents, "ForgetGravity"))
		{
			hints->win_gravity = ForgetGravity;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "NorthWestGravity"))
		{
			hints->win_gravity = NorthWestGravity;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "NorthGravity"))
		{
			hints->win_gravity = NorthGravity;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "NorthEastGravity"))
		{
			hints->win_gravity = NorthEastGravity;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "WestGravity"))
		{
			hints->win_gravity = WestGravity;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "CenterGravity"))
		{
			hints->win_gravity = CenterGravity;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "EastGravity"))
		{
			hints->win_gravity = EastGravity;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "SouthWestGravity"))
		{
			hints->win_gravity = SouthWestGravity;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "SouthGravity"))
		{
			hints->win_gravity = SouthGravity;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "SouthEastGravity"))
		{
			hints->win_gravity = SouthEastGravity;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "StaticGravity"))
		{
			hints->win_gravity = StaticGravity;
		}

		hints->flags |= PWinGravity;
		XSetWMNormalHints(display, window, hints);
	}

	XFree(hints);
}

void XListPropertiesFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Atom *props;
	int n;
	Display *display;
	unsigned long window;
	MultifieldBuilder *mb;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	window = theArg.integerValue->contents;

	if ((props = XListProperties(display, window, &n)))
	{
		mb = CreateMultifieldBuilder(theEnv, 0);
		for (int i = 0; i < n; i++)
		{
			char *name = XGetAtomName(display, props[i]);
			MBAppendSymbol(mb, name);
			XFree(name);
		}
		XFree(props);

		returnValue->multifieldValue = MBCreate(mb);
		MBDispose(mb);
	}
	else
	{
		WriteString(theEnv,STDERR,"Could not list properties of window\n");
	}
}

void XGetPropertyFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue) {

	Atom actual_type, prop, utf8;
	int actual_format, status;
	Display *display;
	unsigned long nitems, bytes_after, window;
	unsigned char *data = NULL;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	window = theArg.integerValue->contents;

	UDFNextArgument(context,LEXEME_BITS,&theArg);

	prop = XInternAtom(display, theArg.lexemeValue->contents, False);
	if (prop == None) {
		WriteString(theEnv,STDERR,"Could not intern atom ");
		WriteString(theEnv,STDERR,theArg.lexemeValue->contents);
		WriteString(theEnv,STDERR,"\n");
		return;
	}

	status = XGetWindowProperty(display, window, prop,
			0, (~0L),
			False,
			AnyPropertyType,
			&actual_type,
			&actual_format,
			&nitems,
			&bytes_after,
			&data);
	if (status != Success || (data == NULL && nitems == 0)) {
		// no property or failure: empty multifield
		if (data) XFree(data);
		WriteString(theEnv,STDERR,"Could not get window property ");
		WriteString(theEnv,STDERR,theArg.lexemeValue->contents);
		WriteString(theEnv,STDERR,"\n");
		return;
	}

	MultifieldBuilder *mb = CreateMultifieldBuilder(theEnv, nitems);

	char *actual_type_str = XGetAtomName(display, actual_type);
	MBAppendSymbol(mb, actual_type_str);
	XFree(actual_type_str);

	MBAppendInteger(mb, actual_format);

	utf8 = XInternAtom(display, "UTF8_STRING", False);
	if (actual_format == 8 && (actual_type == utf8 || actual_type == XA_STRING)) {
		size_t len = (size_t)nitems;
		char *buf = alloca(len + 1);
		for (size_t i = 0; i < len; ++i) {
			buf[i] = ((char *)data)[i];
		}
		buf[len] = '\0';

		MBAppendString(mb, buf);

		returnValue->multifieldValue = MBCreate(mb);
		MBDispose(mb);
		XFree(data);
		return;
	}

	// 32-bit decoding
	if (actual_format == 32) {
		unsigned long *arr = (unsigned long *)data;

		if (actual_type == XA_ATOM) {
			for (unsigned long i = 0; i < nitems; ++i) {
				Atom a = (Atom)(arr[i] & 0xFFFFFFFFUL);
				char *name = XGetAtomName(display, a);
				if (name) {
					MBAppendSymbol(mb, name);
					XFree(name);
				} else {
					MBAppendSymbol(mb, "<unknown>");
				}
			}
			returnValue->multifieldValue = MBCreate(mb);
			MBDispose(mb);
			XFree(data);
			return;
		}

		if (actual_type == XA_WINDOW || actual_type == XA_CARDINAL || actual_type == XA_INTEGER) {
			for (unsigned long i = 0; i < nitems; ++i) {
				MBAppendInteger(mb, (long long)arr[i]);
			}
			returnValue->multifieldValue = MBCreate(mb);
			MBDispose(mb);
			XFree(data);
			return;
		}

		// fallback: treat as generic 32-bit ints
		for (unsigned long i = 0; i < nitems; ++i) {
			MBAppendInteger(mb, (long long)arr[i]);
		}
		returnValue->multifieldValue = MBCreate(mb);
		MBDispose(mb);
		XFree(data);
		return;
	}

	// 16-bit: return each as integer
	if (actual_format == 16) {
		unsigned short *arr16 = (unsigned short *)data;
		for (unsigned long i = 0; i < nitems; ++i) {
			MBAppendInteger(mb, (long long)arr16[i]);
		}
		returnValue->multifieldValue = MBCreate(mb);
		MBDispose(mb);
		XFree(data);
		return;
	}

	// 8-bit fallback: raw bytes as integers
	if (actual_format == 8) {
		unsigned char *arr8 = (unsigned char *)data;
		for (unsigned long i = 0; i < nitems; ++i) {
			MBAppendInteger(mb, (long long)arr8[i]);
		}
		returnValue->multifieldValue = MBCreate(mb);
		MBDispose(mb);
		XFree(data);
		return;
	}

	// Unknown format: empty
	if (data) XFree(data);
	WriteString(theEnv,STDERR,"Got window property ");
	WriteString(theEnv,STDERR,theArg.lexemeValue->contents);
	WriteString(theEnv,STDERR,", but it was an unknown format: empty\n");
}

void XChangePropertyFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue) {

	Display *display;
	Window window;
	Atom prop, type;
	int format;
	int mode = PropModeReplace;
	unsigned long nelements = 0;
	unsigned char *raw_bytes = NULL;
	UDFValue theArg;

	union {
		unsigned long u32;
		unsigned short u16;
		unsigned char u8;
	} single;

	/* display */
	UDFNextArgument(context, EXTERNAL_ADDRESS_BIT, &theArg);
	display = theArg.externalAddressValue->contents;

	/* window */
	UDFNextArgument(context, INTEGER_BIT, &theArg);
	window = theArg.integerValue->contents;

	/* property name */
	UDFNextArgument(context, LEXEME_BITS, &theArg);
	prop = XInternAtom(display, theArg.lexemeValue->contents, False);
	if (prop == None) {
		WriteString(theEnv, STDERR, "Could not intern atom (property) ");
		WriteString(theEnv, STDERR, theArg.lexemeValue->contents);
		WriteString(theEnv, STDERR, "\n");
		return;
	}

	/* type name */
	UDFNextArgument(context, LEXEME_BITS, &theArg);
	type = XInternAtom(display, theArg.lexemeValue->contents, False);
	if (type == None) {
		WriteString(theEnv, STDERR, "Could not intern atom (type) ");
		WriteString(theEnv, STDERR, theArg.lexemeValue->contents);
		WriteString(theEnv, STDERR, "\n");
		return;
	}

	/* format */
	UDFNextArgument(context, INTEGER_BIT, &theArg);
	format = (int)theArg.integerValue->contents;

	/* mode */
	UDFNextArgument(context, SYMBOL_BIT, &theArg);
	if (0 == strcmp(theArg.lexemeValue->contents, "Replace")) {
		mode = PropModeReplace;
	} else if (0 == strcmp(theArg.lexemeValue->contents, "Append")) {
		mode = PropModeAppend;
	} else if (0 == strcmp(theArg.lexemeValue->contents, "Prepend")) {
		mode = PropModePrepend;
	} else {
		mode = PropModeReplace;
	}

	/* data: could be string or multifield or integers */
	if (!UDFHasNextArgument(context)) {
		nelements = 0;
		raw_bytes = NULL;
	} else {
		UDFNextArgument(context, MULTIFIELD_BIT | SYMBOL_BIT | STRING_BIT | INTEGER_BIT, &theArg);
		if (theArg.header->type == MULTIFIELD_TYPE) {
			size_t count = theArg.multifieldValue->length;
			if (format == 32) {
				unsigned long *arr32 = (unsigned long *)alloca(sizeof(unsigned long) * count);
				for (size_t i = 0; i < count; ++i) {
					if (theArg.multifieldValue->contents[i].header->type == INTEGER_TYPE) {
						arr32[i] = (unsigned long)theArg.multifieldValue->contents[i].integerValue->contents;
					} else {
						arr32[i] = 0;
					}
				}
				nelements = count;
				raw_bytes = (unsigned char *)arr32;
			} else if (format == 16) {
				unsigned short *arr16 = (unsigned short *)alloca(sizeof(unsigned short) * count);
				for (size_t i = 0; i < count; ++i) {
					if (theArg.multifieldValue->contents[i].header->type == INTEGER_TYPE) {
						arr16[i] = (unsigned short)theArg.multifieldValue->contents[i].integerValue->contents;
					} else {
						arr16[i] = 0;
					}
				}
				nelements = count;
				raw_bytes = (unsigned char *)arr16;
			} else if (format == 8) {
				unsigned char *b = (unsigned char *)alloca(count);
				for (size_t i = 0; i < count; ++i) {
					if (theArg.multifieldValue->contents[i].header->type == INTEGER_TYPE) {
						b[i] = (unsigned char)theArg.multifieldValue->contents[i].integerValue->contents;
					} else {
						b[i] = 0;
					}
				}
				nelements = count;
				raw_bytes = b;
			} else {
				nelements = 0;
				raw_bytes = NULL;
			}
		} else if (theArg.header->type == STRING_TYPE || theArg.header->type == SYMBOL_TYPE) {
			const char *s = theArg.lexemeValue->contents;
			size_t len = strlen(s);
			if (format != 8) {
				format = 8;
			}
			nelements = len;
			raw_bytes = (unsigned char *)s;
		} else if (theArg.header->type == INTEGER_TYPE) {
			if (format == 32) {
				single.u32 = (unsigned long)theArg.integerValue->contents;
				raw_bytes = (unsigned char *)&single.u32;
				nelements = 1;
			} else if (format == 16) {
				single.u16 = (unsigned short)theArg.integerValue->contents;
				raw_bytes = (unsigned char *)&single.u16;
				nelements = 1;
			} else if (format == 8) {
				single.u8 = (unsigned char)theArg.integerValue->contents;
				raw_bytes = (unsigned char *)&single.u8;
				nelements = 1;
			} else {
				nelements = 0;
				raw_bytes = NULL;
			}
		} else {
			nelements = 0;
			raw_bytes = NULL;
		}
	}

	XChangeProperty(display,
			window,
			prop,
			type,
			format,
			mode,
			raw_bytes,
			nelements);
}

void XDeletePropertyFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue) {

	Display *display;
	Window window;
	Atom prop;
	UDFValue theArg;

	UDFNextArgument(context, EXTERNAL_ADDRESS_BIT, &theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context, INTEGER_BIT, &theArg);
	window = theArg.integerValue->contents;

	UDFNextArgument(context, LEXEME_BITS, &theArg);
	prop = XInternAtom(display, theArg.lexemeValue->contents, False);
	if (prop == None) {
		WriteString(theEnv, STDERR, "Could not intern atom (property) ");
		WriteString(theEnv, STDERR, theArg.lexemeValue->contents);
		WriteString(theEnv, STDERR, "\n");
		return;
	}

	XDeleteProperty(display, window, prop);
}

void XGetGeometryFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	unsigned long window, root;
	int x, y;
	unsigned int width, height, border_width, depth;
	MultifieldBuilder *mb;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	window = theArg.integerValue->contents;

	if (XGetGeometry(display, window, &root, &x, &y, &width, &height, &border_width, &depth) == 0) {
		WriteString(theEnv, STDERR, "x-get-geometry failed for window ");
		WriteInteger(theEnv, STDERR, window);
		WriteString(theEnv, STDERR, "\n");
		return;
	}
	mb = CreateMultifieldBuilder(theEnv, 7);
	MBAppendInteger(mb, root);
	MBAppendInteger(mb, x);
	MBAppendInteger(mb, y);
	MBAppendInteger(mb, width);
	MBAppendInteger(mb, height);
	MBAppendInteger(mb, border_width);
	MBAppendInteger(mb, depth);
	returnValue->multifieldValue = MBCreate(mb);
	MBDispose(mb);
}

void XFetchNameFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	Window window;
	char *name = NULL;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	window = (Window) theArg.integerValue->contents;

	if (XFetchName(display, window, &name) && (name != NULL))
	{
		returnValue->lexemeValue = CreateString(theEnv, name);
		XFree(name);
	}
	else
	{
		WriteString(theEnv, STDERR, "x-fetch-name failed for window ");
		WriteInteger(theEnv, STDERR, window);
		WriteString(theEnv, STDERR, "\n");
	}
}

void XStoreNameFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	Window window;
	const char *name;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	window = (Window) theArg.integerValue->contents;

	UDFNextArgument(context,LEXEME_BITS,&theArg);
	name = theArg.lexemeValue->contents;

	XStoreName(display, window, name);
}

const char *RevertToToStr(int revert_to)
{
	switch(revert_to)
	{
		case RevertToParent:
			return "RevertToParent";
		case RevertToPointerRoot:
			return "RevertToPointerRoot";
		case RevertToNone:
			return "RevertToNone";
		default:
			return "Unknown";
	}
}

void XGetInputFocusFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	Window focus;
	int revert_to, status;
	MultifieldBuilder *mb;
	UDFValue theArg;

	UDFNextArgument(context, EXTERNAL_ADDRESS_BIT, &theArg);
	display = theArg.externalAddressValue->contents;

	status = XGetInputFocus(display, &focus, &revert_to);
	if (status == 0)  /* According to Xlib, non-zero is success */
	{
		WriteString(theEnv, STDERR, "XGetInputFocus failed: could not retrieve focus information.\n");
		returnValue->lexemeValue = FalseSymbol(theEnv);
		return;
	}

	mb = CreateMultifieldBuilder(theEnv, 0);
	MBAppendInteger(mb, focus);
	MBAppendSymbol(mb, RevertToToStr(revert_to));
	returnValue->multifieldValue = MBCreate(mb);
	MBDispose(mb);
}

void XWarpPointerFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	Window src_w, dest_w;
	int src_x, src_y;
	unsigned int src_width, src_height;
	int dest_x, dest_y;
	UDFValue theArg;

	UDFNextArgument(context, EXTERNAL_ADDRESS_BIT, &theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context, INTEGER_BIT, &theArg);
	src_w = (Window) theArg.integerValue->contents;

	UDFNextArgument(context, INTEGER_BIT, &theArg);
	dest_w = (Window) theArg.integerValue->contents;

	UDFNextArgument(context, INTEGER_BIT, &theArg);
	src_x = theArg.integerValue->contents;

	UDFNextArgument(context, INTEGER_BIT, &theArg);
	src_y = theArg.integerValue->contents;

	UDFNextArgument(context, INTEGER_BIT, &theArg);
	src_width = theArg.integerValue->contents;

	UDFNextArgument(context, INTEGER_BIT, &theArg);
	src_height = theArg.integerValue->contents;

	UDFNextArgument(context, INTEGER_BIT, &theArg);
	dest_x = theArg.integerValue->contents;

	UDFNextArgument(context, INTEGER_BIT, &theArg);
	dest_y = theArg.integerValue->contents;

	XWarpPointer(display, src_w, dest_w, src_x, src_y, src_width, src_height, dest_x, dest_y);
}

void XQueryPointerFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	Window root, child;
	int root_x, root_y, win_x, win_y;
	unsigned int mask;
	UDFValue theArg;
	MultifieldBuilder *mb;

	UDFNextArgument(context, EXTERNAL_ADDRESS_BIT, &theArg);
	display = theArg.externalAddressValue->contents;

	root = DefaultRootWindow(display);

	if (!XQueryPointer(display, root, &root, &child, &root_x, &root_y, &win_x, &win_y, &mask))
	{
		WriteString(theEnv, STDERR, "x-query-pointer failed\n");
		returnValue->lexemeValue = FalseSymbol(theEnv);
		return;
	}

	mb = CreateMultifieldBuilder(theEnv, 2);
	MBAppendInteger(mb, root_x);
	MBAppendInteger(mb, root_y);
	returnValue->multifieldValue = MBCreate(mb);
	MBDispose(mb);
}

void BlackPixelFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	int screen;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	screen = theArg.integerValue->contents;

	returnValue->integerValue = CreateInteger(theEnv, (int)BlackPixel(display, screen));
}

void WhitePixelFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	int screen;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	screen = theArg.integerValue->contents;

	returnValue->integerValue = CreateInteger(theEnv, (int)WhitePixel(display, screen));
}

void XDefineCursorFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	Window window;
	Cursor cursor;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	window = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	cursor = theArg.integerValue->contents;

	XDefineCursor(display, window, cursor);
}

void XCreateGCFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	Drawable drawable;
	unsigned long valuemask;
	// we just discard this
	XGCValues values;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	drawable = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	valuemask = theArg.integerValue->contents;

	returnValue->externalAddressValue = CreateCExternalAddress(theEnv, XCreateGC(display, drawable, valuemask, &values));
}

void XSetForegroundFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	GC gc;
	unsigned long foreground;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	gc = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	foreground = theArg.integerValue->contents;

	returnValue->integerValue = CreateInteger(theEnv, XSetForeground(display, gc, foreground));
}

void XLoadQueryFontFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	const char *name;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,LEXEME_BITS,&theArg);
	name = theArg.lexemeValue->contents;

	returnValue->externalAddressValue = CreateCExternalAddress(theEnv, XLoadQueryFont(display, name));
}

void XSetFontFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	GC gc;
	XFontStruct *font_info;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	gc = theArg.externalAddressValue->contents;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	font_info = theArg.externalAddressValue->contents;

	returnValue->integerValue = CreateInteger(theEnv, XSetFont(display, gc, font_info->fid));
}

void XPendingFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	returnValue->integerValue = CreateInteger(theEnv, XPending(display));
}

const char *XEventTypeToStr(int type)
{
	switch (type)
	{
		case KeyPress:
			return "KeyPress";
		case KeyRelease:
			return "KeyRelease";
		case ButtonPress:
			return "ButtonPress";
		case ButtonRelease:
			return "ButtonRelease";
		case MotionNotify:
			return "MotionNotify";
		case EnterNotify:
			return "EnterNotify";
		case LeaveNotify:
			return "LeaveNotify";
		case FocusIn:
			return "FocusIn";
		case FocusOut:
			return "FocusOut";
		case KeymapNotify:
			return "KeymapNotify";
		case Expose:
			return "Expose";
		case GraphicsExpose:
			return "GraphicsExpose";
		case NoExpose:
			return "NoExpose";
		case VisibilityNotify:
			return "VisibilityNotify";
		case CreateNotify:
			return "CreateNotify";
		case DestroyNotify:
			return "DestroyNotify";
		case UnmapNotify:
			return "UnmapNotify";
		case MapNotify:
			return "MapNotify";
		case MapRequest:
			return "MapRequest";
		case ReparentNotify:
			return "ReparentNotify";
		case ConfigureNotify:
			return "ConfigureNotify";
		case ConfigureRequest:
			return "ConfigureRequest";
		case GravityNotify:
			return "GravityNotify";
		case ResizeRequest:
			return "ResizeRequest";
		case CirculateNotify:
			return "CirculateNotify";
		case CirculateRequest:
			return "CirculateRequest";
		case PropertyNotify:
			return "PropertyNotify";
		case SelectionClear:
			return "SelectionClear";
		case SelectionRequest:
			return "SelectionRequest";
		case SelectionNotify:
			return "SelectionNotify";
		case ColormapNotify:
			return "ColormapNotify";
		case ClientMessage:
			return "ClientMessage";
		case MappingNotify:
			return "MappingNotify";
		case GenericEvent:
			return "GenericEvent";
		default:
			return NULL;
	}
}

Multifield *XAnyEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XAnyEvent *e,
		MultifieldBuilder *mb)
{
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e));
	MBAppendSymbol(mb, XEventTypeToStr(e->type));
	MBAppendInteger(mb, e->serial);
	MBAppendSymbol(mb, BoolToStr(e->send_event));
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e->display));
	MBAppendInteger(mb, e->window);
	return MBCreate(mb);
}

int StringToEventMask(
		const char *str)
{
	if (0 == strcmp(str, "KeyPressMask"))
	{
		return KeyPressMask;
	}
	else if (0 == strcmp(str, "KeyReleaseMask"))
	{
		return KeyReleaseMask;
	}
	else if (0 == strcmp(str, "ButtonPressMask"))
	{
		return ButtonPressMask;
	}
	else if (0 == strcmp(str, "ButtonReleaseMask"))
	{
		return ButtonReleaseMask;
	}
	else if (0 == strcmp(str, "EnterWindowMask"))
	{
		return EnterWindowMask;
	}
	else if (0 == strcmp(str, "LeaveWindowMask"))
	{
		return LeaveWindowMask;
	}
	else if (0 == strcmp(str, "PointerMotionMask"))
	{
		return PointerMotionMask;
	}
	else if (0 == strcmp(str, "PointerMotionHintMask"))
	{
		return PointerMotionHintMask;
	}
	else if (0 == strcmp(str, "Button1MotionMask"))
	{
		return Button1MotionMask;
	}
	else if (0 == strcmp(str, "Button2MotionMask"))
	{
		return Button2MotionMask;
	}
	else if (0 == strcmp(str, "Button3MotionMask"))
	{
		return Button3MotionMask;
	}
	else if (0 == strcmp(str, "Button4MotionMask"))
	{
		return Button4MotionMask;
	}
	else if (0 == strcmp(str, "Button5MotionMask"))
	{
		return Button5MotionMask;
	}
	else if (0 == strcmp(str, "ButtonMotionMask"))
	{
		return ButtonMotionMask;
	}
	else if (0 == strcmp(str, "KeymapStateMask"))
	{
		return KeymapStateMask;
	}
	else if (0 == strcmp(str, "ExposureMask"))
	{
		return ExposureMask;
	}
	else if (0 == strcmp(str, "VisibilityChangeMask"))
	{
		return VisibilityChangeMask;
	}
	else if (0 == strcmp(str, "StructureNotifyMask"))
	{
		return StructureNotifyMask;
	}
	else if (0 == strcmp(str, "ResizeRedirectMask"))
	{
		return ResizeRedirectMask;
	}
	else if (0 == strcmp(str, "SubstructureNotifyMask"))
	{
		return SubstructureNotifyMask;
	}
	else if (0 == strcmp(str, "SubstructureRedirectMask"))
	{
		return SubstructureRedirectMask;
	}
	else if (0 == strcmp(str, "FocusChangeMask"))
	{
		return FocusChangeMask;
	}
	else if (0 == strcmp(str, "PropertyChangeMask"))
	{
		return PropertyChangeMask;
	}
	else if (0 == strcmp(str, "ColormapChangeMask"))
	{
		return ColormapChangeMask;
	}
	else if (0 == strcmp(str, "OwnerGrabButtonMask"))
	{
		return OwnerGrabButtonMask;
	}
	else if (0 == strcmp(str, "NoEventMask"))
	{
		return NoEventMask;
	}
	else
	{
		return -1;
	}
}

void LexemeToEventMaskFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	UDFValue theArg;

	UDFNextArgument(context,LEXEME_BITS,&theArg);
	
	returnValue->integerValue = CreateInteger(theEnv, StringToEventMask(theArg.lexemeValue->contents));
}

int MultifieldToEventMask(
		Multifield *mf)
{
	int event_mask = 0;
	int to_add;
	for (int x = 0; x < mf->length; x++)
	{
		to_add = StringToEventMask(mf->contents[x].lexemeValue->contents);
		if (to_add != -1)
		{
			event_mask |= to_add;
		}
	}
	return event_mask;
}

void MultifieldToEventMaskFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	UDFValue theArg;

	UDFNextArgument(context,MULTIFIELD_BIT,&theArg);
	
	returnValue->integerValue = CreateInteger(theEnv, MultifieldToEventMask(theArg.multifieldValue));
}

int StringToMask(
		const char *str)
{
	if (0 == strcmp(str, "ShiftMask"))
	{
		return ShiftMask;
	}
	else
	if (0 == strcmp(str, "LockMask"))
	{
		return LockMask;
	}
	else
	if (0 == strcmp(str, "ControlMask"))
	{
		return ControlMask;
	}
	else
	if (0 == strcmp(str, "Mod1Mask"))
	{
		return Mod1Mask;
	}
	else
	if (0 == strcmp(str, "Mod2Mask"))
	{
		return Mod2Mask;
	}
	else
	if (0 == strcmp(str, "Mod3Mask"))
	{
		return Mod3Mask;
	}
	else
	if (0 == strcmp(str, "Mod4Mask"))
	{
		return Mod4Mask;
	}
	else
	if (0 == strcmp(str, "Mod5Mask"))
	{
		return Mod5Mask;
	}
	else
	if (0 == strcmp(str, "Button1Mask"))
	{
		return Button1Mask;
	}
	else
	if (0 == strcmp(str, "Button2Mask"))
	{
		return Button2Mask;
	}
	else
	if (0 == strcmp(str, "Button3Mask"))
	{
		return Button3Mask;
	}
	else
	if (0 == strcmp(str, "Button4Mask"))
	{
		return Button4Mask;
	}
	else
	if (0 == strcmp(str, "Button5Mask"))
	{
		return Button5Mask;
	}
	else
	if (0 == strcmp(str, "AnyModifier"))
	{
		return AnyModifier;
	}
	else
	{
		return -1;
	}
}

void LexemeToMaskFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	UDFValue theArg;

	UDFNextArgument(context,LEXEME_BITS,&theArg);
	
	returnValue->integerValue = CreateInteger(theEnv, StringToMask(theArg.lexemeValue->contents));
}

int MultifieldToMask(
		Multifield *mf)
{
	int event_mask = 0;
	int to_add;
	for (int x = 0; x < mf->length; x++)
	{
		to_add = StringToMask(mf->contents[x].lexemeValue->contents);
		if (to_add != -1)
		{
			event_mask |= to_add;
		}
	}
	return event_mask;
}

void MultifieldToMaskFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	UDFValue theArg;

	UDFNextArgument(context,MULTIFIELD_BIT,&theArg);
	
	returnValue->integerValue = CreateInteger(theEnv, MultifieldToMask(theArg.multifieldValue));
}

const char *MaskToString(
		unsigned int mask)
{
	switch (mask)
	{
		case Button1Mask:
			return "Button1Mask";
		case Button2Mask:
			return "Button2Mask";
		case Button3Mask:
			return "Button3Mask";
		case Button4Mask:
			return "Button4Mask";
		case Button5Mask:
			return "Button5Mask";
		case ShiftMask:
			return "ShiftMask";
		case LockMask:
			return "LockMask";
		case ControlMask:
			return "ControlMask";
		case Mod1Mask:
			return "Mod1Mask";
		case Mod2Mask:
			return "Mod2Mask";
		case Mod3Mask:
			return "Mod3Mask";
		case Mod4Mask:
			return "Mod4Mask";
		case Mod5Mask:
			return "Mod5Mask";
		default:
			return NULL;
	}
}

void MaskToSymbolFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	const char *sym;
	UDFValue theArg;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	
	sym = MaskToString(theArg.integerValue->contents);

	if (sym != NULL)
	{
		returnValue->lexemeValue = CreateSymbol(theEnv, sym);
	}
	else
	{
		WriteInteger(theEnv,STDERR,theArg.integerValue->contents);
		WriteString(theEnv,STDERR," is not a valid mask\n");
		returnValue->voidValue = VoidConstant(theEnv);
	}
}

Multifield *MaskToMultifield(
		unsigned int mask,
		MultifieldBuilder *mb)
{
	if (mask & Button1Mask) {
		MBAppendSymbol(mb, "Button1Mask");
	}
	if (mask & Button2Mask) {
		MBAppendSymbol(mb, "Button2Mask");
	}
	if (mask & Button3Mask) {
		MBAppendSymbol(mb, "Button3Mask");
	}
	if (mask & Button4Mask) {
		MBAppendSymbol(mb, "Button4Mask");
	}
	if (mask & Button5Mask) {
		MBAppendSymbol(mb, "Button5Mask");
	}
	if (mask & ShiftMask) {
		MBAppendSymbol(mb, "ShiftMask");
	}
	if (mask & LockMask) {
		MBAppendSymbol(mb, "LockMask");
	}
	if (mask & ControlMask) {
		MBAppendSymbol(mb, "ControlMask");
	}
	if (mask & Mod1Mask) {
		MBAppendSymbol(mb, "Mod1Mask");
	}
	if (mask & Mod2Mask) {
		MBAppendSymbol(mb, "Mod2Mask");
	}
	if (mask & Mod3Mask) {
		MBAppendSymbol(mb, "Mod3Mask");
	}
	if (mask & Mod4Mask) {
		MBAppendSymbol(mb, "Mod4Mask");
	}
	if (mask & Mod5Mask) {
		MBAppendSymbol(mb, "Mod5Mask");
	}
	return MBCreate(mb);
}

void MaskToMultifieldFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	MultifieldBuilder *mb = CreateMultifieldBuilder(theEnv, 0);
	UDFValue theArg;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	MaskToMultifield(theArg.integerValue->contents, mb);
	returnValue->multifieldValue = MBCreate(mb);
	MBDispose(mb);
}

Multifield *XKeyEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XKeyEvent *e,
		MultifieldBuilder *mb)
{
	MultifieldBuilder *statemb;
	Multifield *statemf;

	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e));
	MBAppendSymbol(mb, XEventTypeToStr(e->type));
	MBAppendInteger(mb, e->serial);
	MBAppendSymbol(mb, BoolToStr(e->send_event));
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e->display));
	MBAppendInteger(mb, e->window);
	MBAppendInteger(mb, e->root);
	MBAppendInteger(mb, e->subwindow);
	MBAppendInteger(mb, e->time);
	MBAppendInteger(mb, e->x);
	MBAppendInteger(mb, e->y);
	MBAppendInteger(mb, e->x_root);
	MBAppendInteger(mb, e->y_root);
	statemb = CreateMultifieldBuilder(theEnv, 0);
	statemf = MaskToMultifield(e->state, statemb);
	MBDispose(statemb);
	if (statemf == NULL)
	{
		WriteString(theEnv,STDERR,"Could not create multifield for x-key-event's state");
		return NULL;
	}
	MBAppendMultifield(mb, statemf);
	MBAppendInteger(mb, e->keycode);
	MBAppendSymbol(mb, BoolToStr(e->same_screen));
	return MBCreate(mb);
}

Multifield *XButtonEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XButtonEvent *e,
		MultifieldBuilder *mb)
{
	MultifieldBuilder *statemb;
	Multifield *statemf;

	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e));
	MBAppendSymbol(mb, XEventTypeToStr(e->type));
	MBAppendInteger(mb, e->serial);
	MBAppendSymbol(mb, BoolToStr(e->send_event));
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e->display));
	MBAppendInteger(mb, e->window);
	MBAppendInteger(mb, e->root);
	MBAppendInteger(mb, e->subwindow);
	MBAppendInteger(mb, e->time);
	MBAppendInteger(mb, e->x);
	MBAppendInteger(mb, e->y);
	MBAppendInteger(mb, e->x_root);
	MBAppendInteger(mb, e->y_root);
	statemb = CreateMultifieldBuilder(theEnv, 0);
	statemf = MaskToMultifield(e->state, statemb);
	MBDispose(statemb);
	if (statemf == NULL)
	{
		WriteString(theEnv,STDERR,"Could not create multifield for x-button-event's state");
		return NULL;
	}
	MBAppendMultifield(mb, statemf);
	MBAppendInteger(mb, e->button);
	MBAppendSymbol(mb, BoolToStr(e->same_screen));
	return MBCreate(mb);
}

Multifield *XMotionEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XMotionEvent *e,
		MultifieldBuilder *mb)
{
	MultifieldBuilder *statemb;
	Multifield *statemf;

	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e));
	MBAppendSymbol(mb, XEventTypeToStr(e->type));
	MBAppendInteger(mb, e->serial);
	MBAppendSymbol(mb, BoolToStr(e->send_event));
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e->display));
	MBAppendInteger(mb, e->window);
	MBAppendInteger(mb, e->root);
	MBAppendInteger(mb, e->subwindow);
	MBAppendInteger(mb, e->time);
	MBAppendInteger(mb, e->x);
	MBAppendInteger(mb, e->y);
	MBAppendInteger(mb, e->x_root);
	MBAppendInteger(mb, e->y_root);
	statemb = CreateMultifieldBuilder(theEnv, 0);
	statemf = MaskToMultifield(e->state, statemb);
	MBDispose(statemb);
	if (statemf == NULL)
	{
		WriteString(theEnv,STDERR,"Could not create multifield for x-motion-event's state");
		return NULL;
	}
	MBAppendMultifield(mb, statemf);
	switch(e->is_hint)
	{
		case NotifyNormal:
			MBAppendSymbol(mb, "NotifyNormal");
			break;
		case NotifyHint:
			MBAppendSymbol(mb, "NotifyHint");
			break;
		default:
			WriteString(theEnv,STDERR,"Notify hint type ");
			WriteInteger(theEnv,STDERR,e->is_hint);
			WriteString(theEnv,STDERR," not supported.\n");
			return NULL;
	}
	MBAppendSymbol(mb, BoolToStr(e->same_screen));
	return MBCreate(mb);
}

const char *EventModeToStr(int mode)
{
	switch(mode)
	{
		case NotifyNormal:
			return "NotifyNormal";
		case NotifyGrab:
			return "NotifyGrab";
		case NotifyUngrab:
			return "NotifyUngrab";
		default:
			return NULL;
	}
}

const char *EventDetailToStr(int detail)
{
	switch(detail)
	{
		case NotifyAncestor:
			return "NotifyAncestor";
		case NotifyVirtual:
			return "NotifyVirtual";
		case NotifyInferior:
			return "NotifyInferior";
		case NotifyNonlinear:
			return "NotifyNonlinear";
		case NotifyNonlinearVirtual:
			return "NotifyNonlinearVirtual";
		case NotifyPointer:
			return "NotifyPointer";
		case NotifyPointerRoot:
			return "NotifyPointerRoot";
		case NotifyDetailNone:
			return "NotifyDetailNone";
		default:
			return NULL;
	}
}


Multifield *XCrossingEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XCrossingEvent *e,
		MultifieldBuilder *mb)
{
	MultifieldBuilder *statemb;
	Multifield *statemf;

	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e));
	MBAppendSymbol(mb, XEventTypeToStr(e->type));
	MBAppendInteger(mb, e->serial);
	MBAppendSymbol(mb, BoolToStr(e->send_event));
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e->display));
	MBAppendInteger(mb, e->window);
	MBAppendInteger(mb, e->root);
	MBAppendInteger(mb, e->subwindow);
	MBAppendInteger(mb, e->time);
	MBAppendInteger(mb, e->x);
	MBAppendInteger(mb, e->y);
	MBAppendInteger(mb, e->x_root);
	MBAppendInteger(mb, e->y_root);
	MBAppendSymbol(mb, EventModeToStr(e->mode));
	MBAppendSymbol(mb, EventDetailToStr(e->detail));
	MBAppendSymbol(mb, BoolToStr(e->same_screen));
	MBAppendSymbol(mb, BoolToStr(e->focus));
	statemb = CreateMultifieldBuilder(theEnv, 0);
	statemf = MaskToMultifield(e->state, statemb);
	MBDispose(statemb);
	if (statemf == NULL)
	{
		WriteString(theEnv,STDERR,"Could not create multifield for x-crossing-event's state");
		return NULL;
	}
	MBAppendMultifield(mb, statemf);

	return MBCreate(mb);
}

Multifield *XFocusChangeEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XFocusChangeEvent *e,
		MultifieldBuilder *mb)
{
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e));
	MBAppendSymbol(mb, XEventTypeToStr(e->type));
	MBAppendInteger(mb, e->serial);
	MBAppendSymbol(mb, BoolToStr(e->send_event));
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e->display));
	MBAppendInteger(mb, e->window);
	MBAppendSymbol(mb, EventModeToStr(e->mode));
	MBAppendSymbol(mb, EventDetailToStr(e->detail));

	return MBCreate(mb);
}

Multifield *XKeymapEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		Display *display,
		XKeymapEvent *e,
		MultifieldBuilder *mb)
{
	int min_keycode, max_keycode;
	MultifieldBuilder *keyvectormb, *keydownmb;

	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e));
	MBAppendSymbol(mb, XEventTypeToStr(e->type));
	MBAppendInteger(mb, e->serial);
	MBAppendSymbol(mb, BoolToStr(e->send_event));
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e->display));
	MBAppendInteger(mb, e->window);

	XDisplayKeycodes(display, &min_keycode, &max_keycode);

	keyvectormb = CreateMultifieldBuilder(theEnv, 0);
	keydownmb = CreateMultifieldBuilder(theEnv, 0);
	for (int kc = min_keycode; kc <= max_keycode; kc++)
	{
		if (e->key_vector[kc >> 3] & (1 << (kc & 7)))
		{
			MBAppendSymbol(keyvectormb, "TRUE");
			MBAppendInteger(keydownmb, kc);
		}
		else
		{
			MBAppendSymbol(keyvectormb, "FALSE");
		}
	}
	MBAppendMultifield(mb, MBCreate(keyvectormb));
	MBDispose(keyvectormb);
	MBAppendMultifield(mb, MBCreate(keydownmb));
	MBDispose(keydownmb);

	return MBCreate(mb);
}

Multifield *XExposeEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XExposeEvent *e,
		MultifieldBuilder *mb)
{
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e));
	MBAppendSymbol(mb, XEventTypeToStr(e->type));
	MBAppendInteger(mb, e->serial);
	MBAppendSymbol(mb, BoolToStr(e->send_event));
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e->display));
	MBAppendInteger(mb, e->window);
	MBAppendInteger(mb, e->x);
	MBAppendInteger(mb, e->y);
	MBAppendInteger(mb, e->width);
	MBAppendInteger(mb, e->height);
	MBAppendInteger(mb, e->count);
	return MBCreate(mb);
}

Multifield *XGraphicsExposeEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XGraphicsExposeEvent *e,
		MultifieldBuilder *mb)
{
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e));
	MBAppendSymbol(mb, XEventTypeToStr(e->type));
	MBAppendInteger(mb, e->serial);
	MBAppendSymbol(mb, BoolToStr(e->send_event));
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e->display));
	MBAppendInteger(mb, e->drawable);
	MBAppendInteger(mb, e->x);
	MBAppendInteger(mb, e->y);
	MBAppendInteger(mb, e->width);
	MBAppendInteger(mb, e->height);
	MBAppendInteger(mb, e->count);
	MBAppendInteger(mb, e->major_code);
	MBAppendInteger(mb, e->minor_code);
	return MBCreate(mb);
}

Multifield *XNoExposeEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XNoExposeEvent *e,
		MultifieldBuilder *mb)
{
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e));
	MBAppendSymbol(mb, XEventTypeToStr(e->type));
	MBAppendInteger(mb, e->serial);
	MBAppendSymbol(mb, BoolToStr(e->send_event));
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e->display));
	MBAppendInteger(mb, e->drawable);
	MBAppendInteger(mb, e->major_code);
	MBAppendInteger(mb, e->minor_code);
	return MBCreate(mb);
}

const char *VisibilityStateToStr(int state)
{
	switch(state)
	{
		case VisibilityUnobscured:
			return "VisibilityUnobscured";
		case VisibilityPartiallyObscured:
			return "VisibilityPartiallyObscured";
		case VisibilityFullyObscured:
			return "VisibilityFullyObscured";
		default:
			return NULL;
	}
}

Multifield *XVisibilityEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XVisibilityEvent *e,
		MultifieldBuilder *mb)
{
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e));
	MBAppendSymbol(mb, XEventTypeToStr(e->type));
	MBAppendInteger(mb, e->serial);
	MBAppendSymbol(mb, BoolToStr(e->send_event));
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e->display));
	MBAppendInteger(mb, e->window);
	MBAppendSymbol(mb, VisibilityStateToStr(e->state));

	return MBCreate(mb);
}

Multifield *XCreateWindowEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XCreateWindowEvent *e,
		MultifieldBuilder *mb)
{
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e));
	MBAppendSymbol(mb, XEventTypeToStr(e->type));
	MBAppendInteger(mb, e->serial);
	MBAppendSymbol(mb, BoolToStr(e->send_event));
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e->display));
	MBAppendInteger(mb, e->parent);
	MBAppendInteger(mb, e->window);
	MBAppendInteger(mb, e->x);
	MBAppendInteger(mb, e->y);
	MBAppendInteger(mb, e->width);
	MBAppendInteger(mb, e->height);
	MBAppendInteger(mb, e->border_width);
	MBAppendSymbol(mb, BoolToStr(e->override_redirect));

	return MBCreate(mb);
}

Multifield *XDestroyWindowEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XDestroyWindowEvent *e,
		MultifieldBuilder *mb)
{
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e));
	MBAppendSymbol(mb, XEventTypeToStr(e->type));
	MBAppendInteger(mb, e->serial);
	MBAppendSymbol(mb, BoolToStr(e->send_event));
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e->display));
	MBAppendInteger(mb, e->event);
	MBAppendInteger(mb, e->window);
	return MBCreate(mb);
}

Multifield *XUnmapEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XUnmapEvent *e,
		MultifieldBuilder *mb)
{

	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e));
	MBAppendSymbol(mb, XEventTypeToStr(e->type));
	MBAppendInteger(mb, e->serial);
	MBAppendSymbol(mb, BoolToStr(e->send_event));
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e->display));
	MBAppendInteger(mb, e->event);
	MBAppendInteger(mb, e->window);
	MBAppendSymbol(mb, BoolToStr(e->from_configure));
	return MBCreate(mb);
}

Multifield *XMapEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XMapEvent *e,
		MultifieldBuilder *mb)
{
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e));
	MBAppendSymbol(mb, XEventTypeToStr(e->type));
	MBAppendInteger(mb, e->serial);
	MBAppendSymbol(mb, BoolToStr(e->send_event));
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e->display));
	MBAppendInteger(mb, e->event);
	MBAppendInteger(mb, e->window);
	MBAppendSymbol(mb, BoolToStr(e->override_redirect));
	return MBCreate(mb);
}

Multifield *XMapRequestEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XMapRequestEvent *e,
		MultifieldBuilder *mb)
{
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e));
	MBAppendSymbol(mb, XEventTypeToStr(e->type));
	MBAppendInteger(mb, e->serial);
	MBAppendSymbol(mb, BoolToStr(e->send_event));
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e->display));
	MBAppendInteger(mb, e->parent);
	MBAppendInteger(mb, e->window);
	return MBCreate(mb);
}

Multifield *XReparentEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XReparentEvent *e,
		MultifieldBuilder *mb)
{
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e));
	MBAppendSymbol(mb, XEventTypeToStr(e->type));
	MBAppendInteger(mb, e->serial);
	MBAppendSymbol(mb, BoolToStr(e->send_event));
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e->display));
	MBAppendInteger(mb, e->event);
	MBAppendInteger(mb, e->window);
	MBAppendInteger(mb, e->parent);
	MBAppendInteger(mb, e->x);
	MBAppendInteger(mb, e->y);
	MBAppendSymbol(mb, BoolToStr(e->override_redirect));
	return MBCreate(mb);
}

Multifield *XConfigureEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XConfigureEvent *e,
		MultifieldBuilder *mb)
{
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e));
	MBAppendSymbol(mb, XEventTypeToStr(e->type));
	MBAppendInteger(mb, e->serial);
	MBAppendSymbol(mb, BoolToStr(e->send_event));
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e->display));
	MBAppendInteger(mb, e->event);
	MBAppendInteger(mb, e->window);
	MBAppendInteger(mb, e->x);
	MBAppendInteger(mb, e->y);
	MBAppendInteger(mb, e->width);
	MBAppendInteger(mb, e->height);
	MBAppendInteger(mb, e->border_width);
	MBAppendInteger(mb, e->above);
	MBAppendSymbol(mb, BoolToStr(e->override_redirect));
	return MBCreate(mb);
}

const char *ConfigureRequestEventDetailToStr(int mode)
{
	switch(mode)
	{
		case Above:
			return "Above";
		case Below:
			return "Below";
		case TopIf:
			return "TopIf";
		case BottomIf:
			return "BottomIf";
		case Opposite:
			return "Opposite";
		default:
			return NULL;
	}
}

Multifield *XConfigureRequestEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XConfigureRequestEvent *e,
		MultifieldBuilder *mb)
{
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e));
	MBAppendSymbol(mb, XEventTypeToStr(e->type));
	MBAppendInteger(mb, e->serial);
	MBAppendSymbol(mb, BoolToStr(e->send_event));
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e->display));
	MBAppendInteger(mb, e->parent);
	MBAppendInteger(mb, e->window);
	MBAppendInteger(mb, e->x);
	MBAppendInteger(mb, e->y);
	MBAppendInteger(mb, e->width);
	MBAppendInteger(mb, e->height);
	MBAppendInteger(mb, e->border_width);
	MBAppendInteger(mb, e->above);
	MBAppendSymbol(mb, ConfigureRequestEventDetailToStr(e->above));
	MBAppendInteger(mb, e->value_mask);
	return MBCreate(mb);
}

Multifield *XGravityEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XGravityEvent *e,
		MultifieldBuilder *mb)
{
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e));
	MBAppendSymbol(mb, XEventTypeToStr(e->type));
	MBAppendInteger(mb, e->serial);
	MBAppendSymbol(mb, BoolToStr(e->send_event));
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e->display));
	MBAppendInteger(mb, e->event);
	MBAppendInteger(mb, e->window);
	MBAppendInteger(mb, e->x);
	MBAppendInteger(mb, e->y);
	return MBCreate(mb);
}

Multifield *XResizeRequestEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XResizeRequestEvent *e,
		MultifieldBuilder *mb)
{
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e));
	MBAppendSymbol(mb, XEventTypeToStr(e->type));
	MBAppendInteger(mb, e->serial);
	MBAppendSymbol(mb, BoolToStr(e->send_event));
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e->display));
	MBAppendInteger(mb, e->window);
	MBAppendInteger(mb, e->width);
	MBAppendInteger(mb, e->height);
	return MBCreate(mb);
}

const char *CirculateEventPlaceToStr(int place)
{
	switch(place)
	{
		case PlaceOnTop:
			return "PlaceOnTop";
		case PlaceOnBottom:
			return "PlaceOnBottom";
		default:
			return NULL;
	}
}

Multifield *XCirculateEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XCirculateEvent *e,
		MultifieldBuilder *mb)
{
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e));
	MBAppendSymbol(mb, XEventTypeToStr(e->type));
	MBAppendInteger(mb, e->serial);
	MBAppendSymbol(mb, BoolToStr(e->send_event));
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e->display));
	MBAppendInteger(mb, e->event);
	MBAppendInteger(mb, e->window);
	MBAppendSymbol(mb, CirculateEventPlaceToStr(e->place));
	return MBCreate(mb);
}

Multifield *XCirculateRequestEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XCirculateRequestEvent *e,
		MultifieldBuilder *mb)
{
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e));
	MBAppendSymbol(mb, XEventTypeToStr(e->type));
	MBAppendInteger(mb, e->serial);
	MBAppendSymbol(mb, BoolToStr(e->send_event));
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e->display));
	MBAppendInteger(mb, e->parent);
	MBAppendInteger(mb, e->window);
	MBAppendSymbol(mb, CirculateEventPlaceToStr(e->place));
	return MBCreate(mb);
}

const char *PropertyEventStateToStr(int state)
{
	switch(state)
	{
		case PropertyNewValue:
			return "PropertyNewValue";
		case PropertyDelete:
			return "PropertyDelete";
		default:
			return NULL;
	}
}

Multifield *XPropertyEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XPropertyEvent *e,
		MultifieldBuilder *mb)
{
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e));
	MBAppendSymbol(mb, XEventTypeToStr(e->type));
	MBAppendInteger(mb, e->serial);
	MBAppendSymbol(mb, BoolToStr(e->send_event));
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e->display));
	MBAppendInteger(mb, e->window);
	MBAppendInteger(mb, e->atom);
	MBAppendInteger(mb, e->time);
	MBAppendSymbol(mb, PropertyEventStateToStr(e->state));
	return MBCreate(mb);
}

Multifield *XSelectionClearEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XSelectionClearEvent *e,
		MultifieldBuilder *mb)
{
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e));
	MBAppendSymbol(mb, XEventTypeToStr(e->type));
	MBAppendInteger(mb, e->serial);
	MBAppendSymbol(mb, BoolToStr(e->send_event));
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e->display));
	MBAppendInteger(mb, e->window);
	MBAppendInteger(mb, e->selection);
	MBAppendInteger(mb, e->time);
	return MBCreate(mb);
}

Multifield *XSelectionRequestEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XSelectionRequestEvent *e,
		MultifieldBuilder *mb)
{
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e));
	MBAppendSymbol(mb, XEventTypeToStr(e->type));
	MBAppendInteger(mb, e->serial);
	MBAppendSymbol(mb, BoolToStr(e->send_event));
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e->display));
	MBAppendInteger(mb, e->owner);
	MBAppendInteger(mb, e->requestor);
	MBAppendInteger(mb, e->selection);
	MBAppendInteger(mb, e->target);
	MBAppendInteger(mb, e->property);
	MBAppendInteger(mb, e->time);
	return MBCreate(mb);
}

Multifield *XSelectionEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XSelectionEvent *e,
		MultifieldBuilder *mb)
{
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e));
	MBAppendSymbol(mb, XEventTypeToStr(e->type));
	MBAppendInteger(mb, e->serial);
	MBAppendSymbol(mb, BoolToStr(e->send_event));
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e->display));
	MBAppendInteger(mb, e->requestor);
	MBAppendInteger(mb, e->selection);
	MBAppendInteger(mb, e->target);
	MBAppendInteger(mb, e->property);
	MBAppendInteger(mb, e->time);
	return MBCreate(mb);
}

const char *ColormapEventStateToStr(int state)
{
	switch(state)
	{
		case ColormapInstalled:
			return "ColormapInstalled";
		case ColormapUninstalled:
			return "ColormapUninstalled";
		default:
			return NULL;
	}
}

Multifield *XColormapEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XColormapEvent *e,
		MultifieldBuilder *mb)
{
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e));
	MBAppendSymbol(mb, XEventTypeToStr(e->type));
	MBAppendInteger(mb, e->serial);
	MBAppendSymbol(mb, BoolToStr(e->send_event));
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e->display));
	MBAppendInteger(mb, e->window);
	if (e->colormap == None)
	{
		MBAppendSymbol(mb, "None");
	}
	else
	{
		MBAppendInteger(mb, e->colormap);
	}
	MBAppendSymbol(mb, BoolToStr(e->new));
	MBAppendSymbol(mb, ColormapEventStateToStr(e->state));
	return MBCreate(mb);
}

Multifield *XClientMessageEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XClientMessageEvent *e,
		MultifieldBuilder *mb)
{
	MultifieldBuilder *innermb;

	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e));
	MBAppendSymbol(mb, XEventTypeToStr(e->type));
	MBAppendInteger(mb, e->serial);
	MBAppendSymbol(mb, BoolToStr(e->send_event));
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e->display));
	MBAppendInteger(mb, e->window);
	MBAppendInteger(mb, e->message_type);
	MBAppendInteger(mb, e->format);
	innermb = CreateMultifieldBuilder(theEnv, 0);
	if (e->format == 8)
	{
		for (int x = 0; x < 20; x++)
		{
			MBAppendInteger(innermb, e->data.b[x]);
		}
	}
	else if (e->format == 16)
	{
		for (int x = 0; x < 10; x++)
		{
			MBAppendInteger(innermb, e->data.s[x]);
		}
	}
	else if (e->format == 32)
	{
		for (int x = 0; x < 5; x++)
		{
			MBAppendInteger(innermb, e->data.l[x]);
		}
	}
	MBAppendMultifield(mb, MBCreate(innermb));
	MBDispose(innermb);
	return MBCreate(mb);
}

Multifield *XMappingEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XMappingEvent *e,
		MultifieldBuilder *mb)
{
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e));
	MBAppendSymbol(mb, XEventTypeToStr(e->type));
	MBAppendInteger(mb, e->serial);
	MBAppendSymbol(mb, BoolToStr(e->send_event));
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e->display));
	MBAppendInteger(mb, e->window);
	MBAppendInteger(mb, e->request);
	MBAppendInteger(mb, e->first_keycode);
	MBAppendInteger(mb, e->count);
	return MBCreate(mb);
}

Multifield *XGenericEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XGenericEvent *e,
		MultifieldBuilder *mb)
{
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e));
	MBAppendSymbol(mb, XEventTypeToStr(e->type));
	MBAppendInteger(mb, e->serial);
	MBAppendSymbol(mb, BoolToStr(e->send_event));
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e->display));
	MBAppendInteger(mb, e->extension);
	MBAppendInteger(mb, e->evtype);
	return MBCreate(mb);
}

Multifield *XEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XEvent *e,
		MultifieldBuilder *mb)
{

	Multifield *typedevent = NULL;
	MultifieldBuilder *typedeventmb = CreateMultifieldBuilder(theEnv, 0);

	switch (e->type)
	{
		case KeyPress:
			typedevent = XKeyEventToMultifield(theEnv, context, &(e->xkey), typedeventmb);
			break;
		case KeyRelease:
			typedevent = XKeyEventToMultifield(theEnv, context, &(e->xkey), typedeventmb);
			MBAppendMultifield(mb, typedevent);
			break;
		case ButtonPress:
			typedevent = XButtonEventToMultifield(theEnv, context, &(e->xbutton), typedeventmb);
			break;
		case ButtonRelease:
			typedevent = XButtonEventToMultifield(theEnv, context, &(e->xbutton), typedeventmb);
			break;
		case MotionNotify:
			typedevent = XMotionEventToMultifield(theEnv, context, &(e->xmotion), typedeventmb);
			break;
		case EnterNotify:
			typedevent = XCrossingEventToMultifield(theEnv, context, &(e->xcrossing), typedeventmb);
			break;
		case LeaveNotify:
			typedevent = XCrossingEventToMultifield(theEnv, context, &(e->xcrossing), typedeventmb);
			break;
		case FocusIn:
			typedevent = XFocusChangeEventToMultifield(theEnv, context, &(e->xfocus), typedeventmb);
			break;
		case FocusOut:
			typedevent = XFocusChangeEventToMultifield(theEnv, context, &(e->xfocus), typedeventmb);
			break;
		case KeymapNotify:
			typedevent = XKeymapEventToMultifield(theEnv, context, e->xany.display, &e->xkeymap, typedeventmb);
			break;
		case Expose:
			typedevent = XExposeEventToMultifield(theEnv, context, &(e->xexpose), typedeventmb);
			break;
		case GraphicsExpose:
			typedevent = XGraphicsExposeEventToMultifield(theEnv, context, &(e->xgraphicsexpose), typedeventmb);
			break;
		case NoExpose:
			typedevent = XNoExposeEventToMultifield(theEnv, context, &(e->xnoexpose), typedeventmb);
			break;
		case VisibilityNotify:
			typedevent = XVisibilityEventToMultifield(theEnv, context, &(e->xvisibility), typedeventmb);
			break;
		case CreateNotify:
			typedevent = XCreateWindowEventToMultifield(theEnv, context, &(e->xcreatewindow), typedeventmb);
			break;
		case DestroyNotify:
			typedevent = XDestroyWindowEventToMultifield(theEnv, context, &(e->xdestroywindow), typedeventmb);
			break;
		case UnmapNotify:
			typedevent = XUnmapEventToMultifield(theEnv, context, &(e->xunmap), typedeventmb);
			break;
		case MapNotify:
			typedevent = XMapEventToMultifield(theEnv, context, &(e->xmap), typedeventmb);
			break;
		case MapRequest:
			typedevent = XMapRequestEventToMultifield(theEnv, context, &(e->xmaprequest), typedeventmb);
			break;
		case ReparentNotify:
			typedevent = XReparentEventToMultifield(theEnv, context, &(e->xreparent), typedeventmb);
			break;
		case ConfigureNotify:
			typedevent = XConfigureEventToMultifield(theEnv, context, &(e->xconfigure), typedeventmb);
			break;
		case ConfigureRequest:
			typedevent = XConfigureRequestEventToMultifield(theEnv, context, &(e->xconfigurerequest), typedeventmb);
			break;
		case GravityNotify:
			typedevent = XGravityEventToMultifield(theEnv, context, &(e->xgravity), typedeventmb);
			break;
		case ResizeRequest:
			typedevent = XResizeRequestEventToMultifield(theEnv, context, &(e->xresizerequest), typedeventmb);
			break;
		case CirculateNotify:
			typedevent = XCirculateEventToMultifield(theEnv, context, &(e->xcirculate), typedeventmb);
			break;
		case CirculateRequest:
			typedevent = XCirculateRequestEventToMultifield(theEnv, context, &(e->xcirculaterequest), typedeventmb);
			break;
		case PropertyNotify:
			typedevent = XPropertyEventToMultifield(theEnv, context, &(e->xproperty), typedeventmb);
			break;
		case SelectionClear:
			typedevent = XSelectionClearEventToMultifield(theEnv, context, &(e->xselectionclear), typedeventmb);
			break;
		case SelectionRequest:
			typedevent = XSelectionRequestEventToMultifield(theEnv, context, &(e->xselectionrequest), typedeventmb);
			break;
		case SelectionNotify:
			typedevent = XSelectionEventToMultifield(theEnv, context, &(e->xselection), typedeventmb);
			break;
		case ColormapNotify:
			typedevent = XColormapEventToMultifield(theEnv, context, &(e->xcolormap), typedeventmb);
			break;
		case ClientMessage:
			typedevent = XClientMessageEventToMultifield(theEnv, context, &(e->xclient), typedeventmb);
			break;
		case MappingNotify:
			typedevent = XMappingEventToMultifield(theEnv, context, &(e->xmapping), typedeventmb);
			break;
		case GenericEvent:
			typedevent = XGenericEventToMultifield(theEnv, context, &(e->xgeneric), typedeventmb);
			break;
		default:
			WriteString(theEnv,STDERR,"Event Type ");
			WriteInteger(theEnv,STDERR,e->type);
			WriteString(theEnv,STDERR," not supported.\n");
			break;
	}
	MBDispose(typedeventmb);
	if (typedevent == NULL)
	{
		WriteString(theEnv,STDERR,"Could not create multifield for XEvent ");
		WriteString(theEnv,STDERR,XEventTypeToStr(e->type));
		WriteString(theEnv,STDERR,"\n");
		return NULL;
	}
	MBAppendMultifield(mb, typedevent);
	return MBCreate(mb);
}

Fact *XAnyEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XAnyEvent *e,
		FactBuilder *fb)
{
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotInteger(fb, "serial", e->serial);
	if (e->send_event)
	{
		FBPutSlotSymbol(fb, "send-event", "TRUE");
	}
	else
	{
		FBPutSlotSymbol(fb, "send-event", "FALSE");
	}
	FBPutSlotCLIPSExternalAddress(fb, "display", CreateCExternalAddress(theEnv, e->display));
	FBPutSlotInteger(fb, "window", e->window);
	return FBAssert(fb);
}

Fact *XKeyEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XKeyEvent *e,
		FactBuilder *fb)
{
	MultifieldBuilder *mb;
	Multifield *mf;

	FBSetDeftemplate(fb, "x-key-event");
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotSymbol(fb, "type", XEventTypeToStr(e->type));
	FBPutSlotInteger(fb, "serial", e->serial);
	FBPutSlotSymbol(fb, "send-event", BoolToStr(e->send_event));
	FBPutSlotCLIPSExternalAddress(fb, "display", CreateCExternalAddress(theEnv, e->display));
	FBPutSlotInteger(fb, "window", e->window);
	FBPutSlotInteger(fb, "root", e->root);
	FBPutSlotInteger(fb, "subwindow", e->subwindow);
	FBPutSlotInteger(fb, "time", e->time);
	FBPutSlotInteger(fb, "x", e->x);
	FBPutSlotInteger(fb, "y", e->y);
	FBPutSlotInteger(fb, "x-root", e->x_root);
	FBPutSlotInteger(fb, "y-root", e->y_root);
	mb = CreateMultifieldBuilder(theEnv, 0);
	mf = MaskToMultifield(e->state, mb);
	MBDispose(mb);
	if (mf == NULL)
	{
		WriteString(theEnv,STDERR,"Could not create multifield for x-key-event's state");
		return NULL;
	}
	FBPutSlotMultifield(fb, "state", mf);
	FBPutSlotInteger(fb, "keycode", e->keycode);
	FBPutSlotSymbol(fb, "same-screen", BoolToStr(e->same_screen));

	return FBAssert(fb);
}

Fact *XButtonEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XButtonEvent *e,
		FactBuilder *fb)
{
	MultifieldBuilder *mb;
	Multifield *mf;

	FBSetDeftemplate(fb, "x-button-event");
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotSymbol(fb, "type", XEventTypeToStr(e->type));
	FBPutSlotInteger(fb, "serial", e->serial);
	FBPutSlotSymbol(fb, "send-event", BoolToStr(e->send_event));
	FBPutSlotCLIPSExternalAddress(fb, "display", CreateCExternalAddress(theEnv, e->display));
	FBPutSlotInteger(fb, "window", e->window);
	FBPutSlotInteger(fb, "root", e->root);
	FBPutSlotInteger(fb, "subwindow", e->subwindow);
	FBPutSlotInteger(fb, "time", e->time);
	FBPutSlotInteger(fb, "x", e->x);
	FBPutSlotInteger(fb, "y", e->y);
	FBPutSlotInteger(fb, "x-root", e->x_root);
	FBPutSlotInteger(fb, "y-root", e->y_root);
	mb = CreateMultifieldBuilder(theEnv, 0);
	mf = MaskToMultifield(e->state, mb);
	MBDispose(mb);
	if (mf == NULL)
	{
		WriteString(theEnv,STDERR,"Could not create multifield for x-button-event's state");
		return NULL;
	}
	FBPutSlotMultifield(fb, "state", mf);
	FBPutSlotInteger(fb, "button", e->button);
	FBPutSlotSymbol(fb, "same-screen", BoolToStr(e->same_screen));

	return FBAssert(fb);
}

Fact *XMotionEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XMotionEvent *e,
		FactBuilder *fb)
{
	MultifieldBuilder *mb;
	Multifield *mf;

	FBSetDeftemplate(fb, "x-motion-event");
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotSymbol(fb, "type", XEventTypeToStr(e->type));
	FBPutSlotInteger(fb, "serial", e->serial);
	FBPutSlotSymbol(fb, "send-event", BoolToStr(e->send_event));
	FBPutSlotCLIPSExternalAddress(fb, "display", CreateCExternalAddress(theEnv, e->display));
	FBPutSlotInteger(fb, "window", e->window);
	FBPutSlotInteger(fb, "root", e->root);
	FBPutSlotInteger(fb, "subwindow", e->subwindow);
	FBPutSlotInteger(fb, "time", e->time);
	FBPutSlotInteger(fb, "x", e->x);
	FBPutSlotInteger(fb, "y", e->y);
	FBPutSlotInteger(fb, "x-root", e->x_root);
	FBPutSlotInteger(fb, "y-root", e->y_root);
	mb = CreateMultifieldBuilder(theEnv, 0);
	mf = MaskToMultifield(e->state, mb);
	MBDispose(mb);
	if (mf == NULL)
	{
		WriteString(theEnv,STDERR,"Could not create multifield for x-motion-event's state");
		return NULL;
	}
	FBPutSlotMultifield(fb, "state", mf);
	switch(e->is_hint)
	{
		case NotifyNormal:
			FBPutSlotSymbol(fb, "is-hint", "NotifyNormal");
			break;
		case NotifyHint:
			FBPutSlotSymbol(fb, "is-hint", "NotifyHint");
			break;
		default:
			WriteString(theEnv,STDERR,"Notify hint type ");
			WriteInteger(theEnv,STDERR,e->is_hint);
			WriteString(theEnv,STDERR," not supported.\n");
			return NULL;
	}
	FBPutSlotSymbol(fb, "same-screen", BoolToStr(e->same_screen));

	return FBAssert(fb);
}
Fact *XCrossingEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XCrossingEvent *e,
		FactBuilder *fb)
{
	MultifieldBuilder *mb;
	Multifield *mf;

	FBSetDeftemplate(fb, "x-crossing-event");
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotSymbol(fb, "type", XEventTypeToStr(e->type));
	FBPutSlotInteger(fb, "serial", e->serial);
	FBPutSlotSymbol(fb, "send-event", BoolToStr(e->send_event));
	FBPutSlotCLIPSExternalAddress(fb, "display", CreateCExternalAddress(theEnv, e->display));
	FBPutSlotInteger(fb, "window", e->window);
	FBPutSlotInteger(fb, "root", e->root);
	FBPutSlotInteger(fb, "subwindow", e->subwindow);
	FBPutSlotInteger(fb, "time", e->time);
	FBPutSlotInteger(fb, "x", e->x);
	FBPutSlotInteger(fb, "y", e->y);
	FBPutSlotInteger(fb, "x-root", e->x_root);
	FBPutSlotInteger(fb, "y-root", e->y_root);
	FBPutSlotSymbol(fb, "mode", EventModeToStr(e->mode));
	FBPutSlotSymbol(fb, "detail", EventDetailToStr(e->detail));
	FBPutSlotSymbol(fb, "same-screen", BoolToStr(e->same_screen));
	FBPutSlotSymbol(fb, "focus", BoolToStr(e->focus));
	mb = CreateMultifieldBuilder(theEnv, 0);
	mf = MaskToMultifield(e->state, mb);
	MBDispose(mb);
	if (mf == NULL)
	{
		WriteString(theEnv,STDERR,"Could not create multifield for x-crossing-event's state");
		return NULL;
	}
	FBPutSlotMultifield(fb, "state", mf);

	return FBAssert(fb);
}

Fact *XFocusChangeEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XFocusChangeEvent *e,
		FactBuilder *fb)
{
	FBSetDeftemplate(fb, "x-focus-change-event");
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotSymbol(fb, "type", XEventTypeToStr(e->type));
	FBPutSlotInteger(fb, "serial", e->serial);
	FBPutSlotSymbol(fb, "send-event", BoolToStr(e->send_event));
	FBPutSlotCLIPSExternalAddress(fb, "display", CreateCExternalAddress(theEnv, e->display));
	FBPutSlotInteger(fb, "window", e->window);
	FBPutSlotSymbol(fb, "mode", EventModeToStr(e->mode));
	FBPutSlotSymbol(fb, "detail", EventDetailToStr(e->detail));

	return FBAssert(fb);
}

Fact *XKeymapEventToFact(
		Environment *theEnv,
		UDFContext *context,
		Display *display,
		XKeymapEvent *e,
		FactBuilder *fb)
{
	int min_keycode, max_keycode;
	MultifieldBuilder *keyvectormb, *keydownmb;

	FBSetDeftemplate(fb, "x-keymap-event");
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotSymbol(fb, "type", XEventTypeToStr(e->type));
	FBPutSlotInteger(fb, "serial", e->serial);
	FBPutSlotSymbol(fb, "send-event", BoolToStr(e->send_event));
	FBPutSlotCLIPSExternalAddress(fb, "display", CreateCExternalAddress(theEnv, e->display));
	FBPutSlotInteger(fb, "window", e->window);

	XDisplayKeycodes(display, &min_keycode, &max_keycode);

	keyvectormb = CreateMultifieldBuilder(theEnv, 0);
	keydownmb = CreateMultifieldBuilder(theEnv, 0);
	for (int kc = min_keycode; kc <= max_keycode; kc++)
	{
		if (e->key_vector[kc >> 3] & (1 << (kc & 7)))
		{
			MBAppendSymbol(keyvectormb, "TRUE");
			MBAppendInteger(keydownmb, kc);
		}
		else
		{
			MBAppendSymbol(keyvectormb, "FALSE");
		}
	}
	FBPutSlotMultifield(fb, "keyvector", MBCreate(keyvectormb));
	MBDispose(keyvectormb);
	FBPutSlotMultifield(fb, "keydown", MBCreate(keydownmb));
	MBDispose(keydownmb);

	return FBAssert(fb);
}

Fact *XExposeEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XExposeEvent *e,
		FactBuilder *fb)
{
	FBSetDeftemplate(fb, "x-expose-event");
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotSymbol(fb, "type", XEventTypeToStr(e->type));
	FBPutSlotInteger(fb, "serial", e->serial);
	FBPutSlotSymbol(fb, "send-event", BoolToStr(e->send_event));
	FBPutSlotCLIPSExternalAddress(fb, "display", CreateCExternalAddress(theEnv, e->display));
	FBPutSlotInteger(fb, "window", e->window);
	FBPutSlotInteger(fb, "x", e->x);
	FBPutSlotInteger(fb, "y", e->y);
	FBPutSlotInteger(fb, "width", e->width);
	FBPutSlotInteger(fb, "height", e->height);
	FBPutSlotInteger(fb, "count", e->count);

	return FBAssert(fb);
}

Fact *XGraphicsExposeEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XGraphicsExposeEvent *e,
		FactBuilder *fb)
{
	FBSetDeftemplate(fb, "x-graphics-expose-event");
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotSymbol(fb, "type", XEventTypeToStr(e->type));
	FBPutSlotInteger(fb, "serial", e->serial);
	FBPutSlotSymbol(fb, "send-event", BoolToStr(e->send_event));
	FBPutSlotCLIPSExternalAddress(fb, "display", CreateCExternalAddress(theEnv, e->display));
	FBPutSlotInteger(fb, "drawable", e->drawable);
	FBPutSlotInteger(fb, "x", e->x);
	FBPutSlotInteger(fb, "y", e->y);
	FBPutSlotInteger(fb, "width", e->width);
	FBPutSlotInteger(fb, "height", e->height);
	FBPutSlotInteger(fb, "count", e->count);
	FBPutSlotInteger(fb, "major-code", e->major_code);
	FBPutSlotInteger(fb, "minor-code", e->minor_code);

	return FBAssert(fb);
}

Fact *XNoExposeEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XNoExposeEvent *e,
		FactBuilder *fb)
{
	FBSetDeftemplate(fb, "x-no-expose-event");
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotSymbol(fb, "type", XEventTypeToStr(e->type));
	FBPutSlotInteger(fb, "serial", e->serial);
	FBPutSlotSymbol(fb, "send-event", BoolToStr(e->send_event));
	FBPutSlotCLIPSExternalAddress(fb, "display", CreateCExternalAddress(theEnv, e->display));
	FBPutSlotInteger(fb, "drawable", e->drawable);
	FBPutSlotInteger(fb, "major-code", e->major_code);
	FBPutSlotInteger(fb, "minor-code", e->minor_code);

	return FBAssert(fb);
}

Fact *XVisibilityEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XVisibilityEvent *e,
		FactBuilder *fb)
{
	FBSetDeftemplate(fb, "x-visibility-event");
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotSymbol(fb, "type", XEventTypeToStr(e->type));
	FBPutSlotInteger(fb, "serial", e->serial);
	FBPutSlotSymbol(fb, "send-event", BoolToStr(e->send_event));
	FBPutSlotCLIPSExternalAddress(fb, "display", CreateCExternalAddress(theEnv, e->display));
	FBPutSlotInteger(fb, "window", e->window);
	FBPutSlotSymbol(fb, "state", VisibilityStateToStr(e->state));

	return FBAssert(fb);
}

Fact *XCreateWindowEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XCreateWindowEvent *e,
		FactBuilder *fb)
{
	FBSetDeftemplate(fb, "x-create-window-event");
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotSymbol(fb, "type", XEventTypeToStr(e->type));
	FBPutSlotInteger(fb, "serial", e->serial);
	FBPutSlotSymbol(fb, "send-event", BoolToStr(e->send_event));
	FBPutSlotCLIPSExternalAddress(fb, "display", CreateCExternalAddress(theEnv, e->display));
	FBPutSlotInteger(fb, "parent", e->parent);
	FBPutSlotInteger(fb, "window", e->window);
	FBPutSlotInteger(fb, "x", e->x);
	FBPutSlotInteger(fb, "y", e->y);
	FBPutSlotInteger(fb, "width", e->width);
	FBPutSlotInteger(fb, "height", e->height);
	FBPutSlotInteger(fb, "border-width", e->border_width);
	FBPutSlotSymbol(fb, "override-redirect", BoolToStr(e->override_redirect));

	return FBAssert(fb);
}

Fact *XDestroyWindowEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XDestroyWindowEvent *e,
		FactBuilder *fb)
{
	FBSetDeftemplate(fb, "x-destroy-window-event");
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotSymbol(fb, "type", XEventTypeToStr(e->type));
	FBPutSlotInteger(fb, "serial", e->serial);
	FBPutSlotSymbol(fb, "send-event", BoolToStr(e->send_event));
	FBPutSlotCLIPSExternalAddress(fb, "display", CreateCExternalAddress(theEnv, e->display));
	FBPutSlotInteger(fb, "event", e->event);
	FBPutSlotInteger(fb, "window", e->window);
	return FBAssert(fb);
}

Fact *XUnmapEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XUnmapEvent *e,
		FactBuilder *fb)
{

	FBSetDeftemplate(fb, "x-unmap-event");
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotSymbol(fb, "type", XEventTypeToStr(e->type));
	FBPutSlotInteger(fb, "serial", e->serial);
	FBPutSlotSymbol(fb, "send-event", BoolToStr(e->send_event));
	FBPutSlotCLIPSExternalAddress(fb, "display", CreateCExternalAddress(theEnv, e->display));
	FBPutSlotInteger(fb, "event", e->event);
	FBPutSlotInteger(fb, "window", e->window);
	FBPutSlotSymbol(fb, "from-configure", BoolToStr(e->from_configure));
	return FBAssert(fb);
}

Fact *XMapEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XMapEvent *e,
		FactBuilder *fb)
{
	FBSetDeftemplate(fb, "x-map-event");
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotSymbol(fb, "type", XEventTypeToStr(e->type));
	FBPutSlotInteger(fb, "serial", e->serial);
	FBPutSlotSymbol(fb, "send-event", BoolToStr(e->send_event));
	FBPutSlotCLIPSExternalAddress(fb, "display", CreateCExternalAddress(theEnv, e->display));
	FBPutSlotInteger(fb, "event", e->event);
	FBPutSlotInteger(fb, "window", e->window);
	FBPutSlotSymbol(fb, "override-redirect", BoolToStr(e->override_redirect));
	return FBAssert(fb);
}

Fact *XMapRequestEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XMapRequestEvent *e,
		FactBuilder *fb)
{
	FBSetDeftemplate(fb, "x-map-request-event");
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotSymbol(fb, "type", XEventTypeToStr(e->type));
	FBPutSlotInteger(fb, "serial", e->serial);
	FBPutSlotSymbol(fb, "send-event", BoolToStr(e->send_event));
	FBPutSlotCLIPSExternalAddress(fb, "display", CreateCExternalAddress(theEnv, e->display));
	FBPutSlotInteger(fb, "parent", e->parent);
	FBPutSlotInteger(fb, "window", e->window);
	return FBAssert(fb);
}

Fact *XReparentEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XReparentEvent *e,
		FactBuilder *fb)
{
	FBSetDeftemplate(fb, "x-reparent-event");
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotSymbol(fb, "type", XEventTypeToStr(e->type));
	FBPutSlotInteger(fb, "serial", e->serial);
	FBPutSlotSymbol(fb, "send-event", BoolToStr(e->send_event));
	FBPutSlotCLIPSExternalAddress(fb, "display", CreateCExternalAddress(theEnv, e->display));
	FBPutSlotInteger(fb, "event", e->event);
	FBPutSlotInteger(fb, "parent", e->parent);
	FBPutSlotInteger(fb, "x", e->x);
	FBPutSlotInteger(fb, "y", e->y);
	FBPutSlotSymbol(fb, "override-redirect", BoolToStr(e->override_redirect));
	return FBAssert(fb);
}

Fact *XConfigureEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XConfigureEvent *e,
		FactBuilder *fb)
{
	FBSetDeftemplate(fb, "x-configure-event");
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotSymbol(fb, "type", XEventTypeToStr(e->type));
	FBPutSlotInteger(fb, "serial", e->serial);
	FBPutSlotSymbol(fb, "send-event", BoolToStr(e->send_event));
	FBPutSlotCLIPSExternalAddress(fb, "display", CreateCExternalAddress(theEnv, e->display));
	FBPutSlotInteger(fb, "event", e->event);
	FBPutSlotInteger(fb, "window", e->window);
	FBPutSlotInteger(fb, "x", e->x);
	FBPutSlotInteger(fb, "y", e->y);
	FBPutSlotInteger(fb, "width", e->width);
	FBPutSlotInteger(fb, "height", e->height);
	FBPutSlotInteger(fb, "border-width", e->border_width);
	FBPutSlotInteger(fb, "above", e->above);
	FBPutSlotSymbol(fb, "override-redirect", BoolToStr(e->override_redirect));
	return FBAssert(fb);
}

Fact *XConfigureRequestEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XConfigureRequestEvent *e,
		FactBuilder *fb)
{
	FBSetDeftemplate(fb, "x-configure-request-event");
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotSymbol(fb, "type", XEventTypeToStr(e->type));
	FBPutSlotInteger(fb, "serial", e->serial);
	FBPutSlotSymbol(fb, "send-event", BoolToStr(e->send_event));
	FBPutSlotCLIPSExternalAddress(fb, "display", CreateCExternalAddress(theEnv, e->display));
	FBPutSlotInteger(fb, "parent", e->parent);
	FBPutSlotInteger(fb, "window", e->window);
	FBPutSlotInteger(fb, "x", e->x);
	FBPutSlotInteger(fb, "y", e->y);
	FBPutSlotInteger(fb, "width", e->width);
	FBPutSlotInteger(fb, "height", e->height);
	FBPutSlotInteger(fb, "border-width", e->border_width);
	FBPutSlotInteger(fb, "above", e->above);
	FBPutSlotSymbol(fb, "detail", ConfigureRequestEventDetailToStr(e->above));
	FBPutSlotInteger(fb, "value-mask", e->value_mask);
	return FBAssert(fb);
}

Fact *XGravityEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XGravityEvent *e,
		FactBuilder *fb)
{
	FBSetDeftemplate(fb, "x-gravity-event");
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotSymbol(fb, "type", XEventTypeToStr(e->type));
	FBPutSlotInteger(fb, "serial", e->serial);
	FBPutSlotSymbol(fb, "send-event", BoolToStr(e->send_event));
	FBPutSlotCLIPSExternalAddress(fb, "display", CreateCExternalAddress(theEnv, e->display));
	FBPutSlotInteger(fb, "event", e->event);
	FBPutSlotInteger(fb, "window", e->window);
	FBPutSlotInteger(fb, "x", e->x);
	FBPutSlotInteger(fb, "y", e->y);
	return FBAssert(fb);
}

Fact *XResizeRequestEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XResizeRequestEvent *e,
		FactBuilder *fb)
{
	FBSetDeftemplate(fb, "x-resize-request-event");
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotSymbol(fb, "type", XEventTypeToStr(e->type));
	FBPutSlotInteger(fb, "serial", e->serial);
	FBPutSlotSymbol(fb, "send-event", BoolToStr(e->send_event));
	FBPutSlotCLIPSExternalAddress(fb, "display", CreateCExternalAddress(theEnv, e->display));
	FBPutSlotInteger(fb, "window", e->window);
	FBPutSlotInteger(fb, "width", e->width);
	FBPutSlotInteger(fb, "height", e->height);
	return FBAssert(fb);
}

Fact *XCirculateEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XCirculateEvent *e,
		FactBuilder *fb)
{
	FBSetDeftemplate(fb, "x-circulate-event");
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotSymbol(fb, "type", XEventTypeToStr(e->type));
	FBPutSlotInteger(fb, "serial", e->serial);
	FBPutSlotSymbol(fb, "send-event", BoolToStr(e->send_event));
	FBPutSlotCLIPSExternalAddress(fb, "display", CreateCExternalAddress(theEnv, e->display));
	FBPutSlotInteger(fb, "event", e->event);
	FBPutSlotInteger(fb, "window", e->window);
	FBPutSlotSymbol(fb, "place", CirculateEventPlaceToStr(e->place));
	return FBAssert(fb);
}

Fact *XCirculateRequestEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XCirculateRequestEvent *e,
		FactBuilder *fb)
{
	FBSetDeftemplate(fb, "x-circulate-request-event");
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotSymbol(fb, "type", XEventTypeToStr(e->type));
	FBPutSlotInteger(fb, "serial", e->serial);
	FBPutSlotSymbol(fb, "send-event", BoolToStr(e->send_event));
	FBPutSlotCLIPSExternalAddress(fb, "display", CreateCExternalAddress(theEnv, e->display));
	FBPutSlotInteger(fb, "parent", e->parent);
	FBPutSlotInteger(fb, "window", e->window);
	FBPutSlotSymbol(fb, "place", CirculateEventPlaceToStr(e->place));
	return FBAssert(fb);
}

Fact *XPropertyEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XPropertyEvent *e,
		FactBuilder *fb)
{
	FBSetDeftemplate(fb, "x-property-event");
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotSymbol(fb, "type", XEventTypeToStr(e->type));
	FBPutSlotInteger(fb, "serial", e->serial);
	FBPutSlotSymbol(fb, "send-event", BoolToStr(e->send_event));
	FBPutSlotCLIPSExternalAddress(fb, "display", CreateCExternalAddress(theEnv, e->display));
	FBPutSlotInteger(fb, "window", e->window);
	FBPutSlotInteger(fb, "atom", e->atom);
	FBPutSlotInteger(fb, "time", e->time);
	FBPutSlotSymbol(fb, "state", PropertyEventStateToStr(e->state));
	return FBAssert(fb);
}

Fact *XSelectionClearEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XSelectionClearEvent *e,
		FactBuilder *fb)
{
	FBSetDeftemplate(fb, "x-selection-clear-event");
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotSymbol(fb, "type", XEventTypeToStr(e->type));
	FBPutSlotInteger(fb, "serial", e->serial);
	FBPutSlotSymbol(fb, "send-event", BoolToStr(e->send_event));
	FBPutSlotCLIPSExternalAddress(fb, "display", CreateCExternalAddress(theEnv, e->display));
	FBPutSlotInteger(fb, "window", e->window);
	FBPutSlotInteger(fb, "selection", e->selection);
	FBPutSlotInteger(fb, "time", e->time);
	return FBAssert(fb);
}

Fact *XSelectionRequestEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XSelectionRequestEvent *e,
		FactBuilder *fb)
{
	FBSetDeftemplate(fb, "x-selection-request-event");
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotSymbol(fb, "type", XEventTypeToStr(e->type));
	FBPutSlotInteger(fb, "serial", e->serial);
	FBPutSlotSymbol(fb, "send-event", BoolToStr(e->send_event));
	FBPutSlotCLIPSExternalAddress(fb, "display", CreateCExternalAddress(theEnv, e->display));
	FBPutSlotInteger(fb, "owner", e->owner);
	FBPutSlotInteger(fb, "requestor", e->requestor);
	FBPutSlotInteger(fb, "selection", e->selection);
	FBPutSlotInteger(fb, "target", e->target);
	FBPutSlotInteger(fb, "property", e->property);
	FBPutSlotInteger(fb, "time", e->time);
	return FBAssert(fb);
}

Fact *XSelectionEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XSelectionEvent *e,
		FactBuilder *fb)
{
	FBSetDeftemplate(fb, "x-selection-event");
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotSymbol(fb, "type", XEventTypeToStr(e->type));
	FBPutSlotInteger(fb, "serial", e->serial);
	FBPutSlotSymbol(fb, "send-event", BoolToStr(e->send_event));
	FBPutSlotCLIPSExternalAddress(fb, "display", CreateCExternalAddress(theEnv, e->display));
	FBPutSlotInteger(fb, "requestor", e->requestor);
	FBPutSlotInteger(fb, "selection", e->selection);
	FBPutSlotInteger(fb, "target", e->target);
	FBPutSlotInteger(fb, "property", e->property);
	FBPutSlotInteger(fb, "time", e->time);
	return FBAssert(fb);
}

Fact *XColormapEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XColormapEvent *e,
		FactBuilder *fb)
{
	FBSetDeftemplate(fb, "x-colormap-event");
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotSymbol(fb, "type", XEventTypeToStr(e->type));
	FBPutSlotInteger(fb, "serial", e->serial);
	FBPutSlotSymbol(fb, "send-event", BoolToStr(e->send_event));
	FBPutSlotCLIPSExternalAddress(fb, "display", CreateCExternalAddress(theEnv, e->display));
	FBPutSlotInteger(fb, "window", e->window);
	FBPutSlotSymbol(fb, "colormap", BoolToStr(e->colormap));
	FBPutSlotSymbol(fb, "new", ColormapEventStateToStr(e->new));
	FBPutSlotSymbol(fb, "state", ColormapEventStateToStr(e->state));
	return FBAssert(fb);
}

Fact *XClientMessageEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XClientMessageEvent *e,
		FactBuilder *fb)
{
	MultifieldBuilder *mb;

	FBSetDeftemplate(fb, "x-client-message-event");
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotSymbol(fb, "type", XEventTypeToStr(e->type));
	FBPutSlotInteger(fb, "serial", e->serial);
	FBPutSlotSymbol(fb, "send-event", BoolToStr(e->send_event));
	FBPutSlotCLIPSExternalAddress(fb, "display", CreateCExternalAddress(theEnv, e->display));
	FBPutSlotInteger(fb, "window", e->window);
	FBPutSlotInteger(fb, "message-type", e->message_type);
	FBPutSlotInteger(fb, "format", e->format);
	mb = CreateMultifieldBuilder(theEnv, 0);
	if (e->format == 8)
	{
		for (int x = 0; x < 20; x++)
		{
			MBAppendInteger(mb, e->data.b[x]);
		}
	}
	else if (e->format == 16)
	{
		for (int x = 0; x < 10; x++)
		{
			MBAppendInteger(mb, e->data.s[x]);
		}
	}
	else if (e->format == 32)
	{
		for (int x = 0; x < 5; x++)
		{
			MBAppendInteger(mb, e->data.l[x]);
		}
	}
	FBPutSlotMultifield(fb, "data", MBCreate(mb));
	MBDispose(mb);
	return FBAssert(fb);
}

Fact *XMappingEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XMappingEvent *e,
		FactBuilder *fb)
{
	FBSetDeftemplate(fb, "x-mapping-event");
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotSymbol(fb, "type", XEventTypeToStr(e->type));
	FBPutSlotInteger(fb, "serial", e->serial);
	FBPutSlotSymbol(fb, "send-event", BoolToStr(e->send_event));
	FBPutSlotCLIPSExternalAddress(fb, "display", CreateCExternalAddress(theEnv, e->display));
	FBPutSlotInteger(fb, "window", e->window);
	FBPutSlotInteger(fb, "request", e->request);
	FBPutSlotInteger(fb, "first-keycode", e->first_keycode);
	FBPutSlotInteger(fb, "count", e->count);
	return FBAssert(fb);
}

Fact *XGenericEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XGenericEvent *e,
		FactBuilder *fb)
{
	FBSetDeftemplate(fb, "x-generic-event");
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotSymbol(fb, "type", XEventTypeToStr(e->type));
	FBPutSlotInteger(fb, "serial", e->serial);
	FBPutSlotSymbol(fb, "send-event", BoolToStr(e->send_event));
	FBPutSlotCLIPSExternalAddress(fb, "display", CreateCExternalAddress(theEnv, e->display));
	FBPutSlotInteger(fb, "extension", e->extension);
	FBPutSlotInteger(fb, "evtype", e->evtype);
	return FBAssert(fb);
}

Fact *XEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XEvent *e,
		FactBuilder *fb)
		
{
	Fact *f;
	switch (e->type)
	{
		case KeyPress:
		case KeyRelease:
			f = XKeyEventToFact(theEnv, context, &(e->xkey), fb);
			break;
		case ButtonPress:
		case ButtonRelease:
			f = XButtonEventToFact(theEnv, context, &(e->xbutton), fb);
			break;
		case MotionNotify:
			f = XMotionEventToFact(theEnv, context, &(e->xmotion), fb);
			break;
		case EnterNotify:
		case LeaveNotify:
			f = XCrossingEventToFact(theEnv, context, &(e->xcrossing), fb);
			break;
		case FocusIn:
		case FocusOut:
			f = XFocusChangeEventToFact(theEnv, context, &(e->xfocus), fb);
			break;
		case KeymapNotify:
			f = XKeymapEventToFact(theEnv, context, e->xany.display, &(e->xkeymap), fb);
			break;
		case Expose:
			f = XExposeEventToFact(theEnv, context, &(e->xexpose), fb);
			break;
		case GraphicsExpose:
			f = XGraphicsExposeEventToFact(theEnv, context, &(e->xgraphicsexpose), fb);
			break;
		case NoExpose:
			f = XNoExposeEventToFact(theEnv, context, &(e->xnoexpose), fb);
			break;
		case VisibilityNotify:
			f = XVisibilityEventToFact(theEnv, context, &(e->xvisibility), fb);
			break;
		case CreateNotify:
			f = XCreateWindowEventToFact(theEnv, context, &(e->xcreatewindow), fb);
			break;
		case DestroyNotify:
			f = XDestroyWindowEventToFact(theEnv, context, &(e->xdestroywindow), fb);
			break;
		case UnmapNotify:
			f = XUnmapEventToFact(theEnv, context, &(e->xunmap), fb);
			break;
		case MapNotify:
			f = XMapEventToFact(theEnv, context, &(e->xmap), fb);
			break;
		case MapRequest:
			f = XMapRequestEventToFact(theEnv, context, &(e->xmaprequest), fb);
			break;
		case ReparentNotify:
			f = XReparentEventToFact(theEnv, context, &(e->xreparent), fb);
			break;
		case ConfigureNotify:
			f = XConfigureEventToFact(theEnv, context, &(e->xconfigure), fb);
			break;
		case ConfigureRequest:
			f = XConfigureRequestEventToFact(theEnv, context, &(e->xconfigurerequest), fb);
			break;
		case GravityNotify:
			f = XGravityEventToFact(theEnv, context, &(e->xgravity), fb);
			break;
		case ResizeRequest:
			f = XResizeRequestEventToFact(theEnv, context, &(e->xresizerequest), fb);
			break;
		case CirculateNotify:
			f = XCirculateEventToFact(theEnv, context, &(e->xcirculate), fb);
			break;
		case CirculateRequest:
			f = XCirculateRequestEventToFact(theEnv, context, &(e->xcirculaterequest), fb);
			break;
		case PropertyNotify:
			f = XPropertyEventToFact(theEnv, context, &(e->xproperty), fb);
			break;
		case SelectionClear:
			f = XSelectionClearEventToFact(theEnv, context, &(e->xselectionclear), fb);
			break;
		case SelectionRequest:
			f = XSelectionRequestEventToFact(theEnv, context, &(e->xselectionrequest), fb);
			break;
		case SelectionNotify:
			f = XSelectionEventToFact(theEnv, context, &(e->xselection), fb);
			break;
		case ColormapNotify:
			f = XColormapEventToFact(theEnv, context, &(e->xcolormap), fb);
			break;
		case ClientMessage:
			f = XClientMessageEventToFact(theEnv, context, &(e->xclient), fb);
			break;
		case MappingNotify:
			f = XMappingEventToFact(theEnv, context, &(e->xmapping), fb);
			break;
		case GenericEvent:
			f = XGenericEventToFact(theEnv, context, &(e->xgeneric), fb);
			break;
		default:
			WriteString(theEnv,STDERR,"Event Type ");
			WriteInteger(theEnv,STDERR,e->type);
			WriteString(theEnv,STDERR," not supported.\n");
			return NULL;
	}
	FBDispose(fb);
	if (f == NULL)
	{
		WriteString(theEnv,STDERR,"Could not assert fact for XEvent ");
		WriteString(theEnv,STDERR,XEventTypeToStr(e->type));
		ReportFBAssertError(theEnv);
		return NULL;
	}
	fb = CreateFactBuilder(theEnv, "x-event");
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotSymbol(fb, "type", XEventTypeToStr(e->type));
	FBPutSlotFact(fb, "typed-event", f);
	return FBAssert(fb);
}

Instance *XKeyEventToInstance(
		Environment *theEnv,
		UDFContext *context,
		XKeyEvent *e,
		InstanceBuilder *ib,
		const char *name)
{
	MultifieldBuilder *mb;
	Multifield *mf;

	IBSetDefclass(ib, "X-KEY-EVENT");
	IBPutSlotExternalAddress(ib, "c-pointer", CreateCExternalAddress(theEnv, e));
	IBPutSlotSymbol(ib, "type", XEventTypeToStr(e->type));
	IBPutSlotInteger(ib, "serial", e->serial);
	IBPutSlotSymbol(ib, "send-event", BoolToStr(e->send_event));
	IBPutSlotExternalAddress(ib, "display", CreateCExternalAddress(theEnv, e->display));
	IBPutSlotInteger(ib, "window", e->window);
	IBPutSlotInteger(ib, "root", e->root);
	IBPutSlotInteger(ib, "subwindow", e->subwindow);
	IBPutSlotInteger(ib, "time", e->time);
	IBPutSlotInteger(ib, "x", e->x);
	IBPutSlotInteger(ib, "y", e->y);
	IBPutSlotInteger(ib, "x-root", e->x_root);
	IBPutSlotInteger(ib, "y-root", e->y_root);
	mb = CreateMultifieldBuilder(theEnv, 0);
	mf = MaskToMultifield(e->state, mb);
	MBDispose(mb);
	if (mf == NULL)
	{
		WriteString(theEnv,STDERR,"Could not create multifield for x-key-event's state");
		return NULL;
	}
	IBPutSlotMultifield(ib, "state", mf);
	IBPutSlotInteger(ib, "keycode", e->keycode);
	IBPutSlotSymbol(ib, "same-screen", BoolToStr(e->same_screen));

	return IBMake(ib, name);
}

Instance *XButtonEventToInstance(
		Environment *theEnv,
		UDFContext *context,
		XButtonEvent *e,
		InstanceBuilder *ib,
		const char *name)
{
	MultifieldBuilder *mb;
	Multifield *mf;

	IBSetDefclass(ib, "X-BUTTON-EVENT");
	IBPutSlotExternalAddress(ib, "c-pointer", CreateCExternalAddress(theEnv, e));
	IBPutSlotSymbol(ib, "type", XEventTypeToStr(e->type));
	IBPutSlotInteger(ib, "serial", e->serial);
	IBPutSlotSymbol(ib, "send-event", BoolToStr(e->send_event));
	IBPutSlotExternalAddress(ib, "display", CreateCExternalAddress(theEnv, e->display));
	IBPutSlotInteger(ib, "window", e->window);
	IBPutSlotInteger(ib, "root", e->root);
	IBPutSlotInteger(ib, "subwindow", e->subwindow);
	IBPutSlotInteger(ib, "time", e->time);
	IBPutSlotInteger(ib, "x", e->x);
	IBPutSlotInteger(ib, "y", e->y);
	IBPutSlotInteger(ib, "x-root", e->x_root);
	IBPutSlotInteger(ib, "y-root", e->y_root);
	mb = CreateMultifieldBuilder(theEnv, 0);
	mf = MaskToMultifield(e->state, mb);
	MBDispose(mb);
	if (mf == NULL)
	{
		WriteString(theEnv,STDERR,"Could not create multifield for x-button-event's state");
		return NULL;
	}
	IBPutSlotMultifield(ib, "state", mf);
	IBPutSlotInteger(ib, "button", e->button);
	IBPutSlotSymbol(ib, "same-screen", BoolToStr(e->same_screen));

	return IBMake(ib, name);
}

Instance *XMotionEventToInstance(
		Environment *theEnv,
		UDFContext *context,
		XMotionEvent *e,
		InstanceBuilder *ib,
		const char *name)
{
	MultifieldBuilder *mb;
	Multifield *mf;

	IBSetDefclass(ib, "X-MOTION-EVENT");
	IBPutSlotExternalAddress(ib, "c-pointer", CreateCExternalAddress(theEnv, e));
	IBPutSlotSymbol(ib, "type", XEventTypeToStr(e->type));
	IBPutSlotInteger(ib, "serial", e->serial);
	IBPutSlotSymbol(ib, "send-event", BoolToStr(e->send_event));
	IBPutSlotExternalAddress(ib, "display", CreateCExternalAddress(theEnv, e->display));
	IBPutSlotInteger(ib, "window", e->window);
	IBPutSlotInteger(ib, "root", e->root);
	IBPutSlotInteger(ib, "subwindow", e->subwindow);
	IBPutSlotInteger(ib, "time", e->time);
	IBPutSlotInteger(ib, "x", e->x);
	IBPutSlotInteger(ib, "y", e->y);
	IBPutSlotInteger(ib, "x-root", e->x_root);
	IBPutSlotInteger(ib, "y-root", e->y_root);
	mb = CreateMultifieldBuilder(theEnv, 0);
	mf = MaskToMultifield(e->state, mb);
	MBDispose(mb);
	if (mf == NULL)
	{
		WriteString(theEnv,STDERR,"Could not create multifield for x-motion-event's state");
		return NULL;
	}
	IBPutSlotMultifield(ib, "state", mf);
	switch(e->is_hint)
	{
		case NotifyNormal:
			IBPutSlotSymbol(ib, "is-hint", "NotifyNormal");
			break;
		case NotifyHint:
			IBPutSlotSymbol(ib, "is-hint", "NotifyHint");
			break;
		default:
			WriteString(theEnv,STDERR,"Notify hint type ");
			WriteInteger(theEnv,STDERR,e->is_hint);
			WriteString(theEnv,STDERR," not supported.\n");
			return NULL;
	}
	IBPutSlotSymbol(ib, "same-screen", BoolToStr(e->same_screen));

	return IBMake(ib, name);
}
Instance *XCrossingEventToInstance(
		Environment *theEnv,
		UDFContext *context,
		XCrossingEvent *e,
		InstanceBuilder *ib,
		const char *name)
{
	MultifieldBuilder *mb;
	Multifield *mf;

	IBSetDefclass(ib, "X-CROSSING-EVENT");
	IBPutSlotExternalAddress(ib, "c-pointer", CreateCExternalAddress(theEnv, e));
	IBPutSlotSymbol(ib, "type", XEventTypeToStr(e->type));
	IBPutSlotInteger(ib, "serial", e->serial);
	IBPutSlotSymbol(ib, "send-event", BoolToStr(e->send_event));
	IBPutSlotExternalAddress(ib, "display", CreateCExternalAddress(theEnv, e->display));
	IBPutSlotInteger(ib, "window", e->window);
	IBPutSlotInteger(ib, "root", e->root);
	IBPutSlotInteger(ib, "subwindow", e->subwindow);
	IBPutSlotInteger(ib, "time", e->time);
	IBPutSlotInteger(ib, "x", e->x);
	IBPutSlotInteger(ib, "y", e->y);
	IBPutSlotInteger(ib, "x-root", e->x_root);
	IBPutSlotInteger(ib, "y-root", e->y_root);
	IBPutSlotSymbol(ib, "mode", EventModeToStr(e->mode));
	IBPutSlotSymbol(ib, "detail", EventDetailToStr(e->detail));
	IBPutSlotSymbol(ib, "same-screen", BoolToStr(e->same_screen));
	IBPutSlotSymbol(ib, "focus", BoolToStr(e->focus));
	mb = CreateMultifieldBuilder(theEnv, 0);
	mf = MaskToMultifield(e->state, mb);
	MBDispose(mb);
	if (mf == NULL)
	{
		WriteString(theEnv,STDERR,"Could not create multifield for x-crossing-event's state");
		return NULL;
	}
	IBPutSlotMultifield(ib, "state", mf);

	return IBMake(ib, name);
}

Instance *XFocusChangeEventToInstance(
		Environment *theEnv,
		UDFContext *context,
		XFocusChangeEvent *e,
		InstanceBuilder *ib,
		const char *name)
{
	IBSetDefclass(ib, "X-FOCUS-CHANGE-EVENT");
	IBPutSlotExternalAddress(ib, "c-pointer", CreateCExternalAddress(theEnv, e));
	IBPutSlotSymbol(ib, "type", XEventTypeToStr(e->type));
	IBPutSlotInteger(ib, "serial", e->serial);
	IBPutSlotSymbol(ib, "send-event", BoolToStr(e->send_event));
	IBPutSlotExternalAddress(ib, "display", CreateCExternalAddress(theEnv, e->display));
	IBPutSlotInteger(ib, "window", e->window);
	IBPutSlotSymbol(ib, "mode", EventModeToStr(e->mode));
	IBPutSlotSymbol(ib, "detail", EventDetailToStr(e->detail));

	return IBMake(ib, name);
}

Instance *XKeymapEventToInstance(
		Environment *theEnv,
		UDFContext *context,
		Display *display,
		XKeymapEvent *e,
		InstanceBuilder *ib,
		const char *name)
{
	int min_keycode, max_keycode;
	MultifieldBuilder *keyvectormb, *keydownmb;

	IBSetDefclass(ib, "X-KEYMAP-EVENT");
	IBPutSlotExternalAddress(ib, "c-pointer", CreateCExternalAddress(theEnv, e));
	IBPutSlotSymbol(ib, "type", XEventTypeToStr(e->type));
	IBPutSlotInteger(ib, "serial", e->serial);
	IBPutSlotSymbol(ib, "send-event", BoolToStr(e->send_event));
	IBPutSlotExternalAddress(ib, "display", CreateCExternalAddress(theEnv, e->display));
	IBPutSlotInteger(ib, "window", e->window);

	XDisplayKeycodes(display, &min_keycode, &max_keycode);

	keyvectormb = CreateMultifieldBuilder(theEnv, 0);
	keydownmb = CreateMultifieldBuilder(theEnv, 0);
	for (int kc = min_keycode; kc <= max_keycode; kc++)
	{
		if (e->key_vector[kc >> 3] & (1 << (kc & 7)))
		{
			MBAppendSymbol(keyvectormb, "TRUE");
			MBAppendInteger(keydownmb, kc);
		}
		else
		{
			MBAppendSymbol(keyvectormb, "FALSE");
		}
	}
	IBPutSlotMultifield(ib, "keyvector", MBCreate(keyvectormb));
	MBDispose(keyvectormb);
	IBPutSlotMultifield(ib, "keydown", MBCreate(keydownmb));
	MBDispose(keydownmb);

	return IBMake(ib, name);
}

Instance *XExposeEventToInstance(
		Environment *theEnv,
		UDFContext *context,
		XExposeEvent *e,
		InstanceBuilder *ib,
		const char *name)
{
	IBSetDefclass(ib, "X-EXPOSE-EVENT");
	IBPutSlotExternalAddress(ib, "c-pointer", CreateCExternalAddress(theEnv, e));
	IBPutSlotSymbol(ib, "type", XEventTypeToStr(e->type));
	IBPutSlotInteger(ib, "serial", e->serial);
	IBPutSlotSymbol(ib, "send-event", BoolToStr(e->send_event));
	IBPutSlotExternalAddress(ib, "display", CreateCExternalAddress(theEnv, e->display));
	IBPutSlotInteger(ib, "window", e->window);
	IBPutSlotInteger(ib, "x", e->x);
	IBPutSlotInteger(ib, "y", e->y);
	IBPutSlotInteger(ib, "width", e->width);
	IBPutSlotInteger(ib, "height", e->height);
	IBPutSlotInteger(ib, "count", e->count);

	return IBMake(ib, name);
}

Instance *XGraphicsExposeEventToInstance(
		Environment *theEnv,
		UDFContext *context,
		XGraphicsExposeEvent *e,
		InstanceBuilder *ib,
		const char *name)
{
	IBSetDefclass(ib, "X-GRAPHICS-EXPOSE-EVENT");
	IBPutSlotExternalAddress(ib, "c-pointer", CreateCExternalAddress(theEnv, e));
	IBPutSlotSymbol(ib, "type", XEventTypeToStr(e->type));
	IBPutSlotInteger(ib, "serial", e->serial);
	IBPutSlotSymbol(ib, "send-event", BoolToStr(e->send_event));
	IBPutSlotExternalAddress(ib, "display", CreateCExternalAddress(theEnv, e->display));
	IBPutSlotInteger(ib, "drawable", e->drawable);
	IBPutSlotInteger(ib, "x", e->x);
	IBPutSlotInteger(ib, "y", e->y);
	IBPutSlotInteger(ib, "width", e->width);
	IBPutSlotInteger(ib, "height", e->height);
	IBPutSlotInteger(ib, "count", e->count);
	IBPutSlotInteger(ib, "major-code", e->major_code);
	IBPutSlotInteger(ib, "minor-code", e->minor_code);

	return IBMake(ib, name);
}

Instance *XNoExposeEventToInstance(
		Environment *theEnv,
		UDFContext *context,
		XNoExposeEvent *e,
		InstanceBuilder *ib,
		const char *name)
{
	IBSetDefclass(ib, "X-NO-EXPOSE-EVENT");
	IBPutSlotExternalAddress(ib, "c-pointer", CreateCExternalAddress(theEnv, e));
	IBPutSlotSymbol(ib, "type", XEventTypeToStr(e->type));
	IBPutSlotInteger(ib, "serial", e->serial);
	IBPutSlotSymbol(ib, "send-event", BoolToStr(e->send_event));
	IBPutSlotExternalAddress(ib, "display", CreateCExternalAddress(theEnv, e->display));
	IBPutSlotInteger(ib, "drawable", e->drawable);
	IBPutSlotInteger(ib, "major-code", e->major_code);
	IBPutSlotInteger(ib, "minor-code", e->minor_code);

	return IBMake(ib, name);
}

Instance *XVisibilityEventToInstance(
		Environment *theEnv,
		UDFContext *context,
		XVisibilityEvent *e,
		InstanceBuilder *ib,
		const char *name)
{
	IBSetDefclass(ib, "X-VISIBILITY-EVENT");
	IBPutSlotExternalAddress(ib, "c-pointer", CreateCExternalAddress(theEnv, e));
	IBPutSlotSymbol(ib, "type", XEventTypeToStr(e->type));
	IBPutSlotInteger(ib, "serial", e->serial);
	IBPutSlotSymbol(ib, "send-event", BoolToStr(e->send_event));
	IBPutSlotExternalAddress(ib, "display", CreateCExternalAddress(theEnv, e->display));
	IBPutSlotInteger(ib, "window", e->window);
	IBPutSlotSymbol(ib, "state", VisibilityStateToStr(e->state));

	return IBMake(ib, name);
}

Instance *XCreateWindowEventToInstance(
		Environment *theEnv,
		UDFContext *context,
		XCreateWindowEvent *e,
		InstanceBuilder *ib,
		const char *name)
{
	IBSetDefclass(ib, "X-CREATE-WINDOW-EVENT");
	IBPutSlotExternalAddress(ib, "c-pointer", CreateCExternalAddress(theEnv, e));
	IBPutSlotSymbol(ib, "type", XEventTypeToStr(e->type));
	IBPutSlotInteger(ib, "serial", e->serial);
	IBPutSlotSymbol(ib, "send-event", BoolToStr(e->send_event));
	IBPutSlotExternalAddress(ib, "display", CreateCExternalAddress(theEnv, e->display));
	IBPutSlotInteger(ib, "parent", e->parent);
	IBPutSlotInteger(ib, "window", e->window);
	IBPutSlotInteger(ib, "x", e->x);
	IBPutSlotInteger(ib, "y", e->y);
	IBPutSlotInteger(ib, "width", e->width);
	IBPutSlotInteger(ib, "height", e->height);
	IBPutSlotInteger(ib, "border-width", e->border_width);
	IBPutSlotSymbol(ib, "override-redirect", BoolToStr(e->override_redirect));

	return IBMake(ib, name);
}

Instance *XDestroyWindowEventToInstance(
		Environment *theEnv,
		UDFContext *context,
		XDestroyWindowEvent *e,
		InstanceBuilder *ib,
		const char *name)
{
	IBSetDefclass(ib, "X-DESTROY-WINDOW-EVENT");
	IBPutSlotExternalAddress(ib, "c-pointer", CreateCExternalAddress(theEnv, e));
	IBPutSlotSymbol(ib, "type", XEventTypeToStr(e->type));
	IBPutSlotInteger(ib, "serial", e->serial);
	IBPutSlotSymbol(ib, "send-event", BoolToStr(e->send_event));
	IBPutSlotExternalAddress(ib, "display", CreateCExternalAddress(theEnv, e->display));
	IBPutSlotInteger(ib, "event", e->event);
	IBPutSlotInteger(ib, "window", e->window);
	return IBMake(ib, name);
}

Instance *XUnmapEventToInstance(
		Environment *theEnv,
		UDFContext *context,
		XUnmapEvent *e,
		InstanceBuilder *ib,
		const char *name)
{

	IBSetDefclass(ib, "X-UNMAP-EVENT");
	IBPutSlotExternalAddress(ib, "c-pointer", CreateCExternalAddress(theEnv, e));
	IBPutSlotSymbol(ib, "type", XEventTypeToStr(e->type));
	IBPutSlotInteger(ib, "serial", e->serial);
	IBPutSlotSymbol(ib, "send-event", BoolToStr(e->send_event));
	IBPutSlotExternalAddress(ib, "display", CreateCExternalAddress(theEnv, e->display));
	IBPutSlotInteger(ib, "event", e->event);
	IBPutSlotInteger(ib, "window", e->window);
	IBPutSlotSymbol(ib, "from-configure", BoolToStr(e->from_configure));
	return IBMake(ib, name);
}

Instance *XMapEventToInstance(
		Environment *theEnv,
		UDFContext *context,
		XMapEvent *e,
		InstanceBuilder *ib,
		const char *name)
{
	IBSetDefclass(ib, "X-MAP-EVENT");
	IBPutSlotExternalAddress(ib, "c-pointer", CreateCExternalAddress(theEnv, e));
	IBPutSlotSymbol(ib, "type", XEventTypeToStr(e->type));
	IBPutSlotInteger(ib, "serial", e->serial);
	IBPutSlotSymbol(ib, "send-event", BoolToStr(e->send_event));
	IBPutSlotExternalAddress(ib, "display", CreateCExternalAddress(theEnv, e->display));
	IBPutSlotInteger(ib, "event", e->event);
	IBPutSlotInteger(ib, "window", e->window);
	IBPutSlotSymbol(ib, "override-redirect", BoolToStr(e->override_redirect));
	return IBMake(ib, name);
}

Instance *XMapRequestEventToInstance(
		Environment *theEnv,
		UDFContext *context,
		XMapRequestEvent *e,
		InstanceBuilder *ib,
		const char *name)
{
	IBSetDefclass(ib, "X-MAP-REQUEST-EVENT");
	IBPutSlotExternalAddress(ib, "c-pointer", CreateCExternalAddress(theEnv, e));
	IBPutSlotSymbol(ib, "type", XEventTypeToStr(e->type));
	IBPutSlotInteger(ib, "serial", e->serial);
	IBPutSlotSymbol(ib, "send-event", BoolToStr(e->send_event));
	IBPutSlotExternalAddress(ib, "display", CreateCExternalAddress(theEnv, e->display));
	IBPutSlotInteger(ib, "parent", e->parent);
	IBPutSlotInteger(ib, "window", e->window);
	return IBMake(ib, name);
}

Instance *XReparentEventToInstance(
		Environment *theEnv,
		UDFContext *context,
		XReparentEvent *e,
		InstanceBuilder *ib,
		const char *name)
{
	IBSetDefclass(ib, "X-REPARENT-EVENT");
	IBPutSlotExternalAddress(ib, "c-pointer", CreateCExternalAddress(theEnv, e));
	IBPutSlotSymbol(ib, "type", XEventTypeToStr(e->type));
	IBPutSlotInteger(ib, "serial", e->serial);
	IBPutSlotSymbol(ib, "send-event", BoolToStr(e->send_event));
	IBPutSlotExternalAddress(ib, "display", CreateCExternalAddress(theEnv, e->display));
	IBPutSlotInteger(ib, "event", e->event);
	IBPutSlotInteger(ib, "parent", e->parent);
	IBPutSlotInteger(ib, "x", e->x);
	IBPutSlotInteger(ib, "y", e->y);
	IBPutSlotSymbol(ib, "override-redirect", BoolToStr(e->override_redirect));
	return IBMake(ib, name);
}

Instance *XConfigureEventToInstance(
		Environment *theEnv,
		UDFContext *context,
		XConfigureEvent *e,
		InstanceBuilder *ib,
		const char *name)
{
	IBSetDefclass(ib, "X-CONFIGURE-EVENT");
	IBPutSlotExternalAddress(ib, "c-pointer", CreateCExternalAddress(theEnv, e));
	IBPutSlotSymbol(ib, "type", XEventTypeToStr(e->type));
	IBPutSlotInteger(ib, "serial", e->serial);
	IBPutSlotSymbol(ib, "send-event", BoolToStr(e->send_event));
	IBPutSlotExternalAddress(ib, "display", CreateCExternalAddress(theEnv, e->display));
	IBPutSlotInteger(ib, "event", e->event);
	IBPutSlotInteger(ib, "window", e->window);
	IBPutSlotInteger(ib, "x", e->x);
	IBPutSlotInteger(ib, "y", e->y);
	IBPutSlotInteger(ib, "width", e->width);
	IBPutSlotInteger(ib, "height", e->height);
	IBPutSlotInteger(ib, "border-width", e->border_width);
	IBPutSlotInteger(ib, "above", e->above);
	IBPutSlotSymbol(ib, "override-redirect", BoolToStr(e->override_redirect));
	return IBMake(ib, name);
}

Instance *XConfigureRequestEventToInstance(
		Environment *theEnv,
		UDFContext *context,
		XConfigureRequestEvent *e,
		InstanceBuilder *ib,
		const char *name)
{
	IBSetDefclass(ib, "X-CONFIGURE-REQUEST-EVENT");
	IBPutSlotExternalAddress(ib, "c-pointer", CreateCExternalAddress(theEnv, e));
	IBPutSlotSymbol(ib, "type", XEventTypeToStr(e->type));
	IBPutSlotInteger(ib, "serial", e->serial);
	IBPutSlotSymbol(ib, "send-event", BoolToStr(e->send_event));
	IBPutSlotExternalAddress(ib, "display", CreateCExternalAddress(theEnv, e->display));
	IBPutSlotInteger(ib, "parent", e->parent);
	IBPutSlotInteger(ib, "window", e->window);
	IBPutSlotInteger(ib, "x", e->x);
	IBPutSlotInteger(ib, "y", e->y);
	IBPutSlotInteger(ib, "width", e->width);
	IBPutSlotInteger(ib, "height", e->height);
	IBPutSlotInteger(ib, "border-width", e->border_width);
	IBPutSlotInteger(ib, "above", e->above);
	IBPutSlotSymbol(ib, "detail", ConfigureRequestEventDetailToStr(e->above));
	IBPutSlotInteger(ib, "value-mask", e->value_mask);
	return IBMake(ib, name);
}

Instance *XGravityEventToInstance(
		Environment *theEnv,
		UDFContext *context,
		XGravityEvent *e,
		InstanceBuilder *ib,
		const char *name)
{
	IBSetDefclass(ib, "X-GRAVITY-EVENT");
	IBPutSlotExternalAddress(ib, "c-pointer", CreateCExternalAddress(theEnv, e));
	IBPutSlotSymbol(ib, "type", XEventTypeToStr(e->type));
	IBPutSlotInteger(ib, "serial", e->serial);
	IBPutSlotSymbol(ib, "send-event", BoolToStr(e->send_event));
	IBPutSlotExternalAddress(ib, "display", CreateCExternalAddress(theEnv, e->display));
	IBPutSlotInteger(ib, "event", e->event);
	IBPutSlotInteger(ib, "window", e->window);
	IBPutSlotInteger(ib, "x", e->x);
	IBPutSlotInteger(ib, "y", e->y);
	return IBMake(ib, name);
}

Instance *XResizeRequestEventToInstance(
		Environment *theEnv,
		UDFContext *context,
		XResizeRequestEvent *e,
		InstanceBuilder *ib,
		const char *name)
{
	IBSetDefclass(ib, "X-RESIZE-REQUEST-EVENT");
	IBPutSlotExternalAddress(ib, "c-pointer", CreateCExternalAddress(theEnv, e));
	IBPutSlotSymbol(ib, "type", XEventTypeToStr(e->type));
	IBPutSlotInteger(ib, "serial", e->serial);
	IBPutSlotSymbol(ib, "send-event", BoolToStr(e->send_event));
	IBPutSlotExternalAddress(ib, "display", CreateCExternalAddress(theEnv, e->display));
	IBPutSlotInteger(ib, "window", e->window);
	IBPutSlotInteger(ib, "width", e->width);
	IBPutSlotInteger(ib, "height", e->height);
	return IBMake(ib, name);
}

Instance *XCirculateEventToInstance(
		Environment *theEnv,
		UDFContext *context,
		XCirculateEvent *e,
		InstanceBuilder *ib,
		const char *name)
{
	IBSetDefclass(ib, "X-CIRCULATE-EVENT");
	IBPutSlotExternalAddress(ib, "c-pointer", CreateCExternalAddress(theEnv, e));
	IBPutSlotSymbol(ib, "type", XEventTypeToStr(e->type));
	IBPutSlotInteger(ib, "serial", e->serial);
	IBPutSlotSymbol(ib, "send-event", BoolToStr(e->send_event));
	IBPutSlotExternalAddress(ib, "display", CreateCExternalAddress(theEnv, e->display));
	IBPutSlotInteger(ib, "event", e->event);
	IBPutSlotInteger(ib, "window", e->window);
	IBPutSlotSymbol(ib, "place", CirculateEventPlaceToStr(e->place));
	return IBMake(ib, name);
}

Instance *XCirculateRequestEventToInstance(
		Environment *theEnv,
		UDFContext *context,
		XCirculateRequestEvent *e,
		InstanceBuilder *ib,
		const char *name)
{
	IBSetDefclass(ib, "X-CIRCULATE-REQUEST-EVENT");
	IBPutSlotExternalAddress(ib, "c-pointer", CreateCExternalAddress(theEnv, e));
	IBPutSlotSymbol(ib, "type", XEventTypeToStr(e->type));
	IBPutSlotInteger(ib, "serial", e->serial);
	IBPutSlotSymbol(ib, "send-event", BoolToStr(e->send_event));
	IBPutSlotExternalAddress(ib, "display", CreateCExternalAddress(theEnv, e->display));
	IBPutSlotInteger(ib, "parent", e->parent);
	IBPutSlotInteger(ib, "window", e->window);
	IBPutSlotSymbol(ib, "place", CirculateEventPlaceToStr(e->place));
	return IBMake(ib, name);
}

Instance *XPropertyEventToInstance(
		Environment *theEnv,
		UDFContext *context,
		XPropertyEvent *e,
		InstanceBuilder *ib,
		const char *name)
{
	IBSetDefclass(ib, "X-PROPERTY-EVENT");
	IBPutSlotExternalAddress(ib, "c-pointer", CreateCExternalAddress(theEnv, e));
	IBPutSlotSymbol(ib, "type", XEventTypeToStr(e->type));
	IBPutSlotInteger(ib, "serial", e->serial);
	IBPutSlotSymbol(ib, "send-event", BoolToStr(e->send_event));
	IBPutSlotExternalAddress(ib, "display", CreateCExternalAddress(theEnv, e->display));
	IBPutSlotInteger(ib, "window", e->window);
	IBPutSlotInteger(ib, "atom", e->atom);
	IBPutSlotInteger(ib, "time", e->time);
	IBPutSlotSymbol(ib, "state", PropertyEventStateToStr(e->state));
	return IBMake(ib, name);
}

Instance *XSelectionClearEventToInstance(
		Environment *theEnv,
		UDFContext *context,
		XSelectionClearEvent *e,
		InstanceBuilder *ib,
		const char *name)
{
	IBSetDefclass(ib, "X-SELECTION-CLEAR-EVENT");
	IBPutSlotExternalAddress(ib, "c-pointer", CreateCExternalAddress(theEnv, e));
	IBPutSlotSymbol(ib, "type", XEventTypeToStr(e->type));
	IBPutSlotInteger(ib, "serial", e->serial);
	IBPutSlotSymbol(ib, "send-event", BoolToStr(e->send_event));
	IBPutSlotExternalAddress(ib, "display", CreateCExternalAddress(theEnv, e->display));
	IBPutSlotInteger(ib, "window", e->window);
	IBPutSlotInteger(ib, "selection", e->selection);
	IBPutSlotInteger(ib, "time", e->time);
	return IBMake(ib, name);
}

Instance *XSelectionRequestEventToInstance(
		Environment *theEnv,
		UDFContext *context,
		XSelectionRequestEvent *e,
		InstanceBuilder *ib,
		const char *name)
{
	IBSetDefclass(ib, "X-SELECTION-REQUEST-EVENT");
	IBPutSlotExternalAddress(ib, "c-pointer", CreateCExternalAddress(theEnv, e));
	IBPutSlotSymbol(ib, "type", XEventTypeToStr(e->type));
	IBPutSlotInteger(ib, "serial", e->serial);
	IBPutSlotSymbol(ib, "send-event", BoolToStr(e->send_event));
	IBPutSlotExternalAddress(ib, "display", CreateCExternalAddress(theEnv, e->display));
	IBPutSlotInteger(ib, "owner", e->owner);
	IBPutSlotInteger(ib, "requestor", e->requestor);
	IBPutSlotInteger(ib, "selection", e->selection);
	IBPutSlotInteger(ib, "target", e->target);
	IBPutSlotInteger(ib, "property", e->property);
	IBPutSlotInteger(ib, "time", e->time);
	return IBMake(ib, name);
}

Instance *XSelectionEventToInstance(
		Environment *theEnv,
		UDFContext *context,
		XSelectionEvent *e,
		InstanceBuilder *ib,
		const char *name)
{
	IBSetDefclass(ib, "X-SELECTION-EVENT");
	IBPutSlotExternalAddress(ib, "c-pointer", CreateCExternalAddress(theEnv, e));
	IBPutSlotSymbol(ib, "type", XEventTypeToStr(e->type));
	IBPutSlotInteger(ib, "serial", e->serial);
	IBPutSlotSymbol(ib, "send-event", BoolToStr(e->send_event));
	IBPutSlotExternalAddress(ib, "display", CreateCExternalAddress(theEnv, e->display));
	IBPutSlotInteger(ib, "requestor", e->requestor);
	IBPutSlotInteger(ib, "selection", e->selection);
	IBPutSlotInteger(ib, "target", e->target);
	IBPutSlotInteger(ib, "property", e->property);
	IBPutSlotInteger(ib, "time", e->time);
	return IBMake(ib, name);
}

Instance *XColormapEventToInstance(
		Environment *theEnv,
		UDFContext *context,
		XColormapEvent *e,
		InstanceBuilder *ib,
		const char *name)
{
	IBSetDefclass(ib, "X-COLORMAP-EVENT");
	IBPutSlotExternalAddress(ib, "c-pointer", CreateCExternalAddress(theEnv, e));
	IBPutSlotSymbol(ib, "type", XEventTypeToStr(e->type));
	IBPutSlotInteger(ib, "serial", e->serial);
	IBPutSlotSymbol(ib, "send-event", BoolToStr(e->send_event));
	IBPutSlotExternalAddress(ib, "display", CreateCExternalAddress(theEnv, e->display));
	IBPutSlotInteger(ib, "window", e->window);
	IBPutSlotSymbol(ib, "colormap", BoolToStr(e->colormap));
	IBPutSlotSymbol(ib, "new", ColormapEventStateToStr(e->new));
	IBPutSlotSymbol(ib, "state", ColormapEventStateToStr(e->state));
	return IBMake(ib, name);
}

Instance *XClientMessageEventToInstance(
		Environment *theEnv,
		UDFContext *context,
		XClientMessageEvent *e,
		InstanceBuilder *ib,
		const char *name)
{
	MultifieldBuilder *mb;

	IBSetDefclass(ib, "X-CLIENT-MESSAGE-EVENT");
	IBPutSlotExternalAddress(ib, "c-pointer", CreateCExternalAddress(theEnv, e));
	IBPutSlotSymbol(ib, "type", XEventTypeToStr(e->type));
	IBPutSlotInteger(ib, "serial", e->serial);
	IBPutSlotSymbol(ib, "send-event", BoolToStr(e->send_event));
	IBPutSlotExternalAddress(ib, "display", CreateCExternalAddress(theEnv, e->display));
	IBPutSlotInteger(ib, "window", e->window);
	IBPutSlotInteger(ib, "message-type", e->message_type);
	IBPutSlotInteger(ib, "format", e->format);
	mb = CreateMultifieldBuilder(theEnv, 0);
	if (e->format == 8)
	{
		for (int x = 0; x < 20; x++)
		{
			MBAppendInteger(mb, e->data.b[x]);
		}
	}
	else if (e->format == 16)
	{
		for (int x = 0; x < 10; x++)
		{
			MBAppendInteger(mb, e->data.s[x]);
		}
	}
	else if (e->format == 32)
	{
		for (int x = 0; x < 5; x++)
		{
			MBAppendInteger(mb, e->data.l[x]);
		}
	}
	IBPutSlotMultifield(ib, "data", MBCreate(mb));
	MBDispose(mb);
	return IBMake(ib, name);
}

Instance *XMappingEventToInstance(
		Environment *theEnv,
		UDFContext *context,
		XMappingEvent *e,
		InstanceBuilder *ib,
		const char *name)
{
	IBSetDefclass(ib, "X-MAPPING-EVENT");
	IBPutSlotExternalAddress(ib, "c-pointer", CreateCExternalAddress(theEnv, e));
	IBPutSlotSymbol(ib, "type", XEventTypeToStr(e->type));
	IBPutSlotInteger(ib, "serial", e->serial);
	IBPutSlotSymbol(ib, "send-event", BoolToStr(e->send_event));
	IBPutSlotExternalAddress(ib, "display", CreateCExternalAddress(theEnv, e->display));
	IBPutSlotInteger(ib, "window", e->window);
	IBPutSlotInteger(ib, "request", e->request);
	IBPutSlotInteger(ib, "first-keycode", e->first_keycode);
	IBPutSlotInteger(ib, "count", e->count);
	return IBMake(ib, name);
}

Instance *XGenericEventToInstance(
		Environment *theEnv,
		UDFContext *context,
		XGenericEvent *e,
		InstanceBuilder *ib,
		const char *name)
{
	IBSetDefclass(ib, "X-GENERIC-EVENT");
	IBPutSlotExternalAddress(ib, "c-pointer", CreateCExternalAddress(theEnv, e));
	IBPutSlotSymbol(ib, "type", XEventTypeToStr(e->type));
	IBPutSlotInteger(ib, "serial", e->serial);
	IBPutSlotSymbol(ib, "send-event", BoolToStr(e->send_event));
	IBPutSlotExternalAddress(ib, "display", CreateCExternalAddress(theEnv, e->display));
	IBPutSlotInteger(ib, "extension", e->extension);
	IBPutSlotInteger(ib, "evtype", e->evtype);
	return IBMake(ib, name);
}


Instance *XEventToInstance(
		Environment *theEnv,
		UDFContext *context,
		XEvent *e,
		InstanceBuilder *ib,
		const char *name)
{
	Instance *i;
	switch (e->type)
	{
		case KeyPress:
		case KeyRelease:
			i = XKeyEventToInstance(theEnv, context, &(e->xkey), ib, name);
			break;
		case ButtonPress:
		case ButtonRelease:
			i = XButtonEventToInstance(theEnv, context, &(e->xbutton), ib, name);
			break;
		case MotionNotify:
			i = XMotionEventToInstance(theEnv, context, &(e->xmotion), ib, name);
			break;
		case EnterNotify:
		case LeaveNotify:
			i = XCrossingEventToInstance(theEnv, context, &(e->xcrossing), ib, name);
			break;
		case FocusIn:
		case FocusOut:
			i = XFocusChangeEventToInstance(theEnv, context, &(e->xfocus), ib, name);
			break;
		case KeymapNotify:
			i = XKeymapEventToInstance(theEnv, context, e->xany.display, &(e->xkeymap), ib, name);
			break;
		case Expose:
			i = XExposeEventToInstance(theEnv, context, &(e->xexpose), ib, name);
			break;
		case GraphicsExpose:
			i = XGraphicsExposeEventToInstance(theEnv, context, &(e->xgraphicsexpose), ib, name);
			break;
		case NoExpose:
			i = XNoExposeEventToInstance(theEnv, context, &(e->xnoexpose), ib, name);
			break;
		case VisibilityNotify:
			i = XVisibilityEventToInstance(theEnv, context, &(e->xvisibility), ib, name);
			break;
		case CreateNotify:
			i = XCreateWindowEventToInstance(theEnv, context, &(e->xcreatewindow), ib, name);
			break;
		case DestroyNotify:
			i = XDestroyWindowEventToInstance(theEnv, context, &(e->xdestroywindow), ib, name);
			break;
		case UnmapNotify:
			i = XUnmapEventToInstance(theEnv, context, &(e->xunmap), ib, name);
			break;
		case MapNotify:
			i = XMapEventToInstance(theEnv, context, &(e->xmap), ib, name);
			break;
		case MapRequest:
			i = XMapRequestEventToInstance(theEnv, context, &(e->xmaprequest), ib, name);
			break;
		case ReparentNotify:
			i = XReparentEventToInstance(theEnv, context, &(e->xreparent), ib, name);
			break;
		case ConfigureNotify:
			i = XConfigureEventToInstance(theEnv, context, &(e->xconfigure), ib, name);
			break;
		case ConfigureRequest:
			i = XConfigureRequestEventToInstance(theEnv, context, &(e->xconfigurerequest), ib, name);
			break;
		case GravityNotify:
			i = XGravityEventToInstance(theEnv, context, &(e->xgravity), ib, name);
			break;
		case ResizeRequest:
			i = XResizeRequestEventToInstance(theEnv, context, &(e->xresizerequest), ib, name);
			break;
		case CirculateNotify:
			i = XCirculateEventToInstance(theEnv, context, &(e->xcirculate), ib, name);
			break;
		case CirculateRequest:
			i = XCirculateRequestEventToInstance(theEnv, context, &(e->xcirculaterequest), ib, name);
			break;
		case PropertyNotify:
			i = XPropertyEventToInstance(theEnv, context, &(e->xproperty), ib, name);
			break;
		case SelectionClear:
			i = XSelectionClearEventToInstance(theEnv, context, &(e->xselectionclear), ib, name);
			break;
		case SelectionRequest:
			i = XSelectionRequestEventToInstance(theEnv, context, &(e->xselectionrequest), ib, name);
			break;
		case SelectionNotify:
			i = XSelectionEventToInstance(theEnv, context, &(e->xselection), ib, name);
			break;
		case ColormapNotify:
			i = XColormapEventToInstance(theEnv, context, &(e->xcolormap), ib, name);
			break;
		case ClientMessage:
			i = XClientMessageEventToInstance(theEnv, context, &(e->xclient), ib, name);
			break;
		case MappingNotify:
			i = XMappingEventToInstance(theEnv, context, &(e->xmapping), ib, name);
			break;
		case GenericEvent:
			i = XGenericEventToInstance(theEnv, context, &(e->xgeneric), ib, name);
			break;
		default:
			WriteString(theEnv,STDERR,"Event Type ");
			WriteInteger(theEnv,STDERR,e->type);
			WriteString(theEnv,STDERR," not supported.\n");
			return NULL;
	}
	if (i == NULL)
	{
		WriteString(theEnv,STDERR,"Could not make instance for XEvent ");
		WriteString(theEnv,STDERR,XEventTypeToStr(e->type));
		ReportIBMakeError(theEnv);
		return NULL;
	}
	return i;
}

void XNextEventToInstanceFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	XEvent event;
	InstanceBuilder *ib;
	UDFValue theArg;
	const char *name;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	name = NULL;
	if (UDFHasNextArgument(context))
	{
		UDFNextArgument(context,LEXEME_BITS,&theArg);
		name = theArg.lexemeValue->contents;
	}

	XNextEvent(display, &event);

	ib = CreateInstanceBuilder(theEnv, NULL);

	returnValue->instanceValue = XEventToInstance(theEnv, context, &event, ib, name);
	if (returnValue->instanceValue == NULL)
	{
		WriteString(theEnv,STDERR,"Could not assert XEvent instance\n");
		ReportIBMakeError(theEnv);
	}
	IBDispose(ib);
}

void XPeekEventToInstanceFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	XEvent event;
	InstanceBuilder *ib;
	UDFValue theArg;
	const char *name;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	name = NULL;
	if (UDFHasNextArgument(context))
	{
		UDFNextArgument(context,LEXEME_BITS,&theArg);
		name = theArg.lexemeValue->contents;
	}

	XPeekEvent(display, &event);

	ib = CreateInstanceBuilder(theEnv, NULL);

	returnValue->instanceValue = XEventToInstance(theEnv, context, &event, ib, name);
	if (returnValue->instanceValue == NULL)
	{
		WriteString(theEnv,STDERR,"Could not assert XEvent instance\n");
		ReportIBMakeError(theEnv);
	}
	IBDispose(ib);
}

void XPopEventFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	XEvent event;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	XNextEvent(display, &event);
}

void XPeekEventFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	XEvent event;
	MultifieldBuilder *mb;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	XPeekEvent(display, &event);

	mb = CreateMultifieldBuilder(theEnv, 0);

	returnValue->multifieldValue = XEventToMultifield(theEnv, context, &event, mb);

	MBDispose(mb);
}

void XNextEventFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	XEvent event;
	MultifieldBuilder *mb;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	XNextEvent(display, &event);

	mb = CreateMultifieldBuilder(theEnv, 0);

	returnValue->multifieldValue = XEventToMultifield(theEnv, context, &event, mb);

	MBDispose(mb);
}

void XPeekEventToFactFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	XEvent event;
	FactBuilder *fb;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	XNextEvent(display, &event);

	fb = CreateFactBuilder(theEnv, NULL);

	returnValue->factValue = XEventToFact(theEnv, context, &event, fb);
	if (returnValue->factValue == NULL)
	{
		WriteString(theEnv,STDERR,"Could not assert XEvent fact\n");
		ReportFBAssertError(theEnv);
	}
	FBDispose(fb);
}

void XNextEventToFactFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	XEvent event;
	FactBuilder *fb;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	XNextEvent(display, &event);

	fb = CreateFactBuilder(theEnv, NULL);

	returnValue->factValue = XEventToFact(theEnv, context, &event, fb);
	if (returnValue->factValue == NULL)
	{
		WriteString(theEnv,STDERR,"Could not assert XEvent fact\n");
		ReportFBAssertError(theEnv);
	}
	FBDispose(fb);
}

void MultifieldToXKeyEvent(Environment *theEnv, Multifield *mf, XKeyEvent *event)
{
	if (mf->length >= 2 && mf->contents[1].header->type == INTEGER_TYPE)
	{
		event->window = mf->contents[1].integerValue->contents;
	}
	if (mf->length >= 3 && mf->contents[2].header->type == INTEGER_TYPE)
	{
		event->root = mf->contents[2].integerValue->contents;
	}
	if (mf->length >= 4 && mf->contents[2].header->type == INTEGER_TYPE)
	{
		event->subwindow = mf->contents[3].integerValue->contents;
	}
	if (mf->length >= 5 && mf->contents[4].header->type == INTEGER_TYPE)
	{
		event->time = mf->contents[4].integerValue->contents;
	}
	if (mf->length >= 6 && mf->contents[5].header->type == INTEGER_TYPE)
	{
		event->x = mf->contents[5].integerValue->contents;
	}
	if (mf->length >= 7 && mf->contents[6].header->type == INTEGER_TYPE)
	{
		event->y = mf->contents[6].integerValue->contents;
	}
	if (mf->length >= 8 && mf->contents[7].header->type == INTEGER_TYPE)
	{
		event->x_root = mf->contents[7].integerValue->contents;
	}
	if (mf->length >= 9 && mf->contents[8].header->type == INTEGER_TYPE)
	{
		event->y_root = mf->contents[8].integerValue->contents;
	}
	if (mf->length >= 10 && mf->contents[9].header->type == INTEGER_TYPE)
	{
		event->state = mf->contents[9].integerValue->contents;
	}
	if (mf->length >= 11 && mf->contents[10].header->type == INTEGER_TYPE)
	{
		event->keycode = mf->contents[10].integerValue->contents;
	}
	if (mf->length >= 12 && mf->contents[11].header->type == SYMBOL_TYPE)
	{
		event->same_screen = mf->contents[11].lexemeValue == theEnv->TrueSymbol;
	}
}

void MultifieldToXButtonEvent(Environment *theEnv, Multifield *mf, XButtonEvent *event)
{
	if (mf->length >= 2 && mf->contents[1].header->type == INTEGER_TYPE)
	{
		event->window = mf->contents[1].integerValue->contents;
	}
	if (mf->length >= 3 && mf->contents[2].header->type == INTEGER_TYPE)
	{
		event->root = mf->contents[2].integerValue->contents;
	}
	if (mf->length >= 4 && mf->contents[3].header->type == INTEGER_TYPE)
	{
		event->subwindow = mf->contents[3].integerValue->contents;
	}
	if (mf->length >= 5 && mf->contents[4].header->type == INTEGER_TYPE)
	{
		event->time = mf->contents[4].integerValue->contents;
	}
	if (mf->length >= 6 && mf->contents[5].header->type == INTEGER_TYPE)
	{
		event->x = mf->contents[5].integerValue->contents;
	}
	if (mf->length >= 7 && mf->contents[6].header->type == INTEGER_TYPE)
	{
		event->y = mf->contents[6].integerValue->contents;
	}
	if (mf->length >= 8 && mf->contents[7].header->type == INTEGER_TYPE)
	{
		event->x_root = mf->contents[7].integerValue->contents;
	}
	if (mf->length >= 9 && mf->contents[8].header->type == INTEGER_TYPE)
	{
		event->y_root = mf->contents[8].integerValue->contents;
	}
	if (mf->length >= 10 && mf->contents[9].header->type == INTEGER_TYPE)
	{
		event->state = mf->contents[9].integerValue->contents;
	}
	if (mf->length >= 11 && mf->contents[10].header->type == INTEGER_TYPE)
	{
		event->button = mf->contents[10].integerValue->contents;
	}
	if (mf->length >= 12 && mf->contents[11].header->type == SYMBOL_TYPE)
	{
		event->same_screen = mf->contents[11].lexemeValue == theEnv->TrueSymbol;
	}
}

void MultifieldToXMotionEvent(Environment *theEnv, Multifield *mf, XMotionEvent *event)
{
	if (mf->length >= 2 && mf->contents[1].header->type == INTEGER_TYPE)
	{
		event->window = mf->contents[1].integerValue->contents;
	}
	if (mf->length >= 3 && mf->contents[2].header->type == INTEGER_TYPE)
	{
		event->root = mf->contents[2].integerValue->contents;
	}
	if (mf->length >= 4 && mf->contents[3].header->type == INTEGER_TYPE)
	{
		event->subwindow = mf->contents[3].integerValue->contents;
	}
	if (mf->length >= 5 && mf->contents[4].header->type == INTEGER_TYPE)
	{
		event->time = mf->contents[4].integerValue->contents;
	}
	if (mf->length >= 6 && mf->contents[5].header->type == INTEGER_TYPE)
	{
		event->x = mf->contents[5].integerValue->contents;
	}
	if (mf->length >= 7 && mf->contents[6].header->type == INTEGER_TYPE)
	{
		event->y = mf->contents[6].integerValue->contents;
	}
	if (mf->length >= 8 && mf->contents[7].header->type == INTEGER_TYPE)
	{
		event->x_root = mf->contents[7].integerValue->contents;
	}
	if (mf->length >= 9 && mf->contents[8].header->type == INTEGER_TYPE)
	{
		event->y_root = mf->contents[8].integerValue->contents;
	}
	if (mf->length >= 10 && mf->contents[9].header->type == INTEGER_TYPE)
	{
		event->state = mf->contents[9].integerValue->contents;
	}
	if (mf->length >= 11 && mf->contents[10].header->type == SYMBOL_TYPE)
	{
		if (1 == strcmp(mf->contents[10].lexemeValue->contents, "NotifyNormal")) event->is_hint = NotifyNormal;
		else if (1 == strcmp(mf->contents[10].lexemeValue->contents, "NotifyHint")) event->is_hint = NotifyHint;
	}
	if (mf->length >= 12 && mf->contents[11].header->type == SYMBOL_TYPE)
	{
		event->same_screen = mf->contents[11].lexemeValue == theEnv->TrueSymbol;
	}
}

void MultifieldToXCrossingEvent(Environment *theEnv, Multifield *mf, XCrossingEvent *event)
{
	if (mf->length >= 2 && mf->contents[1].header->type == INTEGER_TYPE)
	{
		event->window = mf->contents[1].integerValue->contents;
	}
	if (mf->length >= 3 && mf->contents[2].header->type == INTEGER_TYPE)
	{
		event->root = mf->contents[2].integerValue->contents;
	}
	if (mf->length >= 4 && mf->contents[3].header->type == INTEGER_TYPE)
	{
		event->subwindow = mf->contents[3].integerValue->contents;
	}
	if (mf->length >= 5 && mf->contents[4].header->type == INTEGER_TYPE)
	{
		event->time = mf->contents[4].integerValue->contents;
	}
	if (mf->length >= 6 && mf->contents[5].header->type == INTEGER_TYPE)
	{
		event->x = mf->contents[5].integerValue->contents;
	}
	if (mf->length >= 7 && mf->contents[6].header->type == INTEGER_TYPE)
	{
		event->y = mf->contents[6].integerValue->contents;
	}
	if (mf->length >= 8 && mf->contents[7].header->type == INTEGER_TYPE)
	{
		event->x_root = mf->contents[7].integerValue->contents;
	}
	if (mf->length >= 9 && mf->contents[8].header->type == INTEGER_TYPE)
	{
		event->y_root = mf->contents[8].integerValue->contents;
	}
	if (mf->length >= 10 && mf->contents[9].header->type == SYMBOL_TYPE)
	{
		if (1 == strcmp(mf->contents[9].lexemeValue->contents, "NotifyNormal")) event->mode = NotifyNormal;
		else if (1 == strcmp(mf->contents[9].lexemeValue->contents, "NotifyGrab")) event->mode = NotifyGrab;
		else if (1 == strcmp(mf->contents[9].lexemeValue->contents, "NotifyUngrab")) event->mode = NotifyUngrab;
	}
	if (mf->length >= 11 && mf->contents[10].header->type == SYMBOL_TYPE)
	{
		if (1 == strcmp(mf->contents[10].lexemeValue->contents, "NotifyAncestor")) event->detail = NotifyAncestor;
		else if (1 == strcmp(mf->contents[10].lexemeValue->contents, "NotifyVirtual")) event->detail = NotifyVirtual;
		else if (1 == strcmp(mf->contents[10].lexemeValue->contents, "NotifyInferior")) event->detail = NotifyInferior;
		else if (1 == strcmp(mf->contents[10].lexemeValue->contents, "NotifyNonlinear")) event->detail = NotifyNonlinear;
		else if (1 == strcmp(mf->contents[10].lexemeValue->contents, "NotifyNonlinearVirtual")) event->detail = NotifyNonlinearVirtual;
		else if (1 == strcmp(mf->contents[10].lexemeValue->contents, "NotifyPointer")) event->detail = NotifyPointer;
		else if (1 == strcmp(mf->contents[10].lexemeValue->contents, "NotifyPointerRoot")) event->detail = NotifyPointerRoot;
		else if (1 == strcmp(mf->contents[10].lexemeValue->contents, "NotifyDetailNone")) event->detail = NotifyDetailNone;
	}
	if (mf->length >= 12 && mf->contents[11].header->type == SYMBOL_TYPE)
	{
		event->same_screen = mf->contents[11].lexemeValue == theEnv->TrueSymbol;
	}
	if (mf->length >= 13 && mf->contents[12].header->type == SYMBOL_TYPE)
	{
		event->focus = mf->contents[12].lexemeValue == theEnv->TrueSymbol;
	}
	if (mf->length >= 14 && mf->contents[13].header->type == INTEGER_TYPE)
	{
		event->state = mf->contents[13].integerValue->contents;
	}
}

void MultifieldToXFocusChangeEvent(Environment *theEnv, Multifield *mf, XFocusChangeEvent *event)
{
	if (mf->length >= 2 && mf->contents[1].header->type == INTEGER_TYPE)
	{
		event->window = mf->contents[1].integerValue->contents;
	}
	if (mf->length >= 3 && mf->contents[2].header->type == SYMBOL_TYPE)
	{
		if (1 == strcmp(mf->contents[2].lexemeValue->contents, "NotifyNormal")) event->mode = NotifyNormal;
		else if (1 == strcmp(mf->contents[2].lexemeValue->contents, "NotifyGrab")) event->mode = NotifyGrab;
		else if (1 == strcmp(mf->contents[2].lexemeValue->contents, "NotifyUngrab")) event->mode = NotifyUngrab;
	}

	if (mf->length >= 4 && mf->contents[3].header->type == SYMBOL_TYPE)
	{
		if (1 == strcmp(mf->contents[3].lexemeValue->contents, "NotifyAncestor")) event->detail = NotifyAncestor;
		else if (1 == strcmp(mf->contents[3].lexemeValue->contents, "NotifyVirtual")) event->detail = NotifyVirtual;
		else if (1 == strcmp(mf->contents[3].lexemeValue->contents, "NotifyInferior")) event->detail = NotifyInferior;
		else if (1 == strcmp(mf->contents[3].lexemeValue->contents, "NotifyNonlinear")) event->detail = NotifyNonlinear;
		else if (1 == strcmp(mf->contents[3].lexemeValue->contents, "NotifyNonlinearVirtual")) event->detail = NotifyNonlinearVirtual;
		else if (1 == strcmp(mf->contents[3].lexemeValue->contents, "NotifyPointer")) event->detail = NotifyPointer;
		else if (1 == strcmp(mf->contents[3].lexemeValue->contents, "NotifyPointerRoot")) event->detail = NotifyPointerRoot;
		else if (1 == strcmp(mf->contents[3].lexemeValue->contents, "NotifyDetailNone")) event->detail = NotifyDetailNone;
	}
}

void MultifieldToXKeymapEvent(Environment *theEnv, Multifield *mf, XKeymapEvent *event)
{
	int min_kc, max_kc;
	long bitIndex;
	if (mf->length >= 2 && mf->contents[1].header->type == EXTERNAL_ADDRESS_TYPE)
	{
		XDisplayKeycodes(mf->contents[1].externalAddressValue->contents, &min_kc, &max_kc);
		memset(event->key_vector, 1, sizeof(event->key_vector));
		if (mf->length >= 3 && mf->contents[2].header->type == INTEGER_TYPE)
		{
			event->window = mf->contents[2].integerValue->contents;
		}
		for (int x = 1; x < mf->length; x++)
		{
			if (mf->contents[x].header->type == SYMBOL_TYPE && mf->contents[x].lexemeValue == theEnv->TrueSymbol)
			{
				bitIndex = x + min_kc;
				event->key_vector[ bitIndex >> 3 ] |= (1 << (bitIndex & 7));
			}
			else
			if (mf->contents[x].header->type == INTEGER_TYPE && mf->contents[x].integerValue->contents >= 0 && mf->contents[x].integerValue->contents <= 255)
			{
				event->key_vector[ mf->contents[x].integerValue->contents >> 3 ] |= (1 << (mf->contents[x].integerValue->contents & 7));
			}
		}
	}
}

void MultifieldToXExposeEvent(Environment *theEnv, Multifield *mf, XExposeEvent *event)
{
	if (mf->length >= 2 && mf->contents[1].header->type == INTEGER_TYPE)
	{
		event->window = mf->contents[1].integerValue->contents;
	}
	if (mf->length >= 3 && mf->contents[2].header->type == INTEGER_TYPE)
	{
		event->x = mf->contents[2].integerValue->contents;
	}
	if (mf->length >= 4 && mf->contents[3].header->type == INTEGER_TYPE)
	{
		event->y = mf->contents[3].integerValue->contents;
	}
	if (mf->length >= 5 && mf->contents[4].header->type == INTEGER_TYPE)
	{
		event->width = mf->contents[4].integerValue->contents;
	}
	if (mf->length >= 6 && mf->contents[5].header->type == INTEGER_TYPE)
	{
		event->height = mf->contents[5].integerValue->contents;
	}
	if (mf->length >= 7 && mf->contents[6].header->type == INTEGER_TYPE)
	{
		event->count = mf->contents[6].integerValue->contents;
	}
}

void MultifieldToXGraphicsExposeEvent(Environment *theEnv, Multifield *mf, XGraphicsExposeEvent *event)
{
	if (mf->length >= 2 && mf->contents[1].header->type == INTEGER_TYPE)
	{
		event->drawable = mf->contents[1].integerValue->contents;
	}
	if (mf->length >= 3 && mf->contents[2].header->type == INTEGER_TYPE)
	{
		event->x = mf->contents[2].integerValue->contents;
	}
	if (mf->length >= 4 && mf->contents[3].header->type == INTEGER_TYPE)
	{
		event->y = mf->contents[3].integerValue->contents;
	}
	if (mf->length >= 5 && mf->contents[4].header->type == INTEGER_TYPE)
	{
		event->width = mf->contents[4].integerValue->contents;
	}
	if (mf->length >= 6 && mf->contents[5].header->type == INTEGER_TYPE)
	{
		event->height = mf->contents[5].integerValue->contents;
	}
	if (mf->length >= 7 && mf->contents[6].header->type == INTEGER_TYPE)
	{
		event->count = mf->contents[6].integerValue->contents;
	}
	if (mf->length >= 8 && mf->contents[7].header->type == INTEGER_TYPE)
	{
		event->major_code = mf->contents[7].integerValue->contents;
	}
	if (mf->length >= 9 && mf->contents[8].header->type == INTEGER_TYPE)
	{
		event->minor_code = mf->contents[8].integerValue->contents;
	}
}

void MultifieldToXNoExposeEvent(Environment *theEnv, Multifield *mf, XNoExposeEvent *event)
{
	if (mf->length >= 2 && mf->contents[1].header->type == INTEGER_TYPE)
	{
		event->drawable = mf->contents[1].integerValue->contents;
	}
	if (mf->length >= 3 && mf->contents[2].header->type == INTEGER_TYPE)
	{
		event->major_code = mf->contents[2].integerValue->contents;
	}
	if (mf->length >= 4 && mf->contents[3].header->type == INTEGER_TYPE)
	{
		event->minor_code = mf->contents[3].integerValue->contents;
	}
}

void MultifieldToXVisibilityEvent(Environment *theEnv, Multifield *mf, XVisibilityEvent *event)
{
	if (mf->length >= 2 && mf->contents[1].header->type == INTEGER_TYPE)
	{
		event->window = mf->contents[1].integerValue->contents;
	}
	if (mf->length >= 3 && mf->contents[2].header->type == SYMBOL_TYPE)
	{
		if (0 == strcmp(mf->contents[2].lexemeValue->contents, "VisibilityUnobscured")) event->state = VisibilityUnobscured;
		else if (0 == strcmp(mf->contents[2].lexemeValue->contents, "VisibilityPartiallyObscured")) event->state = VisibilityPartiallyObscured;
		else if (0 == strcmp(mf->contents[2].lexemeValue->contents, "VisibilityFullyObscured")) event->state = VisibilityFullyObscured;
	}
}

void MultifieldToXCreateWindowEvent(Environment *theEnv, Multifield *mf, XCreateWindowEvent *event)
{
	if (mf->length >= 2 && mf->contents[1].header->type == INTEGER_TYPE)
	{
		event->parent = mf->contents[1].integerValue->contents;
	}
	if (mf->length >= 3 && mf->contents[2].header->type == INTEGER_TYPE)
	{
		event->window = mf->contents[2].integerValue->contents;
	}
	if (mf->length >= 4 && mf->contents[3].header->type == INTEGER_TYPE)
	{
		event->x = mf->contents[3].integerValue->contents;
	}
	if (mf->length >= 5 && mf->contents[4].header->type == INTEGER_TYPE)
	{
		event->y = mf->contents[4].integerValue->contents;
	}
	if (mf->length >= 6 && mf->contents[5].header->type == INTEGER_TYPE)
	{
		event->width = mf->contents[5].integerValue->contents;
	}
	if (mf->length >= 7 && mf->contents[6].header->type == INTEGER_TYPE)
	{
		event->height = mf->contents[6].integerValue->contents;
	}
	if (mf->length >= 8 && mf->contents[7].header->type == INTEGER_TYPE)
	{
		event->border_width = mf->contents[7].integerValue->contents;
	}
	if (mf->length >= 9 && mf->contents[8].header->type == SYMBOL_TYPE)
	{
		event->override_redirect = mf->contents[8].lexemeValue == theEnv->TrueSymbol; 
	}
}

void MultifieldToXDestroyWindowEvent(Environment *theEnv, Multifield *mf, XDestroyWindowEvent *event)
{
	if (mf->length >= 2 && mf->contents[1].header->type == INTEGER_TYPE)
	{
		event->event = mf->contents[1].integerValue->contents;
	}
	if (mf->length >= 3 && mf->contents[2].header->type == INTEGER_TYPE)
	{
		event->window = mf->contents[2].integerValue->contents;
	}
}

void MultifieldToXUnmapEvent(Environment *theEnv, Multifield *mf, XUnmapEvent *event)
{
	if (mf->length >= 2 && mf->contents[1].header->type == INTEGER_TYPE)
	{
		event->event = mf->contents[1].integerValue->contents;
	}
	if (mf->length >= 3 && mf->contents[2].header->type == INTEGER_TYPE)
	{
		event->window = mf->contents[2].integerValue->contents;
	}
	if (mf->length >= 4 && mf->contents[3].header->type == SYMBOL_TYPE)
	{
		event->from_configure = mf->contents[3].lexemeValue == theEnv->TrueSymbol; 
	}
}

void MultifieldToXMapEvent(Environment *theEnv, Multifield *mf, XMapEvent *event)
{
	if (mf->length >= 2 && mf->contents[1].header->type == INTEGER_TYPE)
	{
		event->event = mf->contents[1].integerValue->contents;
	}
	if (mf->length >= 3 && mf->contents[2].header->type == INTEGER_TYPE)
	{
		event->window = mf->contents[2].integerValue->contents;
	}
	if (mf->length >= 4 && mf->contents[3].header->type == SYMBOL_TYPE)
	{
		event->override_redirect = mf->contents[3].lexemeValue == theEnv->TrueSymbol; 
	}
}

void MultifieldToXMapRequestEvent(Environment *theEnv, Multifield *mf, XMapRequestEvent *event)
{
	if (mf->length >= 2 && mf->contents[1].header->type == INTEGER_TYPE)
	{
		event->parent = mf->contents[1].integerValue->contents;
	}
	if (mf->length >= 3 && mf->contents[2].header->type == INTEGER_TYPE)
	{
		event->window = mf->contents[2].integerValue->contents;
	}
}


void MultifieldToXReparentEvent(Environment *theEnv, Multifield *mf, XReparentEvent *event)
{
	if (mf->length >= 2 && mf->contents[1].header->type == INTEGER_TYPE)
	{
		event->event = mf->contents[1].integerValue->contents;
	}
	if (mf->length >= 3 && mf->contents[2].header->type == INTEGER_TYPE)
	{
		event->window = mf->contents[2].integerValue->contents;
	}
	if (mf->length >= 4 && mf->contents[3].header->type == INTEGER_TYPE)
	{
		event->parent = mf->contents[3].integerValue->contents;
	}
	if (mf->length >= 5 && mf->contents[4].header->type == INTEGER_TYPE)
	{
		event->x = mf->contents[4].integerValue->contents;
	}
	if (mf->length >= 6 && mf->contents[5].header->type == INTEGER_TYPE)
	{
		event->y = mf->contents[5].integerValue->contents;
	}
	if (mf->length >= 7 && mf->contents[6].header->type == SYMBOL_TYPE)
	{
		event->override_redirect = mf->contents[6].lexemeValue == theEnv->TrueSymbol; 
	}
}

void MultifieldToXConfigureEvent(Environment *theEnv, Multifield *mf, XConfigureEvent *event)
{
	if (mf->length >= 2 && mf->contents[1].header->type == INTEGER_TYPE)
	{
		event->event = mf->contents[1].integerValue->contents;
	}
	if (mf->length >= 3 && mf->contents[2].header->type == INTEGER_TYPE)
	{
		event->window = mf->contents[2].integerValue->contents;
	}
	if (mf->length >= 4 && mf->contents[2].header->type == INTEGER_TYPE)
	{
		event->x = mf->contents[3].integerValue->contents;
	}
	if (mf->length >= 5 && mf->contents[4].header->type == INTEGER_TYPE)
	{
		event->y = mf->contents[4].integerValue->contents;
	}
	if (mf->length >= 6 && mf->contents[5].header->type == INTEGER_TYPE)
	{
		event->width = mf->contents[5].integerValue->contents;
	}
	if (mf->length >= 7 && mf->contents[6].header->type == INTEGER_TYPE)
	{
		event->height = mf->contents[6].integerValue->contents;
	}
	if (mf->length >= 8 && mf->contents[7].header->type == INTEGER_TYPE)
	{
		event->border_width = mf->contents[7].integerValue->contents;
	}
	if (mf->length >= 9 && mf->contents[8].header->type == INTEGER_TYPE)
	{
		event->above = mf->contents[8].integerValue->contents;
	}
	if (mf->length >= 10 && mf->contents[9].header->type == SYMBOL_TYPE)
	{
		event->override_redirect = mf->contents[9].lexemeValue == theEnv->TrueSymbol; 
	}
}

void MultifieldToXGravityEvent(Environment *theEnv, Multifield *mf, XGravityEvent *event)
{
	if (mf->length >= 2 && mf->contents[1].header->type == INTEGER_TYPE)
	{
		event->event = mf->contents[1].integerValue->contents;
	}
	if (mf->length >= 3 && mf->contents[2].header->type == INTEGER_TYPE)
	{
		event->window = mf->contents[2].integerValue->contents;
	}
	if (mf->length >= 4 && mf->contents[3].header->type == INTEGER_TYPE)
	{
		event->x = mf->contents[3].integerValue->contents;
	}
	if (mf->length >= 5 && mf->contents[4].header->type == INTEGER_TYPE)
	{
		event->y = mf->contents[4].integerValue->contents;
	}
}

void MultifieldToXResizeRequestEvent(Environment *theEnv, Multifield *mf, XResizeRequestEvent *event)
{
	if (mf->length >= 2 && mf->contents[1].header->type == INTEGER_TYPE)
	{
		event->window = mf->contents[1].integerValue->contents;
	}
	if (mf->length >= 3 && mf->contents[2].header->type == INTEGER_TYPE)
	{
		event->width = mf->contents[2].integerValue->contents;
	}
	if (mf->length >= 4 && mf->contents[3].header->type == INTEGER_TYPE)
	{
		event->height = mf->contents[3].integerValue->contents;
	}
}

void MultifieldToXConfigureRequestEvent(Environment *theEnv, Multifield *mf, XConfigureRequestEvent *event)
{
	if (mf->length >= 2 && mf->contents[1].header->type == INTEGER_TYPE)
	{
		event->parent = mf->contents[1].integerValue->contents;
	}
	if (mf->length >= 3 && mf->contents[2].header->type == INTEGER_TYPE)
	{
		event->window = mf->contents[2].integerValue->contents;
	}
	if (mf->length >= 4 && mf->contents[3].header->type == INTEGER_TYPE)
	{
		event->x = mf->contents[3].integerValue->contents;
	}
	if (mf->length >= 5 && mf->contents[4].header->type == INTEGER_TYPE)
	{
		event->y = mf->contents[4].integerValue->contents;
	}
	if (mf->length >= 6 && mf->contents[5].header->type == INTEGER_TYPE)
	{
		event->width = mf->contents[5].integerValue->contents;
	}
	if (mf->length >= 7 && mf->contents[6].header->type == INTEGER_TYPE)
	{
		event->height = mf->contents[6].integerValue->contents;
	}
	if (mf->length >= 8 && mf->contents[7].header->type == INTEGER_TYPE)
	{
		event->border_width = mf->contents[7].integerValue->contents;
	}
	if (mf->length >= 9 && mf->contents[8].header->type == INTEGER_TYPE)
	{
		event->above = mf->contents[8].integerValue->contents;
	}
	if (mf->length >= 10 && mf->contents[9].header->type == SYMBOL_TYPE)
	{
		if (0 == strcmp(mf->contents[9].lexemeValue->contents, "Above")) event->detail = Above;
		else if (0 == strcmp(mf->contents[9].lexemeValue->contents, "Below")) event->detail = Below;
		else if (0 == strcmp(mf->contents[9].lexemeValue->contents, "TopIf")) event->detail = TopIf;
		else if (0 == strcmp(mf->contents[9].lexemeValue->contents, "BottomIf")) event->detail = BottomIf;
		else if (0 == strcmp(mf->contents[9].lexemeValue->contents, "Opposite")) event->detail = Opposite;
	}
	if (mf->length >= 11 && mf->contents[10].header->type == INTEGER_TYPE)
	{
		event->value_mask = mf->contents[10].integerValue->contents;
	}
}

void MultifieldToXCirculateEvent(Environment *theEnv, Multifield *mf, XCirculateEvent *event)
{
	if (mf->length >= 2 && mf->contents[1].header->type == INTEGER_TYPE)
	{
		event->event = mf->contents[1].integerValue->contents;
	}
	if (mf->length >= 3 && mf->contents[2].header->type == INTEGER_TYPE)
	{
		event->window = mf->contents[2].integerValue->contents;
	}
	if (mf->length >= 4 && mf->contents[3].header->type == SYMBOL_TYPE)
	{
		if (0 == strcmp(mf->contents[3].lexemeValue->contents, "PlaceOnTop")) event->place = PlaceOnTop;
		else if (0 == strcmp(mf->contents[3].lexemeValue->contents, "PlaceOnBottom")) event->place = PlaceOnBottom;
	}
}

void MultifieldToXCirculateRequestEvent(Environment *theEnv, Multifield *mf, XCirculateRequestEvent *event)
{
	if (mf->length >= 2 && mf->contents[1].header->type == INTEGER_TYPE)
	{
		event->parent = mf->contents[1].integerValue->contents;
	}
	if (mf->length >= 3 && mf->contents[2].header->type == INTEGER_TYPE)
	{
		event->window = mf->contents[2].integerValue->contents;
	}
	if (mf->length >= 4 && mf->contents[3].header->type == SYMBOL_TYPE)
	{
		if (0 == strcmp(mf->contents[3].lexemeValue->contents, "PlaceOnTop")) event->place = PlaceOnTop;
		else if (0 == strcmp(mf->contents[3].lexemeValue->contents, "PlaceOnBottom")) event->place = PlaceOnBottom;
	}
}

void MultifieldToXPropertyEvent(Environment *theEnv, Multifield *mf, XPropertyEvent *event)
{
	if (mf->length >= 2 && mf->contents[1].header->type == INTEGER_TYPE)
	{
		event->window = mf->contents[1].integerValue->contents;
	}
	if (mf->length >= 3 && mf->contents[2].header->type == INTEGER_TYPE)
	{
		event->atom = mf->contents[2].integerValue->contents;
	}
	if (mf->length >= 4 && mf->contents[3].header->type == INTEGER_TYPE)
	{
		event->time = mf->contents[3].integerValue->contents;
	}
	if (mf->length >= 5 && mf->contents[4].header->type == SYMBOL_TYPE)
	{
		if (0 == strcmp(mf->contents[4].lexemeValue->contents, "PropertyNewValue")) event->state = PropertyNewValue;
		else if (0 == strcmp(mf->contents[4].lexemeValue->contents, "PropertyDelete")) event->state = PropertyDelete;
	}
}

void MultifieldToXSelectionClearEvent(Environment *theEnv, Multifield *mf, XSelectionClearEvent *event)
{
	if (mf->length >= 2 && mf->contents[1].header->type == INTEGER_TYPE)
	{
		event->window = mf->contents[1].integerValue->contents;
	}
	if (mf->length >= 3 && mf->contents[2].header->type == INTEGER_TYPE)
	{
		event->selection = mf->contents[2].integerValue->contents;
	}
	if (mf->length >= 4 && mf->contents[3].header->type == INTEGER_TYPE)
	{
		event->time = mf->contents[3].integerValue->contents;
	}
}

void MultifieldToXSelectionRequestEvent(Environment *theEnv, Multifield *mf, XSelectionRequestEvent *event)
{
	if (mf->length >= 2 && mf->contents[1].header->type == INTEGER_TYPE)
	{
		event->owner = mf->contents[1].integerValue->contents;
	}
	if (mf->length >= 3 && mf->contents[2].header->type == INTEGER_TYPE)
	{
		event->requestor = mf->contents[2].integerValue->contents;
	}
	if (mf->length >= 4 && mf->contents[3].header->type == INTEGER_TYPE)
	{
		event->selection = mf->contents[3].integerValue->contents;
	}
	if (mf->length >= 5 && mf->contents[4].header->type == INTEGER_TYPE)
	{
		event->target = mf->contents[4].integerValue->contents;
	}
	if (mf->length >= 6 && mf->contents[5].header->type == INTEGER_TYPE)
	{
		event->property = mf->contents[5].integerValue->contents;
	}
	if (mf->length >= 7 && mf->contents[6].header->type == INTEGER_TYPE)
	{
		event->time = mf->contents[6].integerValue->contents;
	}
}

void MultifieldToXSelectionEvent(Environment *theEnv, Multifield *mf, XSelectionEvent *event)
{
	if (mf->length >= 2 && mf->contents[1].header->type == INTEGER_TYPE)
	{
		event->requestor = mf->contents[1].integerValue->contents;
	}
	if (mf->length >= 3 && mf->contents[2].header->type == INTEGER_TYPE)
	{
		event->selection = mf->contents[2].integerValue->contents;
	}
	if (mf->length >= 4 && mf->contents[3].header->type == INTEGER_TYPE)
	{
		event->target = mf->contents[3].integerValue->contents;
	}
	if (mf->length >= 5 && mf->contents[4].header->type == INTEGER_TYPE)
	{
		event->property = mf->contents[4].integerValue->contents;
	}
	if (mf->length >= 6 && mf->contents[5].header->type == INTEGER_TYPE)
	{
		event->time = mf->contents[5].integerValue->contents;
	}
}

void MultifieldToXColormapEvent(Environment *theEnv, Multifield *mf, XColormapEvent *event)
{
	if (mf->length >= 2 && mf->contents[1].header->type == INTEGER_TYPE)
	{
		event->window = mf->contents[1].integerValue->contents;
	}
	if (mf->length >= 3 && mf->contents[2].header->type == INTEGER_TYPE)
	{
		event->colormap = mf->contents[2].integerValue->contents;
	}
	if (mf->length >= 4 && mf->contents[3].header->type == SYMBOL_TYPE)
	{
		event->new = mf->contents[3].lexemeValue == theEnv->TrueSymbol;
	}
	if (mf->length >= 5 && mf->contents[4].header->type == SYMBOL_TYPE)
	{
		if (0 == strcmp(mf->contents[4].lexemeValue->contents, "ColormapInstalled")) event->state = ColormapInstalled;
		else if (0 == strcmp(mf->contents[4].lexemeValue->contents, "ColormapUninstalled")) event->state = ColormapUninstalled;
	}
}

void MultifieldToXClientMessageEvent(Environment *theEnv, Multifield *mf, XClientMessageEvent *event)
{
	if (mf->length >= 2 && mf->contents[1].header->type == INTEGER_TYPE)
	{
		event->window = mf->contents[1].integerValue->contents;
	}
	if (mf->length >= 3 && mf->contents[2].header->type == INTEGER_TYPE)
	{
		event->message_type = mf->contents[2].integerValue->contents;
	}
	if (mf->length >= 4 && mf->contents[3].header->type == INTEGER_TYPE)
	{
		event->format = mf->contents[3].integerValue->contents;
	}
	if (mf->length >= 5)
	{
		if (event->format == 8 && mf->length >= 28)
		{
			for (int x = 0; x < 20; x++)
			{
				if (mf->contents[3 + x].header->type == INTEGER_TYPE)
				event->data.b[x] = mf->contents[3 + x].integerValue->contents;
			}
		}
		else if (event->format == 16)
		{
			for (int x = 0; x < 10; x++)
			{
				if (mf->contents[3 + x].header->type == INTEGER_TYPE)
				event->data.s[x] = mf->contents[3 + x].integerValue->contents;
			}
		}
		else if (event->format == 32)
		{
			for (int x = 0; x < 5; x++)
			{
				if (mf->contents[3 + x].header->type == INTEGER_TYPE)
				event->data.l[x] = mf->contents[3 + x].integerValue->contents;
			}
		}
	}
}

void MultifieldToXMappingEvent(Environment *theEnv, Multifield *mf, XMappingEvent *event)
{
	if (mf->length >= 2 && mf->contents[1].header->type == INTEGER_TYPE)
	{
		event->window = mf->contents[1].integerValue->contents;
	}
	if (mf->length >= 3 && mf->contents[2].header->type == SYMBOL_TYPE)
	{
		if (0 == strcmp(mf->contents[2].lexemeValue->contents, "MappingModifier")) event->request = MappingModifier;
		else if (0 == strcmp(mf->contents[2].lexemeValue->contents, "MappingKeyboard")) event->request = MappingKeyboard;
		else if (0 == strcmp(mf->contents[2].lexemeValue->contents, "MappingPointer")) event->request = MappingPointer;
	}
	if (mf->length >= 4 && mf->contents[3].header->type == INTEGER_TYPE)
	{
		event->first_keycode = mf->contents[3].integerValue->contents;
	}
	if (mf->length >= 5 && mf->contents[4].header->type == INTEGER_TYPE)
	{
		event->count = mf->contents[4].integerValue->contents;
	}
}

void MultifieldToXGenericEvent(Environment *theEnv, Multifield *mf, XGenericEvent *event)
{
	if (mf->length >= 2 && mf->contents[1].header->type == INTEGER_TYPE)
	{
		event->extension = mf->contents[1].integerValue->contents;
	}
	if (mf->length >= 3 && mf->contents[2].header->type == INTEGER_TYPE)
	{
		event->evtype = mf->contents[2].integerValue->contents;
	}
}

void MultifieldToXEvent(Environment *theEnv, Multifield *mf, XEvent *event)
{
	if (mf->length > 0 && mf->contents[0].header->type == SYMBOL_TYPE)
	{
		if (0 == strcmp(mf->contents[0].lexemeValue->contents, "KeyPress"))
		{
			event->xkey.type = KeyPress;
			MultifieldToXKeyEvent(theEnv, mf, &(event->xkey));
		}
		else
		if (0 == strcmp(mf->contents[0].lexemeValue->contents, "KeyRelease"))
		{
			event->xkey.type = KeyRelease;
			MultifieldToXKeyEvent(theEnv, mf, &(event->xkey));
		}
		else
		if (0 == strcmp(mf->contents[0].lexemeValue->contents, "ButtonPress"))
		{
			event->xbutton.type = ButtonPress;
			MultifieldToXButtonEvent(theEnv, mf, &(event->xbutton));
		}
		else
		if (0 == strcmp(mf->contents[0].lexemeValue->contents, "ButtonRelease"))
		{
			event->xbutton.type = ButtonRelease;
			MultifieldToXButtonEvent(theEnv, mf, &(event->xbutton));
		}
		else
		if (0 == strcmp(mf->contents[0].lexemeValue->contents, "MotionNotify"))
		{
			event->xmotion.type = ButtonRelease;
			MultifieldToXMotionEvent(theEnv, mf, &(event->xmotion));
		}
		else
		if (0 == strcmp(mf->contents[0].lexemeValue->contents, "EnterNotify"))
		{
			event->xcrossing.type = EnterNotify;
			MultifieldToXCrossingEvent(theEnv, mf, &(event->xcrossing));
		}
		else
		if (0 == strcmp(mf->contents[0].lexemeValue->contents, "LeaveNotify"))
		{
			event->xcrossing.type = LeaveNotify;
			MultifieldToXCrossingEvent(theEnv, mf, &(event->xcrossing));
		}
		else
		if (0 == strcmp(mf->contents[0].lexemeValue->contents, "FocusIn"))
		{
			event->xfocus.type = FocusIn;
			MultifieldToXFocusChangeEvent(theEnv, mf, &(event->xfocus));
		}
		else
		if (0 == strcmp(mf->contents[0].lexemeValue->contents, "FocusOut"))
		{
			event->xfocus.type = FocusOut;
			MultifieldToXFocusChangeEvent(theEnv, mf, &(event->xfocus));
		}
		else
		if (0 == strcmp(mf->contents[0].lexemeValue->contents, "KeymapNotify"))
		{
			event->xkeymap.type = KeymapNotify;
			MultifieldToXKeymapEvent(theEnv, mf, &(event->xkeymap));
		}
		else
		if (0 == strcmp(mf->contents[0].lexemeValue->contents, "Expose"))
		{
			event->xexpose.type = Expose;
			MultifieldToXExposeEvent(theEnv, mf, &(event->xexpose));
		}
		else
		if (0 == strcmp(mf->contents[0].lexemeValue->contents, "GraphicsExpose"))
		{
			event->xgraphicsexpose.type = GraphicsExpose;
			MultifieldToXGraphicsExposeEvent(theEnv, mf, &(event->xgraphicsexpose));
		}
		else
		if (0 == strcmp(mf->contents[0].lexemeValue->contents, "NoExpose"))
		{
			event->xnoexpose.type = NoExpose;
			MultifieldToXNoExposeEvent(theEnv, mf, &(event->xnoexpose));
		}
		else
		if (0 == strcmp(mf->contents[0].lexemeValue->contents, "VisibilityNotify"))
		{
			event->xvisibility.type = VisibilityNotify;
			MultifieldToXVisibilityEvent(theEnv, mf, &(event->xvisibility));
		}
		else
		if (0 == strcmp(mf->contents[0].lexemeValue->contents, "CreateNotify"))
		{
			event->xcreatewindow.type = CreateNotify;
			MultifieldToXCreateWindowEvent(theEnv, mf, &(event->xcreatewindow));
		}
		else
		if (0 == strcmp(mf->contents[0].lexemeValue->contents, "DestroyNotify"))
		{
			event->xdestroywindow.type = DestroyNotify;
			MultifieldToXDestroyWindowEvent(theEnv, mf, &(event->xdestroywindow));
		}
		else
		if (0 == strcmp(mf->contents[0].lexemeValue->contents, "UnmapNotify"))
		{
			event->xunmap.type = UnmapNotify;
			MultifieldToXUnmapEvent(theEnv, mf, &(event->xunmap));
		}
		else
		if (0 == strcmp(mf->contents[0].lexemeValue->contents, "MapNotify"))
		{
			event->xmap.type = MapNotify;
			MultifieldToXMapEvent(theEnv, mf, &(event->xmap));
		}
		else
		if (0 == strcmp(mf->contents[0].lexemeValue->contents, "MapRequest"))
		{
			event->xmaprequest.type = MapRequest;
			MultifieldToXMapRequestEvent(theEnv, mf, &(event->xmaprequest));
		}
		else
		if (0 == strcmp(mf->contents[0].lexemeValue->contents, "ReparentNotify"))
		{
			event->xreparent.type = ReparentNotify;
			MultifieldToXReparentEvent(theEnv, mf, &(event->xreparent));
		}
		else
		if (0 == strcmp(mf->contents[0].lexemeValue->contents, "ConfigureNotify"))
		{
			event->xconfigure.type = ConfigureNotify;
			MultifieldToXConfigureEvent(theEnv, mf, &(event->xconfigure));
		}
		else
		if (0 == strcmp(mf->contents[0].lexemeValue->contents, "ConfigureRequest"))
		{
			event->xconfigurerequest.type = ConfigureRequest;
			MultifieldToXConfigureRequestEvent(theEnv, mf, &(event->xconfigurerequest));
		}
		else
		if (0 == strcmp(mf->contents[0].lexemeValue->contents, "GravityNotify"))
		{
			event->xgravity.type = GravityNotify;
			MultifieldToXGravityEvent(theEnv, mf, &(event->xgravity));
		}
		else
		if (0 == strcmp(mf->contents[0].lexemeValue->contents, "ResizeRequest"))
		{
			event->xresizerequest.type = ResizeRequest;
			MultifieldToXResizeRequestEvent(theEnv, mf, &(event->xresizerequest));
		}
		else
		if (0 == strcmp(mf->contents[0].lexemeValue->contents, "CirculateNotify"))
		{
			event->xcirculate.type = CirculateNotify;
			MultifieldToXCirculateEvent(theEnv, mf, &(event->xcirculate));
		}
		else
		if (0 == strcmp(mf->contents[0].lexemeValue->contents, "CirculateRequest"))
		{
			event->xcirculaterequest.type = CirculateRequest;
			MultifieldToXCirculateRequestEvent(theEnv, mf, &(event->xcirculaterequest));
		}
		else
		if (0 == strcmp(mf->contents[0].lexemeValue->contents, "PropertyNotify"))
		{
			event->xproperty.type = PropertyNotify;
			MultifieldToXPropertyEvent(theEnv, mf, &(event->xproperty));
		}
		else
		if (0 == strcmp(mf->contents[0].lexemeValue->contents, "SelectionClear"))
		{
			event->xselectionclear.type = SelectionClear;
			MultifieldToXSelectionClearEvent(theEnv, mf, &(event->xselectionclear));
		}
		else
		if (0 == strcmp(mf->contents[0].lexemeValue->contents, "SelectionRequest"))
		{
			event->xselectionrequest.type = SelectionRequest;
			MultifieldToXSelectionRequestEvent(theEnv, mf, &(event->xselectionrequest));
		}
		else
		if (0 == strcmp(mf->contents[0].lexemeValue->contents, "SelectionNotify"))
		{
			event->xselection.type = SelectionNotify;
			MultifieldToXSelectionEvent(theEnv, mf, &(event->xselection));
		}
		else
		if (0 == strcmp(mf->contents[0].lexemeValue->contents, "ColormapNotify"))
		{
			event->xcolormap.type = ColormapNotify;
			MultifieldToXColormapEvent(theEnv, mf, &(event->xcolormap));
		}
		else
		if (0 == strcmp(mf->contents[0].lexemeValue->contents, "ClientMessage"))
		{
			event->xclient.type = ClientMessage;
			MultifieldToXClientMessageEvent(theEnv, mf, &(event->xclient));
		}
		else
		if (0 == strcmp(mf->contents[0].lexemeValue->contents, "MappingNotify"))
		{
			event->xmapping.type = MappingNotify;
			MultifieldToXMappingEvent(theEnv, mf, &(event->xmapping));
		}
		else
		if (0 == strcmp(mf->contents[0].lexemeValue->contents, "GenericEvent"))
		{
			event->xgeneric.type = GenericEvent;
			MultifieldToXGenericEvent(theEnv, mf, &(event->xgeneric));
		}
		else
		{
			WriteString(theEnv, STDERR, "Event '");
			WriteString(theEnv, STDERR, mf->contents[0].lexemeValue->contents);
			WriteString(theEnv, STDERR, "' not supported.\n");
		}
	}
	else
	{
		WriteString(theEnv, STDERR, "First value in multifield sent to x-send-event as last argument must be a symbol");
	}
}

void FactToXKeyEvent(Environment *theEnv, Fact *f, XKeyEvent *event)
{
	CLIPSValue out;
	GetFactSlot(f, "window", &out);
	event->window = out.integerValue->contents;
	GetFactSlot(f, "root", &out);
	event->root = out.integerValue->contents;
	GetFactSlot(f, "subwindow", &out);
	event->subwindow = out.integerValue->contents;
	GetFactSlot(f, "time", &out);
	event->time = out.integerValue->contents;
	GetFactSlot(f, "x", &out);
	event->x = out.integerValue->contents;
	GetFactSlot(f, "y", &out);
	event->y = out.integerValue->contents;
	GetFactSlot(f, "x_root", &out);
	event->x_root = out.integerValue->contents;
	GetFactSlot(f, "y_root", &out);
	event->y_root = out.integerValue->contents;
	GetFactSlot(f, "state", &out);
	event->state = out.integerValue->contents;
	GetFactSlot(f, "keycode", &out);
	event->keycode = out.integerValue->contents;
	GetFactSlot(f, "same-screen", &out);
	event->same_screen = out.lexemeValue == theEnv->TrueSymbol;
}

void FactToXButtonEvent(Environment *theEnv, Fact *f, XButtonEvent *event)
{
	CLIPSValue out;
	GetFactSlot(f, "window", &out);
	event->window = out.integerValue->contents;
	GetFactSlot(f, "root", &out);
	event->root = out.integerValue->contents;
	GetFactSlot(f, "subwindow", &out);
	event->subwindow = out.integerValue->contents;
	GetFactSlot(f, "time", &out);
	event->time = out.integerValue->contents;
	GetFactSlot(f, "x", &out);
	event->x = out.integerValue->contents;
	GetFactSlot(f, "y", &out);
	event->y = out.integerValue->contents;
	GetFactSlot(f, "x_root", &out);
	event->x_root = out.integerValue->contents;
	GetFactSlot(f, "y_root", &out);
	event->y_root = out.integerValue->contents;
	GetFactSlot(f, "state", &out);
	event->state = out.integerValue->contents;
	GetFactSlot(f, "button", &out);
	event->button = out.integerValue->contents;
	GetFactSlot(f, "same-screen", &out);
	event->same_screen = out.lexemeValue == theEnv->TrueSymbol;
}

void FactToXMotionEvent(Environment *theEnv, Fact *f, XMotionEvent *event)
{
	CLIPSValue out;
	GetFactSlot(f, "window", &out);
	event->window = out.integerValue->contents;
	GetFactSlot(f, "root", &out);
	event->root = out.integerValue->contents;
	GetFactSlot(f, "subwindow", &out);
	event->subwindow = out.integerValue->contents;
	GetFactSlot(f, "time", &out);
	event->time = out.integerValue->contents;
	GetFactSlot(f, "x", &out);
	event->x = out.integerValue->contents;
	GetFactSlot(f, "y", &out);
	event->y = out.integerValue->contents;
	GetFactSlot(f, "x_root", &out);
	event->x_root = out.integerValue->contents;
	GetFactSlot(f, "y_root", &out);
	event->y_root = out.integerValue->contents;
	GetFactSlot(f, "state", &out);
	event->state = out.integerValue->contents;
	GetFactSlot(f, "is-hint", &out);
	if (0 == strcmp(out.lexemeValue->contents, "NotifyNormal")) event->is_hint = NotifyNormal;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyHint")) event->is_hint = NotifyGrab;
	GetFactSlot(f, "same-screen", &out);
	event->same_screen = out.lexemeValue == theEnv->TrueSymbol;
}

void FactToXCrossingEvent(Environment *theEnv, Fact *f, XCrossingEvent *event)
{
	CLIPSValue out;
	GetFactSlot(f, "window", &out);
	event->window = out.integerValue->contents;
	GetFactSlot(f, "root", &out);
	event->root = out.integerValue->contents;
	GetFactSlot(f, "subwindow", &out);
	event->subwindow = out.integerValue->contents;
	GetFactSlot(f, "time", &out);
	event->time = out.integerValue->contents;
	GetFactSlot(f, "x", &out);
	event->x = out.integerValue->contents;
	GetFactSlot(f, "y", &out);
	event->y = out.integerValue->contents;
	GetFactSlot(f, "x_root", &out);
	event->x_root = out.integerValue->contents;
	GetFactSlot(f, "y_root", &out);
	event->y_root = out.integerValue->contents;
	GetFactSlot(f, "mode", &out);
	if (0 == strcmp(out.lexemeValue->contents, "NotifyNormal")) event->mode = NotifyNormal;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyGrab")) event->mode = NotifyGrab;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyUngrab")) event->mode = NotifyUngrab;
	GetFactSlot(f, "detail", &out);
	if (0 == strcmp(out.lexemeValue->contents, "NotifyAncestor")) event->detail = NotifyAncestor;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyVirtual")) event->detail = NotifyVirtual;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyInferior")) event->detail = NotifyInferior;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyNonlinear")) event->detail = NotifyNonlinear;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyNonlinearVirtual")) event->detail = NotifyNonlinearVirtual;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyPointer")) event->detail = NotifyPointer;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyPointerRoot")) event->detail = NotifyPointerRoot;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyDetailNone")) event->detail = NotifyDetailNone;
	GetFactSlot(f, "same-screen", &out);
	event->same_screen = out.lexemeValue == theEnv->TrueSymbol;
	GetFactSlot(f, "focus", &out);
	event->focus = out.lexemeValue == theEnv->TrueSymbol;
	GetFactSlot(f, "state", &out);
	event->state = out.integerValue->contents;
}

void FactToXFocusChangeEvent(Environment *theEnv, Fact *f, XFocusChangeEvent *event)
{
	CLIPSValue out;
	GetFactSlot(f, "window", &out);
	event->window = out.integerValue->contents;
	GetFactSlot(f, "mode", &out);
	if (0 == strcmp(out.lexemeValue->contents, "NotifyNormal")) event->mode = NotifyNormal;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyGrab")) event->mode = NotifyGrab;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyUngrab")) event->mode = NotifyUngrab;
	GetFactSlot(f, "detail", &out);
	if (0 == strcmp(out.lexemeValue->contents, "NotifyAncestor")) event->detail = NotifyAncestor;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyVirtual")) event->detail = NotifyVirtual;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyInferior")) event->detail = NotifyInferior;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyNonlinear")) event->detail = NotifyNonlinear;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyNonlinearVirtual")) event->detail = NotifyNonlinearVirtual;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyPointer")) event->detail = NotifyPointer;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyPointerRoot")) event->detail = NotifyPointerRoot;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyDetailNone")) event->detail = NotifyDetailNone;
}

void FactToXKeymapEvent(Environment *theEnv, Fact *f, XKeymapEvent *event)
{
	int min_kc, max_kc;
	long bitIndex;
	CLIPSValue out;
	GetFactSlot(f, "display", &out);
	XDisplayKeycodes(out.externalAddressValue->contents, &min_kc, &max_kc);
	memset(event->key_vector, 0, sizeof(event->key_vector));
	GetFactSlot(f, "window", &out);
	event->window = out.integerValue->contents;
	GetFactSlot(f, "key-vector", &out);
	for (int x = 1; x < out.multifieldValue->length; x++)
	{
		if (out.multifieldValue->contents[x].header->type == SYMBOL_TYPE && out.multifieldValue->contents[x].lexemeValue == theEnv->TrueSymbol)
		{
			bitIndex = x + min_kc;
			event->key_vector[ bitIndex >> 3 ] |= (1 << (bitIndex & 7));
		}
		else
		if (out.multifieldValue->contents[x].header->type == INTEGER_TYPE && out.multifieldValue->contents[x].integerValue->contents >= 0 && out.multifieldValue->contents[x].integerValue->contents <= 255)
		{
			event->key_vector[ out.multifieldValue->contents[x].integerValue->contents >> 3 ] |= (1 << (out.multifieldValue->contents[x].integerValue->contents & 7));
		}
	}
}

void FactToXExposeEvent(Environment *theEnv, Fact *f, XExposeEvent *event)
{
	CLIPSValue out;
	GetFactSlot(f, "window", &out);
	event->window = out.integerValue->contents;
	GetFactSlot(f, "x", &out);
	event->x = out.integerValue->contents;
	GetFactSlot(f, "y", &out);
	event->y = out.integerValue->contents;
	GetFactSlot(f, "width", &out);
	event->width = out.integerValue->contents;
	GetFactSlot(f, "height", &out);
	event->height = out.integerValue->contents;
	GetFactSlot(f, "count", &out);
	event->count = out.integerValue->contents;
}

void FactToXGraphicsExposeEvent(Environment *theEnv, Fact *f, XGraphicsExposeEvent *event)
{
	CLIPSValue out;
	GetFactSlot(f, "drawable", &out);
	event->drawable = out.integerValue->contents;
	GetFactSlot(f, "x", &out);
	event->x = out.integerValue->contents;
	GetFactSlot(f, "y", &out);
	event->y = out.integerValue->contents;
	GetFactSlot(f, "width", &out);
	event->width = out.integerValue->contents;
	GetFactSlot(f, "height", &out);
	event->height = out.integerValue->contents;
	GetFactSlot(f, "count", &out);
	event->count = out.integerValue->contents;
	GetFactSlot(f, "major-code", &out);
	event->major_code = out.integerValue->contents;
	GetFactSlot(f, "minor-code", &out);
	event->minor_code = out.integerValue->contents;
}

void FactToXNoExposeEvent(Environment *theEnv, Fact *f, XNoExposeEvent *event)
{
	CLIPSValue out;
	GetFactSlot(f, "drawable", &out);
	event->drawable = out.integerValue->contents;
	GetFactSlot(f, "major-code", &out);
	event->major_code = out.integerValue->contents;
	GetFactSlot(f, "minor-code", &out);
	event->minor_code = out.integerValue->contents;
}

void FactToXVisibilityEvent(Environment *theEnv, Fact *f, XVisibilityEvent *event)
{
	CLIPSValue out;
	GetFactSlot(f, "window", &out);
	event->window = out.integerValue->contents;
	GetFactSlot(f, "state", &out);
	if (0 == strcmp(out.lexemeValue->contents, "VisibilityUnobscured")) event->state = VisibilityUnobscured;
	else if (0 == strcmp(out.lexemeValue->contents, "VisibilityPartiallyObscured")) event->state = VisibilityPartiallyObscured;
	else if (0 == strcmp(out.lexemeValue->contents, "VisibilityFullyObscured")) event->state = VisibilityFullyObscured;
}

void FactToXCreateWindowEvent(Environment *theEnv, Fact *f, XCreateWindowEvent *event)
{
	CLIPSValue out;
	GetFactSlot(f, "parent", &out);
	event->parent = out.integerValue->contents;
	GetFactSlot(f, "window", &out);
	event->window = out.integerValue->contents;
	GetFactSlot(f, "x", &out);
	event->x = out.integerValue->contents;
	GetFactSlot(f, "y", &out);
	event->y = out.integerValue->contents;
	GetFactSlot(f, "width", &out);
	event->width = out.integerValue->contents;
	GetFactSlot(f, "height", &out);
	event->height = out.integerValue->contents;
	GetFactSlot(f, "border-width", &out);
	event->border_width = out.integerValue->contents;
	GetFactSlot(f, "override-redirect", &out);
	event->override_redirect = out.lexemeValue == theEnv->TrueSymbol; 
}

void FactToXDestroyWindowEvent(Environment *theEnv, Fact *f, XDestroyWindowEvent *event)
{
	CLIPSValue out;
	GetFactSlot(f, "event", &out);
	event->event = out.integerValue->contents;
	GetFactSlot(f, "window", &out);
	event->window = out.integerValue->contents;
}

void FactToXUnmapEvent(Environment *theEnv, Fact *f, XUnmapEvent *event)
{
	CLIPSValue out;
	GetFactSlot(f, "event", &out);
	event->event = out.integerValue->contents;
	GetFactSlot(f, "window", &out);
	event->window = out.integerValue->contents;
	GetFactSlot(f, "from-configure", &out);
	event->from_configure = out.lexemeValue == theEnv->TrueSymbol; 
}

void FactToXMapEvent(Environment *theEnv, Fact *f, XMapEvent *event)
{
	CLIPSValue out;
	GetFactSlot(f, "event", &out);
	event->event = out.integerValue->contents;
	GetFactSlot(f, "window", &out);
	event->window = out.integerValue->contents;
	GetFactSlot(f, "override-redirect", &out);
	event->override_redirect = out.lexemeValue == theEnv->TrueSymbol; 
}

void FactToXMapRequestEvent(Environment *theEnv, Fact *f, XMapRequestEvent *event)
{
	CLIPSValue out;
	GetFactSlot(f, "parent", &out);
	event->parent = out.integerValue->contents;
	GetFactSlot(f, "window", &out);
	event->window = out.integerValue->contents;
}


void FactToXReparentEvent(Environment *theEnv, Fact *f, XReparentEvent *event)
{
	CLIPSValue out;
	GetFactSlot(f, "event", &out);
	event->event = out.integerValue->contents;
	GetFactSlot(f, "window", &out);
	event->window = out.integerValue->contents;
	GetFactSlot(f, "parent", &out);
	event->parent = out.integerValue->contents;
	GetFactSlot(f, "x", &out);
	event->x = out.integerValue->contents;
	GetFactSlot(f, "y", &out);
	event->y = out.integerValue->contents;
	GetFactSlot(f, "override-redirect", &out);
	event->override_redirect = out.lexemeValue == theEnv->TrueSymbol; 
}

void FactToXConfigureEvent(Environment *theEnv, Fact *f, XConfigureEvent *event)
{
	CLIPSValue out;
	GetFactSlot(f, "event", &out);
	event->event = out.integerValue->contents;
	GetFactSlot(f, "window", &out);
	event->window = out.integerValue->contents;
	GetFactSlot(f, "x", &out);
	event->x = out.integerValue->contents;
	GetFactSlot(f, "y", &out);
	event->y = out.integerValue->contents;
	GetFactSlot(f, "width", &out);
	event->width = out.integerValue->contents;
	GetFactSlot(f, "height", &out);
	event->height = out.integerValue->contents;
	GetFactSlot(f, "border-width", &out);
	event->border_width = out.integerValue->contents;
	GetFactSlot(f, "above", &out);
	event->above = out.integerValue->contents;
	GetFactSlot(f, "override-redirect", &out);
	event->override_redirect = out.lexemeValue == theEnv->TrueSymbol; 
}

void FactToXGravityEvent(Environment *theEnv, Fact *f, XGravityEvent *event)
{
	CLIPSValue out;
	GetFactSlot(f, "event", &out);
	event->event = out.integerValue->contents;
	GetFactSlot(f, "window", &out);
	event->window = out.integerValue->contents;
	GetFactSlot(f, "x", &out);
	event->x = out.integerValue->contents;
	GetFactSlot(f, "y", &out);
	event->y = out.integerValue->contents;
}

void FactToXResizeRequestEvent(Environment *theEnv, Fact *f, XResizeRequestEvent *event)
{
	CLIPSValue out;
	GetFactSlot(f, "window", &out);
	event->window = out.integerValue->contents;
	GetFactSlot(f, "width", &out);
	event->width = out.integerValue->contents;
	GetFactSlot(f, "height", &out);
	event->height = out.integerValue->contents;
}

void FactToXConfigureRequestEvent(Environment *theEnv, Fact *f, XConfigureRequestEvent *event)
{
	CLIPSValue out;
	GetFactSlot(f, "parent", &out);
	event->parent = out.integerValue->contents;
	GetFactSlot(f, "window", &out);
	event->window = out.integerValue->contents;
	GetFactSlot(f, "x", &out);
	event->x = out.integerValue->contents;
	GetFactSlot(f, "y", &out);
	event->y = out.integerValue->contents;
	GetFactSlot(f, "width", &out);
	event->width = out.integerValue->contents;
	GetFactSlot(f, "height", &out);
	event->height = out.integerValue->contents;
	GetFactSlot(f, "border-width", &out);
	event->border_width = out.integerValue->contents;
	GetFactSlot(f, "above", &out);
	event->above = out.integerValue->contents;
	GetFactSlot(f, "detail", &out);
	if (0 == strcmp(out.lexemeValue->contents, "Above")) event->detail = Above;
	else if (0 == strcmp(out.lexemeValue->contents, "Below")) event->detail = Below;
	else if (0 == strcmp(out.lexemeValue->contents, "TopIf")) event->detail = TopIf;
	else if (0 == strcmp(out.lexemeValue->contents, "BottomIf")) event->detail = BottomIf;
	else if (0 == strcmp(out.lexemeValue->contents, "Opposite")) event->detail = Opposite;
	GetFactSlot(f, "value-mask", &out);
	event->value_mask = out.integerValue->contents;
}

void FactToXCirculateEvent(Environment *theEnv, Fact *f, XCirculateEvent *event)
{
	CLIPSValue out;
	GetFactSlot(f, "event", &out);
	event->event = out.integerValue->contents;
	GetFactSlot(f, "window", &out);
	event->window = out.integerValue->contents;
	GetFactSlot(f, "place", &out);
	if (0 == strcmp(out.lexemeValue->contents, "PlaceOnTop")) event->place = PlaceOnTop;
	else if (0 == strcmp(out.lexemeValue->contents, "PlaceOnBottom")) event->place = PlaceOnBottom;
}

void FactToXCirculateRequestEvent(Environment *theEnv, Fact *f, XCirculateRequestEvent *event)
{
	CLIPSValue out;
	GetFactSlot(f, "parent", &out);
	event->parent = out.integerValue->contents;
	GetFactSlot(f, "window", &out);
	event->window = out.integerValue->contents;
	GetFactSlot(f, "detail", &out);
	if (0 == strcmp(out.lexemeValue->contents, "PlaceOnTop")) event->place = PlaceOnTop;
	else if (0 == strcmp(out.lexemeValue->contents, "PlaceOnBottom")) event->place = PlaceOnBottom;
}

void FactToXPropertyEvent(Environment *theEnv, Fact *f, XPropertyEvent *event)
{
	CLIPSValue out;
	GetFactSlot(f, "window", &out);
	event->window = out.integerValue->contents;
	GetFactSlot(f, "atom", &out);
	event->atom = out.integerValue->contents;
	GetFactSlot(f, "time", &out);
	event->time = out.integerValue->contents;
	GetFactSlot(f, "state", &out);
	if (0 == strcmp(out.lexemeValue->contents, "PropertyNewValue")) event->state = PropertyNewValue;
	else if (0 == strcmp(out.lexemeValue->contents, "PropertyDelete")) event->state = PropertyDelete;
}

void FactToXSelectionClearEvent(Environment *theEnv, Fact *f, XSelectionClearEvent *event)
{
	CLIPSValue out;
	GetFactSlot(f, "window", &out);
	event->window = out.integerValue->contents;
	GetFactSlot(f, "selection", &out);
	event->selection = out.integerValue->contents;
	GetFactSlot(f, "time", &out);
	event->time = out.integerValue->contents;
}

void FactToXSelectionRequestEvent(Environment *theEnv, Fact *f, XSelectionRequestEvent *event)
{
	CLIPSValue out;
	GetFactSlot(f, "owner", &out);
	event->owner = out.integerValue->contents;
	GetFactSlot(f, "requestor", &out);
	event->requestor = out.integerValue->contents;
	GetFactSlot(f, "selection", &out);
	event->selection = out.integerValue->contents;
	GetFactSlot(f, "target", &out);
	event->target = out.integerValue->contents;
	GetFactSlot(f, "property", &out);
	event->property = out.integerValue->contents;
	GetFactSlot(f, "time", &out);
	event->time = out.integerValue->contents;
}

void FactToXSelectionEvent(Environment *theEnv, Fact *f, XSelectionEvent *event)
{
	CLIPSValue out;
	GetFactSlot(f, "requestor", &out);
	event->requestor = out.integerValue->contents;
	GetFactSlot(f, "selection", &out);
	event->selection = out.integerValue->contents;
	GetFactSlot(f, "target", &out);
	event->target = out.integerValue->contents;
	GetFactSlot(f, "property", &out);
	event->property = out.integerValue->contents;
	GetFactSlot(f, "time", &out);
	event->time = out.integerValue->contents;
}

void FactToXColormapEvent(Environment *theEnv, Fact *f, XColormapEvent *event)
{
	CLIPSValue out;
	GetFactSlot(f, "window", &out);
	event->window = out.integerValue->contents;
	GetFactSlot(f, "colormap", &out);
	event->colormap = out.integerValue->contents;
	GetFactSlot(f, "new", &out);
	event->new = out.lexemeValue == theEnv->TrueSymbol;
	GetFactSlot(f, "state", &out);
	if (0 == strcmp(out.lexemeValue->contents, "ColormapInstalled")) event->state = ColormapInstalled;
	else if (0 == strcmp(out.lexemeValue->contents, "ColormapUninstalled")) event->state = ColormapUninstalled;
}

void FactToXClientMessageEvent(Environment *theEnv, Fact *f, XClientMessageEvent *event)
{
	CLIPSValue out;
	GetFactSlot(f, "window", &out);
	event->window = out.integerValue->contents;
	GetFactSlot(f, "message-type", &out);
	event->message_type = out.integerValue->contents;
	GetFactSlot(f, "format", &out);
	event->format = out.integerValue->contents;
	GetFactSlot(f, "data", &out);
	if (event->format == 8 && out.multifieldValue->length >= 28)
	{
		for (int x = 0; x < 20; x++)
		{
			if (out.multifieldValue->contents[3 + x].header->type == INTEGER_TYPE)
			event->data.b[x] = out.multifieldValue->contents[3 + x].integerValue->contents;
		}
	}
	else if (event->format == 16)
	{
		for (int x = 0; x < 10; x++)
		{
			if (out.multifieldValue->contents[3 + x].header->type == INTEGER_TYPE)
			event->data.s[x] = out.multifieldValue->contents[3 + x].integerValue->contents;
		}
	}
	else if (event->format == 32)
	{
		for (int x = 0; x < 5; x++)
		{
			if (out.multifieldValue->contents[3 + x].header->type == INTEGER_TYPE)
			event->data.l[x] = out.multifieldValue->contents[3 + x].integerValue->contents;
		}
	}
}

void FactToXMappingEvent(Environment *theEnv, Fact *f, XMappingEvent *event)
{
	CLIPSValue out;
	GetFactSlot(f, "window", &out);
	event->window = out.integerValue->contents;
	GetFactSlot(f, "request", &out);
	if (0 == strcmp(out.lexemeValue->contents, "MappingModifier")) event->request = MappingModifier;
	else if (0 == strcmp(out.lexemeValue->contents, "MappingKeyboard")) event->request = MappingKeyboard;
	else if (0 == strcmp(out.lexemeValue->contents, "MappingPointer")) event->request = MappingPointer;
	GetFactSlot(f, "first-keycode", &out);
	event->first_keycode = out.integerValue->contents;
	GetFactSlot(f, "count", &out);
	event->count = out.integerValue->contents;
}

void FactToXGenericEvent(Environment *theEnv, Fact *f, XGenericEvent *event)
{
	CLIPSValue out;
	GetFactSlot(f, "extension", &out);
	event->extension = out.integerValue->contents;
	GetFactSlot(f, "evtype", &out);
	event->evtype = out.integerValue->contents;
}

void FactToXEvent(Environment *theEnv, Fact *f, XEvent *event)
{
	CLIPSValue out;
	GetFactSlot(f, "type", &out);
	if (0 == strcmp(out.lexemeValue->contents, "KeyPress"))
	{
		event->xkey.type = KeyPress;
		FactToXKeyEvent(theEnv, f, &(event->xkey));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "KeyRelease"))
	{
		event->xkey.type = KeyRelease;
		FactToXKeyEvent(theEnv, f, &(event->xkey));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "ButtonPress"))
	{
		event->xbutton.type = ButtonPress;
		FactToXButtonEvent(theEnv, f, &(event->xbutton));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "ButtonRelease"))
	{
		event->xbutton.type = ButtonRelease;
		FactToXButtonEvent(theEnv, f, &(event->xbutton));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "MotionNotify"))
	{
		event->xmotion.type = ButtonRelease;
		FactToXMotionEvent(theEnv, f, &(event->xmotion));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "EnterNotify"))
	{
		event->xcrossing.type = EnterNotify;
		FactToXCrossingEvent(theEnv, f, &(event->xcrossing));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "LeaveNotify"))
	{
		event->xcrossing.type = LeaveNotify;
		FactToXCrossingEvent(theEnv, f, &(event->xcrossing));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "FocusIn"))
	{
		event->xfocus.type = FocusIn;
		FactToXFocusChangeEvent(theEnv, f, &(event->xfocus));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "FocusOut"))
	{
		event->xfocus.type = FocusOut;
		FactToXFocusChangeEvent(theEnv, f, &(event->xfocus));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "KeymapNotify"))
	{
		event->xkeymap.type = KeymapNotify;
		FactToXKeymapEvent(theEnv, f, &(event->xkeymap));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "Expose"))
	{
		event->xexpose.type = Expose;
		FactToXExposeEvent(theEnv, f, &(event->xexpose));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "GraphicsExpose"))
	{
		event->xgraphicsexpose.type = GraphicsExpose;
		FactToXGraphicsExposeEvent(theEnv, f, &(event->xgraphicsexpose));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "NoExpose"))
	{
		event->xnoexpose.type = NoExpose;
		FactToXNoExposeEvent(theEnv, f, &(event->xnoexpose));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "VisibilityNotify"))
	{
		event->xvisibility.type = VisibilityNotify;
		FactToXVisibilityEvent(theEnv, f, &(event->xvisibility));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "CreateNotify"))
	{
		event->xcreatewindow.type = CreateNotify;
		FactToXCreateWindowEvent(theEnv, f, &(event->xcreatewindow));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "DestroyNotify"))
	{
		event->xdestroywindow.type = DestroyNotify;
		FactToXDestroyWindowEvent(theEnv, f, &(event->xdestroywindow));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "UnmapNotify"))
	{
		event->xunmap.type = UnmapNotify;
		FactToXUnmapEvent(theEnv, f, &(event->xunmap));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "MapNotify"))
	{
		event->xmap.type = MapNotify;
		FactToXMapEvent(theEnv, f, &(event->xmap));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "MapRequest"))
	{
		event->xmaprequest.type = MapRequest;
		FactToXMapRequestEvent(theEnv, f, &(event->xmaprequest));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "ReparentNotify"))
	{
		event->xreparent.type = ReparentNotify;
		FactToXReparentEvent(theEnv, f, &(event->xreparent));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "ConfigureNotify"))
	{
		event->xconfigure.type = ConfigureNotify;
		FactToXConfigureEvent(theEnv, f, &(event->xconfigure));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "ConfigureRequest"))
	{
		event->xconfigurerequest.type = ConfigureRequest;
		FactToXConfigureRequestEvent(theEnv, f, &(event->xconfigurerequest));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "GravityNotify"))
	{
		event->xgravity.type = GravityNotify;
		FactToXGravityEvent(theEnv, f, &(event->xgravity));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "ResizeRequest"))
	{
		event->xresizerequest.type = ResizeRequest;
		FactToXResizeRequestEvent(theEnv, f, &(event->xresizerequest));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "CirculateNotify"))
	{
		event->xcirculate.type = CirculateNotify;
		FactToXCirculateEvent(theEnv, f, &(event->xcirculate));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "CirculateRequest"))
	{
		event->xcirculaterequest.type = CirculateRequest;
		FactToXCirculateRequestEvent(theEnv, f, &(event->xcirculaterequest));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "PropertyNotify"))
	{
		event->xproperty.type = PropertyNotify;
		FactToXPropertyEvent(theEnv, f, &(event->xproperty));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "SelectionClear"))
	{
		event->xselectionclear.type = SelectionClear;
		FactToXSelectionClearEvent(theEnv, f, &(event->xselectionclear));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "SelectionRequest"))
	{
		event->xselectionrequest.type = SelectionRequest;
		FactToXSelectionRequestEvent(theEnv, f, &(event->xselectionrequest));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "SelectionNotify"))
	{
		event->xselection.type = SelectionNotify;
		FactToXSelectionEvent(theEnv, f, &(event->xselection));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "ColormapNotify"))
	{
		event->xcolormap.type = ColormapNotify;
		FactToXColormapEvent(theEnv, f, &(event->xcolormap));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "ClientMessage"))
	{
		event->xclient.type = ClientMessage;
		FactToXClientMessageEvent(theEnv, f, &(event->xclient));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "MappingNotify"))
	{
		event->xmapping.type = MappingNotify;
		FactToXMappingEvent(theEnv, f, &(event->xmapping));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "GenericEvent"))
	{
		event->xgeneric.type = GenericEvent;
		FactToXGenericEvent(theEnv, f, &(event->xgeneric));
	}
	else
	{
		WriteString(theEnv, STDERR, "Event '");
		WriteString(theEnv, STDERR, out.lexemeValue->contents);
		WriteString(theEnv, STDERR, "' not supported.\n");
	}
}

void InstanceToXKeyEvent(Environment *theEnv, Instance *i, XKeyEvent *event)
{
	CLIPSValue out;
	DirectGetSlot(i, "window", &out);
	event->window = out.integerValue->contents;
	DirectGetSlot(i, "root", &out);
	event->root = out.integerValue->contents;
	DirectGetSlot(i, "subwindow", &out);
	event->subwindow = out.integerValue->contents;
	DirectGetSlot(i, "time", &out);
	event->time = out.integerValue->contents;
	DirectGetSlot(i, "x", &out);
	event->x = out.integerValue->contents;
	DirectGetSlot(i, "y", &out);
	event->y = out.integerValue->contents;
	DirectGetSlot(i, "x_root", &out);
	event->x_root = out.integerValue->contents;
	DirectGetSlot(i, "y_root", &out);
	event->y_root = out.integerValue->contents;
	DirectGetSlot(i, "state", &out);
	event->state = out.integerValue->contents;
	DirectGetSlot(i, "keycode", &out);
	event->keycode = out.integerValue->contents;
	DirectGetSlot(i, "same-screen", &out);
	event->same_screen = out.lexemeValue == theEnv->TrueSymbol;
}

void InstanceToXButtonEvent(Environment *theEnv, Instance *i, XButtonEvent *event)
{
	CLIPSValue out;
	DirectGetSlot(i, "window", &out);
	event->window = out.integerValue->contents;
	DirectGetSlot(i, "root", &out);
	event->root = out.integerValue->contents;
	DirectGetSlot(i, "subwindow", &out);
	event->subwindow = out.integerValue->contents;
	DirectGetSlot(i, "time", &out);
	event->time = out.integerValue->contents;
	DirectGetSlot(i, "x", &out);
	event->x = out.integerValue->contents;
	DirectGetSlot(i, "y", &out);
	event->y = out.integerValue->contents;
	DirectGetSlot(i, "x_root", &out);
	event->x_root = out.integerValue->contents;
	DirectGetSlot(i, "y_root", &out);
	event->y_root = out.integerValue->contents;
	DirectGetSlot(i, "state", &out);
	event->state = out.integerValue->contents;
	DirectGetSlot(i, "button", &out);
	event->button = out.integerValue->contents;
	DirectGetSlot(i, "same-screen", &out);
	event->same_screen = out.lexemeValue == theEnv->TrueSymbol;
}

void InstanceToXMotionEvent(Environment *theEnv, Instance *i, XMotionEvent *event)
{
	CLIPSValue out;
	DirectGetSlot(i, "window", &out);
	event->window = out.integerValue->contents;
	DirectGetSlot(i, "root", &out);
	event->root = out.integerValue->contents;
	DirectGetSlot(i, "subwindow", &out);
	event->subwindow = out.integerValue->contents;
	DirectGetSlot(i, "time", &out);
	event->time = out.integerValue->contents;
	DirectGetSlot(i, "x", &out);
	event->x = out.integerValue->contents;
	DirectGetSlot(i, "y", &out);
	event->y = out.integerValue->contents;
	DirectGetSlot(i, "x_root", &out);
	event->x_root = out.integerValue->contents;
	DirectGetSlot(i, "y_root", &out);
	event->y_root = out.integerValue->contents;
	DirectGetSlot(i, "state", &out);
	event->state = out.integerValue->contents;
	DirectGetSlot(i, "is-hint", &out);
	if (0 == strcmp(out.lexemeValue->contents, "NotifyNormal")) event->is_hint = NotifyNormal;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyHint")) event->is_hint = NotifyGrab;
	DirectGetSlot(i, "same-screen", &out);
	event->same_screen = out.lexemeValue == theEnv->TrueSymbol;
}

void InstanceToXCrossingEvent(Environment *theEnv, Instance *i, XCrossingEvent *event)
{
	CLIPSValue out;
	DirectGetSlot(i, "window", &out);
	event->window = out.integerValue->contents;
	DirectGetSlot(i, "root", &out);
	event->root = out.integerValue->contents;
	DirectGetSlot(i, "subwindow", &out);
	event->subwindow = out.integerValue->contents;
	DirectGetSlot(i, "time", &out);
	event->time = out.integerValue->contents;
	DirectGetSlot(i, "x", &out);
	event->x = out.integerValue->contents;
	DirectGetSlot(i, "y", &out);
	event->y = out.integerValue->contents;
	DirectGetSlot(i, "x_root", &out);
	event->x_root = out.integerValue->contents;
	DirectGetSlot(i, "y_root", &out);
	event->y_root = out.integerValue->contents;
	DirectGetSlot(i, "mode", &out);
	if (0 == strcmp(out.lexemeValue->contents, "NotifyNormal")) event->mode = NotifyNormal;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyGrab")) event->mode = NotifyGrab;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyUngrab")) event->mode = NotifyUngrab;
	DirectGetSlot(i, "detail", &out);
	if (0 == strcmp(out.lexemeValue->contents, "NotifyAncestor")) event->detail = NotifyAncestor;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyVirtual")) event->detail = NotifyVirtual;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyInferior")) event->detail = NotifyInferior;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyNonlinear")) event->detail = NotifyNonlinear;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyNonlinearVirtual")) event->detail = NotifyNonlinearVirtual;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyPointer")) event->detail = NotifyPointer;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyPointerRoot")) event->detail = NotifyPointerRoot;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyDetailNone")) event->detail = NotifyDetailNone;
	DirectGetSlot(i, "same-screen", &out);
	event->same_screen = out.lexemeValue == theEnv->TrueSymbol;
	DirectGetSlot(i, "focus", &out);
	event->focus = out.lexemeValue == theEnv->TrueSymbol;
	DirectGetSlot(i, "state", &out);
	event->state = out.integerValue->contents;
}

void InstanceToXFocusChangeEvent(Environment *theEnv, Instance *i, XFocusChangeEvent *event)
{
	CLIPSValue out;
	DirectGetSlot(i, "window", &out);
	event->window = out.integerValue->contents;
	DirectGetSlot(i, "mode", &out);
	if (0 == strcmp(out.lexemeValue->contents, "NotifyNormal")) event->mode = NotifyNormal;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyGrab")) event->mode = NotifyGrab;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyUngrab")) event->mode = NotifyUngrab;
	DirectGetSlot(i, "detail", &out);
	if (0 == strcmp(out.lexemeValue->contents, "NotifyAncestor")) event->detail = NotifyAncestor;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyVirtual")) event->detail = NotifyVirtual;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyInferior")) event->detail = NotifyInferior;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyNonlinear")) event->detail = NotifyNonlinear;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyNonlinearVirtual")) event->detail = NotifyNonlinearVirtual;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyPointer")) event->detail = NotifyPointer;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyPointerRoot")) event->detail = NotifyPointerRoot;
	else if (0 == strcmp(out.lexemeValue->contents, "NotifyDetailNone")) event->detail = NotifyDetailNone;
}

void InstanceToXKeymapEvent(Environment *theEnv, Instance *i, XKeymapEvent *event)
{
	int min_kc, max_kc;
	long bitIndex;
	CLIPSValue out;
	DirectGetSlot(i, "display", &out);
	XDisplayKeycodes(out.externalAddressValue->contents, &min_kc, &max_kc);
	memset(event->key_vector, 0, sizeof(event->key_vector));
	DirectGetSlot(i, "window", &out);
	event->window = out.integerValue->contents;
	DirectGetSlot(i, "key-vector", &out);
	for (int x = 1; x < out.multifieldValue->length; x++)
	{
		if (out.multifieldValue->contents[x].header->type == SYMBOL_TYPE && out.multifieldValue->contents[x].lexemeValue == theEnv->TrueSymbol)
		{
			bitIndex = x + min_kc;
			event->key_vector[ bitIndex >> 3 ] |= (1 << (bitIndex & 7));
		}
		else
		if (out.multifieldValue->contents[x].header->type == INTEGER_TYPE && out.multifieldValue->contents[x].integerValue->contents >= 0 && out.multifieldValue->contents[x].integerValue->contents <= 255)
		{
			event->key_vector[ out.multifieldValue->contents[x].integerValue->contents >> 3 ] |= (1 << (out.multifieldValue->contents[x].integerValue->contents & 7));
		}
	}
}

void InstanceToXExposeEvent(Environment *theEnv, Instance *i, XExposeEvent *event)
{
	CLIPSValue out;
	DirectGetSlot(i, "window", &out);
	event->window = out.integerValue->contents;
	DirectGetSlot(i, "x", &out);
	event->x = out.integerValue->contents;
	DirectGetSlot(i, "y", &out);
	event->y = out.integerValue->contents;
	DirectGetSlot(i, "width", &out);
	event->width = out.integerValue->contents;
	DirectGetSlot(i, "height", &out);
	event->height = out.integerValue->contents;
	DirectGetSlot(i, "count", &out);
	event->count = out.integerValue->contents;
}

void InstanceToXGraphicsExposeEvent(Environment *theEnv, Instance *i, XGraphicsExposeEvent *event)
{
	CLIPSValue out;
	DirectGetSlot(i, "drawable", &out);
	event->drawable = out.integerValue->contents;
	DirectGetSlot(i, "x", &out);
	event->x = out.integerValue->contents;
	DirectGetSlot(i, "y", &out);
	event->y = out.integerValue->contents;
	DirectGetSlot(i, "width", &out);
	event->width = out.integerValue->contents;
	DirectGetSlot(i, "height", &out);
	event->height = out.integerValue->contents;
	DirectGetSlot(i, "count", &out);
	event->count = out.integerValue->contents;
	DirectGetSlot(i, "major-code", &out);
	event->major_code = out.integerValue->contents;
	DirectGetSlot(i, "minor-code", &out);
	event->minor_code = out.integerValue->contents;
}

void InstanceToXNoExposeEvent(Environment *theEnv, Instance *i, XNoExposeEvent *event)
{
	CLIPSValue out;
	DirectGetSlot(i, "drawable", &out);
	event->drawable = out.integerValue->contents;
	DirectGetSlot(i, "major-code", &out);
	event->major_code = out.integerValue->contents;
	DirectGetSlot(i, "minor-code", &out);
	event->minor_code = out.integerValue->contents;
}

void InstanceToXVisibilityEvent(Environment *theEnv, Instance *i, XVisibilityEvent *event)
{
	CLIPSValue out;
	DirectGetSlot(i, "window", &out);
	event->window = out.integerValue->contents;
	DirectGetSlot(i, "state", &out);
	if (0 == strcmp(out.lexemeValue->contents, "VisibilityUnobscured")) event->state = VisibilityUnobscured;
	else if (0 == strcmp(out.lexemeValue->contents, "VisibilityPartiallyObscured")) event->state = VisibilityPartiallyObscured;
	else if (0 == strcmp(out.lexemeValue->contents, "VisibilityFullyObscured")) event->state = VisibilityFullyObscured;
}

void InstanceToXCreateWindowEvent(Environment *theEnv, Instance *i, XCreateWindowEvent *event)
{
	CLIPSValue out;
	DirectGetSlot(i, "parent", &out);
	event->parent = out.integerValue->contents;
	DirectGetSlot(i, "window", &out);
	event->window = out.integerValue->contents;
	DirectGetSlot(i, "x", &out);
	event->x = out.integerValue->contents;
	DirectGetSlot(i, "y", &out);
	event->y = out.integerValue->contents;
	DirectGetSlot(i, "width", &out);
	event->width = out.integerValue->contents;
	DirectGetSlot(i, "height", &out);
	event->height = out.integerValue->contents;
	DirectGetSlot(i, "border-width", &out);
	event->border_width = out.integerValue->contents;
	DirectGetSlot(i, "override-redirect", &out);
	event->override_redirect = out.lexemeValue == theEnv->TrueSymbol; 
}

void InstanceToXDestroyWindowEvent(Environment *theEnv, Instance *i, XDestroyWindowEvent *event)
{
	CLIPSValue out;
	DirectGetSlot(i, "event", &out);
	event->event = out.integerValue->contents;
	DirectGetSlot(i, "window", &out);
	event->window = out.integerValue->contents;
}

void InstanceToXUnmapEvent(Environment *theEnv, Instance *i, XUnmapEvent *event)
{
	CLIPSValue out;
	DirectGetSlot(i, "event", &out);
	event->event = out.integerValue->contents;
	DirectGetSlot(i, "window", &out);
	event->window = out.integerValue->contents;
	DirectGetSlot(i, "from-configure", &out);
	event->from_configure = out.lexemeValue == theEnv->TrueSymbol; 
}

void InstanceToXMapEvent(Environment *theEnv, Instance *i, XMapEvent *event)
{
	CLIPSValue out;
	DirectGetSlot(i, "event", &out);
	event->event = out.integerValue->contents;
	DirectGetSlot(i, "window", &out);
	event->window = out.integerValue->contents;
	DirectGetSlot(i, "override-redirect", &out);
	event->override_redirect = out.lexemeValue == theEnv->TrueSymbol; 
}

void InstanceToXMapRequestEvent(Environment *theEnv, Instance *i, XMapRequestEvent *event)
{
	CLIPSValue out;
	DirectGetSlot(i, "parent", &out);
	event->parent = out.integerValue->contents;
	DirectGetSlot(i, "window", &out);
	event->window = out.integerValue->contents;
}


void InstanceToXReparentEvent(Environment *theEnv, Instance *i, XReparentEvent *event)
{
	CLIPSValue out;
	DirectGetSlot(i, "event", &out);
	event->event = out.integerValue->contents;
	DirectGetSlot(i, "window", &out);
	event->window = out.integerValue->contents;
	DirectGetSlot(i, "parent", &out);
	event->parent = out.integerValue->contents;
	DirectGetSlot(i, "x", &out);
	event->x = out.integerValue->contents;
	DirectGetSlot(i, "y", &out);
	event->y = out.integerValue->contents;
	DirectGetSlot(i, "override-redirect", &out);
	event->override_redirect = out.lexemeValue == theEnv->TrueSymbol; 
}

void InstanceToXConfigureEvent(Environment *theEnv, Instance *i, XConfigureEvent *event)
{
	CLIPSValue out;
	DirectGetSlot(i, "event", &out);
	event->event = out.integerValue->contents;
	DirectGetSlot(i, "window", &out);
	event->window = out.integerValue->contents;
	DirectGetSlot(i, "x", &out);
	event->x = out.integerValue->contents;
	DirectGetSlot(i, "y", &out);
	event->y = out.integerValue->contents;
	DirectGetSlot(i, "width", &out);
	event->width = out.integerValue->contents;
	DirectGetSlot(i, "height", &out);
	event->height = out.integerValue->contents;
	DirectGetSlot(i, "border-width", &out);
	event->border_width = out.integerValue->contents;
	DirectGetSlot(i, "above", &out);
	event->above = out.integerValue->contents;
	DirectGetSlot(i, "override-redirect", &out);
	event->override_redirect = out.lexemeValue == theEnv->TrueSymbol; 
}

void InstanceToXGravityEvent(Environment *theEnv, Instance *i, XGravityEvent *event)
{
	CLIPSValue out;
	DirectGetSlot(i, "event", &out);
	event->event = out.integerValue->contents;
	DirectGetSlot(i, "window", &out);
	event->window = out.integerValue->contents;
	DirectGetSlot(i, "x", &out);
	event->x = out.integerValue->contents;
	DirectGetSlot(i, "y", &out);
	event->y = out.integerValue->contents;
}

void InstanceToXResizeRequestEvent(Environment *theEnv, Instance *i, XResizeRequestEvent *event)
{
	CLIPSValue out;
	DirectGetSlot(i, "window", &out);
	event->window = out.integerValue->contents;
	DirectGetSlot(i, "width", &out);
	event->width = out.integerValue->contents;
	DirectGetSlot(i, "height", &out);
	event->height = out.integerValue->contents;
}

void InstanceToXConfigureRequestEvent(Environment *theEnv, Instance *i, XConfigureRequestEvent *event)
{
	CLIPSValue out;
	DirectGetSlot(i, "parent", &out);
	event->parent = out.integerValue->contents;
	DirectGetSlot(i, "window", &out);
	event->window = out.integerValue->contents;
	DirectGetSlot(i, "x", &out);
	event->x = out.integerValue->contents;
	DirectGetSlot(i, "y", &out);
	event->y = out.integerValue->contents;
	DirectGetSlot(i, "width", &out);
	event->width = out.integerValue->contents;
	DirectGetSlot(i, "height", &out);
	event->height = out.integerValue->contents;
	DirectGetSlot(i, "border-width", &out);
	event->border_width = out.integerValue->contents;
	DirectGetSlot(i, "above", &out);
	event->above = out.integerValue->contents;
	DirectGetSlot(i, "detail", &out);
	if (0 == strcmp(out.lexemeValue->contents, "Above")) event->detail = Above;
	else if (0 == strcmp(out.lexemeValue->contents, "Below")) event->detail = Below;
	else if (0 == strcmp(out.lexemeValue->contents, "TopIf")) event->detail = TopIf;
	else if (0 == strcmp(out.lexemeValue->contents, "BottomIf")) event->detail = BottomIf;
	else if (0 == strcmp(out.lexemeValue->contents, "Opposite")) event->detail = Opposite;
	DirectGetSlot(i, "value-mask", &out);
	event->value_mask = out.integerValue->contents;
}

void InstanceToXCirculateEvent(Environment *theEnv, Instance *i, XCirculateEvent *event)
{
	CLIPSValue out;
	DirectGetSlot(i, "event", &out);
	event->event = out.integerValue->contents;
	DirectGetSlot(i, "window", &out);
	event->window = out.integerValue->contents;
	DirectGetSlot(i, "place", &out);
	if (0 == strcmp(out.lexemeValue->contents, "PlaceOnTop")) event->place = PlaceOnTop;
	else if (0 == strcmp(out.lexemeValue->contents, "PlaceOnBottom")) event->place = PlaceOnBottom;
}

void InstanceToXCirculateRequestEvent(Environment *theEnv, Instance *i, XCirculateRequestEvent *event)
{
	CLIPSValue out;
	DirectGetSlot(i, "parent", &out);
	event->parent = out.integerValue->contents;
	DirectGetSlot(i, "window", &out);
	event->window = out.integerValue->contents;
	DirectGetSlot(i, "detail", &out);
	if (0 == strcmp(out.lexemeValue->contents, "PlaceOnTop")) event->place = PlaceOnTop;
	else if (0 == strcmp(out.lexemeValue->contents, "PlaceOnBottom")) event->place = PlaceOnBottom;
}

void InstanceToXPropertyEvent(Environment *theEnv, Instance *i, XPropertyEvent *event)
{
	CLIPSValue out;
	DirectGetSlot(i, "window", &out);
	event->window = out.integerValue->contents;
	DirectGetSlot(i, "atom", &out);
	event->atom = out.integerValue->contents;
	DirectGetSlot(i, "time", &out);
	event->time = out.integerValue->contents;
	DirectGetSlot(i, "state", &out);
	if (0 == strcmp(out.lexemeValue->contents, "PropertyNewValue")) event->state = PropertyNewValue;
	else if (0 == strcmp(out.lexemeValue->contents, "PropertyDelete")) event->state = PropertyDelete;
}

void InstanceToXSelectionClearEvent(Environment *theEnv, Instance *i, XSelectionClearEvent *event)
{
	CLIPSValue out;
	DirectGetSlot(i, "window", &out);
	event->window = out.integerValue->contents;
	DirectGetSlot(i, "selection", &out);
	event->selection = out.integerValue->contents;
	DirectGetSlot(i, "time", &out);
	event->time = out.integerValue->contents;
}

void InstanceToXSelectionRequestEvent(Environment *theEnv, Instance *i, XSelectionRequestEvent *event)
{
	CLIPSValue out;
	DirectGetSlot(i, "owner", &out);
	event->owner = out.integerValue->contents;
	DirectGetSlot(i, "requestor", &out);
	event->requestor = out.integerValue->contents;
	DirectGetSlot(i, "selection", &out);
	event->selection = out.integerValue->contents;
	DirectGetSlot(i, "target", &out);
	event->target = out.integerValue->contents;
	DirectGetSlot(i, "property", &out);
	event->property = out.integerValue->contents;
	DirectGetSlot(i, "time", &out);
	event->time = out.integerValue->contents;
}

void InstanceToXSelectionEvent(Environment *theEnv, Instance *i, XSelectionEvent *event)
{
	CLIPSValue out;
	DirectGetSlot(i, "requestor", &out);
	event->requestor = out.integerValue->contents;
	DirectGetSlot(i, "selection", &out);
	event->selection = out.integerValue->contents;
	DirectGetSlot(i, "target", &out);
	event->target = out.integerValue->contents;
	DirectGetSlot(i, "property", &out);
	event->property = out.integerValue->contents;
	DirectGetSlot(i, "time", &out);
	event->time = out.integerValue->contents;
}

void InstanceToXColormapEvent(Environment *theEnv, Instance *i, XColormapEvent *event)
{
	CLIPSValue out;
	DirectGetSlot(i, "window", &out);
	event->window = out.integerValue->contents;
	DirectGetSlot(i, "colormap", &out);
	event->colormap = out.integerValue->contents;
	DirectGetSlot(i, "new", &out);
	event->new = out.lexemeValue == theEnv->TrueSymbol;
	DirectGetSlot(i, "state", &out);
	if (0 == strcmp(out.lexemeValue->contents, "ColormapInstalled")) event->state = ColormapInstalled;
	else if (0 == strcmp(out.lexemeValue->contents, "ColormapUninstalled")) event->state = ColormapUninstalled;
}

void InstanceToXClientMessageEvent(Environment *theEnv, Instance *i, XClientMessageEvent *event)
{
	CLIPSValue out;
	DirectGetSlot(i, "window", &out);
	event->window = out.integerValue->contents;
	DirectGetSlot(i, "message-type", &out);
	event->message_type = out.integerValue->contents;
	DirectGetSlot(i, "format", &out);
	event->format = out.integerValue->contents;
	DirectGetSlot(i, "data", &out);
	if (event->format == 8 && out.multifieldValue->length >= 28)
	{
		for (int x = 0; x < 20; x++)
		{
			if (out.multifieldValue->contents[3 + x].header->type == INTEGER_TYPE)
			event->data.b[x] = out.multifieldValue->contents[3 + x].integerValue->contents;
		}
	}
	else if (event->format == 16)
	{
		for (int x = 0; x < 10; x++)
		{
			if (out.multifieldValue->contents[3 + x].header->type == INTEGER_TYPE)
			event->data.s[x] = out.multifieldValue->contents[3 + x].integerValue->contents;
		}
	}
	else if (event->format == 32)
	{
		for (int x = 0; x < 5; x++)
		{
			if (out.multifieldValue->contents[3 + x].header->type == INTEGER_TYPE)
			event->data.l[x] = out.multifieldValue->contents[3 + x].integerValue->contents;
		}
	}
}

void InstanceToXMappingEvent(Environment *theEnv, Instance *i, XMappingEvent *event)
{
	CLIPSValue out;
	DirectGetSlot(i, "window", &out);
	event->window = out.integerValue->contents;
	DirectGetSlot(i, "request", &out);
	if (0 == strcmp(out.lexemeValue->contents, "MappingModifier")) event->request = MappingModifier;
	else if (0 == strcmp(out.lexemeValue->contents, "MappingKeyboard")) event->request = MappingKeyboard;
	else if (0 == strcmp(out.lexemeValue->contents, "MappingPointer")) event->request = MappingPointer;
	DirectGetSlot(i, "first-keycode", &out);
	event->first_keycode = out.integerValue->contents;
	DirectGetSlot(i, "count", &out);
	event->count = out.integerValue->contents;
}

void InstanceToXGenericEvent(Environment *theEnv, Instance *i, XGenericEvent *event)
{
	CLIPSValue out;
	DirectGetSlot(i, "extension", &out);
	event->extension = out.integerValue->contents;
	DirectGetSlot(i, "evtype", &out);
	event->evtype = out.integerValue->contents;
}

void InstanceToXEvent(Environment *theEnv, Instance *i, XEvent *event)
{
	CLIPSValue out;
	DirectGetSlot(i, "type", &out);
	if (0 == strcmp(out.lexemeValue->contents, "KeyPress"))
	{
		event->xkey.type = KeyPress;
		InstanceToXKeyEvent(theEnv, i, &(event->xkey));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "KeyRelease"))
	{
		event->xkey.type = KeyRelease;
		InstanceToXKeyEvent(theEnv, i, &(event->xkey));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "ButtonPress"))
	{
		event->xbutton.type = ButtonPress;
		InstanceToXButtonEvent(theEnv, i, &(event->xbutton));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "ButtonRelease"))
	{
		event->xbutton.type = ButtonRelease;
		InstanceToXButtonEvent(theEnv, i, &(event->xbutton));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "MotionNotify"))
	{
		event->xmotion.type = ButtonRelease;
		InstanceToXMotionEvent(theEnv, i, &(event->xmotion));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "EnterNotify"))
	{
		event->xcrossing.type = EnterNotify;
		InstanceToXCrossingEvent(theEnv, i, &(event->xcrossing));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "LeaveNotify"))
	{
		event->xcrossing.type = LeaveNotify;
		InstanceToXCrossingEvent(theEnv, i, &(event->xcrossing));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "FocusIn"))
	{
		event->xfocus.type = FocusIn;
		InstanceToXFocusChangeEvent(theEnv, i, &(event->xfocus));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "FocusOut"))
	{
		event->xfocus.type = FocusOut;
		InstanceToXFocusChangeEvent(theEnv, i, &(event->xfocus));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "KeymapNotify"))
	{
		event->xkeymap.type = KeymapNotify;
		InstanceToXKeymapEvent(theEnv, i, &(event->xkeymap));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "Expose"))
	{
		event->xexpose.type = Expose;
		InstanceToXExposeEvent(theEnv, i, &(event->xexpose));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "GraphicsExpose"))
	{
		event->xgraphicsexpose.type = GraphicsExpose;
		InstanceToXGraphicsExposeEvent(theEnv, i, &(event->xgraphicsexpose));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "NoExpose"))
	{
		event->xnoexpose.type = NoExpose;
		InstanceToXNoExposeEvent(theEnv, i, &(event->xnoexpose));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "VisibilityNotify"))
	{
		event->xvisibility.type = VisibilityNotify;
		InstanceToXVisibilityEvent(theEnv, i, &(event->xvisibility));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "CreateNotify"))
	{
		event->xcreatewindow.type = CreateNotify;
		InstanceToXCreateWindowEvent(theEnv, i, &(event->xcreatewindow));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "DestroyNotify"))
	{
		event->xdestroywindow.type = DestroyNotify;
		InstanceToXDestroyWindowEvent(theEnv, i, &(event->xdestroywindow));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "UnmapNotify"))
	{
		event->xunmap.type = UnmapNotify;
		InstanceToXUnmapEvent(theEnv, i, &(event->xunmap));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "MapNotify"))
	{
		event->xmap.type = MapNotify;
		InstanceToXMapEvent(theEnv, i, &(event->xmap));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "MapRequest"))
	{
		event->xmaprequest.type = MapRequest;
		InstanceToXMapRequestEvent(theEnv, i, &(event->xmaprequest));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "ReparentNotify"))
	{
		event->xreparent.type = ReparentNotify;
		InstanceToXReparentEvent(theEnv, i, &(event->xreparent));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "ConfigureNotify"))
	{
		event->xconfigure.type = ConfigureNotify;
		InstanceToXConfigureEvent(theEnv, i, &(event->xconfigure));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "ConfigureRequest"))
	{
		event->xconfigurerequest.type = ConfigureRequest;
		InstanceToXConfigureRequestEvent(theEnv, i, &(event->xconfigurerequest));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "GravityNotify"))
	{
		event->xgravity.type = GravityNotify;
		InstanceToXGravityEvent(theEnv, i, &(event->xgravity));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "ResizeRequest"))
	{
		event->xresizerequest.type = ResizeRequest;
		InstanceToXResizeRequestEvent(theEnv, i, &(event->xresizerequest));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "CirculateNotify"))
	{
		event->xcirculate.type = CirculateNotify;
		InstanceToXCirculateEvent(theEnv, i, &(event->xcirculate));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "CirculateRequest"))
	{
		event->xcirculaterequest.type = CirculateRequest;
		InstanceToXCirculateRequestEvent(theEnv, i, &(event->xcirculaterequest));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "PropertyNotify"))
	{
		event->xproperty.type = PropertyNotify;
		InstanceToXPropertyEvent(theEnv, i, &(event->xproperty));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "SelectionClear"))
	{
		event->xselectionclear.type = SelectionClear;
		InstanceToXSelectionClearEvent(theEnv, i, &(event->xselectionclear));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "SelectionRequest"))
	{
		event->xselectionrequest.type = SelectionRequest;
		InstanceToXSelectionRequestEvent(theEnv, i, &(event->xselectionrequest));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "SelectionNotify"))
	{
		event->xselection.type = SelectionNotify;
		InstanceToXSelectionEvent(theEnv, i, &(event->xselection));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "ColormapNotify"))
	{
		event->xcolormap.type = ColormapNotify;
		InstanceToXColormapEvent(theEnv, i, &(event->xcolormap));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "ClientMessage"))
	{
		event->xclient.type = ClientMessage;
		InstanceToXClientMessageEvent(theEnv, i, &(event->xclient));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "MappingNotify"))
	{
		event->xmapping.type = MappingNotify;
		InstanceToXMappingEvent(theEnv, i, &(event->xmapping));
	}
	else
	if (0 == strcmp(out.lexemeValue->contents, "GenericEvent"))
	{
		event->xgeneric.type = GenericEvent;
		InstanceToXGenericEvent(theEnv, i, &(event->xgeneric));
	}
	else
	{
		WriteString(theEnv, STDERR, "Event '");
		WriteString(theEnv, STDERR, out.lexemeValue->contents);
		WriteString(theEnv, STDERR, "' not supported.\n");
	}
}

void XSendEventFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	Window window;
	bool propagate;
	long event_mask = 0;
	XEvent event = { 0 };
	UDFValue theArg;

	UDFNextArgument(context, EXTERNAL_ADDRESS_BIT, &theArg);
	display = (Display *) theArg.externalAddressValue->contents;

	UDFNextArgument(context, INTEGER_BIT, &theArg);
	window = (Window) theArg.integerValue->contents;

	UDFNextArgument(context, SYMBOL_BIT, &theArg);
	propagate = theArg.lexemeValue == theEnv->TrueSymbol;

	UDFNextArgument(context, INTEGER_BIT, &theArg);
	event_mask = theArg.integerValue->contents;

	UDFNextArgument(context, FACT_ADDRESS_BIT|INSTANCE_BITS|MULTIFIELD_BIT, &theArg);
	switch (theArg.header->type)
	{
		case MULTIFIELD_TYPE:
			MultifieldToXEvent(theEnv, theArg.multifieldValue, &event);
			break;
		case FACT_ADDRESS_TYPE:
			FactToXEvent(theEnv, theArg.factValue, &event);
			break;
		case INSTANCE_ADDRESS_TYPE:
			InstanceToXEvent(theEnv, theArg.instanceValue, &event);
			break;
		default:
			WriteString(theEnv, STDERR, "Passed event was not a multifield, fact, or instance.\n");
			returnValue->integerValue->contents = 0;
			return;
	}

	returnValue->integerValue = CreateInteger(theEnv, XSendEvent(display, window, propagate, event_mask, &event));
}

void XDrawArcFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	Drawable drawable;
	GC gc;
	int x, y;
	unsigned int width, height;
	int angle1, angle2;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	drawable = theArg.integerValue->contents;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	gc = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	x = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	y = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	width = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	height = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	angle1 = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	angle2 = theArg.integerValue->contents;

	XDrawArc(display, drawable, gc, x, y, width, height, angle1, angle2);
}

void XDrawLineFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	Drawable drawable;
	GC gc;
	int x1, y1, x2, y2;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	drawable = theArg.integerValue->contents;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	gc = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	x1 = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	y1 = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	x2 = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	y2 = theArg.integerValue->contents;

	XDrawLine(display, drawable, gc, x1, y1, x2, y2);
}

void XDrawPointFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	Drawable drawable;
	GC gc;
	int x, y;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	drawable = theArg.integerValue->contents;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	gc = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	x = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	y = theArg.integerValue->contents;

	XDrawPoint(display, drawable, gc, x, y);
}

void XDrawRectangleFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	Drawable drawable;
	GC gc;
	int x, y;
	unsigned int width, height;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	drawable = theArg.integerValue->contents;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	gc = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	x = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	y = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	width = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	height = theArg.integerValue->contents;

	XDrawRectangle(display, drawable, gc, x, y, width, height);
}

void XDrawStringFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	Drawable drawable;
	GC gc;
	int x, y;
	const char *str;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	drawable = theArg.integerValue->contents;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	gc = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	x = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	y = theArg.integerValue->contents;

	UDFNextArgument(context,LEXEME_BITS,&theArg);
	str = theArg.lexemeValue->contents;

	XDrawString(display, drawable, gc, x, y, str, strlen(str));
}

void XSelectInputFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	Window window;
	int to_add;
	long event_mask = 0;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	window = theArg.integerValue->contents;

	if (!UDFHasNextArgument(context))
	{
		XSelectInput(display, window, NoEventMask);

		return;
	}

	while (UDFHasNextArgument(context))
	{
		UDFNextArgument(context,SYMBOL_BIT,&theArg);
		to_add = StringToEventMask(theArg.lexemeValue->contents);
		if (to_add != -1)
		{
			event_mask |= to_add;
		}
	}
			
	XSelectInput(display, window, event_mask);
}

void XSetInputFocusFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	int focus, revert_to, time;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	focus = theArg.integerValue->contents;

	UDFNextArgument(context,SYMBOL_BIT,&theArg);
	revert_to = 0;
	if (0 == strcmp(theArg.lexemeValue->contents, "RevertToParent"))
	{
		revert_to = RevertToParent;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "RevertToPointerRoot"))
	{
		revert_to = RevertToPointerRoot;
	}
	else if (0 == strcmp(theArg.lexemeValue->contents, "RevertToNone"))
	{
		revert_to = RevertToNone;
	}

	time = 0;
	if (UDFHasNextArgument(context))
	{
		UDFNextArgument(context,INTEGER_BIT,&theArg);
		time = theArg.integerValue->contents;
	}

	XSetInputFocus(display, focus, revert_to, time);
}


void XLookupStringFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	XEvent *event;
	XKeyEvent key_event;
	char buffer[10];
	KeySym keysym;
	MultifieldBuilder *mb;
	int len;

	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	event = theArg.externalAddressValue->contents;
	key_event = event->xkey;

	len = XLookupString(&key_event, buffer, sizeof(buffer)-1, &keysym, NULL);
	if (len > 0) {
		buffer[len] = '\0';
	}
	mb = CreateMultifieldBuilder(theEnv, 2);
	MBAppendString(mb, buffer);
	MBAppendInteger(mb, keysym);
	returnValue->multifieldValue = MBCreate(mb);
	MBDispose(mb);
}

void XStringToKeysymFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	UDFValue theArg;

	UDFNextArgument(context,LEXEME_BITS,&theArg);

	returnValue->integerValue = CreateInteger(theEnv, (unsigned long)XStringToKeysym(theArg.lexemeValue->contents));
}

void XKeysymToKeycodeFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);

	returnValue->integerValue = CreateInteger(theEnv, (unsigned char)XKeysymToKeycode(display, theArg.integerValue->contents));
}

void XGrabButtonFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Cursor cursor;
	Display *display;
	unsigned int button;
	Window confine_to, grab_window;
	unsigned int event_mask, modifiers;
	bool owner_events;
	int pointer_mode, keyboard_mode;

	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	button = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	modifiers = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	grab_window = (Window)theArg.integerValue->contents;

	UDFNextArgument(context,BOOLEAN_BIT,&theArg);
	owner_events = theArg.lexemeValue == theEnv->TrueSymbol;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	event_mask = theArg.integerValue->contents;

	UDFNextArgument(context,SYMBOL_BIT,&theArg);
	if (0 == strcmp(theArg.lexemeValue->contents, "GrabModeSync"))
	{
		pointer_mode = 0;
	}
	else
	{
		pointer_mode = 1;
	}

	UDFNextArgument(context,SYMBOL_BIT,&theArg);
	if (0 == strcmp(theArg.lexemeValue->contents, "GrabModeSync"))
	{
		keyboard_mode = 0;
	}
	else
	{
		keyboard_mode = 1;
	}

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	confine_to = (Window)theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	cursor = (Cursor)theArg.integerValue->contents;

	returnValue->integerValue = CreateInteger(theEnv, XGrabButton(display, button, modifiers, grab_window, owner_events, event_mask, pointer_mode, keyboard_mode, confine_to, cursor));
}

void XUngrabButtonFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	unsigned int button;
	Window grab_window;
	unsigned int modifiers;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	button = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	modifiers = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	grab_window = (Window)theArg.integerValue->contents;

	XUngrabButton(display, button, modifiers, grab_window);
}

void XGrabKeyFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	unsigned char keycode;
	Window grab_window;
	unsigned int modifiers;
	bool owner_events;
	int pointer_mode, keyboard_mode;

	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	keycode = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	modifiers = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	grab_window = (Window)theArg.integerValue->contents;

	UDFNextArgument(context,BOOLEAN_BIT,&theArg);
	owner_events = theArg.lexemeValue == theEnv->TrueSymbol;

	UDFNextArgument(context,SYMBOL_BIT,&theArg);
	if (0 == strcmp(theArg.lexemeValue->contents, "GrabModeSync"))
	{
		pointer_mode = 0;
	}
	else
	{
		pointer_mode = 1;
	}

	UDFNextArgument(context,SYMBOL_BIT,&theArg);
	if (0 == strcmp(theArg.lexemeValue->contents, "GrabModeSync"))
	{
		keyboard_mode = 0;
	}
	else
	{
		keyboard_mode = 1;
	}

	returnValue->integerValue = CreateInteger(theEnv, XGrabKey(display, keycode, modifiers, grab_window, owner_events, pointer_mode, keyboard_mode));
}

void XUngrabKeyFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	unsigned char keycode;
	Window grab_window;
	unsigned int modifiers;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	keycode = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	modifiers = theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	grab_window = (Window)theArg.integerValue->contents;

	XUngrabKey(display, keycode, modifiers, grab_window);
}

void XGrabPointerFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Cursor cursor;
	Display *display;
	Time time;
	Window confine_to, grab_window;
	unsigned int event_mask;
	bool owner_events;
	int pointer_mode, keyboard_mode;

	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	grab_window = (Window)theArg.integerValue->contents;

	UDFNextArgument(context,BOOLEAN_BIT,&theArg);
	owner_events = theArg.lexemeValue == theEnv->TrueSymbol;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	event_mask = theArg.integerValue->contents;

	UDFNextArgument(context,SYMBOL_BIT,&theArg);
	if (0 == strcmp(theArg.lexemeValue->contents, "GrabModeSync"))
	{
		pointer_mode = 0;
	}
	else
	{
		pointer_mode = 1;
	}

	UDFNextArgument(context,SYMBOL_BIT,&theArg);
	if (0 == strcmp(theArg.lexemeValue->contents, "GrabModeSync"))
	{
		keyboard_mode = 0;
	}
	else
	{
		keyboard_mode = 1;
	}

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	confine_to = (Window)theArg.integerValue->contents;

	UDFNextArgument(context,INTEGER_BIT,&theArg);
	cursor = (Cursor)theArg.integerValue->contents;

	time = CurrentTime;
	if (UDFHasNextArgument(context))
	{
		UDFNextArgument(context,INTEGER_BIT,&theArg);
		time = theArg.integerValue->contents;
	}

	returnValue->integerValue = CreateInteger(theEnv, XGrabPointer(display, grab_window, owner_events, event_mask, pointer_mode, keyboard_mode, confine_to, cursor, time));
}

void XUngrabPointerFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	Time time;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	time = CurrentTime;
	if (UDFHasNextArgument(context))
	{
		UDFNextArgument(context,INTEGER_BIT,&theArg);
		time = (Time)theArg.integerValue->contents;
	}

	XUngrabPointer(display, time);
}

void XFlushFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);

	returnValue->integerValue = CreateInteger(theEnv, XFlush(theArg.externalAddressValue->contents));
}

void XSyncFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *d;
	bool discard;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	d = theArg.externalAddressValue->contents;

	discard = false;
	if (UDFHasNextArgument(context))
	{
		UDFNextArgument(context,SYMBOL_BIT,&theArg);
		if (theArg.lexemeValue == theEnv->TrueSymbol)
		{
			discard = true;
		}
	}

	returnValue->integerValue = CreateInteger(theEnv, XSync(d, discard));
}

/*********************************************************/
/* UserFunctions: Informs the expert system environment  */
/*   of any user defined functions. In the default case, */
/*   there are no user defined functions. To define      */
/*   functions, either this function must be replaced by */
/*   a function with the same name within this file, or  */
/*   this function can be deleted from this file and     */
/*   included in another file.                           */
/*********************************************************/
void UserFunctions(
  Environment *env)
  {
#if MAC_XCD
#pragma unused(env)
#endif
	  AddUDF(env,"x-open-display","be",0,1,";sy",XOpenDisplayFunction,"XOpenDisplayFunction",NULL);
	  AddUDF(env,"x-close-display","v",1,1,";e",XCloseDisplayFunction,"XCloseDisplayFunction",NULL);
	  AddUDF(env,"default-screen","l",1,1,";e",DefaultScreenFunction,"DefaultScreenFunction",NULL);
	  AddUDF(env,"default-screen-of-display","e",1,1,";e",DefaultScreenOfDisplayFunction,"DefaultScreenOfDisplayFunction",NULL);
	  AddUDF(env,"default-root-window","l",1,1,";e",DefaultRootWindowFunction,"DefaultRootWindowFunction",NULL);
	  AddUDF(env,"root-window","l",2,2,";e;l",RootWindowFunction,"RootWindowFunction",NULL);
	  AddUDF(env,"x-create-simple-window","bl",9,9,";e;l;l;l;l;l;l;l;l",XCreateSimpleWindowFunction,"XCreateSimpleWindowFunction",NULL);
	  AddUDF(env,"x-create-window","bl",12,12,";e;l;l;l;l;l;l;l;l;e;l;e",XCreateWindowFunction,"XCreateWindowFunction",NULL);
	  AddUDF(env,"x-destroy-window","v",2,2,";e;l",XDestroyWindowFunction,"XDestroyWindowFunction",NULL);
	  AddUDF(env,"x-create-font-cursor","bl",2,2,";e;y",XCreateFontCursorFunction,"XCreateFontCursorFunction",NULL);
	  AddUDF(env,"x-define-cursor","v",3,3,";e;l;l",XDefineCursorFunction,"XDefineCursorFunction",NULL);
	  AddUDF(env,"x-map-window","v",2,2,";e;l",XMapWindowFunction,"XMapWindowFunction",NULL);
	  AddUDF(env,"x-unmap-window","v",2,2,";e;l",XUnmapWindowFunction,"XUnmapWindowFunction",NULL);
	  AddUDF(env,"x-reparent-window","v",5,5,";e;l;l;l;l",XReparentWindowFunction,"XReparentWindowFunction",NULL);
	  AddUDF(env,"x-move-resize-window","l",6,6,";e;l;l;l;l;l",XMoveResizeWindowFunction,"XMoveResizeWindowFunction",NULL);
	  AddUDF(env,"x-circulate-subwindows-up","l",2,2,";e;l",XCirculateSubwindowsUpFunction,"XCirculateSubwindowsUpFunction",NULL);
	  AddUDF(env,"x-raise-window","l",2,2,";e;l",XRaiseWindowFunction,"XRaiseWindowFunction",NULL);
	  AddUDF(env,"x-lower-window","l",2,2,";e;l",XLowerWindowFunction,"XLowerWindowFunction",NULL);
	  AddUDF(env,"x-get-window-attributes","mv",2,2,";e;l",XGetWindowAttributesFunction,"XGetWindowAttributesFunction",NULL);
	  AddUDF(env,"x-get-window-attributes-to-fact","mv",2,2,";e;l",XGetWindowAttributesToFactFunction,"XGetWindowAttributesToFactFunction",NULL);
	  AddUDF(env,"x-get-window-attributes-to-instance","mv",2,3,";e;l;sy",XGetWindowAttributesToInstanceFunction,"XGetWindowAttributesToInstanceFunction",NULL);
	  AddUDF(env,"event-mask-to-multifield","m",1,1,";l",EventMaskToMultifieldFunction,"EventMaskToMultifieldFunction",NULL);
	  AddUDF(env,"mask-to-multifield","m",1,1,";l",MaskToMultifieldFunction,"MaskToMultifieldFunction",NULL);
	  AddUDF(env,"event-mask-to-symbol","vy",1,1,";l",EventMaskToSymbolFunction,"EventMaskToSymbolFunction",NULL);
	  AddUDF(env,"mask-to-symbol","vy",1,1,";l",MaskToSymbolFunction,"MaskToSymbolFunction",NULL);
	  AddUDF(env,"x-query-tree","mv",2,2,";e;l",XQueryTreeFunction,"XQueryTreeFunction",NULL);
	  AddUDF(env,"x-kill-client","l",2,2,";e;l",XKillClientFunction,"XKillClientFunction",NULL);
	  AddUDF(env,"screen-to-fact","f",1,1,";e",ScreenToFactFunction,"ScreenToFactFunction",NULL);
	  AddUDF(env,"screen-to-instance","i",1,2,";e;sy",ScreenToInstanceFunction,"ScreenToInstanceFunction",NULL);
	  AddUDF(env,"screen-to-multifield","m",1,1,";e",ScreenToMultifieldFunction,"ScreenToMultifieldFunction",NULL);
	  AddUDF(env,"remove-hints-flags-from-window","v",3,12,";e;l;y;y;y;y;y;y;y;y;y;y",RemoveHintsFlagsFromWindowFunction,"RemoveHintsFlagsFromWindowFunction",NULL);
	  AddUDF(env,"set-window-gravity","v",3,3,";e;l;y",SetWindowGravityFunction,"SetWindowGravityFunction",NULL);
	  AddUDF(env,"x-list-properties","m",2,2,";e;l",XListPropertiesFunction,"XListPropertiesFunction",NULL);
	  AddUDF(env,"x-get-property","ms",3,3,";e;l;sy",XGetPropertyFunction,"XGetPropertyFunction",NULL);
	  AddUDF(env,"x-change-property","v",6,7,";e;l;sy;sy;l;y;lmsy",XChangePropertyFunction,"XChangePropertyFunction",NULL);
	  AddUDF(env,"x-delete-property","v",3,3,";e;l;sy",XDeletePropertyFunction,"XDeletePropertyFunction",NULL);
	  AddUDF(env,"x-get-geometry","m",2,2,";e;l",XGetGeometryFunction,"XGetGeometryFunction",NULL);
	  AddUDF(env,"x-fetch-name","s",2,2,";e;l",XFetchNameFunction,"XFetchNameFunction",NULL);
	  AddUDF(env,"x-store-name","v",3,3,";e;l;sy",XStoreNameFunction,"XStoreNameFunction",NULL);
	  AddUDF(env,"x-get-input-focus","bm",1,1,";e",XGetInputFocusFunction,"XGetInputFocusFunction",NULL);
	  AddUDF(env,"x-warp-pointer","v",9,9,";e;l;l;l;l;l;l;l;l",XWarpPointerFunction,"XWarpPointerFunction",NULL);
	  AddUDF(env,"x-query-pointer","bm",1,1,";e",XQueryPointerFunction,"XQueryPointerFunction",NULL);
	  AddUDF(env,"multifield-to-mask","l",1,1,";m",MultifieldToMaskFunction,"MultifieldToMaskFunction",NULL);
	  AddUDF(env,"multifield-to-event-mask","l",1,1,";m",MultifieldToEventMaskFunction,"MultifieldToEventMaskFunction",NULL);
	  AddUDF(env,"lexeme-to-mask","l",1,1,";sy",LexemeToMaskFunction,"LexemeToMaskFunction",NULL);
	  AddUDF(env,"lexeme-to-event-mask","l",1,1,";sy",LexemeToEventMaskFunction,"LexemeToEventMaskFunction",NULL);

	  AddUDF(env,"black-pixel","l",2,2,";e;l",BlackPixelFunction,"BlackPixelFunction",NULL);
	  AddUDF(env,"white-pixel","l",2,2,";e;l",WhitePixelFunction,"WhitePixelFunction",NULL);

	  AddUDF(env,"x-create-gc","e",3,3,";e;l;l",XCreateGCFunction,"XCreateGCFunction",NULL);
	  AddUDF(env,"x-set-foreground","v",3,3,";e;e;l",XSetForegroundFunction,"XSetForegroundFunction",NULL);

	  AddUDF(env,"x-load-query-font","be",2,2,";e;sy",XLoadQueryFontFunction,"XLoadQueryFontFunction",NULL);
	  AddUDF(env,"x-set-font","be",3,3,";e;e;e",XSetFontFunction,"XSetFontFunction",NULL);

	  AddUDF(env,"x-pending","l",1,1,";e",XPendingFunction,"XPendingFunction",NULL);
	  AddUDF(env,"x-pop-event","v",1,1,";e",XPopEventFunction,"XPopEventFunction",NULL);
	  AddUDF(env,"x-peek-event","bm",1,1,";e",XPeekEventFunction,"XPeekEventFunction",NULL);
	  AddUDF(env,"x-peek-event-to-fact","bf",1,1,";e",XPeekEventToFactFunction,"XPeekEventToFactFunction",NULL);
	  AddUDF(env,"x-peek-event-to-instance","bi",1,2,";e;sy",XPeekEventToInstanceFunction,"XPeekEventToInstanceFunction",NULL);
	  AddUDF(env,"x-next-event","bm",1,1,";e",XNextEventFunction,"XNextEventFunction",NULL);
	  AddUDF(env,"x-next-event-to-fact","bf",1,1,";e",XNextEventToFactFunction,"XNextEventToFactFunction",NULL);
	  AddUDF(env,"x-next-event-to-instance","bi",1,2,";e;sy",XNextEventToInstanceFunction,"XNextEventToInstanceFunction",NULL);
	  AddUDF(env,"x-send-event","l",5,5,";e;l;b;l;fim",XSendEventFunction,"XSendEventFunction",NULL);

	  AddUDF(env,"x-draw-arc","v",9,9,";e;l;e;l;l;l;l;l;l",XDrawArcFunction,"XDrawArcFunction",NULL);
	  AddUDF(env,"x-draw-line","v",7,7,";e;l;e;l;l;l;l",XDrawLineFunction,"XDrawLineFunction",NULL);
	  AddUDF(env,"x-draw-point","v",5,5,";e;l;e;l;l",XDrawPointFunction,"XDrawPointFunction",NULL);
	  AddUDF(env,"x-draw-rectangle","v",7,7,";e;l;e;l;l;l;l",XDrawRectangleFunction,"XDrawRectangleFunction",NULL);
	  AddUDF(env,"x-draw-string","v",6,6,";e;l;e;l;l;sy",XDrawStringFunction,"XDrawStringFunction",NULL);

	  AddUDF(env,"x-select-input","v",3,26,"y;e;l",XSelectInputFunction,"XSelectInputFunction",NULL);
	  AddUDF(env,"x-set-input-focus","v",3,4,";e;l;y;l",XSetInputFocusFunction,"XSetInputFocusFunction",NULL);

	  AddUDF(env,"x-lookup-string","v",1,1,";e",XLookupStringFunction,"XLookupStringFunction",NULL);
	  AddUDF(env,"x-string-to-keysym","l",1,1,";sy",XStringToKeysymFunction,"XStringToKeysymFunction",NULL);
	  AddUDF(env,"x-keysym-to-keycode","l",2,2,";e;l",XKeysymToKeycodeFunction,"XKeysymToKeycodeFunction",NULL);

	  AddUDF(env,"x-grab-button","l",10,10,";e;l;l;l;b;l;l;l;l;l",XGrabButtonFunction,"XGrabButtonFunction",NULL);
	  AddUDF(env,"x-ungrab-button","v",4,4,";e;l;l;l",XUngrabButtonFunction,"XUngrabButtonFunction",NULL);
	  AddUDF(env,"x-grab-key","l",7,7,";e;l;ym;l;b;y;y",XGrabKeyFunction,"XGrabKeyFunction",NULL);
	  AddUDF(env,"x-ungrab-key","v",4,4,";e;l;ly;l",XUngrabKeyFunction,"XUngrabKeyFunction",NULL);
	  AddUDF(env,"x-grab-pointer","l",8,9,";e;l;b;l;l;l;l;l;l",XGrabPointerFunction,"XGrabPointerFunction",NULL);
	  AddUDF(env,"x-ungrab-pointer","v",1,2,";e;l",XUngrabPointerFunction,"XUngrabPointerFunction",NULL);

	  AddUDF(env,"x-flush","l",1,1,";e",XFlushFunction,"XFlushFunction",NULL);
	  AddUDF(env,"x-sync","l",1,2,";e;b",XSyncFunction,"XSyncFunction",NULL);
  }
