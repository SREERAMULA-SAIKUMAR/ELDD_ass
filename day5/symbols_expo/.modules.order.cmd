cmd_/home/sai/saik2/ELDD/symbols_expo/modules.order := {   echo /home/sai/saik2/ELDD/symbols_expo/src.ko;   echo /home/sai/saik2/ELDD/symbols_expo/dest.ko; :; } | awk '!x[$$0]++' - > /home/sai/saik2/ELDD/symbols_expo/modules.order