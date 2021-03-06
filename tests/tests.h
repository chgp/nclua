/* tests.h -- Common declarations for tests.
   Copyright (C) 2013-2016 PUC-Rio/Laboratorio TeleMidia

This file is part of NCLua.

NCLua is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

NCLua is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
License for more details.

You should have received a copy of the GNU General Public License
along with NCLua.  If not, see <http://www.gnu.org/licenses/>.  */

#ifndef TESTS_H
#define TESTS_H

#include <config.h>
#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <cairo.h>
#include <glib.h>

#include "macros.h"

/* Ignore warnings about big strings in tests.  */
/* *INDENT-OFF* */
PRAGMA_DIAG_IGNORE (-Woverlength-strings)
/* *INDENT-ON* */

#include "luax-macros.h"

#include "nclua.h"
#include "ncluaw.h"

#ifdef __MINGW32__
# define INVALID_PATH "invalid:/invalid"
#else
# define INVALID_PATH "/invalid/invalid"
#endif

#define TEST_BEGIN TRACE_SEP (); STMT_BEGIN
#define TEST_END   STMT_END

#define ASSERT(cond)                                            \
  STMT_BEGIN                                                    \
  {                                                             \
   if (unlikely (!(cond)))                                      \
     {                                                          \
      fprintf (stderr, "%s:%d: ASSERTION FAILED!\n--> %s\n",    \
               __FILE__, __LINE__, STRINGIFY (cond));           \
      abort ();                                                 \
     }                                                          \
  }                                                             \
  STMT_END

#define ASSERT_LUA_DOSTRING(L, s) ASSERT (luaL_dostring (L, s) == 0)
#define ASSERT_LUA_GETTOP(L, i)   ASSERT (lua_gettop (L) == i)

/*-
 * Creates and returns a new Lua state with standard libraries opened.
 */
static ATTR_UNUSED inline lua_State *
LUA_NEWSTATE (void)
{
  lua_State *L;
  L = luaL_newstate ();
  luaL_openlibs (L);
  return L;
}

/*-
 * Outputs arguments to stdout prefixed with a time-stamp.
 */
static ATTR_UNUSED
ATTR_PRINTF_FORMAT (1, 2)
     void TRACE (const char *format, ...)
{
  static gint64 t0 = -1;
  gint64 dt;
  va_list args;

  if (unlikely (t0 < 0))
    {
      t0 = g_get_monotonic_time ();
    }
  dt = g_get_monotonic_time () - t0;

  va_start (args, format);
  printf ("[%gms]\t", ((double) dt) / 1000);
  vprintf (format, args);
  putc ('\n', stdout);
  fflush (stdout);
  va_end (args);
}

/*-
 * Outputs a numbered entry separator.
 */
static ATTR_UNUSED void
TRACE_SEP (void)
{
  static int n = 1;
  printf ("#%d\t", n++);
  printf ("-----------------------------------");
  printf ("-----------------------------------");
  putc ('\n', stdout);
  fflush (stdout);
}

#endif /* TESTS_H */
