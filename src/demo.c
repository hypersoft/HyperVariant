/*

Sun Feb 16 22:03:03 CST 2014

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

#include "HyperVariant.h"
#include <stdio.h>

int main ( int argc, char **argv )
{
	/* Setup shop, elbow drop from the top */
	HyperVariant var = varcreate(utf8var("Hello World!", 0));

	puts("Testing immediate string data (Hello World!)...");
	printf("Length: %i; value: %s\n", varlen(var), var);
	printf("string impact: %i\n", varimpact(var));
	puts("cleaning up...");
	varfree(var);

	printf("\n");

	var = varcreate(utf8var(argv[0], 0));
	puts("Testing static string data (argv[0])...");
	printf("Length: %i; Value: %s\n", varlen(var), var);
	printf("Total Impact: %i\n", varimpact(var));
	puts("cleaning up...");
	varfree(var);

	printf("\n");

	var = varcreate(lngvar(255));
	puts("Testing integer data (255)...");
	printf("Length: %i; Value: %i\n", varlen(var), varlong(var));
	printf("Total Impact: %i\n", varimpact(var));
	puts("cleaning up...");
	varfree(var);

	printf("\n");

	var = varcreate(dblvar(1234.5678));
	puts("Testing double data (1234.5678)...");
	printf("Length: %i; Value: %.8g\n", varlen(var), vardouble(var));
	printf("Total Impact: %i\n", varimpact(var));
	puts("While we have a variant, test the private data...");
	varprvt(var) = argv[0];
	if (varprvt(var) != argv[0]) puts("uhhh.. private data doesn't match up..");
	else puts("Good to go..");
	puts("cleaning up...");
	varfree(var);

	printf("\nI'd say she's in good working order captain...\n\n");

	return 0;
}
