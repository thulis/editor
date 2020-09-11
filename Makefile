CXX = clang++
CXXFLAGS = -Wall --std=c++2a
LFLAGS = -llua -ldl
OUTNAME = editor
OUTDIR = build
DEBUG = -g -Werror -fsanitize=address

lua_test: src/*.cpp
	${CXX} src/*.cpp ${CXXFLAGS} -o ${OUTDIR}/${OUTNAME} ${LFLAGS}

debug: src/*.cpp
	${CXX} src/*.cpp ${CXXFLAGS} ${DEBUG} -o ${OUTDIR}/${OUTNAME} ${LFLAGS}

clean: ${OUTDIR}/${OUTNAME}
	rm ${OUTDIR}/${OUTNAME}

run: ${OUTDIR}/${OUTNAME}
	./${OUTDIR}/${OUTNAME}
