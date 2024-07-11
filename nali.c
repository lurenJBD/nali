#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <locale.h>
#include <iconv.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "libqqwry/qqwry.h"
#include "config.h"

static void gbk_to_utf8(char *src, char *dst, size_t dst_size);
static int is_valid_ipv4(const char *ip);
static int is_valid_ipv6(const char *ip);

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    if (isatty(fileno(stdin)) && argc <= 1) {
        printf("Please enter IPs addresses (separated by space): ");
        fflush(stdout);
    }

    // Default to getting large range address information
    int detailed_info = 0; // 0 for large range, 1 for detailed information

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0) {
            detailed_info = 1;
            break;
        }
    }

    char **ips = NULL;
    int ip_count = 0;

    if (argc > 1) {
        ips = malloc((argc - 1) * sizeof(char *));
        if (ips == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return 1;
        }
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-d") != 0) { // Skip the -d flag itself
                if (is_valid_ipv4(argv[i]) || is_valid_ipv6(argv[i])) {
                    ips[ip_count] = strdup(argv[i]);
                    ip_count++;
                } else {
                    fprintf(stderr, "Invalid IP address: %s\n", argv[i]);
                }
            }
        }
    } else {
        char input[1024];
        if (fgets(input, sizeof(input), stdin) == NULL) {
            fprintf(stderr, "Error reading input.\n");
            return 1;
        }
        // Remove newline character if present
        input[strcspn(input, "\n")] = '\0';
        
        char *token;
        ips = malloc(128 * sizeof(char *));
        if (ips == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return 1;
        }
        
        token = strtok(input, " ");
        while (token != NULL) {
            if (strcmp(token, "-d") != 0) { // Skip the -d flag itself
                if (is_valid_ipv4(token) || is_valid_ipv6(token)) {
                    ips[ip_count] = strdup(token);
                    ip_count++;
                } else {
                    fprintf(stderr, "Invalid IP address: %s\n", token);
                }
            }
            token = strtok(NULL, " ");
        }
    }

    FILE *wry_file = NULL;
    wry_file = fopen(NALI_QQWRY_PATH, "r");
    if (wry_file == NULL) {
        wry_file = fopen("./qqwry.dat", "r");
    }
    if (wry_file == NULL) {
        fprintf(stderr, "Failed to open qqwry.dat file. Make sure it exists.\n");
        return 1;
    }

    for (int i = 0; i < ip_count; ++i) {
        char address[1024] = {'\0'};
        char company[1024] = {'\0'};
        char utf8_address[2048] = {'\0'};
        char utf8_company[2048] = {'\0'}; 

        int success;
        success = qqwry_get_location(address, company, ips[i], wry_file);
        if (success) {
            gbk_to_utf8(address, utf8_address, sizeof(utf8_address));
            gbk_to_utf8(company, utf8_company, sizeof(utf8_company));
            // Output in the specified format: IP[address company] or IP[address]
            if (detailed_info) {
                printf("%s[%s %s]\n", ips[i], utf8_address, utf8_company);
            } else {
                printf("%s[%s]\n", ips[i], utf8_address);
            }
        } else {
            fprintf(stderr, "Failed to retrieve location information for IP: %s\n", ips[i]);
        }
        
        free(ips[i]);
    }

    free(ips);
    fclose(wry_file);
    return 0;
}

// Convert GBK string to UTF-8
static void gbk_to_utf8(char *src, char *dst, size_t dst_size)
{
    if (src == NULL || dst == NULL || dst_size == 0) {
        return;
    }
    iconv_t cd = iconv_open("UTF-8", "GBK");
    if (cd == (iconv_t)-1) {
        perror("iconv_open failed");
        return;
    }

    size_t src_len = strlen(src);
    size_t dst_len = dst_size - 1; // Leave one space for '\0'
    size_t ret = iconv(cd, &src, &src_len, &dst, &dst_len);
    if (ret == (size_t)-1) {
        perror("iconv failed");
    }

    iconv_close(cd);
}

static int is_valid_ipv4(const char *ip)
{
    struct in_addr addr;
    return inet_pton(AF_INET, ip, &addr);
}

static int is_valid_ipv6(const char *ip)
{
    struct in6_addr addr;
    return inet_pton(AF_INET6, ip, &addr);
}

        if (wry_file!=NULL) {
            break;
        }
    }
    qqwry_get_location(country,area,ip,wry_file);
    fclose(wry_file);
    if (strlen(country)>0) {
        printf("%s",country);
    }
    if (strlen(area)>0) {
        if (strlen(country)>0) {
            printf(" ");
        }
        if (strlen(country)<=0) {
            printf("unknown");
        } else {
            printf("%s",area);
        }
    }
    printf("\n");
    return 0;
}

