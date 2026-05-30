/*
* Copyright (c) 2025-present Wojciech Kaptur ( _Sqyd_ / Sqydev )
* Github: https://github.com/Sqydev
* GPG Fingerprint: 6DC2516B0DFDA9C59661650722F7B8A777F33B56
* 
* This software is provided "as-is", without any express or implied warranty. In no event
* will the authors be held liable for any damages arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose, including commercial
* applications, and to alter it and redistribute it freely, subject to the following restrictions:
* 
* 1. Non-Misrepresentation: The origin of this software must not be misrepresented; 
*	you must not claim that you wrote the original software. An acknowledgment in 
*	product documentation is appreciated but not required.
* 
* 2. Source-Level Copyleft: Any altered versions (forks) of this software's source code, 
*	or files containing significant portions of this code, must be distributed under 
*	these same license terms. Such modified source code must be made publicly available 
*	to any recipient, even if used over a network (SaaS).
* 
* 3. Proprietary Integration: This software may be integrated into, linked with, or 
*	used as a component of proprietary and closed-source products. In such cases, 
*	the surrounding proprietary application code does not need to be disclosed, 
*	provided that the original or modified source code of THIS software remains 
*	available under the terms of Section 2.
* 
* 4. Persistent Metadata: All original credits, including those in the source code headers 
*	and binary metadata (e.g., ELF .comment section, PE StringFileInfo, or equivalent), 
*	must not be removed. You may add your own credits to forks, provided the original 
*	authorship remains clearly identified.
* 
* 5. Notice Retention: This license notice may not be removed or altered from any 
*	source or binary distribution.
*/

#ifndef CLASSES_LIB_H
#define CLASSES_LIB_H

#define CLASSES_VERSION_MAJOR 1
#define CLASSES_VERSION_MINOR 0
#define CLASSES_VERSION_PATCH 0

// NOTE: Thoes library specyfiers
#if defined(_WIN32) || defined (_WIN64)
	#if defined(__TINYC__)
		#define __declspec(x) __attribute__((x))
	#endif
	#if defined(BUILD_LIBTYPE_SHARED)
		#define RLAPI __declspec(dllexport)
	#elif defined(USE_LIBTYPE_SHARED)
		#define RLAPI __declspec(dllimport)
	#endif
#else
	#if defined(BUILD_LIBTYPE_SHARED)
		#define RLAPI __attribute__((visibility("default")))
	#endif
#endif

#ifndef RLAPI
	#define RLAPI
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#define Class class_t
#define Object object_t

#define class_struct(name) struct name { object_t base

#define Self(cls, object) (cls*)object
#define $(obj, function, ...) (obj)->function((obj), ##__VA_ARGS__)

typedef struct class_t class_t;
typedef struct object_t object_t;

struct class_t {
	size_t id;
	size_t index;

	void (*initTask)(object_t*);
	void (*cleanupTask)(object_t*);

	object_t** objects;

	size_t objectSize;

	size_t lastObjectId;
	size_t objectsCount;
};

struct object_t {
	size_t id;
	size_t index;

	class_t* root;
};

RLAPI class_t* RegisterClass(size_t objectSizeof, void (*initTask)(object_t*), void (*cleanupTask)(object_t*));
RLAPI void DestroyAllClasses(void);
RLAPI object_t* CreateObject(class_t* cls);
RLAPI void DestroyObject(object_t* object);
RLAPI void DestroyClass(class_t* cls);

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L

#include <stdint.h>

#define PA(x) (pm_item_t){ _PA_TYPE(x), _PA_ARG(x) }
#define PolyArg(x) PA(x)

#define _POLY_END (pm_item_t){ (poly_type_t)-1, {0} }

#define $P(poly, self, ...) CallPoly((poly), (object_t*)(self), (pm_item_t[]){ __VA_ARGS__, _POLY_END })

#define PolyDispatch(poly, self, ...) $P(poly, self, __VA_ARGS__)

#define $PC(obj, function, ...) CallPoly((obj)->function, (object_t*)(obj), (pm_item_t[]){ __VA_ARGS__, _POLY_END })

#define PolyCall(obj, function, ...) $PC(obj, function, __VA_ARGS__)

#define PReg(poly, handler, ...) _PolyRegSig((poly), (pm_sig_item_t[]){ __VA_ARGS__, _POLY_SIG_END }, (handler))

#define _POLY_SIG_END (pm_sig_item_t){ (poly_type_t)-1, 0 }

#define _PSig(type) (pm_sig_item_t){ (type), 0 }
#define _PSigObj(cls) (pm_sig_item_t){ POLY_TYPE_OBJ, (cls)->id }
#define _PSigCust(tid) (pm_sig_item_t){ POLY_TYPE_CUSTOM, (tid) }

#define PInt _PSig(POLY_TYPE_INT)
#define PUint _PSig(POLY_TYPE_UINT)
#define PLong _PSig(POLY_TYPE_LONG)
#define PUlong _PSig(POLY_TYPE_ULONG)
#define PLLong _PSig(POLY_TYPE_LLONG)
#define PULLong _PSig(POLY_TYPE_ULLONG)
#define PFloat _PSig(POLY_TYPE_FLOAT)
#define PDouble _PSig(POLY_TYPE_DOUBLE)
#define PStr _PSig(POLY_TYPE_STRING)
#define PObj(cls) _PSigObj(cls)
#define PType(t) _PSig(t)
#define PCust(tid) _PSigCust(tid)

#define PolyInt PInt
#define PolyUint PUint
#define PolyLong PLong
#define PolyUlong PUlong
#define PolyLLong PLLong
#define PolyULLong PULLong
#define PolyFloat PFloat
#define PolyDouble PDouble
#define PolyStr PStr
#define PolyObj(cls) PObj(cls)
#define PolyType(t) PType(t)
#define PolyCust(tid) PCust(tid)

#define PM_INT PInt
#define PM_STR PStr
#define PM_FLOAT PFloat
#define PM_DOUBLE PDouble
#define PM_OBJ(cls) PObj(cls)
#define $CALL(obj, function, ...) $PC(obj, function, __VA_ARGS__)

typedef enum {
    POLY_TYPE_INT,
    POLY_TYPE_UINT,
    POLY_TYPE_LONG,
    POLY_TYPE_ULONG,
    POLY_TYPE_LLONG,
    POLY_TYPE_ULLONG,
    POLY_TYPE_FLOAT,
    POLY_TYPE_DOUBLE,
    POLY_TYPE_STRING,
    POLY_TYPE_OBJ,
    POLY_TYPE_CUSTOM
} poly_type_t;

typedef size_t poly_type_id_t;

typedef union {
    int i;
    unsigned int ui;
    long l;
    unsigned long ul;
    long long ll;
    unsigned long long ull;
    float f;
    double d;
    const char* s;
    void* p;
    struct {
        poly_type_id_t type_id;
        void* ptr;
    } custom;
} poly_arg_t;

typedef void (*poly_handler_t)(object_t*, poly_arg_t*, size_t);

typedef struct {
    poly_type_t type;
    poly_type_id_t type_id;
} pm_sig_item_t;

typedef struct {
    poly_type_t type;
    poly_arg_t arg;
} pm_item_t;

typedef struct {
    poly_type_t* sig;
    poly_type_id_t* type_ids;
    size_t sig_len;
    poly_handler_t handler;
} poly_entry_t;

typedef struct {
    poly_entry_t* entries;
    size_t count;
} poly_t;

RLAPI poly_type_id_t CreatePolyType(void);

RLAPI poly_t* CreatePoly(void);
RLAPI void DestroyPoly(poly_t* poly);
RLAPI void DestroyAllPolys(void);

RLAPI void _PolyRegSig(poly_t* poly, pm_sig_item_t* sig, poly_handler_t handler);

RLAPI void CallPoly(poly_t* poly, object_t* self, pm_item_t* items);

#define PM_T(type) (pm_sig_item_t){ (type), 0 }
#define PM_T_OBJ(cls) (pm_sig_item_t){ POLY_TYPE_OBJ, (cls)->id }
#define PM_T_CUSTOM(tid) (pm_sig_item_t){ POLY_TYPE_CUSTOM, (tid) }

#define _PM_SIG_END (pm_sig_item_t){ (poly_type_t)-1, 0 }

#define PolyReg(poly, handler, ...) _PolyRegSig((poly), (pm_sig_item_t[]){ __VA_ARGS__, _PM_SIG_END }, (handler))

static inline poly_arg_t _pa_i(int x) { return (poly_arg_t){ .i = x }; }
static inline poly_arg_t _pa_ui(unsigned int x) { return (poly_arg_t){ .ui = x }; }
static inline poly_arg_t _pa_l(long x) { return (poly_arg_t){ .l = x }; }
static inline poly_arg_t _pa_ul(unsigned long x) { return (poly_arg_t){ .ul = x }; }
static inline poly_arg_t _pa_ll(long long x) { return (poly_arg_t){ .ll = x }; }
static inline poly_arg_t _pa_ull(unsigned long long x) { return (poly_arg_t){ .ull = x }; }
static inline poly_arg_t _pa_f(float x) { return (poly_arg_t){ .f = x }; }
static inline poly_arg_t _pa_d(double x) { return (poly_arg_t){ .d = x }; }
static inline poly_arg_t _pa_s(char* x) { return (poly_arg_t){ .s = x }; }
static inline poly_arg_t _pa_cs(const char* x) { return (poly_arg_t){ .s = x }; }
static inline poly_arg_t _pa_p(void* x) { return (poly_arg_t){ .p = x }; }

#define _PA_TYPE(x) _Generic((x), \
    int: POLY_TYPE_INT, \
    unsigned int: POLY_TYPE_UINT, \
    long: POLY_TYPE_LONG, \
    unsigned long: POLY_TYPE_ULONG, \
    long long: POLY_TYPE_LLONG, \
    unsigned long long: POLY_TYPE_ULLONG, \
    float: POLY_TYPE_FLOAT, \
    double: POLY_TYPE_DOUBLE, \
    char*: POLY_TYPE_STRING, \
    const char*: POLY_TYPE_STRING, \
    default: POLY_TYPE_OBJ \
)

#define _PA_ARG(x) _Generic((x), \
    int: _pa_i, \
    unsigned int: _pa_ui, \
    long: _pa_l, \
    unsigned long: _pa_ul, \
    long long: _pa_ll, \
    unsigned long long: _pa_ull, \
    float: _pa_f, \
    double: _pa_d, \
    char*: _pa_s, \
    const char*: _pa_cs, \
    default: _pa_p \
)(x)

#define PM_A(x)(pm_item_t){ _PA_TYPE(x), _PA_ARG(x) }

#define _PM_END (pm_item_t){ (poly_type_t)-1, {0} }

#define $PM(poly, self, ...) CallPoly((poly), (object_t*)(self), (pm_item_t[]){ __VA_ARGS__, _PM_END })

#endif

#ifdef __cplusplus
}
#endif

#endif
