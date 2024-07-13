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
	if (0 == strcmp(theArg.lexemeValue->contents, "XC_left_ptr"))
	{
		shape = XC_left_ptr;
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

void XPeekEventFunction(
		Environment *theEnv,
		UDFContext *context,
		UDFValue *returnValue)
{
	Display *display;
	XComposeStatus compose;
	XEvent event;
	MultifieldBuilder *mb;
	char buffer[32];
	KeySym keysym;
	FactBuilder *fb;
	Fact *f;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	XPeekEvent(display, &event);

	mb = CreateMultifieldBuilder(theEnv, 0);
	fb = CreateFactBuilder(theEnv, "x-event");
	FBPutSlotInteger(fb, "serial", event.xany.serial);
	if (event.xany.send_event)
	{
		FBPutSlotSymbol(fb, "send-event", "TRUE");
	}
	else
	{
		FBPutSlotSymbol(fb, "send-event", "FALSE");
	}
	FBPutSlotExternalAddress(fb, "display", CreateCExternalAddress(theEnv, event.xany.display));
	FBPutSlotInteger(fb, "window", event.xany.window);
	switch (event.type)
	{
		case KeyPress:
			FBPutSlotSymbol(fb, "type", "KeyPress");
			f = FBAssert(fb);
			FBDispose(fb);
			fb = CreateFactBuilder(theEnv, "x-key-event");
			FBPutSlotInteger(fb, "root", event.xkey.root);
			FBPutSlotInteger(fb, "subwindow", event.xkey.subwindow);
			FBPutSlotInteger(fb, "time", event.xkey.time);
			FBPutSlotInteger(fb, "x", event.xkey.x);
			FBPutSlotInteger(fb, "y", event.xkey.y);
			FBPutSlotInteger(fb, "x-root", event.xkey.x_root);
			FBPutSlotInteger(fb, "y-root", event.xkey.y_root);
			if (event.xkey.state & Button1Mask) {
				MBAppendSymbol(mb, "Button1");
			}
			if (event.xkey.state & Button2Mask) {
				MBAppendSymbol(mb, "Button2");
			}
			if (event.xkey.state & Button3Mask) {
				MBAppendSymbol(mb, "Button3");
			}
			if (event.xkey.state & Button4Mask) {
				MBAppendSymbol(mb, "Button4");
			}
			if (event.xkey.state & Button5Mask) {
				MBAppendSymbol(mb, "Button5");
			}
			if (event.xkey.state & ShiftMask) {
				MBAppendSymbol(mb, "Shift");
			}
			if (event.xkey.state & LockMask) {
				MBAppendSymbol(mb, "Lock");
			}
			if (event.xkey.state & ControlMask) {
				MBAppendSymbol(mb, "Control");
			}
			if (event.xkey.state & Mod1Mask) {
				MBAppendSymbol(mb, "Mod1");
			}
			if (event.xkey.state & Mod2Mask) {
				MBAppendSymbol(mb, "Mod2");
			}
			if (event.xkey.state & Mod3Mask) {
				MBAppendSymbol(mb, "Mod3");
			}
			if (event.xkey.state & Mod4Mask) {
				MBAppendSymbol(mb, "Mod4");
			}
			if (event.xkey.state & Mod5Mask) {
				MBAppendSymbol(mb, "Mod5");
			}
			FBPutSlotMultifield(fb, "state", MBCreate(mb));
			MBDispose(mb);
			FBPutSlotInteger(fb, "keycode", event.xkey.keycode);
			if (event.xkey.same_screen)
			{
				FBPutSlotSymbol(fb, "same-screen", "TRUE");
			}
			else
			{
				FBPutSlotSymbol(fb, "same-screen", "FALSE");
			}
			XLookupString(&event.xkey, buffer, sizeof(buffer), &keysym, &compose);
			FBPutSlotString(fb, "buffer", buffer);
			FBPutSlotInteger(fb, "keysym", keysym);
			FBPutSlotExternalAddress(fb, "compose-ptr", CreateCExternalAddress(theEnv, compose.compose_ptr));
			FBPutSlotInteger(fb, "chars-matched", compose.chars_matched);
			break;
		case KeyRelease:
			FBPutSlotSymbol(fb, "type", "KeyPress");
			f = FBAssert(fb);
			FBDispose(fb);
			fb = CreateFactBuilder(theEnv, "x-key-event");
			FBPutSlotInteger(fb, "root", event.xkey.root);
			FBPutSlotInteger(fb, "subwindow", event.xkey.subwindow);
			FBPutSlotInteger(fb, "time", event.xkey.time);
			FBPutSlotInteger(fb, "x", event.xkey.x);
			FBPutSlotInteger(fb, "y", event.xkey.y);
			FBPutSlotInteger(fb, "x-root", event.xkey.x_root);
			FBPutSlotInteger(fb, "y-root", event.xkey.y_root);
			if (event.xkey.state & Button1Mask) {
				MBAppendSymbol(mb, "Button1");
			}
			if (event.xkey.state & Button2Mask) {
				MBAppendSymbol(mb, "Button2");
			}
			if (event.xkey.state & Button3Mask) {
				MBAppendSymbol(mb, "Button3");
			}
			if (event.xkey.state & Button4Mask) {
				MBAppendSymbol(mb, "Button4");
			}
			if (event.xkey.state & Button5Mask) {
				MBAppendSymbol(mb, "Button5");
			}
			if (event.xkey.state & ShiftMask) {
				MBAppendSymbol(mb, "Shift");
			}
			if (event.xkey.state & LockMask) {
				MBAppendSymbol(mb, "Lock");
			}
			if (event.xkey.state & ControlMask) {
				MBAppendSymbol(mb, "Control");
			}
			if (event.xkey.state & Mod1Mask) {
				MBAppendSymbol(mb, "Mod1");
			}
			if (event.xkey.state & Mod2Mask) {
				MBAppendSymbol(mb, "Mod2");
			}
			if (event.xkey.state & Mod3Mask) {
				MBAppendSymbol(mb, "Mod3");
			}
			if (event.xkey.state & Mod4Mask) {
				MBAppendSymbol(mb, "Mod4");
			}
			if (event.xkey.state & Mod5Mask) {
				MBAppendSymbol(mb, "Mod5");
			}
			FBPutSlotMultifield(fb, "state", MBCreate(mb));
			MBDispose(mb);

			FBPutSlotInteger(fb, "keycode", event.xkey.keycode);
			if (event.xkey.same_screen)
			{
				FBPutSlotSymbol(fb, "same-screen", "TRUE");
			}
			else
			{
				FBPutSlotSymbol(fb, "same-screen", "FALSE");
			}
			XLookupString(&event.xkey, buffer, sizeof(buffer), &keysym, &compose);
			FBPutSlotString(fb, "buffer", buffer);
			FBPutSlotInteger(fb, "keysym", keysym);
			FBPutSlotExternalAddress(fb, "compose-ptr", CreateCExternalAddress(theEnv, compose.compose_ptr));
			FBPutSlotInteger(fb, "chars-matched", compose.chars_matched);
			break;
		case ButtonPress:
			FBPutSlotSymbol(mb, "type", "ButtonPress");
			f = FBAssert(fb);
			FBDispose(fb);
			fb = CreateFactBuilder(theEnv, "x-button-event");
			FBPutSlotInteger(fb, "root", event.xbutton.root);
			FBPutSlotInteger(fb, "subwindow", event.xbutton.subwindow);
			FBPutSlotInteger(fb, "time", event.xbutton.time);
			FBPutSlotInteger(fb, "x", event.xbutton.x);
			FBPutSlotInteger(fb, "y", event.xbutton.y);
			FBPutSlotInteger(fb, "x-root", event.xbutton.x_root);
			FBPutSlotInteger(fb, "y-root", event.xbutton.y_root);
			MBAppendInteger(mb, event.xbutton.state);
			if (event.xbutton.state & Button1Mask) {
				MBAppendSymbol(mb, "Button1");
			}
			if (event.xbutton.state & Button2Mask) {
				MBAppendSymbol(mb, "Button2");
			}
			if (event.xbutton.state & Button3Mask) {
				MBAppendSymbol(mb, "Button3");
			}
			if (event.xbutton.state & Button4Mask) {
				MBAppendSymbol(mb, "Button4");
			}
			if (event.xbutton.state & Button5Mask) {
				MBAppendSymbol(mb, "Button5");
			}
			if (event.xbutton.state & ShiftMask) {
				MBAppendSymbol(mb, "Shift");
			}
			if (event.xbutton.state & LockMask) {
				MBAppendSymbol(mb, "Lock");
			}
			if (event.xbutton.state & ControlMask) {
				MBAppendSymbol(mb, "Control");
			}
			if (event.xbutton.state & Mod1Mask) {
				MBAppendSymbol(mb, "Mod1");
			}
			if (event.xbutton.state & Mod2Mask) {
				MBAppendSymbol(mb, "Mod2");
			}
			if (event.xbutton.state & Mod3Mask) {
				MBAppendSymbol(mb, "Mod3");
			}
			if (event.xbutton.state & Mod4Mask) {
				MBAppendSymbol(mb, "Mod4");
			}
			if (event.xbutton.state & Mod5Mask) {
				MBAppendSymbol(mb, "Mod5");
			}
			FBPutSlotMultifield(fb, "state", MBCreate(mb));
			MBDispose(mb);
			FBPutSlotInteger(fb, "button", event.xbutton.button);
			if (event.xbutton.same_screen)
			{
				FBAppendSymbol(mb, "same-screen", "TRUE");
			}
			else
			{
				FBAppendSymbol(mb, "same-screen", "FALSE");
			}
			break;
		case ButtonRelease:
			FBPutSlotSymbol(mb, "type", "ButtonRelease");
			f = FBAssert(fb);
			FBDispose(fb);
			fb = CreateFactBuilder(theEnv, "x-button-event");
			FBPutSlotInteger(fb, "root", event.xbutton.root);
			FBPutSlotInteger(fb, "subwindow", event.xbutton.subwindow);
			FBPutSlotInteger(fb, "time", event.xbutton.time);
			FBPutSlotInteger(fb, "x", event.xbutton.x);
			FBPutSlotInteger(fb, "y", event.xbutton.y);
			FBPutSlotInteger(fb, "x-root", event.xbutton.x_root);
			FBPutSlotInteger(fb, "y-root", event.xbutton.y_root);
			MBAppendInteger(mb, event.xbutton.state);
			if (event.xbutton.state & Button1Mask) {
				MBAppendSymbol(mb, "Button1");
			}
			if (event.xbutton.state & Button2Mask) {
				MBAppendSymbol(mb, "Button2");
			}
			if (event.xbutton.state & Button3Mask) {
				MBAppendSymbol(mb, "Button3");
			}
			if (event.xbutton.state & Button4Mask) {
				MBAppendSymbol(mb, "Button4");
			}
			if (event.xbutton.state & Button5Mask) {
				MBAppendSymbol(mb, "Button5");
			}
			if (event.xbutton.state & ShiftMask) {
				MBAppendSymbol(mb, "Shift");
			}
			if (event.xbutton.state & LockMask) {
				MBAppendSymbol(mb, "Lock");
			}
			if (event.xbutton.state & ControlMask) {
				MBAppendSymbol(mb, "Control");
			}
			if (event.xbutton.state & Mod1Mask) {
				MBAppendSymbol(mb, "Mod1");
			}
			if (event.xbutton.state & Mod2Mask) {
				MBAppendSymbol(mb, "Mod2");
			}
			if (event.xbutton.state & Mod3Mask) {
				MBAppendSymbol(mb, "Mod3");
			}
			if (event.xbutton.state & Mod4Mask) {
				MBAppendSymbol(mb, "Mod4");
			}
			if (event.xbutton.state & Mod5Mask) {
				MBAppendSymbol(mb, "Mod5");
			}
			FBPutSlotMultifield(fb, "state", MBCreate(mb));
			MBDispose(mb);
			FBPutSlotInteger(fb, "button", event.xbutton.button);
			if (event.xbutton.same_screen)
			{
				FBAppendSymbol(mb, "same-screen", "TRUE");
			}
			else
			{
				FBAppendSymbol(mb, "same-screen", "FALSE");
			}
			break;
		case MotionNotify:
			FBPutSlotSymbol(fb, "type", "MotionNotify");
			f = FBAssert(fb);
			FBDispose(fb);
			fb = CreateFactBuilder(theEnv, "x-motion-event");
			FBPutSlotInteger(fb, "root", event.xmotion.root);
			FBPutSlotInteger(fb, "subwindow", event.xmotion.subwindow);
			FBPutSlotInteger(fb, "time", event.xmotion.time);
			FBPutSlotInteger(fb, "x", event.xmotion.x);
			FBPutSlotInteger(fb, "y", event.xmotion.y);
			FBPutSlotInteger(fb, "x-root", event.xmotion.x_root);
			FBPutSlotInteger(fb, "y-root", event.xmotion.y_root);
			switch(event.xmotion.is_hint)
			{
				case NotifyNormal:
					FBPutSlotSymbol(fb, "is-hint", "NotifyNormal");
					break;
				case NotifyHint:
					FBPutSlotSymbol(fb, "is-hint", "NotifyHint");
					break;
				default:
					WriteString(theEnv,STDERR,"Notify hint type ");
					WriteInteger(theEnv,STDERR,event.xmotion.is_hint);
					WriteString(theEnv,STDERR," not supported.\n");
					returnValue->lexemeValue = FalseSymbol(theEnv);
					return;
			}
			if (event.xmotion.same_screen)
			{
				FBPutSlotSymbol(fb, "same-screen", "TRUE");
			}
			else
			{
				FBPutSlotSymbol(fb, "same-screen", "FALSE");
			}
			break;
		case EnterNotify:
			FBPutSlotSymbol(fb, "type", "EnterNotify");
			f = FBAssert(fb);
			FBDispose(fb);
			fb = CreateFactBuilder(theEnv, "x-crossing-event");
			FBPutSlotInteger(fb, "root", event.xcrossing.root);
			FBPutSlotInteger(fb, "subwindow", event.xcrossing.subwindow);
			FBPutSlotInteger(fb, "time", event.xcrossing.time);
			FBPutSlotInteger(fb, "x", event.xcrossing.x);
			FBPutSlotInteger(fb, "y", event.xcrossing.y);
			FBPutSlotInteger(fb, "x-root", event.xcrossing.x_root);
			FBPutSlotInteger(fb, "y-root", event.xcrossing.y_root);
			switch(event.xcrossing.mode)
			{
				case NotifyNormal:
					FBPutSlotSymbol(fb, "mode", "NotifyNormal");
					break;
				case NotifyGrab:
					FBPutSlotSymbol(fb, "mode", "NotifyGrab");
					break;
				case NotifyUngrab:
					FBPutSlotSymbol(fb, "mode", "NotifyUngrab");
					break;
				default:
					WriteString(theEnv,STDERR,"EnterNotify mode ");
					WriteInteger(theEnv,STDERR,event.xcrossing.mode);
					WriteString(theEnv,STDERR," not supported.\n");
					returnValue->lexemeValue = FalseSymbol(theEnv);
					return;
			}
			switch(event.xcrossing.detail)
			{
				case NotifyAncestor:
					FBPutSlotSymbol(fb, "detail", "NotifyAncestor");
					break;
				case NotifyVirtual:
					FBPutSlotSymbol(fb, "detail", "NotifyVirtual");
					break;
				case NotifyInferior:
					FBPutSlotSymbol(fb, "detail", "NotifyInferior");
					break;
				case NotifyNonlinear:
					FBPutSlotSymbol(fb, "detail", "NotifyNonlinear");
					break;
				case NotifyNonlinearVirtual:
					FBPutSlotSymbol(fb, "detail", "NotifyNonlinearVirtual");
					break;
				default:
					WriteString(theEnv,STDERR,"EnterNotify detail ");
					WriteInteger(theEnv,STDERR,event.xcrossing.detail);
					WriteString(theEnv,STDERR," not supported.\n");
					returnValue->lexemeValue = FalseSymbol(theEnv);
					return;
			}
			if (event.xcrossing.same_screen)
			{
				FBPutSlotSymbol(fb, "same-screen", "TRUE");
			}
			else
			{
				FBPutSlotSymbol(fb, "same-screen", "FALSE");
			}
			if (event.xcrossing.focus)
			{
				FBPutSlotSymbol(fb, "focus", "TRUE");
			}
			else
			{
				FBPutSlotSymbol(fb, "focus", "FALSE");
			}
			if (event.xcrossing.state & Button1Mask) {
				MBAppendSymbol(mb, "Button1");
			}
			if (event.xcrossing.state & Button2Mask) {
				MBAppendSymbol(mb, "Button2");
			}
			if (event.xcrossing.state & Button3Mask) {
				MBAppendSymbol(mb, "Button3");
			}
			if (event.xcrossing.state & Button4Mask) {
				MBAppendSymbol(mb, "Button4");
			}
			if (event.xcrossing.state & Button5Mask) {
				MBAppendSymbol(mb, "Button5");
			}
			if (event.xcrossing.state & ShiftMask) {
				MBAppendSymbol(mb, "Shift");
			}
			if (event.xcrossing.state & LockMask) {
				MBAppendSymbol(mb, "Lock");
			}
			if (event.xcrossing.state & ControlMask) {
				MBAppendSymbol(mb, "Control");
			}
			if (event.xcrossing.state & Mod1Mask) {
				MBAppendSymbol(mb, "Mod1");
			}
			if (event.xcrossing.state & Mod2Mask) {
				MBAppendSymbol(mb, "Mod2");
			}
			if (event.xcrossing.state & Mod3Mask) {
				MBAppendSymbol(mb, "Mod3");
			}
			if (event.xcrossing.state & Mod4Mask) {
				MBAppendSymbol(mb, "Mod4");
			}
			if (event.xcrossing.state & Mod5Mask) {
				MBAppendSymbol(mb, "Mod5");
			}
			FBPutSlotMultifield(fb, "state", MBCreate(mb));
			MBDispose(mb);
			break;
		case LeaveNotify:
			FBPutSlotSymbol(fb, "type", "LeaveNotify");
			f = FBAssert(fb);
			FBDispose(fb);
			fb = CreateFactBuilder(theEnv, "x-crossing-event");
			FBPutSlotInteger(fb, "root", event.xcrossing.root);
			FBPutSlotInteger(fb, "subwindow", event.xcrossing.subwindow);
			FBPutSlotInteger(fb, "time", event.xcrossing.time);
			FBPutSlotInteger(fb, "x", event.xcrossing.x);
			FBPutSlotInteger(fb, "y", event.xcrossing.y);
			FBPutSlotInteger(fb, "x-root", event.xcrossing.x_root);
			FBPutSlotInteger(fb, "y-root", event.xcrossing.y_root);
			switch(event.xcrossing.mode)
			{
				case NotifyNormal:
					FBPutSlotSymbol(fb, "mode", "NotifyNormal");
					break;
				case NotifyGrab:
					FBPutSlotSymbol(fb, "mode", "NotifyGrab");
					break;
				case NotifyUngrab:
					FBPutSlotSymbol(fb, "mode", "NotifyUngrab");
					break;
				default:
					WriteString(theEnv,STDERR,"LeaveNotify mode ");
					WriteInteger(theEnv,STDERR,event.xcrossing.mode);
					WriteString(theEnv,STDERR," not supported.\n");
					returnValue->lexemeValue = FalseSymbol(theEnv);
					return;
			}
			switch(event.xcrossing.detail)
			{
				case NotifyAncestor:
					FBPutSlotSymbol(fb, "detail", "NotifyAncestor");
					break;
				case NotifyVirtual:
					FBPutSlotSymbol(fb, "detail", "NotifyVirtual");
					break;
				case NotifyInferior:
					FBPutSlotSymbol(fb, "detail", "NotifyInferior");
					break;
				case NotifyNonlinear:
					FBPutSlotSymbol(fb, "detail", "NotifyNonlinear");
					break;
				case NotifyNonlinearVirtual:
					FBPutSlotSymbol(fb, "detail", "NotifyNonlinearVirtual");
					break;
				default:
					WriteString(theEnv,STDERR,"LeaveNotify detail ");
					WriteInteger(theEnv,STDERR,event.xcrossing.detail);
					WriteString(theEnv,STDERR," not supported.\n");
					returnValue->lexemeValue = FalseSymbol(theEnv);
					return;
			}
			if (event.xcrossing.same_screen)
			{
				FBPutSlotSymbol(fb, "same-screen", "TRUE");
			}
			else
			{
				FBPutSlotSymbol(fb, "same-screen", "FALSE");
			}
			if (event.xcrossing.focus)
			{
				FBPutSlotSymbol(fb, "focus", "TRUE");
			}
			else
			{
				FBPutSlotSymbol(fb, "focus", "FALSE");
			}
			if (event.xcrossing.state & Button1Mask) {
				MBAppendSymbol(mb, "Button1");
			}
			if (event.xcrossing.state & Button2Mask) {
				MBAppendSymbol(mb, "Button2");
			}
			if (event.xcrossing.state & Button3Mask) {
				MBAppendSymbol(mb, "Button3");
			}
			if (event.xcrossing.state & Button4Mask) {
				MBAppendSymbol(mb, "Button4");
			}
			if (event.xcrossing.state & Button5Mask) {
				MBAppendSymbol(mb, "Button5");
			}
			if (event.xcrossing.state & ShiftMask) {
				MBAppendSymbol(mb, "Shift");
			}
			if (event.xcrossing.state & LockMask) {
				MBAppendSymbol(mb, "Lock");
			}
			if (event.xcrossing.state & ControlMask) {
				MBAppendSymbol(mb, "Control");
			}
			if (event.xcrossing.state & Mod1Mask) {
				MBAppendSymbol(mb, "Mod1");
			}
			if (event.xcrossing.state & Mod2Mask) {
				MBAppendSymbol(mb, "Mod2");
			}
			if (event.xcrossing.state & Mod3Mask) {
				MBAppendSymbol(mb, "Mod3");
			}
			if (event.xcrossing.state & Mod4Mask) {
				MBAppendSymbol(mb, "Mod4");
			}
			if (event.xcrossing.state & Mod5Mask) {
				MBAppendSymbol(mb, "Mod5");
			}
			FBPutSlotMultifield(fb, "state", MBCreate(mb));
			MBDispose(mb);
			break;
		case FocusIn:
			FBPutSlotSymbol(fb, "type", "FocusIn");
			f = FBAssert(fb);
			FBDispose(fb);
			fb = CreateFactBuilder(theEnv, "x-focus-event");
			FBPutSlotInteger(fb, "root", event.xcrossing.root);
			FBPutSlotInteger(fb, "subwindow", event.xcrossing.subwindow);
			FBPutSlotInteger(fb, "time", event.xcrossing.time);
			FBPutSlotInteger(fb, "x", event.xcrossing.x);
			FBPutSlotInteger(fb, "y", event.xcrossing.y);
			FBPutSlotInteger(fb, "x-root", event.xcrossing.x_root);
			FBPutSlotInteger(fb, "y-root", event.xcrossing.y_root);
			switch(event.xcrossing.mode)
			{
				case NotifyNormal:
					FBPutSlotSymbol(fb, "mode", "NotifyNormal");
					break;
				case NotifyGrab:
					FBPutSlotSymbol(fb, "mode", "NotifyGrab");
					break;
				case NotifyUngrab:
					FBPutSlotSymbol(fb, "mode", "NotifyUngrab");
					break;
				default:
					WriteString(theEnv,STDERR,"FocusIn mode ");
					WriteInteger(theEnv,STDERR,event.xcrossing.mode);
					WriteString(theEnv,STDERR," not supported.\n");
					returnValue->lexemeValue = FalseSymbol(theEnv);
					return;
			}
			switch(event.xcrossing.detail)
			{
				case NotifyAncestor:
					FBPutSlotSymbol(fb, "detail", "NotifyAncestor");
					break;
				case NotifyVirtual:
					FBPutSlotSymbol(fb, "detail", "NotifyVirtual");
					break;
				case NotifyInferior:
					FBPutSlotSymbol(fb, "detail", "NotifyInferior");
					break;
				case NotifyNonlinear:
					FBPutSlotSymbol(fb, "detail", "NotifyNonlinear");
					break;
				case NotifyNonlinearVirtual:
					FBPutSlotSymbol(fb, "detail", "NotifyNonlinearVirtual");
					break;
				case NotifyPointer:
					FBPutSlotSymbol(fb, "detail", "NotifyPointer");
					break;
				case NotifyPointerRoot:
					FBPutSlotSymbol(fb, "detail", "NotifyPointerRoot");
					break;
				case NotifyDetailNone:
					FBPutSlotSymbol(fb, "detail", "NotifyDetailNone");
					break;
				default:
					WriteString(theEnv,STDERR,"FocusIn detail ");
					WriteInteger(theEnv,STDERR,event.xcrossing.detail);
					WriteString(theEnv,STDERR," not supported.\n");
					returnValue->lexemeValue = FalseSymbol(theEnv);
					return;
			}
			break;
		case FocusOut:
			FBPutSlotSymbol(fb, "type", "FocusOut");
			f = FBAssert(fb);
			FBDispose(fb);
			fb = CreateFactBuilder(theEnv, "x-focus-event");
			FBPutSlotInteger(fb, "root", event.xcrossing.root);
			FBPutSlotInteger(fb, "subwindow", event.xcrossing.subwindow);
			FBPutSlotInteger(fb, "time", event.xcrossing.time);
			FBPutSlotInteger(fb, "x", event.xcrossing.x);
			FBPutSlotInteger(fb, "y", event.xcrossing.y);
			FBPutSlotInteger(fb, "x-root", event.xcrossing.x_root);
			FBPutSlotInteger(fb, "y-root", event.xcrossing.y_root);
			switch(event.xcrossing.mode)
			{
				case NotifyNormal:
					FBPutSlotSymbol(fb, "mode", "NotifyNormal");
					break;
				case NotifyGrab:
					FBPutSlotSymbol(fb, "mode", "NotifyGrab");
					break;
				case NotifyUngrab:
					FBPutSlotSymbol(fb, "mode", "NotifyUngrab");
					break;
				default:
					WriteString(theEnv,STDERR,"FocusOut mode ");
					WriteInteger(theEnv,STDERR,event.xcrossing.mode);
					WriteString(theEnv,STDERR," not supported.\n");
					returnValue->lexemeValue = FalseSymbol(theEnv);
					return;
			}
			switch(event.xcrossing.detail)
			{
				case NotifyAncestor:
					FBPutSlotSymbol(fb, "detail", "NotifyAncestor");
					break;
				case NotifyVirtual:
					FBPutSlotSymbol(fb, "detail", "NotifyVirtual");
					break;
				case NotifyInferior:
					FBPutSlotSymbol(fb, "detail", "NotifyInferior");
					break;
				case NotifyNonlinear:
					FBPutSlotSymbol(fb, "detail", "NotifyNonlinear");
					break;
				case NotifyNonlinearVirtual:
					FBPutSlotSymbol(fb, "detail", "NotifyNonlinearVirtual");
					break;
				case NotifyPointer:
					FBPutSlotSymbol(fb, "detail", "NotifyPointer");
					break;
				case NotifyPointerRoot:
					FBPutSlotSymbol(fb, "detail", "NotifyPointerRoot");
					break;
				case NotifyDetailNone:
					FBPutSlotSymbol(fb, "detail", "NotifyDetailNone");
					break;
				default:
					WriteString(theEnv,STDERR,"FocusOut detail ");
					WriteInteger(theEnv,STDERR,event.xcrossing.detail);
					WriteString(theEnv,STDERR," not supported.\n");
					returnValue->lexemeValue = FalseSymbol(theEnv);
					return;
			}
		case KeymapNotify:
			FBPutSlotSymbol(fb, "type", "KeymapNotify");
			f = FBAssert(fb);
			FBDispose(fb);
			fb = CreateFactBuilder(theEnv, "x-keymap-event");
			for (int x = 0; x < 32; x++)
			{
				MBAppendInteger(mb, event.xkeymap.key_vector[x]);
			}
			FBPutSlotMultifield(fb, "key-vector", MBCreate(mb));
			MBDispose(mb);
			break;
		case Expose:
			FBPutSlotSymbol(fb, "type", "Expose");
			f = FBAssert(fb);
			FBDispose(fb);
			fb = CreateFactBuilder(theEnv, "x-expose-event");
			FBPutSlotInteger(fb, "x", event.xexpose.x);
			FBPutSlotInteger(fb, "y", event.xexpose.y);
			FBPutSlotInteger(fb, "width", event.xexpose.width);
			FBPutSlotInteger(fb, "height", event.xexpose.height);
			FBPutSlotInteger(fb, "count", event.xexpose.count);
			break;
		case GraphicsExpose:
			FBPutSlotSymbol(fb, "type", "GraphicsExpose");
			f = FBAssert(fb);
			FBDispose(fb);
			fb = CreateFactBuilder(theEnv, "x-graphics-expose-event");
			FBPutSlotInteger(fb, "x", event.xgraphicsexpose.x);
			FBPutSlotInteger(fb, "y", event.xgraphicsexpose.y);
			FBPutSlotInteger(fb, "width", event.xgraphicsexpose.width);
			FBPutSlotInteger(fb, "height", event.xgraphicsexpose.height);
			FBPutSlotInteger(fb, "count", event.xgraphicsexpose.count);
			FBPutSlotInteger(fb, "major-code", event.xgraphicsexpose.major_code);
			FBPutSlotInteger(fb, "minor-code", event.xgraphicsexpose.minor_code);
			break;
		case NoExpose:
			FBPutSlotSymbol(fb, "type", "NoExpose");
			f = FBAssert(fb);
			FBDispose(fb);
			fb = CreateFactBuilder(theEnv, "x-no-expose-event");
			FBPutSlotInteger(fb, "drawable", event.xnoexpose.drawable);
			FBPutSlotInteger(fb, "major-code", event.xnoexpose.major_code);
			FBPutSlotInteger(fb, "minor-code", event.xnoexpose.minor_code);
			break;
		case CirculateRequest:
			FBPutSlotSymbol(fb, "type", "CirculateRequest");
			f = FBAssert(fb);
			FBDispose(fb);
			fb = CreateFactBuilder(theEnv, "x-circulate-request-event");
			FBPutSlotInteger(fb, "parent", event.xcirculaterequest.parent);
			switch(event.xcirculaterequest.place)
			{
				case PlaceOnTop:
					FBPutSlotSymbol(fb, "place", "PlaceOnTop");
					break;
				case PlaceOnBottom:
					FBPutSlotSymbol(fb, "place", "PlaceOnBottom");
					break;
				default:
					WriteString(theEnv,STDERR,"CirculateRequest place ");
					WriteInteger(theEnv,STDERR,event.xcirculaterequest.place);
					WriteString(theEnv,STDERR," not supported.\n");
					returnValue->lexemeValue = FalseSymbol(theEnv);
					return;
			}
			break;
		case ConfigureRequest:
			FBPutSlotSymbol(fb, "type", "ConfigureRequest");
			f = FBAssert(fb);
			FBDispose(fb);
			fb = CreateFactBuilder(theEnv, "x-configure-request-event");
			FBPutSlotInteger(fb, "parent", event.xconfigurerequest.parent);
			FBPutSlotInteger(fb, "x", event.xconfigurerequest.x);
			FBPutSlotInteger(fb, "y", event.xconfigurerequest.y);
			FBPutSlotInteger(fb, "width", event.xconfigurerequest.width);
			FBPutSlotInteger(fb, "height", event.xconfigurerequest.height);
			FBPutSlotInteger(fb, "border-width", event.xconfigurerequest.border_width);
			FBPutSlotInteger(fb, "above", event.xconfigurerequest.above);
			switch(event.xconfigurerequest.detail)
			{
				case Above:
					FBPutSlotSymbol(fb, "detail", "Above");
					break;
				case Below:
					FBPutSlotSymbol(fb, "detail", "Below");
					break;
				case TopIf:
					FBPutSlotSymbol(fb, "detail", "TopIf");
					break;
				case BottomIf:
					FBPutSlotSymbol(fb, "detail", "BottomIf");
					break;
				case Opposite:
					FBPutSlotSymbol(fb, "detail", "Opposite");
					break;
				default:
					WriteString(theEnv,STDERR,"ConfigureRequest detail ");
					WriteInteger(theEnv,STDERR,event.xconfigurerequest.detail);
					WriteString(theEnv,STDERR," not supported.\n");
					returnValue->lexemeValue = FalseSymbol(theEnv);
					return;
			}
			FBPutSlotInteger(fb, "value-mask", event.xconfigurerequest.value_mask);
			break;
		case MapRequest:
			FBPutSlotSymbol(fb, "type", "MapRequest");
			f = FBAssert(fb);
			FBDispose(fb);
			fb = CreateFactBuilder(theEnv, "x-map-request-event");
			FBPutSlotInteger(fb, "parent", event.xmaprequest.parent);
			break;
		case ResizeRequest:
			FBPutSlotSymbol(fb, "type", "ResizeRequest");
			f = FBAssert(fb);
			FBDispose(fb);
			fb = CreateFactBuilder(theEnv, "x-resize-request-event");
			FBPutSlotInteger(fb, "width", event.xresizerequest.width);
			FBPutSlotInteger(fb, "height", event.xresizerequest.height);
			break;
		case CirculateNotify:
			FBPutSlotSymbol(fb, "type", "CirculateNotify");
			f = FBAssert(fb);
			FBDispose(fb);
			fb = CreateFactBuilder(theEnv, "x-circulate-event");
			FBPutSlotInteger(fb, "event", event.xcirculate.event);
			switch(event.xcirculate.place)
			{
				case PlaceOnTop:
					FBPutSlotInteger(fb, "place", "PlaceOnTop");
					break;
				case PlaceOnBottom:
					FBPutSlotInteger(fb, "place", "PlaceOnBottom");
					break;
				default:
					WriteString(theEnv,STDERR,"CirculateNotify place ");
					WriteInteger(theEnv,STDERR,event.xcirculate.place);
					WriteString(theEnv,STDERR," not supported.\n");
					returnValue->lexemeValue = FalseSymbol(theEnv);
					return;
			}
			break;
		case ConfigureNotify:
			FBPutSlotSymbol(fb, "type", "ConfigureNotify");
			f = FBAssert(fb);
			FBDispose(fb);
			fb = CreateFactBuilder(theEnv, "x-configure-event");
			FBPutSlotInteger(fb, "event", event.xconfigure.event);
			FBPutSlotInteger(fb, "x", event.xconfigure.x);
			FBPutSlotInteger(fb, "y", event.xconfigure.y);
			FBPutSlotInteger(fb, "width", event.xconfigure.width);
			FBPutSlotInteger(fb, "height", event.xconfigure.height);
			FBPutSlotInteger(fb, "border-width", event.xconfigure.border_width);
			FBPutSlotInteger(fb, "above", event.xconfigure.above);
			if (event.xconfigure.override_redirect)
			{
				FBPutSlotSymbol(fb, "override-redirect", "TRUE");
			}
			else
			{
				FBPutSlotSymbol(fb, "override-redirect", "FALSE");
			}
			break;
		case CreateNotify:
			FBPutSlotSymbol(fb, "type", "CreateNotify");
			f = FBAssert(fb);
			FBDispose(fb);
			fb = CreateFactBuilder(theEnv, "x-create-window-event");
			FBPutSlotInteger(fb, "parent", event.xcreatewindow.parent);
			FBPutSlotInteger(fb, "x", event.xcreatewindow.x);
			FBPutSlotInteger(fb, "y", event.xcreatewindow.y);
			FBPutSlotInteger(fb, "width", event.xcreatewindow.width);
			FBPutSlotInteger(fb, "height", event.xcreatewindow.height);
			FBPutSlotInteger(fb, "border-width", event.xcreatewindow.border_width);
			if (event.xcreatewindow.override_redirect)
			{
				FBPutSlotSymbol(fb, "override-redirect", "TRUE");
			}
			else
			{
				FBPutSlotSymbol(fb, "override-redirect", "FALSE");
			}
			break;
		case DestroyNotify:
			FBPutSlotSymbol(fb, "type", "DestroyNotify");
			f = FBAssert(fb);
			FBDispose(fb);
			fb = CreateFactBuilder(theEnv, "x-destroy-window-event");
			FBPutSlotInteger(fb, "event", event.xdestroywindow.event);
			break;
		case GravityNotify:
			FBPutSlotSymbol(fb, "type", "GravityNotify");
			f = FBAssert(fb);
			FBDispose(fb);
			fb = CreateFactBuilder(theEnv, "x-gravity-event");
			FBPutSlotInteger(fb, "event", event.xgravity.event);
			break;
		case MapNotify:
			FBPutSlotSymbol(fb, "type", "MapNotify");
			f = FBAssert(fb);
			FBDispose(fb);
			fb = CreateFactBuilder(theEnv, "x-map-event");
			FBPutSlotInteger(fb, "event", event.xmap.event);
			if (event.xmap.override_redirect)
			{
				FBPutSlotSymbol(fb, "override-redirect", "TRUE");
			}
			else
			{
				FBPutSlotSymbol(fb, "override-redirect", "FALSE");
			}
			break;
		case MappingNotify:
			FBPutSlotSymbol(fb, "type", "MappingNotify");
			f = FBAssert(fb);
			FBDispose(fb);
			fb = CreateFactBuilder(theEnv, "x-mapping-event");
			FBPutSlotInteger(fb, "request", event.xmapping.request);
			FBPutSlotInteger(fb, "first-keycode", event.xmapping.first_keycode);
			FBPutSlotInteger(fb, "count", event.xmapping.count);
			break;
		case ReparentNotify:
			FBPutSlotSymbol(fb, "type", "ReparentNotify");
			f = FBAssert(fb);
			FBDispose(fb);
			fb = CreateFactBuilder(theEnv, "x-reparent-event");
			FBPutSlotInteger(fb, "event", event.xreparent.event);
			FBPutSlotInteger(fb, "parent", event.xreparent.parent);
			FBPutSlotInteger(fb, "x", event.xreparent.x);
			FBPutSlotInteger(fb, "y", event.xreparent.y);
			if (event.xreparent.override_redirect)
			{
				FBPutSlotSymbol(fb, "override-redirect", "TRUE");
			}
			else
			{
				FBPutSlotSymbol(fb, "override-redirect", "FALSE");
			}
			break;
		case UnmapNotify:
			FBPutSlotSymbol(fb, "type", "UnmapNotify");
			f = FBAssert(fb);
			FBDispose(fb);
			fb = CreateFactBuilder(theEnv, "x-reparent-event");
			FBPutSlotInteger(fb, "event", event.xunmap.event);
			if (event.xunmap.from_configure)
			{
				FBPutSlotSymbol(fb, "from-configure", "TRUE");
			}
			else
			{
				FBPutSlotSymbol(fb, "from-configure", "FALSE");
			}
			break;
		case VisibilityNotify:
			FBPutSlotSymbol(fb, "type", "VisibilityNotify");
			f = FBAssert(fb);
			FBDispose(fb);
			fb = CreateFactBuilder(theEnv, "x-visibility-event");
			if (event.xvisibility.state & VisibilityUnobscured) {
				MBAppendSymbol(mb, "VisibilityUnobscured");
			}
			if (event.xvisibility.state & VisibilityPartiallyObscured) {
				MBAppendSymbol(mb, "VisibilityPartiallyObscured");
			}
			if (event.xvisibility.state & VisibilityFullyObscured) {
				MBAppendSymbol(mb, "VisibilityFullyObscured");
			}
			FBPutSlotMultifield(fb, "state", MBCreate(mb));
			MBDispose(mb);
			break;
		case ColormapNotify:
			FBPutSlotSymbol(fb, "type", "ColormapNotify");
			f = FBAssert(fb);
			FBDispose(fb);
			fb = CreateFactBuilder(theEnv, "x-colormap-event");
			if (event.xcolormap.colormap == None)
			{
				FBPutSlotSymbol(fb, "colormap", "None");
			}
			else
			{
				FBPutSlotInteger(fb, "colormap", event.xcolormap.colormap);
			}
			if (event.xcolormap.new)
			{
				FBPutSlotSymbol(fb, "new", "TRUE");
			}
			else
			{
				FBPutSlotSymbol(fb, "new", "FALSE");
			}
			switch(event.xcolormap.state)
			{	
				case ColormapInstalled:
					FBPutSlotSymbol(fb, "state", "ColormapInstalled");
					break;
				case ColormapUninstalled:
					FBPutSlotSymbol(fb, "state", "ColormapUninstalled");
					break;
				default:
					break;
			}
			break;
		case ClientMessage:
			FBPutSlotSymbol(fb, "type", "ClientMessage");
			f = FBAssert(fb);
			FBDispose(fb);
			fb = CreateFactBuilder(theEnv, "x-client-message-event");
			FBPutSlotInteger(fb, "message-type", event.xclient.message_type);
			FBPutSlotInteger(fb, "format", event.xclient.format);
			if (event.xclient.format == 8)
			{
				for (int x = 0; x < 20; x++)
				{
					MBAppendInteger(mb, event.xclient.data.b[x]);
				}
			}
			else if (event.xclient.format == 16)
			{
				for (int x = 0; x < 10; x++)
				{
					MBAppendInteger(mb, event.xclient.data.s[x]);
				}
			}
			else if (event.xclient.format == 32)
			{
				for (int x = 0; x < 5; x++)
				{
					MBAppendInteger(mb, event.xclient.data.l[x]);
				}
			}
			FBPutSlotMultifield(fb, "data", MBCreate(mb));
			MBDispose(mb);
			break;
		case PropertyNotify:
			FBPutSlotSymbol(fb, "type", "PropertyNotify");
			f = FBAssert(fb);
			FBDispose(fb);
			fb = CreateFactBuilder(theEnv, "x-property-event");
			FBPutSlotInteger(fb, "atom", event.xproperty.atom);
			FBPutSlotInteger(fb, "time", event.xproperty.time);
			switch(event.xproperty.state)
			{
				case PropertyNewValue:
					FBPutSlotSymbol(fb, "state", "PropertyNewValue");
					break;
				case PropertyDelete:
					FBPutSlotSymbol(fb, "state", "PropertyDelete");
					break;
				default:
					break;
			}
			break;
		case SelectionClear:
			FBPutSlotSymbol(fb, "type", "SelectionClear");
			f = FBAssert(fb);
			FBDispose(fb);
			fb = CreateFactBuilder(theEnv, "x-selection-clear-event");
			FBPutSlotInteger(fb, "selection", event.xselectionclear.selection);
			FBPutSlotInteger(fb, "time", event.xselectionclear.time);
			break;
		case SelectionNotify:
			FBPutSlotSymbol(fb, "type", "SelectionNotify");
			f = FBAssert(fb);
			FBDispose(fb);
			fb = CreateFactBuilder(theEnv, "x-selection-notify-event");
			FBPutSlotInteger(fb, "requestor", event.xselection.requestor);
			FBPutSlotInteger(fb, "selection", event.xselection.selection);
			FBPutSlotInteger(fb, "target", event.xselection.target);
			FBPutSlotInteger(fb, "property", event.xselection.property);
			FBPutSlotInteger(fb, "time", event.xselection.time);
			break;
		case SelectionRequest:
			FBPutSlotSymbol(fb, "type", "SelectionRequest");
			f = FBAssert(fb);
			FBDispose(fb);
			fb = CreateFactBuilder(theEnv, "x-selection-notify-event");
			FBPutSlotInteger(fb, "owner", event.xselectionrequest.owner);
			FBPutSlotInteger(fb, "requestor", event.xselectionrequest.requestor);
			FBPutSlotInteger(fb, "selection", event.xselectionrequest.selection);
			FBPutSlotInteger(fb, "target", event.xselectionrequest.target);
			FBPutSlotInteger(fb, "property", event.xselectionrequest.property);
			FBPutSlotInteger(fb, "time", event.xselectionrequest.time);
			break;
		default:
			WriteString(theEnv,STDERR,"Event Type ");
			WriteInteger(theEnv,STDERR,event.type);
			WriteString(theEnv,STDERR," not supported.\n");
			returnValue->lexemeValue = FalseSymbol(theEnv);
			return;
	}
	returnValue->multifieldValue = MBCreate(mb);
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
	XComposeStatus compose;
	char buffer[32];
	KeySym keysym;
	UDFValue theArg;

	UDFNextArgument(context,EXTERNAL_ADDRESS_BIT,&theArg);
	display = theArg.externalAddressValue->contents;

	XNextEvent(display, &event);

	mb = CreateMultifieldBuilder(theEnv, 5);
	MBAppendInteger(mb, event.xany.serial);
	if (event.xany.send_event)
	{
		MBAppendSymbol(mb, "TRUE");
	}
	else
	{
		MBAppendSymbol(mb, "FALSE");
	}
	MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, event.xany.display));
	MBAppendInteger(mb, event.xany.window);
	switch (event.type)
	{
		case KeyPress:
			MBAppendSymbol(mb, "KeyPress");
			MBAppendInteger(mb, event.xkey.root);
			MBAppendInteger(mb, event.xkey.subwindow);
			MBAppendInteger(mb, event.xkey.time);
			MBAppendInteger(mb, event.xkey.x);
			MBAppendInteger(mb, event.xkey.y);
			MBAppendInteger(mb, event.xkey.x_root);
			MBAppendInteger(mb, event.xkey.y_root);
			MBAppendInteger(mb, event.xkey.state);
			MBAppendInteger(mb, event.xkey.keycode);
			if (event.xkey.same_screen)
			{
				MBAppendSymbol(mb, "TRUE");
			}
			else
			{
				MBAppendSymbol(mb, "FALSE");
			}
			XLookupString(&event.xkey, buffer, sizeof(buffer), &keysym, &compose);
			MBAppendSymbol(mb, buffer);
			MBAppendInteger(mb, keysym);
			MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, compose.compose_ptr));
			MBAppendInteger(mb, compose.chars_matched);
			break;
		case KeyRelease:
			MBAppendSymbol(mb, "KeyRelease");
			MBAppendInteger(mb, event.xkey.root);
			MBAppendInteger(mb, event.xkey.subwindow);
			MBAppendInteger(mb, event.xkey.time);
			MBAppendInteger(mb, event.xkey.x);
			MBAppendInteger(mb, event.xkey.y);
			MBAppendInteger(mb, event.xkey.x_root);
			MBAppendInteger(mb, event.xkey.y_root);
			MBAppendInteger(mb, event.xkey.state);
			MBAppendInteger(mb, event.xkey.keycode);
			if (event.xkey.same_screen)
			{
				MBAppendSymbol(mb, "TRUE");
			}
			else
			{
				MBAppendSymbol(mb, "FALSE");
			}
			XLookupString(&event.xkey, buffer, sizeof(buffer), &keysym, &compose);
			MBAppendSymbol(mb, buffer);
			MBAppendInteger(mb, keysym);
			MBAppendCLIPSExternalAddress(mb, CreateCExternalAddress(theEnv, compose.compose_ptr));
			MBAppendInteger(mb, compose.chars_matched);
			break;
		case ButtonPress:
			MBAppendSymbol(mb, "ButtonPress");
			MBAppendInteger(mb, event.xbutton.root);
			MBAppendInteger(mb, event.xbutton.subwindow);
			MBAppendInteger(mb, event.xbutton.time);
			MBAppendInteger(mb, event.xbutton.x);
			MBAppendInteger(mb, event.xbutton.y);
			MBAppendInteger(mb, event.xbutton.x_root);
			MBAppendInteger(mb, event.xbutton.y_root);
			MBAppendInteger(mb, event.xbutton.state);
			MBAppendInteger(mb, event.xbutton.button);
			if (event.xbutton.same_screen)
			{
				MBAppendSymbol(mb, "TRUE");
			}
			else
			{
				MBAppendSymbol(mb, "FALSE");
			}
			break;
		case ButtonRelease:
			MBAppendSymbol(mb, "ButtonRelease");
			MBAppendInteger(mb, event.xbutton.root);
			MBAppendInteger(mb, event.xbutton.subwindow);
			MBAppendInteger(mb, event.xbutton.time);
			MBAppendInteger(mb, event.xbutton.x);
			MBAppendInteger(mb, event.xbutton.y);
			MBAppendInteger(mb, event.xbutton.x_root);
			MBAppendInteger(mb, event.xbutton.y_root);
			MBAppendInteger(mb, event.xbutton.state);
			MBAppendInteger(mb, event.xbutton.button);
			if (event.xbutton.same_screen)
			{
				MBAppendSymbol(mb, "TRUE");
			}
			else
			{
				MBAppendSymbol(mb, "FALSE");
			}
			break;
		case MotionNotify:
			MBAppendSymbol(mb, "MotionNotify");
			MBAppendInteger(mb, event.xmotion.root);
			MBAppendInteger(mb, event.xmotion.subwindow);
			MBAppendInteger(mb, event.xmotion.time);
			MBAppendInteger(mb, event.xmotion.x);
			MBAppendInteger(mb, event.xmotion.y);
			MBAppendInteger(mb, event.xmotion.x_root);
			MBAppendInteger(mb, event.xmotion.y_root);
			switch(event.xmotion.is_hint)
			{
				case NotifyNormal:
					MBAppendSymbol(mb, "NotifyNormal");
					break;
				case NotifyHint:
					MBAppendSymbol(mb, "NotifyHint");
					break;
				default:
					WriteString(theEnv,STDERR,"Notify hint type ");
					WriteInteger(theEnv,STDERR,event.xmotion.is_hint);
					WriteString(theEnv,STDERR," not supported.\n");
					returnValue->lexemeValue = FalseSymbol(theEnv);
					return;
			}
			if (event.xmotion.same_screen)
			{
				MBAppendSymbol(mb, "TRUE");
			}
			else
			{
				MBAppendSymbol(mb, "FALSE");
			}
			break;
		case EnterNotify:
			MBAppendSymbol(mb, "EnterNotify");
			MBAppendInteger(mb, event.xcrossing.root);
			MBAppendInteger(mb, event.xcrossing.subwindow);
			MBAppendInteger(mb, event.xcrossing.time);
			MBAppendInteger(mb, event.xcrossing.x);
			MBAppendInteger(mb, event.xcrossing.y);
			MBAppendInteger(mb, event.xcrossing.x_root);
			MBAppendInteger(mb, event.xcrossing.y_root);
			switch(event.xcrossing.mode)
			{
				case NotifyNormal:
					break;
				case NotifyGrab:
					break;
				case NotifyUngrab:
					break;
				default:
					WriteString(theEnv,STDERR,"EnterNotify mode ");
					WriteInteger(theEnv,STDERR,event.xcrossing.mode);
					WriteString(theEnv,STDERR," not supported.\n");
					returnValue->lexemeValue = FalseSymbol(theEnv);
					return;
			}
			switch(event.xcrossing.detail)
			{
				case NotifyAncestor:
					break;
				case NotifyVirtual:
					break;
				case NotifyInferior:
					break;
				case NotifyNonlinear:
					break;
				case NotifyNonlinearVirtual:
					break;
				default:
					WriteString(theEnv,STDERR,"EnterNotify detail ");
					WriteInteger(theEnv,STDERR,event.xcrossing.detail);
					WriteString(theEnv,STDERR," not supported.\n");
					returnValue->lexemeValue = FalseSymbol(theEnv);
					return;
			}
			if (event.xcrossing.same_screen)
			{
				MBAppendSymbol(mb, "TRUE");
			}
			else
			{
				MBAppendSymbol(mb, "FALSE");
			}
			if (event.xcrossing.focus)
			{
				MBAppendSymbol(mb, "TRUE");
			}
			else
			{
				MBAppendSymbol(mb, "FALSE");
			}
			if (event.xcrossing.state & Button1Mask) {
				MBAppendSymbol(mb, "Button1");
			}
			if (event.xcrossing.state & Button2Mask) {
				MBAppendSymbol(mb, "Button2");
			}
			if (event.xcrossing.state & Button3Mask) {
				MBAppendSymbol(mb, "Button3");
			}
			if (event.xcrossing.state & Button4Mask) {
				MBAppendSymbol(mb, "Button4");
			}
			if (event.xcrossing.state & Button5Mask) {
				MBAppendSymbol(mb, "Button5");
			}
			if (event.xcrossing.state & ShiftMask) {
				MBAppendSymbol(mb, "Shift");
			}
			if (event.xcrossing.state & LockMask) {
				MBAppendSymbol(mb, "Lock");
			}
			if (event.xcrossing.state & ControlMask) {
				MBAppendSymbol(mb, "Control");
			}
			if (event.xcrossing.state & Mod1Mask) {
				MBAppendSymbol(mb, "Mod1");
			}
			if (event.xcrossing.state & Mod2Mask) {
				MBAppendSymbol(mb, "Mod2");
			}
			if (event.xcrossing.state & Mod3Mask) {
				MBAppendSymbol(mb, "Mod3");
			}
			if (event.xcrossing.state & Mod4Mask) {
				MBAppendSymbol(mb, "Mod4");
			}
			if (event.xcrossing.state & Mod5Mask) {
				MBAppendSymbol(mb, "Mod5");
			}
			break;
		case LeaveNotify:
			MBAppendSymbol(mb, "LeaveNotify");
			MBAppendInteger(mb, event.xcrossing.root);
			MBAppendInteger(mb, event.xcrossing.subwindow);
			MBAppendInteger(mb, event.xcrossing.time);
			MBAppendInteger(mb, event.xcrossing.x);
			MBAppendInteger(mb, event.xcrossing.y);
			MBAppendInteger(mb, event.xcrossing.x_root);
			MBAppendInteger(mb, event.xcrossing.y_root);
			switch(event.xcrossing.mode)
			{
				case NotifyNormal:
					break;
				case NotifyGrab:
					break;
				case NotifyUngrab:
					break;
				default:
					WriteString(theEnv,STDERR,"LeaveNotify mode ");
					WriteInteger(theEnv,STDERR,event.xcrossing.mode);
					WriteString(theEnv,STDERR," not supported.\n");
					returnValue->lexemeValue = FalseSymbol(theEnv);
					return;
			}
			switch(event.xcrossing.detail)
			{
				case NotifyAncestor:
					break;
				case NotifyVirtual:
					break;
				case NotifyInferior:
					break;
				case NotifyNonlinear:
					break;
				case NotifyNonlinearVirtual:
					break;
				default:
					WriteString(theEnv,STDERR,"LeaveNotify detail ");
					WriteInteger(theEnv,STDERR,event.xcrossing.detail);
					WriteString(theEnv,STDERR," not supported.\n");
					returnValue->lexemeValue = FalseSymbol(theEnv);
					return;
			}
			if (event.xcrossing.same_screen)
			{
				MBAppendSymbol(mb, "TRUE");
			}
			else
			{
				MBAppendSymbol(mb, "FALSE");
			}
			if (event.xcrossing.focus)
			{
				MBAppendSymbol(mb, "TRUE");
			}
			else
			{
				MBAppendSymbol(mb, "FALSE");
			}
			if (event.xcrossing.state & Button1Mask) {
				MBAppendSymbol(mb, "Button1");
			}
			if (event.xcrossing.state & Button2Mask) {
				MBAppendSymbol(mb, "Button2");
			}
			if (event.xcrossing.state & Button3Mask) {
				MBAppendSymbol(mb, "Button3");
			}
			if (event.xcrossing.state & Button4Mask) {
				MBAppendSymbol(mb, "Button4");
			}
			if (event.xcrossing.state & Button5Mask) {
				MBAppendSymbol(mb, "Button5");
			}
			if (event.xcrossing.state & ShiftMask) {
				MBAppendSymbol(mb, "Shift");
			}
			if (event.xcrossing.state & LockMask) {
				MBAppendSymbol(mb, "Lock");
			}
			if (event.xcrossing.state & ControlMask) {
				MBAppendSymbol(mb, "Control");
			}
			if (event.xcrossing.state & Mod1Mask) {
				MBAppendSymbol(mb, "Mod1");
			}
			if (event.xcrossing.state & Mod2Mask) {
				MBAppendSymbol(mb, "Mod2");
			}
			if (event.xcrossing.state & Mod3Mask) {
				MBAppendSymbol(mb, "Mod3");
			}
			if (event.xcrossing.state & Mod4Mask) {
				MBAppendSymbol(mb, "Mod4");
			}
			if (event.xcrossing.state & Mod5Mask) {
				MBAppendSymbol(mb, "Mod5");
			}
			break;
		case FocusIn:
			MBAppendSymbol(mb, "FocusIn");
			MBAppendInteger(mb, event.xcrossing.root);
			MBAppendInteger(mb, event.xcrossing.subwindow);
			MBAppendInteger(mb, event.xcrossing.time);
			MBAppendInteger(mb, event.xcrossing.x);
			MBAppendInteger(mb, event.xcrossing.y);
			MBAppendInteger(mb, event.xcrossing.x_root);
			MBAppendInteger(mb, event.xcrossing.y_root);
			switch(event.xcrossing.mode)
			{
				case NotifyNormal:
					break;
				case NotifyGrab:
					break;
				case NotifyUngrab:
					break;
				default:
					WriteString(theEnv,STDERR,"FocusIn mode ");
					WriteInteger(theEnv,STDERR,event.xcrossing.mode);
					WriteString(theEnv,STDERR," not supported.\n");
					returnValue->lexemeValue = FalseSymbol(theEnv);
					return;
			}
			switch(event.xcrossing.detail)
			{
				case NotifyAncestor:
					break;
				case NotifyVirtual:
					break;
				case NotifyInferior:
					break;
				case NotifyNonlinear:
					break;
				case NotifyNonlinearVirtual:
					break;
				case NotifyPointer:
					break;
				case NotifyPointerRoot:
					break;
				case NotifyDetailNone:
					break;
				default:
					WriteString(theEnv,STDERR,"FocusIn detail ");
					WriteInteger(theEnv,STDERR,event.xcrossing.detail);
					WriteString(theEnv,STDERR," not supported.\n");
					returnValue->lexemeValue = FalseSymbol(theEnv);
					return;
			}
			break;
		case FocusOut:
			MBAppendSymbol(mb, "FocusOut");
			MBAppendInteger(mb, event.xcrossing.root);
			MBAppendInteger(mb, event.xcrossing.subwindow);
			MBAppendInteger(mb, event.xcrossing.time);
			MBAppendInteger(mb, event.xcrossing.x);
			MBAppendInteger(mb, event.xcrossing.y);
			MBAppendInteger(mb, event.xcrossing.x_root);
			MBAppendInteger(mb, event.xcrossing.y_root);
			switch(event.xcrossing.mode)
			{
				case NotifyNormal:
					break;
				case NotifyGrab:
					break;
				case NotifyUngrab:
					break;
				default:
					WriteString(theEnv,STDERR,"FocusOut mode ");
					WriteInteger(theEnv,STDERR,event.xcrossing.mode);
					WriteString(theEnv,STDERR," not supported.\n");
					returnValue->lexemeValue = FalseSymbol(theEnv);
					return;
			}
			switch(event.xcrossing.detail)
			{
				case NotifyAncestor:
					break;
				case NotifyVirtual:
					break;
				case NotifyInferior:
					break;
				case NotifyNonlinear:
					break;
				case NotifyNonlinearVirtual:
					break;
				case NotifyPointer:
					break;
				case NotifyPointerRoot:
					break;
				case NotifyDetailNone:
					break;
				default:
					WriteString(theEnv,STDERR,"FocusIn detail ");
					WriteInteger(theEnv,STDERR,event.xcrossing.detail);
					WriteString(theEnv,STDERR," not supported.\n");
					returnValue->lexemeValue = FalseSymbol(theEnv);
					return;
			}
			MBAppendSymbol(mb, "FocusOut");
			break;
		case KeymapNotify:
			MBAppendSymbol(mb, "KeymapNotify");
			MBAppendString(mb, event.xkeymap.key_vector);
			break;
		case Expose:
			MBAppendSymbol(mb, "Expose");
			MBAppendInteger(mb, event.xexpose.x);
			MBAppendInteger(mb, event.xexpose.y);
			MBAppendInteger(mb, event.xexpose.width);
			MBAppendInteger(mb, event.xexpose.height);
			MBAppendInteger(mb, event.xexpose.count);
			break;
		case GraphicsExpose:
			MBAppendSymbol(mb, "GraphicsExpose");
			MBAppendInteger(mb, event.xgraphicsexpose.drawable);
			MBAppendInteger(mb, event.xgraphicsexpose.x);
			MBAppendInteger(mb, event.xgraphicsexpose.y);
			MBAppendInteger(mb, event.xgraphicsexpose.width);
			MBAppendInteger(mb, event.xgraphicsexpose.height);
			MBAppendInteger(mb, event.xgraphicsexpose.count);
			MBAppendInteger(mb, event.xgraphicsexpose.major_code);
			MBAppendInteger(mb, event.xgraphicsexpose.minor_code);
			break;
		case NoExpose:
			MBAppendSymbol(mb, "NoExpose");
			MBAppendInteger(mb, event.xnoexpose.drawable);
			MBAppendInteger(mb, event.xnoexpose.major_code);
			MBAppendInteger(mb, event.xnoexpose.minor_code);
			break;
		case CirculateRequest:
			MBAppendSymbol(mb, "CirculateRequest");
			MBAppendInteger(mb, event.xcirculaterequest.parent);
			switch(event.xcirculaterequest.place)
			{
				case PlaceOnTop:
					break;
				case PlaceOnBottom:
					break;
				default:
					WriteString(theEnv,STDERR,"CirculateRequest place ");
					WriteInteger(theEnv,STDERR,event.xcirculaterequest.place);
					WriteString(theEnv,STDERR," not supported.\n");
					returnValue->lexemeValue = FalseSymbol(theEnv);
					return;
			}
			break;
		case ConfigureRequest:
			MBAppendSymbol(mb, "ConfigureRequest");
			MBAppendInteger(mb, event.xconfigurerequest.parent);
			MBAppendInteger(mb, event.xconfigurerequest.x);
			MBAppendInteger(mb, event.xconfigurerequest.y);
			MBAppendInteger(mb, event.xconfigurerequest.width);
			MBAppendInteger(mb, event.xconfigurerequest.height);
			MBAppendInteger(mb, event.xconfigurerequest.border_width);
			MBAppendInteger(mb, event.xconfigurerequest.above);
			switch(event.xconfigurerequest.detail)
			{
				case Above:
					break;
				case Below:
					break;
				case TopIf:
					break;
				case BottomIf:
					break;
				case Opposite:
					break;
				default:
					WriteString(theEnv,STDERR,"ConfigureRequest detail ");
					WriteInteger(theEnv,STDERR,event.xconfigurerequest.detail);
					WriteString(theEnv,STDERR," not supported.\n");
					returnValue->lexemeValue = FalseSymbol(theEnv);
					return;
			}
			MBAppendInteger(mb, event.xconfigurerequest.value_mask);
			break;
		case MapRequest:
			MBAppendSymbol(mb, "MapRequest");
			MBAppendInteger(mb, event.xmaprequest.parent);
			break;
		case ResizeRequest:
			MBAppendSymbol(mb, "ResizeRequest");
			MBAppendInteger(mb, event.xresizerequest.width);
			MBAppendInteger(mb, event.xresizerequest.height);
			break;
		case CirculateNotify:
			MBAppendSymbol(mb, "CirculateNotify");
			MBAppendInteger(mb, event.xcirculate.event);
			switch(event.xcirculate.place)
			{
				case PlaceOnTop:
					break;
				case PlaceOnBottom:
					break;
				default:
					WriteString(theEnv,STDERR,"CirculateNotify place ");
					WriteInteger(theEnv,STDERR,event.xcirculate.place);
					WriteString(theEnv,STDERR," not supported.\n");
					returnValue->lexemeValue = FalseSymbol(theEnv);
					return;
			}
			break;
		case ConfigureNotify:
			MBAppendSymbol(mb, "ConfigureNotify");
			MBAppendInteger(mb, event.xconfigure.event);
			MBAppendInteger(mb, event.xconfigure.x);
			MBAppendInteger(mb, event.xconfigure.y);
			MBAppendInteger(mb, event.xconfigure.width);
			MBAppendInteger(mb, event.xconfigure.height);
			MBAppendInteger(mb, event.xconfigure.border_width);
			MBAppendInteger(mb, event.xconfigure.above);
			if (event.xconfigure.override_redirect)
			{
				MBAppendSymbol(mb, "TRUE");
			}
			else
			{
				MBAppendSymbol(mb, "FALSE");
			}
			break;
		case CreateNotify:
			MBAppendSymbol(mb, "CreateNotify");
			MBAppendInteger(mb, event.xcreatewindow.parent);
			MBAppendInteger(mb, event.xcreatewindow.x);
			MBAppendInteger(mb, event.xcreatewindow.y);
			MBAppendInteger(mb, event.xcreatewindow.width);
			MBAppendInteger(mb, event.xcreatewindow.height);
			MBAppendInteger(mb, event.xcreatewindow.border_width);
			if (event.xcreatewindow.override_redirect)
			{
				MBAppendSymbol(mb, "TRUE");
			}
			else
			{
				MBAppendSymbol(mb, "FALSE");
			}
			break;
		case DestroyNotify:
			MBAppendSymbol(mb, "DestroyNotify");
			MBAppendInteger(mb, event.xdestroywindow.event);
			break;
		case GravityNotify:
			MBAppendSymbol(mb, "GravityNotify");
			MBAppendInteger(mb, event.xgravity.event);
			break;
		case MapNotify:
			MBAppendSymbol(mb, "MapNotify");
			MBAppendInteger(mb, event.xmap.event);
			MBAppendInteger(mb, event.xmap.override_redirect);
			break;
		case MappingNotify:
			MBAppendSymbol(mb, "MappingNotify");
			MBAppendInteger(mb, event.xmapping.request);
			MBAppendInteger(mb, event.xmapping.first_keycode);
			MBAppendInteger(mb, event.xmapping.count);
			break;
		case ReparentNotify:
			MBAppendSymbol(mb, "ReparentNotify");
			MBAppendInteger(mb, event.xreparent.event);
			MBAppendInteger(mb, event.xreparent.parent);
			MBAppendInteger(mb, event.xreparent.x);
			MBAppendInteger(mb, event.xreparent.y);
			if (event.xreparent.override_redirect)
			{
				MBAppendSymbol(mb, "TRUE");
			}
			else
			{
				MBAppendSymbol(mb, "FALSE");
			}
			break;
		case UnmapNotify:
			MBAppendSymbol(mb, "UnmapNotify");
			MBAppendInteger(mb, event.xunmap.event);
			if (event.xunmap.from_configure)
			{
				MBAppendSymbol(mb, "TRUE");
			}
			else
			{
				MBAppendSymbol(mb, "FALSE");
			}
			break;
		case VisibilityNotify:
			MBAppendSymbol(mb, "VisibilityNotify");
			if (event.xvisibility.state & VisibilityUnobscured) {
				MBAppendSymbol(mb, "VisibilityUnobscured");
			}
			if (event.xvisibility.state & VisibilityPartiallyObscured) {
				MBAppendSymbol(mb, "VisibilityPartiallyObscured");
			}
			if (event.xvisibility.state & VisibilityFullyObscured) {
				MBAppendSymbol(mb, "VisibilityFullyObscured");
			}
			break;
		case ColormapNotify:
			MBAppendSymbol(mb, "ColormapNotify");
			if (event.xcolormap.colormap == None)
			{
				MBAppendSymbol(mb, "None");
			}
			else
			{
				MBAppendInteger(mb, event.xcolormap.colormap);
			}
			if (event.xcolormap.new)
			{
				MBAppendSymbol(mb, "TRUE");
			}
			else
			{
				MBAppendSymbol(mb, "FALSE");
			}
			if (event.xcolormap.state & ColormapInstalled) {
				MBAppendSymbol(mb, "ColormapInstalled");
			}
			if (event.xcolormap.state & ColormapUninstalled) {
				MBAppendSymbol(mb, "ColormapUninstalled");
			}
			break;
		case ClientMessage:
			MBAppendSymbol(mb, "ClientMessage");
			MBAppendInteger(mb, event.xclient.message_type);
			MBAppendInteger(mb, event.xclient.format);
			if (event.xclient.format == 8)
			{
				for (int x = 0; x < 20; x++)
				{
					MBAppendInteger(mb, event.xclient.data.b[x]);
				}
			}
			else if (event.xclient.format == 16)
			{
				for (int x = 0; x < 10; x++)
				{
					MBAppendInteger(mb, event.xclient.data.s[x]);
				}
			}
			else if (event.xclient.format == 32)
			{
				for (int x = 0; x < 5; x++)
				{
					MBAppendInteger(mb, event.xclient.data.l[x]);
				}
			}
			break;
		case PropertyNotify:
			MBAppendSymbol(mb, "PropertyNotify");
			MBAppendInteger(mb, event.xproperty.atom);
			MBAppendInteger(mb, event.xproperty.time);
			if (event.xproperty.state & PropertyNewValue)
			{
				MBAppendSymbol(mb, "PropertyNewValue");
			}
			else if (event.xproperty.state & PropertyDelete)
			{
				MBAppendSymbol(mb, "PropertyDelete");
			}
			break;
		case SelectionClear:
			MBAppendSymbol(mb, "SelectionClear");
			MBAppendInteger(mb, event.xselectionclear.selection);
			MBAppendInteger(mb, event.xselectionclear.time);
			break;
		case SelectionNotify:
			MBAppendSymbol(mb, "SelectionNotify");
			MBAppendInteger(mb, event.xselection.requestor);
			MBAppendInteger(mb, event.xselection.selection);
			MBAppendInteger(mb, event.xselection.target);
			MBAppendInteger(mb, event.xselection.property);
			MBAppendInteger(mb, event.xselection.time);
			break;
		case SelectionRequest:
			MBAppendSymbol(mb, "SelectionRequest");
			MBAppendInteger(mb, event.xselectionrequest.owner);
			MBAppendInteger(mb, event.xselectionrequest.requestor);
			MBAppendInteger(mb, event.xselectionrequest.selection);
			MBAppendInteger(mb, event.xselectionrequest.target);
			MBAppendInteger(mb, event.xselectionrequest.property);
			MBAppendInteger(mb, event.xselectionrequest.time);
			break;
		default:
			WriteString(theEnv,STDERR,"Event Type ");
			WriteInteger(theEnv,STDERR,event.type);
			WriteString(theEnv,STDERR," not supported.\n");
			returnValue->lexemeValue = FalseSymbol(theEnv);
			return;
	}
	returnValue->multifieldValue = MBCreate(mb);
	MBDispose(mb);
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
	  AddUDF(env,"default-screen","l",1,1,";e",DefaultScreenFunction,"DefaultScreenOfDisplayFunction",NULL);
	  AddUDF(env,"default-screen-of-display","l",1,1,";e",DefaultScreenOfDisplayFunction,"DefaultScreenOfDisplayFunction",NULL);
	  AddUDF(env,"root-window","l",2,2,";e;l",RootWindowFunction,"RootWindowFunction",NULL);
	  AddUDF(env,"x-create-simple-window","bl",9,9,";e;l;l;l;l;l;l;l;l",XCreateSimpleWindowFunction,"XCreateSimpleWindowFunction",NULL);
	  AddUDF(env,"x-create-window","bl",12,12,";e;l;l;l;l;l;l;l;l;e;l;e",XCreateWindowFunction,"XCreateWindowFunction",NULL);
	  AddUDF(env,"x-create-font-cursor","bl",2,2,";e;y",XCreateFontCursorFunction,"XCreateFontCursorFunction",NULL);
	  AddUDF(env,"x-define-cursor","v",3,3,";e;l;l",XDefineCursorFunction,"XDefineCursorFunction",NULL);
	  AddUDF(env,"x-map-window","v",2,2,";e;l",XMapWindowFunction,"XMapWindowFunction",NULL);
	  AddUDF(env,"black-pixel","l",2,2,";e;l",BlackPixelFunction,"BlackPixelFunction",NULL);
	  AddUDF(env,"white-pixel","l",2,2,";e;l",WhitePixelFunction,"WhitePixelFunction",NULL);

	  AddUDF(env,"x-create-gc","e",3,3,";e;l;l",XCreateGCFunction,"XCreateGCFunction",NULL);
	  AddUDF(env,"x-set-foreground","v",3,3,";e;e;l",XSetForegroundFunction,"XSetForegroundFunction",NULL);

	  AddUDF(env,"x-load-query-font","be",2,2,";e;sy",XLoadQueryFontFunction,"XLoadQueryFontFunction",NULL);
	  AddUDF(env,"x-set-font","be",3,3,";e;e;e",XSetFontFunction,"XSetFontFunction",NULL);

	  AddUDF(env,"x-pending","l",1,1,";e",XPendingFunction,"XPendingFunction",NULL);
	  AddUDF(env,"x-peek-event","bm",1,1,";e",XPeekEventFunction,"XPeekEventFunction",NULL);
	  AddUDF(env,"x-next-event","bm",1,1,";e",XNextEventFunction,"XNextEventFunction",NULL);

	  AddUDF(env,"x-draw-arc","v",9,9,";e;l;e;l;l;l;l;l;l",XDrawArcFunction,"XDrawArcFunction",NULL);
	  AddUDF(env,"x-draw-line","v",7,7,";e;l;e;l;l;l;l",XDrawLineFunction,"XDrawLineFunction",NULL);
	  AddUDF(env,"x-draw-point","v",5,5,";e;l;e;l;l",XDrawPointFunction,"XDrawPointFunction",NULL);
	  AddUDF(env,"x-draw-rectangle","v",7,7,";e;l;e;l;l;l;l",XDrawRectangleFunction,"XDrawRectangleFunction",NULL);
	  AddUDF(env,"x-draw-string","v",6,6,";e;l;e;l;l;sy",XDrawStringFunction,"XDrawStringFunction",NULL);

	  AddUDF(env,"x-select-input","v",3,26,"y;e;l",XSelectInputFunction,"XSelectInputFunction",NULL);

	  AddUDF(env,"x-lookup-string","v",1,1,";e",XLookupStringFunction,"XLookupStringFunction",NULL);
  }
