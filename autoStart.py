file = open ('/etc/rc.local','w')

file.write('''# Put your custom commands here that should be executed once
# the system init finished. By default this file does nothing.

wifi-live-or-reset
boot-complete-notify

# Uncomment the following line in order to reset the microntroller
# right after linux becomes ready

reset-mcu

# Uncomment the following line in order to disable kernel console
# debug messages, thus having a silent and clean serial communication
# with the microcontroller

#echo 0 > /proc/sys/kernel/printk


(sleep 0;python -u /root/DAI.py)&

exit 0
''')

file.close()
