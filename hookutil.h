#ifndef HOOKUTIL_H
#define HOOKUTIL_H

#ifdef _WIN32
#include <windows.h>
#endif

int startMouseHook();

bool stopMouseHook();

#endif // HOOKUTIL_H
