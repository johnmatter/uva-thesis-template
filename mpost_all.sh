#!/bin/bash
find . -type d -name "chap*" -exec bash -c \
    'cd $1; for feynman in ./*.mp; do if [ -f "$feynman" ]; then mpost $feynman; fi; done' none {}  \;
