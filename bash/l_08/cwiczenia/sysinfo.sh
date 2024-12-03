#!/bin/bash

Cpu(){
    echo "CPU: "
    lscpu | grep "Nazwa modelu:" | sed -r 's/Nazwa modelu:\s{1,}//g'
}

Memory(){
    echo "Memory :"
    free -m | grep "Pamięć:" | awk '{print $3 "/" $2 "MiB (" ($3/$2)*100 "% used)"}'
    free -m | grep "Memory:" | awk '{print $3 "/" $2 "MiB (" ($3/$2)*100 "% used)"}'
    
}

Load(){

}

Uptime(){
    echo "Uptime: "
    uptime -p
}

Kernel(){
    echo "Kernel: "
    uname -r
}

Gpu(){

}

User(){
    echo "User: "$USER
}

Shell(){

}

Processes(){

}

Threads(){

}

Ip(){

}

Dns(){

}

Internet(){

}

