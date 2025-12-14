#include <stdio.h>
#include <stdlib.h>

static char *read_entire_file(const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;

    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return NULL; }
    long size = ftell(f);
    if (size < 0) { fclose(f); return NULL; }
    rewind(f);

    char *buf = (char *)malloc((size_t)size + 1);
    if (!buf) { fclose(f); return NULL; }

    size_t n = fread(buf, 1, (size_t)size, f);
    fclose(f);

    if (n != (size_t)size) { free(buf); return NULL; }
    buf[size] = '\0';
    return buf;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: snek <file.sk>\n");
        return 1;
    }

    char *source = read_entire_file(argv[1]);
    if (!source) {
        fprintf(stderr, "error: could not read file '%s'\n", argv[1]);
        return 1;
    }

    printf("=== Sneklang source (%s) ===\n", argv[1]);
    printf("%s\n", source);

    free(source);
    return 0;
}
