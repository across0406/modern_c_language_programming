#include "object.h"
#include "classical_stack.h"
#include "multiple_stack.h"

#include <stdio.h>
#include <stdbool.h>

//
//	int stack_push_test( int iter_num )
//	- Description : push test
//	- return values:
//		|- 0 => success
//		|- 1 => push error
//
int stack_push_test( int iter_num )
{
	int test_result = 0;

	size_t buffer_size = 0;
	STACK_OPERATION_STATUS get_size_result = stack_get_size( stack_obj, &buffer_size);

	if (get_size_result != SUCCESS)
	{
		return test_result = 1;
	}

	for ( int i = 0; i < iter_num; ++i )
	{
		STACK_OPERATION_STATUS push_check_result = stack_push(stack_obj, i);		

		if ( i >= buffer_size && push_check_result != SUCCESS )
		{
			printf("Finish push test.\n");
			test_result = 0;
		}
		else if ( i < buffer_size && push_check_result != SUCCESS )
		{
			test_result = 1;
			break;
		}
		else
		{
			switch (i)
			{
			case 0:
				printf("%d st push item is %d.\n", i + 1, i);
				break;

			case 1:
				printf("%d nd push item is %d.\n", i + 1, i);
				break;

			default:
				printf("%d th push item is %d.\n", i + 1, i);
				break;
			}
		}
	}

	return test_result;
}

//
//	int stack_pop_test( int iter_num )
//	- Description : pop test
//	- return values:
//		|- 0 => success
//		|- 1 => pop error
//
int stack_pop_test( int iter_num )
{
	int test_result = 0;

	size_t buffer_size = 0;
	STACK_OPERATION_STATUS get_size_result = stack_get_size( stack_obj, &buffer_size );

	if (get_size_result != SUCCESS)
	{
		return test_result = 1;
	}

	for (int i = 0; i < iter_num; ++i)
	{
		int pop_item = 0;

		STACK_OPERATION_STATUS pop_check_result = stack_pop( stack_obj, &pop_item );

		if ( i >= buffer_size && pop_check_result != SUCCESS )
		{
			printf("Finish pop test.\n");
			test_result = 0;
		}
		else if ( i < buffer_size && pop_check_result != SUCCESS )
		{
			test_result = 1;
			break;
		}
		else
		{
			switch ( i )
			{
			case 0:
				printf("%d st pop item is %d.\n", i + 1, pop_item);
				break;

			case 1:
				printf("%d nd pop item is %d.\n", i + 1, pop_item);
				break;

			default:
				printf( "%d th pop item is %d.\n", i + 1, pop_item );
				break;
			}			
		}
	}

	return test_result;
}

//
//	int stack_new_free_test( void )
//	- Description : new and free test
//	- return values:
//		|- 0 => success
//		|- 1 => fail for new
//		|- 2 => fail for free
//		|- 3 => fail for push test
//		|- 4 => fail for pop test
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

	// push test call
	if ( !stack_push_test( 11 ) )
	{
		test_result = 0;
	}
	else
	{
		return test_result = 3;
	}

	// pop test call
	if ( !stack_pop_test( 11 ) )
	{
		test_result = 0;
	}
	else
	{
		return test_result = 4;
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