#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

MINISHELL="./minishell"
PASSED=0
FAILED=0

# Helper function to run a test and compare with bash
run_test() {
    local test_name="$1"
    local command="$2"

    echo -e "${YELLOW}[$test_name]${NC} $command"

    # Run the command in bash and capture output (remove trailing newlines)
    eval "$command" > /tmp/bash_output.txt 2>&1
    sed -i '/^$/d' /tmp/bash_output.txt
    # Remove _= line for env command
    sed -i '/^_=/d' /tmp/bash_output.txt

    # Run the command in minishell and capture output
    # Remove: first line (command echo), prompt prefix, last prompt-only line, and empty lines
    echo "$command" | $MINISHELL 2>&1 | \
        tail -n +2 | \
        head -n -1 | \
        sed 's/^minishell\$ //' | \
        sed '/^$/d' | \
        sed '/^_=/d' > /tmp/minishell_output.txt

    # Compare outputs
    if diff -q /tmp/bash_output.txt /tmp/minishell_output.txt > /dev/null 2>&1; then
        echo -e "${GREEN}✓ PASSED${NC}"
        ((PASSED++))
    else
        echo -e "${RED}✗ FAILED - Output differs:${NC}"
        echo -e "${BLUE}Expected (bash):${NC}"
        cat /tmp/bash_output.txt | sed 's/^/  /'
        echo -e "${BLUE}Got (minishell):${NC}"
        cat /tmp/minishell_output.txt | sed 's/^/  /'
        ((FAILED++))
    fi
    echo ""
}

# Header
echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}  Minishell Test Suite${NC}"
echo -e "${BLUE}========================================${NC}"
echo ""

# Check if minishell exists
if [ ! -f "$MINISHELL" ]; then
    echo -e "${RED}Error: $MINISHELL not found. Please run 'make' first.${NC}"
    exit 1
fi

echo -e "${YELLOW}[1/5] Basic Commands Test${NC}"
echo "-----------------------------------"
run_test "ls command" "ls"
run_test "pwd command" "pwd"
run_test "echo simple" "echo hello"
run_test "echo with args" "echo hello world"
run_test "echo with quotes" "echo \"hello world\""

echo -e "${YELLOW}[2/5] Redirection Test${NC}"
echo "-----------------------------------"

# 出力リダイレクトのテスト（手動検証）
rm -f minishell_test.txt
echo "echo test > minishell_test.txt" | $MINISHELL 2>&1 > /dev/null
echo -e "${YELLOW}[output redirection]${NC} echo test > minishell_test.txt"
if [ -f minishell_test.txt ] && [ "$(cat minishell_test.txt)" = "test" ]; then
    echo -e "${GREEN}✓ PASSED${NC}"
    ((PASSED++))
else
    echo -e "${RED}✗ FAILED${NC}"
    if [ -f minishell_test.txt ]; then
        echo "Expected: test"
        echo "Got: $(cat minishell_test.txt)"
    else
        echo "File was not created"
    fi
    ((FAILED++))
fi
echo ""

# 入力リダイレクトのテスト
run_test "input redirection" "cat < minishell_test.txt"

# 追記リダイレクトのテスト（手動検証）
echo "echo append >> minishell_test.txt" | $MINISHELL 2>&1 > /dev/null
echo -e "${YELLOW}[append redirection]${NC} echo append >> minishell_test.txt"
expected=$'test\nappend'
actual=$(cat minishell_test.txt)
if [ "$actual" = "$expected" ]; then
    echo -e "${GREEN}✓ PASSED${NC}"
    ((PASSED++))
else
    echo -e "${RED}✗ FAILED${NC}"
    echo "Expected:"
    echo "$expected" | sed 's/^/  /'
    echo "Got:"
    echo "$actual" | sed 's/^/  /'
    ((FAILED++))
fi
echo ""

rm -f minishell_test.txt

echo -e "${YELLOW}[3/5] Pipe Test${NC}"
echo "-----------------------------------"
run_test "simple pipe" "echo hello | cat"
run_test "ls with grep" "ls | grep minishell"
run_test "multiple pipes" "ls | grep .c | cat"

echo -e "${YELLOW}[4/5] Edge Cases Test${NC}"
echo "-----------------------------------"
run_test "empty input" ""
run_test "spaces only" "   "
run_test "multiple spaces" "echo    multiple   spaces"
run_test "tabs" "echo tab separated"

echo -e "${YELLOW}[5/5] Built-in Commands Test (if implemented)${NC}"
echo "-----------------------------------"
run_test "cd command" "cd /tmp"
run_test "export command" "export TEST=value"
run_test "unset command" "unset TEST"
run_test "exit command" "exit"

# ここに追加のテストを書く
# 例: run_test "test name" "command"

# Summary
echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}  Test Summary${NC}"
echo -e "${BLUE}========================================${NC}"
echo -e "${GREEN}Passed: $PASSED${NC}"
echo -e "${RED}Failed: $FAILED${NC}"
echo -e "Total:  $((PASSED + FAILED))"
echo ""

# Clean up
rm -f /tmp/minishell_output.txt /tmp/bash_output.txt /tmp/minishell_test.txt

# Exit with appropriate code
if [ $FAILED -gt 0 ]; then
    echo -e "${RED}Some tests failed.${NC}"
    exit 1
else
    echo -e "${GREEN}All tests passed!${NC}"
    exit 0
fi
