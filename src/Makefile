.PHONY: all build install uninstall dvi dist distdir clean test gcov_report check leaks git valgrind

CXX = g++ -ggdb3 -std=c++17 -Wall -Werror -Wextra 
GCOV = -fprofile-arcs -ftest-coverage
GCOF_FLAGS = lcov --no-external -t "gcov_report" -o gcov_report.info -c -d .
OS = $(shell uname)
ifeq ($(OS), Linux)
  LIBS = -lgtest -lstdc++ -lpthread -lrt -lm 
  OPEN = xdg-open
  SOURCE_F = ./Build/3D_Viewer_2_0
else
  LIBS = -lgtest -lstdc++
  OPEN = open
  SOURCE_F = Build/3DViewer_2_0.app/Contents/MacOS/3DViewer_2_0
endif

DIST = controller \
			 gif_src \
			 model \
			 shaders \
			 view \
			 3DViewer_2_0.pro \
			 main.cpp \
			 Makefile \
			 manual.texi \
			 misc.h \
			 OpenGL.qrc

TAR = tar -cf
COPY_DIR = cp -f -R
COMPRESS = gzip -9f
DISTNAME = 3DViewer_2_0
DISTDIR = $(HOME)/3DViewer_2_0/

BUILD = Build/
FILES = model_test.cpp ./model/model.cpp ./model/mvpmatrix.cpp
TEST_FILES = model_test.cpp ./model/*.cpp ./model/*.h ./controller/*.h
APP = $(BUILD)3DViewer_2_0.app
APPDIR = $(HOME)/Applications/3DViewer_2_0/
REMOVE_RF = rm -rf
REMOVE_F = rm -f

all: gcov_report install

build: clean
	@mkdir $(BUILD)
	@cd $(BUILD) && qmake ../3DViewer_2_0.pro
	@make -C $(BUILD)

install: build dvi
	@mkdir $(APPDIR)
	@cp -rf $(APP) $(APPDIR)
	@$(REMOVE_RF) $(BUILD)

uninstall: 
	@$(REMOVE_RF) $(APPDIR)
	@$(REMOVE_RF) ./manual

dist: distdir
	(cd `dirname $(DISTDIR)` && $(TAR) $(DISTNAME).tar $(DISTNAME) && $(COMPRESS) $(DISTNAME).tar) 
	$(REMOVE_RF) $(DISTDIR)

distdir:
	@test -d $(DISTDIR) || mkdir -p $(DISTDIR)
	$(COPY_DIR) $(DIST) $(DISTDIR)/

dvi:
	@makeinfo --html manual.texi

test:
	@$(CXX) $(FILES) $(LIBS) -o model_test
	./model_test

gcov_report: clean 
	@$(CXX) $(GCOV) $(FILES) $(LIBS) -o gcov_report
	@./gcov_report
	@$(GCOF_FLAGS)
	@genhtml -o report gcov_report.info
	@$(OPEN) ./report/index.html

clean:
	@$(REMOVE_F) *.o *.a *.gcno *.gcda *.info model_test gcov_report *.out main
	@$(REMOVE_RF) ./report *.dSYM ./3D_Viewer_2_0_tar ./Build ./App
	@$(REMOVE_RF) ./manual *.dSYM
	@$(REMOVE_RF) /Build
	@$(REMOVE_RF) $(DISTDIR)/
	@$(REMOVE_F) $(HOME)/$(DISTNAME).tar.gz

# ==================================================================================== #
	
git: clean
	@git add -A
	@git commit -m 'fixed dist'
	@git push origin develop

check:
	@cppcheck --enable=all --suppress=missingInclude  --suppress=unusedFunction --std=c++17 --language=c++  $(TEST_FILES)
	@clang-format -n $(TEST_FILES)

leaks: test
	@CK_FORK=no leaks --atExit -- ./model_test
	@make clean

valgrind: test
	@valgrind -s --tool=memcheck --track-origins=yes --leak-check=full ./model_test
	@make clean
