TEMPLATE = subdirs
CONFIG += ordered
QT -= qt core gui

SUBDIRS = \
   src \
   tests

tests.depends = src
