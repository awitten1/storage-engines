#include <iostream>
#include "wiredtiger.h"

static const char *home = "asdf";

static void
access_example(void)
{
    WT_CONNECTION *conn;
    WT_CURSOR *cursor;
    WT_SESSION *session;
    const char *key, *value;
    int ret;

    /* Open a connection to the database, creating it if necessary. */
    wiredtiger_open(home, NULL,
            """create,cache_size=4GB,log=(enabled,recover=on),"""
            """statistics_log=(json=true),transaction_sync=(enabled=true,method=fsync)""", &conn);

    /* Open a session handle for the database. */
    conn->open_session(conn, NULL, NULL, &session);
    session->create(session, "table:access", "key_format=S,value_format=S");
    session->open_cursor(session, "table:access", NULL, NULL, &cursor);
    cursor->set_key(cursor, "key1"); /* Insert a record. */
    cursor->set_value(cursor, "value1");
    cursor->insert(cursor);
    cursor->reset(cursor); /* Restart the scan. */
    while ((ret = cursor->next(cursor)) == 0) {
        cursor->get_key(cursor, &key);
        cursor->get_value(cursor, &value);

        printf("Got record: %s : %s\n", key, value);
    }
    conn->close(conn, NULL); /* Close all handles. */
}


int main() {
  access_example();
  return 0;
}