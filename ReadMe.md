Signal tattooing to embedded information in a noisy digital signal.

Tattoo type: spread ASCII in head

In tattoo Cimg, some data has its bits spread into a CImg object data. The CImg object data has only the least significant bit modified to guarantee that no important data is lost.
Is recommended to use only integer data types in CImg (8, 16, 32 or 64 bits);

# Install 
~~~ { .bash }
make bin
~~~

# Use

~~~ { .bash }
make run
~~~

# Example of output
~~~{ .bash}
Non tattooed data
CImg<uint16>: this = 0x7ffcff321e60, size = (8192,1,1,1) [16 Kio], data = (uint16*)0x59dfe2760320..0x59dfe276431f (non-shared) = [ 0 0 0 0 0 0 0 0 ... 0 0 0 0 0 0 0 0 ], min = 0, max = 65535, mean = 17.3097, std = 829.553, coords_min = (0,0,0,0), coords_max = (4096,0,0,0).
Tattooed data
CImg<uint16>: this = 0x7ffcff321e40, size = (8192,1,1,1) [16 Kio], data = (uint16*)0x59dfe275c310..0x59dfe276030f (non-shared) = [ 0 1 0 1 0 1 0 0 ... 0 0 0 0 0 0 0 0 ], min = 0, max = 65535, mean = 17.3231, std = 829.553, coords_min = (0,0,0,0), coords_max = (4096,0,0,0).
Received info = 4096
Received info = 4096
Received info = 65535
Received info = 0
