#!/bin/bash
# heavily modified version of:
# https://raw.githubusercontent.com/kaihendry/dotfiles/master/bin/dwm_status
# Network speed stuff stolen from http://linuxclues.blogspot.sg/2009/11/shell-script-show-network-speed.html

# 2 intervals https://www.youtube.com/watch?v=6vTrVPpNodI
# 2 loops; should show up twice in ps, or 4x whenever mpstat is running
# temp: acpi -t

if pgrep kai; then	# be stricter; check pgrep options
echo "Already running, will not spawn another instance."; sleep 2; exit
fi

int=5
sep="|"

print_weather() { 
	curl wttr.in/Singapore?format="%c+%t\n" 
}

print_mpc() {		# requires unicode font, e.g. symbola
	title=$(mpc current)
	if [[ -z "$title" ]]; then title="Stopped"	# nothing playing
	elif [[ $(mpc | sed -n '2p') =~ paused ]]; then title=" $title" 
	else title=" $title"
	fi
	printf "%s" "$title"
}

print_network(){	# todo: SSID, down speed, vpn status
	network=$(grep wlp3s0 /proc/net/dev | cut -d ':' -f 2 | awk '{print $1" "$9}')
	# total bytes received/transmitted, then divide by $int
	received=$(cut -d' ' -f1 <<< "$network")
	#transmitted=$(cut -d' ' -f2 <<< "$network")
	printf "%s" "$received"
}

print_bat(){		# todo: icon (plugged/discharging), time left, text color?
	hash acpi || return 0
	batstat="$(cat /sys/class/power_supply/BAT*/status)"
	charge="$(cat /sys/class/power_supply/BAT*/capacity)%"
	#charge="$(awk '{ sum += $1 } END { print sum }' /sys/class/power_supply/BAT*/capacity)"
	if [[ "$batstat" = "Discharging" ]]; then
		battime=$(acpi -V | head -n1 | cut -d' ' -f5) # get rid of seconds
		charge="$charge ($battime)"
	fi
	# suspend when we close the lid
	#systemctl --user stop inhibit-lid-sleep-on-battery.service
	# On mains! no need to suspend
	#systemctl --user start inhibit-lid-sleep-on-battery.service
	printf "%s" "$charge"
}

print_cpu() {		# why do all 4 commands show in ps -faux?
	cpu=$(mpstat "$int" 1 | awk 'NR==4 {print $3"%\n"$4"%\n"$5"%"}' | sort | tail -1)
	printf "%s" "$cpu"
	# top | sed -n 3p
	# sar
}

print_mem(){ free -h | awk 'NR==2 {print $3}' | tr -d i; }

print_disk() { df -h /dev/sdb1 | tail -1 | tr -s ' ' | cut -d' ' -f4; }

print_date(){ TZ=Asia/Singapore date '+%a %d/%m %H:%M' ; }

while true; do print_weather > /tmp/dwmweather	
	sleep 30m
done &

while true; do
	xsetroot -name "$(< /tmp/dwmweather) $sep $(print_mpc) $sep $(print_bat) $sep $(print_cpu) $sep $(print_mem) $sep $(print_disk) $sep $(print_date)"
	sleep "$int"
done &
