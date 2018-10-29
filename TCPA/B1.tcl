
set ns [new Simulator]
$ns color 1 RED
$ns color 2 BLUE

set nf [open output.nam w]
$ns namtrace-all $nf

set nf [open b.tr w]
$ns trace-all $nf

proc finish {} {
    global ns nf
    $ns flush-trace
    close $nf
    exec nam output.nam &
    exit 0
}

set n0 [$ns node] 
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

#create duplex link

$ns duplex-link $n0 $n2 2Mb 10ms DropTail
$ns duplex-link $n1 $n2 2Mb 10ms DropTail
$ns duplex-link $n2 $n3 1.7Mb 10ms DropTail

#orientation
$ns duplex-link-op $n0 $n2 orient right-down
$ns duplex-link-op $n1 $n2 orient right-up
$ns duplex-link-op $n2 $n3 orient right

$ns queue-limit $n2 $n3 5
$ns duplex-link-op $n2 $n3 queuePos 0.5


#tcp

set tcp [new Agent/TCP] 
$tcp set class_ 2
$ns attach-agent $n0 $tcp

set sink [new Agent/TCPSink]
$ns attach-agent $n3 $sink
$ns connect $tcp $sink
$ns set fid_ 1

#ftp
set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ftp set type_ FTP



#udp
set udp [new Agent/UDP]
$ns attach-agent $n1 $udp

set null [new Agent/Null]
$ns attach-agent $n3 $null
$ns connect $udp $null
$ns set fid_ 2

#cbr 


set cbr [new Application/Traffic/CBR] 
$cbr attach-agent $udp
$cbr set type_ CBR
$cbr set packetsize_ 1000
$cbr set rate_ 1Mb
$cbr set random_ false

$ns at 0.1 "$cbr start"
$ns at 0.3 "$ftp start"
$ns at 0.5 "$ftp stop"
$ns at 0.7 "$cbr stop"
$ns at 0.9 "finish"

$ns run

