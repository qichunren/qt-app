#include "web_server.h"
#include "third_libs/mongoose.h"
#include <QDebug>
#include <pthread.h>
#include <QFileInfo>
#include <QFile>
#include "database.h"
#include <json/json.h>

static bool running_flag;
static struct mg_server *server1, *server2;
static pthread_t thread1, thread2;
static int thread1_return_value, thread2_return_value;
static const char *web_server_root;
static const char *web_server_port;

static int serve_static_assets(struct mg_connection *conn) {
    qDebug() << "template";
    int file_path_length = strlen(conn->uri) + 1;
    char local_res_file_path[file_path_length];

    strcpy(local_res_file_path, ":");
    strcat(local_res_file_path, conn->uri);
    QFile cssFile(local_res_file_path);
        qDebug() << local_res_file_path;
    if (!cssFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "template error";
        return MG_HTTP_ERROR;
    }

    QTextStream in(&cssFile);

    QString file_path(local_res_file_path);
        qDebug() << file_path;
    if(file_path.endsWith(".js")) {
        mg_send_header(conn, "Content-Type", "application/javascript; charset=utf-8"); // application/javascript; charset=utf-8
    } else if (file_path.endsWith(".css")){
        mg_send_header(conn, "Content-Type", "text/css; charset=utf-8");
    }

    mg_printf_data(conn, "%s",
                   (char *) in.readAll().toUtf8().data());
    return MG_TRUE;
}

static int serve_get_request(struct mg_connection *conn) {
    qDebug() << "GET" << conn->uri << strlen(conn->uri);
    if(strcmp(conn->uri, "/") == 0) {
        QFile indexFile(":/html/static/index.html");

        if (!indexFile.open(QIODevice::ReadOnly | QIODevice::Text))
                return 1;

        QTextStream in(&indexFile);
        mg_send_header(conn, "Content-Type", "text/html; charset=utf-8");
        mg_printf_data(conn, "%s",
                       (char *) in.readAll().toUtf8().data());
        return MG_TRUE;
    } else if (8 <= strlen(conn->uri) && ( strncmp("/assets/", conn->uri, 8) == 0 )) { // uri start with '/assets/'
        return serve_static_assets(conn);
    } else if(strcmp(conn->uri, "/setting") == 0) {
        mg_printf(conn, "HTTP/1.1 302 Moved\r\nLocation: %s\r\n\r\n", "/tickers.html");
        return MG_FALSE;
    } else if(strcmp(conn->uri, "/tickers.html") == 0) {
        mg_send_header(conn, "Content-Type", "text/html; charset=utf-8");
        mg_printf_data(conn, "%s",
                       (char *) "tickers");
        return MG_TRUE;
    } else if(strcmp(conn->uri, "/logo.png") == 0) {
        QFile indexFile(":/static/images/30.png");
        QTextStream in(&indexFile);
        qDebug() << in.readAll();
        mg_send_header(conn, "Content-Type", "image/png");
        mg_printf_data(conn, "%s",
                       (char *) in.readAll().toUtf8().data());
        return MG_TRUE;

    } else if(strcmp(conn->uri, "/stations.json") == 0) {
        QList<QString> stations = Database::get_all();
        json_object * jobj = json_object_new_object();
        json_object *jarray = json_object_new_array();
        for(int i=0; i<stations.length(); i++) {
            QByteArray ba = stations.at(i).toUtf8();
            char *c_str2 = ba.data();
            json_object *jstring = json_object_new_string(c_str2);
            json_object_array_add(jarray,jstring);

        }
        json_object_object_add(jobj,"stations", jarray);
        mg_send_header(conn, "Content-Type", "application/json; charset=utf-8");

        mg_printf_data(conn, "%s",
                       (char *) json_object_to_json_string(jobj));
        return MG_TRUE;
    } else {
        return MG_HTTP_ERROR;
    }
}

static int serve_post_request(struct mg_connection *conn) {

}

static int serve_request(struct mg_connection *conn) {
    if (strcmp(conn->request_method, "GET") == 0) {
        return serve_get_request(conn);
    } else if (strcmp(conn->request_method, "POST") == 0) {
        return serve_post_request(conn);
    }
}

// Start a browser and hit refresh couple of times. The replies will
// come from both server instances.
static int ev_handler(struct mg_connection *conn, enum mg_event ev) {
  if (ev == MG_REQUEST) {
      return serve_request(conn);
  } else if (ev == MG_AUTH) {
    return MG_TRUE;
  } else {
    return MG_FALSE;
  }
}

static void *serve(void *server) {
  while(running_flag) { mg_poll_server((struct mg_server *) server, 1000); }
  return NULL;
}

WebServer::WebServer(const char *document_root, const char *port, QObject *parent) :
    QObject(parent)
{
    running_flag = false;
    web_server_root = document_root;
    web_server_port = port;
}

bool WebServer::is_running() {
    return running_flag;
}

void WebServer::start() {
    if(running_flag) return; // Already started.

    server1 = mg_create_server((void *) "1", ev_handler);
    server2 = mg_create_server((void *) "2", ev_handler);
    // Make both server1 and server2 listen on the same sockets
    mg_set_option(server1, "listening_port", web_server_port);
    mg_set_option(server1, "document_root", web_server_root);
    mg_set_option(server2, "listening_port", web_server_port);
    mg_set_option(server2, "document_root", web_server_root);
    mg_copy_listeners(server1, server2);
    //  mg_start_thread(serve, server1);
    //  mg_start_thread(serve, server2); // I did not use this lib function to start thread, I use pthread.
    running_flag = true;
    thread1_return_value = pthread_create( &thread1, NULL, serve, (void*) server1);
    thread2_return_value = pthread_create( &thread2, NULL, serve, (void*) server2);
}

void WebServer::stop() {

    if(running_flag) {
        running_flag = false;
        pthread_join( thread1, NULL);
        pthread_join( thread2, NULL);
        mg_destroy_server(&server1);
        mg_destroy_server(&server2);
    }
}
