#!/bin/bash

get_cpu(){
    echo "CPU: $(lscpu | awk -F ': ' '/Nazwa modelu/ {print $2}')"
}

get_memory(){
    used=$(free -m | awk '/Pamięć:/ {print $3}')
    total=$(free -m | awk '/Pamięć:/ {print $2}')
    percent=$((used*100/total))
    echo "Memory: ${used} / ${total} MiB (${percent}% used)"
}

get_load(){
    echo "Load: $(uptime | awk -F 'load average:' '{print $2}' | xargs)"
}

get_uptime(){
    echo "Uptime: $(uptime -p)"
}

get_kernel(){
    echo "Kernel: $(uname -r)"
}

get_gpu(){
    echo "GPU: $(lspci | grep -i vga | awk -F ': ' '{print $2}')"
}

get_user(){
    echo "User: $USER"
}

get_shell(){
    echo "Shell: $SHELL"
}

get_processes(){
    echo "Processes: $(ps -e --no-headers | wc -l)"
}

get_threads(){
    echo "Threads: $(ps -eLf --no-headers | wc -l)"
}

get_ip(){
    echo "IP: $(hostname -I)"
}

get_dns(){
    echo "DNS: $(awk '/^nameserver/ {print $2}' /etc/resolv.conf | tr '\n' ' ')"
}

get_internet(){
    if ping -c 1 -w 8.8.8.8 &>/dev/null; then
        echo "Internet: OK"
    else
        echo "Internet: FAIL"
    fi
}

# wywoływanie informacji

# wszystkie

show_all() {
    get_cpu
    get_memory
    get_load
    get_uptime
    get_kernel
    get_gpu
    get_user
    get_shell
    get_processes
    get_threads
    get_ip
    get_dns
    get_internet
}

# po argumentach

if [[ $# -eq 0 ]]; then
    show_all
else
    for arg in "$@"; do
            case "${arg,,}" in
            cpu) get_cpu ;;
            memory) get_memory ;;
            load) get_load ;;
            uptime) get_uptime ;;
            kernel) get_kernel ;;
            gpu) get_gpu ;;
            user) get_user ;;
            shell) get_shell ;;
            processes) get_processes ;;
            threads) get_threads ;;
            ip) get_ip ;;
            dns) get_dns ;;
            internet) get_internet ;;
            *) echo "Invalid argument: $arg"; exit 1 ;;
        esac
    done
fi
exit 0