/*
 * Copyright (C) 2006-2009 Citrix Systems Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; version 2.1 only. with the special
 * exception on linking described in file LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 */

/*
  This stubs file retrieves the blkback statistics struct created by
  blktap3 under '/dev/shm/<vbd3-domid-devid>/statistics' *)
*/

#include <stdio.h>
#include <errno.h>

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/fail.h>
#include <caml/unixsupport.h>

struct stats {
	unsigned long long read_reqs_submitted;
	unsigned long long read_reqs_completed;
	unsigned long long read_sectors;
	unsigned long long read_total_ticks;
	unsigned long long write_reqs_submitted;
	unsigned long long write_reqs_completed;
	unsigned long long write_sectors;
	unsigned long long write_total_ticks;
};

CAMLprim value stub_get_blktap3_stats(value filename)
{

	CAMLparam1(filename);
	CAMLlocal1(stats);

	FILE *c_fd;
	struct stats c_stats;

	c_fd = fopen(String_val(filename), "rb");

	if (!c_fd) uerror("fopen", Nothing);
	if (fread(&c_stats, sizeof(struct stats), 1, c_fd) < 1) uerror("fread", Nothing);

	stats = caml_alloc_tuple(14);

	Store_field(stats, 0, caml_copy_int64((int64) c_stats.read_reqs_submitted));
	Store_field(stats, 1, caml_copy_int64((int64) c_stats.read_reqs_completed));
	Store_field(stats, 2, caml_copy_int64((int64) c_stats.read_sectors));
	Store_field(stats, 3, caml_copy_int64((int64) c_stats.read_total_ticks));
	Store_field(stats, 4, caml_copy_int64((int64) c_stats.write_reqs_submitted));
	Store_field(stats, 5, caml_copy_int64((int64) c_stats.write_reqs_completed));
	Store_field(stats, 6, caml_copy_int64((int64) c_stats.write_sectors));
	Store_field(stats, 7, caml_copy_int64((int64) c_stats.write_total_ticks));

	fclose(c_fd);

	CAMLreturn(stats);

}
