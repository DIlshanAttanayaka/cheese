/*
 * Copyright © 2011 Lucas Baudin <xapantu@gmail.com>
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

#include "cheese-config.h"

#include <glib/gi18n.h>
#include "cheese-fileutil.h"

/* Test CheeseFileUtil */
static void
fileutil_burst (void)
{
    CheeseFileUtil *fileutil;
    gchar *first_path, *second_path, *third_path, *stub;
    gchar *real_second, *real_third;
    gchar **split;

    fileutil = cheese_fileutil_new ();
    g_assert (fileutil != NULL);

    first_path = cheese_fileutil_get_new_media_filename (fileutil,
        CHEESE_MEDIA_MODE_BURST);
    split = g_strsplit (first_path, "_1.jpg", -1);
    stub = g_strdup (split[0]);

    second_path = g_strdup_printf ("%s_2.jpg", stub);
    third_path = g_strdup_printf ("%s_3.jpg", stub);

    real_second = cheese_fileutil_get_new_media_filename (fileutil,
        CHEESE_MEDIA_MODE_BURST);
    /* Sleep for two seconds, and check to ensure that the original burst time
     * remains constant. */
    g_usleep (2000000);
    real_third = cheese_fileutil_get_new_media_filename (fileutil,
        CHEESE_MEDIA_MODE_BURST);

    g_assert_cmpstr (real_second, ==, second_path);
    g_assert_cmpstr (real_third, ==, third_path);

    g_strfreev (split);
    g_free (real_second);
    g_free (real_third);
    g_free (second_path);
    g_free (third_path);
    g_free (stub);
    g_object_unref (fileutil);
}

static void
fileutil_reset_burst (void)
{
    CheeseFileUtil *fileutil;
    gchar *first_path, *second_path;

    fileutil = cheese_fileutil_new ();
    g_assert (fileutil != NULL);

    first_path = cheese_fileutil_get_new_media_filename (fileutil,
        CHEESE_MEDIA_MODE_BURST);
    cheese_fileutil_reset_burst (fileutil);
    /* Sleep for two seconds to ensure a different burst time. */
    g_usleep (2000000);
    second_path = cheese_fileutil_get_new_media_filename (fileutil,
        CHEESE_MEDIA_MODE_BURST);

    g_assert (g_str_has_suffix (first_path, "_1.jpg"));
    g_assert (g_str_has_suffix (second_path, "_1.jpg"));
    g_assert_cmpstr (first_path, !=, second_path);

    g_free (first_path);
    g_free (second_path);
    g_object_unref (fileutil);
}

static void
fileutil_photo_path (void)
{
    CheeseFileUtil *fileutil;
    const gchar *path;

    fileutil = cheese_fileutil_new ();
    g_assert (fileutil != NULL);

    path = cheese_fileutil_get_photo_path (fileutil);
    g_assert (path != NULL);
    g_assert (g_file_test (path, G_FILE_TEST_EXISTS));
    g_assert (g_file_test (path, G_FILE_TEST_IS_DIR));

    g_object_unref (fileutil);
}

static void
fileutil_video_path (void)
{
    CheeseFileUtil *fileutil;
    const gchar *path;

    fileutil = cheese_fileutil_new ();
    g_assert (fileutil != NULL);

    path = cheese_fileutil_get_video_path (fileutil);
    g_assert (path != NULL);
    g_assert (g_file_test (path, G_FILE_TEST_EXISTS));
    g_assert (g_file_test (path, G_FILE_TEST_IS_DIR));

    g_object_unref (fileutil);
}

int main (int argc, gchar *argv[])
{
    g_thread_init (NULL);
    g_type_init ();

    g_test_init (&argc, &argv, NULL);

    if (g_test_slow ())
    {
        g_test_add_func ("/libcheese/fileutil/burst", fileutil_burst);
        g_test_add_func ("/libcheese/fileutil/reset_burst", fileutil_reset_burst);
    }
    g_test_add_func ("/libcheese/fileutil/photo_path", fileutil_photo_path);
    g_test_add_func ("/libcheese/fileutil/video_path", fileutil_video_path);

    return g_test_run ();
}
