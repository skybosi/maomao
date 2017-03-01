#ifndef __ZQ_GETOPT_H__
#define __ZQ_GETOPT_H__

/** Callers store zero here to inhibit the error message `getopt' prints
for unrecognized options.  */
extern int   opterr;      /* if error message should be printed */

/** Index in ARGV of the next element to be scanned.
This is used for communication to and from the caller
and for communication between successive calls to `getopt'.

On entry to `getopt', zero means this is the first call; initialize.

When `getopt' returns -1, this is the index of the first of the
non-option elements that the caller should itself scan.

Otherwise, `optind' communicates from one call to the next
how much of ARGV has been scanned so far.  */
extern int   optind;      /* index into parent argv vector */

/** Set to an option character which was unrecognized.  */
extern int   optopt;      /* character checked for validity */


extern int   optreset;    /* reset getopt */

/** For communication from `getopt' to the caller.
When `getopt' finds an option that takes an argument,
the argument value is returned here.
Also, when `ordering' is RETURN_IN_ORDER,
each non-option ARGV-element is returned here.  */
extern char *optarg;      /* argument associated with option */

enum
{
	no_argument=0,
	required_argument=1,
	optional_argument=2,
};

struct option 
{
	const char *name;
	int  has_arg;
	int *flag;
	int val;
};


/**The getopt function gets the next option argument from the argument list specified by the argv 
and argc arguments.  Normally these values come directly from the arguments received by main.

@n The options argument is a string that specifies the option characters that are valid for this program.
An option character in this string can be followed by a colon (:) to indicate that it takes a required 
argument.  If an option character is followed by two colons (::), its argument is optional; this is 
a GNU extension.

@n getopt has three ways to deal with options that follow non-options argv elements.  The special 
argument -- forces in all cases the end of option scanning.


@n The default is to permute the contents of argv while scanning it so that eventually all 
the non-options are at the end.  This allows options to be given in any order, even with programs 
that were not written to expect this.

@n If the options argument string begins with a hyphen (-), this is treated specially.  It 
permits arguments that are not options to be returned as if they were associated with option 
character \1.

@n POSIX demands the following behavior: The first non-option stops option processing.  
This mode is selected by either setting the environment variable POSIXLY_CORRECT or beginning 
the options argument string with a plus sign (+).

@n The getopt function returns the option character for the next command line option.  When no 
more option arguments are available, it returns -1.  There may still be more non-option arguments; 
you must compare the external variable optind against the argc parameter to check this.

@n If the option has an argument, getopt returns the argument by storing it in the variable optarg. 
You don't ordinarily need to copy the optarg string, since it is a pointer into the original argv 
array, not into a static area that might be overwritten.

@n If getopt finds an option character in argv that was not included in options, or a missing 
option argument, it returns ? and sets the external variable optopt to the actual option character.
If the first character of options is a colon (:), then getopt returns : instead of ? to indicate 
a missing option argument.  In addition, if the external variable opterr is nonzero (which is the 
default), getopt prints an error message.
*/
int getopt (int argc,char *const *argv,const char *optstring);

int getopt_long (int argc,char *const *argv,const char *options,const struct option *long_options,int *opt_index);

#endif //__ZQ_GETOPT_H__
