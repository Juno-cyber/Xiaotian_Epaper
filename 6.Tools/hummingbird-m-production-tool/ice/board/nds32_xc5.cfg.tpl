set _CPUTAPID 0x1000063d
set _CHIPNAME nds32
#--ace-conf
jtag init
#--target

#--edm-passcode
#--soft-reset-halt
nds reset_memAccSize
nds memAccSize 0x00000000 0x80000000 32
nds memAccSize 0x80000000 0x100000000 32
nds memAccSize 0x00000000 0x800000 32

proc dma_mww {args} {
	nds mem_access bus
	eval mww $args
	nds mem_access cpu
}

proc dma_mwh {args} {
	nds mem_access bus
	eval mwh $args
	nds mem_access cpu
}

proc dma_mwb {args} {
	nds mem_access bus
	eval mwb $args
	nds mem_access cpu
}

proc dma_mdw {args} {
	nds mem_access bus
	eval mdw $args
	nds mem_access cpu
}

proc dma_mdh {args} {
	nds mem_access bus
	eval mdh $args
	nds mem_access cpu
}

proc dma_mdb {args} {
	nds mem_access bus
	eval mdb $args
	nds mem_access cpu
}

proc dma_read_buffer {args} {
	nds mem_access bus
	eval nds read_buffer $args
	nds mem_access cpu
}

proc dma_write_buffer {args} {
	nds mem_access bus
	eval nds write_buffer $args
	nds mem_access cpu
}

proc dma_mdb_w {args} {
	nds mem_access bus

	# get parameters
	set address [lindex $args 0]
	set count [lindex $args 1]

	set aligned [expr $address & 0xFFFFFFFC]
	set offset [expr $address & 0x3]
	eval mem2array wordarray 32 $aligned 1
	set answer [expr $wordarray(0) >> ($offset * 8)]
	set answer [expr $answer & 0xFF]
	set answer_byte [format %02X $answer]
	set answer_addr [format %08X $address]
	puts "0x$answer_addr: $answer_byte"

	nds mem_access cpu
}

proc dma_mwb_w {args} {
	nds mem_access bus

	# get parameters
	set address [lindex $args 0]
	set data [lindex $args 1]

	set aligned [expr $address & 0xFFFFFFFC]
	set offset [expr $address & 0x3]

	eval mem2array wordarray 32 $aligned 1

	set mask [expr 0xFF << ($offset * 8)]
	set mask [expr ~ $mask]
	set wordarray(0) [expr $wordarray(0) & $mask]

	set data [expr $data << ($offset * 8)]
	set wordarray(0) [expr $wordarray(0) | $data]

	eval array2mem wordarray 32 $aligned 1

	nds mem_access cpu
}
