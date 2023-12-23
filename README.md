# File Manager

## Description

File Manager is a command-line application written in C that offers basic file system navigation and management functionalities. Designed to mimic some of the fundamental behaviors of Unix-like shell commands, this lightweight tool provides users with a hands-on approach to managing files and directories without leaving the terminal.

## Key Features

- **List Files and Directories (`ls`)**: Display the contents of the current directory, showing both files and directories.
- **Change Directory (`cd`)**: Navigate to different directories within the file system.
- **Print Working Directory (`pwd`)**: Output the path of the current working directory.
- **Create File (`create`)**: Generate new files, specifying the desired filename.
- **Delete File (`delete`)**: Remove files from the file system.
- **Rename File (`rename`)**: Change the name of existing files.
- **Create Directory (`mkdir`)**: Create new directories.
- **Remove Directory (`rmdir`)**: Delete empty directories.
- **Move to Parent Directory (`back`)**: Navigate back to the parent directory of the current working directory.
- **Help (`help`)**: Display information about available commands and their usage.
- **Exit (`exit`)**: Terminate the file manager session.

## Technical Specifications

- Written in standard C programming language.
- Utilizes system calls and standard library functions for file and directory operations.
- Employs command-line parsing for user input handling.
- Platform-independent design, suitable for Unix-like environments and Windows systems (with appropriate C environments like GCC or MinGW).

## Usage Scenario

This tool is ideal for educational purposes, for users beginning to learn about file systems and command-line interfaces, and for those who need a simple, scriptable interface for basic file management tasks.
