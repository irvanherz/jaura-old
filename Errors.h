#ifndef ERRORS_H
#define ERRORS_H


/*#define SUCCESS				 0
#define ERROR_INVALID 		-1
#define ERROR_NOT_FOUND		-2
#define ERROR_UNDEFINED		-3
#define ERROR_BAD_ADDRESS	-4
#define ERROR_TRY_AGAIN		-5
#define ERROR_BUSY			-6
#define ERROR_READ_ONLY		-7
#define ERROR_OOM			-8
*/
enum ERROR_TYPE {
	SUCCESS				=  0,
	ERROR_INVALID 		= -1,
	ERROR_NOT_FOUND		= -2,
	ERROR_UNDEFINED		= -3,
	ERROR_BAD_ADDRESS	= -4,
	ERROR_TRY_AGAIN		= -5,
	ERROR_BUSY			= -6,
	ERROR_READ_ONLY		= -7,
	ERROR_OOM			= -8,
};

#define IS_ERROR(val)(((val <= -1) && (val >= -255)) ? TRUE : FALSE)

#endif
