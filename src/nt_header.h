// Add C includes here

#define OrganizationName "ShanghaiNT"
#define OrganizationDomain "shanghainovotech.com"
#define APP_DESC "Shanghai NT PIS for 160KM/H train."
#define APP_NAME "qt-app"
#define APP_VERSION "v1.0.1"
#define USER_AGENT APP_NAME " " APP_VERSION
#define BUILD_DATE ""__TIME__"," __DATE__

#define ERROR_FILE     "/var/log/ntpis/error.log"
#define INFO_FILE      "/var/log/ntpis/info.log"
#define GPS_LOG_FILE   "/var/log/ntpis/gps.log"

#define DATA_DIR  "/var/lib/ntpis/"
#define DATA_FILE "/var/lib/ntpis/data.db"

#define PID_FILE "/tmp/ntpis.pid"
#define NTLocalServer_socket "ntpis.socket"

#include <unistd.h>

#if defined __cplusplus
// Add C++ includes here
#include <QDebug>
#include <QDateTime>
#include <QTimer>
#include <cstdlib>
#include <cstdio>
#include <iostream>

#endif
