/***************************************************************************
Copyright (c) 2013-2016, The OpenBLAS Project
All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:
1. Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in
the documentation and/or other materials provided with the
distribution.
3. Neither the name of the OpenBLAS project nor the names of
its contributors may be used to endorse or promote products
derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE OPENBLAS PROJECT OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************/

/**************************************************************************************
* 2016/03/28 Werner Saar (wernsaar@googlemail.com)
* 	 BLASTEST 		: OK
* 	 CTEST			: OK
* 	 TEST			: OK
*	 LAPACK-TEST		: OK
**************************************************************************************/

#define HAVE_KERNEL_16 1
static void dasum_kernel_16( BLASLONG n, FLOAT *x, FLOAT *svec) __attribute__ ((noinline));

static void dasum_kernel_16( BLASLONG n, FLOAT *x, FLOAT *svec)
{


	BLASLONG i = n;
	BLASLONG o16 = 16;
	BLASLONG o32 = 32;
	BLASLONG o48 = 48;
	BLASLONG o64 = 64;
	BLASLONG o80 = 80;
	BLASLONG o96 = 96;
	BLASLONG o112 = 112;
	FLOAT *x1=x;
	BLASLONG pre = 384;

	__asm__  __volatile__
	(

	"dcbt		%2 , %4				    \n\t"

	"xxlxor		32,32,32			    \n\t"
	"xxlxor		33,33,33			    \n\t"
	"xxlxor		34,34,34			    \n\t"
	"xxlxor		35,35,35			    \n\t"
	"xxlxor		36,36,36			    \n\t"
	"xxlxor		37,37,37			    \n\t"
	"xxlxor		38,38,38			    \n\t"
	"xxlxor		39,39,39			    \n\t"

	"lxvd2x		40, 0, %2			    \n\t"
	"lxvd2x		41, %5, %2			    \n\t"
	"lxvd2x		42, %6, %2			    \n\t"
	"lxvd2x		43, %7, %2			    \n\t"
	"lxvd2x		44, %8, %2			    \n\t"
	"lxvd2x		45, %9, %2			    \n\t"
	"lxvd2x		46, %10, %2			    \n\t"
	"lxvd2x		47, %11, %2			    \n\t"

	"addi		%2, %2, 128			    \n\t"

	"addic.		%0 , %0	, -16  	 	             \n\t"
	"ble		2f		             	     \n\t"

	".align 5				            \n\t"
	"1:				                    \n\t"

	"dcbt		%2 , %4				    \n\t"

	"xvabsdp	48, 40				    \n\t"
	"xvabsdp	49, 41				    \n\t"
	"xvabsdp	50, 42				    \n\t"
	"xvabsdp	51, 43				    \n\t"

	"lxvd2x		40, 0, %2			    \n\t"
	"lxvd2x		41, %5, %2			    \n\t"

	"xvabsdp	52, 44				    \n\t"
	"xvabsdp	53, 45				    \n\t"

	"lxvd2x		42, %6, %2			    \n\t"
	"lxvd2x		43, %7, %2			    \n\t"

	"xvabsdp	54, 46				    \n\t"
	"xvabsdp	55, 47				    \n\t"

	"lxvd2x		44, %8, %2			    \n\t"
	"lxvd2x		45, %9, %2			    \n\t"

	"xvadddp	32, 32, 48		    \n\t"
	"xvadddp	33, 33, 49		    \n\t"

	"lxvd2x		46, %10, %2			    \n\t"
	"lxvd2x		47, %11, %2			    \n\t"

	"xvadddp	34, 34, 50		    \n\t"
	"xvadddp	35, 35, 51		    \n\t"
	"addi		%2, %2, 128			    \n\t"
	"xvadddp	36, 36, 52		    \n\t"
	"xvadddp	37, 37, 53		    \n\t"
	"addic.		%0 , %0	, -16  	 	             \n\t"
	"xvadddp	38, 38, 54		    \n\t"
	"xvadddp	39, 39, 55		    \n\t"

	"bgt		1b		             	     \n\t"

	"2:						     \n\t"


	"xvabsdp	48, 40				    \n\t"
	"xvabsdp	49, 41				    \n\t"
	"xvabsdp	50, 42				    \n\t"
	"xvabsdp	51, 43				    \n\t"
	"xvabsdp	52, 44				    \n\t"
	"xvabsdp	53, 45				    \n\t"
	"xvabsdp	54, 46				    \n\t"
	"xvabsdp	55, 47				    \n\t"

	"xvadddp	32, 32, 48		    \n\t"
	"xvadddp	33, 33, 49		    \n\t"
	"xvadddp	34, 34, 50		    \n\t"
	"xvadddp	35, 35, 51		    \n\t"
	"xvadddp	36, 36, 52		    \n\t"
	"xvadddp	37, 37, 53		    \n\t"
	"xvadddp	38, 38, 54		    \n\t"
	"xvadddp	39, 39, 55		    \n\t"

	"xvadddp	32, 32, 33		     \n\t"
	"xvadddp	34, 34, 35		     \n\t"
	"xvadddp	36, 36, 37		     \n\t"
	"xvadddp	38, 38, 39		     \n\t"

	"xvadddp	32, 32, 34		     \n\t"
	"xvadddp	36, 36, 38		     \n\t"

	"xvadddp	32, 32, 36		     \n\t"


	"stxvd2x	32, 0, %3		     \n\t"

	:
        : 
          "r" (i),	// 0	
	  "r" (n),  	// 1
          "r" (x1),     // 2
          "r" (svec),   // 3
          "r" (pre),    // 4
	  "r" (o16),	// 5
	  "r" (o32),	// 6
	  "r" (o48),    // 7
          "r" (o64),    // 8
          "r" (o80),    // 9
          "r" (o96),    // 10
          "r" (o112)   // 11
	: "cr0", "%0", "%2",  "memory"
	);

} 


