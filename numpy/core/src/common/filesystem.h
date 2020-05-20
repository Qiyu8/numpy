
static int
get_file_size(const char* pathname);
static int
read_file(const char*  pathname, char*  buffer, size_t  buffsize);
static char*
extract_cpuinfo_field(const char* buffer, int buflen, const char* field);
static int
has_list_item(const char* list, const char* item);