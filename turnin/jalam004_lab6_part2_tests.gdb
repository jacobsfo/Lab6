# Test file for "Lab6"


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

# Example test:
test "Intialize to PORTB => PORTB:0x01"
timeContinue 1
expectPORTB 0x01
checkResult

# Add tests below

test "1 period passed => PORTB:0x02"
timeContinue 1
expectPORTB 0x02
checkResult

#test "1 period passed => PORTB:0x04"
#timeContinue 1
#expectPORTB 0x04
#checkResult

test "2 periods passed => PORTB:0x02"
timeContinue 2
expectPORTB 0x02
checkResult

test "PINA:0xFE => PORTB:0x02"
timeContinue 1
setPINA 0xFE
expectPORTB 0x02
checkResult

test "PINA:0xFE => PORTB:0x02"
setPINA 0xFE
expectPORTB 0x02
checkResult

test "PINA:0xFF => PORTB:0x02"
setPINA 0xFF
expectPORTB 0x02
checkResult

test "Pressing button restarts game, 3 periods passed PINA:0xFE => PORTB:0x04"
setPINA 0xFE
timeContinue 3
expectPORTB 0x04
checkResult

test "Releasing button does not restart, 3 periods passed, PINA:0xFF => PORTB:0x04"
setPINA 0xFF
timeContinue 3
expectPORTB 0x02
checkResult









# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
