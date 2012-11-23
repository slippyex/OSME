/*
 *                      sc68 - ice file loader
 *         Copyright (C) 2001-2003 Benjamin Gerard <ben@sashipa.com>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by the
 *  Free Software Foundation; either version 2 of the License, or (at your
 *  option) any later version.
 *
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 */

#include <string.h>
#include "file68/ice68.h"
//#include "file68/debugmsg68.h"
//#include "file68/error68.h"
#include "file68/alloc68.h"
#include "unice68/unice68.h"

int ice_is_magic(const void * buffer)
{
  return unice68_get_depacked_size(buffer, 0) > 0;
}

void *ice_load(istream_t *is, int *ulen)
{
  char header[12], *inbuf = 0, * outbuf = 0;
  int dsize, csize;
  const char * fname;

  fname = istream_filename(is);

  if (istream_read(is,header,12) != 12) {
//    SC68error_add("ice_load(%s) : no header", fname);
    goto error;
  }

  csize = 0;
  dsize = unice68_get_depacked_size(header, &csize);

  if (dsize < 0) {
//    SC68error_add("ice_load(%s) : not ICE!", fname);
    goto error;
  }

  inbuf = (char*)SC68alloc(csize + 12);

  if (!inbuf) {
//    SC68error_add("ice_load(%s) : alloc input buffer failed", fname);
    goto error;
  }

  memcpy(inbuf,header,12);
  if (istream_read(is,inbuf+12,csize) != csize) {
//    SC68error_add("ice_load(%s) : read failed", fname);
    goto error;
  }

  outbuf = (char*)SC68alloc(dsize);

  if (!outbuf) {
//    SC68error_add("ice_load(%s) : alloc output buffer failed", fname);
    goto error;
  }

  if (!unice68_depacker(outbuf, inbuf)) {
    goto success;
  }
  
 error:

  SC68free(outbuf);
  outbuf = 0;
  dsize = 0;
 success:
  SC68free(inbuf);
  if (ulen) {
    *ulen = dsize;
  }
  return outbuf;
}
