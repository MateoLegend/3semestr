#!/bin/bash

list_cpu(){
    echo "Top 5 processes by CPU usage:"
    ps -eo pid,comm,%cpu --sort=-%cpu | head -n 6
}

list_memory(){
    echo "Top 5 processes by memory usage:"
    ps -eo pid,comm,%mem --sort=-%mem | head -n 6
}

show_tree(){
    echo "Process tree:"
    pstree -p
}

show_pid_by_name() {
    read -p "Enter process name: " pname
    pgrep -l "$pname"
}

kill_by_pid(){
    read -p "Enter PID to kill: " pid
    kill "$pid" && echo "Process $pid killed." || echo "Failed to kill process $pid."
}

kill_by_name(){
    read -p "Enter process name to kill: " pname
    pkill "$pname" && echo "Processes named $pname killed." || echo "Failed to kill processes named $pname."
}

# wyswietlenie menu
while true; do
    echo "Process Control:"
    echo "1) List top 5 processes by CPU usage"
    echo "2) List top 5 processes by memory usage"
    echo "3) Show process tree"
    echo "4) Show process name by PID"
    echo "5) Show process PID(s) by name"
    echo "6) Kill process by PID"
    echo "7) Kill process by name"
    echo "q) Exit"
    read -p "Choice: " choice

    case $choice in
        1) list_cpu ;;
        2) list_memory ;;
        3) show_tree ;;
        4) show_pid_by_name ;;
        5) show_pid_by_name ;;
        6) kill_by_pid ;;
        7) kill_by_name ;;
        q) echo "Exiting..."; break ;;
        *) echo "Invalid option." ;;
    esac
done
exit 0