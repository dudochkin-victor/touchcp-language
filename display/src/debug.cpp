/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of duicontrolpanel-languageapplet.
**
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/
/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <QString>
#include <QTime>
#include <QStack>
#include <QMultiMap>

#include "debug.h"

#ifdef NO_COLOR
#define VT_GRAPHICS_MODE(code) ""
#else
#define VT_GRAPHICS_MODE(code) "\e\["#code"m"
#endif

#define VT_TA_ALLOFF        VT_GRAPHICS_MODE(0)
#define VT_TA_BOLD          VT_GRAPHICS_MODE(1)
#define VT_TA_UNDERSCORE    VT_GRAPHICS_MODE(4)
#define VT_TA_BLINK         VT_GRAPHICS_MODE(5)
#define VT_TA_REVERSE       VT_GRAPHICS_MODE(7)
#define VT_TA_CONCEALED     VT_GRAPHICS_MODE(8)

#define VT_FG_BLACK         VT_GRAPHICS_MODE(30)
#define VT_FG_RED           VT_GRAPHICS_MODE(31)
#define VT_FG_GREEN         VT_GRAPHICS_MODE(32)
#define VT_FG_YELLOW        VT_GRAPHICS_MODE(33)
#define VT_FG_BLUE          VT_GRAPHICS_MODE(34)
#define VT_FG_MAGENTA       VT_GRAPHICS_MODE(35)
#define VT_FG_CYAN          VT_GRAPHICS_MODE(36)
#define VT_FG_WHITE         VT_GRAPHICS_MODE(37)

#define VT_BG_BLACK         VT_GRAPHICS_MODE(40)
#define VT_BG_RED           VT_GRAPHICS_MODE(41)
#define VT_BG_GREEN         VT_GRAPHICS_MODE(42)
#define VT_BG_YELLOW        VT_GRAPHICS_MODE(43)
#define VT_BG_BLUE          VT_GRAPHICS_MODE(44)
#define VT_BG_MAGENTA       VT_GRAPHICS_MODE(45)
#define VT_BG_CYAN          VT_GRAPHICS_MODE(46)
#define VT_BG_WHITE         VT_GRAPHICS_MODE(47)

void _nothing(){}

#ifndef NO_RUNTIME_BACKTRACE
#ifndef APP_NAME
#error Please define APP_NAME on command line to be used as prefix for function call debug messages.
#endif



void _runtimeBacktrace(
        bool enter, /* true - enter; false - leave */
        void *ptr,
        const char *funcName)
{
    static QTime timer;
    static bool started = false;
    static QString inPrefix, outPrefix;
    static QStack<int> timeStack;

    if(!started){
        timer.start();
        started = true;
    }

    if(enter) {
        timeStack.push(timer.elapsed());
        inPrefix.append("> ");
        outPrefix.append("< ");
        fprintf(stderr, "%s%16s%s %12p %s%12s %s%s%s %s\n",
                VT_FG_YELLOW, APP_NAME, VT_TA_ALLOFF,
                ptr,
                VT_FG_BLUE, qPrintable(QTime::currentTime().toString("HH:mm:ss.zzz")),
                VT_FG_YELLOW, qPrintable(inPrefix), VT_TA_ALLOFF,
                funcName);
        return;
    }

    int pop = timeStack.isEmpty() ? 0 : timeStack.pop();
    fprintf(stderr, "%s%16s%s %12p %s%11.3fs %s%s%s %s\n",
            VT_FG_YELLOW, APP_NAME, VT_TA_ALLOFF,
            ptr,
            VT_FG_MAGENTA, ((timer.elapsed()-pop) / 1000.0),
            VT_FG_YELLOW, qPrintable(outPrefix), VT_TA_ALLOFF,
            funcName);
    inPrefix.chop(2);
    outPrefix.chop(2);
}
#endif

void
message_print_debug (
		const char *function,
		const char *format,
		...)
{
	va_list args;
	
	va_start (args, format);
	printf("\033[1;32m%s()\033[0;39m: ", function);
	vprintf(format, args);
	va_end (args);
	putchar('\n');
	fflush(stdout);
}

void
message_print_warning (
		const char *function,
		const char *format,
		...)
{
	va_list args;
	
	va_start (args, format);
	printf("\033[1;33m%s()\033[0;39m: ", function);
	vprintf(format, args);
	va_end (args);
	putchar('\n');
	fflush(stdout);
}
