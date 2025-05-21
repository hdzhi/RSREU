.386                      ; Указываем процессор (Intel 80386)
.model flat,stdcall       ; Модель памяти (плоская) и соглашение вызова (stdcall)
option casemap:none       ; Чувствительность к регистру символов (отключена)

; Подключаем необходимые библиотеки и заголовочные файлы
include C:\masm32\include\windows.inc
include C:\masm32\include\user32.inc
include C:\masm32\include\kernel32.inc
includelib C:\masm32\lib\user32.lib
includelib C:\masm32\lib\kernel32.lib

.data                     ; Начало секции инициализированных данных
ClassName  db "SimpleWinClass",0  ; Имя класса окна (заканчивается нулем)
AppName    db "Window for lab",0  ; Заголовок окна

; Сообщения для MessageBox
hello_mess1  db "left button",0   ; Сообщение при нажатии левой кнопки
hello_mess2  db "right button",0  ; Сообщение при нажатии правой кнопки
hello_title  db "Great!",0        ; Заголовок MessageBox

orange_color DWORD 0000A5FF  ; ColorRef для оранжевого (B=255, G=165, R=0)

; --- Custom Cursor (from file) ---
cursor_file_name db "my_custom_cursor.cur", 0  ; Имя файла курсора (замените на ваше имя)
; custom_cursor_wait  DWORD IDC_WAIT           ; (Удалено, так как больше не используется)

.data?                    ; Начало секции неинициализированных данных
hInstance     HINSTANCE ? ; Дескриптор экземпляра приложения
hInst         HINSTANCE ? ; Альтернативное имя для hInstance
CommandLine   LPSTR ?     ; Командная строка
wc            WNDCLASSEX <?> ; Структура класса окна
msg           MSG <?>     ; Структура сообщения
hwnd          HWND ?      ; Дескриптор главного окна
hCursor       HCURSOR ?     ; Дескриптор текущего курсора

.code                     ; Начало секции кода
start:                    ; Точка входа в программу
    ; Получаем дескриптор текущего модуля
    invoke GetModuleHandle,NULL
    mov  hInstance,eax

    ; Заполняем структуру WNDCLASSEX для регистрации класса окна
    mov  wc.cbSize,SIZEOF WNDCLASSEX      ; Размер структуры
    mov  wc.style,CS_HREDRAW or CS_VREDRAW ; Стиль окна (перерисовка при изменении размера)
    mov  wc.lpfnWndProc,OFFSET WndProc    ; Указатель на процедуру окна
    mov  wc.cbClsExtra,NULL               ; Доп. память для класса
    mov  wc.cbWndExtra,NULL               ; Доп. память для окна
    push hInstance
    pop  wc.hInstance                     ; Дескриптор экземпляра

    ; Загружаем курсор из файла
    invoke LoadCursorFromFile, ADDR cursor_file_name  ; Загружаем курсор из файла
    mov  wc.hCursor, eax           ; Устанавливаем загруженный курсор в структуру класса окна

    ; Устанавливаем оранжевый цвет фона
    mov  wc.hbrBackground,orange_color   ; Цвет фона окна - ОРАНЖЕВЫЙ
    mov  wc.lpszMenuName,NULL             ; Меню (отсутствует)
    mov  wc.lpszClassName,OFFSET ClassName ; Имя класса окна
    ; Регистрируем класс окна
    invoke RegisterClassEx,addr wc

    ; Создаем окно
    INVOKE CreateWindowEx,NULL,ADDR ClassName,ADDR AppName,WS_OVERLAPPEDWINDOW,
           CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
           NULL,NULL,hInst,NULL
    mov  hwnd,eax                         ; Сохраняем дескриптор окна

    ; Показываем и обновляем окно
    invoke ShowWindow,hwnd,SW_SHOWNORMAL
    invoke UpdateWindow,hwnd

    ; Инициализация дескриптора текущего курсора
    ;  Это, по сути, уже сделано при загрузке курсора для класса окна.  Удалим это, чтобы избежать путаницы.
    ;invoke LoadCursor, NULL, IDC_ARROW ; загружаем курсор-стрелку по умолчанию
    ;mov  hCursor, eax; Сохраняем дескриптор

    ; Цикл обработки сообщений
    MSG_LOOP:
        invoke GetMessage,ADDR msg,NULL,0,0 ; Получаем сообщение
        cmp  eax,0                         ; Проверяем на выход
        je   END_LOOP                      ; Если WM_QUIT, выходим
        ; Обработка сообщений, включая изменение курсора
        invoke TranslateMessage,ADDR msg    ; Преобразуем сообщения клавиш
        invoke DispatchMessage,ADDR msg     ; Отправляем в оконную процедуру
        jmp  MSG_LOOP                      ; Повторяем цикл
    
    END_LOOP:
        ; Завершаем программу с кодом возврата из сообщения WM_QUIT
        mov  eax,msg.wParam 
        invoke ExitProcess,eax

; Оконная процедура (обработчик сообщений)
WndProc proc hWnd:HWND,uMsg:UINT,wParam:WPARAM,lParam:LPARAM
    cmp  uMsg,WM_DESTROY    ; Проверяем сообщение о закрытии окна
    je   WMDESTROY          ; Если да, обрабатываем
    cmp  uMsg,WM_LBUTTONDOWN ; Проверяем нажатие левой кнопки мыши
    je   LBUTTON            ; Обрабатываем
    cmp  uMsg,WM_RBUTTONDOWN ; Проверяем нажатие правой кнопки мыши
    je   RBUTTON            ; Обрабатываем

    cmp uMsg, WM_SETCURSOR ; Обработка сообщения WM_SETCURSOR
    je WM_SETCURSOR_HANDLER ; Обрабатываем сообщение WM_SETCURSOR

    JMP  DEFWNDPROC         ; Остальные сообщения - стандартная обработка
    
    WMDESTROY:
        invoke PostQuitMessage,NULL ; Посылаем сообщение WM_QUIT
        xor  eax,eax               ; Возвращаем 0
        jmp  FINISH
    
    LBUTTON:
        ; Показываем MessageBox при нажатии левой кнопки
        invoke MessageBoxA,hwnd,addr hello_mess1,addr hello_title,MB_APPLMODAL
        ; Не нужно менять курсор здесь, т.к. он уже задан для класса окна
        jmp  FINISH
    
    RBUTTON:
        ; Показываем MessageBox при нажатии правой кнопки
        invoke MessageBoxA,hwnd,addr hello_mess2,addr hello_title,MB_OK
        ; Не нужно менять курсор здесь, т.к. он уже задан для класса окна
        jmp  FINISH
        
    WM_SETCURSOR_HANDLER:  ; Обработчик сообщения WM_SETCURSOR
        ;  Изменяем курсор на стрелку (или другой выбранный курсор)
       invoke SetCursor, wc.hCursor ; Используем курсор, установленный для класса
       mov eax, TRUE ; Сообщаем системе, что курсор уже установлен
       jmp FINISH

    DEFWNDPROC:
        ; Стандартная обработка сообщений
        invoke DefWindowProc,hWnd,uMsg,wParam,lParam
    
    FINISH:
        ret
WndProc endp

end start  ; Конец программы, точка входа - start