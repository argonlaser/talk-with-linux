# talk-with-the-linux
This repository aims to explore all the functionality of linux with simple programs. Lets talk with the linux !

# Install linux headers
Since we are talking to the linux, we need to know its language. So, lets install their headers first.
Depending on the linux distro, use apt-get or yum.
```linux
$ apt-get install build-essential linux-headers-$(uname -r)
```
Check your headers are installed on ```/lib/modules/$(uname -r)```. 
Now, we have all the stuffs needed to talk with the linux in the above folder.

# Play with linux
Go to every folder in the workspace, compile and talk with the linux!



