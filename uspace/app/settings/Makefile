USPACE_PREFIX = ../..


# TODO: Should be just "AppKit", rest is transitive dependencies. "AppKit" needs to stay first !
#LIBS =  AppKit gui draw softrend compress  math

#This is temporary and should be remove when SettingsClient.c/h are moved into a proper library.
EXTRA_CFLAGS = -I.

BINARY = settings
SOURCES = settings.c \
        SettingsClient.c \
        DataStore.c \
        DataStoreJSON.c \
        cJSON.c \




include $(USPACE_PREFIX)/Makefile.common
