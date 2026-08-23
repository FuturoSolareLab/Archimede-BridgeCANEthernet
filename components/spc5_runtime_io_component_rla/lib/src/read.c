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

#include <spc5_io.h>

#ifndef __ghs__
ssize_t read(int fd, void *buf, size_t count)
{
	ssize_t ret;

	ret = (ssize_t)ioRead(fd, buf, count);

	return ret;
}
#else
long read (int fno, void *buf, long size)
{
	long ret;

	ret = (long)ioRead(fno, buf, size);

	return ret;
}
#endif
/*lint -restore */
