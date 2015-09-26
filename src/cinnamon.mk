# This file is part of GPaste.
#
# Copyright 2015 Marc-Antoine Perennou <Marc-Antoine@Perennou.com>
#
# GPaste is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# GPaste is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GPaste.  If not, see <http://www.gnu.org/licenses/>.

cinnamondir = $(datadir)/cinnamon/applets/GPaste@gnome-shell-extensions.gnome.org

cinnamon_applet_files = \
	src/cinnamon/applet.js \
	$(NULL)

if ENABLE_CINNAMON_APPLET
nodist_cinnamon_DATA = \
	$(gpaste_extension_files) \
	$(gpaste_extension_metadata_file)   \
	$(cinnamon_applet_files) \
	$(NULL)
endif

EXTRA_DIST += \
	$(cinnamon_applet_files) \
	$(NULL)
