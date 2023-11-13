/*************************************************************
 * Author:	Lionfore Hao
 * Date	 :	Jun 30th, 2019
 * Module:	AHPL mpq fd C++ implementation
 *
 *
 * This is a part of the Agora SDK.
 * Copyright (C) 2019 Agora IO. All rights reserved.
 *
 *************************************************************/

#ifndef __AHPL_MPQ_FD_CLASS_H__
#define __AHPL_MPQ_FD_CLASS_H__

#include <stdlib.h>

#include <api/ahpl_types.h>
#include <api/ahpl_mpq_fd.h>


class ahpl_mpq_fd_class {
public:
	ahpl_mpq_fd_class (ahpl_fd_t fd): attached_fd (fd)
	{
	}

	virtual ~ahpl_mpq_fd_class ()
	{
		if (!ahpl_fd_invalid (attached_fd))
			ahpl_close (attached_fd);
	}

	ahpl_fd_t get_fd ()
	{
		return attached_fd;
	}

public:
	int co_read (ahpl_data_t d_ret, ahpl_data_t d_buf)
	{
		return ahpl_co_read (attached_fd, d_ret, d_buf);
	}

	ssize_t co_write (ahpl_data_t d_ret, ahpl_data_t d_buf)
	{
		return ahpl_co_write (attached_fd, d_ret, d_buf);
	}

	ssize_t co_buf_write (ahpl_data_t d_ret, const void *buf, size_t count)
	{
		return ahpl_co_buf_write (attached_fd, d_ret, buf, count);
	}

private:
	const ahpl_fd_t attached_fd;

#if (__cplusplus >= 201103) || defined (_MSC_VER)
private:
	ahpl_mpq_fd_class () = delete;
	ahpl_mpq_fd_class (const ahpl_mpq_fd_class &) = delete;
	ahpl_mpq_fd_class (ahpl_mpq_fd_class &&) = delete;
	ahpl_mpq_fd_class &operator = (const ahpl_mpq_fd_class &) = delete;
	ahpl_mpq_fd_class &operator = (ahpl_mpq_fd_class &&) = delete;
#endif /* C++11 */
};


#endif /* __AHPL_MPQ_FD_CLASS_H__ */