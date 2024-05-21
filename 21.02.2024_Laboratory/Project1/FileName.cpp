#include <windows.h>
#include <tchar.h>
#include "resource.h"

static HWND hChildWnd1 = NULL;
static HWND hChildWnd2 = NULL;
static HWND hChildWnd3 = NULL;

INT_PTR CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);

INT_PTR CALLBACK ChildDlgProc(HWND hChildWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpszCmdLine, int nCmdShow)
{
    return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

INT_PTR CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp)
{
    switch (mes)
    {
    case WM_INITDIALOG:
    {

    }
    break;
    case WM_COMMAND:
    {
        switch (LOWORD(wp))
        {
        case IDC_BUTTON1:
        {
            if (hChildWnd1 == NULL)
            {
                hChildWnd1 = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), hWnd, (DLGPROC)ChildDlgProc);

                if (hChildWnd1 != NULL)
                {
                    ShowWindow(hChildWnd1, SW_SHOW);
                }
            }
            else
            {
                ShowWindow(hChildWnd1, SW_SHOW);
            }
        }
        break;
        case IDC_BUTTON2:
        {
            if (hChildWnd2 == NULL)
            {
                hChildWnd2 = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), hWnd, (DLGPROC)ChildDlgProc);

                if (hChildWnd2 != NULL)
                {
                    ShowWindow(hChildWnd2, SW_SHOW);
                }
            }
            else
            {
                ShowWindow(hChildWnd2, SW_SHOW);
            }
        }
        break;
        case IDC_BUTTON3:
        {
            if (hChildWnd3 == NULL)
            {
                hChildWnd3 = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), hWnd, (DLGPROC)ChildDlgProc);

                if (hChildWnd3 != NULL)
                {
                    ShowWindow(hChildWnd3, SW_SHOW);
                }
            }
            else
            {
                ShowWindow(hChildWnd3, SW_SHOW);
            }
        }
        break;
        case IDC_BUTTON4:
        {
            HWND hEdit = GetDlgItem(hWnd, IDC_EDIT1);
            if (hEdit != NULL)
            {
                int textLength = GetWindowTextLength(hEdit);
                if (textLength > 0)
                {
                    TCHAR* buffer = new TCHAR[textLength + 1];
                    GetWindowText(hEdit, buffer, textLength + 1);

                    HWND hList1 = GetDlgItem(hChildWnd1, IDC_LIST2);
                    HWND hList2 = GetDlgItem(hChildWnd2, IDC_LIST2);
                    HWND hList3 = GetDlgItem(hChildWnd3, IDC_LIST2);

                    if (hList1 != NULL || hList2 != NULL || hList3 != NULL)
                    {
                        SendMessage(hList1, LB_ADDSTRING, 0, (LPARAM)buffer);
                        SendMessage(hList2, LB_ADDSTRING, 0, (LPARAM)buffer);
                        SendMessage(hList3, LB_ADDSTRING, 0, (LPARAM)buffer);

                    }

                    delete[] buffer;
                    SetWindowText(hEdit, _T(""));
                }
            }
        }
        break;
        }
    }
    break;
    case WM_CLOSE:
    {
        EndDialog(hWnd, 0);
        return TRUE;
    }
    }
    return FALSE;
}

INT_PTR CALLBACK ChildDlgProc(HWND hChildWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDC_BUTTON1:
        {
            HWND hChildEdit = GetDlgItem(hChildWnd, IDC_EDIT2);
            if (hChildEdit != NULL)
            {
                int textLength = GetWindowTextLength(hChildEdit);
                if (textLength > 0)
                {
                    TCHAR* buffer = new TCHAR[textLength + 1];
                    GetWindowText(hChildEdit, buffer, textLength + 1);

                    HWND hwnd = GetParent(hChildWnd);

                    HWND hList = GetDlgItem(hwnd, IDC_LIST1);
                    if (hList != NULL)
                    {
                        SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)buffer);
                    }

                    delete[] buffer;
                    SetWindowText(hChildEdit, _T(""));
                }
            }
        }
        break;
        case IDC_BUTTON2:
        {
            EndDialog(hChildWnd, 0);
            hChildWnd = NULL;
            return (INT_PTR)TRUE;
        }
        }
    }
    break;

    case WM_CLOSE:
        EndDialog(hChildWnd, 0);
        hChildWnd = NULL;
        return (INT_PTR)TRUE;
    }
    return (INT_PTR)FALSE;
}