
ragel.output = ${QMAKE_FILE_IN_PATH}/${QMAKE_FILE_IN_BASE}    # output file (input filename without .rl)
ragel.input = RAGEL_FILES         # list of input files
ragel.commands = ragel ${QMAKE_FILE_IN} -o ${QMAKE_FILE_OUT}    #command
ragel.variable_out = SOURCES    # where output files should be placed
ragel.name = RAGEL    # name (for internal qmake usage)

QMAKE_EXTRA_COMPILERS += ragel



