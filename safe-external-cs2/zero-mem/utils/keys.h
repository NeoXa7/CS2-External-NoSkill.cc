#pragma once

static const char* KeyNames[] = {
    "None",
    "Left Mouse",
    "Right Mouse",
    "Cancel",
    "Middle Mouse",
    "Mouse 4",
    "Mouse 5",
    "Unknown",
    "Backspace",
    "Tab",
    "Unknown",
    "Unknown",
    "Clear",
    "Enter",
    "Unknown",
    "Unknown",
    "Shift",
    "Ctrl",
    "Alt",
    "Pause",
    "Caps Lock",
    "Kana",
    "Unknown",
    "Junja",
    "Final",
    "Kanji",
    "Unknown",
    "Escape",
    "Convert",
    "Non Convert",
    "Accept",
    "Mode Change",
    "Space",
    "Page Up",
    "Page Down",
    "End",
    "Home",
    "Left Arrow",
    "Up Arrow",
    "Right Arrow",
    "Down Arrow",
    "Select",
    "Print",
    "Execute",
    "Print Screen",
    "Insert",
    "Delete",
    "Help",
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "U",
    "V",
    "W",
    "X",
    "Y",
    "Z",
    "Left Windows",
    "Right Windows",
    "Apps",
    "Unknown",
    "Sleep",
    "Numpad 0",
    "Numpad 1",
    "Numpad 2",
    "Numpad 3",
    "Numpad 4",
    "Numpad 5",
    "Numpad 6",
    "Numpad 7",
    "Numpad 8",
    "Numpad 9",
    "Multiply",
    "Add",
    "Separator",
    "Subtract",
    "Decimal",
    "Divide",
    "F1",
    "F2",
    "F3",
    "F4",
    "F5",
    "F6",
    "F7",
    "F8",
    "F9",
    "F10",
    "F11",
    "F12",
    "F13",
    "F14",
    "F15",
    "F16",
    "F17",
    "F18",
    "F19",
    "F20",
    "F21",
    "F22",
    "F23",
    "F24",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Num Lock",
    "Scroll Lock",
    "OEM Equal",
    "OEM Masshou",
    "OEM Touroku",
    "OEM Loya",
    "OEM Roya",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Left Shift",
    "Right Shift",
    "Left Ctrl",
    "Right Ctrl",
    "Left Alt",
    "Right Alt"
};

static const int KeyCodes[] = {
    0x00,  // None
    0x01,  // Left Mouse
    0x02,  // Right Mouse
    0x03,  // Cancel
    0x04,  // Middle Mouse
    0x05,  // Mouse 4
    0x06,  // Mouse 5
    0x07,  // Unknown
    0x08,  // Backspace
    0x09,  // Tab
    0x0A,  // Reserved
    0x0B,  // Reserved
    0x0C,  // Clear
    0x0D,  // Enter
    0x0E,  // Unknown
    0x0F,  // Unknown
    0x10,  // Shift
    0x11,  // Ctrl
    0x12,  // Alt
    0x13,  // Pause
    0x14,  // Caps Lock
    0x15,  // Kana
    0x16,  // IME On
    0x17,  // Junja
    0x18,  // Final
    0x19,  // Kanji
    0x1A,  // IME Off
    0x1B,  // Escape
    0x1C,  // Convert
    0x1D,  // Non Convert
    0x1E,  // Accept
    0x1F,  // Mode Change
    0x20,  // Space
    0x21,  // Page Up
    0x22,  // Page Down
    0x23,  // End
    0x24,  // Home
    0x25,  // Left Arrow
    0x26,  // Up Arrow
    0x27,  // Right Arrow
    0x28,  // Down Arrow
    0x29,  // Select
    0x2A,  // Print
    0x2B,  // Execute
    0x2C,  // Print Screen
    0x2D,  // Insert
    0x2E,  // Delete
    0x2F,  // Help
    0x30,  // 0
    0x31,  // 1
    0x32,  // 2
    0x33,  // 3
    0x34,  // 4
    0x35,  // 5
    0x36,  // 6
    0x37,  // 7
    0x38,  // 8
    0x39,  // 9
    0x3A,  // Undefined
    0x3B,  // Undefined
    0x3C,  // Undefined
    0x3D,  // Undefined
    0x3E,  // Undefined
    0x3F,  // Undefined
    0x40,  // Undefined
    0x41,  // A
    0x42,  // B
    0x43,  // C
    0x44,  // D
    0x45,  // E
    0x46,  // F
    0x47,  // G
    0x48,  // H
    0x49,  // I
    0x4A,  // J
    0x4B,  // K
    0x4C,  // L
    0x4D,  // M
    0x4E,  // N
    0x4F,  // O
    0x50,  // P
    0x51,  // Q
    0x52,  // R
    0x53,  // S
    0x54,  // T
    0x55,  // U
    0x56,  // V
    0x57,  // W
    0x58,  // X
    0x59,  // Y
    0x5A,  // Z
    0x5B,  // Left Windows
    0x5C,  // Right Windows
    0x5D,  // Apps
    0x5E,  // Reserved
    0x5F,  // Sleep
    0x60,  // Numpad 0
    0x61,  // Numpad 1
    0x62,  // Numpad 2
    0x63,  // Numpad 3
    0x64,  // Numpad 4
    0x65,  // Numpad 5
    0x66,  // Numpad 6
    0x67,  // Numpad 7
    0x68,  // Numpad 8
    0x69,  // Numpad 9
    0x6A,  // Multiply
    0x6B,  // Add
    0x6C,  // Separator
    0x6D,  // Subtract
    0x6E,  // Decimal
    0x6F,  // Divide
    0x70,  // F1
    0x71,  // F2
    0x72,  // F3
    0x73,  // F4
    0x74,  // F5
    0x75,  // F6
    0x76,  // F7
    0x77,  // F8
    0x78,  // F9
    0x79,  // F10
    0x7A,  // F11
    0x7B,  // F12
    0x7C,  // F13
    0x7D,  // F14
    0x7E,  // F15
    0x7F,  // F16
    0x80,  // F17
    0x81,  // F18
    0x82,  // F19
    0x83,  // F20
    0x84,  // F21
    0x85,  // F22
    0x86,  // F23
    0x87,  // F24
    0x88,  // Unknown
    0x89,  // Unknown
    0x8A,  // Unknown
    0x8B,  // Unknown
    0x8C,  // Unknown
    0x8D,  // Unknown
    0x8E,  // Unknown
    0x8F,  // Unknown
    0x90,  // Num Lock
    0x91,  // Scroll Lock
    0x92,  // OEM Equal
    0x93,  // OEM Masshou
    0x94,  // OEM Touroku
    0x95,  // OEM Loya
    0x96,  // OEM Roya
    0x97,  // Unknown
    0x98,  // Unknown
    0x99,  // Unknown
    0x9A,  // Unknown
    0x9B,  // Unknown
    0x9C,  // Unknown
    0x9D,  // Unknown
    0x9E,  // Unknown
    0x9F,  // Unknown
    0xA0,  // Left Shift
    0xA1,  // Right Shift
    0xA2,  // Left Ctrl
    0xA3,  // Right Ctrl
    0xA4,  // Left Alt
    0xA5   // Right Alt
};