#
# Andes AICE
#
# http://www.andestech.com
#

interface aice
aice desc "Andes AICE adapter"
aice serial "C001-42163"
aice vid_pid 0x1CFC 0x0000
#aice port aice_pipe
#aice adapter aice_adapter
aice port aice_usb
#aice misc_config tracer_disable
#aice misc_config usb_log_enable 1
aice misc_config usb_pack_disable
#aice misc_config usb_pack_level 0

reset_config trst_and_srst
