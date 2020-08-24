/**
 * @file library.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef MONGOCWRAPPER_LIBRARY_H
#define MONGOCWRAPPER_LIBRARY_H
#include <stdio.h>
#include <mongoc.h>

/**
 * @brief Connections_t struct
 * 
 */
typedef struct {
    mongoc_client_t *client;
    mongoc_database_t *db;
    mongoc_collection_t *collection;
} Connections_t;

/**
 * @brief 
 * 
 */
typedef struct {
    int32_t doc_count;
    char** documents;
} Result_t;

/**
 * @brief 
 * 
 * @param url_string 
 * @param db_name 
 * @param collection_name 
 * @return Connections_t* 
 */
Connections_t* initialize(const char* url_string, const char* db_name, const char* collection_name);
/**
 * @brief free all Connections_t member
 * 
 * @param conn 
 */
void clear_up(Connections_t* conn);
/**
 * @brief query db
 * 
 * @param query 
 * @param conn 
 * @return mongoc_cursor_t* 
 */
mongoc_cursor_t* query(bson_t* query, Connections_t* conn);
/**
 * @brief 
 * 
 * @param doc 
 * @param conn 
 */
void insert(bson_t *doc, Connections_t* conn);
/**
 * @brief 
 * 
 * @param doc 
 * @param conn 
 */
void insert_string(char *doc, Connections_t *conn);
/**
 * @brief 
 * 
 * @param oid 
 * @param doc 
 * @param conn 
 */
void update(bson_oid_t *oid, bson_t *doc, Connections_t *conn);

void update_string(uint8_t *oid, char *doc, Connections_t *conn);
/**
 * @brief 
 * 
 * @param oid 
 * @param conn 
 */
void delete(bson_oid_t *oid, Connections_t *conn);

void delete_(uint8_t *oid, Connections_t *conn);
#endif //MONGOCWRAPPER_LIBRARY_H
