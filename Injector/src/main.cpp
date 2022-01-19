#include <iostream>
#include <filesystem>
#include <cstring>
#include <thread>
#include <chrono>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <tlhelp32.h>
#include <processthreadsapi.h>
#include <libloaderapi.h>
#include <memoryapi.h>
#include <processthreadsapi.h>
#include <errhandlingapi.h>
#include <winuser.h>

using namespace std::chrono_literals;

char rand_char()
{
  return 'a' + rand() % 26;
}

DWORD get_proc(const char *name)
{
  HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  PROCESSENTRY32 pe32;
  if (hProcessSnap == INVALID_HANDLE_VALUE)
  {
    std::cout << "CreateToolhelp32Snapshot failed" << std::endl;
    return 0;
  }
  DWORD pid = 0;
  pe32.dwSize = sizeof(PROCESSENTRY32);
  if (Process32First(hProcessSnap, &pe32))
  {
    if (strcmp(name, pe32.szExeFile) == 0)
      pid = pe32.th32ProcessID;
    else
    {
      while (Process32Next(hProcessSnap, &pe32))
      {
        if (strcmp(name, pe32.szExeFile) == 0)
        {
          pid = pe32.th32ProcessID;
          break;
        }
      }
    }
    CloseHandle(hProcessSnap);
  }
  return pid;
}

std::string last_error_as_str()
{
  DWORD errorMessageID = GetLastError();
  if (errorMessageID == 0)
  {
    return std::string();
  }
  LPSTR messageBuffer = nullptr;
  size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                               NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
  std::string message(messageBuffer, size);
  LocalFree(messageBuffer);
  return message;
}

int main(int argc, char *argv[])
{
  if (argc < 3)
  {
    std::filesystem::path p(argv[0]);
    std::cout << "Usage: " << p.filename().generic_string() << " <Path to DLL> <Window Name>" << std::endl;
    return 1;
  }

  std::filesystem::path dll(argv[1]);
  dll = std::filesystem::absolute(dll);

  std::cout << "Waiting for process..." << std::endl;
  DWORD proc_id = 0;
  while (proc_id = get_proc(argv[2]), proc_id == 0)
  {
    std::this_thread::sleep_for(1s);
  }
  std::cout << "Found " << argv[2] << " with pid " << proc_id << std::endl;
  srand(static_cast<unsigned int>(time(NULL)));
  std::filesystem::path temp_dll = std::filesystem::temp_directory_path();
  std::string temp_filename = "WI_";
  for (unsigned short i = 0; i < 4 + (rand() % 8); i++)
    temp_filename += rand_char();
  temp_filename += ".dll";
  temp_dll.append(temp_filename);
  const char *temp_dll_bytes = temp_dll.generic_string().c_str();
  unsigned short temp_dll_length = strlen(temp_dll_bytes);
  std::filesystem::copy(dll, temp_dll);

  HANDLE proc = OpenProcess(PROCESS_ALL_ACCESS, false, proc_id);
  LPTHREAD_START_ROUTINE lla_addr = (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
  std::this_thread::sleep_for(1s);
  void *filename_ptr = VirtualAllocEx(proc, NULL, temp_dll.generic_string().length(), MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
  WriteProcessMemory(proc, filename_ptr, temp_dll_bytes, temp_dll.generic_string().length(), 0);
  CreateRemoteThread(proc, NULL, 0, lla_addr, filename_ptr, 0, NULL);
  std::this_thread::sleep_for(1s);
  CloseHandle(proc);
  std::cout << "Injected, Goodbye." << std::endl;
}