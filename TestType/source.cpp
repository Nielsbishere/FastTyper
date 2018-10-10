#include <Windows.h>
#include <WinUser.h>
#include <string>

void press(int i) {

	INPUT input;
	ZeroMemory(&input, sizeof(input));
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = i;

	SendInput(1, &input, sizeof(INPUT));

}

void release(int i) {

	INPUT input;
	ZeroMemory(&input, sizeof(input));
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = i;
	input.ki.dwFlags = KEYEVENTF_KEYUP;

	SendInput(1, &input, sizeof(INPUT));

}

void typeOne(int i) {
	press(i);
	release(i);
}

void typeShift(int i) {

	press(VK_SHIFT);
	press(i);
	release(i);
	release(VK_SHIFT);

}

void typeKey(char c) {

	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z'))
		typeOne(toupper(c));
	else if (c >= 'A' && c <= 'Z')
		typeShift(c);
	else if (c == ',')
		typeOne(VK_OEM_COMMA);
	else if (c == ' ')
		typeOne(VK_SPACE);
	else if (c == '!')
		typeShift('1');
	else if (c == '?')
		typeShift(VK_OEM_2);
	else if (c == '\'')
		typeOne(VK_OEM_7);
	else if (c == '"')
		typeShift(VK_OEM_7);
	else if (c == '.')
		typeOne(VK_OEM_PERIOD);
	else if (c == '-')
		typeOne(VK_OEM_MINUS);
	else if (c == ';')
		typeOne(VK_OEM_1);
	else if (c == ':')
		typeShift(VK_OEM_1);
	else if (c == '(')
		typeShift('9');
	else if (c == ')')
		typeShift('0');
	else if (c == '`')
		typeOne(VK_RETURN);
	else if (c == '@')
		typeShift('2');

}

void type(const char *str, DWORD ms) {

	size_t len = strlen(str);

	for (size_t i = 0; i < len; ++i) {
		typeKey(str[i]);
		Sleep(ms);
	}

}

int main(int argc, char *argv[]) {

	if (argc < 4) {
		printf("Usage: TestType waitTime(ms) typeInterval(ms) loops <text>");
		return 1;
	}

	int wait = std::stoi(argv[1]);
	int speed = std::stoi(argv[2]);
	int loops = std::stoi(argv[3]);

	Sleep(wait);

	for (int j = 0; j < loops; ++j)
		for (int i = 4; i < argc; ++i) {
			type(argv[i], speed);
			if(i != argc - 1) type(" ", speed);
		}

	return 0;

}