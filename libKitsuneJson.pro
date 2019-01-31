TEMPLATE = subdirs
CONFIG += ordered
QT -= qt core gui
CONFIG += c++14

SUBDIRS = \
   src \
   tests

tests.depends = src
