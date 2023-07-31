# XV6_FileRecovery-Functionality

**Xv6 Recovery and File Management Enhancement**

Xv6 has been changed to support best-effort recovery. This enhancement focuses on file recovery, while directory recovery is not supported. A file can only be recovered if its integrity remains untouched, meaning none of the file's memory blocks are used by another file or directory.

To make this task possible, two significant changes have been implemented in xv6:

1. **Tracking Memory Blocks:** A file structure now includes an array `array[memory block address]` to keep track of memory blocks that belong to a particular file.

2. **Deletion Flag:** Each file in the directory is assigned a flag called `del` (deletion flag) to indicate whether the file is deleted or not. By default, when a file is deleted in xv6, all its contents disappear, and the busy flag is set to zero, allowing the file structure to be reused by other directories. The modification ensures that when a file is deleted, all of its data remains on disk, but the busy flag is set to 0, and the `del` flag is set to 1. This way, the data of the file is preserved, while the file structure is made available for reuse.

**Additional Changes to Xv6 OS:**

**System Calls:**

1. `int lsdel(char *path, char *result)`: This system call lists all deleted files from the directory specified by the `path`. It returns the number of deleted files in the directory or -1 if the path is incorrect.

2. `int rec(char *path)`: This system call attempts "best effort" recovery of the file specified by the `path`. The return value indicates the success of the recovery attempt. Possible return values include 0 - successful recovery, 1 - wrong path, 2 - file not found in the directory, 3 - file structure is used for something else, and 4 - some of the file's memory blocks are used for something else.

**User Programs:**

1. `lsdel [path]`: This user program prints the names of deleted files from the directory specified by the `path`. If the path is omitted, it considers the current directory by default.

2. `rec <path>`: This user program tries to recover the file specified by the `path` or reports an error if recovery is not possible.

3. `writter <filename> <numberOfBytes>`: This user program creates a file with the given `filename` and size specified by `numberOfBytes`.

**Example Usage:**

1. Creating, deleting, and recovering a file:
   ```
   writer a 500
   rm a
   rec a
   ```

2. Error message example for a file structure used for something else:
   ```
   cd home
   writer a 500
   rm a
   cd ..
   writer b 500
   cd home
   rec a
   ```

3. Error message example for memory blocks used for something else:
   ```
   cd home
   writer a 10
   writer b 10
   rm a b
   cd ..
   writer c 1500
   cd home
   rec b
   ```

**Instructions to Start the Program:**
1. Open the terminal in the project's directory.
2. Run 'make clean' to clean the project.
3. Run 'make qemu' to start the xv6 operating system, displayed in the QEMU window.
