/*
 * Copyright (C) 2007 Copyright (C) 2007 daniel g. siegel <dgsiegel@gmail.com>
 *
 * Licensed under the GNU General Public License Version 2
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __CHEESE_H__
#define __CHEESE_H__

#include <glib.h>
#include <gtk/gtk.h>

//FIXME: provide option to choose the folder
#define PHOTO_FOLDER_DEFAULT  	  "images/"
#define PHOTO_NAME_DEFAULT	      "Picture"
#define PHOTO_NAME_SUFFIX_DEFAULT ".jpg"
#define VIDEO_FOLDER_DEFAULT  	  "videos/"
#define VIDEO_NAME_DEFAULT	      "Video"
#define VIDEO_NAME_SUFFIX_DEFAULT ".ogg"

void on_cheese_window_close_cb (GtkWidget *, gpointer);

#endif /* __CHEESE_H__ */
