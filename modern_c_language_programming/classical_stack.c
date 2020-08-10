#include "classical_stack.h"

static int stack[16];
static int top = 0;

bool is_stack_full( void )
{
	return top == sizeof(stack) / sizeof(int);
}

bool is_stack_empty( void )
{
	return top == 0;
}

static bool classical_stack_push( int val )
{
	bool return_value = false;

	if ( is_stack_full() )
	{
		return_value = false;
	}
	else
	{
		stack[ top++ ] = val;
		return_value = true;
	}	

	return return_value;
}

static bool classical_stack_pop( int* ret )
{
	bool return_value = false;

	if ( is_stack_empty() )
	{
		return_value = false;
	}
	else
	{
		*ret = stack[ --top ];
		return_value = true;
	}

	return return_value;
}
