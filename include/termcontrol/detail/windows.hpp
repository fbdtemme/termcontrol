#pragma once

#include <cstdio>
#include <cwchar>
#include <stdexcept>
#include <fmt/format.h>

#define WIN32_LEAN_AND_MEAN
#ifdef NOMINMAX
#include <windows.h>
#else
#define NOMINMAX
#include <windows.h>
#undef NOMINMAX
#endif

namespace termcontrol {

class win32_terminal_error: public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class win32_terminal {
private:
    static constexpr DWORD vt_out_modes = ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;
    static constexpr DWORD vt_in_modes = ENABLE_VIRTUAL_TERMINAL_INPUT;

public:
    win32_terminal()
    {
        handle_out_ = GetStdHandle(STD_OUTPUT_HANDLE);
        handle_in_ = GetStdHandle(STD_INPUT_HANDLE);
        original_in_cp_ = GetConsoleCP();
        original_out_cp_ = GetConsoleOutputCP();

        if (handle_out_ == INVALID_HANDLE_VALUE) {
            throw win32_terminal_error(format_error("Invalid output handle value"));
        }
        if (handle_in_ == INVALID_HANDLE_VALUE) {
            throw win32_terminal_error(format_error("Invalid input handle value"));
        }
        if (original_in_cp_ == 0) {
            throw win32_terminal_error(format_error("Could not get console input code point"));
        }
        if (original_out_cp_ == 0) {
            throw win32_terminal_error(format_error("Could not get console input code point"));
        }

        if (!GetConsoleMode(handle_out_, &original_out_mode_)) {
            throw win32_terminal_error(format_error("Could not retrieve output console mode"));
        }
        if (!GetConsoleMode(handle_in_, &original_in_mode_)) {
            throw win32_terminal_error(format_error("Could not retrieve input console mode"));
        }
    }

    void enable_utf8() {
        if (!SetConsoleOutputCP(CP_UTF8)) {
            throw win32_terminal_error(format_error("Could not set console output code point"));
        }
        if (!SetConsoleCP(CP_UTF8)) {
            throw win32_terminal_error(format_error("Could not set console input code point"));
        }
    }

    void restore_codepoint() {
        if (!SetConsoleOutputCP(original_out_cp_)) {
            throw win32_terminal_error(format_error("Could not restore console output code point"));
        }
        if (!SetConsoleCP(original_in_cp_)) {
            throw win32_terminal_error(format_error("Could not restore console input code point"));
        }
    }

    void enable_virtual_terminal_processing() {
        DWORD out_mode = original_out_mode_ | vt_out_modes;
        if (! SetConsoleMode(handle_out_, out_mode)) {
            throw win32_terminal_error(format_error("Could not set console output mode"));
        }

        DWORD in_mode = original_in_mode_ | vt_in_modes;
        if (!SetConsoleMode(handle_in_, in_mode)) {
            throw win32_terminal_error(format_error("Could not set console input mode"));
        }
    }

    void restore_console_mode() {
        DWORD out_mode = original_out_mode_;
        if (! SetConsoleMode(handle_out_, out_mode)) {
            throw win32_terminal_error(format_error("Could not restore console output mode"));
        }

        DWORD in_mode = original_in_mode_;
        if (!SetConsoleMode(handle_in_, in_mode)) {
            throw win32_terminal_error(format_error("Could not restore console input mode"));
        }
    }

    //Returns the last Win32 error, in string format. Returns an empty string if there is no error.
    static std::string get_win32_error()
    {
        //Get the error message ID, if any.
        DWORD errorMessageID = ::GetLastError();
        if(errorMessageID == 0) {
            return {}; //No error message has been recorded
        }

        LPSTR messageBuffer = nullptr;

        //Ask Win32 to give us the string version of that message ID.
        //The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
        size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

        //Copy the error message into a std::string.
        std::string message(messageBuffer, size);

        //Free the Win32's string's buffer.
        LocalFree(messageBuffer);

        return message;
    }

    static std::string format_error(std::string_view format_str) {
        auto msg = get_win32_error();
        return fmt::format(fmt::runtime(format_str), msg);
    }


private:
    HANDLE handle_out_ = nullptr;
    HANDLE handle_in_ = nullptr;

    DWORD original_out_mode_ = 0;
    DWORD original_in_mode_ = 0;

    UINT original_in_cp_ = 0;
    UINT original_out_cp_ = 0;
};


} // namespace termcontrol