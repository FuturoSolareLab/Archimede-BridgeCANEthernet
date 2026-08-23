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
int open(const char *pathname, int flags)
{
	int io_id;

	io_id = ioOpen(pathname, flags);

	return io_id;
}
#else
int open (const char *filename, int flags)
{
	int io_id;

	io_id = ioOpen(filename, flags);

	return io_id;
}
#endif
/*lint -restore */
