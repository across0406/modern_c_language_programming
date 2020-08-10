#include "object.h"
#include "classical_stack.h"
#include "multiple_stack.h"

#include <stdio.h>
#include <stdbool.h>

//
//	int stack_new_free_test( void )
//	- Description : new and free test
//	- return values:
//		|- 0 => success
//		|- 1 => fail for new
//		|- 2 => fail for free
//
int stack_new_free_test( void )
{
	int test_result = 0;

	if ( stack_new( stack_obj, 10, &stack_obj ) )
	{
		test_result = 0;
	}
	else
	{
		return test_result = 1;
	}

	if ( stack_free( stack_obj, &stack_obj ) )
	{
		test_result = 0;
	}
	else
	{
		return test_result = 2;
	}
	
	return test_result;
}

int main( void )
{
	// stack_new_free_test start
	int stack_new_free_result = stack_new_free_test();

	switch (stack_new_free_result)
	{
	case 1:
		printf("It was fail to generate stack.");
		break;

	case 2:
		printf("It was fail to delete stack.");
		break;

	default:
	case 0:
		printf("It was success to generate and delete stack.");
		break;
	}
	// stack_new_free_test end

	return 0;
}