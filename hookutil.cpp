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
