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
	HVT_NUMBER = 1 << 1,
	HVT_DOUBLE = 1 << 2,
	HVT_POINTER = 1 << 3,
	HVT_BLOCK = 1 << 4,
	HVT_UTF8 = 1 << 5, HVT_UCS1 = HVT_UTF8,
	HVT_UTF16 = 1 << 6,	HVT_UCS2 = HVT_UTF16,
	HVT_UTF32 = 1 << 7, HVT_UCS4 = HVT_UTF32,
} HyperVariantType;

#define varlea(index, type, address) (type*) ((index * sizeof(type)) + address)

#define ptrval(d) ((void*)(size_t)(d))
#define dblval(i) ((double)(size_t)(i))

#define numvar(i) sizeof(size_t), dblval(i), HVT_NUMBER
#define ptrvar(p) sizeof(void *), dblval(p), HVT_POINTER
#define dblvar(d) sizeof(double), d, HVT_DOUBLE
#define utf8var(p, l) l, dblval(p), HVT_UTF8
#define utf16var(p, b) b, dblval(p), HVT_UTF16
#define utf32var(p, b) b, dblval(p), HVT_UTF32
#define blkvar(p, b) b, dblval((void*)p), HVT_BLOCK

#define varhead(v) (v - (sizeof(size_t) << 2))

#define vardouble(p) *(double*)(p)
#define varnum(p) *(size_t*)(p)
#define varptr(p) *(void**)(p)
#define varprvt(p) *(void**)varhead(p)
#define varprvti(p) *(size_t*)varhead(p)
#define varnote(p) *(size_t*)(p - (sizeof(size_t) << 1))
#define varbytes(p) *(size_t*)(p - sizeof(size_t))
#define vartype(p) * (size_t*)(varhead(p)+sizeof(size_t))
#define varpadding(p) ((vartype(p) & (HVT_UTF8 | HVT_UTF16 | HVT_UTF32)) >> 5)

#define varlen(p) \
((vartype(p) & (HVT_UTF8 | HVT_UTF16 | HVT_UTF32)) ? varucslen(p) : varbytes(p))

#define varimpact(v)                                                           \
((v) ? (sizeof(size_t) << 2) + varbytes(v) : 0L)

#define varfree(v) free(varhead(v)); v = NULL

typedef void * HyperVariant;

#ifndef HyperVariant_c
extern size_t varucslen(register void * p);
extern HyperVariant varcreate
(
	size_t bytes,
	double data,
	HyperVariantType type
);
#endif

#endif
