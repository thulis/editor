CXX = g++
CXXFLAGS = -Wall --std=c++2a
LDFLAGS = -Iinclude -llua -ldl
OUTNAME = editor
OUTDIR = build
DEBUG = -g -Werror -fsanitize=address

lua_test: src/*.cpp
	${CXX} src/*.cpp ${CXXFLAGS} ${LDFLAGS} -o ${OUTDIR}/${OUTNAME} 

debug: src/*.cpp
	${CXX} src/*.cpp ${CXXFLAGS} ${DEBUG} ${LDFLAGS} -o ${OUTDIR}/${OUTNAME} 

clean: ${OUTDIR}/${OUTNAME}
	rm ${OUTDIR}/${OUTNAME}

run: ${OUTDIR}/${OUTNAME}
	./${OUTDIR}/${OUTNAME}
