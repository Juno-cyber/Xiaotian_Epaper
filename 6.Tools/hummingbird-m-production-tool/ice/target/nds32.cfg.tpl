#
# Andes AICE
#
# http://www.andestech.com
#

set number_of_core 05
for {set i 0} {$i < $number_of_core} {incr i} {
    jtag newtap $_CHIPNAME cpu$i -expected-id $_CPUTAPID
    set _TARGETNAME $_CHIPNAME.cpu$i
    target create $_TARGETNAME nds32_<_TARGET_ARCH> -endian little -chain-position $_TARGETNAME -coreid $i -variant $_ACE_CONF
    set _CONNECTED connected$i
    set $_CONNECTED 0
    $_TARGETNAME configure -event gdb-attach {
        if  {$_CONNECTED == 0} {
          #<--boot>
          set $_CONNECTED 1
          #targets $_TARGETNAME
        }
    }
    $_TARGETNAME configure -event gdb-detach {
        if {$_CONNECTED == 1} {
          set $_CONNECTED 0
        }
    }
}
