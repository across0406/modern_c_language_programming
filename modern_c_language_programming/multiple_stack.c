#include <stdbool.h>
#include <stdlib.h>
#include "multiple_stack.h"

static bool is_stack_null( const Stack* stack )
{
	bool return_value = false;

	if ( is_null( stack ) )
	{
		return_value = false;
	}
	else
	{
		return_value = stack->buffer == NULL;
	}

	return return_value;
}

static bool is_stack_full( const Stack* stack )
{
	bool return_value = false;

	if ( is_null( stack ) )
	{
		return_value = false;
	}
	else
	{
		return_value = stack->top == stack->size;
	}

	return return_value;
}

static bool is_stack_empty( const Stack* stack )
{
	bool return_value = false;

	if ( is_null( stack ) )
	{
		return_value = false;
	}
	else
	{
		return_value = stack->top == 0;
	}

	return return_value;
}

static bool is_stack_range_ok( const Stack_Range_Check* check, int val )
{
	bool return_value = false;

	if ( is_null(check) )
	{
		return_value = false;
	}
	else
	{
		return_value = ( check == NULL || ( check->min <= val && val <= check->max ));
	}

	return return_value;
}

STACK_OPERATION_CHECK stack_push( Stack* stack, int val)
{
	STACK_OPERATION_CHECK return_value = 0;

	if ( is_null( stack ) )
	{
		return_value = NULL_OBJECT;
	}
	else if ( is_stack_null( stack ) )
	{
		return_value = NULL_BUFFER;
	}
	else if ( is_stack_full( stack ) )
	{
		return_value = FULL_OR_EMPTY_BUFFER;
	}
	else if ( !is_stack_range_ok( stack->check, val ) )
	{
		return_value = NOT_MATCH_RANGE;
	}
	else
	{
		stack->buffer[ stack->top++ ] = val;
		return_value = SUCCESS;
	}

	return return_value;
}

STACK_OPERATION_CHECK stack_pop( Stack* stack, int* ret )
{
	STACK_OPERATION_CHECK return_value = 0;

	if ( is_null( stack ) )
	{
		return_value = NULL_OBJECT;
	}
	else if ( is_stack_null( stack ) )
	{
		return_value = NULL_BUFFER;
	}
	else if ( is_stack_full( stack ) )
	{
		return_value = FULL_OR_EMPTY_BUFFER;
	}
	else
	{
		*ret = stack->buffer[ --stack->top ];
		return_value = SUCCESS;
	}

	return return_value;
}

bool stack_only_buffer_new( Stack* stack, int num )
{
	bool return_value = false;

	if ( is_null( stack ) )
	{
		return_value = false;
	}
	if ( !is_stack_null( stack ) )
	{
		stack_free( stack, &stack );
	}

	int* temp_buffer = (int*)malloc(sizeof(int) * num);
	stack->buffer = temp_buffer;
	return_value = true;

	return return_value;
}

bool stack_only_buffer_free( Stack* stack )
{
	bool return_value = false;

	if (is_null(stack))
	{
		return_value = false;
	}
	else if (!is_stack_null(stack))
	{
		free(stack->buffer);
		stack->buffer = NULL;
		return_value = true;
	}

	return return_value;
}

bool stack_only_check_new( Stack* stack, int min, int max )
{
	bool return_value = false;

	if ( is_null( stack ) )
	{
		return_value = false;
	}
	if ( !is_stack_null( stack ) )
	{
		stack_free( stack, &stack );
	}

	Stack_Range_Check* temp_check = (Stack_Range_Check*)malloc( sizeof( Stack_Range_Check ) );
	temp_check->min = min;
	temp_check->max = max;
	stack->check = temp_check;
	return_value = true;

	return return_value;
}

bool stack_only_check_free( Stack* stack )
{
	bool return_value = false;

	if ( is_null( stack ) )
	{
		return_value = false;
	}
	else if ( !is_stack_null( stack ) )
	{
		free(stack->check);
		return_value = true;
	}

	return return_value;
}

bool stack_new( Stack* stack, int num, Stack** out_stack_addr )
{
	bool return_value = false;

	if ( is_null( stack ) )
	{
		stack = ( Stack* )malloc( sizeof( Stack ) );
		stack->buffer = NULL;
		stack->check = NULL;
		stack->top = 0;
		stack->size = num;
		*out_stack_addr = stack;
	}

	return_value = stack_only_buffer_new( stack, num );

	return return_value;
}

bool stack_new_with_check( Stack* stack, int num, int min, int max )
{
	bool return_value = false;

	if ( is_null( stack ) )
	{
		stack = (Stack*)malloc( sizeof( Stack ) );
		stack->buffer = NULL;
		stack->check = NULL;
		stack->top = 0;
		stack->size = num;
	}

	return_value = stack_only_buffer_new( stack, num );
	return_value = stack_only_check_new( stack, min, max );

	return return_value;
}

bool stack_free( Stack* stack, Stack** out_stack_addr )
{
	bool return_value = false;

	return_value = stack_only_buffer_free(stack);

	if (!return_value)
	{
		return return_value;
	}

	if ( stack->check )
	{
		return_value = stack_only_check_free(stack);

		if ( !return_value )
		{
			return return_value;
		}
	}

	*out_stack_addr = NULL;
	free( stack );
	return_value = true;

	return return_value;
}
