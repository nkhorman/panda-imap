/* Generated by the NeXT Project Builder 
   NOTE: Do NOT change this file -- Project Builder maintains it.
*/

#import "EasyMail.h"

void main(int argc, char *argv[]) {

    [EasyMail new];
    if ([NXApp loadNibSection:"EasyMail.nib" owner:NXApp withNames:NO])
	    [NXApp run];
	    
    [NXApp free];
    exit(0);
}