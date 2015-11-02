PWD = $(shell pwd)
TEX_DIR = tex
TEX_FILES = $(shell ls -d tex/*)
SOURCE_CODE_FILES = $(shell ls -d source_code/*)

TEX_FILE_ENTRY = codebook.tex

TARGET_DIR = $(PWD)/dist
TARGET_NAME = codebook.pdf
TARGET = $(TARGET_DIR)/$(TARGET_NAME)

##################################################

FLAGS = \
    -interaction=nonstopmode \
    -shell-escape \
    -output-directory=$(TARGET_DIR) \
    -jobname=$(TARGET_NAME) \

TIMES = 2

SHELL = bash

##################################################

.PHONY: all clean


all: $(TARGET_DIR)/$(TARGET_NAME)

clean:
	rm -rf $(TARGET_DIR)/*

$(TARGET_DIR)/$(TARGET_NAME): $(TEX_FILES) $(SOURCE_CODE_FILES)
	cd $(TEX_DIR); \
	for ((i=0; i<$(TIMES); ++i)); do \
	  xelatex $(FLAGS) $(TEX_FILE_ENTRY) || break; \
	done
