# Makefile.am -- Template for generating Makefile via Automake.
# Copyright (C) 2013-2016 PUC-Rio/Laboratorio TeleMidia
#
# This file is part of NCLua.
#
# NCLua is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# NCLua is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
# or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
# License for more details.
#
# You should have received a copy of the GNU General Public License
# along with NCLua.  If not, see <http://www.gnu.org/licenses/>.

include $(top_srcdir)/build-aux/Makefile.am.common
include $(top_srcdir)/build-aux/Makefile.am.link

AM_CFLAGS= $(WERROR_CFLAGS) $(WARN_CFLAGS)

EXTRA_DIST= nclua.pc.in nclua.rc.in ncluaconf.h.in
DISTCLEANFILES+= nclua.pc nclua.rc ncluaconf.h

pkgconfigdir= $(libdir)/pkgconfig
pkgconfig_DATA= nclua.pc

include_HEADERS= nclua.h ncluaconf.h ncluaw.h
noinst_HEADERS= macros.h luax-macros.h
lib_LTLIBRARIES= libnclua.la

if OS_WIN32
export_symbols= -export-symbols $(builddir)/nclua.def
nclua_def_depedency= $(builddir)/nclua.def
nclua_win32_res= nclua-win32-res.o
nclua_win32_res_ldflag= -Wl,$(nclua_win32_res)
install_def_file_cmd= $(INSTALL)\
  $(builddir)/nclua.def $(DESTDIR)$(libdir)/nclua.def
uninstall_def_file_cmd= -rm $(DESTDIR)$(libdir)/nclua.def
endif

sed_nclua_def=\
  s/^NCLUA_API[ 	]\+[a-zA-Z0-9_]\+[ 	]*\*\?[ 	]*\(nclua[a-zA-Z0-9_]\+\).*/\1/p

CLEANFILES+= nclua-win32-res.o
nclua-win32-res.o: nclua.rc
	$(AM_V_GEN) $(WINDRES) nclua.rc $@

CLEANFILES+= nclua.def
nclua.def: nclua.h ncluaw.h
	$(AM_V_GEN) (echo EXPORTS;\
	cat nclua.h ncluaw.h | sed -n '$(sed_nclua_def)' | sort;\
	echo LIBRARY libnclua-$(NCLUA_LIBTOOL_CURRENT_MINUS_AGE)$(SOEXT)) >$@
install-def-file:
	$(install_def_file_cmd)
uninstall-def-file:
	$(uninstall_def_file_cmd)

CLEANFILES+= nclua.exp nclua.lib
nclua.lib: libnclua.la nclua.def
	$(AM_V_GEN) lib -machine:$(LIB_EXE_MACHINE_FLAG)\
	  -name:libnclua-$(NCLUA_LIBTOOL_CURRENT_MINUS_AGE)$(SOEXT)\
	  -def:$(builddir)/nclua.def -out:$@

if HAVE_MS_LIB
noinst_DATA= nclua.lib
install_ms_lib_cmd= $(INSTALL) nclua.lib $(DESTDIR)$(libdir)
uninstall_ms_lib_cmd= -rm $(DESTDIR)$(libdir)/nclua.lib
endif
install-ms-lib:
	$(install_ms_lib_cmd)
uninstall-ms-lib:
	$(uninstall_ms_lib_cmd)

install-data-local: install-def-file install-ms-lib
uninstall-local: uninstall-def-file uninstall-ms-lib

libnclua_la_DEPENDENCIES= $(include_HEADERS) $(noinst_HEADERS)\
  $(nclua_def_depedency) $(nclua_win32_res)
libnclua_la_CPPFLAGS= -DNCLUA_BUILDING
libnclua_la_CFLAGS= $(AM_CFLAGS) $(CFLAG_VISIBILITY) $(LUA_CFLAGS)
libnclua_la_LDFLAGS= -version-info $(NCLUA_LIBTOOL_STRING)\
  $(export_symbols) -no-undefined $(nclua_win32_res_ldflag)\
  $(LUA_LIBS)

libnclua_la_SOURCES=\
  luax-macros.h\
  macros.h\
  nclua.c\
  nclua.h\
  ncluaconf.h\
  ncluaw.c\
  ncluaw.h\
  $(NULL)

if WITH_NCLUA_GST
gstplugins_LTLIBRARIES= gstnclua.la
noinst_HEADERS+= gstx-macros.h
endif

gstnclua_la_DEPENDENCIES= $(lib_LTLIBRARIES) $(noinst_HEADERS)
gstnclua_la_CFLAGS= $(AM_CFLAGS) $(GLIB_CFLAGS)\
  $(GSTREAMER_CFLAGS) $(LUA_CFLAGS)
gstnclua_la_LDFLAGS= $(AM_LDFLAGS) -module $(LT_MODULE_LDFLAGS)\
  $(GLIB_LIBS) $(GSTREAMER_LIBS)
gstnclua_la_LIBADD= $(top_builddir)/lib/libnclua.la
gstnclua_la_SOURCES=\
  gstnclua.c\
  $(NULL)
