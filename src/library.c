#include "library.h"

void hello(void) {
    printf("Hello, World!\n");
}

Connections_t* initialize(const char* url_string, const char* db_name, const char* collection_name) {
    mongoc_init();
    Connections_t *res = malloc(sizeof(*res));
    mongoc_uri_t *uri = NULL;
    uri = mongoc_uri_new(url_string);
    res->client = mongoc_client_new_from_uri(uri);
    res->db = mongoc_client_get_database(res->client, db_name);
    res->collection = mongoc_client_get_collection(res->client, db_name, collection_name);
    return res;
}

void clear_up(Connections_t* conn) {
    mongoc_collection_destroy (conn->collection);
    mongoc_database_destroy (conn->db);
    mongoc_client_destroy (conn->client);
    mongoc_cleanup();
    free(conn);
}

mongoc_cursor_t* query(bson_t* query, Connections_t* conn) {
    Result_t result;
    if (!conn || !query) {
        result = (Result_t){.doc_count = 0, .documents = NULL};
        return;
    }
    const bson_t* doc;
    mongoc_cursor_t *cursor;
    char* str;

    cursor = mongoc_collection_find_with_opts(conn->collection, query, NULL, NULL);

    int doc_count = 0;
    while (mongoc_cursor_next (cursor, &doc)) {
        str = bson_as_canonical_extended_json (doc, NULL);
        printf ("%s\n", str);
        bson_free (str);
    }
    cursor = mongoc_collection_find_with_opts(conn->collection, query, NULL, NULL);
    return cursor;
}

void insert(bson_t *doc, Connections_t* conn) {
    bson_error_t error;

//    const char *json = "{\"name\": {\"first\":\"Grace\", \"last\":\"Hopper\"}}";
    // bson = bson_new_from_json ((const uint8_t *)doc, -1, &error);

    // if (!bson) {
    //     fprintf (stderr, "%s\n", error.message);
    //     return;
    // }

    if (!mongoc_collection_insert_one (conn->collection, doc, NULL, NULL, &error)) {
        fprintf (stderr, "%s\n", error.message);
    }
    // bson_destroy (bson);
}

void update(bson_oid_t *oid, bson_t *doc, Connections_t *conn)
{
    bson_error_t error;
    bson_t *query = NULL;
    query = BCON_NEW("_id", BCON_OID(oid));
    if (!mongoc_collection_update_one(conn->collection, query, doc, NULL, NULL, &error)){
        fprintf(stderr, "%s\n", error.message);
    }
    bson_destroy(query);
}

void delete(bson_oid_t *oid, Connections_t *conn)
{
    bson_error_t error;
    bson_t *doc = NULL;
    doc = bson_new();
    BSON_APPEND_OID(doc, "_id", oid);
    if (! mongoc_collection_delete_one(
            conn->collection, doc, NULL, NULL, &error)){
        fprintf (stderr, "Delete failed: %s\n", error.message);
            }
    bson_destroy(doc);
}