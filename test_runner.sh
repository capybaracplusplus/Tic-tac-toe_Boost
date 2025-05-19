#!/bin/bash

BLUE="\033[0;34m"
RED="\033[0;31m"
NC="\033[0m"

echo -e "${BLUE}Running tests with unittest discover...${NC}"

if python3 -m unittest discover -s tests -p "*.py"; then
    echo -e "${BLUE}The tests were successful${NC}"
else
    echo -e "${RED}Test failed!${NC}"
    exit 1
fi