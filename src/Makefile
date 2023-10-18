CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror
LIBS = -lgtest -lgtest_main -lpthread
SRC_DIR = smartCalc
BUILD_DIR = build
ARCHIVE_DIR := archive_calculator
ARCHIVE_NAME := archive_calculator.tgz

.PHONY: all clean install uninstall dist tests gcov_report leak_application open clang

all: install

install:
	@if [ -d "$(BUILD_DIR)" ] && [ -f "$(BUILD_DIR)/smartCalc.app/Contents/MacOS/smartCalc" ]; then \
		echo "The SmartCalc application is already installed in the ${PWD}/$(BUILD_DIR) folder"; \
	else \
		mkdir -p $(BUILD_DIR); \
		cd $(SRC_DIR)/view && qmake && make && make clean && rm Makefile; \
		cd ../..; \
		mv $(SRC_DIR)/view/smartCalc.app $(BUILD_DIR); \
		echo "The SmartCalc application has been successfully installed and is in ${PWD}/$(BUILD_DIR)"; \
	fi

uninstall:
	@if [ -d "$(BUILD_DIR)" ]; then \
		rm -r $(BUILD_DIR); \
		echo "The application was successfully deleted"; \
	else \
		echo "The application is not installed"; \
	fi

clean:
	@-rm -rf test
	@-rm -rf print
	@-rm -rf test.info
	@-rm -rf *.gcda
	@-rm -rf *.gcno
	@-rm -rf report
	@-rm -rf leaks
	@-rm -rf *.dSYM
	@-rm -rf gcov_report*
	@echo "Deletion completed" 

dvi:
	open README.md

dist:
	@if [ -d "$(BUILD_DIR)" ] && [ -f "$(BUILD_DIR)/smartCalc.app/Contents/MacOS/smartCalc" ]; then \
		echo "Begin packaging process"; \
		mkdir -p $(ARCHIVE_DIR); \
		mv $(BUILD_DIR)/smartCalc.app $(ARCHIVE_DIR)/; \
		tar cvzf $(ARCHIVE_NAME) $(ARCHIVE_DIR)/; \
		rm -rf $(ARCHIVE_DIR)/; \
		echo "Build completed"; \
	else \
		make install; \
		make dist; \
	fi

print: clean
	@$(CXX) $(CXXFLAGS) $(SRC_DIR)/model/s21_model.cc -g -o print $(LIBS)
	@./print

tests: clean
	@$(CXX) $(CXXFLAGS) tests.cc $(SRC_DIR)/model/s21_model.cc -g -o test $(LIBS)
	@./test

gcov_report: clean
	@$(CXX) $(CXXFLAGS) --coverage tests.cc $(SRC_DIR)/model/s21_model.cc -o test $(LIBS)
	chmod +x *
	./test
	lcov -t "test" -o test.info --no-external -c -d . --ignore-errors mismatch
	genhtml -o report/ test.info
	open ./report/index.html

leaks: clean
	@echo ╭┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈╮
	@echo ┊--------------------MEMORY_LEAKS--------------------┊
	@echo ╰┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈╯
	@$(CXX) $(CXXFLAGS) tests.cc smartCalc/model/s21_model.cc -lgtest -o leaks
	CK_FORK=no leaks --atExit -- ./leaks
	@rm ./leaks

leak_application: 
	@echo ╭┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈╮
	@echo ┊--------------MEMORY_LEAKS_APPLICATION--------------┊
	@echo ╰┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈╯
	CK_FORK=no leaks --atExit -- ./$(BUILD_DIR)/smartCalc.app/Contents/MacOS/smartCalc

open:
	@if [ -d "$(BUILD_DIR)" ] && [ -f "$(BUILD_DIR)/smartCalc.app/Contents/MacOS/smartCalc" ]; then \
		./$(BUILD_DIR)/smartCalc.app/Contents/MacOS/smartCalc; \
	else \
		echo "application not found"; \
	fi

clang:
	@echo ╭┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈╮
	@echo ┊--------------------CLANG_FORMAT--------------------┊
	@echo ╰┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈╯
	@find . \( -name '*.h' -o -name '*.cc' \) -print0 | xargs -0 clang-format -n -style=Google
