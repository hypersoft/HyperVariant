HyperVariant
============

It's time to kick ass and chew bubblegum. Here's a pack of "double int" gum...

[Wikipedia Variant Article](http://en.wikipedia.org/wiki/Variant_type)

"Variant is a data type in certain programming languages, particularly Visual Basic, OCaml, and C++ when using the Component Object Model."
***

### This ain't no OOPS ###
Ahh, the variant. Highly utilitarian. Great for optimizaiton. For example, string data. You pass a string around,
from API, which passess it to yet another API, all the while, each procedure scanning the bytes of the string...
tsk..tsk...tsk... What a horrible mess. At least YOU can implement some wisdom by using this data type, wherefore,
you don't need to scan for length, its been cached for you. You've also been given a few bits to store flags, and in extreme cases, you've also got private data. While this does eat up 128-bits of header space, (or more *= 2 in 64-bit systems) the added performance and property association, is well worth it for systems that heavily depend on data properties.

### It's more than what you think... ###
Casting. Always so ugly looking. This project brings to the table, never before seen macros that make neat little mnemonics (that actually make sense) out of the most important data types. Pointers as integers, integers as pointers, all on demand. Cast away my good fellow, the ball is now in your court, and when you go to read your play book, you won't be sitting there thinking WTF does this code actually "say", because you've already said it. Have a look at the dissasembly of a few of these macros accessing the variant. You will find, these macros indeed produce fairly effective machine code, that seems to be more legible than what GCC normally spits out.

<pre>
C:
printf("Length: %i; value: %s\n", varlen(var), var);

ASM:
0x08048567  <main+71>:  mov    eax,DWORD PTR [esp+0x2c]
0x0804856b  <main+75>:  sub    eax,0x4
0x0804856e  <main+78>:  mov    eax,DWORD PTR [eax]
0x08048570  <main+80>:  mov    edx,DWORD PTR [esp+0x2c]
0x08048574  <main+84>:  mov    DWORD PTR [esp+0x8],edx
0x08048578  <main+88>:  mov    DWORD PTR [esp+0x4],eax
0x0804857c  <main+92>:  mov    DWORD PTR [esp],0x80489f0
0x08048583  <main+99>:  call   0x8048390 <printf@plt>
</pre>

Quick, clean, and efficient. Think about that for a second... If we did this in standard programming, you'd have to scan that string before you could print its length and the value. We've practically done both here for "nothing".
