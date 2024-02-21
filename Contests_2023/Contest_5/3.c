int
parse_rwx_permissions(const char *str)
{
    if (!str) {
        return -1;
    }
    const char m[] = "rwxrwxrwx";
    unsigned int i, ret = 0;
    for (i = 0; m[i] && str[i]; ++i) {
        if (str[i] != m[i] && str[i] != '-') {
            return -1;
        }
        ret = (ret << 1) | (m[i] == str[i]);
    }

    return (m[i] == str[i]) ? (int) ret : -1;
}