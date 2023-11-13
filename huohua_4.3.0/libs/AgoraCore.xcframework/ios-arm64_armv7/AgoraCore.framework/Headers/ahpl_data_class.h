/*************************************************************
 * Author:	Lionfore Hao (haolianfu@agora.io)
 * Date	 :	Sep 4th, 2023
 * Module:	AHPL common data for C++ definition file
 *
 *
 * This is a part of the Advanced High Performance Library.
 * Copyright (C) 2018 ~ 2023 Agora IO
 * All rights reserved.
 *
 *************************************************************/

#ifndef __AHPL_DATA_CLASS_H__
#define __AHPL_DATA_CLASS_H__


#include <stdlib.h>

#include <api/ahpl_types.h>
#include <api/ahpl_defs.h>
#include <api/ahpl_data.h>


class ahpl_data_class {
protected:
	ahpl_data_t d;

public:
	ahpl_data_class ()
	{
		d = NULL;
	}

	ahpl_data_class (const ahpl_data_class &src)
	{
		d = src.d;
		if (d != NULL)
			ahpl_data_get (d);
	}

	ahpl_data_class &operator = (const ahpl_data_class &src)
	{
		if (d != NULL)
			ahpl_data_put (d);

		d = src.d;
		if (d != NULL)
			ahpl_data_get (d);

		return *this;
	}

	operator ahpl_data_t () const
	{
		return d;
	}

	ahpl_data_t detach ()
	{
		ahpl_data_t data = d;
		d = NULL;
		return data;
	}

	void *ptr () const
	{
		if (d != NULL)
			return ahpl_data_ptr_get (d);

		return NULL;
	}

	size_t len () const
	{
		if (d != NULL)
			return ahpl_data_len (d);

		return 0;
	}

	~ahpl_data_class ()
	{
		if (d != NULL)
			ahpl_data_put (d);
	}

#if (__cplusplus >= 201103) || defined (_MSC_VER)
	ahpl_data_class (ahpl_data_class &&src)
	{
		d = src.d;
		src.d = NULL;
	}

	ahpl_data_class &operator = (ahpl_data_class &&src)
	{
		if (d != NULL)
			ahpl_data_put (d);

		d = src.d;
		src.d = NULL;
		return *this;
	}
#endif /* C++11 */
};

class ahpl_data_buf: public ahpl_data_class {
public:
	ahpl_data_buf (size_t sz)
	{
		if (sz > 0) {
			d = ahpl_data_create (sz);
			if (d == NULL)
				abort ();
		}
	}

	ahpl_data_buf (const void *src, size_t len)
	{
		if (len > 0) {
			d = ahpl_data_create (len);
			if (d == NULL)
				abort ();

			memcpy (ptr (), src, len);
		}
	}

	ahpl_data_buf (const char *str)
	{
		if (str != NULL) {
			size_t str_l = strlen (str);
			d = ahpl_data_create (str_l + 1);
			if (d == NULL)
				abort ();

			memcpy (ptr (), str, str_l + 1);
		}
	}

	ahpl_data_buf (ahpl_data_t src)
	{
		d = src;
		if (src != NULL)
			ahpl_data_get (src);
	}

	ahpl_data_buf (const ahpl_data_buf &src)
	{
		d = src.d;
		if (d != NULL)
			ahpl_data_get (d);
	}

	ahpl_data_buf &operator = (const char *str)
	{
		if (d != NULL) {
			ahpl_data_put (d);
			d = NULL;
		}

		if (str != NULL) {
			size_t str_l = strlen (str);
			d = ahpl_data_create (str_l + 1);
			if (d == NULL)
				abort ();

			memcpy (ptr (), str, str_l + 1);
		}

		return *this;
	}

	ahpl_data_buf &operator = (ahpl_data_t src)
	{
		if (d != NULL)
			ahpl_data_put (d);

		d = src;
		if (src != NULL)
			ahpl_data_get (src);

		return *this;
	}

	ahpl_data_buf &operator = (const ahpl_data_buf &src)
	{
		if (d != NULL)
			ahpl_data_put (d);

		d = src.d;
		if (d != NULL)
			ahpl_data_get (d);

		return *this;
	}

	operator void *() const
	{
		if (d != NULL)
			return ptr ();

		return NULL;
	}

	operator char *() const
	{
		return (char *)ptr ();
	}

	operator unsigned char *() const
	{
		return (unsigned char *)ptr ();
	}

#if (__cplusplus >= 201103) || defined (_MSC_VER)
	ahpl_data_buf (ahpl_data_buf &&src)
	{
		d = src.d;
		src.d = NULL;
	}

	ahpl_data_buf &operator = (ahpl_data_buf &&src)
	{
		if (d != NULL)
			ahpl_data_put (d);

		d = src.d;
		src.d = NULL;
		return *this;
	}
#endif /* C++11 */
};

template<typename T>
class ahpl_data_var: public ahpl_data_class {
public:
	ahpl_data_var ()
	{
		d = ahpl_data_create (sizeof (T));
		if (d == NULL)
			abort ();
	}

	ahpl_data_var (size_t nelems)
	{
		if (nelems == 0)
			abort ();

		d = ahpl_data_create (sizeof (T) * nelems);
		if (d == NULL)
			abort ();
	}

	ahpl_data_var (const ahpl_data_var &src)
	{
		d = src.d;
		if (d != NULL)
			ahpl_data_get (d);
	}

	ahpl_data_var &operator = (const ahpl_data_var &src)
	{
		if (d != NULL)
			ahpl_data_put (d);

		d = src.d;
		if (d != NULL)
			ahpl_data_get (d);

		return *this;
	}

	ahpl_data_var &operator = (const T &v)
	{
		*(T *)ahpl_data_ptr_get (d) = v;
		return *this;
	}

	operator T () const
	{
		if (d == NULL)
			abort ();

		return *(T *)ahpl_data_ptr_get (d);
	}

	operator T& ()
	{
		if (d == NULL)
			abort ();

		return *(T *)ahpl_data_ptr_get (d);
	}

	T operator [] (size_t i) const
	{
		size_t count;
		T *arr;

		if (d == NULL)
			abort ();

		count = len () / sizeof (T);
		if (i >= count)
			abort ();

		arr = (T *)ahpl_data_ptr_get (d);
		return arr [i];
	}

	T& operator [] (size_t i)
	{
		size_t count;
		T *arr;

		if (d == NULL)
			abort ();

		count = len () / sizeof (T);
		if (i >= count)
			abort ();

		arr = (T *)ahpl_data_ptr_get (d);
		return arr [i];
	}

#if (__cplusplus >= 201103) || defined (_MSC_VER)
	ahpl_data_var (ahpl_data_var &&src)
	{
		d = src.d;
		src.d = NULL;
	}

	ahpl_data_var &operator = (ahpl_data_var &&src)
	{
		if (d != NULL)
			ahpl_data_put (d);

		d = src.d;
		src.d = NULL;
		return *this;
	}
#endif /* C++11 */
};


#endif /* __AHPL_DATA_CLASS_H__ */