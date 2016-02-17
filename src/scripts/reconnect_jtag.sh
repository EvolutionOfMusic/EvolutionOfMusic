#Nancy Minderman
# nancy.minderman@ualberta.ca
# nancy.minderman@ece.ualberta.ca
# This script kills all jtagd daemons and reconnects using jtaconfig

JTAGCONFIG=/OPT/altera/12.1/tools/quartus/bin/jtagconfig

/usr/bin/killall jtagd
$JTAGCONFIG
