#!/bin/sh

PATH=/usr/sbin:/usr/bin:/sbin:/bin:/usr/local/sbin:/usr/local/bin:$PATH

trap process_user_sig SIGUSR1

process_user_sig()
{
    echo "qt-app-watchdog is still alive!"
}

echo 'Waiting for qt-app startup....'
sleep 30
echo 'Watchdog starting....'
DROP_CACHE_COUNT=0

while :
do
    LEVEL=`runlevel | cut -f2 -d ' '`
    if [ "$LEVEL" = "6" -o "$LEVEL" = "0" -o "$LEVEL" = "1" ] ; then
        break
    fi

    QTAPP_PID=`pidof -s qt-app`
    RESTARTED="0"

    if [ -z "$QTAPP_PID" ] ; then
        echo 'qt-app is dead, restarting....'
        killall -9 qt-app
        /usr/bin/qt-app -d >/dev/null 2>/dev/null &
        RESTARTED="1"
    fi

    if [ "$RESTARTED" = "1" ] ; then
        sleep 30
        continue
    fi

    sleep 3
    echo "Check ..."
done
