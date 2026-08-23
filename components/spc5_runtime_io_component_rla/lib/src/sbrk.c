/***********************************************************************************
*
* Copyright © 2017-2019 STMicroelectronics - All Rights Reserved
*
* This software is licensed under SLA0098 terms that can be found in the
* DM00779817_1_0.pdf file in the licenses directory of this software product.
*
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED,
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
************************************************************************************/

/*lint -save -e* */
#include <stdio.h>
#include <errno.h>
#include <stdint.h>

/*
 * sbrk()  increments the program's data space by increment bytes.
 * Calling sbrk() with an increment of 0 can be used to find the
 * current location of the program break.
 *
 *  On  success,  sbrk()  returns  the previous program break.
 *  If the break was increased, then this value is a pointer
 *  to the start of the newly allocated memory.
 *
 *  On error, (void *) -1 is returned, and errno is set  to ENOMEM.
 */

#ifndef __ghs__
void *sbrk(intptr_t increment)
{
	/*
	 * Using external symbols:
	 *   __heap_base__ : is placed at the beginning of the heap chunk
	 *   __heap_end__  : is placed at the end of available heap chunk
	 *
	 * For definition of __heap_base__ and __heap_end__,
	 * see linker script file.
	 *
	 * Limitation:
	 *   multiple heap chunks not handled
	 *   re-entrance (multi-threading) not handled
	 */
	extern uint8_t __heap_base__;
	extern uint8_t __heap_end__;

	static uint8_t *heap_base = &__heap_base__;
	uint8_t *prev_head_base;;

	prev_head_base = heap_base;
	if ((heap_base + increment) > (uint8_t*) &__heap_end__) {
		/* not enough memory, set errno and return -1 */
		errno = ENOMEM;
		return (void *) -1;
	}

	/* enough memory, increment heap base */
	heap_base += increment;

	/* return prior head base */
	return (void *)prev_head_base;
}
#else
  /* GHS implementation */
#endif
/*lint -restore */
