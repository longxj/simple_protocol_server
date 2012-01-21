set xtics nomirror
set ytics nomirror
set y2tics
set xlabel "time(sec)"
set y1label "cpu%"
set y2label "net(100k)"
set title "cpu&net vs time"
plot "cpunet.data" u 1:2 w l lt 1 axes xy1
plot "cpunet.data" u 1:3 w l lt 3 axes xy2

