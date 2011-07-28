#!/bin/bash
find $1/devices/src/ $1/libsherlog/src/ $1/stmtool/  -type f | grep -E '(\.c$)|(\.cpp$)|(\.h$)|(\.hpp$)'|grep -v -E '(moc_)|(qrc_)|(ui_)|(^.+\..+\.)' | xargs wc -l

