#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


#include "cache.h"

typedef enum {
    CMD_UNKNOWN,
    CMD_FLUSH,
    CMD_R,
    CMD_W,
    CMD_MR
} command_t;

/**
 * Imprime la ayuda del programa por stderr.
 */
void print_help() {
    fprintf(stderr, 
        "Simulador de caché\n"
        "Uso: \n"
        "./tp2 [-v|--verbose] <file.mem>\n"
        "\n"
        "-v --verbose: Muestra el detalle de cada lectura/escritura\n"
    );
}

/**
 * Compara un argumento contra su forma corta y su forma larga. 
 * 
 * Devuelve true si el argumento coincide con alguna de ellas.
 */
bool arg_compare(const char *arg, const char* shortstr, const char *longstr) {
    return (strcmp(arg, shortstr) == 0) || (strcmp(arg, longstr) == 0);
}

/**
 * Procesa los argumentos de línea de comando.
 * 
 * Si no se recibe un nombre de archivo o si los argumentos son inválidos 
 * devuelve falso.
 * 
 * En caso contrario devuelve verdadero y almacena los argumentos recibidos
 * en los parámetros verbose y filename.
 */
bool process_argv(int argc, char *argv[], bool *verbose, char** filename) {
    if (argc == 2) {
        *filename = argv[1];
        *verbose = false;
        return true;
    } else if (argc == 3) {
        if (!arg_compare(argv[1], "-v", "--verbose"))
            return false;

        *verbose = true;
        *filename = argv[2];
        return true;
    }

    return false;
}

/**
 * Determina el comando a partir de una línea del archivo.
 * Ignora los caracteres de separación '\t', '\v', '\n', ' '.
 * 
 * Copia en p la primer posición no reconocida.
 * 
 * Devuelve CMD_UNKNOWN si no se reconoce un comando en la línea.
 */
command_t read_command(const char *line, size_t *p) {
    size_t ptr = 0;
    size_t in_ptr = 0;
    command_t curr_cmd = CMD_UNKNOWN;
    const char *curr_ptr = NULL;

    enum {
        IN_STR,
        OUTSIDE
    } state;

    state = OUTSIDE;

    while (line[ptr]) {
        char c = tolower(line[ptr++]);
        switch(state) {
            case OUTSIDE:
                in_ptr = 1;
                state = IN_STR;
                switch(c) {
                    case 'f':
                        curr_ptr = "flush";
                        curr_cmd = CMD_FLUSH;
                        break;
                    case 'm':
                        curr_ptr = "mr";
                        curr_cmd = CMD_MR;
                        break;
                    case 'r':
                        curr_ptr = "r";
                        curr_cmd = CMD_R;
                        break;
                    case 'w':
                        curr_ptr = "w";
                        curr_cmd = CMD_W;
                        break;
                    default:
                        curr_cmd = CMD_UNKNOWN;
                        state = OUTSIDE;
                        break;
                }
                break;
            case IN_STR:
                if (c == curr_ptr[in_ptr]) {
                    in_ptr++;
                } else if ((curr_ptr[in_ptr] == '\0') && isspace(c)) {
                    *p = ptr;
                    return curr_cmd;
                } else {
                    *p = ptr;
                    return CMD_UNKNOWN;
                }
                break;
        }
    }

    *p = ptr;
    return CMD_UNKNOWN;
}

bool read_addr(const char *buffer, size_t ptr, unsigned int *addr) {
    while (isspace(buffer[ptr])) ptr++;
    if (!buffer[ptr])
        return false;

    char *p = NULL;
    *addr = strtol(buffer + ptr, &p, 10);
    if ((*p) && !isspace(*p))
        return false;
    
    return true;
}

bool read_addr_n_val(const char *buffer, size_t ptr, unsigned int *addr, 
    unsigned char *value) {
    while (isspace(buffer[ptr])) ptr++;
    if (!buffer[ptr])
        return false;

    char *p = NULL;
    *addr = strtol(buffer + ptr, &p, 10);
    if (*p != ',')
        return false;
    ptr = 0;
    while (isspace(p[++ptr]));
    *value = strtol(p + ptr, &p, 10);

    if ((*p) && !isspace(*p))
        return false;

    return true;
}

/**
 * Simulador de caché.
 * 
 * Uso:
 * ./tp2 [-v|--verbose] <file.mem>
 * 
 * -v --verbose: Muestra el detalle de cada lectura/escritura.
 */
int main(int argc, char *argv[]) {
    bool verbose = false;
    char* filename = NULL;
    FILE* input;

    if (!process_argv(argc, argv, &verbose, &filename)) {
        print_help();
        return EXIT_FAILURE;
    }

    if (strcmp(filename, "-") == 0)
        input = stdin;
    else
        input = fopen(filename, "r");
    
    if (!input) {
        fprintf(stderr, 
            "ERROR: No se pudo abrir %s\n", filename);
        return EXIT_FAILURE;
    }

    char buffer[8192];
    while (fgets(buffer, sizeof(buffer), input)) {
        size_t ptr = 0;
        unsigned int addr;
        unsigned char value;
        command_t cmd = read_command(buffer, &ptr);
        switch(cmd) {
            case CMD_FLUSH:
                if (verbose)
                    printf("flush\n");
                init();
                break;
            case CMD_R:
                if (!read_addr(buffer, ptr, &addr)) {
                    fprintf(stderr, "ERROR: Formato inválido. Abortando\n");
                    if (input != stdin)
                        fclose(input);
                    return EXIT_FAILURE;
                }
                if (verbose)
                    printf("read addr %d\n", addr);
                read_byte(addr);
                break;
            case CMD_W:
                if (!read_addr_n_val(buffer, ptr, &addr, &value)) {
                    fprintf(stderr, "ERROR: Formato inválido. Abortando\n");
                    if (input != stdin)
                        fclose(input);
                    return EXIT_FAILURE;
                }
                if (verbose)
                    printf("write value %d to addr %d\n", value, addr);
                write_byte(addr, value);
                break;
            case CMD_MR:
                if (verbose)
                    printf("miss rate: ");
                printf("%.2f\n", get_miss_rate());
                break;
            default:
                fprintf(stderr, "ERROR: Comando no reconocido. Abortando\n");
                if (input != stdin)
                    fclose(input);
                return EXIT_FAILURE;
        }
    }

    if (input != stdin)
        fclose(input);

    return EXIT_SUCCESS;
}