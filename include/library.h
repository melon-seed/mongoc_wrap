/**
 * @file library.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-08-19
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef MONGOCWRAPPER_LIBRARY_H
#define MONGOCWRAPPER_LIBRARY_H
#include <stdio.h>
#include <mongoc/mongoc.h>

typedef struct {
    mongoc_client_t *client;
    mongoc_database_t *db;
    mongoc_collection_t *collection;
} Connections_t;

typedef struct {
    int32_t doc_count;
    char** documents;
} Result_t;

void hello();

Connections_t* initialize(const char* url_string, const char* db_name, const char* collection_name);
void clear_up(Connections_t* conn);
mongoc_cursor_t* query(bson_t* query, Connections_t* conn);
void insert(bson_t *doc, Connections_t* conn);
void update(bson_oid_t *oid, bson_t *doc, Connections_t *conn);
void delete(bson_oid_t *oid, Connections_t *conn);
#endif //MONGOCWRAPPER_LIBRARY_H
