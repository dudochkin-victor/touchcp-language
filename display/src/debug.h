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
/******************************************************************************
 * The first part can be loaded again and again.
 */
#ifdef DEBUG
#  ifndef WARNING
#    define WARNING
#  endif
#endif

#undef PRINT_DEBUG
#if !defined(DEBUG) || defined(PUBLIC_RELEASE)
#  define PRINT_DEBUG(...) {/* nop */}
#else
#  define PRINT_DEBUG(...) \
       message_print_debug(__PRETTY_FUNCTION__, __VA_ARGS__)
#endif

#undef PRINT_WARNING
#if !defined(WARNING) || defined(PUBLIC_RELEASE)
#  define PRINT_WARNING(...) {/* nop */}
#else
#  define PRINT_WARNING(...) \
       message_print_warning(__PRETTY_FUNCTION__, __VA_ARGS__)
#endif

/******************************************************************************
 * This second part will be loaded only once.
 */
#ifndef DEBUG_H
#define DEBUG_H

#define STR(str) str.toLatin1().constData()
void
message_print_debug (
		const char *function,
		const char *message,
		...);

void
message_print_warning (
		const char *function,
		const char *message,
		...);


#ifndef DEBUG
#define NO_RUNTIME_BACKTRACE
#else
/* remove this if you dont mind long messages on terminal */
#define NO_RUNTIME_BACKTRACE
#endif

#ifndef RUNTIME_BACKTRACE_VERBOSE_LEVEL
/* The higher value causes less debug messages. */
#define RUNTIME_BACKTRACE_VERBOSE_LEVEL 1
#endif

/* big hack :( */
void _nothing();
#define NOTHING _nothing()

#ifndef NO_RUNTIME_BACKTRACE

void _runtimeBacktrace(
        bool enter, /* TRUE - enter; FALSE - leave */
        void *ptr,
        const char *func_name);

#define ENTER_STATIC_FUNCTION_VERBOSE(v) (RUNTIME_BACKTRACE_VERBOSE_LEVEL <= v) ? ENTER_STATIC_FUNCTION() : NOTHING ;
#define LEAVE_STATIC_FUNCTION_VERBOSE(v) (RUNTIME_BACKTRACE_VERBOSE_LEVEL <= v) ? LEAVE_STATIC_FUNCTION() : NOTHING ;
#define ENTER_FUNCTION_VERBOSE(v) (RUNTIME_BACKTRACE_VERBOSE_LEVEL <= v) ? ENTER_FUNCTION() : NOTHING ;
#define LEAVE_FUNCTION_VERBOSE(v) (RUNTIME_BACKTRACE_VERBOSE_LEVEL <= v) ? LEAVE_FUNCTION() : NOTHING ;

#define ENTER_STATIC_FUNCTION() _runtimeBacktrace(true, (void*)(0), __PRETTY_FUNCTION__)
#define LEAVE_STATIC_FUNCTION() _runtimeBacktrace(false, (void*)(0),  __PRETTY_FUNCTION__)
#define ENTER_FUNCTION() _runtimeBacktrace(true, (void*)(this), __PRETTY_FUNCTION__)
#define LEAVE_FUNCTION() _runtimeBacktrace(false, (void*)(this),  __PRETTY_FUNCTION__)

#else

#define ENTER_STATIC_FUNCTION_VERBOSE(v) NOTHING
#define LEAVE_STATIC_FUNCTION_VERBOSE(v) NOTHING
#define ENTER_FUNCTION_VERBOSE(v) NOTHING
#define LEAVE_FUNCTION_VERBOSE(v) NOTHING

#define ENTER_STATIC_FUNCTION() NOTHING
#define LEAVE_STATIC_FUNCTION() NOTHING
#define ENTER_FUNCTION() NOTHING
#define LEAVE_FUNCTION() NOTHING

#endif


#endif

