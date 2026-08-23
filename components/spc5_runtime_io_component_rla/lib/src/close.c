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

#ifndef __ghs__
int close(int fd)
{
	(void) (fd);

	/*
	 * Nothing to do, just return success.
	 */
	return 0;
}
#else
int close (int fno)
{
	(void) (fno);

	/*
	 * Nothing to do, just return success.
	 */
	return 0;
}
#endif
/*lint -restore */
