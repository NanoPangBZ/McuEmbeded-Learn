#pragma once

#include <stdarg.h>

typedef struct{
    const char* name;
    int (*func)(void* args , ... );
    void* other_info;
}function_info_t ;

#ifndef STR
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#endif

#define CONST_FUNCTION_INFO( func , info_ptr )  const function_info_t func ## _info_table = { STR(func) , func , info_ptr }
#define FUNCTION_SETTION_DECARLE_HEAD( section_name )   __attribute__ ( (section( section_name  ) , used  )  )
#define DECLARE_FUNCTION_INFO_IN_SECTION( section_name , func , info_ptr ) FUNCTION_SETTION_DECARLE_HEAD( section_name ) CONST_FUNCTION_INFO( func , info_ptr );


#define REGISTER_FUNCTION( func )                           DECLARE_FUNCTION_INFO_IN_SECTION( ".function_table" , func , 0 )
#define REGISTER_FUNCTION_WITH_INFO( func , info_ptr )      DECLARE_FUNCTION_INFO_IN_SECTION( ".function_table" , func , info_ptr )

//DECLARE_FUNCTION_INFO_IN_SECTION( 段名 , 函数指针 , 指针 )
//DECLARE_FUNCTION_INFO_IN_SECTION( ".pre_init" , test , NULL )
//__attribute__ ( (section( ".pre_init" ) , used  ) const function_info_t test_info = { "test" , test , NULL }
//相当与将一个名叫test_info的const function_info_t变量定义在.pre_init段中。
