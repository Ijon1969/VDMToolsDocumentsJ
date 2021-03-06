
/* 
 *  M_APM  -  calc.c
 *
 *  Copyright (C) 1999, 2000   Michael C. Ring
 *
 *  Permission to use, copy, and distribute this software and its
 *  documentation for any purpose with or without fee is hereby granted, 
 *  provided that the above copyright notice appear in all copies and 
 *  that both that copyright notice and this permission notice appear 
 *  in supporting documentation.
 *
 *  Permission to modify the software is granted, but not the right to
 *  distribute the modified code.  Modifications are to be distributed 
 *  as patches to released version.
 *  
 *  This software is provided "as is" without express or implied warranty.
 */

/*
 *      $Id: calc.c,v 1.1.1.1 2001/10/04 13:02:56 paulm Exp $
 *
 *      RPN Calculator : demo of the MAPM math library
 *
 *      $Log: calc.c,v $
 *      Revision 1.1.1.1  2001/10/04 13:02:56  paulm
 *      Import of dir
 *
 *      Revision 1.13  2000/08/04 00:37:39  mike
 *      remove unneeded int from calc_square
 *
 *      Revision 1.12  2000/08/03 18:05:12  mike
 *      add help for new memory commands
 *
 *      Revision 1.11  2000/08/03 17:56:38  mike
 *      add memory capability
 *
 *      Revision 1.10  2000/07/11 23:20:19  mike
 *      calculate 'pi' using the new AGM library function
 *
 *      Revision 1.9  2000/05/05 20:21:14  mike
 *      compute PI on the fly if more than 115 decimal
 *      places are asked for.
 *
 *      Revision 1.8  2000/04/03 18:51:25  mike
 *      added operators cube root and hyperbolic sin, cos, tan
 *      with their inverses
 *
 *      Revision 1.7  2000/02/03 22:43:03  mike
 *      calculate a few extra decimal places on the
 *      intermediate results so all answers on the
 *      final output stay consistent
 *
 *      Revision 1.6  1999/07/05 15:06:04  mike
 *      added DUP operator
 *
 *      Revision 1.5  1999/06/01 02:35:00  mike
 *      fix isdigit call with cast
 *
 *      Revision 1.4  1999/05/28 21:17:11  mike
 *      break up usage into 2 printf so dos compile doesnt choke
 *
 *      Revision 1.3  1999/05/19 02:29:44  mike
 *      added version of calc to usage line
 *
 *      Revision 1.2  1999/05/19 02:18:33  mike
 *      added check for stack under-flow
 *
 *      Revision 1.1  1999/05/19 02:01:02  mike
 *      Initial revision
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "m_apm.h"

/*  prototypes for functions in this file  */

void	 calc_reciprocal(M_APM, int, M_APM);
void	 calc_square(M_APM, M_APM);
void	 calc_pi(M_APM, int);
char 	 *lowercase(char *);

char	 *out_buffer;
char	 in_buffer[8192];

#define  STACK_SIZE 96

M_APM    calc_stack_data[STACK_SIZE];
M_APM    memory_data[36];

#define NUM_OPERATOR_ENTRIES 35          /* number of operators */

/* calling convention for various MAPM library functions ... */

#define	MMM     0x0A01                   /*  ( MAPM, MAPM, MAPM )       */
#define	MiMM    0x0A02                   /*  ( MAPM, int, MAPM, MAPM )  */
#define	MiM     0x0A03                   /*  ( MAPM, int, MAPM )        */
#define	Mi      0x0A04                   /*  ( MAPM, int )              */
#define	MM      0x0A05                   /*  ( MAPM, MAPM )             */
#define	MXY     0x0A80                   /*  special for x <> y         */
#define	MDUP    0x0A81                   /*  special for dup            */
#define	M_END   0x0AFF                   /*  end of table flag          */

struct  opstr {
  char  operator[16];      
  int	calling_convention;
  void	(*funcname)();
};

struct  opstr  operator_lookup[NUM_OPERATOR_ENTRIES] = {  
   {  "+",    MMM,     m_apm_add,             /*   0   */  },
   {  "-",    MMM,     m_apm_subtract,        /*   1   */  },
   {  "*",    MMM,     m_apm_multiply,        /*   2   */  },
   {  "x",    MMM,     m_apm_multiply,        /*   3   */  },
   {  "/",    MiMM,    m_apm_divide,          /*   4   */  },
   {  "\\",   MMM,     m_apm_integer_divide,  /*   5   */  },
   {  "i",    MMM,     m_apm_integer_divide,  /*   6   */  },
   {  "!",    MM,      m_apm_factorial,       /*   7   */  },
   {  "s",    MiM,     m_apm_sin,             /*   8   */  },
   {  "c",    MiM,     m_apm_cos,             /*   9   */  },
   {  "t",    MiM,     m_apm_tan,             /*  10   */  },
   {  "q",    MiM,     m_apm_sqrt,            /*  11   */  },
   {  "as",   MiM,     m_apm_asin,            /*  12   */  },
   {  "ac",   MiM,     m_apm_acos,            /*  13   */  },
   {  "at",   MiM,     m_apm_atan,            /*  14   */  },
   {  "at2",  MiMM,    m_apm_atan2,           /*  15   */  },
   {  "lg",   MiM,     m_apm_log,             /*  16   */  },
   {  "lg10", MiM,     m_apm_log10,           /*  17   */  },
   {  "e",    MiM,     m_apm_exp,             /*  18   */  },
   {  "p",    MiMM,    m_apm_pow,             /*  19   */  },
   {  "h",    MM,      m_apm_negate,          /*  20   */  },
   {  "n",    MM,      m_apm_negate,          /*  21   */  },
   {  "xy",   MXY,     NULL,                  /*  22   */  },
   {  "d",    MDUP,    NULL,                  /*  23   */  },
   {  "r",    MiM,     calc_reciprocal,       /*  24   */  },
   {  "x2",   MM,      calc_square,           /*  25   */  },
   {  "pi",   Mi,      calc_pi,               /*  26   */  },
   {  "hs",   MiM,     m_apm_sinh,            /*  27   */  },
   {  "hc",   MiM,     m_apm_cosh,            /*  28   */  },
   {  "ht",   MiM,     m_apm_tanh,            /*  29   */  },
   {  "has",  MiM,     m_apm_asinh,           /*  30   */  },
   {  "hac",  MiM,     m_apm_acosh,           /*  31   */  },
   {  "hat",  MiM,     m_apm_atanh,           /*  32   */  },
   {  "b",    MiM,     m_apm_cbrt,            /*  33   */  },
   {  "ZZZ",  M_END,   NULL                   /*  34   */  }
 }; 


int main(argc, argv)
int argc;  char *argv[];
{
void	 (*fp)();
char     ch0, ch1, *cp;
int      ii, ilow, stack_pointer, decimal_places, k,
	 index, len, memory_ref[36];
M_APM    apmtmp;
M_APM    arg1;   
M_APM    arg2;

if (argc < 2)
  {
   fprintf(stderr,"calc [-d##] <numbers,operators>\t\t\t\t[Version 1.6]\n");
   fprintf(stderr,"      -d : specify decimal places, default = 30\n\n");

   fprintf(stderr,
"operators :  + : add                           s : sin\n\
             - : subtract                      c : cos\n\
             x : multiply (*)                  t : tan\n\
             / : divide                        q : sqrt\n\
             \\ : integer divide (i)           as : arc-sin\n\
             ! : factorial                    ac : arc-cos\n");

   fprintf(stderr,
"            x2 : x ^ 2                        at : arc-tan\n\
             r : 1 / x                       at2 : arc-tan2 (y,x)\n\
            lg : log                           e : e ^ x\n\
          lg10 : log10                         p : y ^ x\n\
            xy : x<>y (exchange x,y)           n : +/- (negate (h))\n\
");

   fprintf(stderr,
"            hs : sinh                        has : arc-sinh\n\
            hc : cosh                        hac : arc-cosh\n\
            ht : tanh                        hat : arc-tanh\n\
             b : cube root                     d : dup (HP-Enter)\n\
            s# : save memory, # = 0-9,a-z     r# : recall memory, # = 0-9,a-z\n\
            pi : 3.14159.. \n\
");


   exit(2);
  }

/* leave arg1, arg2 uninitialized on purpose */
/*                                           */
/* analagous to  :   int  *arg1, buffer[NN]; */
/*                   arg1 = buffer;          */

apmtmp = m_apm_init();

for (k=0; k < STACK_SIZE; k++)
  calc_stack_data[k] = m_apm_init();

for (k=0; k < 36; k++)
  {
   memory_data[k] = m_apm_init();
   memory_ref[k]  = 0;
  }

/*
 *   normally, stack_pointer would be 0 and we would 
 *   check all operations on it to verify it never 
 *   went < 0. since this is a just demo program and not
 *   a 'real' application, we will just warn the user
 *   at the end if a potential stack underflow occurred.
 *   we can likely force a run-time core dump with 16 
 *   math operations with no numbers to work with :
 *   i.e. -> calc + + + + ... 16 times
 */

stack_pointer  = 16;
decimal_places = 30;
ilow           = 1;

strcpy(in_buffer, argv[1]);
lowercase(in_buffer);
if ((cp = strstr(in_buffer,"-d")) != NULL)
  {
   ilow++;
   cp += 2;
   decimal_places = atoi(cp);
   if (decimal_places < 2)
     decimal_places = 2;
  }

for (ii=ilow; ii < argc; ii++)
  {
   strcpy(in_buffer, argv[ii]);
   lowercase(in_buffer);
   k = 0;

   while (1)
     {        
      /*
       *  if the first char is a digit, we assume this is a number 
       */

      if (k == 0)
        {
         if (isdigit((int)*in_buffer))
           {
	    stack_pointer++;
	    m_apm_set_string(calc_stack_data[stack_pointer], in_buffer);
	    break;
	   }
	}

      /* 
       *  at end of operator table ??    if so, see if we have
       *  a memory operator. if not, assume this is a number.
       */

      if (operator_lookup[k].calling_convention == M_END)
        {
	 /*
	  *  see if we have a 'memory' operator
	  */

	 len = strlen(in_buffer);
	 ch0 = in_buffer[0];
	 ch1 = in_buffer[1];

	 if (ch0 == 's' || ch0 == 'r')
	   {
	    /*  s[0-9,a-z]   or  r[0-9,a-z]  */

            index = -1;
      
            if (ch1 >= '0' && ch1 <= '9')
              index = (int)ch1 - '0';
      
            if (ch1 >= 'a' && ch1 <= 'z')
              index = (int)ch1 + 10 - 'a';

            if (len == 2 && index >= 0)
	      {
	       if (ch0 == 'r')     /* re-call memory */
	         {
		  if (memory_ref[index] != 0)
		    {
	             stack_pointer++;
	             arg1 = memory_data[index];
	             m_apm_copy(calc_stack_data[stack_pointer], arg1);
		    }
		  else
		    {
               fprintf(stderr,
	"Warning!, Using un-initialized memory location : \'%c\'\n",ch1);
		    }
		 }
               else                /* store memory   */
	         {
	          arg1 = memory_data[index];
	          m_apm_copy(arg1, calc_stack_data[stack_pointer]);
		  memory_ref[index] = 1;
		 }
	      }
            else
	      {
               fprintf(stderr,
	"Error!, Memory command error : Syntax  s[0-9,a-z] or r[0-9,a-z]\n");
	       exit(4);
              }
	   }
         else     /* assume this is a number */
	   {
	    stack_pointer++;
	    m_apm_set_string(calc_stack_data[stack_pointer], in_buffer);
	   }

	 break;
	}

      if (strcmp(operator_lookup[k].operator, in_buffer) == 0)
        {
         /*
          *  we found an operator, so do it 
          */

	 if (operator_lookup[k].calling_convention == Mi)
	   {
            fp = operator_lookup[k].funcname;
            (*fp)(apmtmp, (decimal_places + 6));
	    m_apm_copy(calc_stack_data[++stack_pointer], apmtmp);
	   }
	
	 if (operator_lookup[k].calling_convention == MXY)
	   {
	    arg2 = calc_stack_data[stack_pointer - 1];
	    arg1 = calc_stack_data[stack_pointer];

	    m_apm_copy(apmtmp, arg1);
	    m_apm_copy(arg1, arg2);
	    m_apm_copy(arg2, apmtmp);
	   }
	
	 if (operator_lookup[k].calling_convention == MDUP)
	   {
	    arg1 = calc_stack_data[stack_pointer];
	    m_apm_copy(calc_stack_data[++stack_pointer], arg1);
	   }
	
	 if (operator_lookup[k].calling_convention == MMM)
	   {
            fp   = operator_lookup[k].funcname;
	    arg2 = calc_stack_data[stack_pointer];
	    arg1 = calc_stack_data[--stack_pointer];
            (*fp)(apmtmp, arg1, arg2);
	    m_apm_copy(arg1, apmtmp);
	   }
	
	 if (operator_lookup[k].calling_convention == MiMM)
	   {
            fp   = operator_lookup[k].funcname;
	    arg2 = calc_stack_data[stack_pointer];
	    arg1 = calc_stack_data[--stack_pointer];
            (*fp)(apmtmp, (decimal_places + 6), arg1, arg2);
	    m_apm_copy(arg1, apmtmp);
	   }
	
	 if (operator_lookup[k].calling_convention == MM)
	   {
            fp   = operator_lookup[k].funcname;
	    arg1 = calc_stack_data[stack_pointer];
            (*fp)(apmtmp, arg1);
	    m_apm_copy(arg1, apmtmp);
	   }
	
	 if (operator_lookup[k].calling_convention == MiM)
	   {
            fp   = operator_lookup[k].funcname;
	    arg1 = calc_stack_data[stack_pointer];
            (*fp)(apmtmp, (decimal_places + 6), arg1);
	    m_apm_copy(arg1, apmtmp);
	   }

	 break;
	}

      k++;
     }
  }

if ((out_buffer = (char *)malloc(decimal_places + 16)) == NULL)
  {
   fprintf(stderr,"out of memory\n");
   exit(6);
  }

if (stack_pointer <= 16)
  {
   fprintf(stderr,"Warning!, stack under-flow, result is unreliable\n");
  }

arg1 = calc_stack_data[stack_pointer];
m_apm_round(apmtmp, decimal_places, arg1);
m_apm_to_string(out_buffer, -1, apmtmp);
printf("%s\n",out_buffer);

for (k=0; k < STACK_SIZE; k++)
  m_apm_free(calc_stack_data[k]);

for (k=0; k < 36; k++)
  m_apm_free(memory_data[k]);

m_apm_free(apmtmp);
free(out_buffer);

exit(0);
}
/***********************************************************************/
void	 calc_reciprocal(rr, p, xx)
M_APM	 rr, xx;
int	 p;
{
m_apm_divide(rr, p, MM_One, xx);
}
/***********************************************************************/
void	 calc_square(rr, xx)
M_APM	 rr, xx;
{
m_apm_multiply(rr, xx, xx);
}
/***********************************************************************/
void	 calc_pi(rr, p)
M_APM	 rr;
int	 p;
{
M_APM    aa;

if (p > 115)
  {
   aa = m_apm_init();

   /* compute : PI = 2 * asin(1) */

   m_apm_asin(aa, (p + 2), MM_One);
   m_apm_add(rr, aa, aa);

   m_apm_free(aa);
  }
else
  m_apm_round(rr, p, MM_PI);
}
/***********************************************************************/
char	*lowercase(s)
char    *s;
{
register char *p;

p = s;
while (1)
  {
   if (*p >= 'A' && *p <= 'Z')  *p += 'a' - 'A';
   if (*p++ == 0)  break;
  }
return(s);
}
/***********************************************************************/
