#pragma once

#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct
	{
		void* item;
		int type;
	} Object;

	typedef enum
	{
		VALUE = 0,
		ARRAY = 1,
		FUNCTION = 2
	} OBJECT_TYPE;

	typedef enum
	{
		INT = 0,
		UNSIGNED_INT = 1,
		LONG_LONG_INT = 2,
		UNSIGNED_LONG_LONG_INT = 3,

	} OBJECT_DATA_TYPE;

	bool is_null( void* obj );

#ifdef __cplusplus
}
#endif

#endif