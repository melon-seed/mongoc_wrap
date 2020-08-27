/**
 * @file library.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "library.h"

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
    mongoc_cursor_t *cursor;
    cursor = mongoc_collection_find_with_opts(conn->collection, query, NULL, NULL);
    return cursor;
}

void insert(bson_t *doc, Connections_t* conn) {
    bson_error_t error;
    if (!mongoc_collection_insert_one (conn->collection, doc, NULL, NULL, &error)) {
        fprintf (stderr, "%s\n", error.message);
    }
}

void insert_string(char *doc, Connections_t *conn){
    bson_error_t error;
    bson_t *doc_bson = bson_new_from_json((const uint8_t *)doc, -1, &error);
    insert(doc_bson, conn);
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

void update_string(uint8_t *oid, char *doc, Connections_t *conn)
{
    bson_error_t error;
    bson_oid_t *oid_bson;
    for (int i = 0; i < 12; ++i)
    {
        oid_bson->bytes[i] = oid[i];
    }
    bson_t *doc_bson = bson_new_from_json((const uint8_t *)doc, -1, &error);
    update(oid_bson, doc_bson, conn);
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

void delete_(uint8_t *oid, Connections_t *conn)
{
    bson_oid_t oid_bson;
    for (int i = 0; i < 12; ++i)
    {
        oid_bson.bytes[i] = oid[i];
    }
    delete(&oid_bson, conn);
}