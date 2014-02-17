/*

Sun Feb 16 21:50:44 CST 2014

Copyright (c) 2014, Triston J. Taylor
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice, this
  list of conditions and the following disclaimer in the documentation and/or
  other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#ifndef HyperVariant_h
#define HyperVariant_h

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

typedef enum eHyperVariantType {
	HVT_INT = 1 << 1,
	HVT_DOUBLE = 1 << 2,
	HVT_POINTER = 1 << 3,
	HVT_UTF8 = 1 << 4,
	HVT_BLOCK = 1 << 5,
} HyperVariantType;

#define ptrVar(d) ((void*)(uint)(d))
#define dblInt(i) ((double)(uint)(i))

#define intVal(i) sizeof(uint), dblInt(i), HVT_INT
#define ptrVal(p) sizeof(void *), dblInt(p), HVT_POINTER
#define dblVal(d) sizeof(double), d, HVT_DOUBLE

#define strVal(s, l) l, dblInt(s), HVT_UTF8
#define blkVal(b, s) s, dblInt((void*)b), HVT_BLOCK

#define blkPtr(t, p) ((t*)(p))

#define intPtr(p) blkPtr(uint, p)
#define intPtrVal(p) *intPtr(p)

#define ptrPtr(p) blkPtr(void*, p)
#define ptrPtrVal(p) *ptrPtr(p)

#define dblPtr(p) blkPtr(double, p)
#define dblPtrVal(p) *dblPtr(p)

#define strPtr(p) blkPtr(char, p)
#define strPtrVal *strPtr(p)

#define varfree(v) free(intPtr(v - ((sizeof(size_t) << 1) << 1))); v = NULL
#define varsize(v) intPtrVal(v - (sizeof(size_t) << 1))
#define varlen(v) intPtrVal(v - sizeof(size_t))
#define vartype(v) intPtrVal(v - (sizeof(size_t) | (sizeof(size_t) << 1)))

#ifndef HyperVariant_c
	#define HyperVariantLinkage extern
	typedef void * HyperVariant;
	HyperVariant varcreate(size_t length, double data, HyperVariantType type);
#endif

#undef HyperVariantLinkage

#endif
