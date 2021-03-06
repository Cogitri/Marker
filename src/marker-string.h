/*
 * marker-string.h
 *
 * Copyright (C) 2017 - 2018 Fabio Colacio
 *
 * Marker is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public License as
 * published by the Free Software Foundation; either version 3 of the
 * License, or (at your option) any later version.
 *
 * Marker is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with Marker; see the file LICENSE.md. If not,
 * see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __MARKER_STRING_H__
#define __MARKER_STRING_H__

#include <string.h>

int                  marker_string_ends_with                     (const char         *str,
                                                                  const char         *sub_str);
int		             marker_string_contains 	                 (const char	     *str,
                                     		                      const char         *sub_str);
char                *marker_string_alloc                         (const char         *str);
char                *marker_string_prepend                       (const char         *str,
                                                                  const char         *addition,
                                                                  char               *buffer,
                                                                  size_t              buffer_size);
char                *marker_string_append                        (const char         *str, 
                                                                  const char         *addition,
                                                                  char               *buffer,
                                                                  size_t              buffer_size);
int                  marker_string_buffer_set                    (const char         *str,
                                                                  char               *buffer,
                                                                  size_t              buffer_size);
char                *marker_string_escape                        (const char         *str);
char                *marker_string_filename_get_path             (const char         *filename);
char                *marker_string_filename_get_name             (const char         *filename);
char                *marker_string_filename_get_name_noext       (const char         *filename);

#endif
