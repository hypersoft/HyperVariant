/*

Sun Feb 16 21:50:41 CST 2014

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

#define HyperVariant_c
#include "HyperVariant.h"
#undef HyperVariant_c

typedef struct sHyperVariant {
	void * private; size_t type;
	size_t note; size_t bytes;
	char data[];
} iHyperVariant;

HyperVariant varcreate(size_t bytes, double data, HyperVariantType type)
{
	iHyperVariant * var; void * ptr = ptrval(data);
	if (type & (HVT_UTF8)) {
		if (bytes == 0) bytes = strlen(ptr);
		bytes++;
	} else
	if (type & HVT_UTF16) {
		if (bytes == 0) bytes = strlen(ptr);
		bytes += sizeof(uint16_t);
	} else
	if (type & HVT_UTF32) {
		if (bytes == 0) bytes = (wcslen(ptr)*sizeof(wchar_t)) + sizeof(wchar_t);
		else bytes += sizeof(wchar_t);
	}
	var = malloc(sizeof(iHyperVariant) + bytes);
	if (var) {
		var->note = 0, var->private = 0, var->type = type, var->bytes = bytes;
		if (type & HVT_UTF8) var->data[--bytes] = 0,
			memcpy(var->data, ptr, bytes);
		else if (type & HVT_POINTER || type & HVT_NUMBER)	varptr(var->data) = ptr;
		else if (type & HVT_DOUBLE)	vardouble(var->data) = data;
		else if (type & HVT_BLOCK) memcpy(var->data, ptr,  bytes);
		else if (type & HVT_UTF16) {
			* varop(-, uint16_t, var->data+bytes, 1) = 0,
			memcpy(var->data, ptr, bytes - sizeof(uint16_t));
		} else if (type & HVT_UTF32) {
			* varop(-, wchar_t, var->data+bytes, 1) = 0,
			memcpy(var->data, ptr,  bytes - sizeof(wchar_t));
		}
		return var->data;
	} return NULL;
}

