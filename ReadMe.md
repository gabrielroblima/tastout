Signal tattooing to embedded information in a noisy digital signal.

Tattoo type: spread ASCII in head

In tattoo Cimg, some data has its bits spread into a CImg object data. The CImg object data has only the least significant bit modified to guarantee that no important data is lost.
Is recommended to use only integer data types in CImg (8, 16, 32 or 64 bits);

# Install 
~~~ { .bash }
ls ../CImg
make bin
~~~

# Use

~~~ { .bash }
make run
~~~

# Example of output
~~~{ .bash}
roberto-lima@ganl1203:~/Documents/code/tastout$ ./tastout -s false
Non tattooed data
CImg<uint16>: this = 0x7fff24fb7510, size = (8192,1,1,1) [16 Kio], data = (uint16*)0x62e4ab03a340..0x62e4ab03e33f (shared) = [ 0 0 0 0 0 0 0 0 ... 0 0 0 0 0 0 0 0 ], min = 0, max = 65535, mean = 17.3097, std = 829.553, coords_min = (0,0,0,0), coords_max = (4096,0,0,0).
Tattooed data
CImg<uint16>: this = 0x7fff24fb7510, size = (8192,1,1,1) [16 Kio], data = (uint16*)0x62e4ab03e340..0x62e4ab04233f (shared) = [ 0 1 0 1 0 1 0 0 ... 0 0 0 0 0 0 0 0 ], min = 0, max = 65535, mean = 17.3231, std = 829.553, coords_min = (0,0,0,0), coords_max = (4096,0,0,0).
Received Data
CImg<uint16>: this = 0x7fff24fb7510, size = (4,1,1,1) [8 b], data = (uint16*)0x62e4ab042900..0x62e4ab042907 (non-shared) = [ 4096 4096 65535 0 ], min = 0, max = 65535, mean = 18431.8, std = 31461.5, coords_min = (3,0,0,0), coords_max = (2,0,0,0).
