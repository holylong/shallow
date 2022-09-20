// MIT License

// Copyright (c) 2022 hooy

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "hookutil.h"
#include <mousehistory.h>
#include <QDebug>

static HHOOK hMouseHook = NULL;

HMODULE ModuleFromAddress(PVOID pv)
{
    MEMORY_BASIC_INFORMATION mbi;
    if (VirtualQuery(pv, &mbi, sizeof(mbi)) != 0)
    {
        return (HMODULE)mbi.AllocationBase;
    }
    else
    {
        return NULL;
    }
}

bool stopMouseHook()
{
    if (hMouseHook == NULL)
    {
        return FALSE;
    }
    UnhookWindowsHookEx(hMouseHook);
    hMouseHook = NULL;
    return TRUE;
}
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if(HC_ACTION == nCode){
        if (WM_LBUTTONDOWN == wParam || WM_RBUTTONDOWN == wParam
                        || WM_MBUTTONDOWN == wParam)
        {
            if (MouseHistory::instance())
            {
                MouseHistory::instance()->setPressEvent(1);
            }
        }

        if (WM_LBUTTONUP == wParam || WM_RBUTTONUP == wParam
                        || WM_MBUTTONUP == wParam)
        {
            if (MouseHistory::instance())
            {
                MouseHistory::instance()->setPressEvent(2);
            }
        }


        if (MouseHistory::instance())
        {
            PMSLLHOOKSTRUCT p = (PMSLLHOOKSTRUCT)lParam;
            MouseHistory::instance()->setPosValue(p->pt.x, p->pt.y);
        }
    }
    return CallNextHookEx(hMouseHook, nCode, wParam, lParam);
}

BOOL startMouseHook()
{
    if (hMouseHook != NULL)
    {
        return FALSE;
    }
    hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, ModuleFromAddress((PVOID)MouseProc), NULL);
    if (NULL == hMouseHook)
    {
        qDebug() << "regiter hook for mouse failed";
        return FALSE;
    }
    return TRUE;
}
