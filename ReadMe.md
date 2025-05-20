Signal tattooing to embedded information in a noisy digital signal.

Tattoo type: spread ASCII in head

In tattoo Cimg, some data has its bits spread into a CImg object data. The CImg object data has only the least significant bit modified to guarantee that no important data is lost. CImg is send via TCP/IP using TCP_ZMQ library.
Is recommended to use only integer data types in CImg (8, 16, 32 or 64 bits);

# Install 
~~~ { .bash }
ls ../CImg
ls ../tcp_zmq
make bin
~~~

# Use

~~~ { .bash }
./send
./recv
~~~

# Example of sender output
~~~{ .bash}
roberto-lima@ganl1203:~/Documents/code/tastout$ ./send -a 10.10.4.14
CImgList<uint8>: this = 0x7ffdd403d7c0, size = 1/16 [9 Kio], data = (CImg<uint8>*)0x64549b7298c8..0x64549b7298e7.
  [0]: this = 0x64549b7298c8, size = (100,100,1,1) [9 Kio], data = (uint8*)0x64549b745b20..0x64549b74822f (non-shared) = [ 122 76 21 33 107 28 31 31 ... 36 115 19 65 3 134 70 78 ], min = 1, max = 135, mean = 67.8618, std = 39.1393, coords_min = (14,1,0,0), coords_max = (83,1,0,0).
~~~

# Example of receiver output
~~~{ .bash}
ubuntu22@ubuntu22:~/code/tastout$ ./recv
Waiting for number of data to receive or stop signal.
Received 1 iterations.
Dimensions assigned N = 1 X = 100 Y = 100 Z = 1 C = 1
Tattooed Max = 110 Tattooed Min = 7

CImgList<unsigned char>: this = 0x7ffdb0df5b70, size = 1/16 [9 Kio], data = (CImg<unsigned char>*)0x5646639ac6f8..0x5646639ac717.
  [0]: this = 0x5646639ac6f8, size = (100,100,1,1) [9 Kio], data = (unsigned char*)0x5646639acd70..0x5646639af47f (non-shared) = [ 100 65 22 31 88 29 30 30 ... 34 95 21 56 9 110 60 67 ], min = 7, max = 110, mean = 58.3969, std = 30.1532, coords_min = (99,0,0,0), coords_max = (83,1,0,0).
Waiting for number of data to receive or stop signal.
Stop received
