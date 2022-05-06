#include <chrono>
#include <iomanip>
#include <iostream>
#include <format>
#include <sstream>
#include <thread>

#include <atlimage.h>
#include <Windows.h>

using namespace std;

void SendKey(const unsigned char& code)
{
	keybd_event(code, 0x00, KEYEVENTF_EXTENDEDKEY | 0, 0);
	keybd_event(code, 0x00, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}

HBITMAP ScreenShot()
{
	const HDC hScreenDC = GetDC(nullptr);
	const HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
	const int width = GetDeviceCaps(hScreenDC, HORZRES);
	const int height = GetDeviceCaps(hScreenDC, VERTRES);

	HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);
	HBITMAP hOldBitmap = static_cast<HBITMAP>(SelectObject(hMemoryDC, hBitmap));
	BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, 0, 0, SRCCOPY);
	hBitmap = static_cast<HBITMAP>(SelectObject(hMemoryDC, hOldBitmap));

	DeleteDC(hMemoryDC);
	DeleteDC(hScreenDC);

	return hBitmap;
}

void SaveImage(const string& target_directory, const string& file_index, const int iteration, const HBITMAP& hBitmap) {
	ostringstream sout;
	sout << target_directory << file_index << '_' << setfill('0') << setw(5) << iteration << ".bmp";
	string target_string = sout.str();
	wstring target_path(begin(target_string), end(target_string));

	CImage image;
	image.Attach(hBitmap);
	image.Save(target_path.c_str());
	image.Detach();

	cout << "Saved File -> " << target_string << endl;
}

int main()
{
	string target_directory;
	string file_index;
	int max_iteration;

	cout << "target directory: ";
	cin >> target_directory;
	cout << endl;

	cout << "file index: ";
	cin >> file_index;
	cout << endl;

	cout << "max iteration: ";
	cin >> max_iteration;
	cout << endl;

	cout << "Start after 10s" << endl;
	this_thread::sleep_for(chrono::seconds(10));

	cout << "[START]" << endl;
	
	for (int i = 1; i <= max_iteration; ++i) {
		const HBITMAP hBitmap = ScreenShot();
		SaveImage(target_directory, file_index, i, hBitmap);
		this_thread::sleep_for(chrono::seconds(1));
		SendKey(VK_RIGHT);
		
		if ((GetAsyncKeyState(VK_SPACE) | GetAsyncKeyState(VK_ESCAPE)) & 0x01) {
			break;
		}
		this_thread::sleep_for(chrono::seconds(3));
	}

	cout << "[END]" << endl;
}