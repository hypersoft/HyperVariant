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
#include <wchar.h>
#include <inttypes.h>

typedef enum eHyperVariantType {
	HVT_LONG = 1 << 1,
	HVT_DOUBLE = 1 << 2,
	HVT_POINTER = 1 << 3,
	HVT_BLOCK = 1 << 4,
	HVT_UTF8 = 1 << 5, HVT_UCS1 = HVT_UTF8,
	HVT_UTF16 = 1 << 6,	HVT_UCS2 = HVT_UTF16,
	HVT_UTF32 = 1 << 7, HVT_UCS4 = HVT_UTF32,
} HyperVariantType;

#define ptrVar(d) ((void*)(size_t)(d))
#define dblInt(i) ((double)(size_t)(i))

#define intVal(i) sizeof(size_t), dblInt(i), HVT_LONG
#define ptrVal(p) sizeof(void *), dblInt(p), HVT_POINTER
#define dblVal(d) sizeof(double), d, HVT_DOUBLE

#define strVal(s, l) l, dblInt(s), HVT_UTF8
#define blkVal(b, s) s, dblInt((void*)b), HVT_BLOCK

#define blkPtr(t, p) ((t*)(p))

#define intPtr(p) blkPtr(size_t, p)
#define intPtrVal(p) *intPtr(p)

#define ptrPtr(p) blkPtr(void*, p)
#define ptrPtrVal(p) *ptrPtr(p)

#define dblPtr(p) blkPtr(double, p)
#define dblPtrVal(p) *dblPtr(p)

#define strPtr(p) blkPtr(char, p)
#define strPtrVal *strPtr(p)

#define varop(op, type, variant, index) \
	(type*)(variant op (index) ? (index * sizeof(type)) : 0)

#define varprev(type, variant, index) varop( -, type, variant, index)
#define varindex(type, variant, index) varop( +, type, variant, index)

#define varhead(v) (v - (sizeof(size_t) << 2))

#define varfree(v) free(varhead(v)); v = NULL
#define varprvt(v) *(void**)varhead(v)
#define varprvti(v) *(size_t*)varhead(v)
#define varnote(v) *(size_t*)(v - (sizeof(size_t) << 1))
#define varbytes(v) *(size_t*)(v - sizeof(size_t))
#define vartype(v) *(varprev(size_t, v, 3))
#define varpadding(v) ((vartype(v) & (HVT_UTF8 | HVT_UTF16 | HVT_UTF32)) >> 5)
#define varlen(v) (varbytes(v) - varpadding(v))

#define varimpact(v)                                                           \
((v) ? (sizeof(size_t) << 2) + varbytes(v) : 0L)

typedef void * HyperVariant;

#ifndef HyperVariant_c
extern HyperVariant varcreate
(
	size_t bytes,
	double data,
	HyperVariantType type
);
#endif

#endif
