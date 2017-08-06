// parseJSON.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//
#include <stdio.h>
#include <tchar.h>
#include <string.h>

#include "parson.h"

#define NAME_MAX 32

#define JSON2STRUCT_STR(_json, _struct, _key, _size)						\
do{																			\
	strncpy(_struct.##_key, json_object_dotget_string(_json, #_key),_size); \
} while (0);																\

#define JSON2STRUCT_NUM(_json, _struct, _key)					\
do {															\
	_struct.##_key = json_object_dotget_number(_json, #_key);	\
}while(0); 

#define JSON2STRUCT_BOOL(_json, _struct, _key)					\
do {															\
	_struct.##_key = json_object_dotget_boolean(_json, #_key);	\
}while(0); 


typedef struct _NAME {
	char first[NAME_MAX + 1];
	char last[NAME_MAX + 1];
} Name;

typedef struct _PERSONINFO {
	Name name;
	unsigned int age;
}PERSON_INFO;

int main()
{
	JSON_Value *root_value = json_parse_file("./personal.json");
	JSON_Object *root = json_object(root_value);

	PERSON_INFO person;
	
	JSON2STRUCT_NUM(root, person, age);
	JSON2STRUCT_STR(root, person, name.first, 32);
	JSON2STRUCT_STR(root, person, name.last, 32);


	json_value_free(root_value);
	
    return 0;
}

