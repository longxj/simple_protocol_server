use strict;

if( $#ARGV < (3 - 1))
{
    print "Usage: perl getcpunet.pl  ethname  samplefrequence(sec: how often to take one sample) samplenumber\n";
    exit(0);
}


my $eth_name = $ARGV[0];
my $sleepTime = $ARGV[1];
my $times = $ARGV[2];
my $time = 0;

open  fcpu, ">cpu.data" or die "Error: can not create cpu.data";
open  fnet, ">net.data" or die "Error: can not create net.data";

my $send_last = `ifconfig $eth_name | grep bytes | awk '{print \$6}' | awk -F : '{print \$2}'`;
my $recv_last = `ifconfig $eth_name | grep bytes | awk '{print \$2}' | awk -F : '{print \$2}'`;

while( $times > 0 )
{
    sleep($sleepTime);

    print "$times ";

    #get data for cpu
    my $ret = `top -n 1 | head -n 8 | tail -n 1 |awk '{print $9}'`;
    chomp($ret);
    print  fcpu "$time\t$ret\n";

    #get data for net
    my $send_now = `ifconfig $eth_name | grep bytes | awk '{print \$6}' | awk -F : '{print \$2}'`;
    my $recv_now = `ifconfig $eth_name | grep bytes | awk '{print \$2}' | awk -F : '{print \$2}'`;

    my $send_rate = ($send_now - $send_last) / $sleepTime; #Kb
    my $recv_rate = ($recv_now - $recv_last) / $sleepTime; #Kb

    $send_rate = $send_rate / 100;
    $recv_rate = $recv_rate / 100;
    print fnet "$time\t$recv_rate\n";

    $send_last = $send_now;
    $recv_last = $recv_now;
    $time = $time + $sleepTime;
    $times = $times - 1;
}

close(fcpu);
close(fnet);
print "\n";
print "Info: done!\n";
