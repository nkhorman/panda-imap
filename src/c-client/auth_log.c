/*
 * Program:	Login authenticator
 *
 * Author:	Mark Crispin
 *		Networks and Distributed Computing
 *		Computing & Communications
 *		University of Washington
 *		Administration Building, AG-44
 *		Seattle, WA  98195
 *		Internet: MRC@CAC.Washington.EDU
 *
 * Date:	5 December 1995
 * Last Edited:	24 October 2000
 * 
 * The IMAP toolkit provided in this Distribution is
 * Copyright 2000 University of Washington.
 * The full text of our legal notices is contained in the file called
 * CPYRIGHT, included with this Distribution.
 */

long auth_login_client (authchallenge_t challenger,authrespond_t responder,
			NETMBX *mb,void *stream,unsigned long *trial,
			char *user);
char *auth_login_server (authresponse_t responder,int argc,char *argv[]);

AUTHENTICATOR auth_log = {
  NIL,				/* not secure */
  "LOGIN",			/* authenticator name */
  NIL,				/* always valid */
  auth_login_client,		/* client method */
  auth_login_server,		/* server method */
  NIL				/* next authenticator */
};

#define PWD_USER "User Name"
#define PWD_PWD "Password"

/* Client authenticator
 * Accepts: challenger function
 *	    responder function
 *	    parsed network mailbox structure
 *	    stream argument for functions
 *	    pointer to current trial count
 *	    returned user name
 * Returns: T if success, NIL otherwise, number of trials incremented if retry
 */

long auth_login_client (authchallenge_t challenger,authrespond_t responder,
			NETMBX *mb,void *stream,unsigned long *trial,
			char *user)
{
  char pwd[MAILTMPLEN];
  void *challenge;
  unsigned long clen;
				/* get user name prompt */
  if (challenge = (*challenger) (stream,&clen)) {
    fs_give ((void **) &challenge);
				/* prompt user */
    mm_login (mb,user,pwd,*trial);
    if (!pwd[0]) {		/* user requested abort */
      (*responder) (stream,NIL,0);
      *trial = 0;		/* don't retry */
      return T;			/* will get a NO response back */
    }
				/* send user name */
    else if ((*responder) (stream,user,strlen (user)) &&
	     (challenge = (*challenger) (stream,&clen))) {
      fs_give ((void **) &challenge);
				/* send password */
      if ((*responder) (stream,pwd,strlen (pwd)) &&
	  !(challenge = (*challenger) (stream,&clen))) {
	++*trial;		/* can try again if necessary */
	return T;		/* check the authentication */
      }
    }
  }
  *trial = 0;			/* don't retry */
  return NIL;			/* failed */
}


/* Server authenticator
 * Accepts: responder function
 *	    argument count
 *	    argument vector
 * Returns: authenticated user name or NIL
 */

char *auth_login_server (authresponse_t responder,int argc,char *argv[])
{
  char *ret = NIL;
  char *user,*pass,*authuser;
  if (user = (*responder) (PWD_USER,sizeof (PWD_USER),NIL)) {
    if (pass = (*responder) (PWD_PWD,sizeof (PWD_PWD),NIL)) {
				/* delimit user from possible admin */
      if (authuser = strchr (user,'*')) *authuser++ = '\0';
      if (server_login (user,pass,authuser,argc,argv)) ret = myusername ();
      fs_give ((void **) &pass);
    }
    fs_give ((void **) &user);
  }
  return ret;
}
