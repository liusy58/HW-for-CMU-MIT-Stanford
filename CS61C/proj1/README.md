Files:



Some functions in `utils.h`

* `void fs_mkdir(const char* dirname)`: Create a new directory of name dirname
* `void fs_rm(const char* filename)`: Delete the file filename
* `void fs_mv(const char* src, const char* dst)`: Move the file src to dst, potentially overwriting it
* `void fs_cp(const char* src, const char* dst)`: Copy the file src to dst, potentially overwriting it
* `int fs_check_dir_exists(const char* dirname)`. This function tests whether a given directory exists.
* `void write_string_to_file(const char* filename, const char* str)`: Create or overwrite the file filename and write str into it, including the NULL-character
* `void read_string_from_file(const char* filename, char* str, int size)`: Open the file filename and read its content into the location pointed to by str; limit the amount to read to at most size bytes, including the NULL character