/***************************************************************/
/*                                                             */
/*      PROJECT NAME :  RA8835_ex                              */
/*      FILE         :  RA8835_ex.c                            */
/*      DESCRIPTION  :  Main Program                           */
/*                                                             */
/*      This file was generated by e2 studio.                  */
/*                                                             */
/***************************************************************/


#include "iodefine.h"

#ifdef CPPAPP
//Initialize global constructors
extern void __main()
{
  static int initialized;
  if (! initialized)
    {
      typedef void (*pfunc) ();
      extern pfunc __ctors[];
      extern pfunc __ctors_end[];
      pfunc *p;

      initialized = 1;
      for (p = __ctors_end; p > __ctors; )
    (*--p) ();

    }
}
#endif 

int main(void) {

    while(1) {
	// TODO: add application code here
    }
return 0;
}