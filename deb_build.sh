#!/bin/sh

echo "Build deb package ..."

name="ntapp"

rm -rf /tmp/$name-build
mkdir -p /tmp/$name-build/$name-1.0
cp -r * /tmp/$name-build/$name-1.0
cd /tmp/$name-build/$name-1.0
dh_make --createorig --single -e whyruby@gmail.com -c gpl

cd /tmp/$name-build/$name-1.0
dpkg-buildpackage -uc -us
cd ..
mv *.deb ~/
echo "Build a deb package at home directory."
