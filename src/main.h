#ifndef MAIN_H
#define MAIN_H

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <math.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/uio.h>

#include "ssl.h"
#include "aprintf.h"
#include "stats.h"
#include "units.h"
#include "zmalloc.h"
#include "jansson.h"

struct config;
struct resultForm;

static void *thread_main(void *);
static int connect_socket(thread *, connection *);
static int reconnect_socket(thread *, connection *);

static int record_rate(aeEventLoop *, long long, void *);

static void socket_connected(aeEventLoop *, int, void *, int);
static void socket_writeable(aeEventLoop *, int, void *, int);
static void socket_readable(aeEventLoop *, int, void *, int);

static int response_complete(http_parser *);
static int header_field(http_parser *, const char *, size_t);
static int header_value(http_parser *, const char *, size_t);
static int response_body(http_parser *, const char *, size_t);

static uint64_t time_us();

static int parse_args(struct config *, char **, char **, int, char **);
static char *copy_url_part(char *, struct http_parser_url *, enum http_parser_url_fields);

static void statistics_rps(stats *);

static void record_html_log(char *key, char *value);

static void print_stats(char *, stats *, char *(*)(long double));
static void print_stats_latency(stats *);
static void print_stats_requests(stats *);
static void print_stats_latency_map(stats *);
static void print_stats_error_code(errors *);
static void print_result_form();
static void print_test_parameter(const char *);

static void print_test_result(struct resultForm *, errors *);
static void print_result_details(struct resultForm *, errors *);

static void print_disk_info(json_t *json);
static void print_platform_info(json_t *json);

typedef struct CollectConfig {
	uint64_t start_time;
	char hash_string[64];
	bool result;
} CollectConfig;
static void print_dstServerPerformance(CollectConfig *, json_t *);

static void clear_unused_variable();
#endif /* MAIN_H */
