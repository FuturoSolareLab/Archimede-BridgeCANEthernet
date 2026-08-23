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
#include <spc5_io.h>

#ifndef __ghs__
off_t lseek(int fd, off_t offset, int whence)
{
	(void) (fd);
	(void) (offset);
	(void) (whence);

	/*
	 * This function is implemented only for stdout or stderr
	 * no need to check anything, assuming always success.
	 */
	return 0;
}
#else
  /* GHS implementation */
#endif
/*lint -restore */
