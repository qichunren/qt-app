#
# Regular cron jobs for the qt-web-app package
#
0 4	* * *	root	[ -x /usr/bin/qt-web-app_maintenance ] && /usr/bin/qt-web-app_maintenance
