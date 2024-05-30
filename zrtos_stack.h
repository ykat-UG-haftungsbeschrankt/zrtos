/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_TASK_MUTEX_H
#define ZRTOS_TASK_MUTEX_H
#ifdef __cplusplus
extern "C" {
#endif


#include "zrtos.h"
#include "zrtos_types.h"
#include "zrtos_mem.h"


typedef struct _zrtos_stack_t{
	void    *data;
	size_t  offset;
	size_t  length;
}zrtos_stack_t;

bool zrtos_stack__init(
	 zrtos_stack_t *thiz
	,void *data
	,size_t length
){
	thiz->data = data;
	thiz->offset = 0;
	thiz->length = 0;
	return true;
}

static bool _zrtos_stack__cpy(
	 zrtos_stack_t *thiz
	,void *dest
	,void *src
	,size_t length
	,size_t offset_plus_length
){
	if(offset_plus_length <= thiz->length){
		zrtos_mem__cpy(
			 dest
			,src
			,length
		);
		return true;
	}
	return false;
}

bool zrtos_stack__read(
	 zrtos_stack_t *thiz
	,void *data
	,size_t length
	,size_t offset
){
	return _zrtos_stack__cpy(
		 thiz
		,data
		,zrtos_types__ptr_add(
			 thiz->data
			,offset
		)
		,length
		,offset + length
	);
}

bool zrtos_stack__write(
	 zrtos_stack_t *thiz
	,void *data
	,size_t length
	,size_t offset
){
	return _zrtos_stack__cpy(
		 thiz
		,zrtos_types__ptr_add(
			 thiz->data
			,offset
		)
		,data
		,length
		,offset + length
	);
}

bool zrtos_stack__push(
	 zrtos_stack_t *thiz
	,void *data
	,size_t length
){
	size_t offset = thiz->offset;
	bool ret = _zrtos_stack__cpy(
		 thiz
		,zrtos_types__ptr_add(
			 thiz->data
			,offset
		)
		,data
		,length
		,offset + length
	);
	if(ret){
		thiz->offset += length;
	}
	return ret;
}

bool zrtos_stack__pop(
	 zrtos_stack_t *thiz
	,void *data
	,size_t length
){
	size_t offset = thiz->offset;
	if(offset >= length){
		offset = (thiz->offset = offset - length);
		zrtos_mem__cpy(
			 data
			,zrtos_types__ptr_add(
				 thiz->data
				,offset
			)
			,length
		);
		return true;
	}
	return false;
}

bool zrtos_stack__set_offset(
	 zrtos_stack_t *thiz
	,size_t offset
){
	if(offset <= length){
		thiz->offset = offset;
		return true;
	}
	return false;
}

size_t zrtos_stack__get_offset(
	 zrtos_stack_t *thiz
){
	return thiz->offset;
}


#ifdef __cplusplus
}
#endif
#endif