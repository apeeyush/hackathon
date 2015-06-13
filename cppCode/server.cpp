#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mongoose.h"

static const char *s_no_cache_header =
  "Cache-Control: max-age=0, post-check=0, "
  "pre-check=0, no-store, no-cache, must-revalidate\r\n";

// static void handle_restful_call(struct mg_connection *conn) {
//   char n1[100], n2[100];
//   mg_get_var(conn, "n1", n1, sizeof(n1));
//   mg_get_var(conn, "n2", n2, sizeof(n2));

//   mg_printf_data(conn, "{ \"result\": %lf }", strtod(n1, NULL) + strtod(n2, NULL));
// }

static void handle_ping_call(struct mg_connection *conn) {
  mg_printf_data(conn, "{ \"ok\": \"true\" }");
}

static void handle_start_call(struct mg_connection *conn) {
  char y[100], o[100], g[100];
  mg_get_var(conn, "y", y, sizeof(y));
  mg_get_var(conn, "o", o, sizeof(o));
  mg_get_var(conn, "g", g, sizeof(g));

  // TODO : initGame(strtod(y, NULL), strtod(o, NULL), strtod(g, NULL))

  mg_printf_data(conn, "{ \"ok\": \"true\" }");
}

static void handle_play_call(struct mg_connection *conn) {
  char m[100];
  mg_get_var(conn, "m", m, sizeof(m));

  // TODO : Send move and ask our more

  mg_printf_data(conn, "{ \"ok\": \"true\" }");
}


static int ev_handler(struct mg_connection *conn, enum mg_event ev) {
  switch (ev) {
    case MG_AUTH: return MG_TRUE;
    case MG_REQUEST:

      if (!strcmp(conn->uri, "/ping")) {
        handle_ping_call(conn);
        return MG_TRUE;
      }
      if (!strcmp(conn->uri, "/start")) {
        handle_start_call(conn);
        return MG_TRUE;
      }
      if (!strcmp(conn->uri, "/play")) {
        handle_play_call(conn);
        return MG_TRUE;
      }
      return MG_FALSE;
      // if (!strcmp(conn->uri, "/api/sum")) {
      //   handle_restful_call(conn);
      //   return MG_TRUE;
      // }
      // mg_send_file(conn, "index.html", s_no_cache_header);
      // return MG_MORE;
    default: return MG_FALSE;
  }
}

int main(void) {
  struct mg_server *server;
  // Create and configure the server
  server = mg_create_server(NULL, ev_handler);
  mg_set_option(server, "listening_port", "8080");
  // Serve request. Hit Ctrl-C to terminate the program
  printf("Starting on port %s\n", mg_get_option(server, "listening_port"));
  for (;;) {
    mg_poll_server(server, 1000);
  }
  // Cleanup, and free server instance
  mg_destroy_server(&server);
  return 0;
}
