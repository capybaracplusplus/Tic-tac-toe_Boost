#!/bin/bash

BLUE="\033[0;34m"
RED="\033[0;31m"
NC="\033[0m"

echo -e "${BLUE}Running matchmaking.py tests...${NC}"

if python3 tests/matchmaking.py; then
    echo -e "${BLUE}The test was successful${NC}"
else
    echo -e "${RED}Test failed!${NC}"
    exit 1
fi