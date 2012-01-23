set term post color solid
set output "cpunetvstime.ps"
set grid
set ytics nomirror
set y2tics
set xlabel "time(sec)"
set ylabel "cpu%"
set y2label "net(100k)"
set title "cpu&net vs time"
plot "cpu.data" u 1:2 w l lt 1 axes x1y1, "net.data" u 1:2 w l lt 3 axes x1y2

