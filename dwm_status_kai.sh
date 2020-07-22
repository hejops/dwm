#!/bin/bash
# heavily condensed version of:
# https://raw.githubusercontent.com/kaihendry/dotfiles/master/bin/dwm_status
# Network speed stuff stolen from http://linuxclues.blogspot.sg/2009/11/shell-script-show-network-speed.html

# separate intervals?
# temp: acpi -t

int=10
sep="|"

print_weather() {
	#echo WTR
	curl wttr.in/Singapore?format="%c+%t\n"
}

print_mpc() {
	#"" paused / "" playing
	#title="[$title]"; fi
	title=$(mpc current)
	if [[ $(mpc | sed -n '2p') =~ paused ]]; then icon="" 
	else icon=""
	fi
	echo -e "$icon $title"
}

print_network(){
	network=$(grep wlp3s0 /proc/net/dev | cut -d ':' -f 2 | awk '{print $1" "$9}')
	# total bytes received/transmitted
	received=$(cut -d' ' -f1 <<< "$network")
	transmitted=$(cut -d' ' -f2 <<< "$network")
	# include vpn status
	echo -e "$received"
}

print_bat(){		# todo: icon (plugged/discharging), time left, text color
	hash acpi || return 0
	onl="$(grep "on-line" <(acpi -V))"
	charge="$(awk '{ sum += $1 } END { print sum }' /sys/class/power_supply/BAT*/capacity)"
	if test -z "$onl"
	then
		# suspend when we close the lid
		#systemctl --user stop inhibit-lid-sleep-on-battery.service
		echo -e "${charge}%"
	else
		# On mains! no need to suspend
		#systemctl --user start inhibit-lid-sleep-on-battery.service
		echo -e "${charge}%"
	fi
}

print_cpu() {
	mpstat $(( int / 2 )) 1 | awk 'NR==4 {print $3"%\n"$4"%\n"$5"%"}' | sort | tail -1
	# top | sed -n 3p
	# sar
}

print_mem(){
	free -h | awk 'NR==2 {print $3}' | tr -d i
}

print_disk() {
	df -h /dev/sdb1 | tail -1 | tr -s ' ' | cut -d' ' -f4
}

print_date(){	# time zone
	TZ=Asia/Singapore date '+%a %d/%m %H:%M'
}

while true
do
	xsetroot -name "$(print_weather) $sep $(print_mpc) $sep $(print_bat) $sep $(print_cpu) $sep $(print_mem) $sep $(print_disk) $sep $(print_date)"
	sleep "$int"
done
