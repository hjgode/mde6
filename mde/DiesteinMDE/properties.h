#include "stdafx.h"

// properties.h

#ifndef _PROPERTIES_H
#define _PROPERTIES_H

#define PROPERTY(t, n) __declspec( property (put = __set_##n, get = __get_##n ) ) t n;\
	typedef t __type_##n
#define READONLY_PROPERTY(t, n) __declspec( property (get = __get_##n) ) t n;\
	typedef const t __type_##n
#define WRITEONLY_PROPERTY(t, n) __declspec( property (put = __set_##n) ) t n;\
	typedef t __type_##n
 
#define GET(n) __type_##n& __get_##n()
#define SET(n) __type_##n& __set_##n(const __type_##n& value)

#endif /* _PROPERTIES_H */ 
