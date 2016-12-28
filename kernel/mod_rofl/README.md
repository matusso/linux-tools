# mod_rofl
easy kernel module for show random jokes in /dev/rofl 
(it has been created just for fun)

##### installation #####
<pre>
$ cd linux-tools/kernel/mod_rofl
$ make
$ sudo su
# insmod rofl.ko
</pre>

##### example #####
<pre>
# cat /dev/rofl
I am a nobody, nobody is perfect, therefore I am perfect.
</pre>

##### cleanup module #####
<pre>
# rmmod rofl
</pre>
