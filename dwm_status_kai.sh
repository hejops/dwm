#!/bin/bash
# heavily modified version of:
# https://raw.githubusercontent.com/kaihendry/dotfiles/master/bin/dwm_status
# Network speed stuff stolen from http://linuxclues.blogspot.sg/2009/11/shell-script-show-network-speed.html
# if i ever decide to learn c, this would be a nice project
# see also: https://github.com/Cornu/dwmstatus/blob/master/status.c
# https://github.com/joestandring/dwm-bar	bloat
# https://github.com/jiji606/dwm-status/blob/master/dwm-status.sh	ok i guess

# polybar, lemonbar, succade

# 2 intervals https://www.youtube.com/watch?v=6vTrVPpNodI
# temp: acpi -t

# using pgrep causes this script to check itself lol

int=5
sep="|"

# TODO: check deps
# TODO: use awk on everything

weather_count=0
get_weather() {
	weather=$(curl -s wttr.in/Munich?format="%c+%t\n") # 2>&1)
	[[ "$weather" =~ Unknown|fritz|requests ]] && weather="Error"

}

print_weather() {	# needs testing
	if [[ "$weather_count" -eq 0 ]]; then
		get_weather
		weather_count=360		# every 30 min
	fi
	printf "%s" "$weather"
	((weather_count-=1))
}

print_mpc() {		# requires unicode font, e.g. symbola
	title=$(mpc current)
	if [[ -z "$title" ]]; then
		title="Stopped"	# nothing playing
	elif [[ $(mpc | sed -n '2p') =~ paused ]]; then
		title=" $title" 
	else
		title=" $title"
	fi
	printf "%s" "$title"
}

print_network(){
	state=$(nmcli)

	if [[ "$state" =~ 'enp4s0: unmanaged' ]]; then
		ssid="ethernet"
	elif [[ "$state" =~ 'connected to' ]]; then
		ssid=$(<<< "$state" sed -rn 's|.*connected to (.+)|\1|p')	# use sed instead
	else
		ssid="error"
	fi

	if  [[ -z "$ssid" ]]; then
		ssid="No network"
	elif ip tuntap show | grep -q queue; then
		ssid="[$ssid]"
	elif [[ "$ssid" =~ LRZ ]]; then	# ip tuntap can't be used due to "persist" option
		ssid="{$ssid}"
	fi
	printf "%s" "$ssid"

	#network=$(grep wlp3s0 /proc/net/dev | cut -d ':' -f 2 | awk '{print $1" "$9}')
	# total bytes received/transmitted, then divide by $int
	#received=$(cut -d' ' -f1 <<< "$network")
	#transmitted=$(cut -d' ' -f2 <<< "$network")
}

print_bat(){
	# TODO: icon (plugged/discharging), text color?
	# hash acpi || return 0
	# why disappears???
	batstat="$(cat /sys/class/power_supply/BAT*/status)"
	charge="$(cat /sys/class/power_supply/BAT*/capacity)%"
	#charge="$(awk '{ sum += $1 } END { print sum }' /sys/class/power_supply/BAT*/capacity)"
	if [[ "$batstat" = "Discharging" ]]; then
		battime=$(acpi -V | head -n1 | cut -d' ' -f5) # get rid of seconds
		charge="$charge ($battime)"
		[[ "$battime" =~ ^\d:\d{2}$ ]] && notify-send -u critical "Critical battery" "$battime"
	fi
	# suspend when we close the lid
	#systemctl --user stop inhibit-lid-sleep-on-battery.service
	# On mains! no need to suspend
	#systemctl --user start inhibit-lid-sleep-on-battery.service
	printf "%s" "$charge"
}

print_cpu() {
	cpu=$(mpstat "$int" 1 | awk 'NR==4 {print $3"%\n"$4"%\n"$5"%"}' | sort | tail -1)
	printf "%s" "$cpu"
	# top | sed -n 3p
	# sar
}

print_mem(){ free -h | awk 'NR==2 {print $3}' | tr -d i; }	# line 3, field 3

print_disk() {		# if hdd not (yet) mounted, shows ~ instead
	# TODO: use awk
	# TODO: use name instead, designation depends on port!
	df_output=$(df -h)
	if [[ $df_output = *sdb* ]]; then 
		device=$(grep sdb <<< "$df_output")
	else device=$(grep -P '/$')
	fi
	tr -s ' ' <<< "$device" | cut -d' ' -f4 
}

print_date(){ date '+%a %d/%m %H:%M' ; }

while true; do
	#while true; do print_weather > /tmp/dwmweather; sleep 30m; done &
	#$(< /tmp/dwmweather) 	i'll live with 5s weather for now
	xsetroot -name "$(print_weather) $sep $(print_mpc) $sep $(print_network) $sep $(print_bat) $sep $(print_cpu) $sep $(print_mem) $sep $(print_disk) $sep $(print_date)"
	sleep "$int"
done
# & puts the process into the background, where it cannot be killed by dwm

