# 📔 Secure Personal Diary

A password-protected, multi-user personal diary application written in C. Store your thoughts with tiered privacy controls — only the people you trust can see what you choose to share.

---

## Table of Contents

- [Features](#features)
- [User Roles & Permissions](#user-roles--permissions)
- [Note Privacy Levels](#note-privacy-levels)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Build with Code::Blocks](#build-with-codeblocks)
  - [Build with GCC (Command Line)](#build-with-gcc-command-line)
  - [Running the Application](#running-the-application)
- [Usage Walkthrough](#usage-walkthrough)
- [Security Notes](#security-notes)
- [Data Storage](#data-storage)
- [Known Limitations](#known-limitations)

---

## Features

- 🔐 **Password-protected login** for Admin and Life Partner roles
- 👥 **Three user roles** with distinct access levels
- 🏷️ **Three note privacy levels** — Public, Protected, and Private
- 📅 **Date-based diary entries** — notes are grouped and stored by date
- ✏️ **Full CRUD** — Add, View, Modify, and Delete diary records
- 🔒 **Note encryption** — diary content is obfuscated at rest
- 📋 **Today's summary** shown on the main menu on every login
- 🗑️ **Wipe all data** option (Admin only)

---

## User Roles & Permissions

The application supports three user roles, selected from the login menu. Roles determine what notes a user can read and which operations they can perform.

| Role | Level | Password Required | Add Notes | View Notes | Modify Notes | Delete Records | Change Password |
|---|---|---|---|---|---|---|---|
| **Guest** | 0 | ❌ | Public only | Public only | ❌ | ❌ | ❌ |
| **Life Partner** | 1 | ✅ | Public, Protected | Public, Protected | ❌ | ❌ | ✅ |
| **Admin** | 2 | ✅ | All levels | All levels | ✅ | ✅ | ✅ |

> **Note:** If no password file is found for a role (first run), the application will prompt to set a new password before proceeding.

---

## Note Privacy Levels

When adding a note, users with sufficient permissions can choose a privacy level. The diary renders each privacy level in a distinct color in the terminal.

| Privacy Level | Label | Terminal Color | Visible To |
|---|---|---|---|
| 0 | **Public** | 🟢 Green | Everyone (Guest, Life Partner, Admin) |
| 1 | **Protected** | 🟡 Yellow | Life Partner & Admin |
| 2 | **Private** | 🔵 Cyan | Admin only |

Notes above a user's permission level are hidden with the message:
> `You do not have the required permission to view this note.`

---

## Project Structure

```
Secure-Personal-Diary/
│
├── main.c                    # Entry point — login menu, user-level selection, main loop
├── diary.h                   # Core data structure: struct record
├── fucntion_prototypes.h     # Function declarations for all modules
│
├── add_record.c              # Add a new diary note
├── view_record.c             # View notes for a specific date or all dates
├── view_all_records.c        # Render all historical records
├── show_today_record.c       # Display today's notes on the main menu
├── modify_record.c           # Edit an existing note (Admin only)
├── delete_record.c           # Delete a day's records or all records (Admin only)
│
├── change_password.c         # Change password (requires current password)
├── set_pass.c                # Set a new password
│
├── hash.c                    # HASH() and HASH2() — password hashing functions
├── encryption.c              # encode() / decode() — note content encryption
├── erase_everything.c        # Wipe all diary data files
├── time.c                    # show_Time() and delay() utilities
│
├── admin_pass.txt            # Hashed Admin password (auto-created on first run)
├── part_pass.txt             # Hashed Life Partner password (auto-created on first run)
├── available_records.txt     # Index of all dates that have diary entries
│
├── Secure-Personal-Diary.cbp # Code::Blocks project file
└── bin/                      # Compiled output (Debug / Release)
```

The `struct record` (defined in `diary.h`) is the core data unit:

```c
struct record {
    int  privacy_level;      // 0 = Public, 1 = Protected, 2 = Private
    char time[50];           // Time the note was written (e.g. "09:45 AM")
    char note[500];          // The diary note content (stored encrypted)
};
```

---

## Getting Started

### Prerequisites

- **Windows OS** — the application uses `<conio.h>` and `system("cls")`, which are Windows-specific.
- **GCC compiler** — bundled with [Code::Blocks](https://www.codeblocks.org/), [MinGW](https://www.mingw-w64.org/), or [TDM-GCC](https://jmeubank.github.io/tdm-gcc/).

### Build with Code::Blocks

1. Open `Secure-Personal-Diary.cbp` in [Code::Blocks](https://www.codeblocks.org/).
2. Select the desired build target (**Debug** or **Release**) from the toolbar.
3. Press **F9** (Build & Run) or go to **Build → Build**.
4. The compiled binary is placed in `bin/Debug/` or `bin/Release/`.

### Build with GCC (Command Line)

Open a terminal (Command Prompt / PowerShell) in the project directory and run:

```bash
gcc -Wall -o secure-personal-diary \
    main.c \
    add_record.c \
    view_record.c \
    view_all_records.c \
    show_today_record.c \
    modify_record.c \
    delete_record.c \
    change_password.c \
    set_pass.c \
    hash.c \
    encryption.c \
    erase_everything.c \
    time.c
```

### Running the Application

```bash
./secure-personal-diary
```

> **Important:** Run the executable from the project root directory (where `available_records.txt` and password files reside), so the app can correctly locate its data files.

---

## Usage Walkthrough

### 1. Login

On launch you are presented with the login menu:

```
*******************************************************************************
******************** WELCOME TO YOUR SECURED PERSONAL DIARY *******************
*******************************************************************************
*                              LOGIN MENU                                     *
* SELECT USER:                                                                *
* 1. Admin                                                                    *
* 2. Life Partner                                                             *
* 3. Guest                                                                    *
* 4. Exit                                                                     *
* Choice:
```

- Select your role and enter your password (displayed as `*` characters).
- First-time login as Admin or Life Partner will prompt you to **set a password**.
- Guest requires no password.

### 2. Main Menu

After login, today's notes are displayed (if any), followed by the menu:

```
>> MENU <<
1. Add Record
2. View Record
3. Modify Record
4. Delete Record
5. Change Password
6. Log Out
```

### 3. Adding a Note

1. Select **1. Add Record**.
2. Choose the privacy level of the note (available options depend on your user level).
3. Type your note and press **Enter**.
4. The note is saved and encrypted to the current date's file.

### 4. Viewing Records

1. Select **2. View Record**.
2. Available dates are listed. Enter a date (e.g. `18-09-2023`) or type `all` to view everything.
3. Notes you don't have permission to see are shown as hidden placeholders.

### 5. Modifying a Note *(Admin only)*

1. Select **3. Modify Record**.
2. Enter the date of the note you want to edit.
3. Enter the note number to modify.
4. Optionally update the time and/or the note content.

### 6. Deleting Records *(Admin only)*

1. Select **4. Delete Record**.
2. Enter a date to delete that day's records, or type `all` and confirm to wipe everything.

### 7. Changing Password

1. Select **5. Change Password**.
2. Confirm your current password.
3. Enter the new password.

---

## Security Notes

### Password Hashing

Passwords are **never stored in plaintext**. When a password is set, a hash value is computed and saved to `admin_pass.txt` or `part_pass.txt`. On login, the entered password is hashed and compared.

The hash function used (`hash.c`):

```c
int HASH(char *pass) {
    int n = strlen(pass);
    int h = 0;
    for (int i = 0; i < n; i++) {
        h += ((i + 1) * pass[i]);
    }
    return h;
}
```

> ⚠️ **This is a simple custom hash, not a cryptographic one.** It is not collision-resistant and should not be considered production-grade security. For a real-world application, use a library like bcrypt or Argon2.

### Note Encryption

All diary notes are encrypted before being written to disk using a character-shift cipher (`encryption.c`):

```c
// Encoding: shift each character by +128
void encode(char* s) {
    for (int i = 0; i < strlen(s); i++)
        s[i] = s[i] + 128;
}

// Decoding: shift each character by -128
void decode(char* s) {
    for (int i = 0; i < strlen(s); i++)
        s[i] = s[i] - 128;
}
```

> ⚠️ **This is a Caesar-cipher-style shift, not strong encryption.** Anyone with access to the raw binary files can decode the notes trivially. It provides basic obfuscation only.

---

## Data Storage

All data is stored as flat files in the project's working directory:

| File | Description |
|---|---|
| `available_records.txt` | Plain-text list of all dates that have diary entries (one per line) |
| `admin_pass.txt` | Single integer — the hashed Admin password |
| `part_pass.txt` | Single integer — the hashed Life Partner password |
| `DD-MM-YYYY` | Binary file containing all `struct record` entries for that date |

**Example `available_records.txt`:**
```
18-09-2023
19-09-2023
21-09-2023
```

Each dated file (e.g. `18-09-2023`) stores binary-serialized `struct record` structs written sequentially with `fwrite`.

---

## Known Limitations

| Limitation | Details |
|---|---|
| **Windows only** | Uses `<conio.h>`, `_getch()`, and `system("cls")` — not portable to Linux/macOS without modification |
| **Deprecated `gets()`** | Several modules use `gets()`, which is unsafe and removed in C11. Should be replaced with `fgets()` |
| **Weak security** | The password hash and note cipher are not cryptographically secure |
| **No note-level delete** | Records can only be deleted by the entire day, not individually |
| **Binary struct serialization** | Data files are tied to the struct layout; changes to `struct record` break existing files |
| **Single-machine only** | No network or cloud storage; all data lives on the local filesystem |
