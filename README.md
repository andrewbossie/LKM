# LKM Process Identifier 

# Description 

This is a loadable kernel module that will iteratively display process information for children of a user-defined PID. 

# Installation

On Linux, make with makefile. Run 'sudo insmod' on the newly created kernel object including user-defined PID number. Display information after loading module by calling 'dmesg' on your logfile location (usually var/log/syslog)
