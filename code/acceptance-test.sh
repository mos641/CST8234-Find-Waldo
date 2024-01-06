#!/bin/sh

#
# Acceptance Test script for Find Waldo Game
#
# Usage:
#     Compile with #define DEBUG and run AT.sh: all unit tests will PASS
#     Compile with no #define DEBUG and run AT.sh: all unit tests will FAIL
#
#   It is your sole responsilbilty to verify the previous 2 statements.
#
# #TODO
#   Compile with #define DEBUG and manually run the following tests:
#
#     ./find_waldo < ./unit_tests/fail_no_input.txt
#     echo $?
#
#     ./find_waldo < ./unit_tests/fail_one_guess.txt
#     echo $?
#
#     ./find_waldo < ./unit_tests/fail_ten_guesses.txt
#     echo $?
#
#   Verify that you see: 1 (i.e. fail)
#
# @version 1.0
#
# @author Gerald.Hurdle@AlgonquinCollege.com
#

TARGET=find_waldo
rc=0

for unit_test in ./unit_tests/unit_test_*.txt; do
    echo $unit_test
    ./$TARGET < $unit_test
    rc=`echo $?`
    if [ $rc = 0 ]
    then
        echo "PASS"
    else
        echo "FAIL"
    fi
    echo ""
done

exit 0
