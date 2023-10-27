.586P
.MODEL FLAT, STDCALL
includelib kernel32.lib

ExitProcess PROTO : DWORD
MessageBoxA PROTO : DWORD, : DWORD, : DWORD, : DWORD
;MessageBox PROTO hwnd:DWORD, lpText:DWORD, lpCaption:DWORD, 

.STACK 4096

.CONST
NULL equ 0
MB_OK equ 0
MB_OKCANCEL equ 1
MB_YESNO equ 4

.DATA
msgBoxCaption db "Пример окна сообщения",0
msgBoxText db "Текст окна!",0


.CODE

Main:
INVOKE MessageBoxA, NULL, ADDR MsgBoxText, ADDR MsgBoxCaption, MB_YESNO
INVOKE ExitProcess, NULL
end Main