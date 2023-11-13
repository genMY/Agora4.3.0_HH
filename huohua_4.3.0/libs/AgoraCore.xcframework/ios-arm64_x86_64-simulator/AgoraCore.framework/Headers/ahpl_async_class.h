/*************************************************************
 * Author:	Lionfore Hao (haolianfu@agora.io)
 * Date	 :	Aug 15th, 2023
 * Module:	AHPL async class for C++11 definition file
 *
 *
 * This is a part of the Advanced High Performance Library.
 * Copyright (C) 2018 ~ 2023 Agora IO
 * All rights reserved.
 *
 *************************************************************/

#if (__cplusplus >= 201103) || defined (_MSC_VER)

#ifndef __AHPL_ASYNC_CPP_H__
#define __AHPL_ASYNC_CPP_H__


#include <api/ahpl_types.h>
#include <api/ahpl_async.h>

#include <functional>
#include <memory>

class ahpl_async_class {
public:
	typedef std::function <void (void)> ahpl_async_block_lambda_f;

	static int block (ahpl_async_block_lambda_f&& task)
	{
		ahpl_async_block_lambda_f block_f (std::move (task));
		return ahpl_async_block (____block_f, 1, &block_f);
	}

private:
	static void ____block_f (uintptr_t argc, uintptr_t argv [])
	{
		ahpl_async_block_lambda_f *block_f = reinterpret_cast<ahpl_async_block_lambda_f *>(argv [0]);
		(*block_f) ();
	}
};

/**
 * Helper async macro for single line code, example:
 * __ahpl_async__ (some_func ());
 **/
#define __ahpl_async__(_x_y__) { ahpl_async_class::block ([&] { _x_y__; }); }

/**
 * Helper async macros for multiple lines code, example:
 *
 * __ahpl_async_begin__
 *	// Add your own multiple lines code here:
 *	ahpl_define_stack (stack);
 *
 *	task->async ("<task lambda name>", [=] {
 *		......
 *	});
 *
 *	ahpl_ref_class::resume (stack, AHPL_REF_INVALID, "<resume lambda name>", [=](int free_only) {
 *		......
 *	});
 * __ahpl_async_end__
 *
 **/
#define __ahpl_async_begin__ { ahpl_async_class::block ([&] {
#define __ahpl_async_end__ }); }

/**
 * Helper async macros for implementing a function with return value, example:
 *
 * __ahpl_async_func_def__ (<return type>, <ret var>, func_name (func args))
 * {
 *     <func body>
 * }
 * __ahpl_async_func_end__ (<ret var>)
 *
 **/
#define __ahpl_async_func_def__(_ret_type_, _ret_var_, _fn_and_args_) \
_ret_type_ _fn_and_args_ \
{ \
	_ret_type_ _ret_var_; \
	ahpl_async_class::block ([&]

#define __ahpl_async_func_end__(_ret_var_) \
	); \
	return _ret_var_; \
}

/**
 * Helper async macros for implementing a void function, example:
 *
 * __ahpl_async_func_def_void__ (func_name (func args))
 * {
 *     <func body>
 * }
 * __ahpl_async_func_end_void__ ()
 *
 **/
#define __ahpl_async_func_def_void__(_fn_) \
void _fn_ \
{ \
	ahpl_async_class::block ([&]

#define __ahpl_async_func_end_void__() \
	); \
}


#endif /* __AHPL_ASYNC_CPP_H__ */

#endif /* C++11 */