/*
 * Program:	NT Kerberos default key
 *
 * Author:	Mark Crispin
 *		Networks and Distributed Computing
 *		Computing & Communications
 *		University of Washington
 *		Administration Building, AG-44
 *		Seattle, WA  98195
 *		Internet: MRC@CAC.Washington.EDU
 *
 * Date:	28 April 1998
 * Last Edited:	24 October 2000
 * 
 * The IMAP toolkit provided in this Distribution is
 * Copyright 2000 University of Washington.
 * The full text of our legal notices is contained in the file called
 * CPYRIGHT, included with this Distribution.
 */

#include <stdio.h>
#include "mail.h"
#include "osdep.h"
#include "misc.h"
#define _MSDOS			/* work around osconf.h bug */
#include <osconf.h>
#undef _MSDOS

#define PROTOTYPE(x) x
#define KRB5_PROVIDE_PROTOTYPES
#include <gssapi/gssapi_generic.h>
#include <gssapi/gssapi_krb5.h>
#include <krb5.h>

static const gss_OID_desc oid[] = {
  {9,"\052\206\110\206\367\022\001\002\002"}
};

static const gss_OID_set_desc oidset[] = {
  {1,(gss_OID) oid}
};

const gss_OID_desc *const gss_mech_krb5 = oid;
const gss_OID_set_desc * const gss_mech_set_krb5 = oidset;


char *krb5_defkeyname = 0;

void setkrbdefkey (void)
{
  char tmp[MAILTMPLEN],windir[256];
  int i = GetWindowsDirectory (windir,254);
  windir[i] = '\0';
  sprintf (tmp,DEFAULT_KEYTAB_NAME,windir);
  krb5_defkeyname = cpystr (tmp);
}
