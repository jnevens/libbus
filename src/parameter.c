/*
 * parameter.c
 *
 *  Created on: Apr 10, 2016
 *      Author: jnevens
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bus/object.h"
#include "bus/variant.h"
#include "bus/parameter.h"

struct parameter_s
{
	object_t *parent;
	char *name;
	parameter_type_t type;
	variant_t *value;
};

//static variant_type_t param_type_to_variant_type_conversion[] = {
//		VARIANT_TYPE_INVALID,
//		VARIANT_TYPE_BOOL,
//		VARIANT_TYPE_INT8,
//		VARIANT_TYPE_UINT8,
//		VARIANT_TYPE_INT16,
//		VARIANT_TYPE_UINT16,
//		VARIANT_TYPE_INT32,
//		VARIANT_TYPE_UINT32,
//		VARIANT_TYPE_INT64,
//		VARIANT_TYPE_UINT64,
//		VARIANT_TYPE_FLOAT,
//		VARIANT_TYPE_DOUBLE,
//		VARIANT_TYPE_CHAR,
//};
//
//static variant_type_t parameter_type_to_variant_type(parameter_type_t param_type)
//{
//	return param_type_to_variant_type_conversion[param_type];
//}

parameter_t *parameter_create(object_t *obj, const char *name, parameter_type_t type)
{
	parameter_t *param = calloc(1, sizeof(parameter_t));
	param->name = strdup(name);
	param->type = type;
	param->parent = obj;

	object_add_parameter(obj, param);

	return param;
}

void parameter_destroy(parameter_t *param)
{
	object_remove_parameter(param->parent, param);
	variant_destroy(param->value);
	free(param->name);
	free(param);
}

const char *parameter_name(parameter_t *param)
{
	if(param) {
		return param->name;
	}

	return NULL;
}

bool parameter_set_value(parameter_t *param, variant_t *variant)
{
	if(!param || !variant) {
		return false;
	}

	variant_destroy(param->value);

	param->value = variant_duplicate(variant);

	return (param->value) ? true : false;
}

variant_t *parameter_value(parameter_t *param)
{
	return variant_duplicate(param->value);
}

variant_t *parameter_da_value(parameter_t *param)
{
	return param->value;
}

void parameter_print(parameter_t *param)
{
	object_print_path(param->parent);
	printf(".%s=", param->name);
	variant_print(param->value);
	printf("\n");
}
