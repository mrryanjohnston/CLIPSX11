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

	// Case: string-like (UTF8 or legacy)
	utf8 = XInternAtom(display, "UTF8_STRING", False);
	if (actual_format == 8 && (actual_type == utf8 || actual_type == XA_STRING)) {
		size_t len = (size_t)nitems;
		char *buf = alloca(len + 1);
		for (size_t i = 0; i < len; ++i) {
			buf[i] = ((char *)data)[i];
		}
		buf[len] = '\0';

		returnValue->lexemeValue = CreateString(theEnv, buf);
		XFree(data);
		return;
	}

	// 32-bit decoding
	if (actual_format == 32) {
		unsigned long *arr = (unsigned long *)data;
		void *mb = CreateMultifieldBuilder(theEnv, nitems);

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
		void *mb = CreateMultifieldBuilder(theEnv, nitems);
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
		void *mb = CreateMultifieldBuilder(theEnv, nitems);
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

Multifield *XAnyEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XAnyEvent *e,
		MultifieldBuilder *mb)
{
	MBAppendInteger(mb, e->serial);
	if (e->send_event)
	{
		MBAppendSymbol(mb, "TRUE");
	}
	else
	{
		MBAppendSymbol(mb, "FALSE");
	}
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, e->display));
	MBAppendInteger(mb, e->window);
	return MBCreate(mb);
}

Multifield *StateToMultifield(
		unsigned int state,
		MultifieldBuilder *mb)
{
	if (state & Button1Mask) {
		MBAppendSymbol(mb, "Button1Mask");
	}
	if (state & Button2Mask) {
		MBAppendSymbol(mb, "Button2Mask");
	}
	if (state & Button3Mask) {
		MBAppendSymbol(mb, "Button3Mask");
	}
	if (state & Button4Mask) {
		MBAppendSymbol(mb, "Button4Mask");
	}
	if (state & Button5Mask) {
		MBAppendSymbol(mb, "Button5Mask");
	}
	if (state & ShiftMask) {
		MBAppendSymbol(mb, "ShiftMask");
	}
	if (state & LockMask) {
		MBAppendSymbol(mb, "LockMask");
	}
	if (state & ControlMask) {
		MBAppendSymbol(mb, "ControlMask");
	}
	if (state & Mod1Mask) {
		MBAppendSymbol(mb, "Mod1Mask");
	}
	if (state & Mod2Mask) {
		MBAppendSymbol(mb, "Mod2Mask");
	}
	if (state & Mod3Mask) {
		MBAppendSymbol(mb, "Mod3Mask");
	}
	if (state & Mod4Mask) {
		MBAppendSymbol(mb, "Mod4Mask");
	}
	if (state & Mod5Mask) {
		MBAppendSymbol(mb, "Mod5Mask");
	}
	return MBCreate(mb);
}

Multifield *XKeyEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XKeyEvent *e,
		MultifieldBuilder *mb)
{
	XComposeStatus compose = { 0 };
	MultifieldBuilder *statemb;
	Multifield *statemf;
	char buffer[32];
	KeySym keysym;

	MBAppendInteger(mb, e->root);
	MBAppendInteger(mb, e->subwindow);
	MBAppendInteger(mb, e->time);
	MBAppendInteger(mb, e->x);
	MBAppendInteger(mb, e->y);
	MBAppendInteger(mb, e->x_root);
	MBAppendInteger(mb, e->y_root);
	statemb = CreateMultifieldBuilder(theEnv, 0);
	statemf = StateToMultifield(e->state, statemb);
	MBDispose(statemb);
	if (statemf == NULL)
	{
		WriteString(theEnv,STDERR,"Could not create multifield for x-key-event's state");
		return NULL;
	}
	MBAppendMultifield(mb, statemf);
	MBAppendInteger(mb, e->keycode);
	if (e->same_screen)
	{
		MBAppendSymbol(mb, "TRUE");
	}
	else
	{
		MBAppendSymbol(mb, "FALSE");
	}
	XLookupString(e, buffer, sizeof(buffer), &keysym, &compose);
	MBAppendSymbol(mb, buffer);
	MBAppendInteger(mb, keysym);
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, compose.compose_ptr));
	MBAppendInteger(mb, compose.chars_matched);
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

	MBAppendInteger(mb, e->root);
	MBAppendInteger(mb, e->subwindow);
	MBAppendInteger(mb, e->time);
	MBAppendInteger(mb, e->x);
	MBAppendInteger(mb, e->y);
	MBAppendInteger(mb, e->x_root);
	MBAppendInteger(mb, e->y_root);
	statemb = CreateMultifieldBuilder(theEnv, 0);
	statemf = StateToMultifield(e->state, statemb);
	MBDispose(statemb);
	if (statemf == NULL)
	{
		WriteString(theEnv,STDERR,"Could not create multifield for x-button-event's state");
		return NULL;
	}
	MBAppendMultifield(mb, statemf);
	MBAppendInteger(mb, e->button);
	if (e->same_screen)
	{
		MBAppendSymbol(mb, "TRUE");
	}
	else
	{
		MBAppendSymbol(mb, "FALSE");
	}
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

	MBAppendInteger(mb, e->root);
	MBAppendInteger(mb, e->subwindow);
	MBAppendInteger(mb, e->time);
	MBAppendInteger(mb, e->x);
	MBAppendInteger(mb, e->y);
	MBAppendInteger(mb, e->x_root);
	MBAppendInteger(mb, e->y_root);
	statemb = CreateMultifieldBuilder(theEnv, 0);
	statemf = StateToMultifield(e->state, statemb);
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
	if (e->same_screen)
	{
		MBAppendSymbol(mb, "TRUE");
	}
	else
	{
		MBAppendSymbol(mb, "FALSE");
	}
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

	MBAppendInteger(mb, e->root);
	MBAppendInteger(mb, e->subwindow);
	MBAppendInteger(mb, e->time);
	MBAppendInteger(mb, e->x);
	MBAppendInteger(mb, e->y);
	MBAppendInteger(mb, e->x_root);
	MBAppendInteger(mb, e->y_root);
	MBAppendSymbol(mb, EventModeToStr(e->mode));
	MBAppendSymbol(mb, EventDetailToStr(e->detail));
	if (e->same_screen)
	{
		MBAppendSymbol(mb, "TRUE");
	}
	else
	{
		MBAppendSymbol(mb, "FALSE");
	}
	if (e->focus)
	{
		MBAppendSymbol(mb, "TRUE");
	}
	else
	{
		MBAppendSymbol(mb, "FALSE");
	}
	statemb = CreateMultifieldBuilder(theEnv, 0);
	statemf = StateToMultifield(e->state, statemb);
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
	MBAppendSymbol(mb, VisibilityStateToStr(e->state));

	return MBCreate(mb);
}

Multifield *XCreateWindowEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XCreateWindowEvent *e,
		MultifieldBuilder *mb)
{
	MBAppendInteger(mb, e->parent);
	MBAppendInteger(mb, e->window);
	MBAppendInteger(mb, e->x);
	MBAppendInteger(mb, e->y);
	MBAppendInteger(mb, e->width);
	MBAppendInteger(mb, e->height);
	MBAppendInteger(mb, e->border_width);
	if (e->override_redirect)
	{
		MBAppendSymbol(mb, "TRUE");
	}
	else
	{
		MBAppendSymbol(mb, "FALSE");
	}

	return MBCreate(mb);
}

Multifield *XDestroyWindowEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XDestroyWindowEvent *e,
		MultifieldBuilder *mb)
{

	MBAppendInteger(mb, e->event);
	return MBCreate(mb);
}

Multifield *XUnmapEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XUnmapEvent *e,
		MultifieldBuilder *mb)
{

	MBAppendInteger(mb, e->event);
	if (e->from_configure)
	{
		MBAppendSymbol(mb, "TRUE");
	}
	else
	{
		MBAppendSymbol(mb, "FALSE");
	}
	return MBCreate(mb);
}

Multifield *XMapEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XMapEvent *e,
		MultifieldBuilder *mb)
{
	MBAppendInteger(mb, e->event);
	if (e->override_redirect)
	{
		MBAppendSymbol(mb, "TRUE");
	}
	else
	{
		MBAppendSymbol(mb, "FALSE");
	}
	return MBCreate(mb);
}

Multifield *XMapRequestEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XMapRequestEvent *e,
		MultifieldBuilder *mb)
{
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
	MBAppendInteger(mb, e->event);
	MBAppendInteger(mb, e->parent);
	MBAppendInteger(mb, e->x);
	MBAppendInteger(mb, e->y);
	if (e->override_redirect)
	{
		MBAppendSymbol(mb, "TRUE");
	}
	else
	{
		MBAppendSymbol(mb, "FALSE");
	}
	return MBCreate(mb);
}

Multifield *XConfigureEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XConfigureEvent *e,
		MultifieldBuilder *mb)
{
	MBAppendInteger(mb, e->event);
	MBAppendInteger(mb, e->x);
	MBAppendInteger(mb, e->y);
	MBAppendInteger(mb, e->width);
	MBAppendInteger(mb, e->height);
	MBAppendInteger(mb, e->border_width);
	MBAppendInteger(mb, e->above);
	if (e->override_redirect)
	{
		MBAppendSymbol(mb, "TRUE");
	}
	else
	{
		MBAppendSymbol(mb, "FALSE");
	}
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
	MBAppendInteger(mb, e->event);
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
	MBAppendInteger(mb, e->event);
	MBAppendSymbol(mb, CirculateEventPlaceToStr(e->place));
	return MBCreate(mb);
}

Multifield *XCirculateRequestEventToMultifield(
		Environment *theEnv,
		UDFContext *context,
		XCirculateRequestEvent *e,
		MultifieldBuilder *mb)
{
	MBAppendInteger(mb, e->parent);
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
	if (e->colormap == None)
	{
		MBAppendSymbol(mb, "None");
	}
	else
	{
		MBAppendInteger(mb, e->colormap);
	}
	if (e->new)
	{
		MBAppendSymbol(mb, "TRUE");
	}
	else
	{
		MBAppendSymbol(mb, "FALSE");
	}
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

	Multifield *typedevent;
	MultifieldBuilder *typedeventmb;

	typedeventmb = CreateMultifieldBuilder(theEnv, 0);
	typedevent = XAnyEventToMultifield(theEnv, context, &(e->xany), typedeventmb);
	MBDispose(typedeventmb);
	if (typedevent == NULL)
	{
		WriteString(theEnv,STDERR,"Could not create multifield for x-any-event");
		return NULL;
	}
	MBAppendMultifield(mb, typedevent);

	switch (e->type)
	{
		case KeyPress:
			MBAppendSymbol(mb, "KeyPress");
			typedeventmb = CreateMultifieldBuilder(theEnv, 0);
			typedevent = XKeyEventToMultifield(theEnv, context, &(e->xkey), typedeventmb);
			MBDispose(typedeventmb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not create multifield for x-key-event");
				return NULL;
			}
			MBAppendMultifield(mb, typedevent);
			break;
		case KeyRelease:
			MBAppendSymbol(mb, "KeyRelease");
			typedeventmb = CreateMultifieldBuilder(theEnv, 0);
			typedevent = XKeyEventToMultifield(theEnv, context, &(e->xkey), typedeventmb);
			MBDispose(typedeventmb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not create multifield for x-key-event");
				return NULL;
			}
			MBAppendMultifield(mb, typedevent);
			break;
		case ButtonPress:
			MBAppendSymbol(mb, "ButtonPress");
			typedeventmb = CreateMultifieldBuilder(theEnv, 0);
			typedevent = XButtonEventToMultifield(theEnv, context, &(e->xbutton), typedeventmb);
			MBDispose(typedeventmb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not create multifield for x-button-event");
				return NULL;
			}
			MBAppendMultifield(mb, typedevent);
			break;
		case ButtonRelease:
			MBAppendSymbol(mb, "ButtonRelease");
			typedeventmb = CreateMultifieldBuilder(theEnv, 0);
			typedevent = XButtonEventToMultifield(theEnv, context, &(e->xbutton), typedeventmb);
			MBDispose(typedeventmb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not create multifield for x-button-event");
				return NULL;
			}
			MBAppendMultifield(mb, typedevent);
			break;
		case MotionNotify:
			MBAppendSymbol(mb, "MotionNotify");
			typedeventmb = CreateMultifieldBuilder(theEnv, 0);
			typedevent = XMotionEventToMultifield(theEnv, context, &(e->xmotion), typedeventmb);
			MBDispose(typedeventmb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not create multifield for x-motion-event");
				return NULL;
			}
			MBAppendMultifield(mb, typedevent);
			break;
		case EnterNotify:
			MBAppendSymbol(mb, "EnterNotify");
			typedeventmb = CreateMultifieldBuilder(theEnv, 0);
			typedevent = XCrossingEventToMultifield(theEnv, context, &(e->xcrossing), typedeventmb);
			MBDispose(typedeventmb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not create multifield for x-crossing-event");
				return NULL;
			}
			MBAppendMultifield(mb, typedevent);
			break;
		case LeaveNotify:
			MBAppendSymbol(mb, "LeaveNotify");
			typedeventmb = CreateMultifieldBuilder(theEnv, 0);
			typedevent = XCrossingEventToMultifield(theEnv, context, &(e->xcrossing), typedeventmb);
			MBDispose(typedeventmb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not create multifield for x-crossing-event");
				return NULL;
			}
			MBAppendMultifield(mb, typedevent);
			break;
		case FocusIn:
			MBAppendSymbol(mb, "FocusIn");
			typedeventmb = CreateMultifieldBuilder(theEnv, 0);
			typedevent = XFocusChangeEventToMultifield(theEnv, context, &(e->xfocus), typedeventmb);
			MBDispose(typedeventmb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not create multifield for x-focus-in-event");
				return NULL;
			}
			MBAppendMultifield(mb, typedevent);
			break;
		case FocusOut:
			MBAppendSymbol(mb, "FocusOut");
			typedeventmb = CreateMultifieldBuilder(theEnv, 0);
			typedevent = XFocusChangeEventToMultifield(theEnv, context, &(e->xfocus), typedeventmb);
			MBDispose(typedeventmb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not create multifield for x-focus-in-event");
				return NULL;
			}
			MBAppendMultifield(mb, typedevent);
			break;
		case KeymapNotify:
			MBAppendSymbol(mb, "KeymapNotify");
			typedeventmb = CreateMultifieldBuilder(theEnv, 0);
			typedevent = XKeymapEventToMultifield(theEnv, context, e->xany.display, &e->xkeymap, typedeventmb);
			MBDispose(typedeventmb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not create multifield for x-keymap-notify-event");
				return NULL;
			}
			MBAppendMultifield(mb, typedevent);
			break;
		case Expose:
			MBAppendSymbol(mb, "Expose");
			typedeventmb = CreateMultifieldBuilder(theEnv, 0);
			typedevent = XExposeEventToMultifield(theEnv, context, &(e->xexpose), typedeventmb);
			MBDispose(typedeventmb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not create multifield for x-expose-event");
				return NULL;
			}
			MBAppendMultifield(mb, typedevent);
			break;
		case GraphicsExpose:
			MBAppendSymbol(mb, "GraphicsExpose");
			typedeventmb = CreateMultifieldBuilder(theEnv, 0);
			typedevent = XGraphicsExposeEventToMultifield(theEnv, context, &(e->xgraphicsexpose), typedeventmb);
			MBDispose(typedeventmb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not create multifield for x-graphics-expose-event");
				return NULL;
			}
			MBAppendMultifield(mb, typedevent);
			break;
		case NoExpose:
			MBAppendSymbol(mb, "NoExpose");
			typedeventmb = CreateMultifieldBuilder(theEnv, 0);
			typedevent = XNoExposeEventToMultifield(theEnv, context, &(e->xnoexpose), typedeventmb);
			MBDispose(typedeventmb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not create multifield for x-no-expose-event");
				return NULL;
			}
			MBAppendMultifield(mb, typedevent);
			break;
		case VisibilityNotify:
			MBAppendSymbol(mb, "VisibilityNotify");
			typedeventmb = CreateMultifieldBuilder(theEnv, 0);
			typedevent = XVisibilityEventToMultifield(theEnv, context, &(e->xvisibility), typedeventmb);
			MBDispose(typedeventmb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not create multifield for x-visibility-event");
				return NULL;
			}
			MBAppendMultifield(mb, typedevent);
			break;
		case CreateNotify:
			MBAppendSymbol(mb, "CreateNotify");
			typedeventmb = CreateMultifieldBuilder(theEnv, 0);
			typedevent = XCreateWindowEventToMultifield(theEnv, context, &(e->xcreatewindow), typedeventmb);
			MBDispose(typedeventmb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not create multifield for x-create-window-event");
				return NULL;
			}
			MBAppendMultifield(mb, typedevent);
			break;
		case DestroyNotify:
			MBAppendSymbol(mb, "DestroyNotify");
			typedeventmb = CreateMultifieldBuilder(theEnv, 0);
			typedevent = XDestroyWindowEventToMultifield(theEnv, context, &(e->xdestroywindow), typedeventmb);
			MBDispose(typedeventmb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not destroy multifield for x-destroy-window-event");
				return NULL;
			}
			MBAppendMultifield(mb, typedevent);
			break;
		case UnmapNotify:
			MBAppendSymbol(mb, "UnmapNotify");
			typedeventmb = CreateMultifieldBuilder(theEnv, 0);
			typedevent = XUnmapEventToMultifield(theEnv, context, &(e->xunmap), typedeventmb);
			MBDispose(typedeventmb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not destroy multifield for x-unmap-event");
				return NULL;
			}
			MBAppendMultifield(mb, typedevent);
			break;
		case MapNotify:
			MBAppendSymbol(mb, "MapNotify");
			typedeventmb = CreateMultifieldBuilder(theEnv, 0);
			typedevent = XMapEventToMultifield(theEnv, context, &(e->xmap), typedeventmb);
			MBDispose(typedeventmb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not destroy multifield for x-map-event");
				return NULL;
			}
			MBAppendMultifield(mb, typedevent);
			break;
		case MapRequest:
			MBAppendSymbol(mb, "MapRequest");
			typedeventmb = CreateMultifieldBuilder(theEnv, 0);
			typedevent = XMapRequestEventToMultifield(theEnv, context, &(e->xmaprequest), typedeventmb);
			MBDispose(typedeventmb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not destroy multifield for x-map-request-event");
				return NULL;
			}
			MBAppendMultifield(mb, typedevent);
			break;
		case ReparentNotify:
			MBAppendSymbol(mb, "ReparentNotify");
			typedeventmb = CreateMultifieldBuilder(theEnv, 0);
			typedevent = XReparentEventToMultifield(theEnv, context, &(e->xreparent), typedeventmb);
			MBDispose(typedeventmb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not destroy multifield for x-reparent-event");
				return NULL;
			}
			MBAppendMultifield(mb, typedevent);
			break;
		case ConfigureNotify:
			MBAppendSymbol(mb, "ConfigureNotify");
			typedeventmb = CreateMultifieldBuilder(theEnv, 0);
			typedevent = XConfigureEventToMultifield(theEnv, context, &(e->xconfigure), typedeventmb);
			MBDispose(typedeventmb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not destroy multifield for x-configure-event");
				return NULL;
			}
			MBAppendMultifield(mb, typedevent);
			break;
		case ConfigureRequest:
			MBAppendSymbol(mb, "ConfigureRequest");
			typedeventmb = CreateMultifieldBuilder(theEnv, 0);
			typedevent = XConfigureRequestEventToMultifield(theEnv, context, &(e->xconfigurerequest), typedeventmb);
			MBDispose(typedeventmb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not destroy multifield for x-configure-request-event");
				return NULL;
			}
			MBAppendMultifield(mb, typedevent);
			break;
		case GravityNotify:
			MBAppendSymbol(mb, "GravityNotify");
			typedeventmb = CreateMultifieldBuilder(theEnv, 0);
			typedevent = XGravityEventToMultifield(theEnv, context, &(e->xgravity), typedeventmb);
			MBDispose(typedeventmb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not destroy multifield for x-gravity-event");
				return NULL;
			}
			MBAppendMultifield(mb, typedevent);
			break;
		case ResizeRequest:
			MBAppendSymbol(mb, "ResizeRequest");
			typedeventmb = CreateMultifieldBuilder(theEnv, 0);
			typedevent = XResizeRequestEventToMultifield(theEnv, context, &(e->xresizerequest), typedeventmb);
			MBDispose(typedeventmb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not destroy multifield for x-resize-request-event");
				return NULL;
			}
			MBAppendMultifield(mb, typedevent);
			break;
		case CirculateNotify:
			MBAppendSymbol(mb, "CirculateNotify");
			typedeventmb = CreateMultifieldBuilder(theEnv, 0);
			typedevent = XCirculateEventToMultifield(theEnv, context, &(e->xcirculate), typedeventmb);
			MBDispose(typedeventmb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not destroy multifield for x-circulate-event");
				return NULL;
			}
			MBAppendMultifield(mb, typedevent);
			break;
		case CirculateRequest:
			MBAppendSymbol(mb, "CirculateRequest");
			typedeventmb = CreateMultifieldBuilder(theEnv, 0);
			typedevent = XCirculateRequestEventToMultifield(theEnv, context, &(e->xcirculaterequest), typedeventmb);
			MBDispose(typedeventmb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not destroy multifield for x-circulate-request-event");
				return NULL;
			}
			MBAppendMultifield(mb, typedevent);
			break;
		case PropertyNotify:
			MBAppendSymbol(mb, "PropertyNotify");
			typedeventmb = CreateMultifieldBuilder(theEnv, 0);
			typedevent = XPropertyEventToMultifield(theEnv, context, &(e->xproperty), typedeventmb);
			MBDispose(typedeventmb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not destroy multifield for x-property-event");
				return NULL;
			}
			MBAppendMultifield(mb, typedevent);
			break;
		case SelectionClear:
			MBAppendSymbol(mb, "SelectionClear");
			typedeventmb = CreateMultifieldBuilder(theEnv, 0);
			typedevent = XSelectionClearEventToMultifield(theEnv, context, &(e->xselectionclear), typedeventmb);
			MBDispose(typedeventmb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not destroy multifield for x-selection-clear-event");
				return NULL;
			}
			MBAppendMultifield(mb, typedevent);
			break;
		case SelectionRequest:
			MBAppendSymbol(mb, "SelectionRequest");
			typedeventmb = CreateMultifieldBuilder(theEnv, 0);
			typedevent = XSelectionRequestEventToMultifield(theEnv, context, &(e->xselectionrequest), typedeventmb);
			MBDispose(typedeventmb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not destroy multifield for x-selection-request-event");
				return NULL;
			}
			MBAppendMultifield(mb, typedevent);
			break;
		case SelectionNotify:
			MBAppendSymbol(mb, "SelectionNotify");
			typedeventmb = CreateMultifieldBuilder(theEnv, 0);
			typedevent = XSelectionEventToMultifield(theEnv, context, &(e->xselection), typedeventmb);
			MBDispose(typedeventmb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not destroy multifield for x-selection-event");
				return NULL;
			}
			MBAppendMultifield(mb, typedevent);
			break;
		case ColormapNotify:
			MBAppendSymbol(mb, "ColormapNotify");
			typedeventmb = CreateMultifieldBuilder(theEnv, 0);
			typedevent = XColormapEventToMultifield(theEnv, context, &(e->xcolormap), typedeventmb);
			MBDispose(typedeventmb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not destroy multifield for x-colormap-event");
				return NULL;
			}
			MBAppendMultifield(mb, typedevent);
			break;
		case ClientMessage:
			MBAppendSymbol(mb, "ClientMessage");
			typedeventmb = CreateMultifieldBuilder(theEnv, 0);
			typedevent = XClientMessageEventToMultifield(theEnv, context, &(e->xclient), typedeventmb);
			MBDispose(typedeventmb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not destroy multifield for x-client-message-event");
				return NULL;
			}
			MBAppendMultifield(mb, typedevent);
			break;
		case MappingNotify:
			MBAppendSymbol(mb, "MappingNotify");
			typedeventmb = CreateMultifieldBuilder(theEnv, 0);
			typedevent = XMappingEventToMultifield(theEnv, context, &(e->xmapping), typedeventmb);
			MBDispose(typedeventmb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not destroy multifield for x-mapping-event");
				return NULL;
			}
			MBAppendMultifield(mb, typedevent);
			break;
		case GenericEvent:
			MBAppendSymbol(mb, "GenericEvent");
			typedeventmb = CreateMultifieldBuilder(theEnv, 0);
			typedevent = XGenericEventToMultifield(theEnv, context, &(e->xgeneric), typedeventmb);
			MBDispose(typedeventmb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not create x-generic-event multifield");
				return NULL;
			}
			break;
		default:
			WriteString(theEnv,STDERR,"Event Type ");
			WriteInteger(theEnv,STDERR,e->type);
			WriteString(theEnv,STDERR," not supported.\n");
			return NULL;
	}
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
	XComposeStatus compose = { 0 };
	MultifieldBuilder *mb;
	Multifield *mf;
	char buffer[32];
	KeySym keysym;

	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotInteger(fb, "root", e->root);
	FBPutSlotInteger(fb, "subwindow", e->subwindow);
	FBPutSlotInteger(fb, "time", e->time);
	FBPutSlotInteger(fb, "x", e->x);
	FBPutSlotInteger(fb, "y", e->y);
	FBPutSlotInteger(fb, "x-root", e->x_root);
	FBPutSlotInteger(fb, "y-root", e->y_root);
	mb = CreateMultifieldBuilder(theEnv, 0);
	mf = StateToMultifield(e->state, mb);
	MBDispose(mb);
	if (mf == NULL)
	{
		WriteString(theEnv,STDERR,"Could not create multifield for x-key-event's state");
		return NULL;
	}
	FBPutSlotMultifield(fb, "state", mf);
	FBPutSlotInteger(fb, "keycode", e->keycode);
	if (e->same_screen)
	{
		FBPutSlotSymbol(fb, "same-screen", "TRUE");
	}
	else
	{
		FBPutSlotSymbol(fb, "same-screen", "FALSE");
	}
	XLookupString(e, buffer, sizeof(buffer), &keysym, &compose);
	FBPutSlotString(fb, "buffer", buffer);
	FBPutSlotInteger(fb, "keysym", keysym);
	FBPutSlotCLIPSExternalAddress(fb, "compose-ptr", CreateCExternalAddress(theEnv, compose.compose_ptr));
	FBPutSlotInteger(fb, "chars-matched", compose.chars_matched);

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

	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotInteger(fb, "root", e->root);
	FBPutSlotInteger(fb, "subwindow", e->subwindow);
	FBPutSlotInteger(fb, "time", e->time);
	FBPutSlotInteger(fb, "x", e->x);
	FBPutSlotInteger(fb, "y", e->y);
	FBPutSlotInteger(fb, "x-root", e->x_root);
	FBPutSlotInteger(fb, "y-root", e->y_root);
	mb = CreateMultifieldBuilder(theEnv, 0);
	mf = StateToMultifield(e->state, mb);
	MBDispose(mb);
	if (mf == NULL)
	{
		WriteString(theEnv,STDERR,"Could not create multifield for x-button-event's state");
		return NULL;
	}
	FBPutSlotMultifield(fb, "state", mf);
	FBPutSlotInteger(fb, "button", e->button);
	if (e->same_screen)
	{
		FBPutSlotSymbol(fb, "same-screen", "TRUE");
	}
	else
	{
		FBPutSlotSymbol(fb, "same-screen", "FALSE");
	}

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

	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotInteger(fb, "root", e->root);
	FBPutSlotInteger(fb, "subwindow", e->subwindow);
	FBPutSlotInteger(fb, "time", e->time);
	FBPutSlotInteger(fb, "x", e->x);
	FBPutSlotInteger(fb, "y", e->y);
	FBPutSlotInteger(fb, "x-root", e->x_root);
	FBPutSlotInteger(fb, "y-root", e->y_root);
	mb = CreateMultifieldBuilder(theEnv, 0);
	mf = StateToMultifield(e->state, mb);
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
	if (e->same_screen)
	{
		FBPutSlotSymbol(fb, "same-screen", "TRUE");
	}
	else
	{
		FBPutSlotSymbol(fb, "same-screen", "FALSE");
	}

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

	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotInteger(fb, "root", e->root);
	FBPutSlotInteger(fb, "subwindow", e->subwindow);
	FBPutSlotInteger(fb, "time", e->time);
	FBPutSlotInteger(fb, "x", e->x);
	FBPutSlotInteger(fb, "y", e->y);
	FBPutSlotInteger(fb, "x-root", e->x_root);
	FBPutSlotInteger(fb, "y-root", e->y_root);
	FBPutSlotSymbol(fb, "mode", EventModeToStr(e->mode));
	FBPutSlotSymbol(fb, "detail", EventDetailToStr(e->detail));
	if (e->same_screen)
	{
		FBPutSlotSymbol(fb, "same-screen", "TRUE");
	}
	else
	{
		FBPutSlotSymbol(fb, "same-screen", "FALSE");
	}
	if (e->focus)
	{
		FBPutSlotSymbol(fb, "focus", "TRUE");
	}
	else
	{
		FBPutSlotSymbol(fb, "focus", "FALSE");
	}
	mb = CreateMultifieldBuilder(theEnv, 0);
	mf = StateToMultifield(e->state, mb);
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
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
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

	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));

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
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
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
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
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
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
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
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotSymbol(fb, "state", VisibilityStateToStr(e->state));

	return FBAssert(fb);
}

Fact *XCreateWindowEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XCreateWindowEvent *e,
		FactBuilder *fb)
{
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotInteger(fb, "parent", e->parent);
	FBPutSlotInteger(fb, "window", e->window);
	FBPutSlotInteger(fb, "x", e->x);
	FBPutSlotInteger(fb, "y", e->y);
	FBPutSlotInteger(fb, "width", e->width);
	FBPutSlotInteger(fb, "height", e->height);
	FBPutSlotInteger(fb, "border-width", e->border_width);
	if (e->override_redirect)
	{
		FBPutSlotSymbol(fb, "override-redirect", "TRUE");
	}
	else
	{
		FBPutSlotSymbol(fb, "override-redirect", "FALSE");
	}

	return FBAssert(fb);
}

Fact *XDestroyWindowEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XDestroyWindowEvent *e,
		FactBuilder *fb)
{

	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotInteger(fb, "event", e->event);
	return FBAssert(fb);
}

Fact *XUnmapEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XUnmapEvent *e,
		FactBuilder *fb)
{

	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotInteger(fb, "event", e->event);
	if (e->from_configure)
	{
		FBPutSlotSymbol(fb, "from-configure", "TRUE");
	}
	else
	{
		FBPutSlotSymbol(fb, "from-configure", "FALSE");
	}
	return FBAssert(fb);
}

Fact *XMapEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XMapEvent *e,
		FactBuilder *fb)
{
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotInteger(fb, "event", e->event);
	if (e->override_redirect)
	{
		FBPutSlotSymbol(fb, "override-redirect", "TRUE");
	}
	else
	{
		FBPutSlotSymbol(fb, "override-redirect", "FALSE");
	}
	return FBAssert(fb);
}

Fact *XMapRequestEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XMapRequestEvent *e,
		FactBuilder *fb)
{
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
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
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotInteger(fb, "event", e->event);
	FBPutSlotInteger(fb, "parent", e->parent);
	FBPutSlotInteger(fb, "x", e->x);
	FBPutSlotInteger(fb, "y", e->y);
	if (e->override_redirect)
	{
		FBPutSlotSymbol(fb, "override-redirect", "TRUE");
	}
	else
	{
		FBPutSlotSymbol(fb, "override-redirect", "FALSE");
	}
	return FBAssert(fb);
}

Fact *XConfigureEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XConfigureEvent *e,
		FactBuilder *fb)
{
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotInteger(fb, "event", e->event);
	FBPutSlotInteger(fb, "x", e->x);
	FBPutSlotInteger(fb, "y", e->y);
	FBPutSlotInteger(fb, "width", e->width);
	FBPutSlotInteger(fb, "height", e->height);
	FBPutSlotInteger(fb, "border-width", e->border_width);
	FBPutSlotInteger(fb, "above", e->above);
	if (e->override_redirect)
	{
		FBPutSlotSymbol(fb, "override-redirect", "TRUE");
	}
	else
	{
		FBPutSlotSymbol(fb, "override-redirect", "FALSE");
	}
	return FBAssert(fb);
}

Fact *XConfigureRequestEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XConfigureRequestEvent *e,
		FactBuilder *fb)
{
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
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
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotInteger(fb, "event", e->event);
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
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
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
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotInteger(fb, "event", e->event);
	FBPutSlotSymbol(fb, "place", CirculateEventPlaceToStr(e->place));
	return FBAssert(fb);
}

Fact *XCirculateRequestEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XCirculateRequestEvent *e,
		FactBuilder *fb)
{
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	FBPutSlotInteger(fb, "parent", e->parent);
	FBPutSlotSymbol(fb, "place", CirculateEventPlaceToStr(e->place));
	return FBAssert(fb);
}

Fact *XPropertyEventToFact(
		Environment *theEnv,
		UDFContext *context,
		XPropertyEvent *e,
		FactBuilder *fb)
{
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
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
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
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
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
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
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
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
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	if (e->colormap == None)
	{
		FBPutSlotSymbol(fb, "colormap", "None");
	}
	else
	{
		FBPutSlotInteger(fb, "colormap", e->colormap);
	}
	if (e->new)
	{
		FBPutSlotSymbol(fb, "new", "TRUE");
	}
	else
	{
		FBPutSlotSymbol(fb, "new", "FALSE");
	}
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

	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
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
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
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
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
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
	FBPutSlotCLIPSExternalAddress(fb, "c-pointer", CreateCExternalAddress(theEnv, e));
	Fact *typedevent;
	FactBuilder *typedeventfb;

	typedeventfb = CreateFactBuilder(theEnv, "x-any-event");
	typedevent = XAnyEventToFact(theEnv, context, &(e->xany), typedeventfb);
	FBDispose(typedeventfb);
	if (typedevent == NULL)
	{
		WriteString(theEnv,STDERR,"Could not assert x-any-event fact\n");
		ReportFBAssertError(theEnv);
		return NULL;
	}
	FBPutSlotFact(fb, "x-any-event", typedevent);

	switch (e->type)
	{
		case KeyPress:
			FBPutSlotSymbol(fb, "type", "KeyPress");
			typedeventfb = CreateFactBuilder(theEnv, "x-key-event");
			typedevent = XKeyEventToFact(theEnv, context, &(e->xkey), typedeventfb);
			FBDispose(typedeventfb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not assert x-key-event fact");
				ReportFBAssertError(theEnv);
				return NULL;
			}
			FBPutSlotFact(fb, "typed-event", typedevent);
			break;
		case KeyRelease:
			FBPutSlotSymbol(fb, "type", "KeyRelease");
			typedeventfb = CreateFactBuilder(theEnv, "x-key-event");
			typedevent = XKeyEventToFact(theEnv, context, &(e->xkey), typedeventfb);
			FBDispose(typedeventfb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not assert x-key-event fact");
				ReportFBAssertError(theEnv);
				return NULL;
			}
			FBPutSlotFact(fb, "typed-event", typedevent);
			break;
		case ButtonPress:
			FBPutSlotSymbol(fb, "type", "ButtonPress");
			typedeventfb = CreateFactBuilder(theEnv, "x-button-event");
			typedevent = XButtonEventToFact(theEnv, context, &(e->xbutton), typedeventfb);
			FBDispose(typedeventfb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not assert x-button-event fact");
				ReportFBAssertError(theEnv);
				return NULL;
			}
			FBPutSlotFact(fb, "typed-event", typedevent);
			break;
		case ButtonRelease:
			FBPutSlotSymbol(fb, "type", "ButtonRelease");
			typedeventfb = CreateFactBuilder(theEnv, "x-button-event");
			typedevent = XButtonEventToFact(theEnv, context, &(e->xbutton), typedeventfb);
			FBDispose(typedeventfb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not assert x-button-event fact");
				ReportFBAssertError(theEnv);
				return NULL;
			}
			FBPutSlotFact(fb, "typed-event", typedevent);
			break;
		case MotionNotify:
			FBPutSlotSymbol(fb, "type", "MotionNotify");
			typedeventfb = CreateFactBuilder(theEnv, "x-motion-event");
			typedevent = XMotionEventToFact(theEnv, context, &(e->xmotion), typedeventfb);
			FBDispose(typedeventfb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not assert x-motion-event fact");
				ReportFBAssertError(theEnv);
				return NULL;
			}
			FBPutSlotFact(fb, "typed-event", typedevent);
			break;
		case EnterNotify:
			FBPutSlotSymbol(fb, "type", "EnterNotify");
			typedeventfb = CreateFactBuilder(theEnv, "x-crossing-event");
			typedevent = XCrossingEventToFact(theEnv, context, &(e->xcrossing), typedeventfb);
			FBDispose(typedeventfb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not assert x-crossing-event fact");
				ReportFBAssertError(theEnv);
				return NULL;
			}
			FBPutSlotFact(fb, "typed-event", typedevent);
			break;
		case LeaveNotify:
			FBPutSlotSymbol(fb, "type", "LeaveNotify");
			typedeventfb = CreateFactBuilder(theEnv, "x-crossing-event");
			typedevent = XCrossingEventToFact(theEnv, context, &(e->xcrossing), typedeventfb);
			FBDispose(typedeventfb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not assert x-crossing-event fact");
				ReportFBAssertError(theEnv);
				return NULL;
			}
			FBPutSlotFact(fb, "typed-event", typedevent);
			break;
		case FocusIn:
			FBPutSlotSymbol(fb, "type", "FocusIn");
			typedeventfb = CreateFactBuilder(theEnv, "x-focus-change-event");
			typedevent = XFocusChangeEventToFact(theEnv, context, &(e->xfocus), typedeventfb);
			FBDispose(typedeventfb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not assert x-focus-change-event fact");
				ReportFBAssertError(theEnv);
				return NULL;
			}
			FBPutSlotFact(fb, "typed-event", typedevent);
			break;
		case FocusOut:
			FBPutSlotSymbol(fb, "type", "FocusOut");
			typedeventfb = CreateFactBuilder(theEnv, "x-focus-change-event");
			typedevent = XFocusChangeEventToFact(theEnv, context, &(e->xfocus), typedeventfb);
			FBDispose(typedeventfb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not assert x-focus-change-event fact");
				ReportFBAssertError(theEnv);
				return NULL;
			}
			FBPutSlotFact(fb, "typed-event", typedevent);
			break;
		case KeymapNotify:
			FBPutSlotSymbol(fb, "type", "KeymapNotify");
			typedeventfb = CreateFactBuilder(theEnv, "x-keymap-event");
			typedevent = XKeymapEventToFact(theEnv, context, e->xany.display, &e->xkeymap, typedeventfb);
			FBDispose(typedeventfb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not assert x-keymap-event fact");
				ReportFBAssertError(theEnv);
				return NULL;
			}
			FBPutSlotFact(fb, "typed-event", typedevent);
			break;
		case Expose:
			FBPutSlotSymbol(fb, "type", "Expose");
			typedeventfb = CreateFactBuilder(theEnv, "x-expose-event");
			typedevent = XExposeEventToFact(theEnv, context, &(e->xexpose), typedeventfb);
			FBDispose(typedeventfb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not assert x-expose-event fact");
				ReportFBAssertError(theEnv);
				return NULL;
			}
			FBPutSlotFact(fb, "typed-event", typedevent);
			break;
		case GraphicsExpose:
			FBPutSlotSymbol(fb, "type", "GraphicsExpose");
			typedeventfb = CreateFactBuilder(theEnv, "x-graphics-expose-event");
			typedevent = XGraphicsExposeEventToFact(theEnv, context, &(e->xgraphicsexpose), typedeventfb);
			FBDispose(typedeventfb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not assert x-graphics-expose-event fact");
				ReportFBAssertError(theEnv);
				return NULL;
			}
			FBPutSlotFact(fb, "typed-event", typedevent);
			break;
		case NoExpose:
			FBPutSlotSymbol(fb, "type", "NoExpose");
			typedeventfb = CreateFactBuilder(theEnv, "x-no-expose-event");
			typedevent = XNoExposeEventToFact(theEnv, context, &(e->xnoexpose), typedeventfb);
			FBDispose(typedeventfb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not assert x-no-expose-event fact");
				ReportFBAssertError(theEnv);
				return NULL;
			}
			FBPutSlotFact(fb, "typed-event", typedevent);
			break;
		case VisibilityNotify:
			FBPutSlotSymbol(fb, "type", "VisibilityNotify");
			typedeventfb = CreateFactBuilder(theEnv, "x-visibility-event");
			typedevent = XVisibilityEventToFact(theEnv, context, &(e->xvisibility), typedeventfb);
			FBDispose(typedeventfb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not assert x-visibility-event fact");
				ReportFBAssertError(theEnv);
				return NULL;
			}
			FBPutSlotFact(fb, "typed-event", typedevent);
			break;
		case CreateNotify:
			FBPutSlotSymbol(fb, "type", "CreateNotify");
			typedeventfb = CreateFactBuilder(theEnv, "x-create-window-event");
			typedevent = XCreateWindowEventToFact(theEnv, context, &(e->xcreatewindow), typedeventfb);
			FBDispose(typedeventfb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not assert x-create-window-event fact");
				ReportFBAssertError(theEnv);
				return NULL;
			}
			FBPutSlotFact(fb, "typed-event", typedevent);
			break;
		case DestroyNotify:
			FBPutSlotSymbol(fb, "type", "DestroyNotify");
			typedeventfb = CreateFactBuilder(theEnv, "x-destroy-window-event");
			typedevent = XDestroyWindowEventToFact(theEnv, context, &(e->xdestroywindow), typedeventfb);
			FBDispose(typedeventfb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not assert x-destroy-window-event fact");
				ReportFBAssertError(theEnv);
				return NULL;
			}
			FBPutSlotFact(fb, "typed-event", typedevent);
			break;
		case UnmapNotify:
			FBPutSlotSymbol(fb, "type", "UnmapNotify");
			typedeventfb = CreateFactBuilder(theEnv, "x-unmap-event");
			typedevent = XUnmapEventToFact(theEnv, context, &(e->xunmap), typedeventfb);
			FBDispose(typedeventfb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not assert x-unmap-event fact");
				ReportFBAssertError(theEnv);
				return NULL;
			}
			FBPutSlotFact(fb, "typed-event", typedevent);
			break;
		case MapNotify:
			FBPutSlotSymbol(fb, "type", "MapNotify");
			typedeventfb = CreateFactBuilder(theEnv, "x-map-event");
			typedevent = XMapEventToFact(theEnv, context, &(e->xmap), typedeventfb);
			FBDispose(typedeventfb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not assert x-map-event fact");
				ReportFBAssertError(theEnv);
				return NULL;
			}
			FBPutSlotFact(fb, "typed-event", typedevent);
			break;
		case MapRequest:
			FBPutSlotSymbol(fb, "type", "MapRequest");
			typedeventfb = CreateFactBuilder(theEnv, "x-map-request-event");
			typedevent = XMapRequestEventToFact(theEnv, context, &(e->xmaprequest), typedeventfb);
			FBDispose(typedeventfb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not assert x-map-request-event fact");
				ReportFBAssertError(theEnv);
				return NULL;
			}
			FBPutSlotFact(fb, "typed-event", typedevent);
			break;
		case ReparentNotify:
			FBPutSlotSymbol(fb, "type", "ReparentNotify");
			typedeventfb = CreateFactBuilder(theEnv, "x-reparent-event");
			typedevent = XReparentEventToFact(theEnv, context, &(e->xreparent), typedeventfb);
			FBDispose(typedeventfb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not assert x-reparent-event fact");
				ReportFBAssertError(theEnv);
				return NULL;
			}
			FBPutSlotFact(fb, "typed-event", typedevent);
			break;
		case ConfigureNotify:
			FBPutSlotSymbol(fb, "type", "ConfigureNotify");
			typedeventfb = CreateFactBuilder(theEnv, "x-configure-event");
			typedevent = XConfigureEventToFact(theEnv, context, &(e->xconfigure), typedeventfb);
			FBDispose(typedeventfb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not assert x-configure-event fact");
				ReportFBAssertError(theEnv);
				return NULL;
			}
			FBPutSlotFact(fb, "typed-event", typedevent);
			break;
		case ConfigureRequest:
			FBPutSlotSymbol(fb, "type", "ConfigureRequest");
			typedeventfb = CreateFactBuilder(theEnv, "x-configure-request-event");
			typedevent = XConfigureRequestEventToFact(theEnv, context, &(e->xconfigurerequest), typedeventfb);
			FBDispose(typedeventfb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not assert x-configure-request-event fact");
				ReportFBAssertError(theEnv);
				return NULL;
			}
			FBPutSlotFact(fb, "typed-event", typedevent);
			break;
		case GravityNotify:
			FBPutSlotSymbol(fb, "type", "GravityNotify");
			typedeventfb = CreateFactBuilder(theEnv, "x-gravity-event");
			typedevent = XGravityEventToFact(theEnv, context, &(e->xgravity), typedeventfb);
			FBDispose(typedeventfb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not assert x-gravity-event fact");
				ReportFBAssertError(theEnv);
				return NULL;
			}
			FBPutSlotFact(fb, "typed-event", typedevent);
			break;
		case ResizeRequest:
			FBPutSlotSymbol(fb, "type", "ResizeRequest");
			typedeventfb = CreateFactBuilder(theEnv, "x-resize-request-event");
			typedevent = XResizeRequestEventToFact(theEnv, context, &(e->xresizerequest), typedeventfb);
			FBDispose(typedeventfb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not assert x-gravity-event fact");
				ReportFBAssertError(theEnv);
				return NULL;
			}
			FBPutSlotFact(fb, "typed-event", typedevent);
			break;
		case CirculateNotify:
			FBPutSlotSymbol(fb, "type", "CirculateNotify");
			typedeventfb = CreateFactBuilder(theEnv, "x-circulate-event");
			typedevent = XCirculateEventToFact(theEnv, context, &(e->xcirculate), typedeventfb);
			FBDispose(typedeventfb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not assert x-circulate-event fact");
				ReportFBAssertError(theEnv);
				return NULL;
			}
			FBPutSlotFact(fb, "typed-event", typedevent);
			break;
		case CirculateRequest:
			FBPutSlotSymbol(fb, "type", "CirculateRequest");
			typedeventfb = CreateFactBuilder(theEnv, "x-circulate-request-event");
			typedevent = XCirculateRequestEventToFact(theEnv, context, &(e->xcirculaterequest), typedeventfb);
			FBDispose(typedeventfb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not assert x-circulate-request-event fact");
				ReportFBAssertError(theEnv);
				return NULL;
			}
			FBPutSlotFact(fb, "typed-event", typedevent);
			break;
		case PropertyNotify:
			FBPutSlotSymbol(fb, "type", "PropertyNotify");
			typedeventfb = CreateFactBuilder(theEnv, "x-property-event");
			typedevent = XPropertyEventToFact(theEnv, context, &(e->xproperty), typedeventfb);
			FBDispose(typedeventfb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not assert x-property-event fact");
				ReportFBAssertError(theEnv);
				return NULL;
			}
			FBPutSlotFact(fb, "typed-event", typedevent);
			break;
		case SelectionClear:
			FBPutSlotSymbol(fb, "type", "SelectionClear");
			typedeventfb = CreateFactBuilder(theEnv, "x-selection-clear-event");
			typedevent = XSelectionClearEventToFact(theEnv, context, &(e->xselectionclear), typedeventfb);
			FBDispose(typedeventfb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not assert x-selection-clear-event fact");
				ReportFBAssertError(theEnv);
				return NULL;
			}
			FBPutSlotFact(fb, "typed-event", typedevent);
			break;
		case SelectionRequest:
			FBPutSlotSymbol(fb, "type", "SelectionRequest");
			typedeventfb = CreateFactBuilder(theEnv, "x-selection-request-event");
			typedevent = XSelectionRequestEventToFact(theEnv, context, &(e->xselectionrequest), typedeventfb);
			FBDispose(typedeventfb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not assert x-selection-request-event fact");
				ReportFBAssertError(theEnv);
				return NULL;
			}
			FBPutSlotFact(fb, "typed-event", typedevent);
			break;
		case SelectionNotify:
			FBPutSlotSymbol(fb, "type", "SelectionNotify");
			typedeventfb = CreateFactBuilder(theEnv, "x-selection-event");
			typedevent = XSelectionEventToFact(theEnv, context, &(e->xselection), typedeventfb);
			FBDispose(typedeventfb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not assert x-selection-event fact");
				ReportFBAssertError(theEnv);
				return NULL;
			}
			FBPutSlotFact(fb, "typed-event", typedevent);
			break;
		case ColormapNotify:
			FBPutSlotSymbol(fb, "type", "ColormapNotify");
			typedeventfb = CreateFactBuilder(theEnv, "x-colormap-event");
			typedevent = XColormapEventToFact(theEnv, context, &(e->xcolormap), typedeventfb);
			FBDispose(typedeventfb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not assert x-colormap-event fact");
				ReportFBAssertError(theEnv);
				return NULL;
			}
			FBPutSlotFact(fb, "typed-event", typedevent);
			break;
		case ClientMessage:
			FBPutSlotSymbol(fb, "type", "ClientMessage");
			typedeventfb = CreateFactBuilder(theEnv, "x-client-message-event");
			typedevent = XClientMessageEventToFact(theEnv, context, &(e->xclient), typedeventfb);
			FBDispose(typedeventfb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not assert x-client-message-event fact");
				ReportFBAssertError(theEnv);
				return NULL;
			}
			FBPutSlotFact(fb, "typed-event", typedevent);
			break;
		case MappingNotify:
			FBPutSlotSymbol(fb, "type", "MappingNotify");
			typedeventfb = CreateFactBuilder(theEnv, "x-mapping-event");
			typedevent = XMappingEventToFact(theEnv, context, &(e->xmapping), typedeventfb);
			FBDispose(typedeventfb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not assert x-mapping-event fact");
				ReportFBAssertError(theEnv);
				return NULL;
			}
			FBPutSlotFact(fb, "typed-event", typedevent);
			break;
		case GenericEvent:
			FBPutSlotSymbol(fb, "type", "GenericEvent");
			typedeventfb = CreateFactBuilder(theEnv, "x-generic-event");
			typedevent = XGenericEventToFact(theEnv, context, &(e->xgeneric), typedeventfb);
			FBDispose(typedeventfb);
			if (typedevent == NULL)
			{
				WriteString(theEnv,STDERR,"Could not assert x-generic-event fact\n");
				ReportFBAssertError(theEnv);
				return NULL;
			}
			FBPutSlotFact(fb, "typed-event", typedevent);
			break;
		default:
			WriteString(theEnv,STDERR,"Event Type ");
			WriteInteger(theEnv,STDERR,e->type);
			WriteString(theEnv,STDERR," not supported.\n");
			return NULL;
	}
	return FBAssert(fb);
}

/*
Instance *XEventToInstance(
		Environment *theEnv,
		UDFContext *context,
		XEvent *e,
		InstanceBuilder *ib,
		const char *name,
		const char *typeName)
{
	return IBMake(ib);
}
*/

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

	fb = CreateFactBuilder(theEnv, "x-event");

	returnValue->factValue = XEventToFact(theEnv, context, &event, fb);

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

	fb = CreateFactBuilder(theEnv, "x-event");

	returnValue->factValue = XEventToFact(theEnv, context, &event, fb);
	if (returnValue->factValue == NULL)
	{
		WriteString(theEnv,STDERR,"Could not assert x-event fact\n");
		ReportFBAssertError(theEnv);
	}

	FBDispose(fb);
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
		if (0 == strcmp(theArg.lexemeValue->contents, "KeyPressMask"))
		{
			event_mask |= KeyPressMask;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "KeyReleaseMask"))
		{
			event_mask |= KeyReleaseMask;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "ButtonPressMask"))
		{
			event_mask |= ButtonPressMask;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "ButtonReleaseMask"))
		{
			event_mask |= ButtonReleaseMask;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "EnterWindowMask"))
		{
			event_mask |= EnterWindowMask;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "LeaveWindowMask"))
		{
			event_mask |= LeaveWindowMask;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "PointerMotionMask"))
		{
			event_mask |= PointerMotionMask;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "PointerMotionHintMask"))
		{
			event_mask |= PointerMotionHintMask;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "Button1MotionMask"))
		{
			event_mask |= Button1MotionMask;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "Button2MotionMask"))
		{
			event_mask |= Button2MotionMask;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "Button3MotionMask"))
		{
			event_mask |= Button3MotionMask;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "Button4MotionMask"))
		{
			event_mask |= Button4MotionMask;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "Button5MotionMask"))
		{
			event_mask |= Button5MotionMask;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "ButtonMotionMask"))
		{
			event_mask |= ButtonMotionMask;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "KeymapStateMask"))
		{
			event_mask |= KeymapStateMask;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "ExposureMask"))
		{
			event_mask |= ExposureMask;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "VisibilityChangeMask"))
		{
			event_mask |= VisibilityChangeMask;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "StructureNotifyMask"))
		{
			event_mask |= StructureNotifyMask;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "ResizeRedirectMask"))
		{
			event_mask |= ResizeRedirectMask;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "SubstructureNotifyMask"))
		{
			event_mask |= SubstructureNotifyMask;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "SubstructureRedirectMask"))
		{
			event_mask |= SubstructureRedirectMask;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "FocusChangeMask"))
		{
			event_mask |= FocusChangeMask;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "PropertyChangeMask"))
		{
			event_mask |= PropertyChangeMask;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "ColormapChangeMask"))
		{
			event_mask |= ColormapChangeMask;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "OwnerGrabButtonMask"))
		{
			event_mask |= OwnerGrabButtonMask;
		}
		else if (0 == strcmp(theArg.lexemeValue->contents, "NoEventMask"))
		{
			event_mask |= NoEventMask;
		}
		else
		{
			WriteString(theEnv,STDERR,"Event mask '");
			WriteString(theEnv,STDERR,theArg.lexemeValue->contents);
			WriteString(theEnv,STDERR,"' not supported.\n");
			returnValue->lexemeValue = FalseSymbol(theEnv);
			return;
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

	returnValue->integerValue = CreateInteger(theEnv, XSetInputFocus(display, focus, revert_to, time));
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
		printf("Key pressed: %s\n", buffer);
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

	UDFNextArgument(context,MULTIFIELD_BIT|SYMBOL_BIT,&theArg);
	modifiers = 0;
	if (theArg.header->type == SYMBOL_TYPE)
	{
		const char *mod = theArg.lexemeValue->contents;

		if (strcmp(mod, "ShiftMask") == 0) {
			modifiers |= ShiftMask;
		} else if (strcmp(mod, "LockMask") == 0) {
			modifiers |= LockMask;
		} else if (strcmp(mod, "ControlMask") == 0) {
			modifiers |= ControlMask;
		} else if (strcmp(mod, "Mod1Mask") == 0) {
			modifiers |= Mod1Mask;
		} else if (strcmp(mod, "Mod2Mask") == 0) {
			modifiers |= Mod2Mask;
		} else if (strcmp(mod, "Mod3Mask") == 0) {
			modifiers |= Mod3Mask;
		} else if (strcmp(mod, "Mod4Mask") == 0) {
			modifiers |= Mod4Mask;
		} else if (strcmp(mod, "Mod5Mask") == 0) {
			modifiers |= Mod5Mask;
		} else if (strcmp(mod, "AnyModifier") == 0) {
			modifiers = AnyModifier;
		}
	}
	else
	{
		for (int i = 0; i < theArg.multifieldValue->length; i++)
		{
			const char *mod = theArg.multifieldValue->contents[i].lexemeValue->contents;

			if (strcmp(mod, "Shift") == 0) {
				modifiers |= ShiftMask;
			} else if (strcmp(mod, "LockMask") == 0) {
				modifiers |= LockMask;
			} else if (strcmp(mod, "ControlMask") == 0) {
				modifiers |= ControlMask;
			} else if (strcmp(mod, "Mod1Mask") == 0) {
				modifiers |= Mod1Mask;
			} else if (strcmp(mod, "Mod2Mask") == 0) {
				modifiers |= Mod2Mask;
			} else if (strcmp(mod, "Mod3Mask") == 0) {
				modifiers |= Mod3Mask;
			} else if (strcmp(mod, "Mod4Mask") == 0) {
				modifiers |= Mod4Mask;
			} else if (strcmp(mod, "Mod5Mask") == 0) {
				modifiers |= Mod5Mask;
			} else if (strcmp(mod, "AnyModifier") == 0) {
				modifiers = AnyModifier;
				break;
			}
		}
	}

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
	  AddUDF(env,"default-screen","l",1,1,";e",DefaultScreenFunction,"DefaultScreenFunction",NULL);
	  AddUDF(env,"default-screen-of-display","e",1,1,";e",DefaultScreenOfDisplayFunction,"DefaultScreenOfDisplayFunction",NULL);
	  AddUDF(env,"default-root-window","l",1,1,";e",DefaultRootWindowFunction,"DefaultRootWindowFunction",NULL);
	  AddUDF(env,"root-window","l",2,2,";e;l",RootWindowFunction,"RootWindowFunction",NULL);
	  AddUDF(env,"x-create-simple-window","bl",9,9,";e;l;l;l;l;l;l;l;l",XCreateSimpleWindowFunction,"XCreateSimpleWindowFunction",NULL);
	  AddUDF(env,"x-create-window","bl",12,12,";e;l;l;l;l;l;l;l;l;e;l;e",XCreateWindowFunction,"XCreateWindowFunction",NULL);
	  AddUDF(env,"x-create-font-cursor","bl",2,2,";e;y",XCreateFontCursorFunction,"XCreateFontCursorFunction",NULL);
	  AddUDF(env,"x-define-cursor","v",3,3,";e;l;l",XDefineCursorFunction,"XDefineCursorFunction",NULL);
	  AddUDF(env,"x-map-window","v",2,2,";e;l",XMapWindowFunction,"XMapWindowFunction",NULL);
	  AddUDF(env,"x-move-resize-window","l",6,6,";e;l;l;l;l;l",XMoveResizeWindowFunction,"XMoveResizeWindowFunction",NULL);
	  AddUDF(env,"x-circulate-subwindows-up","l",2,2,";e;l",XCirculateSubwindowsUpFunction,"XCirculateSubwindowsUpFunction",NULL);
	  AddUDF(env,"x-kill-client","l",2,2,";e;l",XKillClientFunction,"XKillClientFunction",NULL);
	  AddUDF(env,"screen-to-fact","f",1,1,";e",ScreenToFactFunction,"ScreenToFactFunction",NULL);
	  AddUDF(env,"screen-to-multifield","m",1,1,";e",ScreenToMultifieldFunction,"ScreenToMultifieldFunction",NULL);
	  AddUDF(env,"remove-hints-flags-from-window","v",3,12,";e;l;y;y;y;y;y;y;y;y;y;y",RemoveHintsFlagsFromWindowFunction,"RemoveHintsFlagsFromWindowFunction",NULL);
	  AddUDF(env,"set-window-gravity","v",3,3,";e;l;y",SetWindowGravityFunction,"SetWindowGravityFunction",NULL);
	  AddUDF(env,"x-list-properties","m",2,2,";e;l",XListPropertiesFunction,"XListPropertiesFunction",NULL);
	  AddUDF(env,"x-get-property","ms",3,3,";e;l;sy",XGetPropertyFunction,"XGetPropertyFunction",NULL);

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
	  AddUDF(env,"x-next-event","bm",1,1,";e",XNextEventFunction,"XNextEventFunction",NULL);
	  AddUDF(env,"x-next-event-to-fact","bf",1,1,";e",XNextEventToFactFunction,"XNextEventToFactFunction",NULL);

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

	  AddUDF(env,"x-grab-key","l",7,7,";e;l;ym;l;b;y;y",XGrabKeyFunction,"XGrabKeyFunction",NULL);

	  AddUDF(env,"x-flush","l",1,1,";e",XFlushFunction,"XFlushFunction",NULL);
	  AddUDF(env,"x-sync","l",1,2,";e;b",XSyncFunction,"XSyncFunction",NULL);
  }
