cmd_/home/sai/saik2/ELDD/modprobe/modules.order := {   echo /home/sai/saik2/ELDD/modprobe/mod1.ko;   echo /home/sai/saik2/ELDD/modprobe/mod2.ko; :; } | awk '!x[$$0]++' - > /home/sai/saik2/ELDD/modprobe/modules.order
