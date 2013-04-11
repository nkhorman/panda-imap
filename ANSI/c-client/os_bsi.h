/*
 * Program:	Operating-system dependent routines -- BSDI BSD/386 version
 *
 * Author:       Mike Santangelo (based on NeXT port by Mark Crispin)
 *               UMCEES/CBL Computer and Network Systems Department
 *               Solomons, Maryland
 *               Internet: mike@cbl.umd.edu
 *
 * Date:         5 March 1993
 * Last Edited:  16 August 1993
 *
 * Copyright 1993 by the University of Washington
 *
 *  Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted, provided
 * that the above copyright notice appears in all copies and that both the
 * above copyright notice and this permission notice appear in supporting
 * documentation, and that the name of the University of Washington not be
 * used in advertising or publicity pertaining to distribution of the software
 * without specific, written prior permission.  This software is made available
 * "as is", and
 * THE UNIVERSITY OF WASHINGTON DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED,
 * WITH REGARD TO THIS SOFTWARE, INCLUDING WITHOUT LIMITATION ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, AND IN
 * NO EVENT SHALL THE UNIVERSITY OF WASHINGTON BE LIABLE FOR ANY SPECIAL,
 * INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE) OR STRICT LIABILITY, ARISING OUT OF OR IN CONNECTION
 * WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

extern int h_errno;

#define MAILFILE "/var/mail/%s"
#define ACTIVEFILE "/usr/lib/news/active"
#define NEWSSPOOL "/usr/spool/news"
#define NEWSRC strcat (strcpy (tmp,myhomedir ()),"/.newsrc")

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/uio.h>		/* needed for writev() prototypes */

/* Dummy definition overridden by TCP routines */

#ifndef TCPSTREAM
#define TCPSTREAM void
#endif


/* Function prototypes */

void rfc822_date (char *date);
void *fs_get (size_t size);
void fs_resize (void **block,size_t size);
void fs_give (void **block);
void fatal (char *string);
unsigned long strcrlfcpy (char **dst,unsigned long *dstl,char *src,
			  unsigned long srcl);
unsigned long strcrlflen (STRING *s);
long server_login (char *user,char *pass,char **home,int argc,char *argv[]);
char *myusername ();
char *myhomedir ();
char *lockname (char *tmp,char *fname);
TCPSTREAM *tcp_open (char *host,int port);
TCPSTREAM *tcp_aopen (char *host,char *service);
char *tcp_getline (TCPSTREAM *stream);
long tcp_getbuffer (TCPSTREAM *stream,unsigned long size,char *buffer);
long tcp_getdata (TCPSTREAM *stream);
long tcp_soutr (TCPSTREAM *stream,char *string);
long tcp_sout (TCPSTREAM *stream,char *string,unsigned long size);
void tcp_close (TCPSTREAM *stream);
char *tcp_host (TCPSTREAM *stream);
char *tcp_localhost (TCPSTREAM *stream);