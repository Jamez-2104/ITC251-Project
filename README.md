# grep-lite

A command-line tool that searches for a text pattern across files in a directory. Supports line numbers, case-insensitive search, whole-word matching, and match counting.

---

## Project Structure

```
grep-lite/
├── main.c      # user input, flag menu, directory traversal
├── search.c    # pattern matching and line processing
├── search.h    # declares process_stream()
├── Makefile
└── .gitignore
```

---

## Building

With `gcc`:

```bash
gcc main.c search.c -o grep-lite
```

To remove the binary:

```bash
make clean
```

---

## Usage

```bash
./grep-lite
```

The program asks for a folder path and a search pattern, then shows the flag menu:

```
--------------------------------------------------------------------
1:Flag-n (line numbers) 
2:Flag-i (case insensitive) 
3:Flag-w (whole word) 
4:Flag-c (count) 
--------------------------------------------------------------------
Current selected flags: n:0, i:0, w:0, c:0
Select what flags you want to use (press 0 to finish):
```

Enter a flag number to toggle it on or off. Enter `0` to start searching.

---

## Flags

| Flag | Description |
|------|-------------|
| `-n` | Print line numbers before each match |
| `-i` | Case-insensitive matching |
| `-w` | Match whole words only (word boundary = anything that isn't a letter, digit, or `_`) |
| `-c` | Print match count per file instead of matching lines |

---

## Example Output

The path prefix in each result reflects whatever folder path the user entered. These examples use `./logs`, but if an absolute path was typed it would appear instead.

No flags (pattern: `error`, folder: `./logs`):
```
./logs/app.log:an error occurred
./logs/debug.log:error: null pointer
```

With `-n`:
```
./logs/app.log:4:an error occurred
./logs/debug.log:12:error: null pointer
```

With `-c`:
```
./logs/app.log:1
./logs/debug.log:1
```

With `-w` — matches `error` and `error.` and `(error)` but not `errors`:
```
./logs/app.log:an error occurred
```

Note: file order in results is not guaranteed — it depends on the order the OS returns directory entries.

---

## How It Works

`check_match()` in `search.c` slides a window across each line comparing characters. With `-i`, both sides are lowercased before comparing. With `-w`, it checks that the characters immediately before and after the match position are non-word characters (not a letter, digit, or underscore) so punctuation like `.` `(` `,` `"` all count as valid boundaries.

`process_stream()` reads line by line with a 1024-byte buffer. If a line exceeds the buffer, the remaining characters are consumed until the next newline so subsequent lines read correctly, but the oversized line itself is not matched and no warning is printed.

`main.c` opens the folder with `opendir()` and uses `stat()` with `S_ISREG()` to skip subdirectories, symlinks, and anything else that isn't a plain file. If a file can't be opened, it prints an error and moves on.

---

## Limitations

**Lines over 1024 characters are silently skipped.**
In `search.c`, the line buffer is declared as `char line[1024]`, which is a hard cap. If a line exceeds this, `fgets()` only reads the first 1023 characters, the rest is flushed, and the line is never matched. No warning is printed.

**Subdirectories are not searched.**
In `main.c`, the `S_ISREG()` check skips anything that isn't a plain file, including folders. If there is a file inside a subfolder, it will never be searched. Fixing this would require recursion.

**Pattern matching is O(n×m).**
In `search.c`, `check_match()` uses two nested loops — the outer loop goes through each position in the line (n), and the inner loop compares up to the full pattern at each position (m). For a 100-character line and a 10-character pattern, up to 1000 comparisons could happen per line. Algorithms like KMP or Boyer-Moore were not implemented.

**No stdin/pipe support.**
The program always prompts for input step by step — folder, pattern, then flags. There is no way to pass input in one command. The current implementation does not support it.

**`scanf` leaves a newline in the input buffer.**
The flag menu uses `scanf("%d", &flag)` to read the user's number. `scanf` reads the number but leaves the newline character sitting in the input buffer. This can interfere with subsequent input reads.

---

## Authors

James Baidiango, Rafael Mercado, Marco Gonzalez, Chinedu Meremikwu.
