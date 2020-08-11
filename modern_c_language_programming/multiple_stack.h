#pragma once

#ifndef __MULTIPLE_STACK_H__
#define __MULTIPLE_STACK_H__

#include <stddef.h>

#include "object.h"

#ifdef __cplusplus
extern "C"
{
#endif

	// General Checker
	typedef struct Validator
	{
		bool ( * const validate )( struct Validator* this_pointer, int val );
		void* const data;
	} Validator;

	typedef struct
	{
		int min;
		int max;
	} Stack_Range_Check;

	typedef struct
	{
		int prev_val;
	} Previous_Item;

	typedef struct
	{
		int top;
		size_t size;		// deleted const keyword.
		int* buffer;		// deleted const keyword.

		// add for range checking.
		//bool need_range_check;
		//int max;
		//int min;
		Stack_Range_Check* check;
	} Stack;

	typedef enum
	{
		SUCCESS = 0,
		NULL_OBJECT = 1,
		NULL_BUFFER = 2,
		FULL_OR_EMPTY_BUFFER = 3,
		NOT_MATCH_RANGE = 4,
		PASSING_ITEM_IS_NULL = 5,
		FAIL_NEW_BUFFER = 6,
		FAIL_FREE_BUFFER = 7,
	} STACK_OPERATION_STATUS;

	STACK_OPERATION_STATUS stack_push( Stack* stack, int val );
	STACK_OPERATION_STATUS stack_pop( Stack* stack, int* ret );
	
	bool stack_only_buffer_new( Stack* stack, size_t buffer_size );
	bool stack_only_buffer_free( Stack* stack );

	bool stack_only_check_new( Stack* stack, int min, int max );
	bool stack_only_check_free( Stack* stack );

	bool stack_new( Stack* stack, size_t buffer_size, Stack** out_stack_addr );
	bool stack_new_with_check( Stack* stack, int num, int min, int max );
	bool stack_free( Stack* stack, Stack** out_stack_addr );

	STACK_OPERATION_STATUS stack_get_size( Stack* stack, size_t* size );
	STACK_OPERATION_STATUS stack_set_size( Stack* stack, size_t size );

	static Stack* stack_obj = NULL;
#ifdef __cplusplus
}
#endif

#endif