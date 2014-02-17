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
	size_t size; size_t length;
	char data[];
} HyperVariant;


void * varcreate(size_t length, double data, HyperVariantType type)
{
	HyperVariant * var; void * ptr = ptrVar(data);
	if (type & HVT_UTF8) {
		if (length == 0 && ptr) length = strlen(ptr); length++;
	}
	var = malloc(sizeof(HyperVariant) + length);
	if (type & HVT_UTF8)  var->data[length--] = 0;
	if (var) { var->type = type, var->length = 1;
		if (type & HVT_POINTER || type & HVT_INT) {
			var->size = sizeof(uint), ptrPtrVal(var->data) = ptr;
		} else if (type & HVT_DOUBLE) {
			var->size = sizeof(double),	dblPtrVal(var->data) = data;
		} else if (type & HVT_UTF8) {
			var->size = 1; memcpy(var->data, ptr, (var->length = length));
		} else if (type & HVT_BLOCK) {
			memcpy(var->data, ptr, (var->size = length));
		}
	}
	return var->data;
}

