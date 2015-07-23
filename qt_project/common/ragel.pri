
# where generated sources should be placed

# ------------ ragel compiler settings ------------

# output file: place in build dir, with "ragel_" prefix and without ".rl" suffix
ragel.output = $$OUT_PWD/ragel_${QMAKE_FILE_IN_BASE}    

# ragel input files should be given in RAGEL_FILES variable
ragel.input = RAGEL_FILES

# command that should be executed to compile file
unix {
    ragel.commands = $$PWD/../../util/ragel_bin/linux/ragel ${QMAKE_FILE_IN} -o ${QMAKE_FILE_OUT}
}

win32 {
    ragel.commands = $$PWD/../../util/ragel_bin/windows/ragel.exe ${QMAKE_FILE_IN} -o ${QMAKE_FILE_OUT}
}


# variable to which generated filenames should be added
ragel.variable_out = SOURCES

# name (for internal qmake usage)
ragel.name = RAGEL



# add ragel as qmake extra compiler

QMAKE_EXTRA_COMPILERS += ragel



