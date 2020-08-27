//
//

#include "library.h"



int main()
{
    char *url_str = "mongodb://localhost:27017";
    char *db_name = "db_name";
    char *collection_name = "coll_name";
    Connections_t *conn = initialize(url_str, db_name, collection_name);
    // 1. insert
    // bson_t *doc = NULL;
    // doc = BCON_NEW("hello", BCON_UTF8("world"), "int", BCON_INT64(12));
    // insert(doc, conn);
    char *doc_string = "{\"hello\":\"world\",\"int\":12}";
    insert_string(doc_string, conn);
    // 2. query
    const bson_t *query_doc = NULL;
    bson_t *doc = bson_new_from_json((const uint8_t *)doc_string, -1, NULL);
    mongoc_cursor_t *cursor = query(doc, conn);
    bson_oid_t *oid = NULL;
    if (! cursor)
    {
        exit(1);
    }
    while (mongoc_cursor_next(cursor, &query_doc))
    {
        bson_iter_t iter;
        bson_iter_init(&iter, query_doc);
        bson_iter_find_case(&iter, "_id");
        oid = bson_iter_oid(&iter);
        char *str = bson_as_canonical_extended_json(query_doc, NULL);
        printf("%s\n", str);
        bson_free(str);
    }
    // 3. update
    bson_t *update_doc = NULL;
    update_doc = BCON_NEW("$set", "{", "int", BCON_INT64(24), "updated", BCON_BOOL(true), "}");
    update(oid, update_doc, conn);
    uint8_t oid_[12];
    for (int i = 0; i < 12; ++i)
    {
        oid_[i] = oid->bytes[i];
    }
    // char *update_doc_string = "$set:{\"int\":24,\"updated\":1}";
    // update_string(oid_,update_doc_string, conn);
    // 4. delete
    // delete(oid, conn);
    delete_(oid_, conn);
    //must clear_up
    clear_up(conn);
    return 0;
}