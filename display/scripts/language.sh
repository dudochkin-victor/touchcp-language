#!/bin/sh

langdata=/var/lib/duicontrolpanel-displaylanguageapplet/lang
langregexp='^[a-z][a-z](_[A-Z][A-Z])?(\.[[:alnum:]_-]+)?(@[[:alnum:]_-]+)?$'
# default
langid=en_US.UTF-8

if [ -r $langdata ]; then
    langid=$(egrep $langregexp $langdata | head -1)
    # some conversion needs from libicu ids to posix ids
    if [ "$langid" == "en" ]; then
        langid=en_GB
    elif [ "$langid" == "es_419" ]; then
        langid="es_MX"  # FIXME?
    fi
fi
export LANG=$langid
