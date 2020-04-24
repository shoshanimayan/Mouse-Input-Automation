
#include <iostream>
#include <Windows.h>
#include <stdio.h>
const int maxLen = 100;

struct Macro {

    int SleepTime;
    int SleepTimeBeforeClick;
    int MacroIndex;
    POINT CursorPosition[maxLen];

};

void MouseClick() {
    INPUT Input = { 0 };
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &Input, sizeof(INPUT));

    ZeroMemory(&Input, sizeof(INPUT));
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &Input, sizeof(INPUT));


}

void InsertNewMacroPosition(Macro* macro) {
    if (macro->MacroIndex + 1 < maxLen) {
        macro->MacroIndex++;
        GetCursorPos(&macro->CursorPosition[macro->MacroIndex]);
        std::cout << "New Macro position added" << std::endl;
    }
}
void ExecuteMacro(Macro* macro) {
    for (int i = 0; i < macro->MacroIndex + 1; i++) {
        SetCursorPos(macro->CursorPosition[i].x, macro->CursorPosition->y);
        Sleep(macro->SleepTimeBeforeClick);
        MouseClick();
        Sleep(macro->SleepTime);

    }

}

Macro CreateMacro(int sleepBeforeClick, int sleep) {
    Macro macro;
    macro.SleepTime = sleep;
    macro.SleepTimeBeforeClick = sleepBeforeClick;
    macro.MacroIndex = -1;
    return macro;

}

int main()
{

    bool macroInsertDone=true;
    bool execMacroDone = true;

    Macro m = CreateMacro(50, 50);
    while (true) {
        if (GetAsyncKeyState('s'))
            macroInsertDone = false;
        else if (!GetAsyncKeyState('s')) {
            if (!macroInsertDone)
                InsertNewMacroPosition(&m);
            macroInsertDone = true;
        }
        if (GetAsyncKeyState('Q'))
            execMacroDone = false;
        else if (!GetAsyncKeyState('Q')) {
            if (!execMacroDone)
                ExecuteMacro(&m);
            execMacroDone = true;
        }
        Sleep(5);
    }

    return 0;

}

